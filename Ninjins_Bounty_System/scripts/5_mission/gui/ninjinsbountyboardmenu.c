class obfc_NinjinsBountyBoardMenu extends UIScriptedMenu
{
	private ButtonWidget obfv_m_BttnCancel;
	private ButtonWidget obfv_m_BttnSkip;
	private ButtonWidget obfv_m_BttnClaimRewards;
	private ButtonWidget obfv_m_BttnClaimMoney;
	private ButtonWidget obfv_m_BttnPlaceBounty;
	private ButtonWidget obfv_m_BttnClose;
	private TextListboxWidget obfv_m_BountyOnlinePlayersList;
	private TextWidget obfv_m_ClaimAmount;
	private ref array<string> obfv_m_OnlinePlayerIdentifiers;
	void obfc_NinjinsBountyBoardMenu()
	{
		obfv_m_OnlinePlayerIdentifiers = new array<string>();
	}
	private string obfm_GetPlayerEntryDisplayName(string entry)
	{
		int separatorIndex = entry.IndexOf("||");
		if (separatorIndex < 0)
			return entry;
		return entry.Substring(0, separatorIndex);
	}
	private string obfm_GetPlayerEntryIdentifier(string entry)
	{
		int separatorIndex = entry.IndexOf("||");
		if (separatorIndex < 0 || separatorIndex >= entry.Length() - 2)
			return entry;
		return entry.Substring(separatorIndex + 2, entry.Length() - (separatorIndex + 2));
	}
	override Widget Init()
	{
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Init() called, loading layout...");
		layoutRoot = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/NinjinsBountyBoard.layout");
		if (!layoutRoot)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[NinjinsBountyBoardMenu] Failed to load layout: Ninjins_Bounty_System/gui/layouts/NinjinsBountyBoard.layout");
			return NULL;
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Layout loaded successfully.");
		obfv_m_BttnCancel = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnCancel"));
		obfv_m_BttnSkip = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnSkip"));
		obfv_m_BttnClaimRewards = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClaimRewards"));
		obfv_m_BttnClaimMoney = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClaimMoney"));
		obfv_m_BttnPlaceBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnPlaceBounty"));
		obfv_m_BttnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClose"));
		obfv_m_BountyOnlinePlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("OnlinePlayersList"));
		obfv_m_ClaimAmount = TextWidget.Cast(layoutRoot.FindAnyWidget("ClaimAmount"));
		if (!obfv_m_BountyOnlinePlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] OnlinePlayersList widget not found in layout!");
		}
		if (!obfv_m_ClaimAmount)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] ClaimAmount widget not found in layout!");
		}
		obfm_RefreshOnlinePlayers();
		obfm_RefreshClaimAmount();
		return layoutRoot;
	}
	override void OnShow()
	{
		PlayerBase player;
		super.OnShow();
		player = PlayerBase.Cast(g_Game.GetPlayer());
		PPEffects.SetBlurMenu(0.5);
		g_Game.GetInput().ChangeGameFocus(1);
		g_Game.GetUIManager().ShowUICursor(true);
		g_Game.GetMission().GetHud().Show(false);
		TIntArray skip = { UAUIBack };
		obfm_ForceDisableInputs(true, skip);
		SetFocus(layoutRoot);
		obfm_RefreshOnlinePlayers();
		obfm_RefreshClaimAmount();
	}
	void obfm_RefreshClaimAmount()
	{
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestClaimAmount", new Param1<int>(0), true, player.GetIdentity());
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Requested claim amount from server via RPC");
	}
	void obfm_UpdateClaimAmount(int claimAmount)
	{
		string claimText;
		if (!obfv_m_ClaimAmount)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] Cannot update - ClaimAmount widget is null!");
			return;
		}
		claimText = "x " + claimAmount.ToString();
		obfv_m_ClaimAmount.SetText(claimText);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Updated claim amount: " + claimAmount.ToString());
	}
	static void obfm_ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
	{
		if (!skipIDs)
			skipIDs = new TIntArray;
		skipIDs.Insert(UAUIBack);
		TIntArray inputIDs = new TIntArray;
		GetUApi().GetActiveInputs(inputIDs);
		foreach (int inputID : inputIDs)
		{
			if (skipIDs.Find(inputID) == -1)
			{
				GetUApi().GetInputByID(inputID).ForceDisable(state);
			}
		}
	}
	override bool OnClick(Widget w, int x, int y, int button)
	{
		PlayerBase player;
		int selectedRow;
		string selectedPlayerName;
		string selectedPlayerIdentifier;
		super.OnClick(w, x, y, button);
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return false;
		if (w == obfv_m_BttnCancel || w == obfv_m_BttnClose)
		{
			OnHide();
			return true;
		}
		else if (w == obfv_m_BttnSkip)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("SkipBounty"), true, player.GetIdentity());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Skip button clicked - requesting bounty transfer");
			return true;
		}
		else if (w == obfv_m_BttnClaimRewards)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("ClaimRewards"), true, player.GetIdentity());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Claim Rewards button clicked - requesting reward chest claim");
			return true;
		}
		else if (w == obfv_m_BttnClaimMoney)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("ClaimCurrencyRewards"), true, player.GetIdentity());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Claim Money button clicked - requesting currency rewards claim");
			return true;
		}
		else if (w == obfv_m_BttnPlaceBounty)
		{
			if (obfv_m_BountyOnlinePlayersList)
			{
				selectedRow = obfv_m_BountyOnlinePlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_OnlinePlayerIdentifiers.Count())
					{
						selectedPlayerIdentifier = obfv_m_OnlinePlayerIdentifiers.Get(selectedRow);
					}
					obfv_m_BountyOnlinePlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("PlaceBountyOnPlayer:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Place Bounty button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] No player selected from list!");
				}
			}
			return true;
		}
		return false;
	}
	void obfm_RefreshOnlinePlayers()
	{
		if (!obfv_m_BountyOnlinePlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] Cannot refresh - OnlinePlayersList widget is null!");
			return;
		}
		obfv_m_BountyOnlinePlayersList.ClearItems();
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", new Param1<int>(0), true, null);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Requested online players list from server via RPC");
	}
	void obfm_UpdateOnlinePlayersList(array<string> players)
	{
		if (!obfv_m_BountyOnlinePlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] Cannot update - OnlinePlayersList widget is null!");
			return;
		}
		obfv_m_BountyOnlinePlayersList.ClearItems();
		obfv_m_OnlinePlayerIdentifiers.Clear();
		if (!players)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[NinjinsBountyBoardMenu] Received null players array from server!");
			return;
		}
		foreach (string playerEntry : players)
		{
			if (playerEntry != "")
			{
				obfv_m_OnlinePlayerIdentifiers.Insert(obfm_GetPlayerEntryIdentifier(playerEntry));
				obfv_m_BountyOnlinePlayersList.AddItem(obfm_GetPlayerEntryDisplayName(playerEntry), null, 0);
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[NinjinsBountyBoardMenu] Updated online players list: " + players.Count().ToString() + " players");
	}
	override void OnHide()
	{
		PlayerBase player;
		super.OnHide();
		player = PlayerBase.Cast(g_Game.GetPlayer());
		obfm_ForceDisableInputs(false);
		PPEffects.SetBlurMenu(0);
		g_Game.GetInput().ResetGameFocus();
		g_Game.GetUIManager().ShowUICursor(false);
		g_Game.GetMission().GetHud().Show(true);
		Close();
	}
}