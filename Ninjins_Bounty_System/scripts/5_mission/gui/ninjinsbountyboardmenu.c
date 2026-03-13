class NinjinsBountyBoardMenu extends UIScriptedMenu
{
    private ButtonWidget m_BttnCancel;
    private ButtonWidget m_BttnSkip;
    private ButtonWidget m_BttnClaimRewards;
    private ButtonWidget m_BttnClaimMoney;
    private ButtonWidget m_BttnPlaceBounty;
    private ButtonWidget m_BttnClose;
    private TextListboxWidget m_BountyOnlinePlayersList;
    private TextWidget m_ClaimAmount;
    private ref array<string> m_OnlinePlayerIdentifiers;
    void NinjinsBountyBoardMenu()
    {
        m_OnlinePlayerIdentifiers = new array<string>();
    }
    private string GetPlayerEntryDisplayName(string entry)
    {
        int separatorIndex = entry.IndexOf("||");
        if (separatorIndex < 0)
            return entry;
        return entry.Substring(0, separatorIndex);
    }
    private string GetPlayerEntryIdentifier(string entry)
    {
        int separatorIndex = entry.IndexOf("||");
        if (separatorIndex < 0 || separatorIndex >= entry.Length() - 2)
            return entry;
        return entry.Substring(separatorIndex + 2, entry.Length() - (separatorIndex + 2));
    }
    override Widget Init()
    {
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Init() called, loading layout...");
        layoutRoot = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/NinjinsBountyBoard.layout");
        if (!layoutRoot)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[NinjinsBountyBoardMenu] Failed to load layout: Ninjins_Bounty_System/gui/layouts/NinjinsBountyBoard.layout");
            return NULL;
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Layout loaded successfully.");
        m_BttnCancel = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnCancel"));
        m_BttnSkip = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnSkip"));
        m_BttnClaimRewards = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClaimRewards"));
        m_BttnClaimMoney = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClaimMoney"));
        m_BttnPlaceBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnPlaceBounty"));
        m_BttnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BttnClose"));
        m_BountyOnlinePlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("OnlinePlayersList"));
        m_ClaimAmount = TextWidget.Cast(layoutRoot.FindAnyWidget("ClaimAmount"));
        if (!m_BountyOnlinePlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] OnlinePlayersList widget not found in layout!");
        }
        if (!m_ClaimAmount)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] ClaimAmount widget not found in layout!");
        }
        RefreshOnlinePlayers();
        RefreshClaimAmount();
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
        ForceDisableInputs(true, skip);
        SetFocus(layoutRoot);
        RefreshOnlinePlayers();
        RefreshClaimAmount();
    }
    void RefreshClaimAmount()
    {
        PlayerBase player;
        player = PlayerBase.Cast(g_Game.GetPlayer());
        if (!player || !player.GetIdentity())
            return;
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestClaimAmount", new Param1<int>(0), true, player.GetIdentity());
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Requested claim amount from server via RPC");
    }
    void UpdateClaimAmount(int claimAmount)
    {
        string claimText;
        if (!m_ClaimAmount)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] Cannot update - ClaimAmount widget is null!");
            return;
        }
        claimText = "x " + claimAmount.ToString();
        m_ClaimAmount.SetText(claimText);
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Updated claim amount: " + claimAmount.ToString());
    }
    static void ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
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
        if (w == m_BttnCancel || w == m_BttnClose)
        {
            OnHide();
            return true;
        }
        else if (w == m_BttnSkip)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("SkipBounty"), true, player.GetIdentity());
            GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Skip button clicked - requesting bounty transfer");
            return true;
        }
        else if (w == m_BttnClaimRewards)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("ClaimRewards"), true, player.GetIdentity());
            GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Claim Rewards button clicked - requesting reward chest claim");
            return true;
        }
        else if (w == m_BttnClaimMoney)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("ClaimCurrencyRewards"), true, player.GetIdentity());
            GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Claim Money button clicked - requesting currency rewards claim");
            return true;
        }
        else if (w == m_BttnPlaceBounty)
        {
            if (m_BountyOnlinePlayersList)
            {
                selectedRow = m_BountyOnlinePlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    if (selectedRow < m_OnlinePlayerIdentifiers.Count())
                    {
                        selectedPlayerIdentifier = m_OnlinePlayerIdentifiers.Get(selectedRow);
                    }
                    m_BountyOnlinePlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerIdentifier != "")
                    {
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BoardBountyAction", new Param1<string>("PlaceBountyOnPlayer:" + selectedPlayerIdentifier), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Place Bounty button clicked for player: " + selectedPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] No player selected from list!");
                }
            }
            return true;
        }
        return false;
    }
    void RefreshOnlinePlayers()
    {
        if (!m_BountyOnlinePlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] Cannot refresh - OnlinePlayersList widget is null!");
            return;
        }
        m_BountyOnlinePlayersList.ClearItems();
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", new Param1<int>(0), true, null);
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Requested online players list from server via RPC");
    }
    void UpdateOnlinePlayersList(array<string> players)
    {
        if (!m_BountyOnlinePlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] Cannot update - OnlinePlayersList widget is null!");
            return;
        }
        m_BountyOnlinePlayersList.ClearItems();
        m_OnlinePlayerIdentifiers.Clear();
        if (!players)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[NinjinsBountyBoardMenu] Received null players array from server!");
            return;
        }
        foreach (string playerEntry : players)
        {
            if (playerEntry != "")
            {
                m_OnlinePlayerIdentifiers.Insert(GetPlayerEntryIdentifier(playerEntry));
                m_BountyOnlinePlayersList.AddItem(GetPlayerEntryDisplayName(playerEntry), null, 0);
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[NinjinsBountyBoardMenu] Updated online players list: " + players.Count().ToString() + " players");
    }
    override void OnHide()
    {
        PlayerBase player;
        super.OnHide();
        player = PlayerBase.Cast(g_Game.GetPlayer());
        ForceDisableInputs(false);
        PPEffects.SetBlurMenu(0);
        g_Game.GetInput().ResetGameFocus();
        g_Game.GetUIManager().ShowUICursor(false);
        g_Game.GetMission().GetHud().Show(true);
        Close();
    }
}