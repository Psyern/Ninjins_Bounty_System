class obfc_BountyAdminMenu extends UIScriptedMenu
{
	private ButtonWidget obfv_m_BtnApplyTestRuleBreakerBounty;
	private ButtonWidget obfv_m_BtnAddBountySelectedPlayer;
	private ButtonWidget obfv_m_BtnClearBounty;
	private ButtonWidget obfv_m_BtnClearBountySelectedPlayer;
	private ButtonWidget obfv_m_BtnReloadConfigs;
	private ButtonWidget obfv_m_BtnClearAllCooldowns;
	private ButtonWidget obfv_m_BtnClearPlayerCooldown;
	private ButtonWidget obfv_m_BtnSaveAndReload;
	private ButtonWidget obfv_m_BtnAddRewardPoint;
	private ButtonWidget obfv_m_BtnRemoveRewardPoint;
	private TextListboxWidget obfv_m_PlayersList;
	private ref obfc_BountyConfig obfv_m_CachedConfig;
	private ref array<string> obfv_m_PlayerIdentifiers;
	private ButtonWidget obfv_m_btnNormalSettings;
	private ButtonWidget obfv_m_btnNotifications;
	private ButtonWidget obfv_m_btnBlacklist;
	private Widget obfv_m_GeneralRootPanel;
	private Widget obfv_m_NotificationsRootPanel;
	private Widget obfv_m_BlacklistRootPanel;
	private TextListboxWidget obfv_m_OnlinePlayersList;
	private TextListboxWidget obfv_m_BlacklistedPlayersList;
	private ref array<string> obfv_m_OnlinePlayerIdentifiers;
	private ButtonWidget obfv_m_AddToBlacklistBtn;
	private ButtonWidget obfv_m_RemoveFromBlacklistBtn;
	private ButtonWidget obfv_m_RefreshBlacklistPlayerListBtn;
	private CheckBoxWidget obfv_m_EnableBountySystem;
	private CheckBoxWidget obfv_m_DisableSelfBounty;
	private CheckBoxWidget obfv_m_TeleportOutOfOwnTerritory;
	private CheckBoxWidget obfv_m_PauseBountyInTerritory;
	private CheckBoxWidget obfv_m_TeleportOutOfSafeZone;
	private CheckBoxWidget obfv_m_EnableAutomatedBountyPlacement;
	private EditBoxWidget obfv_m_BountyCooldownSeconds;
	private EditBoxWidget obfv_m_MaxBountiedPlayers;
	private EditBoxWidget obfv_m_MinOnlinePlayersRequired;
	private EditBoxWidget obfv_m_SkipBountyTokenRequired;
	private EditBoxWidget obfv_m_PlaceBountyTokenRequired;
	private EditBoxWidget obfv_m_ResumeBountyDistanceFromTerritory;
	private EditBoxWidget obfv_m_PausedBountyResumeCheckInterval;
	private EditBoxWidget obfv_m_TeleportOutOfSafeZoneDistance;
	private EditBoxWidget obfv_m_MinimumPlayerLifetimeSeconds;
	private EditBoxWidget obfv_m_AutomatedBountyPlacementIntervalSeconds;
	private CheckBoxWidget obfv_m_EnableRuleBreakerHitThreshold;
	private CheckBoxWidget obfv_m_EnablePvEToPvPRuleBreaker;
	private CheckBoxWidget obfv_m_ClearPendingRewardsOnRuleBreakerBounty;
	private CheckBoxWidget obfv_m_AllowPvEToPvEVictimKill;
	private EditBoxWidget obfv_m_BountyRuleBreakerDurationSeconds;
	private EditBoxWidget obfv_m_RuleBreakerHitThresholdTime;
	private EditBoxWidget obfv_m_RuleBreakerHitThresholdWarningHits;
	private EditBoxWidget obfv_m_RuleBreakerHitThresholdBountyHits;
	private EditBoxWidget obfv_m_PvEToPvPInstantRuleBreakerHits;
	private CheckBoxWidget obfv_m_Expansion_EnableHardlineReputationDecrease;
	private EditBoxWidget obfv_m_Expansion_HardlineReputationDecreaseAmount;
	private EditBoxWidget obfv_m_BountyDurationSeconds;
	private CheckBoxWidget obfv_m_EnableSurvivalReward;
	private CheckBoxWidget obfv_m_PvERuleBreakerGiveRewards;
	private CheckBoxWidget obfv_m_BountyEnableMapDrawing;
	private CheckBoxWidget obfv_m_BountyCircleReduceRadiusOverTime;
	private CheckBoxWidget obfv_m_BountyCircleIncreaseRadiusOverTime;
	private EditBoxWidget obfv_m_BountyCircleRadius;
	private EditBoxWidget obfv_m_BountyCircleMinRadius;
	private EditBoxWidget obfv_m_BountyCircleColor;
	private EditBoxWidget obfv_m_BountyCircleDrawingWidth;
	private EditBoxWidget obfv_m_BountyMapUpdateIntervalSeconds;
	private EditBoxWidget obfv_m_BountyMapRequestCooldownSeconds;
	private EditBoxWidget obfv_m_BountyMapSyncIntervalSeconds;
	private EditBoxWidget obfv_m_BountyMapSyncIntervalNoBountiesSeconds;
	private EditBoxWidget obfv_m_BountyCircleOffsetMinMultiplier;
	private EditBoxWidget obfv_m_BountyCircleOffsetMaxMultiplier;
	private EditBoxWidget obfv_m_CountdownWidgetPositionX;
	private EditBoxWidget obfv_m_CountdownWidgetPositionY;
	private EditBoxWidget obfv_m_CountdownWidgetWidth;
	private EditBoxWidget obfv_m_CountdownWidgetHeight;
	private EditBoxWidget obfv_m_CountdownWidgetBackgroundColor;
	private EditBoxWidget obfv_m_CountdownWidgetTextColor;
	private CheckBoxWidget obfv_m_PlacedBountyHuntedEnabled;
	private EditBoxWidget obfv_m_PlacedBountyHuntedTitle;
	private MultilineEditBoxWidget obfv_m_PlacedBountyHuntedMessage;
	private EditBoxWidget obfv_m_PlacedBountyHuntedIconPath;
	private CheckBoxWidget obfv_m_PlacedBountyExpiredEnabled;
	private EditBoxWidget obfv_m_PlacedBountyExpiredTitle;
	private MultilineEditBoxWidget obfv_m_PlacedBountyExpiredMessage;
	private EditBoxWidget obfv_m_PlacedBountyExpiredIconPath;
	private CheckBoxWidget obfv_m_PlacedBountySurvivalRewardEnabled;
	private EditBoxWidget obfv_m_PlacedBountySurvivalRewardTitle;
	private MultilineEditBoxWidget obfv_m_PlacedBountySurvivalRewardMessage;
	private EditBoxWidget obfv_m_PlacedBountySurvivalRewardIconPath;
	private CheckBoxWidget obfv_m_PlacedBountyKilledRewardEnabled;
	private EditBoxWidget obfv_m_PlacedBountyKilledRewardTitle;
	private MultilineEditBoxWidget obfv_m_PlacedBountyKilledRewardMessage;
	private EditBoxWidget obfv_m_PlacedBountyKilledRewardIconPath;
	private CheckBoxWidget obfv_m_RuleBreakerHuntedEnabled;
	private EditBoxWidget obfv_m_RuleBreakerHuntedTitle;
	private MultilineEditBoxWidget obfv_m_RuleBreakerHuntedMessage;
	private EditBoxWidget obfv_m_RuleBreakerHuntedIconPath;
	private CheckBoxWidget obfv_m_RuleBreakerHitWarningEnabled;
	private EditBoxWidget obfv_m_RuleBreakerHitWarningTitle;
	private MultilineEditBoxWidget obfv_m_RuleBreakerHitWarningMessage;
	private EditBoxWidget obfv_m_RuleBreakerHitWarningIconPath;
	private CheckBoxWidget obfv_m_RuleBreakerExpiredEnabled;
	private EditBoxWidget obfv_m_RuleBreakerExpiredTitle;
	private MultilineEditBoxWidget obfv_m_RuleBreakerExpiredMessage;
	private EditBoxWidget obfv_m_RuleBreakerExpiredIconPath;
	private CheckBoxWidget obfv_m_RuleBreakerSurvivalRewardEnabled;
	private EditBoxWidget obfv_m_RuleBreakerSurvivalRewardTitle;
	private MultilineEditBoxWidget obfv_m_RuleBreakerSurvivalRewardMessage;
	private EditBoxWidget obfv_m_RuleBreakerSurvivalRewardIconPath;
	private CheckBoxWidget obfv_m_RuleBreakerKilledRewardEnabled;
	private EditBoxWidget obfv_m_RuleBreakerKilledRewardTitle;
	private MultilineEditBoxWidget obfv_m_RuleBreakerKilledRewardMessage;
	private EditBoxWidget obfv_m_RuleBreakerKilledRewardIconPath;
	private CheckBoxWidget obfv_m_OtherInsufficientTokensEnabled;
	private EditBoxWidget obfv_m_OtherInsufficientTokensTitle;
	private MultilineEditBoxWidget obfv_m_OtherInsufficientTokensMessage;
	private EditBoxWidget obfv_m_OtherInsufficientTokensIconPath;
	private CheckBoxWidget obfv_m_OtherSkipBountyNoPlayersEnabled;
	private EditBoxWidget obfv_m_OtherSkipBountyNoPlayersTitle;
	private MultilineEditBoxWidget obfv_m_OtherSkipBountyNoPlayersMessage;
	private EditBoxWidget obfv_m_OtherSkipBountyNoPlayersIconPath;
	private CheckBoxWidget obfv_m_OtherSkipBountySuccessEnabled;
	private EditBoxWidget obfv_m_OtherSkipBountySuccessTitle;
	private MultilineEditBoxWidget obfv_m_OtherSkipBountySuccessMessage;
	private EditBoxWidget obfv_m_OtherSkipBountySuccessIconPath;
	private CheckBoxWidget obfv_m_OtherBountySkippedEnabled;
	private EditBoxWidget obfv_m_OtherBountySkippedTitle;
	private MultilineEditBoxWidget obfv_m_OtherBountySkippedMessage;
	private EditBoxWidget obfv_m_OtherBountySkippedIconPath;
	private CheckBoxWidget obfv_m_OtherRewardHandsNotFreeEnabled;
	private EditBoxWidget obfv_m_OtherRewardHandsNotFreeTitle;
	private MultilineEditBoxWidget obfv_m_OtherRewardHandsNotFreeMessage;
	private EditBoxWidget obfv_m_OtherRewardHandsNotFreeIconPath;
	private CheckBoxWidget obfv_m_OtherPlayerOnCooldownEnabled;
	private EditBoxWidget obfv_m_OtherPlayerOnCooldownTitle;
	private MultilineEditBoxWidget obfv_m_OtherPlayerOnCooldownMessage;
	private EditBoxWidget obfv_m_OtherPlayerOnCooldownIconPath;
	private CheckBoxWidget obfv_m_OtherPlayerInSafeZoneEnabled;
	private EditBoxWidget obfv_m_OtherPlayerInSafeZoneTitle;
	private MultilineEditBoxWidget obfv_m_OtherPlayerInSafeZoneMessage;
	private EditBoxWidget obfv_m_OtherPlayerInSafeZoneIconPath;
	private CheckBoxWidget obfv_m_OtherBountyPersistedEnabled;
	private EditBoxWidget obfv_m_OtherBountyPersistedTitle;
	private MultilineEditBoxWidget obfv_m_OtherBountyPersistedMessage;
	private EditBoxWidget obfv_m_OtherBountyPersistedIconPath;
	private CheckBoxWidget obfv_m_OtherTeleportedOutOfTerritoryEnabled;
	private EditBoxWidget obfv_m_OtherTeleportedOutOfTerritoryTitle;
	private MultilineEditBoxWidget obfv_m_OtherTeleportedOutOfTerritoryMessage;
	private EditBoxWidget obfv_m_OtherTeleportedOutOfTerritoryIconPath;
	private CheckBoxWidget obfv_m_OtherBountyPausedInTerritoryEnabled;
	private EditBoxWidget obfv_m_OtherBountyPausedInTerritoryTitle;
	private MultilineEditBoxWidget obfv_m_OtherBountyPausedInTerritoryMessage;
	private EditBoxWidget obfv_m_OtherBountyPausedInTerritoryIconPath;
	private CheckBoxWidget obfv_m_BroadcastsPlacedBountyEnabled;
	private EditBoxWidget obfv_m_BroadcastsPlacedBountyTitle;
	private MultilineEditBoxWidget obfv_m_BroadcastsPlacedBountyMessage;
	private EditBoxWidget obfv_m_BroadcastsPlacedBountyIconPath;
	private CheckBoxWidget obfv_m_BroadcastsRuleBreakerEnabled;
	private EditBoxWidget obfv_m_BroadcastsRuleBreakerTitle;
	private MultilineEditBoxWidget obfv_m_BroadcastsRuleBreakerMessage;
	private EditBoxWidget obfv_m_BroadcastsRuleBreakerIconPath;
	void obfc_BountyAdminMenu()
	{
		obfv_m_PlayerIdentifiers = new array<string>();
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
		layoutRoot = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyAdminMenu.layout");
		if (!layoutRoot)
			return NULL;
		obfv_m_BtnApplyTestRuleBreakerBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnApplyTestRuleBreakerBounty"));
		obfv_m_BtnAddBountySelectedPlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddBountySelectedPlayer"));
		obfv_m_BtnClearBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearBounty"));
		obfv_m_BtnClearBountySelectedPlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearBountySelectedPlayer"));
		obfv_m_BtnReloadConfigs = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnReloadConfigs"));
		obfv_m_BtnClearAllCooldowns = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearAllCooldowns"));
		obfv_m_BtnClearPlayerCooldown = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearPlayerCooldown"));
		obfv_m_BtnSaveAndReload = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BTNSaveAndReload"));
		obfv_m_BtnAddRewardPoint = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddRewardPoint"));
		obfv_m_BtnRemoveRewardPoint = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRemoveRewardPoint"));
		obfv_m_PlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersList"));
		obfv_m_btnNormalSettings = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnNormalSettings"));
		obfv_m_btnNotifications = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnNotifications"));
		obfv_m_btnBlacklist = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnBlacklist"));
		obfv_m_GeneralRootPanel = layoutRoot.FindAnyWidget("GeneralRootPanel");
		obfv_m_NotificationsRootPanel = layoutRoot.FindAnyWidget("NotificationsSettingsPanel");
		obfv_m_BlacklistRootPanel = layoutRoot.FindAnyWidget("BlacklistSettingsPanel");
		obfv_m_OnlinePlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxWidgetOnlinePlayers"));
		obfv_m_BlacklistedPlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxWidgetBlacklistedPlayers"));
		obfv_m_AddToBlacklistBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddToBlacklistBTN"));
		obfv_m_RemoveFromBlacklistBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveFromBlacklistBTN"));
		obfv_m_RefreshBlacklistPlayerListBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RefreshBlacklistPlayerListBTN"));
		obfv_m_EnableBountySystem = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableBountySystem"));
		obfv_m_DisableSelfBounty = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableSelfBounty"));
		obfv_m_TeleportOutOfOwnTerritory = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfOwnTerritory"));
		obfv_m_PauseBountyInTerritory = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PauseBountyInTerritory"));
		obfv_m_TeleportOutOfSafeZone = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfSafeZone"));
		obfv_m_EnableAutomatedBountyPlacement = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableAutomatedBountyPlacement"));
		obfv_m_BountyCooldownSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCooldownSeconds"));
		obfv_m_MaxBountiedPlayers = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MaxBountiedPlayers"));
		obfv_m_MinOnlinePlayersRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinOnlinePlayersRequired"));
		obfv_m_SkipBountyTokenRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SkipBountyTokenRequired"));
		obfv_m_PlaceBountyTokenRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlaceBountyTokenRequired"));
		obfv_m_ResumeBountyDistanceFromTerritory = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ResumeBountyDistanceFromTerritory"));
		obfv_m_PausedBountyResumeCheckInterval = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PausedBountyResumeCheckInterval"));
		obfv_m_TeleportOutOfSafeZoneDistance = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfSafeZoneDistance"));
		obfv_m_MinimumPlayerLifetimeSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinimumPlayerLifetimeSeconds"));
		obfv_m_AutomatedBountyPlacementIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AutomatedBountyPlacementIntervalSeconds"));
		obfv_m_EnableRuleBreakerHitThreshold = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableRuleBreakerHitThreshold"));
		obfv_m_EnablePvEToPvPRuleBreaker = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnablePvEToPvPRuleBreaker"));
		obfv_m_ClearPendingRewardsOnRuleBreakerBounty = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ClearPendingRewardsOnRuleBreakerBounty"));
		obfv_m_AllowPvEToPvEVictimKill = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowPvEToPvEVictimKill"));
		obfv_m_BountyRuleBreakerDurationSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyRuleBreakerDurationSeconds"));
		obfv_m_RuleBreakerHitThresholdTime = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdTime"));
		obfv_m_RuleBreakerHitThresholdWarningHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdWarningHits"));
		obfv_m_RuleBreakerHitThresholdBountyHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdBountyHits"));
		obfv_m_PvEToPvPInstantRuleBreakerHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvEToPvPInstantRuleBreakerHits"));
		obfv_m_Expansion_EnableHardlineReputationDecrease = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Expansion_EnableHardlineReputationDecrease"));
		obfv_m_Expansion_HardlineReputationDecreaseAmount = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Expansion_HardlineReputationDecreaseAmount"));
		obfv_m_BountyDurationSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyDurationSeconds"));
		obfv_m_EnableSurvivalReward = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableSurvivalReward"));
		obfv_m_PvERuleBreakerGiveRewards = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PvERuleBreakerGiveRewards"));
		obfv_m_BountyEnableMapDrawing = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyEnableMapDrawing"));
		obfv_m_BountyCircleReduceRadiusOverTime = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleReduceRadiusOverTime"));
		obfv_m_BountyCircleIncreaseRadiusOverTime = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleIncreaseRadiusOverTime"));
		obfv_m_BountyCircleRadius = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleRadius"));
		obfv_m_BountyCircleMinRadius = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleMinRadius"));
		obfv_m_BountyCircleColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleColor"));
		obfv_m_BountyCircleDrawingWidth = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleDrawingWidth"));
		obfv_m_BountyMapUpdateIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapUpdateIntervalSeconds"));
		obfv_m_BountyMapRequestCooldownSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapRequestCooldownSeconds"));
		obfv_m_BountyMapSyncIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapSyncIntervalSeconds"));
		obfv_m_BountyMapSyncIntervalNoBountiesSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapSyncIntervalNoBountiesSeconds"));
		obfv_m_BountyCircleOffsetMinMultiplier = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleOffsetMinMultiplier"));
		obfv_m_BountyCircleOffsetMaxMultiplier = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleOffsetMaxMultiplier"));
		obfv_m_CountdownWidgetPositionX = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetPositionX"));
		obfv_m_CountdownWidgetPositionY = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetPositionY"));
		obfv_m_CountdownWidgetWidth = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetWidth"));
		obfv_m_CountdownWidgetHeight = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetHeight"));
		obfv_m_CountdownWidgetBackgroundColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetBackgroundColor"));
		obfv_m_CountdownWidgetTextColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetTextColor"));
		obfv_m_PlacedBountyHuntedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedEnabled0"));
		obfv_m_PlacedBountyHuntedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedTitle0"));
		obfv_m_PlacedBountyHuntedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedMessage0"));
		obfv_m_PlacedBountyHuntedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedIconPath0"));
		obfv_m_PlacedBountyExpiredEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredEnabled0"));
		obfv_m_PlacedBountyExpiredTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredTitle0"));
		obfv_m_PlacedBountyExpiredMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredMessage0"));
		obfv_m_PlacedBountyExpiredIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredIconPath0"));
		obfv_m_PlacedBountySurvivalRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardEnabled0"));
		obfv_m_PlacedBountySurvivalRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardTitle0"));
		obfv_m_PlacedBountySurvivalRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardMessage0"));
		obfv_m_PlacedBountySurvivalRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardIconPath0"));
		obfv_m_PlacedBountyKilledRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardEnabled0"));
		obfv_m_PlacedBountyKilledRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardTitle0"));
		obfv_m_PlacedBountyKilledRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardMessage0"));
		obfv_m_PlacedBountyKilledRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardIconPath0"));
		obfv_m_RuleBreakerHuntedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedEnabled0"));
		obfv_m_RuleBreakerHuntedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedTitle0"));
		obfv_m_RuleBreakerHuntedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedMessage0"));
		obfv_m_RuleBreakerHuntedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedIconPath0"));
		obfv_m_RuleBreakerHitWarningEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningEnabled0"));
		obfv_m_RuleBreakerHitWarningTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningTitle0"));
		obfv_m_RuleBreakerHitWarningMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningMessage0"));
		obfv_m_RuleBreakerHitWarningIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningIconPath0"));
		obfv_m_RuleBreakerExpiredEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredEnabled0"));
		obfv_m_RuleBreakerExpiredTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredTitle0"));
		obfv_m_RuleBreakerExpiredMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredMessage0"));
		obfv_m_RuleBreakerExpiredIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredIconPath0"));
		obfv_m_RuleBreakerSurvivalRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardEnabled0"));
		obfv_m_RuleBreakerSurvivalRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardTitle0"));
		obfv_m_RuleBreakerSurvivalRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardMessage0"));
		obfv_m_RuleBreakerSurvivalRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardIconPath0"));
		obfv_m_RuleBreakerKilledRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardEnabled0"));
		obfv_m_RuleBreakerKilledRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardTitle0"));
		obfv_m_RuleBreakerKilledRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardMessage0"));
		obfv_m_RuleBreakerKilledRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardIconPath0"));
		obfv_m_OtherInsufficientTokensEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensEnabled0"));
		obfv_m_OtherInsufficientTokensTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensTitle0"));
		obfv_m_OtherInsufficientTokensMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensMessage0"));
		obfv_m_OtherInsufficientTokensIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensIconPath0"));
		obfv_m_OtherSkipBountyNoPlayersEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersEnabled0"));
		obfv_m_OtherSkipBountyNoPlayersTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersTitle0"));
		obfv_m_OtherSkipBountyNoPlayersMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersMessage0"));
		obfv_m_OtherSkipBountyNoPlayersIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersIconPath0"));
		obfv_m_OtherSkipBountySuccessEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessEnabled0"));
		obfv_m_OtherSkipBountySuccessTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessTitle0"));
		obfv_m_OtherSkipBountySuccessMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessMessage0"));
		obfv_m_OtherSkipBountySuccessIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessIconPath0"));
		obfv_m_OtherBountySkippedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedEnabled0"));
		obfv_m_OtherBountySkippedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedTitle0"));
		obfv_m_OtherBountySkippedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedMessage0"));
		obfv_m_OtherBountySkippedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedIconPath0"));
		obfv_m_OtherRewardHandsNotFreeEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeEnabled0"));
		obfv_m_OtherRewardHandsNotFreeTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeTitle0"));
		obfv_m_OtherRewardHandsNotFreeMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeMessage0"));
		obfv_m_OtherRewardHandsNotFreeIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeIconPath0"));
		obfv_m_OtherPlayerOnCooldownEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownEnabled0"));
		obfv_m_OtherPlayerOnCooldownTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownTitle0"));
		obfv_m_OtherPlayerOnCooldownMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownMessage0"));
		obfv_m_OtherPlayerOnCooldownIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownIconPath0"));
		obfv_m_OtherPlayerInSafeZoneEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneEnabled0"));
		obfv_m_OtherPlayerInSafeZoneTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneTitle0"));
		obfv_m_OtherPlayerInSafeZoneMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneMessage0"));
		obfv_m_OtherPlayerInSafeZoneIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneIconPath0"));
		obfv_m_OtherBountyPersistedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedEnabled0"));
		obfv_m_OtherBountyPersistedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedTitle0"));
		obfv_m_OtherBountyPersistedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedMessage0"));
		obfv_m_OtherBountyPersistedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedIconPath0"));
		obfv_m_OtherTeleportedOutOfTerritoryEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryEnabled0"));
		obfv_m_OtherTeleportedOutOfTerritoryTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryTitle0"));
		obfv_m_OtherTeleportedOutOfTerritoryMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryMessage0"));
		obfv_m_OtherTeleportedOutOfTerritoryIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryIconPath0"));
		obfv_m_OtherBountyPausedInTerritoryEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryEnabled0"));
		obfv_m_OtherBountyPausedInTerritoryTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryTitle0"));
		obfv_m_OtherBountyPausedInTerritoryMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryMessage0"));
		obfv_m_OtherBountyPausedInTerritoryIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryIconPath0"));
		obfv_m_BroadcastsPlacedBountyEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyEnabled0"));
		obfv_m_BroadcastsPlacedBountyTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyTitle0"));
		obfv_m_BroadcastsPlacedBountyMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyMessage0"));
		obfv_m_BroadcastsPlacedBountyIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyIconPath0"));
		obfv_m_BroadcastsRuleBreakerEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerEnabled0"));
		obfv_m_BroadcastsRuleBreakerTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerTitle0"));
		obfv_m_BroadcastsRuleBreakerMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerMessage0"));
		obfv_m_BroadcastsRuleBreakerIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerIconPath0"));
		if (!obfv_m_PlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] PlayersList widget not found in layout!");
		}
		return layoutRoot;
	}
	private void obfm_ShowOnlyPanel(Widget panelToShow)
	{
		if (obfv_m_GeneralRootPanel)
			obfv_m_GeneralRootPanel.Show(false);
		if (obfv_m_NotificationsRootPanel)
			obfv_m_NotificationsRootPanel.Show(false);
		if (obfv_m_BlacklistRootPanel)
			obfv_m_BlacklistRootPanel.Show(false);
		if (panelToShow)
			panelToShow.Show(true);
		if (obfv_m_btnNormalSettings)
		{
			if (panelToShow == obfv_m_GeneralRootPanel)
				obfv_m_btnNormalSettings.SetColor(ARGB(255, 27, 89, 95)); 
			else
				obfv_m_btnNormalSettings.SetColor(ARGB(241, 30, 40, 56)); 
		}
		if (obfv_m_btnNotifications)
		{
			if (panelToShow == obfv_m_NotificationsRootPanel)
				obfv_m_btnNotifications.SetColor(ARGB(255, 27, 89, 95)); 
			else
				obfv_m_btnNotifications.SetColor(ARGB(241, 30, 40, 56)); 
		}
		if (obfv_m_btnBlacklist)
		{
			if (panelToShow == obfv_m_BlacklistRootPanel)
				obfv_m_btnBlacklist.SetColor(ARGB(255, 27, 89, 95)); 
			else
				obfv_m_btnBlacklist.SetColor(ARGB(241, 30, 40, 56)); 
		}
		if (panelToShow == obfv_m_BlacklistRootPanel)
		{
			obfm_RefreshBlacklistLists();
		}
	}
	override void OnShow()
	{
		super.OnShow();
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		PPEffects.SetBlurMenu(0.5);
		g_Game.GetInput().ChangeGameFocus(1);
		g_Game.GetUIManager().ShowUICursor(true);
		g_Game.GetMission().GetHud().Show(false);
		TIntArray skip = { UAUIBack, UABountyAdminMenu };
		obfm_ForceDisableInputs(true, skip);
		SetFocus(layoutRoot);
		obfm_ShowOnlyPanel(obfv_m_GeneralRootPanel);
		if (player && player.GetIdentity())
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestConfig", new Param1<int>(0), true, player.GetIdentity());
		}
		obfm_RefreshPlayersList();
	}
	void obfm_UpdateConfigFromServer(obfc_BountyConfig config)
	{
		obfv_m_CachedConfig = config;
		obfm_PopulateConfigValues();
	}
	void obfm_PopulateConfigValues()
	{
		obfc_BountyConfig config;
		config = obfv_m_CachedConfig;
		if (!config)
			return;
		if (obfv_m_EnableBountySystem && config.Core)
			obfv_m_EnableBountySystem.SetChecked(config.Core.EnableBountySystem);
		if (obfv_m_DisableSelfBounty && config.Core)
			obfv_m_DisableSelfBounty.SetChecked(config.Core.DisableSelfBounty);
		if (obfv_m_TeleportOutOfOwnTerritory && config.Core)
			obfv_m_TeleportOutOfOwnTerritory.SetChecked(config.Core.obfm_TeleportOutOfOwnTerritory);
		if (obfv_m_PauseBountyInTerritory && config.Core)
			obfv_m_PauseBountyInTerritory.SetChecked(config.Core.PauseBountyInTerritory);
		if (obfv_m_TeleportOutOfSafeZone && config.Core)
			obfv_m_TeleportOutOfSafeZone.SetChecked(config.Core.obfm_TeleportOutOfSafeZone);
		if (obfv_m_EnableAutomatedBountyPlacement && config.Core)
			obfv_m_EnableAutomatedBountyPlacement.SetChecked(config.Core.EnableAutomatedBountyPlacement);
		if (obfv_m_BountyCooldownSeconds && config.Core)
			obfv_m_BountyCooldownSeconds.SetText(config.Core.BountyCooldownSeconds.ToString());
		if (obfv_m_MaxBountiedPlayers && config.Core)
			obfv_m_MaxBountiedPlayers.SetText(config.Core.MaxBountiedPlayers.ToString());
		if (obfv_m_MinOnlinePlayersRequired && config.Core)
			obfv_m_MinOnlinePlayersRequired.SetText(config.Core.MinOnlinePlayersRequired.ToString());
		if (obfv_m_SkipBountyTokenRequired && config.Core)
			obfv_m_SkipBountyTokenRequired.SetText(config.Core.SkipBountyTokenRequired.ToString());
		if (obfv_m_PlaceBountyTokenRequired && config.Core)
			obfv_m_PlaceBountyTokenRequired.SetText(config.Core.PlaceBountyTokenRequired.ToString());
		if (obfv_m_ResumeBountyDistanceFromTerritory && config.Core)
			obfv_m_ResumeBountyDistanceFromTerritory.SetText(config.Core.ResumeBountyDistanceFromTerritory.ToString());
		if (obfv_m_PausedBountyResumeCheckInterval && config.Core)
			obfv_m_PausedBountyResumeCheckInterval.SetText(config.Core.PausedBountyResumeCheckInterval.ToString());
		if (obfv_m_TeleportOutOfSafeZoneDistance && config.Core)
			obfv_m_TeleportOutOfSafeZoneDistance.SetText(config.Core.TeleportOutOfSafeZoneDistance.ToString());
		if (obfv_m_MinimumPlayerLifetimeSeconds && config.Core)
			obfv_m_MinimumPlayerLifetimeSeconds.SetText(config.Core.MinimumPlayerLifetimeSeconds.ToString());
		if (obfv_m_AutomatedBountyPlacementIntervalSeconds && config.Core)
			obfv_m_AutomatedBountyPlacementIntervalSeconds.SetText(config.Core.AutomatedBountyPlacementIntervalSeconds.ToString());
		if (obfv_m_EnableRuleBreakerHitThreshold && config.RuleBreaker)
			obfv_m_EnableRuleBreakerHitThreshold.SetChecked(config.RuleBreaker.EnableRuleBreakerHitThreshold);
		if (obfv_m_EnablePvEToPvPRuleBreaker && config.RuleBreaker)
			obfv_m_EnablePvEToPvPRuleBreaker.SetChecked(config.RuleBreaker.EnablePvEToPvPRuleBreaker);
		if (obfv_m_ClearPendingRewardsOnRuleBreakerBounty && config.RuleBreaker)
			obfv_m_ClearPendingRewardsOnRuleBreakerBounty.SetChecked(config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty);
		if (obfv_m_AllowPvEToPvEVictimKill && config.RuleBreaker)
			obfv_m_AllowPvEToPvEVictimKill.SetChecked(config.RuleBreaker.AllowPvEToPvEVictimKill);
		if (obfv_m_BountyRuleBreakerDurationSeconds && config.RuleBreaker)
			obfv_m_BountyRuleBreakerDurationSeconds.SetText(config.RuleBreaker.BountyRuleBreakerDurationSeconds.ToString());
		if (obfv_m_RuleBreakerHitThresholdTime && config.RuleBreaker)
			obfv_m_RuleBreakerHitThresholdTime.SetText(config.RuleBreaker.RuleBreakerHitThresholdTime.ToString());
		if (obfv_m_RuleBreakerHitThresholdWarningHits && config.RuleBreaker)
			obfv_m_RuleBreakerHitThresholdWarningHits.SetText(config.RuleBreaker.RuleBreakerHitThresholdWarningHits.ToString());
		if (obfv_m_RuleBreakerHitThresholdBountyHits && config.RuleBreaker)
			obfv_m_RuleBreakerHitThresholdBountyHits.SetText(config.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString());
		if (obfv_m_PvEToPvPInstantRuleBreakerHits && config.RuleBreaker)
			obfv_m_PvEToPvPInstantRuleBreakerHits.SetText(config.RuleBreaker.PvEToPvPInstantRuleBreakerHits.ToString());
		if (obfv_m_Expansion_EnableHardlineReputationDecrease && config.RuleBreaker)
			obfv_m_Expansion_EnableHardlineReputationDecrease.SetChecked(config.RuleBreaker.Expansion_EnableHardlineReputationDecrease);
		if (obfv_m_Expansion_HardlineReputationDecreaseAmount && config.RuleBreaker)
			obfv_m_Expansion_HardlineReputationDecreaseAmount.SetText(config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString());
		if (obfv_m_BountyDurationSeconds && config.PlacedBounty)
			obfv_m_BountyDurationSeconds.SetText(config.PlacedBounty.BountyDurationSeconds.ToString());
		if (obfv_m_EnableSurvivalReward && config.Reward)
			obfv_m_EnableSurvivalReward.SetChecked(config.Reward.EnableSurvivalReward);
		if (obfv_m_PvERuleBreakerGiveRewards && config.Reward)
			obfv_m_PvERuleBreakerGiveRewards.SetChecked(config.Reward.PvERuleBreakerGiveRewards);
		if (obfv_m_BountyEnableMapDrawing && config.Map)
			obfv_m_BountyEnableMapDrawing.SetChecked(config.Map.BountyEnableMapDrawing);
		if (obfv_m_BountyCircleReduceRadiusOverTime && config.Map)
			obfv_m_BountyCircleReduceRadiusOverTime.SetChecked(config.Map.BountyCircleReduceRadiusOverTime);
		if (obfv_m_BountyCircleIncreaseRadiusOverTime && config.Map)
			obfv_m_BountyCircleIncreaseRadiusOverTime.SetChecked(config.Map.BountyCircleIncreaseRadiusOverTime);
		if (obfv_m_BountyCircleRadius && config.Map)
			obfv_m_BountyCircleRadius.SetText(config.Map.BountyCircleRadius.ToString());
		if (obfv_m_BountyCircleMinRadius && config.Map)
			obfv_m_BountyCircleMinRadius.SetText(config.Map.BountyCircleMinRadius.ToString());
		if (obfv_m_BountyCircleColor && config.Map)
			obfv_m_BountyCircleColor.SetText(config.Map.BountyCircleColor.ToString());
		if (obfv_m_BountyCircleDrawingWidth && config.Map)
			obfv_m_BountyCircleDrawingWidth.SetText(config.Map.BountyCircleDrawingWidth.ToString());
		if (obfv_m_BountyMapUpdateIntervalSeconds && config.Map)
			obfv_m_BountyMapUpdateIntervalSeconds.SetText(config.Map.BountyMapUpdateIntervalSeconds.ToString());
		if (obfv_m_BountyMapRequestCooldownSeconds && config.Map)
			obfv_m_BountyMapRequestCooldownSeconds.SetText(config.Map.BountyMapRequestCooldownSeconds.ToString());
		if (obfv_m_BountyMapSyncIntervalSeconds && config.Map)
			obfv_m_BountyMapSyncIntervalSeconds.SetText(config.Map.BountyMapSyncIntervalSeconds.ToString());
		if (obfv_m_BountyMapSyncIntervalNoBountiesSeconds && config.Map)
			obfv_m_BountyMapSyncIntervalNoBountiesSeconds.SetText(config.Map.BountyMapSyncIntervalNoBountiesSeconds.ToString());
		if (obfv_m_BountyCircleOffsetMinMultiplier && config.Map)
			obfv_m_BountyCircleOffsetMinMultiplier.SetText(config.Map.BountyCircleOffsetMinMultiplier.ToString());
		if (obfv_m_BountyCircleOffsetMaxMultiplier && config.Map)
			obfv_m_BountyCircleOffsetMaxMultiplier.SetText(config.Map.BountyCircleOffsetMaxMultiplier.ToString());
		if (obfv_m_CountdownWidgetPositionX && config.UI)
			obfv_m_CountdownWidgetPositionX.SetText(config.UI.CountdownWidgetPositionX.ToString());
		if (obfv_m_CountdownWidgetPositionY && config.UI)
			obfv_m_CountdownWidgetPositionY.SetText(config.UI.CountdownWidgetPositionY.ToString());
		if (obfv_m_CountdownWidgetWidth && config.UI)
			obfv_m_CountdownWidgetWidth.SetText(config.UI.CountdownWidgetWidth.ToString());
		if (obfv_m_CountdownWidgetHeight && config.UI)
			obfv_m_CountdownWidgetHeight.SetText(config.UI.CountdownWidgetHeight.ToString());
		if (obfv_m_CountdownWidgetBackgroundColor && config.UI)
			obfv_m_CountdownWidgetBackgroundColor.SetText(config.UI.CountdownWidgetBackgroundColor.ToString());
		if (obfv_m_CountdownWidgetTextColor && config.UI)
			obfv_m_CountdownWidgetTextColor.SetText(config.UI.CountdownWidgetTextColor.ToString());
		if (config.Notifications && config.Notifications.PlacedBounty)
		{
			if (obfv_m_PlacedBountyHuntedEnabled && config.Notifications.PlacedBounty.Hunted)
			{
				obfv_m_PlacedBountyHuntedEnabled.SetChecked(config.Notifications.PlacedBounty.Hunted.Enabled);
				if (obfv_m_PlacedBountyHuntedTitle) obfv_m_PlacedBountyHuntedTitle.SetText(config.Notifications.PlacedBounty.Hunted.Title);
				if (obfv_m_PlacedBountyHuntedMessage) obfv_m_PlacedBountyHuntedMessage.SetText(config.Notifications.PlacedBounty.Hunted.Message);
				if (obfv_m_PlacedBountyHuntedIconPath) obfv_m_PlacedBountyHuntedIconPath.SetText(config.Notifications.PlacedBounty.Hunted.IconPath);
			}
			if (obfv_m_PlacedBountyExpiredEnabled && config.Notifications.PlacedBounty.Expired)
			{
				obfv_m_PlacedBountyExpiredEnabled.SetChecked(config.Notifications.PlacedBounty.Expired.Enabled);
				if (obfv_m_PlacedBountyExpiredTitle) obfv_m_PlacedBountyExpiredTitle.SetText(config.Notifications.PlacedBounty.Expired.Title);
				if (obfv_m_PlacedBountyExpiredMessage) obfv_m_PlacedBountyExpiredMessage.SetText(config.Notifications.PlacedBounty.Expired.Message);
				if (obfv_m_PlacedBountyExpiredIconPath) obfv_m_PlacedBountyExpiredIconPath.SetText(config.Notifications.PlacedBounty.Expired.IconPath);
			}
			if (obfv_m_PlacedBountySurvivalRewardEnabled && config.Notifications.PlacedBounty.SurvivalReward)
			{
				obfv_m_PlacedBountySurvivalRewardEnabled.SetChecked(config.Notifications.PlacedBounty.SurvivalReward.Enabled);
				if (obfv_m_PlacedBountySurvivalRewardTitle) obfv_m_PlacedBountySurvivalRewardTitle.SetText(config.Notifications.PlacedBounty.SurvivalReward.Title);
				if (obfv_m_PlacedBountySurvivalRewardMessage) obfv_m_PlacedBountySurvivalRewardMessage.SetText(config.Notifications.PlacedBounty.SurvivalReward.Message);
				if (obfv_m_PlacedBountySurvivalRewardIconPath) obfv_m_PlacedBountySurvivalRewardIconPath.SetText(config.Notifications.PlacedBounty.SurvivalReward.IconPath);
			}
			if (obfv_m_PlacedBountyKilledRewardEnabled && config.Notifications.PlacedBounty.KilledReward)
			{
				obfv_m_PlacedBountyKilledRewardEnabled.SetChecked(config.Notifications.PlacedBounty.KilledReward.Enabled);
				if (obfv_m_PlacedBountyKilledRewardTitle) obfv_m_PlacedBountyKilledRewardTitle.SetText(config.Notifications.PlacedBounty.KilledReward.Title);
				if (obfv_m_PlacedBountyKilledRewardMessage) obfv_m_PlacedBountyKilledRewardMessage.SetText(config.Notifications.PlacedBounty.KilledReward.Message);
				if (obfv_m_PlacedBountyKilledRewardIconPath) obfv_m_PlacedBountyKilledRewardIconPath.SetText(config.Notifications.PlacedBounty.KilledReward.IconPath);
			}
		}
		if (config.Notifications && config.Notifications.RuleBreaker)
		{
			if (obfv_m_RuleBreakerHuntedEnabled && config.Notifications.RuleBreaker.Hunted)
			{
				obfv_m_RuleBreakerHuntedEnabled.SetChecked(config.Notifications.RuleBreaker.Hunted.Enabled);
				if (obfv_m_RuleBreakerHuntedTitle) obfv_m_RuleBreakerHuntedTitle.SetText(config.Notifications.RuleBreaker.Hunted.Title);
				if (obfv_m_RuleBreakerHuntedMessage) obfv_m_RuleBreakerHuntedMessage.SetText(config.Notifications.RuleBreaker.Hunted.Message);
				if (obfv_m_RuleBreakerHuntedIconPath) obfv_m_RuleBreakerHuntedIconPath.SetText(config.Notifications.RuleBreaker.Hunted.IconPath);
			}
			if (obfv_m_RuleBreakerHitWarningEnabled && config.Notifications.RuleBreaker.HitWarning)
			{
				obfv_m_RuleBreakerHitWarningEnabled.SetChecked(config.Notifications.RuleBreaker.HitWarning.Enabled);
				if (obfv_m_RuleBreakerHitWarningTitle) obfv_m_RuleBreakerHitWarningTitle.SetText(config.Notifications.RuleBreaker.HitWarning.Title);
				if (obfv_m_RuleBreakerHitWarningMessage) obfv_m_RuleBreakerHitWarningMessage.SetText(config.Notifications.RuleBreaker.HitWarning.Message);
				if (obfv_m_RuleBreakerHitWarningIconPath) obfv_m_RuleBreakerHitWarningIconPath.SetText(config.Notifications.RuleBreaker.HitWarning.IconPath);
			}
			if (obfv_m_RuleBreakerExpiredEnabled && config.Notifications.RuleBreaker.Expired)
			{
				obfv_m_RuleBreakerExpiredEnabled.SetChecked(config.Notifications.RuleBreaker.Expired.Enabled);
				if (obfv_m_RuleBreakerExpiredTitle) obfv_m_RuleBreakerExpiredTitle.SetText(config.Notifications.RuleBreaker.Expired.Title);
				if (obfv_m_RuleBreakerExpiredMessage) obfv_m_RuleBreakerExpiredMessage.SetText(config.Notifications.RuleBreaker.Expired.Message);
				if (obfv_m_RuleBreakerExpiredIconPath) obfv_m_RuleBreakerExpiredIconPath.SetText(config.Notifications.RuleBreaker.Expired.IconPath);
			}
			if (obfv_m_RuleBreakerSurvivalRewardEnabled && config.Notifications.RuleBreaker.SurvivalReward)
			{
				obfv_m_RuleBreakerSurvivalRewardEnabled.SetChecked(config.Notifications.RuleBreaker.SurvivalReward.Enabled);
				if (obfv_m_RuleBreakerSurvivalRewardTitle) obfv_m_RuleBreakerSurvivalRewardTitle.SetText(config.Notifications.RuleBreaker.SurvivalReward.Title);
				if (obfv_m_RuleBreakerSurvivalRewardMessage) obfv_m_RuleBreakerSurvivalRewardMessage.SetText(config.Notifications.RuleBreaker.SurvivalReward.Message);
				if (obfv_m_RuleBreakerSurvivalRewardIconPath) obfv_m_RuleBreakerSurvivalRewardIconPath.SetText(config.Notifications.RuleBreaker.SurvivalReward.IconPath);
			}
			if (obfv_m_RuleBreakerKilledRewardEnabled && config.Notifications.RuleBreaker.KilledReward)
			{
				obfv_m_RuleBreakerKilledRewardEnabled.SetChecked(config.Notifications.RuleBreaker.KilledReward.Enabled);
				if (obfv_m_RuleBreakerKilledRewardTitle) obfv_m_RuleBreakerKilledRewardTitle.SetText(config.Notifications.RuleBreaker.KilledReward.Title);
				if (obfv_m_RuleBreakerKilledRewardMessage) obfv_m_RuleBreakerKilledRewardMessage.SetText(config.Notifications.RuleBreaker.KilledReward.Message);
				if (obfv_m_RuleBreakerKilledRewardIconPath) obfv_m_RuleBreakerKilledRewardIconPath.SetText(config.Notifications.RuleBreaker.KilledReward.IconPath);
			}
		}
		if (config.Notifications && config.Notifications.Other)
		{
			if (obfv_m_OtherInsufficientTokensEnabled && config.Notifications.Other.InsufficientTokens)
			{
				obfv_m_OtherInsufficientTokensEnabled.SetChecked(config.Notifications.Other.InsufficientTokens.Enabled);
				if (obfv_m_OtherInsufficientTokensTitle) obfv_m_OtherInsufficientTokensTitle.SetText(config.Notifications.Other.InsufficientTokens.Title);
				if (obfv_m_OtherInsufficientTokensMessage) obfv_m_OtherInsufficientTokensMessage.SetText(config.Notifications.Other.InsufficientTokens.Message);
				if (obfv_m_OtherInsufficientTokensIconPath) obfv_m_OtherInsufficientTokensIconPath.SetText(config.Notifications.Other.InsufficientTokens.IconPath);
			}
			if (obfv_m_OtherSkipBountyNoPlayersEnabled && config.Notifications.Other.SkipBountyNoPlayers)
			{
				obfv_m_OtherSkipBountyNoPlayersEnabled.SetChecked(config.Notifications.Other.SkipBountyNoPlayers.Enabled);
				if (obfv_m_OtherSkipBountyNoPlayersTitle) obfv_m_OtherSkipBountyNoPlayersTitle.SetText(config.Notifications.Other.SkipBountyNoPlayers.Title);
				if (obfv_m_OtherSkipBountyNoPlayersMessage) obfv_m_OtherSkipBountyNoPlayersMessage.SetText(config.Notifications.Other.SkipBountyNoPlayers.Message);
				if (obfv_m_OtherSkipBountyNoPlayersIconPath) obfv_m_OtherSkipBountyNoPlayersIconPath.SetText(config.Notifications.Other.SkipBountyNoPlayers.IconPath);
			}
			if (obfv_m_OtherSkipBountySuccessEnabled && config.Notifications.Other.SkipBountySuccess)
			{
				obfv_m_OtherSkipBountySuccessEnabled.SetChecked(config.Notifications.Other.SkipBountySuccess.Enabled);
				if (obfv_m_OtherSkipBountySuccessTitle) obfv_m_OtherSkipBountySuccessTitle.SetText(config.Notifications.Other.SkipBountySuccess.Title);
				if (obfv_m_OtherSkipBountySuccessMessage) obfv_m_OtherSkipBountySuccessMessage.SetText(config.Notifications.Other.SkipBountySuccess.Message);
				if (obfv_m_OtherSkipBountySuccessIconPath) obfv_m_OtherSkipBountySuccessIconPath.SetText(config.Notifications.Other.SkipBountySuccess.IconPath);
			}
			if (obfv_m_OtherBountySkippedEnabled && config.Notifications.Other.BountySkipped)
			{
				obfv_m_OtherBountySkippedEnabled.SetChecked(config.Notifications.Other.BountySkipped.Enabled);
				if (obfv_m_OtherBountySkippedTitle) obfv_m_OtherBountySkippedTitle.SetText(config.Notifications.Other.BountySkipped.Title);
				if (obfv_m_OtherBountySkippedMessage) obfv_m_OtherBountySkippedMessage.SetText(config.Notifications.Other.BountySkipped.Message);
				if (obfv_m_OtherBountySkippedIconPath) obfv_m_OtherBountySkippedIconPath.SetText(config.Notifications.Other.BountySkipped.IconPath);
			}
			if (obfv_m_OtherRewardHandsNotFreeEnabled && config.Notifications.Other.RewardHandsNotFree)
			{
				obfv_m_OtherRewardHandsNotFreeEnabled.SetChecked(config.Notifications.Other.RewardHandsNotFree.Enabled);
				if (obfv_m_OtherRewardHandsNotFreeTitle) obfv_m_OtherRewardHandsNotFreeTitle.SetText(config.Notifications.Other.RewardHandsNotFree.Title);
				if (obfv_m_OtherRewardHandsNotFreeMessage) obfv_m_OtherRewardHandsNotFreeMessage.SetText(config.Notifications.Other.RewardHandsNotFree.Message);
				if (obfv_m_OtherRewardHandsNotFreeIconPath) obfv_m_OtherRewardHandsNotFreeIconPath.SetText(config.Notifications.Other.RewardHandsNotFree.IconPath);
			}
			if (obfv_m_OtherPlayerOnCooldownEnabled && config.Notifications.Other.PlayerOnCooldown)
			{
				obfv_m_OtherPlayerOnCooldownEnabled.SetChecked(config.Notifications.Other.PlayerOnCooldown.Enabled);
				if (obfv_m_OtherPlayerOnCooldownTitle) obfv_m_OtherPlayerOnCooldownTitle.SetText(config.Notifications.Other.PlayerOnCooldown.Title);
				if (obfv_m_OtherPlayerOnCooldownMessage) obfv_m_OtherPlayerOnCooldownMessage.SetText(config.Notifications.Other.PlayerOnCooldown.Message);
				if (obfv_m_OtherPlayerOnCooldownIconPath) obfv_m_OtherPlayerOnCooldownIconPath.SetText(config.Notifications.Other.PlayerOnCooldown.IconPath);
			}
			if (obfv_m_OtherPlayerInSafeZoneEnabled && config.Notifications.Other.PlayerInSafeZone)
			{
				obfv_m_OtherPlayerInSafeZoneEnabled.SetChecked(config.Notifications.Other.PlayerInSafeZone.Enabled);
				if (obfv_m_OtherPlayerInSafeZoneTitle) obfv_m_OtherPlayerInSafeZoneTitle.SetText(config.Notifications.Other.PlayerInSafeZone.Title);
				if (obfv_m_OtherPlayerInSafeZoneMessage) obfv_m_OtherPlayerInSafeZoneMessage.SetText(config.Notifications.Other.PlayerInSafeZone.Message);
				if (obfv_m_OtherPlayerInSafeZoneIconPath) obfv_m_OtherPlayerInSafeZoneIconPath.SetText(config.Notifications.Other.PlayerInSafeZone.IconPath);
			}
			if (obfv_m_OtherBountyPersistedEnabled && config.Notifications.Other.BountyPersisted)
			{
				obfv_m_OtherBountyPersistedEnabled.SetChecked(config.Notifications.Other.BountyPersisted.Enabled);
				if (obfv_m_OtherBountyPersistedTitle) obfv_m_OtherBountyPersistedTitle.SetText(config.Notifications.Other.BountyPersisted.Title);
				if (obfv_m_OtherBountyPersistedMessage) obfv_m_OtherBountyPersistedMessage.SetText(config.Notifications.Other.BountyPersisted.Message);
				if (obfv_m_OtherBountyPersistedIconPath) obfv_m_OtherBountyPersistedIconPath.SetText(config.Notifications.Other.BountyPersisted.IconPath);
			}
			if (obfv_m_OtherTeleportedOutOfTerritoryEnabled && config.Notifications.Other.TeleportedOutOfTerritory)
			{
				obfv_m_OtherTeleportedOutOfTerritoryEnabled.SetChecked(config.Notifications.Other.TeleportedOutOfTerritory.Enabled);
				if (obfv_m_OtherTeleportedOutOfTerritoryTitle) obfv_m_OtherTeleportedOutOfTerritoryTitle.SetText(config.Notifications.Other.TeleportedOutOfTerritory.Title);
				if (obfv_m_OtherTeleportedOutOfTerritoryMessage) obfv_m_OtherTeleportedOutOfTerritoryMessage.SetText(config.Notifications.Other.TeleportedOutOfTerritory.Message);
				if (obfv_m_OtherTeleportedOutOfTerritoryIconPath) obfv_m_OtherTeleportedOutOfTerritoryIconPath.SetText(config.Notifications.Other.TeleportedOutOfTerritory.IconPath);
			}
			if (obfv_m_OtherBountyPausedInTerritoryEnabled && config.Notifications.Other.BountyPausedInTerritory)
			{
				obfv_m_OtherBountyPausedInTerritoryEnabled.SetChecked(config.Notifications.Other.BountyPausedInTerritory.Enabled);
				if (obfv_m_OtherBountyPausedInTerritoryTitle) obfv_m_OtherBountyPausedInTerritoryTitle.SetText(config.Notifications.Other.BountyPausedInTerritory.Title);
				if (obfv_m_OtherBountyPausedInTerritoryMessage) obfv_m_OtherBountyPausedInTerritoryMessage.SetText(config.Notifications.Other.BountyPausedInTerritory.Message);
				if (obfv_m_OtherBountyPausedInTerritoryIconPath) obfv_m_OtherBountyPausedInTerritoryIconPath.SetText(config.Notifications.Other.BountyPausedInTerritory.IconPath);
			}
		}
		if (config.Broadcasts)
		{
			if (obfv_m_BroadcastsPlacedBountyEnabled && config.Broadcasts.PlacedBounty)
			{
				obfv_m_BroadcastsPlacedBountyEnabled.SetChecked(config.Broadcasts.PlacedBounty.Enabled);
				if (obfv_m_BroadcastsPlacedBountyTitle) obfv_m_BroadcastsPlacedBountyTitle.SetText(config.Broadcasts.PlacedBounty.Title);
				if (obfv_m_BroadcastsPlacedBountyMessage) obfv_m_BroadcastsPlacedBountyMessage.SetText(config.Broadcasts.PlacedBounty.Message);
				if (obfv_m_BroadcastsPlacedBountyIconPath) obfv_m_BroadcastsPlacedBountyIconPath.SetText(config.Broadcasts.PlacedBounty.IconPath);
			}
			if (obfv_m_BroadcastsRuleBreakerEnabled && config.Broadcasts.RuleBreaker)
			{
				obfv_m_BroadcastsRuleBreakerEnabled.SetChecked(config.Broadcasts.RuleBreaker.Enabled);
				if (obfv_m_BroadcastsRuleBreakerTitle) obfv_m_BroadcastsRuleBreakerTitle.SetText(config.Broadcasts.RuleBreaker.Title);
				if (obfv_m_BroadcastsRuleBreakerMessage) obfv_m_BroadcastsRuleBreakerMessage.SetText(config.Broadcasts.RuleBreaker.Message);
				if (obfv_m_BroadcastsRuleBreakerIconPath) obfv_m_BroadcastsRuleBreakerIconPath.SetText(config.Broadcasts.RuleBreaker.IconPath);
			}
		}
	}
	void obfm_RefreshPlayersList()
	{
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestPlayers", new Param1<int>(0), true, player.GetIdentity());
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] Requested players list from server via RPC");
	}
	void obfm_UpdatePlayersList(array<string> players)
	{
		if (!obfv_m_PlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Cannot update - PlayersList widget is null!");
			return;
		}
		obfv_m_PlayersList.ClearItems();
		obfv_m_PlayerIdentifiers.Clear();
		if (!players)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Received null players array from server!");
			return;
		}
		foreach (string playerEntry : players)
		{
			if (playerEntry != "")
			{
				obfv_m_PlayerIdentifiers.Insert(obfm_GetPlayerEntryIdentifier(playerEntry));
				obfv_m_PlayersList.AddItem(obfm_GetPlayerEntryDisplayName(playerEntry), null, 0);
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] Updated players list: " + players.Count().ToString() + " players");
	}
	static void obfm_ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
	{
		if (!skipIDs)
			skipIDs = new TIntArray;
		skipIDs.Insert(UAUIBack);
		skipIDs.Insert(UABountyAdminMenu);
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
		super.OnClick(w, x, y, button);
		if (w == obfv_m_btnNormalSettings)
		{
			obfm_ShowOnlyPanel(obfv_m_GeneralRootPanel);
			return true;
		}
		else if (w == obfv_m_btnNotifications)
		{
			obfm_ShowOnlyPanel(obfv_m_NotificationsRootPanel);
			return true;
		}
		else if (w == obfv_m_btnBlacklist)
		{
			obfm_ShowOnlyPanel(obfv_m_BlacklistRootPanel);
			return true;
		}
		int selectedRow;
		string selectedPlayerName;
		string selectedPlayerIdentifier;
		int row;
		string entry;
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return false;
		if (w == obfv_m_BtnApplyTestRuleBreakerBounty)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ApplyTestRuleBreakerBounty:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ApplyTestRuleBreakerBounty button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnAddBountySelectedPlayer)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddBountySelectedPlayer:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] AddBountySelectedPlayer button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnClearBounty)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearBounty"), true, player.GetIdentity());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ClearBounty button clicked");
			return true;
		}
		else if (w == obfv_m_BtnClearBountySelectedPlayer)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearBountySelectedPlayer:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ClearBountySelectedPlayer button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnReloadConfigs)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ReloadConfigs"), true, player.GetIdentity());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ReloadConfigs button clicked");
			return true;
		}
		else if (w == obfv_m_BtnClearAllCooldowns)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearAllCooldowns:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ClearAllCooldowns button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnClearPlayerCooldown)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearPlayerCooldown:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] ClearPlayerCooldown button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnSaveAndReload)
		{
			obfc_BountyConfig updatedConfig = obfm_ReadConfigFromUI();
			if (updatedConfig)
			{
				GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminUpdateConfig", new Param1<ref obfc_BountyConfig>(updatedConfig), true, player.GetIdentity());
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] Save & Reload button clicked - config sent to server");
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Failed to read config from UI!");
			}
			return true;
		}
		else if (w == obfv_m_BtnAddRewardPoint)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddRewardPoint:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] AddRewardPoint button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		else if (w == obfv_m_BtnRemoveRewardPoint)
		{
			if (obfv_m_PlayersList)
			{
				selectedRow = obfv_m_PlayersList.GetSelectedRow();
				if (selectedRow >= 0)
				{
					if (selectedRow < obfv_m_PlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_PlayerIdentifiers.Get(selectedRow);
					obfv_m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("RemoveRewardPoint:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] RemoveRewardPoint button clicked for player: " + selectedPlayerName);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] No player selected from list!");
				}
			}
			return true;
		}
		if (w == obfv_m_AddToBlacklistBtn)
		{
			if (obfv_m_OnlinePlayersList)
			{
				row = obfv_m_OnlinePlayersList.GetSelectedRow();
				if (row >= 0)
				{
					selectedPlayerIdentifier = "";
					if (row < obfv_m_OnlinePlayerIdentifiers.Count())
						selectedPlayerIdentifier = obfv_m_OnlinePlayerIdentifiers.Get(row);
					obfv_m_OnlinePlayersList.GetItemText(row, 0, entry);
					if (selectedPlayerIdentifier != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddToBlacklist:" + selectedPlayerIdentifier), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] AddToBlacklist button clicked for player: " + entry);
					}
				}
			}
			return true;
		}
		else if (w == obfv_m_RemoveFromBlacklistBtn)
		{
			if (obfv_m_BlacklistedPlayersList)
			{
				row = obfv_m_BlacklistedPlayersList.GetSelectedRow();
				if (row >= 0)
				{
					obfv_m_BlacklistedPlayersList.GetItemText(row, 0, entry);
					if (entry != "")
					{
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("RemoveFromBlacklist:" + entry), true, player.GetIdentity());
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] RemoveFromBlacklist button clicked for entry: " + entry);
					}
				}
			}
			return true;
		}
		else if (w == obfv_m_RefreshBlacklistPlayerListBtn)
		{
			obfm_RefreshBlacklistLists();
			return true;
		}
		return false;
	}
	void obfm_RefreshBlacklistLists()
	{
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		if (!player || !player.GetIdentity())
			return;
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", new Param1<int>(0), true, player.GetIdentity());
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestBlacklist", new Param1<int>(0), true, player.GetIdentity());
	}
	void obfm_UpdateOnlinePlayersList(array<string> players)
	{
		if (!obfv_m_OnlinePlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Cannot update - OnlinePlayersList widget is null!");
			return;
		}
		obfv_m_OnlinePlayersList.ClearItems();
		obfv_m_OnlinePlayerIdentifiers.Clear();
		if (!players)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Received null players array from server!");
			return;
		}
		foreach (string playerEntry : players)
		{
			if (playerEntry != "")
			{
				obfv_m_OnlinePlayerIdentifiers.Insert(obfm_GetPlayerEntryIdentifier(playerEntry));
				obfv_m_OnlinePlayersList.AddItem(obfm_GetPlayerEntryDisplayName(playerEntry), null, 0);
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] Updated online players list: " + players.Count().ToString() + " players");
	}
	void obfm_UpdateBlacklistedPlayersList(array<string> blacklistedPlayers)
	{
		if (!obfv_m_BlacklistedPlayersList)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Cannot update - BlacklistedPlayersList widget is null!");
			return;
		}
		obfv_m_BlacklistedPlayersList.ClearItems();
		if (!blacklistedPlayers)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminMenu] Received null blacklisted players array from server!");
			return;
		}
		foreach (string entry : blacklistedPlayers)
		{
			if (entry != "")
			{
				obfv_m_BlacklistedPlayersList.AddItem(entry, null, 0);
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminMenu] Updated blacklisted players list: " + blacklistedPlayers.Count().ToString() + " players");
	}
	obfc_BountyConfig obfm_ReadConfigFromUI()
	{
		obfc_BountyConfig sourceConfig = obfv_m_CachedConfig;
		if (!sourceConfig)
			return null;
		obfc_BountyConfig config = new obfc_BountyConfig();
		string messageText;
		if (sourceConfig.Core)
		{
			config.Core = new obfc_BountyCoreSystemSettings();
			if (obfv_m_EnableBountySystem)
				config.Core.EnableBountySystem = obfv_m_EnableBountySystem.IsChecked();
			else
				config.Core.EnableBountySystem = sourceConfig.Core.EnableBountySystem;
			if (obfv_m_DisableSelfBounty)
				config.Core.DisableSelfBounty = obfv_m_DisableSelfBounty.IsChecked();
			else
				config.Core.DisableSelfBounty = sourceConfig.Core.DisableSelfBounty;
			if (obfv_m_TeleportOutOfOwnTerritory)
				config.Core.obfm_TeleportOutOfOwnTerritory = obfv_m_TeleportOutOfOwnTerritory.IsChecked();
			else
				config.Core.obfm_TeleportOutOfOwnTerritory = sourceConfig.Core.obfm_TeleportOutOfOwnTerritory;
			if (obfv_m_PauseBountyInTerritory)
				config.Core.PauseBountyInTerritory = obfv_m_PauseBountyInTerritory.IsChecked();
			else
				config.Core.PauseBountyInTerritory = sourceConfig.Core.PauseBountyInTerritory;
			if (obfv_m_TeleportOutOfSafeZone)
				config.Core.obfm_TeleportOutOfSafeZone = obfv_m_TeleportOutOfSafeZone.IsChecked();
			else
				config.Core.obfm_TeleportOutOfSafeZone = sourceConfig.Core.obfm_TeleportOutOfSafeZone;
			if (obfv_m_EnableAutomatedBountyPlacement)
				config.Core.EnableAutomatedBountyPlacement = obfv_m_EnableAutomatedBountyPlacement.IsChecked();
			else
				config.Core.EnableAutomatedBountyPlacement = sourceConfig.Core.EnableAutomatedBountyPlacement;
			if (obfv_m_BountyCooldownSeconds)
				config.Core.BountyCooldownSeconds = obfv_m_BountyCooldownSeconds.GetText().ToFloat();
			else
				config.Core.BountyCooldownSeconds = sourceConfig.Core.BountyCooldownSeconds;
			if (obfv_m_MaxBountiedPlayers)
				config.Core.MaxBountiedPlayers = obfv_m_MaxBountiedPlayers.GetText().ToInt();
			else
				config.Core.MaxBountiedPlayers = sourceConfig.Core.MaxBountiedPlayers;
			if (obfv_m_MinOnlinePlayersRequired)
				config.Core.MinOnlinePlayersRequired = obfv_m_MinOnlinePlayersRequired.GetText().ToInt();
			else
				config.Core.MinOnlinePlayersRequired = sourceConfig.Core.MinOnlinePlayersRequired;
			if (obfv_m_SkipBountyTokenRequired)
				config.Core.SkipBountyTokenRequired = obfv_m_SkipBountyTokenRequired.GetText().ToInt();
			else
				config.Core.SkipBountyTokenRequired = sourceConfig.Core.SkipBountyTokenRequired;
			if (obfv_m_PlaceBountyTokenRequired)
				config.Core.PlaceBountyTokenRequired = obfv_m_PlaceBountyTokenRequired.GetText().ToInt();
			else
				config.Core.PlaceBountyTokenRequired = sourceConfig.Core.PlaceBountyTokenRequired;
			if (obfv_m_ResumeBountyDistanceFromTerritory)
				config.Core.ResumeBountyDistanceFromTerritory = obfv_m_ResumeBountyDistanceFromTerritory.GetText().ToFloat();
			else
				config.Core.ResumeBountyDistanceFromTerritory = sourceConfig.Core.ResumeBountyDistanceFromTerritory;
			if (obfv_m_PausedBountyResumeCheckInterval)
				config.Core.PausedBountyResumeCheckInterval = obfv_m_PausedBountyResumeCheckInterval.GetText().ToFloat();
			else
				config.Core.PausedBountyResumeCheckInterval = sourceConfig.Core.PausedBountyResumeCheckInterval;
			if (obfv_m_TeleportOutOfSafeZoneDistance)
				config.Core.TeleportOutOfSafeZoneDistance = obfv_m_TeleportOutOfSafeZoneDistance.GetText().ToFloat();
			else
				config.Core.TeleportOutOfSafeZoneDistance = sourceConfig.Core.TeleportOutOfSafeZoneDistance;
			if (obfv_m_MinimumPlayerLifetimeSeconds)
				config.Core.MinimumPlayerLifetimeSeconds = obfv_m_MinimumPlayerLifetimeSeconds.GetText().ToInt();
			else
				config.Core.MinimumPlayerLifetimeSeconds = sourceConfig.Core.MinimumPlayerLifetimeSeconds;
			if (obfv_m_AutomatedBountyPlacementIntervalSeconds)
				config.Core.AutomatedBountyPlacementIntervalSeconds = obfv_m_AutomatedBountyPlacementIntervalSeconds.GetText().ToFloat();
			else
				config.Core.AutomatedBountyPlacementIntervalSeconds = sourceConfig.Core.AutomatedBountyPlacementIntervalSeconds;
		}
		if (sourceConfig.RuleBreaker)
		{
			config.RuleBreaker = new obfc_BountyRuleBreakerSettings();
			if (obfv_m_EnableRuleBreakerHitThreshold)
				config.RuleBreaker.EnableRuleBreakerHitThreshold = obfv_m_EnableRuleBreakerHitThreshold.IsChecked();
			else
				config.RuleBreaker.EnableRuleBreakerHitThreshold = sourceConfig.RuleBreaker.EnableRuleBreakerHitThreshold;
			if (obfv_m_EnablePvEToPvPRuleBreaker)
				config.RuleBreaker.EnablePvEToPvPRuleBreaker = obfv_m_EnablePvEToPvPRuleBreaker.IsChecked();
			else
				config.RuleBreaker.EnablePvEToPvPRuleBreaker = sourceConfig.RuleBreaker.EnablePvEToPvPRuleBreaker;
			if (obfv_m_ClearPendingRewardsOnRuleBreakerBounty)
				config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = obfv_m_ClearPendingRewardsOnRuleBreakerBounty.IsChecked();
			else
				config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = sourceConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty;
			if (obfv_m_AllowPvEToPvEVictimKill)
				config.RuleBreaker.AllowPvEToPvEVictimKill = obfv_m_AllowPvEToPvEVictimKill.IsChecked();
			else
				config.RuleBreaker.AllowPvEToPvEVictimKill = sourceConfig.RuleBreaker.AllowPvEToPvEVictimKill;
			if (obfv_m_BountyRuleBreakerDurationSeconds)
				config.RuleBreaker.BountyRuleBreakerDurationSeconds = obfv_m_BountyRuleBreakerDurationSeconds.GetText().ToFloat();
			else
				config.RuleBreaker.BountyRuleBreakerDurationSeconds = sourceConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
			if (obfv_m_RuleBreakerHitThresholdTime)
				config.RuleBreaker.RuleBreakerHitThresholdTime = obfv_m_RuleBreakerHitThresholdTime.GetText().ToFloat();
			else
				config.RuleBreaker.RuleBreakerHitThresholdTime = sourceConfig.RuleBreaker.RuleBreakerHitThresholdTime;
			if (obfv_m_RuleBreakerHitThresholdWarningHits)
				config.RuleBreaker.RuleBreakerHitThresholdWarningHits = obfv_m_RuleBreakerHitThresholdWarningHits.GetText().ToInt();
			else
				config.RuleBreaker.RuleBreakerHitThresholdWarningHits = sourceConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits;
			if (obfv_m_RuleBreakerHitThresholdBountyHits)
				config.RuleBreaker.RuleBreakerHitThresholdBountyHits = obfv_m_RuleBreakerHitThresholdBountyHits.GetText().ToInt();
			else
				config.RuleBreaker.RuleBreakerHitThresholdBountyHits = sourceConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
			if (obfv_m_PvEToPvPInstantRuleBreakerHits)
				config.RuleBreaker.PvEToPvPInstantRuleBreakerHits = obfv_m_PvEToPvPInstantRuleBreakerHits.GetText().ToInt();
			else
				config.RuleBreaker.PvEToPvPInstantRuleBreakerHits = sourceConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits;
			if (obfv_m_Expansion_EnableHardlineReputationDecrease)
				config.RuleBreaker.Expansion_EnableHardlineReputationDecrease = obfv_m_Expansion_EnableHardlineReputationDecrease.IsChecked();
			else
				config.RuleBreaker.Expansion_EnableHardlineReputationDecrease = sourceConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease;
			if (obfv_m_Expansion_HardlineReputationDecreaseAmount)
				config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = obfv_m_Expansion_HardlineReputationDecreaseAmount.GetText().ToInt();
			else
				config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = sourceConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount;
		}
		if (sourceConfig.PlacedBounty)
		{
			config.PlacedBounty = new obfc_BountyPlacedBountySettings();
			if (obfv_m_BountyDurationSeconds)
				config.PlacedBounty.BountyDurationSeconds = obfv_m_BountyDurationSeconds.GetText().ToFloat();
			else
				config.PlacedBounty.BountyDurationSeconds = sourceConfig.PlacedBounty.BountyDurationSeconds;
		}
		if (sourceConfig.Reward)
		{
			config.Reward = new obfc_BountyRewardSettings();
			if (obfv_m_EnableSurvivalReward)
				config.Reward.EnableSurvivalReward = obfv_m_EnableSurvivalReward.IsChecked();
			else
				config.Reward.EnableSurvivalReward = sourceConfig.Reward.EnableSurvivalReward;
			if (obfv_m_PvERuleBreakerGiveRewards)
				config.Reward.PvERuleBreakerGiveRewards = obfv_m_PvERuleBreakerGiveRewards.IsChecked();
			else
				config.Reward.PvERuleBreakerGiveRewards = sourceConfig.Reward.PvERuleBreakerGiveRewards;
		}
		if (sourceConfig.Map)
		{
			config.Map = new obfc_BountyMapSettings();
			if (obfv_m_BountyEnableMapDrawing)
				config.Map.BountyEnableMapDrawing = obfv_m_BountyEnableMapDrawing.IsChecked();
			else
				config.Map.BountyEnableMapDrawing = sourceConfig.Map.BountyEnableMapDrawing;
			if (obfv_m_BountyCircleReduceRadiusOverTime)
				config.Map.BountyCircleReduceRadiusOverTime = obfv_m_BountyCircleReduceRadiusOverTime.IsChecked();
			else
				config.Map.BountyCircleReduceRadiusOverTime = sourceConfig.Map.BountyCircleReduceRadiusOverTime;
			if (obfv_m_BountyCircleIncreaseRadiusOverTime)
				config.Map.BountyCircleIncreaseRadiusOverTime = obfv_m_BountyCircleIncreaseRadiusOverTime.IsChecked();
			else
				config.Map.BountyCircleIncreaseRadiusOverTime = sourceConfig.Map.BountyCircleIncreaseRadiusOverTime;
			if (obfv_m_BountyCircleRadius)
				config.Map.BountyCircleRadius = obfv_m_BountyCircleRadius.GetText().ToFloat();
			else
				config.Map.BountyCircleRadius = sourceConfig.Map.BountyCircleRadius;
			if (obfv_m_BountyCircleMinRadius)
				config.Map.BountyCircleMinRadius = obfv_m_BountyCircleMinRadius.GetText().ToFloat();
			else
				config.Map.BountyCircleMinRadius = sourceConfig.Map.BountyCircleMinRadius;
			if (obfv_m_BountyCircleColor)
				config.Map.BountyCircleColor = obfv_m_BountyCircleColor.GetText().ToInt();
			else
				config.Map.BountyCircleColor = sourceConfig.Map.BountyCircleColor;
			if (obfv_m_BountyCircleDrawingWidth)
				config.Map.BountyCircleDrawingWidth = obfv_m_BountyCircleDrawingWidth.GetText().ToInt();
			else
				config.Map.BountyCircleDrawingWidth = sourceConfig.Map.BountyCircleDrawingWidth;
			if (obfv_m_BountyMapUpdateIntervalSeconds)
				config.Map.BountyMapUpdateIntervalSeconds = obfv_m_BountyMapUpdateIntervalSeconds.GetText().ToFloat();
			else
				config.Map.BountyMapUpdateIntervalSeconds = sourceConfig.Map.BountyMapUpdateIntervalSeconds;
			if (obfv_m_BountyMapRequestCooldownSeconds)
				config.Map.BountyMapRequestCooldownSeconds = obfv_m_BountyMapRequestCooldownSeconds.GetText().ToFloat();
			else
				config.Map.BountyMapRequestCooldownSeconds = sourceConfig.Map.BountyMapRequestCooldownSeconds;
			if (obfv_m_BountyMapSyncIntervalSeconds)
				config.Map.BountyMapSyncIntervalSeconds = obfv_m_BountyMapSyncIntervalSeconds.GetText().ToFloat();
			else
				config.Map.BountyMapSyncIntervalSeconds = sourceConfig.Map.BountyMapSyncIntervalSeconds;
			if (obfv_m_BountyMapSyncIntervalNoBountiesSeconds)
				config.Map.BountyMapSyncIntervalNoBountiesSeconds = obfv_m_BountyMapSyncIntervalNoBountiesSeconds.GetText().ToFloat();
			else
				config.Map.BountyMapSyncIntervalNoBountiesSeconds = sourceConfig.Map.BountyMapSyncIntervalNoBountiesSeconds;
			if (obfv_m_BountyCircleOffsetMinMultiplier)
				config.Map.BountyCircleOffsetMinMultiplier = obfv_m_BountyCircleOffsetMinMultiplier.GetText().ToFloat();
			else
				config.Map.BountyCircleOffsetMinMultiplier = sourceConfig.Map.BountyCircleOffsetMinMultiplier;
			if (obfv_m_BountyCircleOffsetMaxMultiplier)
				config.Map.BountyCircleOffsetMaxMultiplier = obfv_m_BountyCircleOffsetMaxMultiplier.GetText().ToFloat();
			else
				config.Map.BountyCircleOffsetMaxMultiplier = sourceConfig.Map.BountyCircleOffsetMaxMultiplier;
		}
		if (sourceConfig.UI)
		{
			config.UI = new obfc_BountyUISettings();
			if (obfv_m_CountdownWidgetPositionX)
				config.UI.CountdownWidgetPositionX = obfv_m_CountdownWidgetPositionX.GetText().ToFloat();
			else
				config.UI.CountdownWidgetPositionX = sourceConfig.UI.CountdownWidgetPositionX;
			if (obfv_m_CountdownWidgetPositionY)
				config.UI.CountdownWidgetPositionY = obfv_m_CountdownWidgetPositionY.GetText().ToFloat();
			else
				config.UI.CountdownWidgetPositionY = sourceConfig.UI.CountdownWidgetPositionY;
			if (obfv_m_CountdownWidgetWidth)
				config.UI.CountdownWidgetWidth = obfv_m_CountdownWidgetWidth.GetText().ToFloat();
			else
				config.UI.CountdownWidgetWidth = sourceConfig.UI.CountdownWidgetWidth;
			if (obfv_m_CountdownWidgetHeight)
				config.UI.CountdownWidgetHeight = obfv_m_CountdownWidgetHeight.GetText().ToFloat();
			else
				config.UI.CountdownWidgetHeight = sourceConfig.UI.CountdownWidgetHeight;
			if (obfv_m_CountdownWidgetBackgroundColor)
				config.UI.CountdownWidgetBackgroundColor = obfv_m_CountdownWidgetBackgroundColor.GetText().ToInt();
			else
				config.UI.CountdownWidgetBackgroundColor = sourceConfig.UI.CountdownWidgetBackgroundColor;
			if (obfv_m_CountdownWidgetTextColor)
				config.UI.CountdownWidgetTextColor = obfv_m_CountdownWidgetTextColor.GetText().ToInt();
			else
				config.UI.CountdownWidgetTextColor = sourceConfig.UI.CountdownWidgetTextColor;
		}
		if (sourceConfig.Notifications && sourceConfig.Notifications.PlacedBounty)
		{
			if (!config.Notifications)
				config.Notifications = new obfc_BountyNotificationConfig();
			if (!config.Notifications.PlacedBounty)
				config.Notifications.PlacedBounty = new obfc_BountyNotificationGroup();
			if (obfv_m_PlacedBountyHuntedEnabled && config.Notifications.PlacedBounty.Hunted)
			{
				config.Notifications.PlacedBounty.Hunted.Enabled = obfv_m_PlacedBountyHuntedEnabled.IsChecked();
				if (obfv_m_PlacedBountyHuntedTitle) config.Notifications.PlacedBounty.Hunted.Title = obfv_m_PlacedBountyHuntedTitle.GetText();
				if (obfv_m_PlacedBountyHuntedMessage)
				{
					obfv_m_PlacedBountyHuntedMessage.GetText(messageText);
					config.Notifications.PlacedBounty.Hunted.Message = messageText;
				}
				if (obfv_m_PlacedBountyHuntedIconPath) config.Notifications.PlacedBounty.Hunted.IconPath = obfv_m_PlacedBountyHuntedIconPath.GetText();
			}
			else if (config.Notifications.PlacedBounty.Hunted)
			{
				config.Notifications.PlacedBounty.Hunted.Enabled = sourceConfig.Notifications.PlacedBounty.Hunted.Enabled;
				config.Notifications.PlacedBounty.Hunted.Title = sourceConfig.Notifications.PlacedBounty.Hunted.Title;
				config.Notifications.PlacedBounty.Hunted.Message = sourceConfig.Notifications.PlacedBounty.Hunted.Message;
				config.Notifications.PlacedBounty.Hunted.IconPath = sourceConfig.Notifications.PlacedBounty.Hunted.IconPath;
			}
			if (obfv_m_PlacedBountyExpiredEnabled && config.Notifications.PlacedBounty.Expired)
			{
				config.Notifications.PlacedBounty.Expired.Enabled = obfv_m_PlacedBountyExpiredEnabled.IsChecked();
				if (obfv_m_PlacedBountyExpiredTitle) config.Notifications.PlacedBounty.Expired.Title = obfv_m_PlacedBountyExpiredTitle.GetText();
				if (obfv_m_PlacedBountyExpiredMessage)
				{
					obfv_m_PlacedBountyExpiredMessage.GetText(messageText);
					config.Notifications.PlacedBounty.Expired.Message = messageText;
				}
				if (obfv_m_PlacedBountyExpiredIconPath) config.Notifications.PlacedBounty.Expired.IconPath = obfv_m_PlacedBountyExpiredIconPath.GetText();
			}
			else if (config.Notifications.PlacedBounty.Expired)
			{
				config.Notifications.PlacedBounty.Expired.Enabled = sourceConfig.Notifications.PlacedBounty.Expired.Enabled;
				config.Notifications.PlacedBounty.Expired.Title = sourceConfig.Notifications.PlacedBounty.Expired.Title;
				config.Notifications.PlacedBounty.Expired.Message = sourceConfig.Notifications.PlacedBounty.Expired.Message;
				config.Notifications.PlacedBounty.Expired.IconPath = sourceConfig.Notifications.PlacedBounty.Expired.IconPath;
			}
			if (obfv_m_PlacedBountySurvivalRewardEnabled && config.Notifications.PlacedBounty.SurvivalReward)
			{
				config.Notifications.PlacedBounty.SurvivalReward.Enabled = obfv_m_PlacedBountySurvivalRewardEnabled.IsChecked();
				if (obfv_m_PlacedBountySurvivalRewardTitle) config.Notifications.PlacedBounty.SurvivalReward.Title = obfv_m_PlacedBountySurvivalRewardTitle.GetText();
				if (obfv_m_PlacedBountySurvivalRewardMessage)
				{
					obfv_m_PlacedBountySurvivalRewardMessage.GetText(messageText);
					config.Notifications.PlacedBounty.SurvivalReward.Message = messageText;
				}
				if (obfv_m_PlacedBountySurvivalRewardIconPath) config.Notifications.PlacedBounty.SurvivalReward.IconPath = obfv_m_PlacedBountySurvivalRewardIconPath.GetText();
			}
			else if (config.Notifications.PlacedBounty.SurvivalReward)
			{
				config.Notifications.PlacedBounty.SurvivalReward.Enabled = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Enabled;
				config.Notifications.PlacedBounty.SurvivalReward.Title = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Title;
				config.Notifications.PlacedBounty.SurvivalReward.Message = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Message;
				config.Notifications.PlacedBounty.SurvivalReward.IconPath = sourceConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
			}
			if (obfv_m_PlacedBountyKilledRewardEnabled && config.Notifications.PlacedBounty.KilledReward)
			{
				config.Notifications.PlacedBounty.KilledReward.Enabled = obfv_m_PlacedBountyKilledRewardEnabled.IsChecked();
				if (obfv_m_PlacedBountyKilledRewardTitle) config.Notifications.PlacedBounty.KilledReward.Title = obfv_m_PlacedBountyKilledRewardTitle.GetText();
				if (obfv_m_PlacedBountyKilledRewardMessage)
				{
					obfv_m_PlacedBountyKilledRewardMessage.GetText(messageText);
					config.Notifications.PlacedBounty.KilledReward.Message = messageText;
				}
				if (obfv_m_PlacedBountyKilledRewardIconPath) config.Notifications.PlacedBounty.KilledReward.IconPath = obfv_m_PlacedBountyKilledRewardIconPath.GetText();
			}
			else if (config.Notifications.PlacedBounty.KilledReward)
			{
				config.Notifications.PlacedBounty.KilledReward.Enabled = sourceConfig.Notifications.PlacedBounty.KilledReward.Enabled;
				config.Notifications.PlacedBounty.KilledReward.Title = sourceConfig.Notifications.PlacedBounty.KilledReward.Title;
				config.Notifications.PlacedBounty.KilledReward.Message = sourceConfig.Notifications.PlacedBounty.KilledReward.Message;
				config.Notifications.PlacedBounty.KilledReward.IconPath = sourceConfig.Notifications.PlacedBounty.KilledReward.IconPath;
			}
		}
		if (sourceConfig.Notifications && sourceConfig.Notifications.RuleBreaker)
		{
			if (!config.Notifications)
				config.Notifications = new obfc_BountyNotificationConfig();
			if (!config.Notifications.RuleBreaker)
				config.Notifications.RuleBreaker = new obfc_BountyRuleBreakerNotificationGroup();
			if (obfv_m_RuleBreakerHuntedEnabled && config.Notifications.RuleBreaker.Hunted)
			{
				config.Notifications.RuleBreaker.Hunted.Enabled = obfv_m_RuleBreakerHuntedEnabled.IsChecked();
				if (obfv_m_RuleBreakerHuntedTitle) config.Notifications.RuleBreaker.Hunted.Title = obfv_m_RuleBreakerHuntedTitle.GetText();
				if (obfv_m_RuleBreakerHuntedMessage)
				{
					obfv_m_RuleBreakerHuntedMessage.GetText(messageText);
					config.Notifications.RuleBreaker.Hunted.Message = messageText;
				}
				if (obfv_m_RuleBreakerHuntedIconPath) config.Notifications.RuleBreaker.Hunted.IconPath = obfv_m_RuleBreakerHuntedIconPath.GetText();
			}
			else if (config.Notifications.RuleBreaker.Hunted)
			{
				config.Notifications.RuleBreaker.Hunted.Enabled = sourceConfig.Notifications.RuleBreaker.Hunted.Enabled;
				config.Notifications.RuleBreaker.Hunted.Title = sourceConfig.Notifications.RuleBreaker.Hunted.Title;
				config.Notifications.RuleBreaker.Hunted.Message = sourceConfig.Notifications.RuleBreaker.Hunted.Message;
				config.Notifications.RuleBreaker.Hunted.IconPath = sourceConfig.Notifications.RuleBreaker.Hunted.IconPath;
			}
			if (obfv_m_RuleBreakerHitWarningEnabled && config.Notifications.RuleBreaker.HitWarning)
			{
				config.Notifications.RuleBreaker.HitWarning.Enabled = obfv_m_RuleBreakerHitWarningEnabled.IsChecked();
				if (obfv_m_RuleBreakerHitWarningTitle) config.Notifications.RuleBreaker.HitWarning.Title = obfv_m_RuleBreakerHitWarningTitle.GetText();
				if (obfv_m_RuleBreakerHitWarningMessage)
				{
					obfv_m_RuleBreakerHitWarningMessage.GetText(messageText);
					config.Notifications.RuleBreaker.HitWarning.Message = messageText;
				}
				if (obfv_m_RuleBreakerHitWarningIconPath) config.Notifications.RuleBreaker.HitWarning.IconPath = obfv_m_RuleBreakerHitWarningIconPath.GetText();
			}
			else if (config.Notifications.RuleBreaker.HitWarning)
			{
				config.Notifications.RuleBreaker.HitWarning.Enabled = sourceConfig.Notifications.RuleBreaker.HitWarning.Enabled;
				config.Notifications.RuleBreaker.HitWarning.Title = sourceConfig.Notifications.RuleBreaker.HitWarning.Title;
				config.Notifications.RuleBreaker.HitWarning.Message = sourceConfig.Notifications.RuleBreaker.HitWarning.Message;
				config.Notifications.RuleBreaker.HitWarning.IconPath = sourceConfig.Notifications.RuleBreaker.HitWarning.IconPath;
			}
			if (obfv_m_RuleBreakerExpiredEnabled && config.Notifications.RuleBreaker.Expired)
			{
				config.Notifications.RuleBreaker.Expired.Enabled = obfv_m_RuleBreakerExpiredEnabled.IsChecked();
				if (obfv_m_RuleBreakerExpiredTitle) config.Notifications.RuleBreaker.Expired.Title = obfv_m_RuleBreakerExpiredTitle.GetText();
				if (obfv_m_RuleBreakerExpiredMessage)
				{
					obfv_m_RuleBreakerExpiredMessage.GetText(messageText);
					config.Notifications.RuleBreaker.Expired.Message = messageText;
				}
				if (obfv_m_RuleBreakerExpiredIconPath) config.Notifications.RuleBreaker.Expired.IconPath = obfv_m_RuleBreakerExpiredIconPath.GetText();
			}
			else if (config.Notifications.RuleBreaker.Expired)
			{
				config.Notifications.RuleBreaker.Expired.Enabled = sourceConfig.Notifications.RuleBreaker.Expired.Enabled;
				config.Notifications.RuleBreaker.Expired.Title = sourceConfig.Notifications.RuleBreaker.Expired.Title;
				config.Notifications.RuleBreaker.Expired.Message = sourceConfig.Notifications.RuleBreaker.Expired.Message;
				config.Notifications.RuleBreaker.Expired.IconPath = sourceConfig.Notifications.RuleBreaker.Expired.IconPath;
			}
			if (obfv_m_RuleBreakerSurvivalRewardEnabled && config.Notifications.RuleBreaker.SurvivalReward)
			{
				config.Notifications.RuleBreaker.SurvivalReward.Enabled = obfv_m_RuleBreakerSurvivalRewardEnabled.IsChecked();
				if (obfv_m_RuleBreakerSurvivalRewardTitle) config.Notifications.RuleBreaker.SurvivalReward.Title = obfv_m_RuleBreakerSurvivalRewardTitle.GetText();
				if (obfv_m_RuleBreakerSurvivalRewardMessage)
				{
					obfv_m_RuleBreakerSurvivalRewardMessage.GetText(messageText);
					config.Notifications.RuleBreaker.SurvivalReward.Message = messageText;
				}
				if (obfv_m_RuleBreakerSurvivalRewardIconPath) config.Notifications.RuleBreaker.SurvivalReward.IconPath = obfv_m_RuleBreakerSurvivalRewardIconPath.GetText();
			}
			else if (config.Notifications.RuleBreaker.SurvivalReward)
			{
				config.Notifications.RuleBreaker.SurvivalReward.Enabled = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Enabled;
				config.Notifications.RuleBreaker.SurvivalReward.Title = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Title;
				config.Notifications.RuleBreaker.SurvivalReward.Message = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Message;
				config.Notifications.RuleBreaker.SurvivalReward.IconPath = sourceConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
			}
			if (obfv_m_RuleBreakerKilledRewardEnabled && config.Notifications.RuleBreaker.KilledReward)
			{
				config.Notifications.RuleBreaker.KilledReward.Enabled = obfv_m_RuleBreakerKilledRewardEnabled.IsChecked();
				if (obfv_m_RuleBreakerKilledRewardTitle) config.Notifications.RuleBreaker.KilledReward.Title = obfv_m_RuleBreakerKilledRewardTitle.GetText();
				if (obfv_m_RuleBreakerKilledRewardMessage)
				{
					obfv_m_RuleBreakerKilledRewardMessage.GetText(messageText);
					config.Notifications.RuleBreaker.KilledReward.Message = messageText;
				}
				if (obfv_m_RuleBreakerKilledRewardIconPath) config.Notifications.RuleBreaker.KilledReward.IconPath = obfv_m_RuleBreakerKilledRewardIconPath.GetText();
			}
			else if (config.Notifications.RuleBreaker.KilledReward)
			{
				config.Notifications.RuleBreaker.KilledReward.Enabled = sourceConfig.Notifications.RuleBreaker.KilledReward.Enabled;
				config.Notifications.RuleBreaker.KilledReward.Title = sourceConfig.Notifications.RuleBreaker.KilledReward.Title;
				config.Notifications.RuleBreaker.KilledReward.Message = sourceConfig.Notifications.RuleBreaker.KilledReward.Message;
				config.Notifications.RuleBreaker.KilledReward.IconPath = sourceConfig.Notifications.RuleBreaker.KilledReward.IconPath;
			}
		}
		if (sourceConfig.Notifications && sourceConfig.Notifications.Other)
		{
			if (!config.Notifications)
				config.Notifications = new obfc_BountyNotificationConfig();
			if (!config.Notifications.Other)
				config.Notifications.Other = new obfc_BountyOtherNotifications();
			if (obfv_m_OtherInsufficientTokensEnabled && config.Notifications.Other.InsufficientTokens)
			{
				config.Notifications.Other.InsufficientTokens.Enabled = obfv_m_OtherInsufficientTokensEnabled.IsChecked();
				if (obfv_m_OtherInsufficientTokensTitle) config.Notifications.Other.InsufficientTokens.Title = obfv_m_OtherInsufficientTokensTitle.GetText();
				if (obfv_m_OtherInsufficientTokensMessage)
				{
					obfv_m_OtherInsufficientTokensMessage.GetText(messageText);
					config.Notifications.Other.InsufficientTokens.Message = messageText;
				}
				if (obfv_m_OtherInsufficientTokensIconPath) config.Notifications.Other.InsufficientTokens.IconPath = obfv_m_OtherInsufficientTokensIconPath.GetText();
			}
			else if (config.Notifications.Other.InsufficientTokens)
			{
				config.Notifications.Other.InsufficientTokens.Enabled = sourceConfig.Notifications.Other.InsufficientTokens.Enabled;
				config.Notifications.Other.InsufficientTokens.Title = sourceConfig.Notifications.Other.InsufficientTokens.Title;
				config.Notifications.Other.InsufficientTokens.Message = sourceConfig.Notifications.Other.InsufficientTokens.Message;
				config.Notifications.Other.InsufficientTokens.IconPath = sourceConfig.Notifications.Other.InsufficientTokens.IconPath;
			}
			if (obfv_m_OtherSkipBountyNoPlayersEnabled && config.Notifications.Other.SkipBountyNoPlayers)
			{
				config.Notifications.Other.SkipBountyNoPlayers.Enabled = obfv_m_OtherSkipBountyNoPlayersEnabled.IsChecked();
				if (obfv_m_OtherSkipBountyNoPlayersTitle) config.Notifications.Other.SkipBountyNoPlayers.Title = obfv_m_OtherSkipBountyNoPlayersTitle.GetText();
				if (obfv_m_OtherSkipBountyNoPlayersMessage)
				{
					obfv_m_OtherSkipBountyNoPlayersMessage.GetText(messageText);
					config.Notifications.Other.SkipBountyNoPlayers.Message = messageText;
				}
				if (obfv_m_OtherSkipBountyNoPlayersIconPath) config.Notifications.Other.SkipBountyNoPlayers.IconPath = obfv_m_OtherSkipBountyNoPlayersIconPath.GetText();
			}
			else if (config.Notifications.Other.SkipBountyNoPlayers)
			{
				config.Notifications.Other.SkipBountyNoPlayers.Enabled = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Enabled;
				config.Notifications.Other.SkipBountyNoPlayers.Title = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Title;
				config.Notifications.Other.SkipBountyNoPlayers.Message = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Message;
				config.Notifications.Other.SkipBountyNoPlayers.IconPath = sourceConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
			}
			if (obfv_m_OtherSkipBountySuccessEnabled && config.Notifications.Other.SkipBountySuccess)
			{
				config.Notifications.Other.SkipBountySuccess.Enabled = obfv_m_OtherSkipBountySuccessEnabled.IsChecked();
				if (obfv_m_OtherSkipBountySuccessTitle) config.Notifications.Other.SkipBountySuccess.Title = obfv_m_OtherSkipBountySuccessTitle.GetText();
				if (obfv_m_OtherSkipBountySuccessMessage)
				{
					obfv_m_OtherSkipBountySuccessMessage.GetText(messageText);
					config.Notifications.Other.SkipBountySuccess.Message = messageText;
				}
				if (obfv_m_OtherSkipBountySuccessIconPath) config.Notifications.Other.SkipBountySuccess.IconPath = obfv_m_OtherSkipBountySuccessIconPath.GetText();
			}
			else if (config.Notifications.Other.SkipBountySuccess)
			{
				config.Notifications.Other.SkipBountySuccess.Enabled = sourceConfig.Notifications.Other.SkipBountySuccess.Enabled;
				config.Notifications.Other.SkipBountySuccess.Title = sourceConfig.Notifications.Other.SkipBountySuccess.Title;
				config.Notifications.Other.SkipBountySuccess.Message = sourceConfig.Notifications.Other.SkipBountySuccess.Message;
				config.Notifications.Other.SkipBountySuccess.IconPath = sourceConfig.Notifications.Other.SkipBountySuccess.IconPath;
			}
			if (obfv_m_OtherBountySkippedEnabled && config.Notifications.Other.BountySkipped)
			{
				config.Notifications.Other.BountySkipped.Enabled = obfv_m_OtherBountySkippedEnabled.IsChecked();
				if (obfv_m_OtherBountySkippedTitle) config.Notifications.Other.BountySkipped.Title = obfv_m_OtherBountySkippedTitle.GetText();
				if (obfv_m_OtherBountySkippedMessage)
				{
					obfv_m_OtherBountySkippedMessage.GetText(messageText);
					config.Notifications.Other.BountySkipped.Message = messageText;
				}
				if (obfv_m_OtherBountySkippedIconPath) config.Notifications.Other.BountySkipped.IconPath = obfv_m_OtherBountySkippedIconPath.GetText();
			}
			else if (config.Notifications.Other.BountySkipped)
			{
				config.Notifications.Other.BountySkipped.Enabled = sourceConfig.Notifications.Other.BountySkipped.Enabled;
				config.Notifications.Other.BountySkipped.Title = sourceConfig.Notifications.Other.BountySkipped.Title;
				config.Notifications.Other.BountySkipped.Message = sourceConfig.Notifications.Other.BountySkipped.Message;
				config.Notifications.Other.BountySkipped.IconPath = sourceConfig.Notifications.Other.BountySkipped.IconPath;
			}
			if (obfv_m_OtherRewardHandsNotFreeEnabled && config.Notifications.Other.RewardHandsNotFree)
			{
				config.Notifications.Other.RewardHandsNotFree.Enabled = obfv_m_OtherRewardHandsNotFreeEnabled.IsChecked();
				if (obfv_m_OtherRewardHandsNotFreeTitle) config.Notifications.Other.RewardHandsNotFree.Title = obfv_m_OtherRewardHandsNotFreeTitle.GetText();
				if (obfv_m_OtherRewardHandsNotFreeMessage)
				{
					obfv_m_OtherRewardHandsNotFreeMessage.GetText(messageText);
					config.Notifications.Other.RewardHandsNotFree.Message = messageText;
				}
				if (obfv_m_OtherRewardHandsNotFreeIconPath) config.Notifications.Other.RewardHandsNotFree.IconPath = obfv_m_OtherRewardHandsNotFreeIconPath.GetText();
			}
			else if (config.Notifications.Other.RewardHandsNotFree)
			{
				config.Notifications.Other.RewardHandsNotFree.Enabled = sourceConfig.Notifications.Other.RewardHandsNotFree.Enabled;
				config.Notifications.Other.RewardHandsNotFree.Title = sourceConfig.Notifications.Other.RewardHandsNotFree.Title;
				config.Notifications.Other.RewardHandsNotFree.Message = sourceConfig.Notifications.Other.RewardHandsNotFree.Message;
				config.Notifications.Other.RewardHandsNotFree.IconPath = sourceConfig.Notifications.Other.RewardHandsNotFree.IconPath;
			}
			if (obfv_m_OtherPlayerOnCooldownEnabled && config.Notifications.Other.PlayerOnCooldown)
			{
				config.Notifications.Other.PlayerOnCooldown.Enabled = obfv_m_OtherPlayerOnCooldownEnabled.IsChecked();
				if (obfv_m_OtherPlayerOnCooldownTitle) config.Notifications.Other.PlayerOnCooldown.Title = obfv_m_OtherPlayerOnCooldownTitle.GetText();
				if (obfv_m_OtherPlayerOnCooldownMessage)
				{
					obfv_m_OtherPlayerOnCooldownMessage.GetText(messageText);
					config.Notifications.Other.PlayerOnCooldown.Message = messageText;
				}
				if (obfv_m_OtherPlayerOnCooldownIconPath) config.Notifications.Other.PlayerOnCooldown.IconPath = obfv_m_OtherPlayerOnCooldownIconPath.GetText();
			}
			else if (config.Notifications.Other.PlayerOnCooldown)
			{
				config.Notifications.Other.PlayerOnCooldown.Enabled = sourceConfig.Notifications.Other.PlayerOnCooldown.Enabled;
				config.Notifications.Other.PlayerOnCooldown.Title = sourceConfig.Notifications.Other.PlayerOnCooldown.Title;
				config.Notifications.Other.PlayerOnCooldown.Message = sourceConfig.Notifications.Other.PlayerOnCooldown.Message;
				config.Notifications.Other.PlayerOnCooldown.IconPath = sourceConfig.Notifications.Other.PlayerOnCooldown.IconPath;
			}
			if (obfv_m_OtherPlayerInSafeZoneEnabled && config.Notifications.Other.PlayerInSafeZone)
			{
				config.Notifications.Other.PlayerInSafeZone.Enabled = obfv_m_OtherPlayerInSafeZoneEnabled.IsChecked();
				if (obfv_m_OtherPlayerInSafeZoneTitle) config.Notifications.Other.PlayerInSafeZone.Title = obfv_m_OtherPlayerInSafeZoneTitle.GetText();
				if (obfv_m_OtherPlayerInSafeZoneMessage)
				{
					obfv_m_OtherPlayerInSafeZoneMessage.GetText(messageText);
					config.Notifications.Other.PlayerInSafeZone.Message = messageText;
				}
				if (obfv_m_OtherPlayerInSafeZoneIconPath) config.Notifications.Other.PlayerInSafeZone.IconPath = obfv_m_OtherPlayerInSafeZoneIconPath.GetText();
			}
			else if (config.Notifications.Other.PlayerInSafeZone)
			{
				config.Notifications.Other.PlayerInSafeZone.Enabled = sourceConfig.Notifications.Other.PlayerInSafeZone.Enabled;
				config.Notifications.Other.PlayerInSafeZone.Title = sourceConfig.Notifications.Other.PlayerInSafeZone.Title;
				config.Notifications.Other.PlayerInSafeZone.Message = sourceConfig.Notifications.Other.PlayerInSafeZone.Message;
				config.Notifications.Other.PlayerInSafeZone.IconPath = sourceConfig.Notifications.Other.PlayerInSafeZone.IconPath;
			}
			if (obfv_m_OtherBountyPersistedEnabled && config.Notifications.Other.BountyPersisted)
			{
				config.Notifications.Other.BountyPersisted.Enabled = obfv_m_OtherBountyPersistedEnabled.IsChecked();
				if (obfv_m_OtherBountyPersistedTitle) config.Notifications.Other.BountyPersisted.Title = obfv_m_OtherBountyPersistedTitle.GetText();
				if (obfv_m_OtherBountyPersistedMessage)
				{
					obfv_m_OtherBountyPersistedMessage.GetText(messageText);
					config.Notifications.Other.BountyPersisted.Message = messageText;
				}
				if (obfv_m_OtherBountyPersistedIconPath) config.Notifications.Other.BountyPersisted.IconPath = obfv_m_OtherBountyPersistedIconPath.GetText();
			}
			else if (config.Notifications.Other.BountyPersisted)
			{
				config.Notifications.Other.BountyPersisted.Enabled = sourceConfig.Notifications.Other.BountyPersisted.Enabled;
				config.Notifications.Other.BountyPersisted.Title = sourceConfig.Notifications.Other.BountyPersisted.Title;
				config.Notifications.Other.BountyPersisted.Message = sourceConfig.Notifications.Other.BountyPersisted.Message;
				config.Notifications.Other.BountyPersisted.IconPath = sourceConfig.Notifications.Other.BountyPersisted.IconPath;
			}
			if (obfv_m_OtherTeleportedOutOfTerritoryEnabled && config.Notifications.Other.TeleportedOutOfTerritory)
			{
				config.Notifications.Other.TeleportedOutOfTerritory.Enabled = obfv_m_OtherTeleportedOutOfTerritoryEnabled.IsChecked();
				if (obfv_m_OtherTeleportedOutOfTerritoryTitle) config.Notifications.Other.TeleportedOutOfTerritory.Title = obfv_m_OtherTeleportedOutOfTerritoryTitle.GetText();
				if (obfv_m_OtherTeleportedOutOfTerritoryMessage)
				{
					obfv_m_OtherTeleportedOutOfTerritoryMessage.GetText(messageText);
					config.Notifications.Other.TeleportedOutOfTerritory.Message = messageText;
				}
				if (obfv_m_OtherTeleportedOutOfTerritoryIconPath) config.Notifications.Other.TeleportedOutOfTerritory.IconPath = obfv_m_OtherTeleportedOutOfTerritoryIconPath.GetText();
			}
			else if (config.Notifications.Other.TeleportedOutOfTerritory)
			{
				config.Notifications.Other.TeleportedOutOfTerritory.Enabled = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled;
				config.Notifications.Other.TeleportedOutOfTerritory.Title = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
				config.Notifications.Other.TeleportedOutOfTerritory.Message = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
				config.Notifications.Other.TeleportedOutOfTerritory.IconPath = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
			}
			if (obfv_m_OtherBountyPausedInTerritoryEnabled && config.Notifications.Other.BountyPausedInTerritory)
			{
				config.Notifications.Other.BountyPausedInTerritory.Enabled = obfv_m_OtherBountyPausedInTerritoryEnabled.IsChecked();
				if (obfv_m_OtherBountyPausedInTerritoryTitle) config.Notifications.Other.BountyPausedInTerritory.Title = obfv_m_OtherBountyPausedInTerritoryTitle.GetText();
				if (obfv_m_OtherBountyPausedInTerritoryMessage)
				{
					obfv_m_OtherBountyPausedInTerritoryMessage.GetText(messageText);
					config.Notifications.Other.BountyPausedInTerritory.Message = messageText;
				}
				if (obfv_m_OtherBountyPausedInTerritoryIconPath) config.Notifications.Other.BountyPausedInTerritory.IconPath = obfv_m_OtherBountyPausedInTerritoryIconPath.GetText();
			}
			else if (config.Notifications.Other.BountyPausedInTerritory)
			{
				config.Notifications.Other.BountyPausedInTerritory.Enabled = sourceConfig.Notifications.Other.BountyPausedInTerritory.Enabled;
				config.Notifications.Other.BountyPausedInTerritory.Title = sourceConfig.Notifications.Other.BountyPausedInTerritory.Title;
				config.Notifications.Other.BountyPausedInTerritory.Message = sourceConfig.Notifications.Other.BountyPausedInTerritory.Message;
				config.Notifications.Other.BountyPausedInTerritory.IconPath = sourceConfig.Notifications.Other.BountyPausedInTerritory.IconPath;
			}
		}
		if (sourceConfig.Broadcasts)
		{
			if (!config.Broadcasts)
				config.Broadcasts = new obfc_BountyBroadcasts();
			if (obfv_m_BroadcastsPlacedBountyEnabled && config.Broadcasts.PlacedBounty)
			{
				config.Broadcasts.PlacedBounty.Enabled = obfv_m_BroadcastsPlacedBountyEnabled.IsChecked();
				if (obfv_m_BroadcastsPlacedBountyTitle) config.Broadcasts.PlacedBounty.Title = obfv_m_BroadcastsPlacedBountyTitle.GetText();
				if (obfv_m_BroadcastsPlacedBountyMessage)
				{
					obfv_m_BroadcastsPlacedBountyMessage.GetText(messageText);
					config.Broadcasts.PlacedBounty.Message = messageText;
				}
				if (obfv_m_BroadcastsPlacedBountyIconPath) config.Broadcasts.PlacedBounty.IconPath = obfv_m_BroadcastsPlacedBountyIconPath.GetText();
			}
			else if (config.Broadcasts.PlacedBounty)
			{
				config.Broadcasts.PlacedBounty.Enabled = sourceConfig.Broadcasts.PlacedBounty.Enabled;
				config.Broadcasts.PlacedBounty.Title = sourceConfig.Broadcasts.PlacedBounty.Title;
				config.Broadcasts.PlacedBounty.Message = sourceConfig.Broadcasts.PlacedBounty.Message;
				config.Broadcasts.PlacedBounty.IconPath = sourceConfig.Broadcasts.PlacedBounty.IconPath;
			}
			if (obfv_m_BroadcastsRuleBreakerEnabled && config.Broadcasts.RuleBreaker)
			{
				config.Broadcasts.RuleBreaker.Enabled = obfv_m_BroadcastsRuleBreakerEnabled.IsChecked();
				if (obfv_m_BroadcastsRuleBreakerTitle) config.Broadcasts.RuleBreaker.Title = obfv_m_BroadcastsRuleBreakerTitle.GetText();
				if (obfv_m_BroadcastsRuleBreakerMessage)
				{
					obfv_m_BroadcastsRuleBreakerMessage.GetText(messageText);
					config.Broadcasts.RuleBreaker.Message = messageText;
				}
				if (obfv_m_BroadcastsRuleBreakerIconPath) config.Broadcasts.RuleBreaker.IconPath = obfv_m_BroadcastsRuleBreakerIconPath.GetText();
			}
			else if (config.Broadcasts.RuleBreaker)
			{
				config.Broadcasts.RuleBreaker.Enabled = sourceConfig.Broadcasts.RuleBreaker.Enabled;
				config.Broadcasts.RuleBreaker.Title = sourceConfig.Broadcasts.RuleBreaker.Title;
				config.Broadcasts.RuleBreaker.Message = sourceConfig.Broadcasts.RuleBreaker.Message;
				config.Broadcasts.RuleBreaker.IconPath = sourceConfig.Broadcasts.RuleBreaker.IconPath;
			}
		}
		return config;
	}
	override void OnHide()
	{
		super.OnHide();
		PlayerBase player;
		player = PlayerBase.Cast(g_Game.GetPlayer());
		obfm_ForceDisableInputs(false);
		PPEffects.SetBlurMenu(0);
		g_Game.GetInput().ResetGameFocus();
		g_Game.GetUIManager().ShowUICursor(false);
		g_Game.GetMission().GetHud().Show(true);
		Close();
	}
}