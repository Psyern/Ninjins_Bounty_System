class BountyAdminMenu extends UIScriptedMenu
{
    private ButtonWidget m_BtnApplyTestRuleBreakerBounty;
    private ButtonWidget m_BtnAddBountySelectedPlayer;
    private ButtonWidget m_BtnClearBounty;
    private ButtonWidget m_BtnClearBountySelectedPlayer;
    private ButtonWidget m_BtnReloadConfigs;
    private ButtonWidget m_BtnClearAllCooldowns;
    private ButtonWidget m_BtnClearPlayerCooldown;
    private ButtonWidget m_BtnSaveAndReload;
    private ButtonWidget m_BtnAddRewardPoint;
    private ButtonWidget m_BtnRemoveRewardPoint;
    private TextListboxWidget m_PlayersList;
    private ref BountyConfig m_CachedConfig;
    private ButtonWidget m_btnNormalSettings;
    private ButtonWidget m_btnNotifications;
    private ButtonWidget m_btnBlacklist;
    private Widget m_GeneralRootPanel;
    private Widget m_NotificationsRootPanel;
    private Widget m_BlacklistRootPanel;
    private TextListboxWidget m_OnlinePlayersList;
    private TextListboxWidget m_BlacklistedPlayersList;
    private ButtonWidget m_AddToBlacklistBtn;
    private ButtonWidget m_RemoveFromBlacklistBtn;
    private ButtonWidget m_RefreshBlacklistPlayerListBtn;
    private CheckBoxWidget m_EnableBountySystem;
    private CheckBoxWidget m_DisableSelfBounty;
    private CheckBoxWidget m_TeleportOutOfOwnTerritory;
    private CheckBoxWidget m_PauseBountyInTerritory;
    private CheckBoxWidget m_TeleportOutOfSafeZone;
    private CheckBoxWidget m_EnableAutomatedBountyPlacement;
    private EditBoxWidget m_BountyCooldownSeconds;
    private EditBoxWidget m_MaxBountiedPlayers;
    private EditBoxWidget m_MinOnlinePlayersRequired;
    private EditBoxWidget m_SkipBountyTokenRequired;
    private EditBoxWidget m_PlaceBountyTokenRequired;
    private EditBoxWidget m_ResumeBountyDistanceFromTerritory;
    private EditBoxWidget m_PausedBountyResumeCheckInterval;
    private EditBoxWidget m_TeleportOutOfSafeZoneDistance;
    private EditBoxWidget m_MinimumPlayerLifetimeSeconds;
    private EditBoxWidget m_AutomatedBountyPlacementIntervalSeconds;
    private CheckBoxWidget m_EnableRuleBreakerHitThreshold;
    private CheckBoxWidget m_EnablePvEToPvPRuleBreaker;
    private CheckBoxWidget m_ClearPendingRewardsOnRuleBreakerBounty;
    private CheckBoxWidget m_AllowPvEToPvEVictimKill;
    private EditBoxWidget m_BountyRuleBreakerDurationSeconds;
    private EditBoxWidget m_RuleBreakerHitThresholdTime;
    private EditBoxWidget m_RuleBreakerHitThresholdWarningHits;
    private EditBoxWidget m_RuleBreakerHitThresholdBountyHits;
    private EditBoxWidget m_PvEToPvPInstantRuleBreakerHits;
    private CheckBoxWidget m_Expansion_EnableHardlineReputationDecrease;
    private EditBoxWidget m_Expansion_HardlineReputationDecreaseAmount;
    private EditBoxWidget m_BountyDurationSeconds;
    private CheckBoxWidget m_EnableSurvivalReward;
    private CheckBoxWidget m_PvERuleBreakerGiveRewards;
    private CheckBoxWidget m_BountyEnableMapDrawing;
    private CheckBoxWidget m_BountyCircleReduceRadiusOverTime;
    private CheckBoxWidget m_BountyCircleIncreaseRadiusOverTime;
    private EditBoxWidget m_BountyCircleRadius;
    private EditBoxWidget m_BountyCircleMinRadius;
    private EditBoxWidget m_BountyCircleColor;
    private EditBoxWidget m_BountyCircleDrawingWidth;
    private EditBoxWidget m_BountyMapUpdateIntervalSeconds;
    private EditBoxWidget m_BountyMapRequestCooldownSeconds;
    private EditBoxWidget m_BountyMapSyncIntervalSeconds;
    private EditBoxWidget m_BountyMapSyncIntervalNoBountiesSeconds;
    private EditBoxWidget m_BountyCircleOffsetMinMultiplier;
    private EditBoxWidget m_BountyCircleOffsetMaxMultiplier;
    private EditBoxWidget m_CountdownWidgetPositionX;
    private EditBoxWidget m_CountdownWidgetPositionY;
    private EditBoxWidget m_CountdownWidgetWidth;
    private EditBoxWidget m_CountdownWidgetHeight;
    private EditBoxWidget m_CountdownWidgetBackgroundColor;
    private EditBoxWidget m_CountdownWidgetTextColor;
    private CheckBoxWidget m_PlacedBountyHuntedEnabled;
    private EditBoxWidget m_PlacedBountyHuntedTitle;
    private MultilineEditBoxWidget m_PlacedBountyHuntedMessage;
    private EditBoxWidget m_PlacedBountyHuntedIconPath;
    private CheckBoxWidget m_PlacedBountyExpiredEnabled;
    private EditBoxWidget m_PlacedBountyExpiredTitle;
    private MultilineEditBoxWidget m_PlacedBountyExpiredMessage;
    private EditBoxWidget m_PlacedBountyExpiredIconPath;
    private CheckBoxWidget m_PlacedBountySurvivalRewardEnabled;
    private EditBoxWidget m_PlacedBountySurvivalRewardTitle;
    private MultilineEditBoxWidget m_PlacedBountySurvivalRewardMessage;
    private EditBoxWidget m_PlacedBountySurvivalRewardIconPath;
    private CheckBoxWidget m_PlacedBountyKilledRewardEnabled;
    private EditBoxWidget m_PlacedBountyKilledRewardTitle;
    private MultilineEditBoxWidget m_PlacedBountyKilledRewardMessage;
    private EditBoxWidget m_PlacedBountyKilledRewardIconPath;
    private CheckBoxWidget m_RuleBreakerHuntedEnabled;
    private EditBoxWidget m_RuleBreakerHuntedTitle;
    private MultilineEditBoxWidget m_RuleBreakerHuntedMessage;
    private EditBoxWidget m_RuleBreakerHuntedIconPath;
    private CheckBoxWidget m_RuleBreakerHitWarningEnabled;
    private EditBoxWidget m_RuleBreakerHitWarningTitle;
    private MultilineEditBoxWidget m_RuleBreakerHitWarningMessage;
    private EditBoxWidget m_RuleBreakerHitWarningIconPath;
    private CheckBoxWidget m_RuleBreakerExpiredEnabled;
    private EditBoxWidget m_RuleBreakerExpiredTitle;
    private MultilineEditBoxWidget m_RuleBreakerExpiredMessage;
    private EditBoxWidget m_RuleBreakerExpiredIconPath;
    private CheckBoxWidget m_RuleBreakerSurvivalRewardEnabled;
    private EditBoxWidget m_RuleBreakerSurvivalRewardTitle;
    private MultilineEditBoxWidget m_RuleBreakerSurvivalRewardMessage;
    private EditBoxWidget m_RuleBreakerSurvivalRewardIconPath;
    private CheckBoxWidget m_RuleBreakerKilledRewardEnabled;
    private EditBoxWidget m_RuleBreakerKilledRewardTitle;
    private MultilineEditBoxWidget m_RuleBreakerKilledRewardMessage;
    private EditBoxWidget m_RuleBreakerKilledRewardIconPath;
    private CheckBoxWidget m_OtherInsufficientTokensEnabled;
    private EditBoxWidget m_OtherInsufficientTokensTitle;
    private MultilineEditBoxWidget m_OtherInsufficientTokensMessage;
    private EditBoxWidget m_OtherInsufficientTokensIconPath;
    private CheckBoxWidget m_OtherSkipBountyNoPlayersEnabled;
    private EditBoxWidget m_OtherSkipBountyNoPlayersTitle;
    private MultilineEditBoxWidget m_OtherSkipBountyNoPlayersMessage;
    private EditBoxWidget m_OtherSkipBountyNoPlayersIconPath;
    private CheckBoxWidget m_OtherSkipBountySuccessEnabled;
    private EditBoxWidget m_OtherSkipBountySuccessTitle;
    private MultilineEditBoxWidget m_OtherSkipBountySuccessMessage;
    private EditBoxWidget m_OtherSkipBountySuccessIconPath;
    private CheckBoxWidget m_OtherBountySkippedEnabled;
    private EditBoxWidget m_OtherBountySkippedTitle;
    private MultilineEditBoxWidget m_OtherBountySkippedMessage;
    private EditBoxWidget m_OtherBountySkippedIconPath;
    private CheckBoxWidget m_OtherRewardHandsNotFreeEnabled;
    private EditBoxWidget m_OtherRewardHandsNotFreeTitle;
    private MultilineEditBoxWidget m_OtherRewardHandsNotFreeMessage;
    private EditBoxWidget m_OtherRewardHandsNotFreeIconPath;
    private CheckBoxWidget m_OtherPlayerOnCooldownEnabled;
    private EditBoxWidget m_OtherPlayerOnCooldownTitle;
    private MultilineEditBoxWidget m_OtherPlayerOnCooldownMessage;
    private EditBoxWidget m_OtherPlayerOnCooldownIconPath;
    private CheckBoxWidget m_OtherPlayerInSafeZoneEnabled;
    private EditBoxWidget m_OtherPlayerInSafeZoneTitle;
    private MultilineEditBoxWidget m_OtherPlayerInSafeZoneMessage;
    private EditBoxWidget m_OtherPlayerInSafeZoneIconPath;
    private CheckBoxWidget m_OtherBountyPersistedEnabled;
    private EditBoxWidget m_OtherBountyPersistedTitle;
    private MultilineEditBoxWidget m_OtherBountyPersistedMessage;
    private EditBoxWidget m_OtherBountyPersistedIconPath;
    private CheckBoxWidget m_OtherTeleportedOutOfTerritoryEnabled;
    private EditBoxWidget m_OtherTeleportedOutOfTerritoryTitle;
    private MultilineEditBoxWidget m_OtherTeleportedOutOfTerritoryMessage;
    private EditBoxWidget m_OtherTeleportedOutOfTerritoryIconPath;
    private CheckBoxWidget m_OtherBountyPausedInTerritoryEnabled;
    private EditBoxWidget m_OtherBountyPausedInTerritoryTitle;
    private MultilineEditBoxWidget m_OtherBountyPausedInTerritoryMessage;
    private EditBoxWidget m_OtherBountyPausedInTerritoryIconPath;
    private CheckBoxWidget m_BroadcastsPlacedBountyEnabled;
    private EditBoxWidget m_BroadcastsPlacedBountyTitle;
    private MultilineEditBoxWidget m_BroadcastsPlacedBountyMessage;
    private EditBoxWidget m_BroadcastsPlacedBountyIconPath;
    private CheckBoxWidget m_BroadcastsRuleBreakerEnabled;
    private EditBoxWidget m_BroadcastsRuleBreakerTitle;
    private MultilineEditBoxWidget m_BroadcastsRuleBreakerMessage;
    private EditBoxWidget m_BroadcastsRuleBreakerIconPath;
    void BountyAdminMenu()
    {
    }
    override Widget Init()
    {
        layoutRoot = g_Game.GetWorkspace().CreateWidgets("Ninjins_Bounty_System/gui/layouts/BountyAdminMenu.layout");
        if (!layoutRoot)
            return NULL;
        m_BtnApplyTestRuleBreakerBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnApplyTestRuleBreakerBounty"));
        m_BtnAddBountySelectedPlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddBountySelectedPlayer"));
        m_BtnClearBounty = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearBounty"));
        m_BtnClearBountySelectedPlayer = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearBountySelectedPlayer"));
        m_BtnReloadConfigs = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnReloadConfigs"));
        m_BtnClearAllCooldowns = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearAllCooldowns"));
        m_BtnClearPlayerCooldown = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClearPlayerCooldown"));
        m_BtnSaveAndReload = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BTNSaveAndReload"));
        m_BtnAddRewardPoint = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnAddRewardPoint"));
        m_BtnRemoveRewardPoint = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnRemoveRewardPoint"));
        m_PlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("PlayersList"));
        m_btnNormalSettings = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnNormalSettings"));
        m_btnNotifications = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnNotifications"));
        m_btnBlacklist = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnBlacklist"));
        m_GeneralRootPanel = layoutRoot.FindAnyWidget("GeneralRootPanel");
        m_NotificationsRootPanel = layoutRoot.FindAnyWidget("NotificationsSettingsPanel");
        m_BlacklistRootPanel = layoutRoot.FindAnyWidget("BlacklistSettingsPanel");
        m_OnlinePlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxWidgetOnlinePlayers"));
        m_BlacklistedPlayersList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("TextListboxWidgetBlacklistedPlayers"));
        m_AddToBlacklistBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("AddToBlacklistBTN"));
        m_RemoveFromBlacklistBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RemoveFromBlacklistBTN"));
        m_RefreshBlacklistPlayerListBtn = ButtonWidget.Cast(layoutRoot.FindAnyWidget("RefreshBlacklistPlayerListBTN"));
        m_EnableBountySystem = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableBountySystem"));
        m_DisableSelfBounty = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("DisableSelfBounty"));
        m_TeleportOutOfOwnTerritory = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfOwnTerritory"));
        m_PauseBountyInTerritory = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PauseBountyInTerritory"));
        m_TeleportOutOfSafeZone = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfSafeZone"));
        m_EnableAutomatedBountyPlacement = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableAutomatedBountyPlacement"));
        m_BountyCooldownSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCooldownSeconds"));
        m_MaxBountiedPlayers = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MaxBountiedPlayers"));
        m_MinOnlinePlayersRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinOnlinePlayersRequired"));
        m_SkipBountyTokenRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("SkipBountyTokenRequired"));
        m_PlaceBountyTokenRequired = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlaceBountyTokenRequired"));
        m_ResumeBountyDistanceFromTerritory = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("ResumeBountyDistanceFromTerritory"));
        m_PausedBountyResumeCheckInterval = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PausedBountyResumeCheckInterval"));
        m_TeleportOutOfSafeZoneDistance = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("TeleportOutOfSafeZoneDistance"));
        m_MinimumPlayerLifetimeSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("MinimumPlayerLifetimeSeconds"));
        m_AutomatedBountyPlacementIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("AutomatedBountyPlacementIntervalSeconds"));
        m_EnableRuleBreakerHitThreshold = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableRuleBreakerHitThreshold"));
        m_EnablePvEToPvPRuleBreaker = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnablePvEToPvPRuleBreaker"));
        m_ClearPendingRewardsOnRuleBreakerBounty = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("ClearPendingRewardsOnRuleBreakerBounty"));
        m_AllowPvEToPvEVictimKill = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("AllowPvEToPvEVictimKill"));
        m_BountyRuleBreakerDurationSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyRuleBreakerDurationSeconds"));
        m_RuleBreakerHitThresholdTime = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdTime"));
        m_RuleBreakerHitThresholdWarningHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdWarningHits"));
        m_RuleBreakerHitThresholdBountyHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitThresholdBountyHits"));
        m_PvEToPvPInstantRuleBreakerHits = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PvEToPvPInstantRuleBreakerHits"));
        m_Expansion_EnableHardlineReputationDecrease = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("Expansion_EnableHardlineReputationDecrease"));
        m_Expansion_HardlineReputationDecreaseAmount = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("Expansion_HardlineReputationDecreaseAmount"));
        m_BountyDurationSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyDurationSeconds"));
        m_EnableSurvivalReward = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("EnableSurvivalReward"));
        m_PvERuleBreakerGiveRewards = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PvERuleBreakerGiveRewards"));
        m_BountyEnableMapDrawing = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyEnableMapDrawing"));
        m_BountyCircleReduceRadiusOverTime = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleReduceRadiusOverTime"));
        m_BountyCircleIncreaseRadiusOverTime = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleIncreaseRadiusOverTime"));
        m_BountyCircleRadius = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleRadius"));
        m_BountyCircleMinRadius = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleMinRadius"));
        m_BountyCircleColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleColor"));
        m_BountyCircleDrawingWidth = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleDrawingWidth"));
        m_BountyMapUpdateIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapUpdateIntervalSeconds"));
        m_BountyMapRequestCooldownSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapRequestCooldownSeconds"));
        m_BountyMapSyncIntervalSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapSyncIntervalSeconds"));
        m_BountyMapSyncIntervalNoBountiesSeconds = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyMapSyncIntervalNoBountiesSeconds"));
        m_BountyCircleOffsetMinMultiplier = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleOffsetMinMultiplier"));
        m_BountyCircleOffsetMaxMultiplier = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BountyCircleOffsetMaxMultiplier"));
        m_CountdownWidgetPositionX = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetPositionX"));
        m_CountdownWidgetPositionY = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetPositionY"));
        m_CountdownWidgetWidth = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetWidth"));
        m_CountdownWidgetHeight = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetHeight"));
        m_CountdownWidgetBackgroundColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetBackgroundColor"));
        m_CountdownWidgetTextColor = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("CountdownWidgetTextColor"));
        m_PlacedBountyHuntedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedEnabled0"));
        m_PlacedBountyHuntedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedTitle0"));
        m_PlacedBountyHuntedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedMessage0"));
        m_PlacedBountyHuntedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyHuntedIconPath0"));
        m_PlacedBountyExpiredEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredEnabled0"));
        m_PlacedBountyExpiredTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredTitle0"));
        m_PlacedBountyExpiredMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredMessage0"));
        m_PlacedBountyExpiredIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyExpiredIconPath0"));
        m_PlacedBountySurvivalRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardEnabled0"));
        m_PlacedBountySurvivalRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardTitle0"));
        m_PlacedBountySurvivalRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardMessage0"));
        m_PlacedBountySurvivalRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountySurvivalRewardIconPath0"));
        m_PlacedBountyKilledRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardEnabled0"));
        m_PlacedBountyKilledRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardTitle0"));
        m_PlacedBountyKilledRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardMessage0"));
        m_PlacedBountyKilledRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("PlacedBountyKilledRewardIconPath0"));
        m_RuleBreakerHuntedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedEnabled0"));
        m_RuleBreakerHuntedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedTitle0"));
        m_RuleBreakerHuntedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedMessage0"));
        m_RuleBreakerHuntedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHuntedIconPath0"));
        m_RuleBreakerHitWarningEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningEnabled0"));
        m_RuleBreakerHitWarningTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningTitle0"));
        m_RuleBreakerHitWarningMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningMessage0"));
        m_RuleBreakerHitWarningIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerHitWarningIconPath0"));
        m_RuleBreakerExpiredEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredEnabled0"));
        m_RuleBreakerExpiredTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredTitle0"));
        m_RuleBreakerExpiredMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredMessage0"));
        m_RuleBreakerExpiredIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerExpiredIconPath0"));
        m_RuleBreakerSurvivalRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardEnabled0"));
        m_RuleBreakerSurvivalRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardTitle0"));
        m_RuleBreakerSurvivalRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardMessage0"));
        m_RuleBreakerSurvivalRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerSurvivalRewardIconPath0"));
        m_RuleBreakerKilledRewardEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardEnabled0"));
        m_RuleBreakerKilledRewardTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardTitle0"));
        m_RuleBreakerKilledRewardMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardMessage0"));
        m_RuleBreakerKilledRewardIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("RuleBreakerKilledRewardIconPath0"));
        m_OtherInsufficientTokensEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensEnabled0"));
        m_OtherInsufficientTokensTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensTitle0"));
        m_OtherInsufficientTokensMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensMessage0"));
        m_OtherInsufficientTokensIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherInsufficientTokensIconPath0"));
        m_OtherSkipBountyNoPlayersEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersEnabled0"));
        m_OtherSkipBountyNoPlayersTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersTitle0"));
        m_OtherSkipBountyNoPlayersMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersMessage0"));
        m_OtherSkipBountyNoPlayersIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountyNoPlayersIconPath0"));
        m_OtherSkipBountySuccessEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessEnabled0"));
        m_OtherSkipBountySuccessTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessTitle0"));
        m_OtherSkipBountySuccessMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessMessage0"));
        m_OtherSkipBountySuccessIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherSkipBountySuccessIconPath0"));
        m_OtherBountySkippedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedEnabled0"));
        m_OtherBountySkippedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedTitle0"));
        m_OtherBountySkippedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedMessage0"));
        m_OtherBountySkippedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountySkippedIconPath0"));
        m_OtherRewardHandsNotFreeEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeEnabled0"));
        m_OtherRewardHandsNotFreeTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeTitle0"));
        m_OtherRewardHandsNotFreeMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeMessage0"));
        m_OtherRewardHandsNotFreeIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherRewardHandsNotFreeIconPath0"));
        m_OtherPlayerOnCooldownEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownEnabled0"));
        m_OtherPlayerOnCooldownTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownTitle0"));
        m_OtherPlayerOnCooldownMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownMessage0"));
        m_OtherPlayerOnCooldownIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerOnCooldownIconPath0"));
        m_OtherPlayerInSafeZoneEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneEnabled0"));
        m_OtherPlayerInSafeZoneTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneTitle0"));
        m_OtherPlayerInSafeZoneMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneMessage0"));
        m_OtherPlayerInSafeZoneIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherPlayerInSafeZoneIconPath0"));
        m_OtherBountyPersistedEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedEnabled0"));
        m_OtherBountyPersistedTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedTitle0"));
        m_OtherBountyPersistedMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedMessage0"));
        m_OtherBountyPersistedIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPersistedIconPath0"));
        m_OtherTeleportedOutOfTerritoryEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryEnabled0"));
        m_OtherTeleportedOutOfTerritoryTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryTitle0"));
        m_OtherTeleportedOutOfTerritoryMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryMessage0"));
        m_OtherTeleportedOutOfTerritoryIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherTeleportedOutOfTerritoryIconPath0"));
        m_OtherBountyPausedInTerritoryEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryEnabled0"));
        m_OtherBountyPausedInTerritoryTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryTitle0"));
        m_OtherBountyPausedInTerritoryMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryMessage0"));
        m_OtherBountyPausedInTerritoryIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("OtherBountyPausedInTerritoryIconPath0"));
        m_BroadcastsPlacedBountyEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyEnabled0"));
        m_BroadcastsPlacedBountyTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyTitle0"));
        m_BroadcastsPlacedBountyMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyMessage0"));
        m_BroadcastsPlacedBountyIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsPlacedBountyIconPath0"));
        m_BroadcastsRuleBreakerEnabled = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerEnabled0"));
        m_BroadcastsRuleBreakerTitle = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerTitle0"));
        m_BroadcastsRuleBreakerMessage = MultilineEditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerMessage0"));
        m_BroadcastsRuleBreakerIconPath = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("BroadcastsRuleBreakerIconPath0"));
        if (!m_PlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] PlayersList widget not found in layout!");
        }
        return layoutRoot;
    }
    private void ShowOnlyPanel(Widget panelToShow)
    {
        if (m_GeneralRootPanel)
            m_GeneralRootPanel.Show(false);
        if (m_NotificationsRootPanel)
            m_NotificationsRootPanel.Show(false);
        if (m_BlacklistRootPanel)
            m_BlacklistRootPanel.Show(false);
        if (panelToShow)
            panelToShow.Show(true);
        if (m_btnNormalSettings)
        {
            if (panelToShow == m_GeneralRootPanel)
                m_btnNormalSettings.SetColor(ARGB(255, 27, 89, 95)); 
            else
                m_btnNormalSettings.SetColor(ARGB(241, 30, 40, 56)); 
        }
        if (m_btnNotifications)
        {
            if (panelToShow == m_NotificationsRootPanel)
                m_btnNotifications.SetColor(ARGB(255, 27, 89, 95)); 
            else
                m_btnNotifications.SetColor(ARGB(241, 30, 40, 56)); 
        }
        if (m_btnBlacklist)
        {
            if (panelToShow == m_BlacklistRootPanel)
                m_btnBlacklist.SetColor(ARGB(255, 27, 89, 95)); 
            else
                m_btnBlacklist.SetColor(ARGB(241, 30, 40, 56)); 
        }
        if (panelToShow == m_BlacklistRootPanel)
        {
            RefreshBlacklistLists();
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
        ForceDisableInputs(true, skip);
        SetFocus(layoutRoot);
        ShowOnlyPanel(m_GeneralRootPanel);
        if (player && player.GetIdentity())
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestConfig", new Param1<int>(0), true, player.GetIdentity());
        }
        RefreshPlayersList();
    }
    void UpdateConfigFromServer(BountyConfig config)
    {
        m_CachedConfig = config;
        PopulateConfigValues();
    }
    void PopulateConfigValues()
    {
        BountyConfig config;
        config = m_CachedConfig;
        if (!config)
            return;
        if (m_EnableBountySystem && config.Core)
            m_EnableBountySystem.SetChecked(config.Core.EnableBountySystem);
        if (m_DisableSelfBounty && config.Core)
            m_DisableSelfBounty.SetChecked(config.Core.DisableSelfBounty);
        if (m_TeleportOutOfOwnTerritory && config.Core)
            m_TeleportOutOfOwnTerritory.SetChecked(config.Core.TeleportOutOfOwnTerritory);
        if (m_PauseBountyInTerritory && config.Core)
            m_PauseBountyInTerritory.SetChecked(config.Core.PauseBountyInTerritory);
        if (m_TeleportOutOfSafeZone && config.Core)
            m_TeleportOutOfSafeZone.SetChecked(config.Core.TeleportOutOfSafeZone);
        if (m_EnableAutomatedBountyPlacement && config.Core)
            m_EnableAutomatedBountyPlacement.SetChecked(config.Core.EnableAutomatedBountyPlacement);
        if (m_BountyCooldownSeconds && config.Core)
            m_BountyCooldownSeconds.SetText(config.Core.BountyCooldownSeconds.ToString());
        if (m_MaxBountiedPlayers && config.Core)
            m_MaxBountiedPlayers.SetText(config.Core.MaxBountiedPlayers.ToString());
        if (m_MinOnlinePlayersRequired && config.Core)
            m_MinOnlinePlayersRequired.SetText(config.Core.MinOnlinePlayersRequired.ToString());
        if (m_SkipBountyTokenRequired && config.Core)
            m_SkipBountyTokenRequired.SetText(config.Core.SkipBountyTokenRequired.ToString());
        if (m_PlaceBountyTokenRequired && config.Core)
            m_PlaceBountyTokenRequired.SetText(config.Core.PlaceBountyTokenRequired.ToString());
        if (m_ResumeBountyDistanceFromTerritory && config.Core)
            m_ResumeBountyDistanceFromTerritory.SetText(config.Core.ResumeBountyDistanceFromTerritory.ToString());
        if (m_PausedBountyResumeCheckInterval && config.Core)
            m_PausedBountyResumeCheckInterval.SetText(config.Core.PausedBountyResumeCheckInterval.ToString());
        if (m_TeleportOutOfSafeZoneDistance && config.Core)
            m_TeleportOutOfSafeZoneDistance.SetText(config.Core.TeleportOutOfSafeZoneDistance.ToString());
        if (m_MinimumPlayerLifetimeSeconds && config.Core)
            m_MinimumPlayerLifetimeSeconds.SetText(config.Core.MinimumPlayerLifetimeSeconds.ToString());
        if (m_AutomatedBountyPlacementIntervalSeconds && config.Core)
            m_AutomatedBountyPlacementIntervalSeconds.SetText(config.Core.AutomatedBountyPlacementIntervalSeconds.ToString());
        if (m_EnableRuleBreakerHitThreshold && config.RuleBreaker)
            m_EnableRuleBreakerHitThreshold.SetChecked(config.RuleBreaker.EnableRuleBreakerHitThreshold);
        if (m_EnablePvEToPvPRuleBreaker && config.RuleBreaker)
            m_EnablePvEToPvPRuleBreaker.SetChecked(config.RuleBreaker.EnablePvEToPvPRuleBreaker);
        if (m_ClearPendingRewardsOnRuleBreakerBounty && config.RuleBreaker)
            m_ClearPendingRewardsOnRuleBreakerBounty.SetChecked(config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty);
        if (m_AllowPvEToPvEVictimKill && config.RuleBreaker)
            m_AllowPvEToPvEVictimKill.SetChecked(config.RuleBreaker.AllowPvEToPvEVictimKill);
        if (m_BountyRuleBreakerDurationSeconds && config.RuleBreaker)
            m_BountyRuleBreakerDurationSeconds.SetText(config.RuleBreaker.BountyRuleBreakerDurationSeconds.ToString());
        if (m_RuleBreakerHitThresholdTime && config.RuleBreaker)
            m_RuleBreakerHitThresholdTime.SetText(config.RuleBreaker.RuleBreakerHitThresholdTime.ToString());
        if (m_RuleBreakerHitThresholdWarningHits && config.RuleBreaker)
            m_RuleBreakerHitThresholdWarningHits.SetText(config.RuleBreaker.RuleBreakerHitThresholdWarningHits.ToString());
        if (m_RuleBreakerHitThresholdBountyHits && config.RuleBreaker)
            m_RuleBreakerHitThresholdBountyHits.SetText(config.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString());
        if (m_PvEToPvPInstantRuleBreakerHits && config.RuleBreaker)
            m_PvEToPvPInstantRuleBreakerHits.SetText(config.RuleBreaker.PvEToPvPInstantRuleBreakerHits.ToString());
        if (m_Expansion_EnableHardlineReputationDecrease && config.RuleBreaker)
            m_Expansion_EnableHardlineReputationDecrease.SetChecked(config.RuleBreaker.Expansion_EnableHardlineReputationDecrease);
        if (m_Expansion_HardlineReputationDecreaseAmount && config.RuleBreaker)
            m_Expansion_HardlineReputationDecreaseAmount.SetText(config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString());
        if (m_BountyDurationSeconds && config.PlacedBounty)
            m_BountyDurationSeconds.SetText(config.PlacedBounty.BountyDurationSeconds.ToString());
        if (m_EnableSurvivalReward && config.Reward)
            m_EnableSurvivalReward.SetChecked(config.Reward.EnableSurvivalReward);
        if (m_PvERuleBreakerGiveRewards && config.Reward)
            m_PvERuleBreakerGiveRewards.SetChecked(config.Reward.PvERuleBreakerGiveRewards);
        if (m_BountyEnableMapDrawing && config.Map)
            m_BountyEnableMapDrawing.SetChecked(config.Map.BountyEnableMapDrawing);
        if (m_BountyCircleReduceRadiusOverTime && config.Map)
            m_BountyCircleReduceRadiusOverTime.SetChecked(config.Map.BountyCircleReduceRadiusOverTime);
        if (m_BountyCircleIncreaseRadiusOverTime && config.Map)
            m_BountyCircleIncreaseRadiusOverTime.SetChecked(config.Map.BountyCircleIncreaseRadiusOverTime);
        if (m_BountyCircleRadius && config.Map)
            m_BountyCircleRadius.SetText(config.Map.BountyCircleRadius.ToString());
        if (m_BountyCircleMinRadius && config.Map)
            m_BountyCircleMinRadius.SetText(config.Map.BountyCircleMinRadius.ToString());
        if (m_BountyCircleColor && config.Map)
            m_BountyCircleColor.SetText(config.Map.BountyCircleColor.ToString());
        if (m_BountyCircleDrawingWidth && config.Map)
            m_BountyCircleDrawingWidth.SetText(config.Map.BountyCircleDrawingWidth.ToString());
        if (m_BountyMapUpdateIntervalSeconds && config.Map)
            m_BountyMapUpdateIntervalSeconds.SetText(config.Map.BountyMapUpdateIntervalSeconds.ToString());
        if (m_BountyMapRequestCooldownSeconds && config.Map)
            m_BountyMapRequestCooldownSeconds.SetText(config.Map.BountyMapRequestCooldownSeconds.ToString());
        if (m_BountyMapSyncIntervalSeconds && config.Map)
            m_BountyMapSyncIntervalSeconds.SetText(config.Map.BountyMapSyncIntervalSeconds.ToString());
        if (m_BountyMapSyncIntervalNoBountiesSeconds && config.Map)
            m_BountyMapSyncIntervalNoBountiesSeconds.SetText(config.Map.BountyMapSyncIntervalNoBountiesSeconds.ToString());
        if (m_BountyCircleOffsetMinMultiplier && config.Map)
            m_BountyCircleOffsetMinMultiplier.SetText(config.Map.BountyCircleOffsetMinMultiplier.ToString());
        if (m_BountyCircleOffsetMaxMultiplier && config.Map)
            m_BountyCircleOffsetMaxMultiplier.SetText(config.Map.BountyCircleOffsetMaxMultiplier.ToString());
        if (m_CountdownWidgetPositionX && config.UI)
            m_CountdownWidgetPositionX.SetText(config.UI.CountdownWidgetPositionX.ToString());
        if (m_CountdownWidgetPositionY && config.UI)
            m_CountdownWidgetPositionY.SetText(config.UI.CountdownWidgetPositionY.ToString());
        if (m_CountdownWidgetWidth && config.UI)
            m_CountdownWidgetWidth.SetText(config.UI.CountdownWidgetWidth.ToString());
        if (m_CountdownWidgetHeight && config.UI)
            m_CountdownWidgetHeight.SetText(config.UI.CountdownWidgetHeight.ToString());
        if (m_CountdownWidgetBackgroundColor && config.UI)
            m_CountdownWidgetBackgroundColor.SetText(config.UI.CountdownWidgetBackgroundColor.ToString());
        if (m_CountdownWidgetTextColor && config.UI)
            m_CountdownWidgetTextColor.SetText(config.UI.CountdownWidgetTextColor.ToString());
        if (config.Notifications && config.Notifications.PlacedBounty)
        {
            if (m_PlacedBountyHuntedEnabled && config.Notifications.PlacedBounty.Hunted)
            {
                m_PlacedBountyHuntedEnabled.SetChecked(config.Notifications.PlacedBounty.Hunted.Enabled);
                if (m_PlacedBountyHuntedTitle) m_PlacedBountyHuntedTitle.SetText(config.Notifications.PlacedBounty.Hunted.Title);
                if (m_PlacedBountyHuntedMessage) m_PlacedBountyHuntedMessage.SetText(config.Notifications.PlacedBounty.Hunted.Message);
                if (m_PlacedBountyHuntedIconPath) m_PlacedBountyHuntedIconPath.SetText(config.Notifications.PlacedBounty.Hunted.IconPath);
            }
            if (m_PlacedBountyExpiredEnabled && config.Notifications.PlacedBounty.Expired)
            {
                m_PlacedBountyExpiredEnabled.SetChecked(config.Notifications.PlacedBounty.Expired.Enabled);
                if (m_PlacedBountyExpiredTitle) m_PlacedBountyExpiredTitle.SetText(config.Notifications.PlacedBounty.Expired.Title);
                if (m_PlacedBountyExpiredMessage) m_PlacedBountyExpiredMessage.SetText(config.Notifications.PlacedBounty.Expired.Message);
                if (m_PlacedBountyExpiredIconPath) m_PlacedBountyExpiredIconPath.SetText(config.Notifications.PlacedBounty.Expired.IconPath);
            }
            if (m_PlacedBountySurvivalRewardEnabled && config.Notifications.PlacedBounty.SurvivalReward)
            {
                m_PlacedBountySurvivalRewardEnabled.SetChecked(config.Notifications.PlacedBounty.SurvivalReward.Enabled);
                if (m_PlacedBountySurvivalRewardTitle) m_PlacedBountySurvivalRewardTitle.SetText(config.Notifications.PlacedBounty.SurvivalReward.Title);
                if (m_PlacedBountySurvivalRewardMessage) m_PlacedBountySurvivalRewardMessage.SetText(config.Notifications.PlacedBounty.SurvivalReward.Message);
                if (m_PlacedBountySurvivalRewardIconPath) m_PlacedBountySurvivalRewardIconPath.SetText(config.Notifications.PlacedBounty.SurvivalReward.IconPath);
            }
            if (m_PlacedBountyKilledRewardEnabled && config.Notifications.PlacedBounty.KilledReward)
            {
                m_PlacedBountyKilledRewardEnabled.SetChecked(config.Notifications.PlacedBounty.KilledReward.Enabled);
                if (m_PlacedBountyKilledRewardTitle) m_PlacedBountyKilledRewardTitle.SetText(config.Notifications.PlacedBounty.KilledReward.Title);
                if (m_PlacedBountyKilledRewardMessage) m_PlacedBountyKilledRewardMessage.SetText(config.Notifications.PlacedBounty.KilledReward.Message);
                if (m_PlacedBountyKilledRewardIconPath) m_PlacedBountyKilledRewardIconPath.SetText(config.Notifications.PlacedBounty.KilledReward.IconPath);
            }
        }
        if (config.Notifications && config.Notifications.RuleBreaker)
        {
            if (m_RuleBreakerHuntedEnabled && config.Notifications.RuleBreaker.Hunted)
            {
                m_RuleBreakerHuntedEnabled.SetChecked(config.Notifications.RuleBreaker.Hunted.Enabled);
                if (m_RuleBreakerHuntedTitle) m_RuleBreakerHuntedTitle.SetText(config.Notifications.RuleBreaker.Hunted.Title);
                if (m_RuleBreakerHuntedMessage) m_RuleBreakerHuntedMessage.SetText(config.Notifications.RuleBreaker.Hunted.Message);
                if (m_RuleBreakerHuntedIconPath) m_RuleBreakerHuntedIconPath.SetText(config.Notifications.RuleBreaker.Hunted.IconPath);
            }
            if (m_RuleBreakerHitWarningEnabled && config.Notifications.RuleBreaker.HitWarning)
            {
                m_RuleBreakerHitWarningEnabled.SetChecked(config.Notifications.RuleBreaker.HitWarning.Enabled);
                if (m_RuleBreakerHitWarningTitle) m_RuleBreakerHitWarningTitle.SetText(config.Notifications.RuleBreaker.HitWarning.Title);
                if (m_RuleBreakerHitWarningMessage) m_RuleBreakerHitWarningMessage.SetText(config.Notifications.RuleBreaker.HitWarning.Message);
                if (m_RuleBreakerHitWarningIconPath) m_RuleBreakerHitWarningIconPath.SetText(config.Notifications.RuleBreaker.HitWarning.IconPath);
            }
            if (m_RuleBreakerExpiredEnabled && config.Notifications.RuleBreaker.Expired)
            {
                m_RuleBreakerExpiredEnabled.SetChecked(config.Notifications.RuleBreaker.Expired.Enabled);
                if (m_RuleBreakerExpiredTitle) m_RuleBreakerExpiredTitle.SetText(config.Notifications.RuleBreaker.Expired.Title);
                if (m_RuleBreakerExpiredMessage) m_RuleBreakerExpiredMessage.SetText(config.Notifications.RuleBreaker.Expired.Message);
                if (m_RuleBreakerExpiredIconPath) m_RuleBreakerExpiredIconPath.SetText(config.Notifications.RuleBreaker.Expired.IconPath);
            }
            if (m_RuleBreakerSurvivalRewardEnabled && config.Notifications.RuleBreaker.SurvivalReward)
            {
                m_RuleBreakerSurvivalRewardEnabled.SetChecked(config.Notifications.RuleBreaker.SurvivalReward.Enabled);
                if (m_RuleBreakerSurvivalRewardTitle) m_RuleBreakerSurvivalRewardTitle.SetText(config.Notifications.RuleBreaker.SurvivalReward.Title);
                if (m_RuleBreakerSurvivalRewardMessage) m_RuleBreakerSurvivalRewardMessage.SetText(config.Notifications.RuleBreaker.SurvivalReward.Message);
                if (m_RuleBreakerSurvivalRewardIconPath) m_RuleBreakerSurvivalRewardIconPath.SetText(config.Notifications.RuleBreaker.SurvivalReward.IconPath);
            }
            if (m_RuleBreakerKilledRewardEnabled && config.Notifications.RuleBreaker.KilledReward)
            {
                m_RuleBreakerKilledRewardEnabled.SetChecked(config.Notifications.RuleBreaker.KilledReward.Enabled);
                if (m_RuleBreakerKilledRewardTitle) m_RuleBreakerKilledRewardTitle.SetText(config.Notifications.RuleBreaker.KilledReward.Title);
                if (m_RuleBreakerKilledRewardMessage) m_RuleBreakerKilledRewardMessage.SetText(config.Notifications.RuleBreaker.KilledReward.Message);
                if (m_RuleBreakerKilledRewardIconPath) m_RuleBreakerKilledRewardIconPath.SetText(config.Notifications.RuleBreaker.KilledReward.IconPath);
            }
        }
        if (config.Notifications && config.Notifications.Other)
        {
            if (m_OtherInsufficientTokensEnabled && config.Notifications.Other.InsufficientTokens)
            {
                m_OtherInsufficientTokensEnabled.SetChecked(config.Notifications.Other.InsufficientTokens.Enabled);
                if (m_OtherInsufficientTokensTitle) m_OtherInsufficientTokensTitle.SetText(config.Notifications.Other.InsufficientTokens.Title);
                if (m_OtherInsufficientTokensMessage) m_OtherInsufficientTokensMessage.SetText(config.Notifications.Other.InsufficientTokens.Message);
                if (m_OtherInsufficientTokensIconPath) m_OtherInsufficientTokensIconPath.SetText(config.Notifications.Other.InsufficientTokens.IconPath);
            }
            if (m_OtherSkipBountyNoPlayersEnabled && config.Notifications.Other.SkipBountyNoPlayers)
            {
                m_OtherSkipBountyNoPlayersEnabled.SetChecked(config.Notifications.Other.SkipBountyNoPlayers.Enabled);
                if (m_OtherSkipBountyNoPlayersTitle) m_OtherSkipBountyNoPlayersTitle.SetText(config.Notifications.Other.SkipBountyNoPlayers.Title);
                if (m_OtherSkipBountyNoPlayersMessage) m_OtherSkipBountyNoPlayersMessage.SetText(config.Notifications.Other.SkipBountyNoPlayers.Message);
                if (m_OtherSkipBountyNoPlayersIconPath) m_OtherSkipBountyNoPlayersIconPath.SetText(config.Notifications.Other.SkipBountyNoPlayers.IconPath);
            }
            if (m_OtherSkipBountySuccessEnabled && config.Notifications.Other.SkipBountySuccess)
            {
                m_OtherSkipBountySuccessEnabled.SetChecked(config.Notifications.Other.SkipBountySuccess.Enabled);
                if (m_OtherSkipBountySuccessTitle) m_OtherSkipBountySuccessTitle.SetText(config.Notifications.Other.SkipBountySuccess.Title);
                if (m_OtherSkipBountySuccessMessage) m_OtherSkipBountySuccessMessage.SetText(config.Notifications.Other.SkipBountySuccess.Message);
                if (m_OtherSkipBountySuccessIconPath) m_OtherSkipBountySuccessIconPath.SetText(config.Notifications.Other.SkipBountySuccess.IconPath);
            }
            if (m_OtherBountySkippedEnabled && config.Notifications.Other.BountySkipped)
            {
                m_OtherBountySkippedEnabled.SetChecked(config.Notifications.Other.BountySkipped.Enabled);
                if (m_OtherBountySkippedTitle) m_OtherBountySkippedTitle.SetText(config.Notifications.Other.BountySkipped.Title);
                if (m_OtherBountySkippedMessage) m_OtherBountySkippedMessage.SetText(config.Notifications.Other.BountySkipped.Message);
                if (m_OtherBountySkippedIconPath) m_OtherBountySkippedIconPath.SetText(config.Notifications.Other.BountySkipped.IconPath);
            }
            if (m_OtherRewardHandsNotFreeEnabled && config.Notifications.Other.RewardHandsNotFree)
            {
                m_OtherRewardHandsNotFreeEnabled.SetChecked(config.Notifications.Other.RewardHandsNotFree.Enabled);
                if (m_OtherRewardHandsNotFreeTitle) m_OtherRewardHandsNotFreeTitle.SetText(config.Notifications.Other.RewardHandsNotFree.Title);
                if (m_OtherRewardHandsNotFreeMessage) m_OtherRewardHandsNotFreeMessage.SetText(config.Notifications.Other.RewardHandsNotFree.Message);
                if (m_OtherRewardHandsNotFreeIconPath) m_OtherRewardHandsNotFreeIconPath.SetText(config.Notifications.Other.RewardHandsNotFree.IconPath);
            }
            if (m_OtherPlayerOnCooldownEnabled && config.Notifications.Other.PlayerOnCooldown)
            {
                m_OtherPlayerOnCooldownEnabled.SetChecked(config.Notifications.Other.PlayerOnCooldown.Enabled);
                if (m_OtherPlayerOnCooldownTitle) m_OtherPlayerOnCooldownTitle.SetText(config.Notifications.Other.PlayerOnCooldown.Title);
                if (m_OtherPlayerOnCooldownMessage) m_OtherPlayerOnCooldownMessage.SetText(config.Notifications.Other.PlayerOnCooldown.Message);
                if (m_OtherPlayerOnCooldownIconPath) m_OtherPlayerOnCooldownIconPath.SetText(config.Notifications.Other.PlayerOnCooldown.IconPath);
            }
            if (m_OtherPlayerInSafeZoneEnabled && config.Notifications.Other.PlayerInSafeZone)
            {
                m_OtherPlayerInSafeZoneEnabled.SetChecked(config.Notifications.Other.PlayerInSafeZone.Enabled);
                if (m_OtherPlayerInSafeZoneTitle) m_OtherPlayerInSafeZoneTitle.SetText(config.Notifications.Other.PlayerInSafeZone.Title);
                if (m_OtherPlayerInSafeZoneMessage) m_OtherPlayerInSafeZoneMessage.SetText(config.Notifications.Other.PlayerInSafeZone.Message);
                if (m_OtherPlayerInSafeZoneIconPath) m_OtherPlayerInSafeZoneIconPath.SetText(config.Notifications.Other.PlayerInSafeZone.IconPath);
            }
            if (m_OtherBountyPersistedEnabled && config.Notifications.Other.BountyPersisted)
            {
                m_OtherBountyPersistedEnabled.SetChecked(config.Notifications.Other.BountyPersisted.Enabled);
                if (m_OtherBountyPersistedTitle) m_OtherBountyPersistedTitle.SetText(config.Notifications.Other.BountyPersisted.Title);
                if (m_OtherBountyPersistedMessage) m_OtherBountyPersistedMessage.SetText(config.Notifications.Other.BountyPersisted.Message);
                if (m_OtherBountyPersistedIconPath) m_OtherBountyPersistedIconPath.SetText(config.Notifications.Other.BountyPersisted.IconPath);
            }
            if (m_OtherTeleportedOutOfTerritoryEnabled && config.Notifications.Other.TeleportedOutOfTerritory)
            {
                m_OtherTeleportedOutOfTerritoryEnabled.SetChecked(config.Notifications.Other.TeleportedOutOfTerritory.Enabled);
                if (m_OtherTeleportedOutOfTerritoryTitle) m_OtherTeleportedOutOfTerritoryTitle.SetText(config.Notifications.Other.TeleportedOutOfTerritory.Title);
                if (m_OtherTeleportedOutOfTerritoryMessage) m_OtherTeleportedOutOfTerritoryMessage.SetText(config.Notifications.Other.TeleportedOutOfTerritory.Message);
                if (m_OtherTeleportedOutOfTerritoryIconPath) m_OtherTeleportedOutOfTerritoryIconPath.SetText(config.Notifications.Other.TeleportedOutOfTerritory.IconPath);
            }
            if (m_OtherBountyPausedInTerritoryEnabled && config.Notifications.Other.BountyPausedInTerritory)
            {
                m_OtherBountyPausedInTerritoryEnabled.SetChecked(config.Notifications.Other.BountyPausedInTerritory.Enabled);
                if (m_OtherBountyPausedInTerritoryTitle) m_OtherBountyPausedInTerritoryTitle.SetText(config.Notifications.Other.BountyPausedInTerritory.Title);
                if (m_OtherBountyPausedInTerritoryMessage) m_OtherBountyPausedInTerritoryMessage.SetText(config.Notifications.Other.BountyPausedInTerritory.Message);
                if (m_OtherBountyPausedInTerritoryIconPath) m_OtherBountyPausedInTerritoryIconPath.SetText(config.Notifications.Other.BountyPausedInTerritory.IconPath);
            }
        }
        if (config.Broadcasts)
        {
            if (m_BroadcastsPlacedBountyEnabled && config.Broadcasts.PlacedBounty)
            {
                m_BroadcastsPlacedBountyEnabled.SetChecked(config.Broadcasts.PlacedBounty.Enabled);
                if (m_BroadcastsPlacedBountyTitle) m_BroadcastsPlacedBountyTitle.SetText(config.Broadcasts.PlacedBounty.Title);
                if (m_BroadcastsPlacedBountyMessage) m_BroadcastsPlacedBountyMessage.SetText(config.Broadcasts.PlacedBounty.Message);
                if (m_BroadcastsPlacedBountyIconPath) m_BroadcastsPlacedBountyIconPath.SetText(config.Broadcasts.PlacedBounty.IconPath);
            }
            if (m_BroadcastsRuleBreakerEnabled && config.Broadcasts.RuleBreaker)
            {
                m_BroadcastsRuleBreakerEnabled.SetChecked(config.Broadcasts.RuleBreaker.Enabled);
                if (m_BroadcastsRuleBreakerTitle) m_BroadcastsRuleBreakerTitle.SetText(config.Broadcasts.RuleBreaker.Title);
                if (m_BroadcastsRuleBreakerMessage) m_BroadcastsRuleBreakerMessage.SetText(config.Broadcasts.RuleBreaker.Message);
                if (m_BroadcastsRuleBreakerIconPath) m_BroadcastsRuleBreakerIconPath.SetText(config.Broadcasts.RuleBreaker.IconPath);
            }
        }
    }
    void RefreshPlayersList()
    {
        PlayerBase player;
        player = PlayerBase.Cast(g_Game.GetPlayer());
        if (!player || !player.GetIdentity())
            return;
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestPlayers", new Param1<int>(0), true, player.GetIdentity());
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] Requested players list from server via RPC");
    }
    void UpdatePlayersList(array<string> players)
    {
        if (!m_PlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Cannot update - PlayersList widget is null!");
            return;
        }
        m_PlayersList.ClearItems();
        if (!players)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Received null players array from server!");
            return;
        }
        foreach (string playerName : players)
        {
            if (playerName != "")
            {
                m_PlayersList.AddItem(playerName, null, 0);
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] Updated players list: " + players.Count().ToString() + " players");
    }
    static void ForceDisableInputs(bool state, inout TIntArray skipIDs = null)
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
        if (w == m_btnNormalSettings)
        {
            ShowOnlyPanel(m_GeneralRootPanel);
            return true;
        }
        else if (w == m_btnNotifications)
        {
            ShowOnlyPanel(m_NotificationsRootPanel);
            return true;
        }
        else if (w == m_btnBlacklist)
        {
            ShowOnlyPanel(m_BlacklistRootPanel);
            return true;
        }
        int selectedRow;
        string selectedPlayerName;
        string actualPlayerName;
        int cdIndex;
        int noCooldownIndex;
        int row;
        string entry;
        PlayerBase player;
        player = PlayerBase.Cast(g_Game.GetPlayer());
        if (!player || !player.GetIdentity())
            return false;
        if (w == m_BtnApplyTestRuleBreakerBounty)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ApplyTestRuleBreakerBounty:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ApplyTestRuleBreakerBounty button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnAddBountySelectedPlayer)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddBountySelectedPlayer:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] AddBountySelectedPlayer button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnClearBounty)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearBounty"), true, player.GetIdentity());
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ClearBounty button clicked");
            return true;
        }
        else if (w == m_BtnClearBountySelectedPlayer)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearBountySelectedPlayer:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ClearBountySelectedPlayer button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnReloadConfigs)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ReloadConfigs"), true, player.GetIdentity());
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ReloadConfigs button clicked");
            return true;
        }
        else if (w == m_BtnClearAllCooldowns)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearAllCooldowns:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ClearAllCooldowns button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnClearPlayerCooldown)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("ClearPlayerCooldown:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] ClearPlayerCooldown button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnSaveAndReload)
        {
            BountyConfig updatedConfig = ReadConfigFromUI();
            if (updatedConfig)
            {
                GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminUpdateConfig", new Param1<ref BountyConfig>(updatedConfig), true, player.GetIdentity());
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] Save & Reload button clicked - config sent to server");
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Failed to read config from UI!");
            }
            return true;
        }
        else if (w == m_BtnAddRewardPoint)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddRewardPoint:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] AddRewardPoint button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        else if (w == m_BtnRemoveRewardPoint)
        {
            if (m_PlayersList)
            {
                selectedRow = m_PlayersList.GetSelectedRow();
                if (selectedRow >= 0)
                {
                    m_PlayersList.GetItemText(selectedRow, 0, selectedPlayerName);
                    if (selectedPlayerName != "")
                    {
                        actualPlayerName = selectedPlayerName;
                        cdIndex = selectedPlayerName.IndexOf(" CD:");
                        if (cdIndex >= 0)
                        {
                            actualPlayerName = selectedPlayerName.Substring(0, cdIndex);
                        }
                        else
                        {
                            noCooldownIndex = selectedPlayerName.IndexOf(" (No Cooldown)");
                            if (noCooldownIndex >= 0)
                            {
                                actualPlayerName = selectedPlayerName.Substring(0, noCooldownIndex);
                            }
                        }
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("RemoveRewardPoint:" + actualPlayerName), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] RemoveRewardPoint button clicked for player: " + actualPlayerName);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] No player selected from list!");
                }
            }
            return true;
        }
        if (w == m_AddToBlacklistBtn)
        {
            if (m_OnlinePlayersList)
            {
                row = m_OnlinePlayersList.GetSelectedRow();
                if (row >= 0)
                {
                    m_OnlinePlayersList.GetItemText(row, 0, entry);
                    if (entry != "")
                    {
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("AddToBlacklist:" + entry), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] AddToBlacklist button clicked for player: " + entry);
                    }
                }
            }
            return true;
        }
        else if (w == m_RemoveFromBlacklistBtn)
        {
            if (m_BlacklistedPlayersList)
            {
                row = m_BlacklistedPlayersList.GetSelectedRow();
                if (row >= 0)
                {
                    m_BlacklistedPlayersList.GetItemText(row, 0, entry);
                    if (entry != "")
                    {
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminAction", new Param1<string>("RemoveFromBlacklist:" + entry), true, player.GetIdentity());
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] RemoveFromBlacklist button clicked for entry: " + entry);
                    }
                }
            }
            return true;
        }
        else if (w == m_RefreshBlacklistPlayerListBtn)
        {
            RefreshBlacklistLists();
            return true;
        }
        return false;
    }
    void RefreshBlacklistLists()
    {
        PlayerBase player;
        player = PlayerBase.Cast(g_Game.GetPlayer());
        if (!player || !player.GetIdentity())
            return;
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", new Param1<int>(0), true, player.GetIdentity());
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminRequestBlacklist", new Param1<int>(0), true, player.GetIdentity());
    }
    void UpdateOnlinePlayersList(array<string> players)
    {
        if (!m_OnlinePlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Cannot update - OnlinePlayersList widget is null!");
            return;
        }
        m_OnlinePlayersList.ClearItems();
        if (!players)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Received null players array from server!");
            return;
        }
        foreach (string playerName : players)
        {
            if (playerName != "")
            {
                m_OnlinePlayersList.AddItem(playerName, null, 0);
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] Updated online players list: " + players.Count().ToString() + " players");
    }
    void UpdateBlacklistedPlayersList(array<string> blacklistedPlayers)
    {
        if (!m_BlacklistedPlayersList)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Cannot update - BlacklistedPlayersList widget is null!");
            return;
        }
        m_BlacklistedPlayersList.ClearItems();
        if (!blacklistedPlayers)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminMenu] Received null blacklisted players array from server!");
            return;
        }
        foreach (string entry : blacklistedPlayers)
        {
            if (entry != "")
            {
                m_BlacklistedPlayersList.AddItem(entry, null, 0);
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminMenu] Updated blacklisted players list: " + blacklistedPlayers.Count().ToString() + " players");
    }
    BountyConfig ReadConfigFromUI()
    {
        BountyConfig sourceConfig = m_CachedConfig;
        if (!sourceConfig)
            return null;
        BountyConfig config = new BountyConfig();
        string messageText;
        if (sourceConfig.Core)
        {
            config.Core = new BountyCoreSystemSettings();
            if (m_EnableBountySystem)
                config.Core.EnableBountySystem = m_EnableBountySystem.IsChecked();
            else
                config.Core.EnableBountySystem = sourceConfig.Core.EnableBountySystem;
            if (m_DisableSelfBounty)
                config.Core.DisableSelfBounty = m_DisableSelfBounty.IsChecked();
            else
                config.Core.DisableSelfBounty = sourceConfig.Core.DisableSelfBounty;
            if (m_TeleportOutOfOwnTerritory)
                config.Core.TeleportOutOfOwnTerritory = m_TeleportOutOfOwnTerritory.IsChecked();
            else
                config.Core.TeleportOutOfOwnTerritory = sourceConfig.Core.TeleportOutOfOwnTerritory;
            if (m_PauseBountyInTerritory)
                config.Core.PauseBountyInTerritory = m_PauseBountyInTerritory.IsChecked();
            else
                config.Core.PauseBountyInTerritory = sourceConfig.Core.PauseBountyInTerritory;
            if (m_TeleportOutOfSafeZone)
                config.Core.TeleportOutOfSafeZone = m_TeleportOutOfSafeZone.IsChecked();
            else
                config.Core.TeleportOutOfSafeZone = sourceConfig.Core.TeleportOutOfSafeZone;
            if (m_EnableAutomatedBountyPlacement)
                config.Core.EnableAutomatedBountyPlacement = m_EnableAutomatedBountyPlacement.IsChecked();
            else
                config.Core.EnableAutomatedBountyPlacement = sourceConfig.Core.EnableAutomatedBountyPlacement;
            if (m_BountyCooldownSeconds)
                config.Core.BountyCooldownSeconds = m_BountyCooldownSeconds.GetText().ToFloat();
            else
                config.Core.BountyCooldownSeconds = sourceConfig.Core.BountyCooldownSeconds;
            if (m_MaxBountiedPlayers)
                config.Core.MaxBountiedPlayers = m_MaxBountiedPlayers.GetText().ToInt();
            else
                config.Core.MaxBountiedPlayers = sourceConfig.Core.MaxBountiedPlayers;
            if (m_MinOnlinePlayersRequired)
                config.Core.MinOnlinePlayersRequired = m_MinOnlinePlayersRequired.GetText().ToInt();
            else
                config.Core.MinOnlinePlayersRequired = sourceConfig.Core.MinOnlinePlayersRequired;
            if (m_SkipBountyTokenRequired)
                config.Core.SkipBountyTokenRequired = m_SkipBountyTokenRequired.GetText().ToInt();
            else
                config.Core.SkipBountyTokenRequired = sourceConfig.Core.SkipBountyTokenRequired;
            if (m_PlaceBountyTokenRequired)
                config.Core.PlaceBountyTokenRequired = m_PlaceBountyTokenRequired.GetText().ToInt();
            else
                config.Core.PlaceBountyTokenRequired = sourceConfig.Core.PlaceBountyTokenRequired;
            if (m_ResumeBountyDistanceFromTerritory)
                config.Core.ResumeBountyDistanceFromTerritory = m_ResumeBountyDistanceFromTerritory.GetText().ToFloat();
            else
                config.Core.ResumeBountyDistanceFromTerritory = sourceConfig.Core.ResumeBountyDistanceFromTerritory;
            if (m_PausedBountyResumeCheckInterval)
                config.Core.PausedBountyResumeCheckInterval = m_PausedBountyResumeCheckInterval.GetText().ToFloat();
            else
                config.Core.PausedBountyResumeCheckInterval = sourceConfig.Core.PausedBountyResumeCheckInterval;
            if (m_TeleportOutOfSafeZoneDistance)
                config.Core.TeleportOutOfSafeZoneDistance = m_TeleportOutOfSafeZoneDistance.GetText().ToFloat();
            else
                config.Core.TeleportOutOfSafeZoneDistance = sourceConfig.Core.TeleportOutOfSafeZoneDistance;
            if (m_MinimumPlayerLifetimeSeconds)
                config.Core.MinimumPlayerLifetimeSeconds = m_MinimumPlayerLifetimeSeconds.GetText().ToInt();
            else
                config.Core.MinimumPlayerLifetimeSeconds = sourceConfig.Core.MinimumPlayerLifetimeSeconds;
            if (m_AutomatedBountyPlacementIntervalSeconds)
                config.Core.AutomatedBountyPlacementIntervalSeconds = m_AutomatedBountyPlacementIntervalSeconds.GetText().ToFloat();
            else
                config.Core.AutomatedBountyPlacementIntervalSeconds = sourceConfig.Core.AutomatedBountyPlacementIntervalSeconds;
        }
        if (sourceConfig.RuleBreaker)
        {
            config.RuleBreaker = new BountyRuleBreakerSettings();
            if (m_EnableRuleBreakerHitThreshold)
                config.RuleBreaker.EnableRuleBreakerHitThreshold = m_EnableRuleBreakerHitThreshold.IsChecked();
            else
                config.RuleBreaker.EnableRuleBreakerHitThreshold = sourceConfig.RuleBreaker.EnableRuleBreakerHitThreshold;
            if (m_EnablePvEToPvPRuleBreaker)
                config.RuleBreaker.EnablePvEToPvPRuleBreaker = m_EnablePvEToPvPRuleBreaker.IsChecked();
            else
                config.RuleBreaker.EnablePvEToPvPRuleBreaker = sourceConfig.RuleBreaker.EnablePvEToPvPRuleBreaker;
            if (m_ClearPendingRewardsOnRuleBreakerBounty)
                config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = m_ClearPendingRewardsOnRuleBreakerBounty.IsChecked();
            else
                config.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = sourceConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty;
            if (m_AllowPvEToPvEVictimKill)
                config.RuleBreaker.AllowPvEToPvEVictimKill = m_AllowPvEToPvEVictimKill.IsChecked();
            else
                config.RuleBreaker.AllowPvEToPvEVictimKill = sourceConfig.RuleBreaker.AllowPvEToPvEVictimKill;
            if (m_BountyRuleBreakerDurationSeconds)
                config.RuleBreaker.BountyRuleBreakerDurationSeconds = m_BountyRuleBreakerDurationSeconds.GetText().ToFloat();
            else
                config.RuleBreaker.BountyRuleBreakerDurationSeconds = sourceConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
            if (m_RuleBreakerHitThresholdTime)
                config.RuleBreaker.RuleBreakerHitThresholdTime = m_RuleBreakerHitThresholdTime.GetText().ToFloat();
            else
                config.RuleBreaker.RuleBreakerHitThresholdTime = sourceConfig.RuleBreaker.RuleBreakerHitThresholdTime;
            if (m_RuleBreakerHitThresholdWarningHits)
                config.RuleBreaker.RuleBreakerHitThresholdWarningHits = m_RuleBreakerHitThresholdWarningHits.GetText().ToInt();
            else
                config.RuleBreaker.RuleBreakerHitThresholdWarningHits = sourceConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits;
            if (m_RuleBreakerHitThresholdBountyHits)
                config.RuleBreaker.RuleBreakerHitThresholdBountyHits = m_RuleBreakerHitThresholdBountyHits.GetText().ToInt();
            else
                config.RuleBreaker.RuleBreakerHitThresholdBountyHits = sourceConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
            if (m_PvEToPvPInstantRuleBreakerHits)
                config.RuleBreaker.PvEToPvPInstantRuleBreakerHits = m_PvEToPvPInstantRuleBreakerHits.GetText().ToInt();
            else
                config.RuleBreaker.PvEToPvPInstantRuleBreakerHits = sourceConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits;
            if (m_Expansion_EnableHardlineReputationDecrease)
                config.RuleBreaker.Expansion_EnableHardlineReputationDecrease = m_Expansion_EnableHardlineReputationDecrease.IsChecked();
            else
                config.RuleBreaker.Expansion_EnableHardlineReputationDecrease = sourceConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease;
            if (m_Expansion_HardlineReputationDecreaseAmount)
                config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = m_Expansion_HardlineReputationDecreaseAmount.GetText().ToInt();
            else
                config.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = sourceConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount;
        }
        if (sourceConfig.PlacedBounty)
        {
            config.PlacedBounty = new BountyPlacedBountySettings();
            if (m_BountyDurationSeconds)
                config.PlacedBounty.BountyDurationSeconds = m_BountyDurationSeconds.GetText().ToFloat();
            else
                config.PlacedBounty.BountyDurationSeconds = sourceConfig.PlacedBounty.BountyDurationSeconds;
        }
        if (sourceConfig.Reward)
        {
            config.Reward = new BountyRewardSettings();
            if (m_EnableSurvivalReward)
                config.Reward.EnableSurvivalReward = m_EnableSurvivalReward.IsChecked();
            else
                config.Reward.EnableSurvivalReward = sourceConfig.Reward.EnableSurvivalReward;
            if (m_PvERuleBreakerGiveRewards)
                config.Reward.PvERuleBreakerGiveRewards = m_PvERuleBreakerGiveRewards.IsChecked();
            else
                config.Reward.PvERuleBreakerGiveRewards = sourceConfig.Reward.PvERuleBreakerGiveRewards;
        }
        if (sourceConfig.Map)
        {
            config.Map = new BountyMapSettings();
            if (m_BountyEnableMapDrawing)
                config.Map.BountyEnableMapDrawing = m_BountyEnableMapDrawing.IsChecked();
            else
                config.Map.BountyEnableMapDrawing = sourceConfig.Map.BountyEnableMapDrawing;
            if (m_BountyCircleReduceRadiusOverTime)
                config.Map.BountyCircleReduceRadiusOverTime = m_BountyCircleReduceRadiusOverTime.IsChecked();
            else
                config.Map.BountyCircleReduceRadiusOverTime = sourceConfig.Map.BountyCircleReduceRadiusOverTime;
            if (m_BountyCircleIncreaseRadiusOverTime)
                config.Map.BountyCircleIncreaseRadiusOverTime = m_BountyCircleIncreaseRadiusOverTime.IsChecked();
            else
                config.Map.BountyCircleIncreaseRadiusOverTime = sourceConfig.Map.BountyCircleIncreaseRadiusOverTime;
            if (m_BountyCircleRadius)
                config.Map.BountyCircleRadius = m_BountyCircleRadius.GetText().ToFloat();
            else
                config.Map.BountyCircleRadius = sourceConfig.Map.BountyCircleRadius;
            if (m_BountyCircleMinRadius)
                config.Map.BountyCircleMinRadius = m_BountyCircleMinRadius.GetText().ToFloat();
            else
                config.Map.BountyCircleMinRadius = sourceConfig.Map.BountyCircleMinRadius;
            if (m_BountyCircleColor)
                config.Map.BountyCircleColor = m_BountyCircleColor.GetText().ToInt();
            else
                config.Map.BountyCircleColor = sourceConfig.Map.BountyCircleColor;
            if (m_BountyCircleDrawingWidth)
                config.Map.BountyCircleDrawingWidth = m_BountyCircleDrawingWidth.GetText().ToInt();
            else
                config.Map.BountyCircleDrawingWidth = sourceConfig.Map.BountyCircleDrawingWidth;
            if (m_BountyMapUpdateIntervalSeconds)
                config.Map.BountyMapUpdateIntervalSeconds = m_BountyMapUpdateIntervalSeconds.GetText().ToFloat();
            else
                config.Map.BountyMapUpdateIntervalSeconds = sourceConfig.Map.BountyMapUpdateIntervalSeconds;
            if (m_BountyMapRequestCooldownSeconds)
                config.Map.BountyMapRequestCooldownSeconds = m_BountyMapRequestCooldownSeconds.GetText().ToFloat();
            else
                config.Map.BountyMapRequestCooldownSeconds = sourceConfig.Map.BountyMapRequestCooldownSeconds;
            if (m_BountyMapSyncIntervalSeconds)
                config.Map.BountyMapSyncIntervalSeconds = m_BountyMapSyncIntervalSeconds.GetText().ToFloat();
            else
                config.Map.BountyMapSyncIntervalSeconds = sourceConfig.Map.BountyMapSyncIntervalSeconds;
            if (m_BountyMapSyncIntervalNoBountiesSeconds)
                config.Map.BountyMapSyncIntervalNoBountiesSeconds = m_BountyMapSyncIntervalNoBountiesSeconds.GetText().ToFloat();
            else
                config.Map.BountyMapSyncIntervalNoBountiesSeconds = sourceConfig.Map.BountyMapSyncIntervalNoBountiesSeconds;
            if (m_BountyCircleOffsetMinMultiplier)
                config.Map.BountyCircleOffsetMinMultiplier = m_BountyCircleOffsetMinMultiplier.GetText().ToFloat();
            else
                config.Map.BountyCircleOffsetMinMultiplier = sourceConfig.Map.BountyCircleOffsetMinMultiplier;
            if (m_BountyCircleOffsetMaxMultiplier)
                config.Map.BountyCircleOffsetMaxMultiplier = m_BountyCircleOffsetMaxMultiplier.GetText().ToFloat();
            else
                config.Map.BountyCircleOffsetMaxMultiplier = sourceConfig.Map.BountyCircleOffsetMaxMultiplier;
        }
        if (sourceConfig.UI)
        {
            config.UI = new BountyUISettings();
            if (m_CountdownWidgetPositionX)
                config.UI.CountdownWidgetPositionX = m_CountdownWidgetPositionX.GetText().ToFloat();
            else
                config.UI.CountdownWidgetPositionX = sourceConfig.UI.CountdownWidgetPositionX;
            if (m_CountdownWidgetPositionY)
                config.UI.CountdownWidgetPositionY = m_CountdownWidgetPositionY.GetText().ToFloat();
            else
                config.UI.CountdownWidgetPositionY = sourceConfig.UI.CountdownWidgetPositionY;
            if (m_CountdownWidgetWidth)
                config.UI.CountdownWidgetWidth = m_CountdownWidgetWidth.GetText().ToFloat();
            else
                config.UI.CountdownWidgetWidth = sourceConfig.UI.CountdownWidgetWidth;
            if (m_CountdownWidgetHeight)
                config.UI.CountdownWidgetHeight = m_CountdownWidgetHeight.GetText().ToFloat();
            else
                config.UI.CountdownWidgetHeight = sourceConfig.UI.CountdownWidgetHeight;
            if (m_CountdownWidgetBackgroundColor)
                config.UI.CountdownWidgetBackgroundColor = m_CountdownWidgetBackgroundColor.GetText().ToInt();
            else
                config.UI.CountdownWidgetBackgroundColor = sourceConfig.UI.CountdownWidgetBackgroundColor;
            if (m_CountdownWidgetTextColor)
                config.UI.CountdownWidgetTextColor = m_CountdownWidgetTextColor.GetText().ToInt();
            else
                config.UI.CountdownWidgetTextColor = sourceConfig.UI.CountdownWidgetTextColor;
        }
        if (sourceConfig.Notifications && sourceConfig.Notifications.PlacedBounty)
        {
            if (!config.Notifications)
                config.Notifications = new BountyNotificationConfig();
            if (!config.Notifications.PlacedBounty)
                config.Notifications.PlacedBounty = new BountyNotificationGroup();
            if (m_PlacedBountyHuntedEnabled && config.Notifications.PlacedBounty.Hunted)
            {
                config.Notifications.PlacedBounty.Hunted.Enabled = m_PlacedBountyHuntedEnabled.IsChecked();
                if (m_PlacedBountyHuntedTitle) config.Notifications.PlacedBounty.Hunted.Title = m_PlacedBountyHuntedTitle.GetText();
                if (m_PlacedBountyHuntedMessage)
                {
                    m_PlacedBountyHuntedMessage.GetText(messageText);
                    config.Notifications.PlacedBounty.Hunted.Message = messageText;
                }
                if (m_PlacedBountyHuntedIconPath) config.Notifications.PlacedBounty.Hunted.IconPath = m_PlacedBountyHuntedIconPath.GetText();
            }
            else if (config.Notifications.PlacedBounty.Hunted)
            {
                config.Notifications.PlacedBounty.Hunted.Enabled = sourceConfig.Notifications.PlacedBounty.Hunted.Enabled;
                config.Notifications.PlacedBounty.Hunted.Title = sourceConfig.Notifications.PlacedBounty.Hunted.Title;
                config.Notifications.PlacedBounty.Hunted.Message = sourceConfig.Notifications.PlacedBounty.Hunted.Message;
                config.Notifications.PlacedBounty.Hunted.IconPath = sourceConfig.Notifications.PlacedBounty.Hunted.IconPath;
            }
            if (m_PlacedBountyExpiredEnabled && config.Notifications.PlacedBounty.Expired)
            {
                config.Notifications.PlacedBounty.Expired.Enabled = m_PlacedBountyExpiredEnabled.IsChecked();
                if (m_PlacedBountyExpiredTitle) config.Notifications.PlacedBounty.Expired.Title = m_PlacedBountyExpiredTitle.GetText();
                if (m_PlacedBountyExpiredMessage)
                {
                    m_PlacedBountyExpiredMessage.GetText(messageText);
                    config.Notifications.PlacedBounty.Expired.Message = messageText;
                }
                if (m_PlacedBountyExpiredIconPath) config.Notifications.PlacedBounty.Expired.IconPath = m_PlacedBountyExpiredIconPath.GetText();
            }
            else if (config.Notifications.PlacedBounty.Expired)
            {
                config.Notifications.PlacedBounty.Expired.Enabled = sourceConfig.Notifications.PlacedBounty.Expired.Enabled;
                config.Notifications.PlacedBounty.Expired.Title = sourceConfig.Notifications.PlacedBounty.Expired.Title;
                config.Notifications.PlacedBounty.Expired.Message = sourceConfig.Notifications.PlacedBounty.Expired.Message;
                config.Notifications.PlacedBounty.Expired.IconPath = sourceConfig.Notifications.PlacedBounty.Expired.IconPath;
            }
            if (m_PlacedBountySurvivalRewardEnabled && config.Notifications.PlacedBounty.SurvivalReward)
            {
                config.Notifications.PlacedBounty.SurvivalReward.Enabled = m_PlacedBountySurvivalRewardEnabled.IsChecked();
                if (m_PlacedBountySurvivalRewardTitle) config.Notifications.PlacedBounty.SurvivalReward.Title = m_PlacedBountySurvivalRewardTitle.GetText();
                if (m_PlacedBountySurvivalRewardMessage)
                {
                    m_PlacedBountySurvivalRewardMessage.GetText(messageText);
                    config.Notifications.PlacedBounty.SurvivalReward.Message = messageText;
                }
                if (m_PlacedBountySurvivalRewardIconPath) config.Notifications.PlacedBounty.SurvivalReward.IconPath = m_PlacedBountySurvivalRewardIconPath.GetText();
            }
            else if (config.Notifications.PlacedBounty.SurvivalReward)
            {
                config.Notifications.PlacedBounty.SurvivalReward.Enabled = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Enabled;
                config.Notifications.PlacedBounty.SurvivalReward.Title = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Title;
                config.Notifications.PlacedBounty.SurvivalReward.Message = sourceConfig.Notifications.PlacedBounty.SurvivalReward.Message;
                config.Notifications.PlacedBounty.SurvivalReward.IconPath = sourceConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
            }
            if (m_PlacedBountyKilledRewardEnabled && config.Notifications.PlacedBounty.KilledReward)
            {
                config.Notifications.PlacedBounty.KilledReward.Enabled = m_PlacedBountyKilledRewardEnabled.IsChecked();
                if (m_PlacedBountyKilledRewardTitle) config.Notifications.PlacedBounty.KilledReward.Title = m_PlacedBountyKilledRewardTitle.GetText();
                if (m_PlacedBountyKilledRewardMessage)
                {
                    m_PlacedBountyKilledRewardMessage.GetText(messageText);
                    config.Notifications.PlacedBounty.KilledReward.Message = messageText;
                }
                if (m_PlacedBountyKilledRewardIconPath) config.Notifications.PlacedBounty.KilledReward.IconPath = m_PlacedBountyKilledRewardIconPath.GetText();
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
                config.Notifications = new BountyNotificationConfig();
            if (!config.Notifications.RuleBreaker)
                config.Notifications.RuleBreaker = new BountyRuleBreakerNotificationGroup();
            if (m_RuleBreakerHuntedEnabled && config.Notifications.RuleBreaker.Hunted)
            {
                config.Notifications.RuleBreaker.Hunted.Enabled = m_RuleBreakerHuntedEnabled.IsChecked();
                if (m_RuleBreakerHuntedTitle) config.Notifications.RuleBreaker.Hunted.Title = m_RuleBreakerHuntedTitle.GetText();
                if (m_RuleBreakerHuntedMessage)
                {
                    m_RuleBreakerHuntedMessage.GetText(messageText);
                    config.Notifications.RuleBreaker.Hunted.Message = messageText;
                }
                if (m_RuleBreakerHuntedIconPath) config.Notifications.RuleBreaker.Hunted.IconPath = m_RuleBreakerHuntedIconPath.GetText();
            }
            else if (config.Notifications.RuleBreaker.Hunted)
            {
                config.Notifications.RuleBreaker.Hunted.Enabled = sourceConfig.Notifications.RuleBreaker.Hunted.Enabled;
                config.Notifications.RuleBreaker.Hunted.Title = sourceConfig.Notifications.RuleBreaker.Hunted.Title;
                config.Notifications.RuleBreaker.Hunted.Message = sourceConfig.Notifications.RuleBreaker.Hunted.Message;
                config.Notifications.RuleBreaker.Hunted.IconPath = sourceConfig.Notifications.RuleBreaker.Hunted.IconPath;
            }
            if (m_RuleBreakerHitWarningEnabled && config.Notifications.RuleBreaker.HitWarning)
            {
                config.Notifications.RuleBreaker.HitWarning.Enabled = m_RuleBreakerHitWarningEnabled.IsChecked();
                if (m_RuleBreakerHitWarningTitle) config.Notifications.RuleBreaker.HitWarning.Title = m_RuleBreakerHitWarningTitle.GetText();
                if (m_RuleBreakerHitWarningMessage)
                {
                    m_RuleBreakerHitWarningMessage.GetText(messageText);
                    config.Notifications.RuleBreaker.HitWarning.Message = messageText;
                }
                if (m_RuleBreakerHitWarningIconPath) config.Notifications.RuleBreaker.HitWarning.IconPath = m_RuleBreakerHitWarningIconPath.GetText();
            }
            else if (config.Notifications.RuleBreaker.HitWarning)
            {
                config.Notifications.RuleBreaker.HitWarning.Enabled = sourceConfig.Notifications.RuleBreaker.HitWarning.Enabled;
                config.Notifications.RuleBreaker.HitWarning.Title = sourceConfig.Notifications.RuleBreaker.HitWarning.Title;
                config.Notifications.RuleBreaker.HitWarning.Message = sourceConfig.Notifications.RuleBreaker.HitWarning.Message;
                config.Notifications.RuleBreaker.HitWarning.IconPath = sourceConfig.Notifications.RuleBreaker.HitWarning.IconPath;
            }
            if (m_RuleBreakerExpiredEnabled && config.Notifications.RuleBreaker.Expired)
            {
                config.Notifications.RuleBreaker.Expired.Enabled = m_RuleBreakerExpiredEnabled.IsChecked();
                if (m_RuleBreakerExpiredTitle) config.Notifications.RuleBreaker.Expired.Title = m_RuleBreakerExpiredTitle.GetText();
                if (m_RuleBreakerExpiredMessage)
                {
                    m_RuleBreakerExpiredMessage.GetText(messageText);
                    config.Notifications.RuleBreaker.Expired.Message = messageText;
                }
                if (m_RuleBreakerExpiredIconPath) config.Notifications.RuleBreaker.Expired.IconPath = m_RuleBreakerExpiredIconPath.GetText();
            }
            else if (config.Notifications.RuleBreaker.Expired)
            {
                config.Notifications.RuleBreaker.Expired.Enabled = sourceConfig.Notifications.RuleBreaker.Expired.Enabled;
                config.Notifications.RuleBreaker.Expired.Title = sourceConfig.Notifications.RuleBreaker.Expired.Title;
                config.Notifications.RuleBreaker.Expired.Message = sourceConfig.Notifications.RuleBreaker.Expired.Message;
                config.Notifications.RuleBreaker.Expired.IconPath = sourceConfig.Notifications.RuleBreaker.Expired.IconPath;
            }
            if (m_RuleBreakerSurvivalRewardEnabled && config.Notifications.RuleBreaker.SurvivalReward)
            {
                config.Notifications.RuleBreaker.SurvivalReward.Enabled = m_RuleBreakerSurvivalRewardEnabled.IsChecked();
                if (m_RuleBreakerSurvivalRewardTitle) config.Notifications.RuleBreaker.SurvivalReward.Title = m_RuleBreakerSurvivalRewardTitle.GetText();
                if (m_RuleBreakerSurvivalRewardMessage)
                {
                    m_RuleBreakerSurvivalRewardMessage.GetText(messageText);
                    config.Notifications.RuleBreaker.SurvivalReward.Message = messageText;
                }
                if (m_RuleBreakerSurvivalRewardIconPath) config.Notifications.RuleBreaker.SurvivalReward.IconPath = m_RuleBreakerSurvivalRewardIconPath.GetText();
            }
            else if (config.Notifications.RuleBreaker.SurvivalReward)
            {
                config.Notifications.RuleBreaker.SurvivalReward.Enabled = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Enabled;
                config.Notifications.RuleBreaker.SurvivalReward.Title = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Title;
                config.Notifications.RuleBreaker.SurvivalReward.Message = sourceConfig.Notifications.RuleBreaker.SurvivalReward.Message;
                config.Notifications.RuleBreaker.SurvivalReward.IconPath = sourceConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
            }
            if (m_RuleBreakerKilledRewardEnabled && config.Notifications.RuleBreaker.KilledReward)
            {
                config.Notifications.RuleBreaker.KilledReward.Enabled = m_RuleBreakerKilledRewardEnabled.IsChecked();
                if (m_RuleBreakerKilledRewardTitle) config.Notifications.RuleBreaker.KilledReward.Title = m_RuleBreakerKilledRewardTitle.GetText();
                if (m_RuleBreakerKilledRewardMessage)
                {
                    m_RuleBreakerKilledRewardMessage.GetText(messageText);
                    config.Notifications.RuleBreaker.KilledReward.Message = messageText;
                }
                if (m_RuleBreakerKilledRewardIconPath) config.Notifications.RuleBreaker.KilledReward.IconPath = m_RuleBreakerKilledRewardIconPath.GetText();
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
                config.Notifications = new BountyNotificationConfig();
            if (!config.Notifications.Other)
                config.Notifications.Other = new BountyOtherNotifications();
            if (m_OtherInsufficientTokensEnabled && config.Notifications.Other.InsufficientTokens)
            {
                config.Notifications.Other.InsufficientTokens.Enabled = m_OtherInsufficientTokensEnabled.IsChecked();
                if (m_OtherInsufficientTokensTitle) config.Notifications.Other.InsufficientTokens.Title = m_OtherInsufficientTokensTitle.GetText();
                if (m_OtherInsufficientTokensMessage)
                {
                    m_OtherInsufficientTokensMessage.GetText(messageText);
                    config.Notifications.Other.InsufficientTokens.Message = messageText;
                }
                if (m_OtherInsufficientTokensIconPath) config.Notifications.Other.InsufficientTokens.IconPath = m_OtherInsufficientTokensIconPath.GetText();
            }
            else if (config.Notifications.Other.InsufficientTokens)
            {
                config.Notifications.Other.InsufficientTokens.Enabled = sourceConfig.Notifications.Other.InsufficientTokens.Enabled;
                config.Notifications.Other.InsufficientTokens.Title = sourceConfig.Notifications.Other.InsufficientTokens.Title;
                config.Notifications.Other.InsufficientTokens.Message = sourceConfig.Notifications.Other.InsufficientTokens.Message;
                config.Notifications.Other.InsufficientTokens.IconPath = sourceConfig.Notifications.Other.InsufficientTokens.IconPath;
            }
            if (m_OtherSkipBountyNoPlayersEnabled && config.Notifications.Other.SkipBountyNoPlayers)
            {
                config.Notifications.Other.SkipBountyNoPlayers.Enabled = m_OtherSkipBountyNoPlayersEnabled.IsChecked();
                if (m_OtherSkipBountyNoPlayersTitle) config.Notifications.Other.SkipBountyNoPlayers.Title = m_OtherSkipBountyNoPlayersTitle.GetText();
                if (m_OtherSkipBountyNoPlayersMessage)
                {
                    m_OtherSkipBountyNoPlayersMessage.GetText(messageText);
                    config.Notifications.Other.SkipBountyNoPlayers.Message = messageText;
                }
                if (m_OtherSkipBountyNoPlayersIconPath) config.Notifications.Other.SkipBountyNoPlayers.IconPath = m_OtherSkipBountyNoPlayersIconPath.GetText();
            }
            else if (config.Notifications.Other.SkipBountyNoPlayers)
            {
                config.Notifications.Other.SkipBountyNoPlayers.Enabled = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Enabled;
                config.Notifications.Other.SkipBountyNoPlayers.Title = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Title;
                config.Notifications.Other.SkipBountyNoPlayers.Message = sourceConfig.Notifications.Other.SkipBountyNoPlayers.Message;
                config.Notifications.Other.SkipBountyNoPlayers.IconPath = sourceConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
            }
            if (m_OtherSkipBountySuccessEnabled && config.Notifications.Other.SkipBountySuccess)
            {
                config.Notifications.Other.SkipBountySuccess.Enabled = m_OtherSkipBountySuccessEnabled.IsChecked();
                if (m_OtherSkipBountySuccessTitle) config.Notifications.Other.SkipBountySuccess.Title = m_OtherSkipBountySuccessTitle.GetText();
                if (m_OtherSkipBountySuccessMessage)
                {
                    m_OtherSkipBountySuccessMessage.GetText(messageText);
                    config.Notifications.Other.SkipBountySuccess.Message = messageText;
                }
                if (m_OtherSkipBountySuccessIconPath) config.Notifications.Other.SkipBountySuccess.IconPath = m_OtherSkipBountySuccessIconPath.GetText();
            }
            else if (config.Notifications.Other.SkipBountySuccess)
            {
                config.Notifications.Other.SkipBountySuccess.Enabled = sourceConfig.Notifications.Other.SkipBountySuccess.Enabled;
                config.Notifications.Other.SkipBountySuccess.Title = sourceConfig.Notifications.Other.SkipBountySuccess.Title;
                config.Notifications.Other.SkipBountySuccess.Message = sourceConfig.Notifications.Other.SkipBountySuccess.Message;
                config.Notifications.Other.SkipBountySuccess.IconPath = sourceConfig.Notifications.Other.SkipBountySuccess.IconPath;
            }
            if (m_OtherBountySkippedEnabled && config.Notifications.Other.BountySkipped)
            {
                config.Notifications.Other.BountySkipped.Enabled = m_OtherBountySkippedEnabled.IsChecked();
                if (m_OtherBountySkippedTitle) config.Notifications.Other.BountySkipped.Title = m_OtherBountySkippedTitle.GetText();
                if (m_OtherBountySkippedMessage)
                {
                    m_OtherBountySkippedMessage.GetText(messageText);
                    config.Notifications.Other.BountySkipped.Message = messageText;
                }
                if (m_OtherBountySkippedIconPath) config.Notifications.Other.BountySkipped.IconPath = m_OtherBountySkippedIconPath.GetText();
            }
            else if (config.Notifications.Other.BountySkipped)
            {
                config.Notifications.Other.BountySkipped.Enabled = sourceConfig.Notifications.Other.BountySkipped.Enabled;
                config.Notifications.Other.BountySkipped.Title = sourceConfig.Notifications.Other.BountySkipped.Title;
                config.Notifications.Other.BountySkipped.Message = sourceConfig.Notifications.Other.BountySkipped.Message;
                config.Notifications.Other.BountySkipped.IconPath = sourceConfig.Notifications.Other.BountySkipped.IconPath;
            }
            if (m_OtherRewardHandsNotFreeEnabled && config.Notifications.Other.RewardHandsNotFree)
            {
                config.Notifications.Other.RewardHandsNotFree.Enabled = m_OtherRewardHandsNotFreeEnabled.IsChecked();
                if (m_OtherRewardHandsNotFreeTitle) config.Notifications.Other.RewardHandsNotFree.Title = m_OtherRewardHandsNotFreeTitle.GetText();
                if (m_OtherRewardHandsNotFreeMessage)
                {
                    m_OtherRewardHandsNotFreeMessage.GetText(messageText);
                    config.Notifications.Other.RewardHandsNotFree.Message = messageText;
                }
                if (m_OtherRewardHandsNotFreeIconPath) config.Notifications.Other.RewardHandsNotFree.IconPath = m_OtherRewardHandsNotFreeIconPath.GetText();
            }
            else if (config.Notifications.Other.RewardHandsNotFree)
            {
                config.Notifications.Other.RewardHandsNotFree.Enabled = sourceConfig.Notifications.Other.RewardHandsNotFree.Enabled;
                config.Notifications.Other.RewardHandsNotFree.Title = sourceConfig.Notifications.Other.RewardHandsNotFree.Title;
                config.Notifications.Other.RewardHandsNotFree.Message = sourceConfig.Notifications.Other.RewardHandsNotFree.Message;
                config.Notifications.Other.RewardHandsNotFree.IconPath = sourceConfig.Notifications.Other.RewardHandsNotFree.IconPath;
            }
            if (m_OtherPlayerOnCooldownEnabled && config.Notifications.Other.PlayerOnCooldown)
            {
                config.Notifications.Other.PlayerOnCooldown.Enabled = m_OtherPlayerOnCooldownEnabled.IsChecked();
                if (m_OtherPlayerOnCooldownTitle) config.Notifications.Other.PlayerOnCooldown.Title = m_OtherPlayerOnCooldownTitle.GetText();
                if (m_OtherPlayerOnCooldownMessage)
                {
                    m_OtherPlayerOnCooldownMessage.GetText(messageText);
                    config.Notifications.Other.PlayerOnCooldown.Message = messageText;
                }
                if (m_OtherPlayerOnCooldownIconPath) config.Notifications.Other.PlayerOnCooldown.IconPath = m_OtherPlayerOnCooldownIconPath.GetText();
            }
            else if (config.Notifications.Other.PlayerOnCooldown)
            {
                config.Notifications.Other.PlayerOnCooldown.Enabled = sourceConfig.Notifications.Other.PlayerOnCooldown.Enabled;
                config.Notifications.Other.PlayerOnCooldown.Title = sourceConfig.Notifications.Other.PlayerOnCooldown.Title;
                config.Notifications.Other.PlayerOnCooldown.Message = sourceConfig.Notifications.Other.PlayerOnCooldown.Message;
                config.Notifications.Other.PlayerOnCooldown.IconPath = sourceConfig.Notifications.Other.PlayerOnCooldown.IconPath;
            }
            if (m_OtherPlayerInSafeZoneEnabled && config.Notifications.Other.PlayerInSafeZone)
            {
                config.Notifications.Other.PlayerInSafeZone.Enabled = m_OtherPlayerInSafeZoneEnabled.IsChecked();
                if (m_OtherPlayerInSafeZoneTitle) config.Notifications.Other.PlayerInSafeZone.Title = m_OtherPlayerInSafeZoneTitle.GetText();
                if (m_OtherPlayerInSafeZoneMessage)
                {
                    m_OtherPlayerInSafeZoneMessage.GetText(messageText);
                    config.Notifications.Other.PlayerInSafeZone.Message = messageText;
                }
                if (m_OtherPlayerInSafeZoneIconPath) config.Notifications.Other.PlayerInSafeZone.IconPath = m_OtherPlayerInSafeZoneIconPath.GetText();
            }
            else if (config.Notifications.Other.PlayerInSafeZone)
            {
                config.Notifications.Other.PlayerInSafeZone.Enabled = sourceConfig.Notifications.Other.PlayerInSafeZone.Enabled;
                config.Notifications.Other.PlayerInSafeZone.Title = sourceConfig.Notifications.Other.PlayerInSafeZone.Title;
                config.Notifications.Other.PlayerInSafeZone.Message = sourceConfig.Notifications.Other.PlayerInSafeZone.Message;
                config.Notifications.Other.PlayerInSafeZone.IconPath = sourceConfig.Notifications.Other.PlayerInSafeZone.IconPath;
            }
            if (m_OtherBountyPersistedEnabled && config.Notifications.Other.BountyPersisted)
            {
                config.Notifications.Other.BountyPersisted.Enabled = m_OtherBountyPersistedEnabled.IsChecked();
                if (m_OtherBountyPersistedTitle) config.Notifications.Other.BountyPersisted.Title = m_OtherBountyPersistedTitle.GetText();
                if (m_OtherBountyPersistedMessage)
                {
                    m_OtherBountyPersistedMessage.GetText(messageText);
                    config.Notifications.Other.BountyPersisted.Message = messageText;
                }
                if (m_OtherBountyPersistedIconPath) config.Notifications.Other.BountyPersisted.IconPath = m_OtherBountyPersistedIconPath.GetText();
            }
            else if (config.Notifications.Other.BountyPersisted)
            {
                config.Notifications.Other.BountyPersisted.Enabled = sourceConfig.Notifications.Other.BountyPersisted.Enabled;
                config.Notifications.Other.BountyPersisted.Title = sourceConfig.Notifications.Other.BountyPersisted.Title;
                config.Notifications.Other.BountyPersisted.Message = sourceConfig.Notifications.Other.BountyPersisted.Message;
                config.Notifications.Other.BountyPersisted.IconPath = sourceConfig.Notifications.Other.BountyPersisted.IconPath;
            }
            if (m_OtherTeleportedOutOfTerritoryEnabled && config.Notifications.Other.TeleportedOutOfTerritory)
            {
                config.Notifications.Other.TeleportedOutOfTerritory.Enabled = m_OtherTeleportedOutOfTerritoryEnabled.IsChecked();
                if (m_OtherTeleportedOutOfTerritoryTitle) config.Notifications.Other.TeleportedOutOfTerritory.Title = m_OtherTeleportedOutOfTerritoryTitle.GetText();
                if (m_OtherTeleportedOutOfTerritoryMessage)
                {
                    m_OtherTeleportedOutOfTerritoryMessage.GetText(messageText);
                    config.Notifications.Other.TeleportedOutOfTerritory.Message = messageText;
                }
                if (m_OtherTeleportedOutOfTerritoryIconPath) config.Notifications.Other.TeleportedOutOfTerritory.IconPath = m_OtherTeleportedOutOfTerritoryIconPath.GetText();
            }
            else if (config.Notifications.Other.TeleportedOutOfTerritory)
            {
                config.Notifications.Other.TeleportedOutOfTerritory.Enabled = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled;
                config.Notifications.Other.TeleportedOutOfTerritory.Title = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
                config.Notifications.Other.TeleportedOutOfTerritory.Message = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
                config.Notifications.Other.TeleportedOutOfTerritory.IconPath = sourceConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
            }
            if (m_OtherBountyPausedInTerritoryEnabled && config.Notifications.Other.BountyPausedInTerritory)
            {
                config.Notifications.Other.BountyPausedInTerritory.Enabled = m_OtherBountyPausedInTerritoryEnabled.IsChecked();
                if (m_OtherBountyPausedInTerritoryTitle) config.Notifications.Other.BountyPausedInTerritory.Title = m_OtherBountyPausedInTerritoryTitle.GetText();
                if (m_OtherBountyPausedInTerritoryMessage)
                {
                    m_OtherBountyPausedInTerritoryMessage.GetText(messageText);
                    config.Notifications.Other.BountyPausedInTerritory.Message = messageText;
                }
                if (m_OtherBountyPausedInTerritoryIconPath) config.Notifications.Other.BountyPausedInTerritory.IconPath = m_OtherBountyPausedInTerritoryIconPath.GetText();
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
                config.Broadcasts = new BountyBroadcasts();
            if (m_BroadcastsPlacedBountyEnabled && config.Broadcasts.PlacedBounty)
            {
                config.Broadcasts.PlacedBounty.Enabled = m_BroadcastsPlacedBountyEnabled.IsChecked();
                if (m_BroadcastsPlacedBountyTitle) config.Broadcasts.PlacedBounty.Title = m_BroadcastsPlacedBountyTitle.GetText();
                if (m_BroadcastsPlacedBountyMessage)
                {
                    m_BroadcastsPlacedBountyMessage.GetText(messageText);
                    config.Broadcasts.PlacedBounty.Message = messageText;
                }
                if (m_BroadcastsPlacedBountyIconPath) config.Broadcasts.PlacedBounty.IconPath = m_BroadcastsPlacedBountyIconPath.GetText();
            }
            else if (config.Broadcasts.PlacedBounty)
            {
                config.Broadcasts.PlacedBounty.Enabled = sourceConfig.Broadcasts.PlacedBounty.Enabled;
                config.Broadcasts.PlacedBounty.Title = sourceConfig.Broadcasts.PlacedBounty.Title;
                config.Broadcasts.PlacedBounty.Message = sourceConfig.Broadcasts.PlacedBounty.Message;
                config.Broadcasts.PlacedBounty.IconPath = sourceConfig.Broadcasts.PlacedBounty.IconPath;
            }
            if (m_BroadcastsRuleBreakerEnabled && config.Broadcasts.RuleBreaker)
            {
                config.Broadcasts.RuleBreaker.Enabled = m_BroadcastsRuleBreakerEnabled.IsChecked();
                if (m_BroadcastsRuleBreakerTitle) config.Broadcasts.RuleBreaker.Title = m_BroadcastsRuleBreakerTitle.GetText();
                if (m_BroadcastsRuleBreakerMessage)
                {
                    m_BroadcastsRuleBreakerMessage.GetText(messageText);
                    config.Broadcasts.RuleBreaker.Message = messageText;
                }
                if (m_BroadcastsRuleBreakerIconPath) config.Broadcasts.RuleBreaker.IconPath = m_BroadcastsRuleBreakerIconPath.GetText();
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
        ForceDisableInputs(false);
        PPEffects.SetBlurMenu(0);
        g_Game.GetInput().ResetGameFocus();
        g_Game.GetUIManager().ShowUICursor(false);
        g_Game.GetMission().GetHud().Show(true);
        Close();
    }
}