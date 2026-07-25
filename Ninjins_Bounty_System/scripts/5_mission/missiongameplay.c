modded class MissionGameplay
{
	private bool obfv_m_RequestedBountiedPlayers = false;
	ref obfc_BountyAdminMenu obfv_m_BountyAdminMenu;
	ref obfc_NinjinsBountyBoardMenu obfv_m_BountyBoardMenu;
	private Widget obfv_m_RootWidgetBountyCountdown;
	private RichTextWidget obfv_m_BountyCountdownTimer;
	private float obfv_m_BountyLastCountdownUpdateTime = 0.0;
	private const float obfv_BOUNTY_COUNTDOWN_UPDATE_INTERVAL = 1.0; 
	private float obfv_m_BountyLastReceivedDuration = 0.0; 
	private float obfv_m_BountyLastReceivedTime = 0.0; 
	private float obfv_m_BountyLastSyncWarningTime = 0.0;
	private bool obfv_m_BountyPaused = false; 
	private const float obfv_BOUNTY_SYNC_WARNING_INTERVAL = 5.0; 
	void MissionGameplay()
	{
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Ninjins_Bounty_System mod has started!");
	}
	override void OnInit()
	{
		super.OnInit();
		obfm_RegisterBountyRPCs();
		obfm_LoadBountyCountdownLayout();
		if (obfv_m_RootWidgetBountyCountdown)
		{
			obfv_m_RootWidgetBountyCountdown.Show(false);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] BountyCountdownTimer widget explicitly hidden in OnInit.");
		}
	}
	private void obfm_RegisterBountyRPCs()
	{
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "ReceiveBountiedPlayers", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyReceiveOnlinePlayers", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminReceivePlayers", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyCloseBoardMenu", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "UpdateBountyState", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyUpdatePaused", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyConfigReloaded", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminReceiveConfig", this, SingleplayerExecutionType.Client);
	}
	private void obfm_LoadBountyCountdownLayout()
	{
		obfv_m_RootWidgetBountyCountdown = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyCountdownTimer.layout");
		if (obfv_m_RootWidgetBountyCountdown)
		{
			obfm_InitializeBountyCountdownWidgets();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] BountyCountdownTimer UI loaded successfully.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[MissionGameplay][ERROR] Failed to create BountyCountdownTimer layout widget.");
		}
	}
	private void obfm_InitializeBountyCountdownWidgets()
	{
		obfv_m_BountyCountdownTimer = RichTextWidget.Cast(obfv_m_RootWidgetBountyCountdown.FindAnyWidget("BountyCountdownTimer"));
		if (obfv_m_BountyCountdownTimer)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] BountyCountdownTimer found successfully.");
			obfv_m_RootWidgetBountyCountdown.Show(false);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] BountyCountdownTimer widget hidden on initialization.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[MissionGameplay][ERROR] Failed to find BountyCountdownTimer widget.");
		}
		obfm_ApplyBountyCountdownPosition(0.0, 0.0, 0.0, 0.0, 0, 0);
	}
	private void obfm_ApplyBountyCountdownPosition(float posX = 0.0, float posY = 0.0, float width = 0.0, float height = 0.0, int bgColor = 0, int textColor = 0)
	{
		if (!obfv_m_RootWidgetBountyCountdown)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] ApplyBountyCountdownPosition: Missing widget");
			return;
		}
		Widget countdownWidget = obfv_m_RootWidgetBountyCountdown.FindAnyWidget("BountyCountdownWidget");
		if (!countdownWidget)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] ApplyBountyCountdownPosition: BountyCountdownWidget not found");
			return;
		}
		countdownWidget.SetPos(posX, posY);
		if (width > 0.0 || height > 0.0)
		{
			float currentWidth;
			float currentHeight;
			countdownWidget.GetSize(currentWidth, currentHeight);
			if (width > 0.0)
				currentWidth = width;
			if (height > 0.0)
				currentHeight = height;
			countdownWidget.SetSize(currentWidth, currentHeight);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Applied countdown widget size: Width=" + currentWidth.ToString() + ", Height=" + currentHeight.ToString());
		}
		if (bgColor != 0)
		{
			countdownWidget.SetColor(bgColor);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Applied countdown widget background color: " + bgColor.ToString());
		}
		if (textColor != 0 && obfv_m_BountyCountdownTimer)
		{
			obfv_m_BountyCountdownTimer.SetColor(textColor);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Applied countdown timer text color: " + textColor.ToString());
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Applied countdown widget settings: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
	}
	override void OnUpdate(float timeslice)
	{
		PlayerBase player;
		super.OnUpdate(timeslice);
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player)
			return;
		obfm_ControlBountyInputs();
		obfm_UpdateBountyCountdownTimer();
		if (!obfv_m_RequestedBountiedPlayers && player.GetIdentity())
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", NULL, true, null);
			obfv_m_RequestedBountiedPlayers = true;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] RequestBountiedPlayers RPC sent from client.");
		}
	}
	private void obfm_UpdateBountyCountdownTimer()
	{
		PlayerBase player;
		bool hasBounty;
		float currentTimeSeconds;
		float remainingDuration;
		float elapsedSinceLastRPC;
		bool shouldUpdate;
		int totalSeconds;
		int hours;
		int minutes;
		int seconds;
		string secondsStr;
		string countdownTimeStr;
		string minutesStr;
		string countdownText;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !obfv_m_RootWidgetBountyCountdown || !obfv_m_BountyCountdownTimer)
			return;
		hasBounty = player.obfm_HasBounty();
		currentTimeSeconds = g_Game.GetTime() / 1000.0; 
		remainingDuration = 0.0;
		if (hasBounty && obfv_m_BountyLastReceivedTime > 0.0)
		{
			if (!obfv_m_BountyPaused)
			{
				elapsedSinceLastRPC = currentTimeSeconds - obfv_m_BountyLastReceivedTime;
				remainingDuration = obfv_m_BountyLastReceivedDuration - elapsedSinceLastRPC;
			}
			else
			{
				remainingDuration = obfv_m_BountyLastReceivedDuration;
			}
			if (remainingDuration < 0.0)
			{
				remainingDuration = 0.0;
			}
		}
		else
		{
			remainingDuration = player.netSync_BountyRemainingDuration;
		}
		shouldUpdate = (currentTimeSeconds - obfv_m_BountyLastCountdownUpdateTime >= obfv_BOUNTY_COUNTDOWN_UPDATE_INTERVAL);
		if (hasBounty && remainingDuration > 0.0)
		{
			if (!obfv_m_RootWidgetBountyCountdown.IsVisible())
			{
				obfv_m_RootWidgetBountyCountdown.Show(true);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Showing bounty countdown timer (bounty detected). HasBounty: " + hasBounty.ToString() + ", RemainingDuration: " + remainingDuration.ToString() + "s");
			}
			if (shouldUpdate)
			{
				obfv_m_BountyLastCountdownUpdateTime = currentTimeSeconds;
				totalSeconds = Math.Floor(remainingDuration);
				hours = Math.Floor(totalSeconds / 3600.0);
				minutes = Math.Floor((totalSeconds - (hours * 3600)) / 60.0);
				seconds = totalSeconds - (hours * 3600) - (minutes * 60);
				secondsStr = seconds.ToString();
				if (seconds < 10)
				{
					secondsStr = "0" + secondsStr;
				}
				if (hours > 0)
				{
					minutesStr = minutes.ToString();
					if (minutes < 10)
					{
						minutesStr = "0" + minutesStr;
					}
					countdownTimeStr = hours.ToString() + ":" + minutesStr + ":" + secondsStr;
				}
				else
				{
					countdownTimeStr = minutes.ToString() + ":" + secondsStr;
				}
				countdownText = "You are on Bounty: " + countdownTimeStr;
				if (obfv_m_BountyPaused)
				{
					countdownText = countdownText + " (PAUSED)";
				}
				obfv_m_BountyCountdownTimer.SetText(countdownText);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Updated bounty countdown: " + countdownText + " (remaining: " + remainingDuration.ToString() + "s, paused: " + obfv_m_BountyPaused.ToString() + ")");
			}
		}
		else if (hasBounty && remainingDuration <= 0.0)
		{
			if (currentTimeSeconds - obfv_m_BountyLastSyncWarningTime >= obfv_BOUNTY_SYNC_WARNING_INTERVAL)
			{
				obfv_m_BountyLastSyncWarningTime = currentTimeSeconds;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Player has bounty but remainingDuration is " + remainingDuration.ToString() + "s - waiting for RPC sync...");
			}
		}
		else
		{
			if (obfv_m_RootWidgetBountyCountdown.IsVisible())
			{
				obfm_HideBountyCountdownTimer();
			}
		}
	}
	private void obfm_ShowBountyCountdownTimer()
	{
		if (obfv_m_RootWidgetBountyCountdown && obfv_m_BountyCountdownTimer)
		{
			obfv_m_RootWidgetBountyCountdown.Show(true);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogDebug("[MissionGameplay] Showing bounty countdown timer UI.");
		}
	}
	private void obfm_HideBountyCountdownTimer()
	{
		if (obfv_m_RootWidgetBountyCountdown && obfv_m_BountyCountdownTimer)
		{
			obfv_m_BountyCountdownTimer.SetText("");
			obfv_m_RootWidgetBountyCountdown.Show(false);
		}
	}
	private void obfm_ControlBountyInputs()
	{
		UIScriptedMenu currentMenu = g_Game.GetUIManager().GetMenu();
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		if (GetUApi().GetInputByName("UAUIBack").LocalPress())
		{
			if (currentMenu && currentMenu.IsInherited(obfc_BountyAdminMenu))
			{
				currentMenu.OnHide();
				obfv_m_BountyAdminMenu = null;
				return;
			}
			if (currentMenu && currentMenu.IsInherited(obfc_NinjinsBountyBoardMenu))
			{
				currentMenu.OnHide();
				obfv_m_BountyBoardMenu = null;
				return;
			}
		}
		if (GetUApi().GetInputByName("UABountyAdminMenu").LocalPress())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[ControlBountyInputs] UABountyAdminMenu hotkey pressed");
			if (!player.obfm_IsBountyAdmin())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[ControlBountyInputs] Player is not admin. GUID: " + player.GetIdentity().GetId());
				NotificationSystem.Create(new StringLocaliser("Access Denied"), new StringLocaliser("You do not have permission to access the bounty admin menu."), "Ninjins_Bounty_System/gui/icons/bountyerror.edds", ARGB(255, 255, 0, 0), 5.0, player.GetIdentity());
				return;
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[ControlBountyInputs] Player is admin. GUID: " + player.GetIdentity().GetId() + ". Opening menu.");
			if (currentMenu && !currentMenu.IsInherited(obfc_BountyAdminMenu))
				return;
			if (currentMenu && currentMenu.IsInherited(obfc_BountyAdminMenu))
			{
				g_Game.GetUIManager().HideScriptedMenu(currentMenu);
				obfv_m_BountyAdminMenu = null;
			}
			else
			{
				obfv_m_BountyAdminMenu = new obfc_BountyAdminMenu();
				g_Game.GetUIManager().ShowScriptedMenu(obfv_m_BountyAdminMenu, NULL);
			}
		}
	}
	void ReceiveBountiedPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<ref obfc_BountyPlayerData>> data;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read bountied players data from RPC.");
			return;
		}
		if (data && data.param1)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " bountied players via RPC.");
			obfc_BountyMapBridge.obfm_SetBountiedPlayers(data.param1);
		}
	}
	void BountyReceiveOnlinePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<string>> data;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read online players data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(obfc_NinjinsBountyBoardMenu))
		{
			obfc_NinjinsBountyBoardMenu bountyMenu = obfc_NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu && data && data.param1)
			{
				bountyMenu.obfm_UpdateOnlinePlayersList(data.param1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " online players via RPC.");
			}
		}
		else if (menu && menu.IsInherited(obfc_BountyAdminMenu))
		{
			obfc_BountyAdminMenu adminMenu = obfc_BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.obfm_UpdateOnlinePlayersList(data.param1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " online players for admin menu via RPC.");
			}
		}
	}
	void BountyAdminReceivePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<string>> data;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read admin players data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(obfc_BountyAdminMenu))
		{
			obfc_BountyAdminMenu adminMenu = obfc_BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.obfm_UpdatePlayersList(data.param1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " admin players via RPC.");
			}
		}
	}
	void BountyAdminReceiveBlacklist(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<string>> data;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read blacklist data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(obfc_BountyAdminMenu))
		{
			obfc_BountyAdminMenu adminMenu = obfc_BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.obfm_UpdateBlacklistedPlayersList(data.param1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " blacklisted players via RPC.");
			}
		}
	}
	void OpenBountyBoardMenuDirect()
	{
		UIScriptedMenu currentMenu = g_Game.GetUIManager().GetMenu();
		if (currentMenu && !currentMenu.IsInherited(obfc_NinjinsBountyBoardMenu))
			return;
		if (currentMenu && currentMenu.IsInherited(obfc_NinjinsBountyBoardMenu))
		{
			g_Game.GetUIManager().HideScriptedMenu(currentMenu);
			obfv_m_BountyBoardMenu = null;
		}
		else
		{
			obfv_m_BountyBoardMenu = new obfc_NinjinsBountyBoardMenu();
			g_Game.GetUIManager().ShowScriptedMenu(obfv_m_BountyBoardMenu, NULL);
		}
	}
	void BountyCloseBoardMenu(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(obfc_NinjinsBountyBoardMenu))
		{
			obfc_NinjinsBountyBoardMenu bountyMenu = obfc_NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu)
			{
				bountyMenu.OnHide();
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Closed bounty board menu via RPC (inventory full).");
			}
		}
	}
	void BountyReceiveClaimAmount(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<int> data;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read claim amount data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(obfc_NinjinsBountyBoardMenu))
		{
			obfc_NinjinsBountyBoardMenu bountyMenu = obfc_NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu && data)
			{
				bountyMenu.obfm_UpdateClaimAmount(data.param1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received claim amount via RPC: " + data.param1.ToString());
			}
		}
	}
	void BountyUpdateCountdown(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<float> data;
		float currentTimeSeconds;
		PlayerBase player;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read bounty countdown data from RPC.");
			return;
		}
		currentTimeSeconds = g_Game.GetTime() / 1000.0;
		obfv_m_BountyLastReceivedDuration = data.param1;
		obfv_m_BountyLastReceivedTime = currentTimeSeconds;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
		{
			player.netSync_BountyRemainingDuration = data.param1;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received bounty countdown update: " + data.param1.ToString() + " seconds - stored for client-driven countdown");
		}
	}
	void UpdateBountyState(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<bool> data;
		PlayerBase player;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read bounty state data from RPC.");
			return;
		}
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
		{
			player.netSync_HasBounty = data.param1;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received bounty state update: " + data.param1.ToString() + " via RPC");
		}
	}
	void BountyUpdatePaused(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<bool> data;
		float currentTimeSeconds;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(data))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read bounty paused state data from RPC.");
			return;
		}
		obfv_m_BountyPaused = data.param1;
		if (!obfv_m_BountyPaused)
		{
			currentTimeSeconds = g_Game.GetTime() / 1000.0;
			obfv_m_BountyLastReceivedTime = currentTimeSeconds;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Bounty countdown resumed - resyncing timer");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Bounty countdown paused");
		}
	}
	void BountyConfigReloaded(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<obfc_BountyUISettingsData> uiDataParam;
		obfc_BountyUISettingsData uiData;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(uiDataParam))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read UI data from BountyConfigReloaded RPC.");
			return;
		}
		uiData = uiDataParam.param1;
		if (!uiData)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] UI data is null from BountyConfigReloaded RPC.");
			return;
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received BountyConfigReloaded RPC - reapplying UI. X=" + uiData.obfv_PositionX.ToString() + ", Y=" + uiData.obfv_PositionY.ToString() + ", Width=" + uiData.obfv_Width.ToString() + ", Height=" + uiData.obfv_Height.ToString() + ", BGColor=" + uiData.obfv_BackgroundColor.ToString() + ", TextColor=" + uiData.obfv_TextColor.ToString());
		obfm_ApplyBountyCountdownPosition(uiData.obfv_PositionX, uiData.obfv_PositionY, uiData.obfv_Width, uiData.obfv_Height, uiData.obfv_BackgroundColor, uiData.obfv_TextColor);
	}
	void BountyAdminReceiveConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<ref obfc_BountyConfig> configParam;
		obfc_BountyConfig config;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(configParam))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Failed to read config from BountyAdminReceiveConfig RPC.");
			return;
		}
		config = configParam.param1;
		if (!config)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Config is null from BountyAdminReceiveConfig RPC.");
			return;
		}
		if (obfv_m_BountyAdminMenu)
		{
			obfv_m_BountyAdminMenu.obfm_UpdateConfigFromServer(config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionGameplay] Received config and updated admin menu UI.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[MissionGameplay] Admin menu not open - cannot update config.");
		}
	}
};