modded class MissionGameplay
{
	private bool m_RequestedBountiedPlayers = false;
	ref BountyAdminMenu m_BountyAdminMenu;
	ref NinjinsBountyBoardMenu m_BountyBoardMenu;
	private Widget m_RootWidgetBountyCountdown;
	private RichTextWidget m_BountyCountdownTimer;
	private float m_LastCountdownUpdateTime = 0.0;
	private const float BOUNTY_COUNTDOWN_UPDATE_INTERVAL = 1.0; 
	private float m_LastReceivedDuration = 0.0; 
	private float m_LastReceivedTime = 0.0; 
	private float m_LastSyncWarningTime = 0.0;
	private bool m_BountyPaused = false; 
	private const float SYNC_WARNING_INTERVAL = 5.0; 
	void MissionGameplay()
	{
		GetNinjins_Bounty_SystemLogger().LogInfo("Ninjins_Bounty_System mod has started!");
	}
	override void OnInit()
	{
		super.OnInit();
		RegisterBountyRPCs();
		LoadBountyCountdownLayout();
		if (m_RootWidgetBountyCountdown)
		{
			m_RootWidgetBountyCountdown.Show(false);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] BountyCountdownTimer widget explicitly hidden in OnInit.");
		}
	}
	private void RegisterBountyRPCs()
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
	private void LoadBountyCountdownLayout()
	{
		m_RootWidgetBountyCountdown = GetGame().GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyCountdownTimer.layout");
		if (m_RootWidgetBountyCountdown)
		{
			InitializeBountyCountdownWidgets();
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] BountyCountdownTimer UI loaded successfully.");
		}
		else
		{
			GetNinjins_Bounty_SystemLogger().LogError("[MissionGameplay][ERROR] Failed to create BountyCountdownTimer layout widget.");
		}
	}
	private void InitializeBountyCountdownWidgets()
	{
		m_BountyCountdownTimer = RichTextWidget.Cast(m_RootWidgetBountyCountdown.FindAnyWidget("BountyCountdownTimer"));
		if (m_BountyCountdownTimer)
		{
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] BountyCountdownTimer found successfully.");
			m_RootWidgetBountyCountdown.Show(false);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] BountyCountdownTimer widget hidden on initialization.");
		}
		else
		{
			GetNinjins_Bounty_SystemLogger().LogError("[MissionGameplay][ERROR] Failed to find BountyCountdownTimer widget.");
		}
		ApplyBountyCountdownPosition(0.0, 0.0, 0.0, 0.0, 0, 0);
	}
	private void ApplyBountyCountdownPosition(float posX = 0.0, float posY = 0.0, float width = 0.0, float height = 0.0, int bgColor = 0, int textColor = 0)
	{
		if (!m_RootWidgetBountyCountdown)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] ApplyBountyCountdownPosition: Missing widget");
			return;
		}
		Widget countdownWidget = m_RootWidgetBountyCountdown.FindAnyWidget("BountyCountdownWidget");
		if (!countdownWidget)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] ApplyBountyCountdownPosition: BountyCountdownWidget not found");
			return;
		}
		countdownWidget.SetPos(posX, posY);
		if (width > 0.0 || height > 0.0)
		{
			float currentWidth, currentHeight;
			countdownWidget.GetSize(currentWidth, currentHeight);
			if (width > 0.0)
				currentWidth = width;
			if (height > 0.0)
				currentHeight = height;
			countdownWidget.SetSize(currentWidth, currentHeight);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Applied countdown widget size: Width=" + currentWidth.ToString() + ", Height=" + currentHeight.ToString());
		}
		if (bgColor != 0)
		{
			countdownWidget.SetColor(bgColor);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Applied countdown widget background color: " + bgColor.ToString());
		}
		if (textColor != 0 && m_BountyCountdownTimer)
		{
			m_BountyCountdownTimer.SetColor(textColor);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Applied countdown timer text color: " + textColor.ToString());
		}
		GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Applied countdown widget settings: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
	}
	override void OnUpdate(float timeslice)
	{
		PlayerBase player;
		super.OnUpdate(timeslice);
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player)
			return;
		ControlBountyInputs();
		UpdateBountyCountdownTimer();
		if (!m_RequestedBountiedPlayers && player.GetIdentity())
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", NULL, true, null);
			m_RequestedBountiedPlayers = true;
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] RequestBountiedPlayers RPC sent from client.");
		}
	}
	private void UpdateBountyCountdownTimer()
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
		if (!player || !m_RootWidgetBountyCountdown || !m_BountyCountdownTimer)
			return;
		hasBounty = player.HasBounty();
		currentTimeSeconds = g_Game.GetTime() / 1000.0; 
		remainingDuration = 0.0;
		if (hasBounty && m_LastReceivedTime > 0.0)
		{
			if (!m_BountyPaused)
			{
				elapsedSinceLastRPC = currentTimeSeconds - m_LastReceivedTime;
				remainingDuration = m_LastReceivedDuration - elapsedSinceLastRPC;
			}
			else
			{
				remainingDuration = m_LastReceivedDuration;
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
		shouldUpdate = (currentTimeSeconds - m_LastCountdownUpdateTime >= BOUNTY_COUNTDOWN_UPDATE_INTERVAL);
		if (hasBounty && remainingDuration > 0.0)
		{
			if (!m_RootWidgetBountyCountdown.IsVisible())
			{
				m_RootWidgetBountyCountdown.Show(true);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Showing bounty countdown timer (bounty detected). HasBounty: " + hasBounty.ToString() + ", RemainingDuration: " + remainingDuration.ToString() + "s");
			}
			if (shouldUpdate)
			{
				m_LastCountdownUpdateTime = currentTimeSeconds;
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
				if (m_BountyPaused)
				{
					countdownText = countdownText + " (PAUSED)";
				}
				m_BountyCountdownTimer.SetText(countdownText);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Updated bounty countdown: " + countdownText + " (remaining: " + remainingDuration.ToString() + "s, paused: " + m_BountyPaused.ToString() + ")");
			}
		}
		else if (hasBounty && remainingDuration <= 0.0)
		{
			if (currentTimeSeconds - m_LastSyncWarningTime >= SYNC_WARNING_INTERVAL)
			{
				m_LastSyncWarningTime = currentTimeSeconds;
				GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Player has bounty but remainingDuration is " + remainingDuration.ToString() + "s - waiting for RPC sync...");
			}
		}
		else
		{
			if (m_RootWidgetBountyCountdown.IsVisible())
			{
				HideBountyCountdownTimer();
			}
		}
	}
	private void ShowBountyCountdownTimer()
	{
		if (m_RootWidgetBountyCountdown && m_BountyCountdownTimer)
		{
			m_RootWidgetBountyCountdown.Show(true);
			GetNinjins_Bounty_SystemLogger().LogDebug("[MissionGameplay] Showing bounty countdown timer UI.");
		}
	}
	private void HideBountyCountdownTimer()
	{
		if (m_RootWidgetBountyCountdown && m_BountyCountdownTimer)
		{
			m_BountyCountdownTimer.SetText("");
			m_RootWidgetBountyCountdown.Show(false);
		}
	}
	private void ControlBountyInputs()
	{
		UIScriptedMenu currentMenu = g_Game.GetUIManager().GetMenu();
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		if (GetUApi().GetInputByName("UAUIBack").LocalPress())
		{
			if (currentMenu && currentMenu.IsInherited(BountyAdminMenu))
			{
				currentMenu.OnHide();
				m_BountyAdminMenu = null;
				return;
			}
			if (currentMenu && currentMenu.IsInherited(NinjinsBountyBoardMenu))
			{
				currentMenu.OnHide();
				m_BountyBoardMenu = null;
				return;
			}
		}
		if (GetUApi().GetInputByName("UABountyAdminMenu").LocalPress())
		{
			GetNinjins_Bounty_SystemLogger().LogInfo("[ControlBountyInputs] UABountyAdminMenu hotkey pressed");
			if (!player.IsBountyAdmin())
			{
				GetNinjins_Bounty_SystemLogger().LogInfo("[ControlBountyInputs] Player is not admin. GUID: " + player.GetIdentity().GetId());
				NotificationSystem.Create(new StringLocaliser("Access Denied"), new StringLocaliser("You do not have permission to access the bounty admin menu."), "Ninjins_Bounty_System/gui/icons/bountyerror.edds", ARGB(255, 255, 0, 0), 5.0, player.GetIdentity());
				return;
			}
			GetNinjins_Bounty_SystemLogger().LogInfo("[ControlBountyInputs] Player is admin. GUID: " + player.GetIdentity().GetId() + ". Opening menu.");
			if (currentMenu && !currentMenu.IsInherited(BountyAdminMenu))
				return;
			if (currentMenu && currentMenu.IsInherited(BountyAdminMenu))
			{
				g_Game.GetUIManager().HideScriptedMenu(currentMenu);
				m_BountyAdminMenu = null;
			}
			else
			{
				m_BountyAdminMenu = new BountyAdminMenu();
				g_Game.GetUIManager().ShowScriptedMenu(m_BountyAdminMenu, NULL);
			}
		}
	}
	void ReceiveBountiedPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<ref BountyPlayerData>> data;
		if (!ctx.Read(data))
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read bountied players data from RPC.");
			return;
		}
		if (data && data.param1)
		{
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " bountied players via RPC.");
			BountyMapBridge.SetBountiedPlayers(data.param1);
		}
	}
	void BountyReceiveOnlinePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		Param1<array<string>> data;
		if (!ctx.Read(data))
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read online players data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(NinjinsBountyBoardMenu))
		{
			NinjinsBountyBoardMenu bountyMenu = NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu && data && data.param1)
			{
				bountyMenu.UpdateOnlinePlayersList(data.param1);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " online players via RPC.");
			}
		}
		else if (menu && menu.IsInherited(BountyAdminMenu))
		{
			BountyAdminMenu adminMenu = BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.UpdateOnlinePlayersList(data.param1);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " online players for admin menu via RPC.");
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read admin players data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(BountyAdminMenu))
		{
			BountyAdminMenu adminMenu = BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.UpdatePlayersList(data.param1);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " admin players via RPC.");
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read blacklist data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(BountyAdminMenu))
		{
			BountyAdminMenu adminMenu = BountyAdminMenu.Cast(menu);
			if (adminMenu && data && data.param1)
			{
				adminMenu.UpdateBlacklistedPlayersList(data.param1);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received " + data.param1.Count().ToString() + " blacklisted players via RPC.");
			}
		}
	}
	void OpenBountyBoardMenuDirect()
	{
		UIScriptedMenu currentMenu = g_Game.GetUIManager().GetMenu();
		if (currentMenu && !currentMenu.IsInherited(NinjinsBountyBoardMenu))
			return;
		if (currentMenu && currentMenu.IsInherited(NinjinsBountyBoardMenu))
		{
			g_Game.GetUIManager().HideScriptedMenu(currentMenu);
			m_BountyBoardMenu = null;
		}
		else
		{
			m_BountyBoardMenu = new NinjinsBountyBoardMenu();
			g_Game.GetUIManager().ShowScriptedMenu(m_BountyBoardMenu, NULL);
		}
	}
	void BountyCloseBoardMenu(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Client)
			return;
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(NinjinsBountyBoardMenu))
		{
			NinjinsBountyBoardMenu bountyMenu = NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu)
			{
				bountyMenu.OnHide();
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Closed bounty board menu via RPC (inventory full).");
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read claim amount data from RPC.");
			return;
		}
		UIScriptedMenu menu = g_Game.GetUIManager().GetMenu();
		if (menu && menu.IsInherited(NinjinsBountyBoardMenu))
		{
			NinjinsBountyBoardMenu bountyMenu = NinjinsBountyBoardMenu.Cast(menu);
			if (bountyMenu && data)
			{
				bountyMenu.UpdateClaimAmount(data.param1);
				GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received claim amount via RPC: " + data.param1.ToString());
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read bounty countdown data from RPC.");
			return;
		}
		currentTimeSeconds = g_Game.GetTime() / 1000.0;
		m_LastReceivedDuration = data.param1;
		m_LastReceivedTime = currentTimeSeconds;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
		{
			player.netSync_BountyRemainingDuration = data.param1;
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received bounty countdown update: " + data.param1.ToString() + " seconds - stored for client-driven countdown");
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read bounty state data from RPC.");
			return;
		}
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
		{
			player.netSync_HasBounty = data.param1;
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received bounty state update: " + data.param1.ToString() + " via RPC");
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
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read bounty paused state data from RPC.");
			return;
		}
		m_BountyPaused = data.param1;
		if (!m_BountyPaused)
		{
			currentTimeSeconds = g_Game.GetTime() / 1000.0;
			m_LastReceivedTime = currentTimeSeconds;
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Bounty countdown resumed - resyncing timer");
		}
		else
		{
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Bounty countdown paused");
		}
	}
	void BountyConfigReloaded(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<BountyUISettingsData> uiDataParam;
		BountyUISettingsData uiData;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(uiDataParam))
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read UI data from BountyConfigReloaded RPC.");
			return;
		}
		uiData = uiDataParam.param1;
		if (!uiData)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] UI data is null from BountyConfigReloaded RPC.");
			return;
		}
		GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received BountyConfigReloaded RPC - reapplying UI. X=" + uiData.PositionX.ToString() + ", Y=" + uiData.PositionY.ToString() + ", Width=" + uiData.Width.ToString() + ", Height=" + uiData.Height.ToString() + ", BGColor=" + uiData.BackgroundColor.ToString() + ", TextColor=" + uiData.TextColor.ToString());
		ApplyBountyCountdownPosition(uiData.PositionX, uiData.PositionY, uiData.Width, uiData.Height, uiData.BackgroundColor, uiData.TextColor);
	}
	void BountyAdminReceiveConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<ref BountyConfig> configParam;
		BountyConfig config;
		if (type != CallType.Client)
			return;
		if (!ctx.Read(configParam))
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Failed to read config from BountyAdminReceiveConfig RPC.");
			return;
		}
		config = configParam.param1;
		if (!config)
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Config is null from BountyAdminReceiveConfig RPC.");
			return;
		}
		if (m_BountyAdminMenu)
		{
			m_BountyAdminMenu.UpdateConfigFromServer(config);
			GetNinjins_Bounty_SystemLogger().LogInfo("[MissionGameplay] Received config and updated admin menu UI.");
		}
		else
		{
			GetNinjins_Bounty_SystemLogger().LogWarning("[MissionGameplay] Admin menu not open - cannot update config.");
		}
	}
};