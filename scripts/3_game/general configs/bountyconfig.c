const string Ninjins_Bounty_System_CONFIG_DIR = Ninjins_Bounty_System_ROOT_FOLDER + "Config\\";
const string Ninjins_Bounty_System_CONFIG_FILE = Ninjins_Bounty_System_CONFIG_DIR + "BountyConfig.json";
ref BountyConfig g_BountyConfig;
class BountyNotificationEntry
{
    bool Enabled;
    string Title;
    string Message;
    string IconPath; 
    void BountyNotificationEntry()
    {
        Enabled = true;
        Title = "";
        Message = "";
        IconPath = ""; 
    }
}
class BountyNotificationGroup
{
    ref BountyNotificationEntry Hunted;
    ref BountyNotificationEntry Expired;
    ref BountyNotificationEntry SurvivalReward;
    ref BountyNotificationEntry KilledReward;
    void BountyNotificationGroup()
    {
        Hunted = new BountyNotificationEntry();
        Expired = new BountyNotificationEntry();
        SurvivalReward = new BountyNotificationEntry();
        KilledReward = new BountyNotificationEntry();
    }
}
class BountyRuleBreakerNotificationGroup
{
    ref BountyNotificationEntry Hunted;
    ref BountyNotificationEntry HitWarning; 
    ref BountyNotificationEntry Expired;
    ref BountyNotificationEntry SurvivalReward;
    ref BountyNotificationEntry KilledReward;
    void BountyRuleBreakerNotificationGroup()
    {
        Hunted = new BountyNotificationEntry();
        HitWarning = new BountyNotificationEntry();
        Expired = new BountyNotificationEntry();
        SurvivalReward = new BountyNotificationEntry();
        KilledReward = new BountyNotificationEntry();
    }
}
class BountyOtherNotifications
{
    ref BountyNotificationEntry InsufficientTokens;
    ref BountyNotificationEntry SkipBountyNoPlayers;
    ref BountyNotificationEntry SkipBountySuccess;
    ref BountyNotificationEntry BountySkipped;
    ref BountyNotificationEntry RewardHandsNotFree;
    ref BountyNotificationEntry PlayerOnCooldown;
    ref BountyNotificationEntry PlayerInSafeZone; 
    ref BountyNotificationEntry BountyPersisted; 
    ref BountyNotificationEntry TeleportedOutOfTerritory; 
    ref BountyNotificationEntry BountyPausedInTerritory; 
    void BountyOtherNotifications()
    {
        InsufficientTokens = new BountyNotificationEntry();
        SkipBountyNoPlayers = new BountyNotificationEntry();
        SkipBountySuccess = new BountyNotificationEntry();
        BountySkipped = new BountyNotificationEntry();
        RewardHandsNotFree = new BountyNotificationEntry();
        PlayerOnCooldown = new BountyNotificationEntry();
        PlayerInSafeZone = new BountyNotificationEntry();
        BountyPersisted = new BountyNotificationEntry();
        TeleportedOutOfTerritory = new BountyNotificationEntry();
        BountyPausedInTerritory = new BountyNotificationEntry();
    }
}
class BountyBroadcastEntry
{
    bool Enabled;
    string Title;
    string Message;
    string IconPath; 
    void BountyBroadcastEntry()
    {
        Enabled = true;
        Title = "";
        Message = "";
        IconPath = ""; 
    }
}
class BountyBroadcasts
{
    ref BountyBroadcastEntry PlacedBounty;
    ref BountyBroadcastEntry RuleBreaker;
    void BountyBroadcasts()
    {
        PlacedBounty = new BountyBroadcastEntry();
        RuleBreaker = new BountyBroadcastEntry();
    }
}
class BountyNotificationConfig
{
    ref BountyNotificationGroup PlacedBounty;
    ref BountyRuleBreakerNotificationGroup RuleBreaker;
    ref BountyOtherNotifications Other;
    void BountyNotificationConfig()
    {
        PlacedBounty = new BountyNotificationGroup();
        RuleBreaker = new BountyRuleBreakerNotificationGroup();
        Other = new BountyOtherNotifications();
    }
}
class BountyRewardAttachment
{
    string ItemClassName; 
    float SpawnChance; 
    int Amount; 
    float QuantMin; 
    float QuantMax; 
    float HealthMin; 
    float HealthMax; 
    ref array<ref BountyRewardAttachment> Attachments; 
    void BountyRewardAttachment()
    {
        ItemClassName = "";
        SpawnChance = 100.0; 
        Amount = 0; 
        QuantMin = 0.0; 
        QuantMax = 0.0; 
        HealthMin = 0.0; 
        HealthMax = 0.0; 
        Attachments = new array<ref BountyRewardAttachment>;
    }
}
class BountyRewardItem
{
    string ItemClassName;
    float SpawnChance; 
    int Amount; 
    float QuantMin; 
    float QuantMax; 
    float HealthMin; 
    float HealthMax; 
    ref array<ref BountyRewardAttachment> Attachments; 
    void BountyRewardItem()
    {
        ItemClassName = "";
        SpawnChance = 100.0; 
        Amount = 0; 
        QuantMin = 0.0; 
        QuantMax = 0.0; 
        HealthMin = 0.0; 
        HealthMax = 0.0; 
        Attachments = new array<ref BountyRewardAttachment>;
    }
}
class BountyCurrencyReward
{
    string ClassName; 
    float SpawnChance; 
    int Amount; 
    void BountyCurrencyReward()
    {
        ClassName = "";
        SpawnChance = 100.0; 
        Amount = 0;
    }
}
class BountyRewardSection
{
    string Name; 
    string ContainerClassName; 
    float SpawnChance; 
    int ItemsMin; 
    int ItemsMax; 
    ref array<ref BountyRewardItem> LootItems; 
    void BountyRewardSection()
    {
        Name = "";
        ContainerClassName = "";
        SpawnChance = 100.0; 
        ItemsMin = 1;
        ItemsMax = 1;
        LootItems = new array<ref BountyRewardItem>;
    }
}
class BountyCoreSystemSettings
{
    bool EnableBountySystem;
    float BountyCooldownSeconds; 
    int MaxBountiedPlayers; 
    int MinOnlinePlayersRequired; 
    bool DisableSelfBounty; 
    int SkipBountyTokenRequired; 
    int PlaceBountyTokenRequired; 
    ref array<string> BountyTokenClassNames; 
    bool EnableConfigReloadSuccessNotification; 
    bool EnableCommandAccessDeniedNotification; 
    bool TeleportOutOfOwnTerritory; 
    bool PauseBountyInTerritory; 
    float ResumeBountyDistanceFromTerritory; 
    float PausedBountyResumeCheckInterval; 
    bool TeleportOutOfSafeZone; 
    float TeleportOutOfSafeZoneDistance; 
    int MinimumPlayerLifetimeSeconds; 
    bool EnableAutomatedBountyPlacement; 
    float AutomatedBountyPlacementIntervalSeconds; 
    void BountyCoreSystemSettings()
    {
        EnableBountySystem = true;
        BountyCooldownSeconds = 3600.0; 
        MaxBountiedPlayers = -1; 
        MinOnlinePlayersRequired = 1; 
        DisableSelfBounty = true; 
        SkipBountyTokenRequired = 10; 
        PlaceBountyTokenRequired = 20; 
        BountyTokenClassNames = new array<string>;
        BountyTokenClassNames.Insert("Ninjins_Bounty_Token_Gold");
        EnableConfigReloadSuccessNotification = true;
        EnableCommandAccessDeniedNotification = true;
        TeleportOutOfOwnTerritory = true; 
        PauseBountyInTerritory = true; 
        ResumeBountyDistanceFromTerritory = 50.0; 
        PausedBountyResumeCheckInterval = 5.0; 
        TeleportOutOfSafeZone = true; 
        TeleportOutOfSafeZoneDistance = 150.0; 
        MinimumPlayerLifetimeSeconds = 900; 
        EnableAutomatedBountyPlacement = false; 
        AutomatedBountyPlacementIntervalSeconds = 3600.0; 
    }
}
class BountyRuleBreakerSettings
{
    bool EnableRuleBreakerHitThreshold; 
    bool EnablePvEToPvPRuleBreaker; 
    int PvEToPvPInstantRuleBreakerHits; 
    float BountyRuleBreakerDurationSeconds; 
    float RuleBreakerHitThresholdTime; 
    int RuleBreakerHitThresholdWarningHits; 
    int RuleBreakerHitThresholdBountyHits; 
    bool ClearPendingRewardsOnRuleBreakerBounty; 
    bool AllowPvEToPvEVictimKill; 
    bool Expansion_EnableHardlineReputationDecrease; 
    int Expansion_HardlineReputationDecreaseAmount; 
    void BountyRuleBreakerSettings()
    {
        EnableRuleBreakerHitThreshold = false; 
        EnablePvEToPvPRuleBreaker = true; 
        PvEToPvPInstantRuleBreakerHits = 0; 
        BountyRuleBreakerDurationSeconds = 3600.0; 
        RuleBreakerHitThresholdTime = 10.0; 
        RuleBreakerHitThresholdWarningHits = 10; 
        RuleBreakerHitThresholdBountyHits = 15; 
        ClearPendingRewardsOnRuleBreakerBounty = false; 
        AllowPvEToPvEVictimKill = false; 
        Expansion_EnableHardlineReputationDecrease = false; 
        Expansion_HardlineReputationDecreaseAmount = 10; 
    }
}
class BountyPlacedBountySettings
{
    float BountyDurationSeconds; 
    void BountyPlacedBountySettings()
    {
        BountyDurationSeconds = 60.0;
    }
}
class BountyRewardSettings
{
    bool EnableSurvivalReward; 
    bool PvERuleBreakerGiveRewards; 
    void BountyRewardSettings()
    {
        EnableSurvivalReward = true;
        PvERuleBreakerGiveRewards = false; 
    }
}
class BountyUISettings
{
    float CountdownWidgetPositionX; 
    float CountdownWidgetPositionY; 
    float CountdownWidgetWidth; 
    float CountdownWidgetHeight; 
    int CountdownWidgetBackgroundColor; 
    int CountdownWidgetTextColor; 
    void BountyUISettings()
    {
        CountdownWidgetPositionX = 0.0; 
        CountdownWidgetPositionY = 0.0; 
        CountdownWidgetWidth = 0.0; 
        CountdownWidgetHeight = 0.0; 
        CountdownWidgetBackgroundColor = 0; 
        CountdownWidgetTextColor = 0; 
    }
}
class BountyMapSettings
{
    bool BountyEnableMapDrawing; 
    float BountyCircleRadius; 
    float BountyCircleMinRadius; 
    bool BountyCircleReduceRadiusOverTime; 
    bool BountyCircleIncreaseRadiusOverTime; 
    int BountyCircleColor; 
    int BountyCircleDrawingWidth; 
    float BountyMapUpdateIntervalSeconds; 
    float BountyMapRequestCooldownSeconds; 
    float BountyMapSyncIntervalSeconds; 
    float BountyMapSyncIntervalNoBountiesSeconds; 
    float BountyCircleOffsetMinMultiplier; 
    float BountyCircleOffsetMaxMultiplier; 
    void BountyMapSettings()
    {
        BountyEnableMapDrawing = true;
        BountyCircleRadius = 100.0; 
        BountyCircleMinRadius = 10.0; 
        BountyCircleReduceRadiusOverTime = true;
        BountyCircleIncreaseRadiusOverTime = false;
        BountyCircleColor = ARGB(255, 255, 0, 0); 
        BountyCircleDrawingWidth = 2;
        BountyMapUpdateIntervalSeconds = 10.0;
        BountyMapRequestCooldownSeconds = 10.0;
        BountyMapSyncIntervalSeconds = 10.0;
        BountyMapSyncIntervalNoBountiesSeconds = 10.0;
        BountyCircleOffsetMinMultiplier = 0.1;
        BountyCircleOffsetMaxMultiplier = 0.9;
    }
}
class BountyConfig
{
    ref BountyCoreSystemSettings Core;
    ref BountyRuleBreakerSettings RuleBreaker;
    ref BountyPlacedBountySettings PlacedBounty;
    ref BountyRewardSettings Reward;
    ref BountyMapSettings Map;
    ref BountyUISettings UI;
    ref BountyNotificationConfig Notifications;
    ref BountyBroadcasts Broadcasts;
    void BountyConfig()
    {
        Core = new BountyCoreSystemSettings();
        RuleBreaker = new BountyRuleBreakerSettings();
        PlacedBounty = new BountyPlacedBountySettings();
        Reward = new BountyRewardSettings();
        Map = new BountyMapSettings();
        UI = new BountyUISettings();
        Notifications = new BountyNotificationConfig();
        Notifications.PlacedBounty.Hunted.Enabled = true;
        Notifications.PlacedBounty.Hunted.Title = "Bounty Placed";
        Notifications.PlacedBounty.Hunted.Message = "A bounty has been placed on you! You are now hunted for {DURATION} seconds.";
        Notifications.PlacedBounty.Hunted.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.PlacedBounty.Expired.Enabled = true;
        Notifications.PlacedBounty.Expired.Title = "Bounty Expired";
        Notifications.PlacedBounty.Expired.Message = "Your bounty has expired. You are no longer hunted.";
        Notifications.PlacedBounty.Expired.IconPath = "Ninjins_Bounty_System/gui/icons/bountycheckmark.edds";
        Notifications.PlacedBounty.SurvivalReward.Enabled = true;
        Notifications.PlacedBounty.SurvivalReward.Title = "Bounty Survived";
        Notifications.PlacedBounty.SurvivalReward.Message = "Congratulations! You have survived your bounty. Claim your reward at the bounty board!";
        Notifications.PlacedBounty.SurvivalReward.IconPath = "Ninjins_Bounty_System/gui/icons/bountycheckmark.edds";
        Notifications.PlacedBounty.KilledReward.Enabled = true;
        Notifications.PlacedBounty.KilledReward.Title = "Bounty Eliminated";
        Notifications.PlacedBounty.KilledReward.Message = "Congratulations! You have eliminated {VICTIM} who had a bounty. Claim your reward at the bounty board!";
        Notifications.PlacedBounty.KilledReward.IconPath = "Ninjins_Bounty_System/gui/icons/bountycheckmark.edds";
        Notifications.RuleBreaker.Hunted.Enabled = true;
        Notifications.RuleBreaker.Hunted.Title = "Rule Violation";
        Notifications.RuleBreaker.Hunted.Message = "Bounty was placed on you! You are now hunted and can be attacked by PvE players for {DURATION} seconds. {CLEARED_REWARDS}";
        Notifications.RuleBreaker.Hunted.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.RuleBreaker.HitWarning.Enabled = true;
        Notifications.RuleBreaker.HitWarning.Title = "Warning: Rule Violation";
        Notifications.RuleBreaker.HitWarning.Message = "You have hit a PvE player {HITS} times! If you hit them {BOUNTY_HITS} times, you will receive a rule breaker bounty!";
        Notifications.RuleBreaker.HitWarning.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.RuleBreaker.Expired.Enabled = true;
        Notifications.RuleBreaker.Expired.Title = "Bounty Expired";
        Notifications.RuleBreaker.Expired.Message = "Your rule breaker bounty has expired. You are no longer hunted. No rewards were given due to rule breaking.";
        Notifications.RuleBreaker.Expired.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.RuleBreaker.SurvivalReward.Enabled = true;
        Notifications.RuleBreaker.SurvivalReward.Title = "Bounty Survived";
        Notifications.RuleBreaker.SurvivalReward.Message = "Your rule breaker bounty has expired. You survived, but no reward is given due to rule breaking.";
        Notifications.RuleBreaker.SurvivalReward.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.RuleBreaker.KilledReward.Enabled = true;
        Notifications.RuleBreaker.KilledReward.Title = "Rule Breaker Eliminated";
        Notifications.RuleBreaker.KilledReward.Message = "You have eliminated {VICTIM} who was a rule breaker. No reward is given for rule breakers.";
        Notifications.RuleBreaker.KilledReward.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.InsufficientTokens.Enabled = true;
        Notifications.Other.InsufficientTokens.Title = "Insufficient Tokens";
        Notifications.Other.InsufficientTokens.Message = "You need {REQUIRED} bounty token(s) to perform this action. You have {FOUND} token(s) in your inventory.";
        Notifications.Other.InsufficientTokens.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.SkipBountyNoPlayers.Enabled = true;
        Notifications.Other.SkipBountyNoPlayers.Title = "Cannot Skip Bounty";
        Notifications.Other.SkipBountyNoPlayers.Message = "There are no other players online to transfer your bounty to. Your tokens were not consumed.";
        Notifications.Other.SkipBountyNoPlayers.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.SkipBountySuccess.Enabled = true;
        Notifications.Other.SkipBountySuccess.Title = "Bounty Skipped";
        Notifications.Other.SkipBountySuccess.Message = "Your bounty has been transferred to {PLAYER}. You are no longer hunted!";
        Notifications.Other.SkipBountySuccess.IconPath = "Ninjins_Bounty_System/gui/icons/bountycheckmark.edds";
        Notifications.Other.BountySkipped.Enabled = true;
        Notifications.Other.BountySkipped.Title = "Bounty Skipped";
        Notifications.Other.BountySkipped.Message = "You have skipped your bounty. No reward was given.";
        Notifications.Other.BountySkipped.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.RewardHandsNotFree.Enabled = true;
        Notifications.Other.RewardHandsNotFree.Title = "Hands Not Free";
        Notifications.Other.RewardHandsNotFree.Message = "Your hands are not free! Please free your hands and try claiming your reward again.";
        Notifications.Other.RewardHandsNotFree.IconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
        Notifications.Other.PlayerOnCooldown.Enabled = true;
        Notifications.Other.PlayerOnCooldown.Title = "Player On Cooldown";
        Notifications.Other.PlayerOnCooldown.Message = "Cannot place bounty on {PLAYER}. They are on cooldown for {COOLDOWN} more seconds.";
        Notifications.Other.PlayerOnCooldown.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.PlayerInSafeZone.Enabled = true;
        Notifications.Other.PlayerInSafeZone.Title = "Player In SafeZone";
        Notifications.Other.PlayerInSafeZone.Message = "Cannot place bounty on {PLAYER}. {PLAYER} is currently in a safezone.";
        Notifications.Other.PlayerInSafeZone.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.BountyPersisted.Enabled = true;
        Notifications.Other.BountyPersisted.Title = "Bounty Persisted";
        Notifications.Other.BountyPersisted.Message = "Your bounty has persisted. The bounty will continue for {DURATION} more seconds.";
        Notifications.Other.BountyPersisted.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.BountyPausedInTerritory.Enabled = true;
        Notifications.Other.BountyPausedInTerritory.Title = "Bounty Paused";
        Notifications.Other.BountyPausedInTerritory.Message = "You are in your own territory. Your bounty timer is paused until you leave.";
        Notifications.Other.BountyPausedInTerritory.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Notifications.Other.TeleportedOutOfTerritory.Enabled = true;
        Notifications.Other.TeleportedOutOfTerritory.Title = "Teleported Out";
        Notifications.Other.TeleportedOutOfTerritory.Message = "You were teleported out of your own territory. Bountied players cannot stay in their own territory.";
        Notifications.Other.TeleportedOutOfTerritory.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Broadcasts = new BountyBroadcasts();
        Broadcasts.PlacedBounty.Enabled = true;
        Broadcasts.PlacedBounty.Title = "Bounty Placed";
        Broadcasts.PlacedBounty.Message = "A bounty has been placed on {PLAYER} for {DURATION} seconds! Hunt them down!";
        Broadcasts.PlacedBounty.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
        Broadcasts.RuleBreaker.Enabled = true;
        Broadcasts.RuleBreaker.Title = "Rule Violation";
        Broadcasts.RuleBreaker.Message = "{PLAYER} has broken the rules! A rule breaker bounty has been placed on them for {DURATION} seconds!";
        Broadcasts.RuleBreaker.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
    }
    void SaveConfig()
    {
        if (IsMissionClient())
        {
            return;
        }
        CheckDirectories();
        JsonFileLoader<BountyConfig>.JsonSaveFile(Ninjins_Bounty_System_CONFIG_FILE, this);
    }
    void ValidateConfig()
    {
        float temp;
        if (!Map)
            return;
        if (Core)
        {
        }
        if (Map.BountyCircleReduceRadiusOverTime && Map.BountyCircleIncreaseRadiusOverTime)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyConfig] Both BountyCircleReduceRadiusOverTime and BountyCircleIncreaseRadiusOverTime are enabled. Disabling BountyCircleIncreaseRadiusOverTime.");
            Map.BountyCircleIncreaseRadiusOverTime = false;
        }
        if (Map.BountyCircleOffsetMinMultiplier > Map.BountyCircleOffsetMaxMultiplier)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyConfig] BountyCircleOffsetMinMultiplier (" + Map.BountyCircleOffsetMinMultiplier.ToString() + ") is above BountyCircleOffsetMaxMultiplier (" + Map.BountyCircleOffsetMaxMultiplier.ToString() + "). Swapping values.");
            temp = Map.BountyCircleOffsetMinMultiplier;
            Map.BountyCircleOffsetMinMultiplier = Map.BountyCircleOffsetMaxMultiplier;
            Map.BountyCircleOffsetMaxMultiplier = temp;
        }
        if (Map.BountyCircleOffsetMinMultiplier < 0.0)
        {
            Map.BountyCircleOffsetMinMultiplier = 0.0;
        }
        if (Map.BountyCircleOffsetMinMultiplier > 1.0)
        {
            Map.BountyCircleOffsetMinMultiplier = 1.0;
        }
        if (Map.BountyCircleOffsetMaxMultiplier < 0.0)
        {
            Map.BountyCircleOffsetMaxMultiplier = 0.0;
        }
        if (Map.BountyCircleOffsetMaxMultiplier > 1.0)
        {
            Map.BountyCircleOffsetMaxMultiplier = 1.0;
        }
    }
    static BountyConfig LoadConfig()
    {
        if (IsMissionClient())
        {
            return null;
        }
        CheckDirectories();
        BountyConfig config;
        if (FileExist(Ninjins_Bounty_System_CONFIG_FILE))
        {
            config = new BountyConfig();
            JsonFileLoader<BountyConfig>.JsonLoadFile(Ninjins_Bounty_System_CONFIG_FILE, config);
            GetNinjins_Bounty_SystemLogger().LogInfo("BountyConfig loaded from file.");
        }
        else
        {
            config = new BountyConfig();
            GetNinjins_Bounty_SystemLogger().LogInfo("BountyConfig.json not found. Creating default config.");
        }
        config.ValidateConfig();
        config.SaveConfig();
        LogConfigValues(config, false);
        return config;
    }
    static void LogConfigValues(BountyConfig config, bool isReload)
    {
        string prefix;
        if (!config)
            return;
        prefix = "[BountyConfig]";
        if (isReload)
        {
            prefix = "[Reload][BountyConfig]";
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Core System Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.Core)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableBountySystem: " + config.Core.EnableBountySystem.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCooldownSeconds: " + config.Core.BountyCooldownSeconds.ToString() + " (0=no cooldown)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   MaxBountiedPlayers: " + config.Core.MaxBountiedPlayers.ToString() + " (-1=unlimited, 0=disabled, >0=limit)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   MinOnlinePlayersRequired: " + config.Core.MinOnlinePlayersRequired.ToString() + " (0=no requirement, >0=minimum players needed)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   DisableSelfBounty: " + config.Core.DisableSelfBounty.ToString() + " (true=exclude self from list, false=allow self-bounty)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   SkipBountyTokenRequired: " + config.Core.SkipBountyTokenRequired.ToString() + " (0=no tokens required, >0=number of tokens needed)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PlaceBountyTokenRequired: " + config.Core.PlaceBountyTokenRequired.ToString() + " (0=no tokens required, >0=number of tokens needed)");
            if (config.Core.BountyTokenClassNames)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyTokenClassNames: " + config.Core.BountyTokenClassNames.Count().ToString() + " token types configured");
                int tokenIdx;
                for (tokenIdx = 0; tokenIdx < config.Core.BountyTokenClassNames.Count(); tokenIdx++)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "     Token[" + tokenIdx.ToString() + "]: " + config.Core.BountyTokenClassNames.Get(tokenIdx));
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyTokenClassNames: Not configured (using defaults)");
            }
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableConfigReloadSuccessNotification: " + config.Core.EnableConfigReloadSuccessNotification.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableCommandAccessDeniedNotification: " + config.Core.EnableCommandAccessDeniedNotification.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableAutomatedBountyPlacement: " + config.Core.EnableAutomatedBountyPlacement.ToString() + " (true=server automatically places bounties, false=disabled)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   AutomatedBountyPlacementIntervalSeconds: " + config.Core.AutomatedBountyPlacementIntervalSeconds.ToString() + " (interval between automated bounty placements, must be >0 if enabled)");
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Rulebreaker Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.RuleBreaker)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableRuleBreakerHitThreshold: " + config.RuleBreaker.EnableRuleBreakerHitThreshold.ToString() + " (false=instant apply, true=use hit count threshold system)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnablePvEToPvPRuleBreaker: " + config.RuleBreaker.EnablePvEToPvPRuleBreaker.ToString() + " (false=PvE can attack PvP without penalty, true=PvE attacking PvP gets rule breaker bounty)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PvEToPvPInstantRuleBreakerHits: " + config.RuleBreaker.PvEToPvPInstantRuleBreakerHits.ToString() + " (0=use normal hit threshold, 1=instant rulebreaker on first PvE-to-PvP hit)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyRuleBreakerDurationSeconds: " + config.RuleBreaker.BountyRuleBreakerDurationSeconds.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   RuleBreakerHitThresholdTime: " + config.RuleBreaker.RuleBreakerHitThresholdTime.ToString() + " seconds (only used if EnableRuleBreakerHitThreshold is true, 0=apply immediately, >0=time window)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   RuleBreakerHitThresholdWarningHits: " + config.RuleBreaker.RuleBreakerHitThresholdWarningHits.ToString() + " hits (only used if EnableRuleBreakerHitThreshold is true, 0=no warning, >0=hits required for warning)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   RuleBreakerHitThresholdBountyHits: " + config.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + " hits (only used if EnableRuleBreakerHitThreshold is true, must be > RuleBreakerHitThresholdWarningHits)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   AllowPvEToPvEVictimKill: " + config.RuleBreaker.AllowPvEToPvEVictimKill.ToString() + " (false=damage blocked, true=allow victim to be killed while still applying bounty)");
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Placed Bounty Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.PlacedBounty)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyDurationSeconds: " + config.PlacedBounty.BountyDurationSeconds.ToString());
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Reward Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.Reward)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   EnableSurvivalReward: " + config.Reward.EnableSurvivalReward.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PvERuleBreakerGiveRewards: " + config.Reward.PvERuleBreakerGiveRewards.ToString());
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Map Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.Map)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyEnableMapDrawing: " + config.Map.BountyEnableMapDrawing.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleRadius: " + config.Map.BountyCircleRadius.ToString() + "m");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleMinRadius: " + config.Map.BountyCircleMinRadius.ToString() + "m");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleReduceRadiusOverTime: " + config.Map.BountyCircleReduceRadiusOverTime.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleIncreaseRadiusOverTime: " + config.Map.BountyCircleIncreaseRadiusOverTime.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleColor: " + config.Map.BountyCircleColor.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleDrawingWidth: " + config.Map.BountyCircleDrawingWidth.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyMapUpdateIntervalSeconds: " + config.Map.BountyMapUpdateIntervalSeconds.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyMapRequestCooldownSeconds: " + config.Map.BountyMapRequestCooldownSeconds.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyMapSyncIntervalSeconds: " + config.Map.BountyMapSyncIntervalSeconds.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyMapSyncIntervalNoBountiesSeconds: " + config.Map.BountyMapSyncIntervalNoBountiesSeconds.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleOffsetMinMultiplier: " + config.Map.BountyCircleOffsetMinMultiplier.ToString());
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountyCircleOffsetMaxMultiplier: " + config.Map.BountyCircleOffsetMaxMultiplier.ToString());
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " UI Settings:");
        if (config.UI)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetPositionX: " + config.UI.CountdownWidgetPositionX.ToString() + " (pixels, 0=default)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetPositionY: " + config.UI.CountdownWidgetPositionY.ToString() + " (pixels, 0=default)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetWidth: " + config.UI.CountdownWidgetWidth.ToString() + " (relative units 0.0-1.0, 0=layout default)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetHeight: " + config.UI.CountdownWidgetHeight.ToString() + " (relative units 0.0-1.0, 0=layout default)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetBackgroundColor: " + config.UI.CountdownWidgetBackgroundColor.ToString() + " (ARGB integer, 0=layout default, use ARGB calculator)");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   CountdownWidgetTextColor: " + config.UI.CountdownWidgetTextColor.ToString() + " (ARGB integer, 0=layout default, use ARGB calculator, example: -65536 for red)");
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Notification Settings (Nested Structure):");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.Notifications && config.Notifications.PlacedBounty)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " --- PLACED BOUNTY NOTIFICATIONS ---");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Hunted - Enabled: " + config.Notifications.PlacedBounty.Hunted.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.Hunted.Title + ", Message: " + config.Notifications.PlacedBounty.Hunted.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Expired - Enabled: " + config.Notifications.PlacedBounty.Expired.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.Expired.Title + ", Message: " + config.Notifications.PlacedBounty.Expired.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   SurvivalReward - Enabled: " + config.Notifications.PlacedBounty.SurvivalReward.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.SurvivalReward.Title + ", Message: " + config.Notifications.PlacedBounty.SurvivalReward.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   KilledReward - Enabled: " + config.Notifications.PlacedBounty.KilledReward.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.KilledReward.Title + ", Message: " + config.Notifications.PlacedBounty.KilledReward.Message);
        }
        if (config.Notifications && config.Notifications.RuleBreaker)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " --- RULE BREAKER NOTIFICATIONS ---");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Hunted - Enabled: " + config.Notifications.RuleBreaker.Hunted.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.Hunted.Title + ", Message: " + config.Notifications.RuleBreaker.Hunted.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   HitWarning - Enabled: " + config.Notifications.RuleBreaker.HitWarning.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.HitWarning.Title + ", Message: " + config.Notifications.RuleBreaker.HitWarning.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Expired - Enabled: " + config.Notifications.RuleBreaker.Expired.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.Expired.Title + ", Message: " + config.Notifications.RuleBreaker.Expired.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   SurvivalReward - Enabled: " + config.Notifications.RuleBreaker.SurvivalReward.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.SurvivalReward.Title + ", Message: " + config.Notifications.RuleBreaker.SurvivalReward.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   KilledReward - Enabled: " + config.Notifications.RuleBreaker.KilledReward.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.KilledReward.Title + ", Message: " + config.Notifications.RuleBreaker.KilledReward.Message);
        }
        if (config.Notifications && config.Notifications.Other)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " --- OTHER NOTIFICATIONS ---");
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   InsufficientTokens - Enabled: " + config.Notifications.Other.InsufficientTokens.Enabled.ToString() + ", Title: " + config.Notifications.Other.InsufficientTokens.Title + ", Message: " + config.Notifications.Other.InsufficientTokens.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   SkipBountyNoPlayers - Enabled: " + config.Notifications.Other.SkipBountyNoPlayers.Enabled.ToString() + ", Title: " + config.Notifications.Other.SkipBountyNoPlayers.Title + ", Message: " + config.Notifications.Other.SkipBountyNoPlayers.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   SkipBountySuccess - Enabled: " + config.Notifications.Other.SkipBountySuccess.Enabled.ToString() + ", Title: " + config.Notifications.Other.SkipBountySuccess.Title + ", Message: " + config.Notifications.Other.SkipBountySuccess.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   BountySkipped - Enabled: " + config.Notifications.Other.BountySkipped.Enabled.ToString() + ", Title: " + config.Notifications.Other.BountySkipped.Title + ", Message: " + config.Notifications.Other.BountySkipped.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   RewardHandsNotFree - Enabled: " + config.Notifications.Other.RewardHandsNotFree.Enabled.ToString() + ", Title: " + config.Notifications.Other.RewardHandsNotFree.Title + ", Message: " + config.Notifications.Other.RewardHandsNotFree.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PlayerOnCooldown - Enabled: " + config.Notifications.Other.PlayerOnCooldown.Enabled.ToString() + ", Title: " + config.Notifications.Other.PlayerOnCooldown.Title + ", Message: " + config.Notifications.Other.PlayerOnCooldown.Message);
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PlayerInSafeZone - Enabled: " + config.Notifications.Other.PlayerInSafeZone.Enabled.ToString() + ", Title: " + config.Notifications.Other.PlayerInSafeZone.Title + ", Message: " + config.Notifications.Other.PlayerInSafeZone.Message);
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Broadcast Settings (Nested Structure):");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        if (config.Broadcasts && config.Broadcasts.PlacedBounty)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   PlacedBounty - Enabled: " + config.Broadcasts.PlacedBounty.Enabled.ToString() + ", Title: " + config.Broadcasts.PlacedBounty.Title + ", Message: " + config.Broadcasts.PlacedBounty.Message);
        }
        if (config.Broadcasts && config.Broadcasts.RuleBreaker)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   RuleBreaker - Enabled: " + config.Broadcasts.RuleBreaker.Enabled.ToString() + ", Title: " + config.Broadcasts.RuleBreaker.Title + ", Message: " + config.Broadcasts.RuleBreaker.Message);
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
    }
    static bool IsSystemActive()
    {
        array<Man> players;
        int onlinePlayerCount;
        if (!IsMissionHost())
            return false;
        if (!g_BountyConfig || !g_BountyConfig.Core || !g_BountyConfig.Core.EnableBountySystem)
            return false;
        if (g_BountyConfig.Core.MinOnlinePlayersRequired > 0)
        {
            players = new array<Man>();
            g_Game.GetPlayers(players);
            onlinePlayerCount = players.Count();
            if (onlinePlayerCount < g_BountyConfig.Core.MinOnlinePlayersRequired)
            {
                return false;
            }
        }
        return true;
    }
    static void CheckDirectories()
    {
        bool dirCreated;
        bool configDirCreated;
        if (!FileExist(Ninjins_Bounty_System_ROOT_FOLDER))
        {
            dirCreated = MakeDirectory(Ninjins_Bounty_System_ROOT_FOLDER);
            if (dirCreated)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("Created root directory: " + Ninjins_Bounty_System_ROOT_FOLDER);
            }
        }
        if (!FileExist(Ninjins_Bounty_System_CONFIG_DIR))
        {
            configDirCreated = MakeDirectory(Ninjins_Bounty_System_CONFIG_DIR);
            if (configDirCreated)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("Created config directory: " + Ninjins_Bounty_System_CONFIG_DIR);
            }
        }
    }
}
const string Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE = Ninjins_Bounty_System_ROOT_FOLDER + "Config\\BountySuccessRewardConfig.json";
ref BountySuccessRewardConfig g_BountySuccessRewardConfig;
class BountySuccessRewardConfig
{
    bool RuinedContainerAsReward; 
    bool SpawnItemsDirectlyToInventory; 
    ref array<ref BountyRewardSection> BountyRewardItems; 
    ref array<ref BountyCurrencyReward> BountyCurrencyRewards; 
    int CurrencyMin; 
    int CurrencyMax; 
    bool EnableHardlineReputationReward; 
    int HardlineReputationRewardAmount; 
    void BountySuccessRewardConfig()
    {
        RuinedContainerAsReward = true; 
        SpawnItemsDirectlyToInventory = false; 
        BountyRewardItems = new array<ref BountyRewardSection>; 
        CurrencyMin = 1; 
        CurrencyMax = 1; 
        EnableHardlineReputationReward = false; 
        HardlineReputationRewardAmount = 50; 
        BountyRewardSection weaponsSection = new BountyRewardSection;
        weaponsSection.Name = "Weapons";
        weaponsSection.ContainerClassName = "NinjinsBountyCrate_250";
        weaponsSection.SpawnChance = 50.0;
        weaponsSection.ItemsMin = 1;
        weaponsSection.ItemsMax = 2;
        weaponsSection.LootItems = new array<ref BountyRewardItem>;
        BountyRewardItem akmReward = new BountyRewardItem;
        akmReward.ItemClassName = "AKM";
        akmReward.SpawnChance = 100.0;
        akmReward.Amount = 0;
        akmReward.QuantMin = 0.0;
        akmReward.QuantMax = 0.0;
        akmReward.HealthMin = 0.0;
        akmReward.HealthMax = 0.0;
        akmReward.Attachments = new array<ref BountyRewardAttachment>;
        weaponsSection.LootItems.Insert(akmReward);
        BountyRewardItem m4a1Reward = new BountyRewardItem;
        m4a1Reward.ItemClassName = "M4A1";
        m4a1Reward.SpawnChance = 100.0;
        m4a1Reward.Amount = 0;
        m4a1Reward.QuantMin = 0.0;
        m4a1Reward.QuantMax = 0.0;
        m4a1Reward.HealthMin = 0.0;
        m4a1Reward.HealthMax = 0.0;
        m4a1Reward.Attachments = new array<ref BountyRewardAttachment>;
        weaponsSection.LootItems.Insert(m4a1Reward);
        BountyRewardItems.Insert(weaponsSection);
        BountyRewardSection medicalSection = new BountyRewardSection;
        medicalSection.Name = "Medical";
        medicalSection.ContainerClassName = "NinjinsBountyCrate_500";
        medicalSection.SpawnChance = 50.0;
        medicalSection.ItemsMin = 1;
        medicalSection.ItemsMax = 5;
        medicalSection.LootItems = new array<ref BountyRewardItem>;
        BountyRewardItem bandageReward = new BountyRewardItem;
        bandageReward.ItemClassName = "BandageDressing";
        bandageReward.SpawnChance = 100.0;
        bandageReward.Amount = 0;
        bandageReward.QuantMin = 0.0;
        bandageReward.QuantMax = 0.0;
        bandageReward.HealthMin = 0.0;
        bandageReward.HealthMax = 0.0;
        bandageReward.Attachments = new array<ref BountyRewardAttachment>;
        medicalSection.LootItems.Insert(bandageReward);
        BountyRewardItem firstAidKitReward = new BountyRewardItem;
        firstAidKitReward.ItemClassName = "FirstAidKit";
        firstAidKitReward.SpawnChance = 100.0;
        firstAidKitReward.Amount = 0;
        firstAidKitReward.QuantMin = 0.0;
        firstAidKitReward.QuantMax = 0.0;
        firstAidKitReward.HealthMin = 0.0;
        firstAidKitReward.HealthMax = 0.0;
        firstAidKitReward.Attachments = new array<ref BountyRewardAttachment>;
        medicalSection.LootItems.Insert(firstAidKitReward);
        BountyRewardItems.Insert(medicalSection);
        BountyCurrencyRewards = new array<ref BountyCurrencyReward>;
        BountyCurrencyReward hryvniaReward = new BountyCurrencyReward;
        hryvniaReward.ClassName = "";
        hryvniaReward.Amount = 500;
        BountyCurrencyRewards.Insert(hryvniaReward);
        BountyCurrencyReward dollarReward = new BountyCurrencyReward;
        dollarReward.ClassName = "";
        dollarReward.Amount = 1000;
        BountyCurrencyRewards.Insert(dollarReward);
    }
    void SaveConfig()
    {
        if (IsMissionClient())
        {
            return;
        }
        BountyConfig.CheckDirectories();
        JsonFileLoader<BountySuccessRewardConfig>.JsonSaveFile(Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, this);
    }
    static BountySuccessRewardConfig LoadConfig()
    {
        if (IsMissionClient())
        {
            return null;
        }
        BountyConfig.CheckDirectories();
        BountySuccessRewardConfig config;
        if (FileExist(Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE))
        {
            config = new BountySuccessRewardConfig();
            JsonFileLoader<BountySuccessRewardConfig>.JsonLoadFile(Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, config);
            GetNinjins_Bounty_SystemLogger().LogInfo("BountySuccessRewardConfig loaded from file.");
        }
        else
        {
            config = new BountySuccessRewardConfig();
            GetNinjins_Bounty_SystemLogger().LogInfo("BountySuccessRewardConfig.json not found. Creating default config.");
        }
        config.SaveConfig();
        LogConfigValues(config, false);
        return config;
    }
    static void LogConfigValues(BountySuccessRewardConfig config, bool isReload)
    {
        string prefix;
        int itemCount;
        int currencyCount;
        int i;
        BountyCurrencyReward currency;
        if (!config)
            return;
        prefix = "[BountySuccessRewardConfig]";
        if (isReload)
        {
            prefix = "[Reload][BountySuccessRewardConfig]";
        }
        int sectionCount = 0;
        if (config.BountyRewardItems)
        {
            sectionCount = config.BountyRewardItems.Count();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " Success Reward Settings:");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " RuinedContainerAsReward: " + config.RuinedContainerAsReward.ToString() + " (1=ruin after populating, 0=keep full health)");
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " RewardSections Count: " + sectionCount.ToString());
        if (config.BountyRewardItems && sectionCount > 0)
        {
            int sectionIdx;
            BountyRewardSection section;
            for (sectionIdx = 0; sectionIdx < sectionCount; sectionIdx++)
            {
                section = config.BountyRewardItems.Get(sectionIdx);
                if (section)
                {
                    int lootItemCount = 0;
                    if (section.LootItems)
                        lootItemCount = section.LootItems.Count();
                    GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Section [" + sectionIdx.ToString() + "]: " + section.Name + " (Container: " + section.ContainerClassName + ", SpawnChance: " + section.SpawnChance.ToString() + "%, ItemsMin: " + section.ItemsMin.ToString() + ", ItemsMax: " + section.ItemsMax.ToString() + ", LootItems: " + lootItemCount.ToString() + ")");
                }
            }
        }
        currencyCount = 0;
        if (config.BountyCurrencyRewards)
        {
            currencyCount = config.BountyCurrencyRewards.Count();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " BountyCurrencyRewards Count: " + currencyCount.ToString());
        if (config.BountyCurrencyRewards && currencyCount > 0)
        {
            for (i = 0; i < currencyCount; i++)
            {
                currency = config.BountyCurrencyRewards.Get(i);
                if (currency)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo(prefix + "   Currency [" + i.ToString() + "]: " + currency.ClassName + " x" + currency.Amount.ToString());
                }
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo(prefix + " ========================================");
    }
}
const string Ninjins_Bounty_System_ADMIN_CONFIG_FILE = Ninjins_Bounty_System_ROOT_FOLDER + "Config\\Admins.json";
ref BountyAdminConfig g_BountyAdminConfig;
class BountyAdminConfig
{
    ref array<string> AdminGUIDs;
    void BountyAdminConfig()
    {
        AdminGUIDs = new array<string>();
        AdminGUIDs.Insert("ADMIN_GUID_1_HERE_CAN_BE_FOUND_IN_ADMIN_TOOLS_OR_CF_TOOLS");
        AdminGUIDs.Insert("ADMIN_GUID_2_HERE_CAN_BE_FOUND_IN_ADMIN_TOOLS_OR_CF_TOOLS");
    }
    void SaveConfig()
    {
        if (IsMissionClient())
        {
            return;
        }
        BountyConfig.CheckDirectories();
        JsonFileLoader<BountyAdminConfig>.JsonSaveFile(Ninjins_Bounty_System_ADMIN_CONFIG_FILE, this);
    }
    static BountyAdminConfig LoadConfig()
    {
        BountyAdminConfig config;
        int adminCount;
        if (IsMissionClient())
        {
            return null;
        }
        BountyConfig.CheckDirectories();
        config = new BountyAdminConfig();
        if (FileExist(Ninjins_Bounty_System_ADMIN_CONFIG_FILE))
        {
            JsonFileLoader<BountyAdminConfig>.JsonLoadFile(Ninjins_Bounty_System_ADMIN_CONFIG_FILE, config);
            GetNinjins_Bounty_SystemLogger().LogInfo("BountyAdminConfig loaded from file.");
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("Admins.json not found. Creating default admin config.");
        }
        config.SaveConfig();
        BountyAdminConfig.LogConfig(config);
        adminCount = 0;
        if (config && config.AdminGUIDs)
        {
            adminCount = config.AdminGUIDs.Count();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminConfig] Loaded " + adminCount.ToString() + " admin(s).");
        Print("[Bounty System] Loaded " + adminCount.ToString() + " admin(s) from Admins.json");
        return config;
    }
    bool IsAdmin(string guid)
    {
        if (!AdminGUIDs || AdminGUIDs.Count() == 0)
        {
            return false;
        }
        return AdminGUIDs.Find(guid) != -1;
    }
    static void LogConfig(BountyAdminConfig config)
    {
        int i;
        GetNinjins_Bounty_SystemLogger().LogInfo("-------------------------------------");
        GetNinjins_Bounty_SystemLogger().LogInfo("---------  Bounty Admin Settings -----------");
        GetNinjins_Bounty_SystemLogger().LogInfo("-------------------------------------");
        if (config && config.AdminGUIDs)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("AdminGUIDs Count: " + config.AdminGUIDs.Count().ToString());
            for (i = 0; i < config.AdminGUIDs.Count(); i++)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("AdminGUID " + i.ToString() + ": " + config.AdminGUIDs.Get(i));
            }
        }
    }
}
const string Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE = Ninjins_Bounty_System_ROOT_FOLDER + "Config\\Blacklist.json";
ref BountyBlacklistConfig g_BountyBlacklistConfig;
class BountyBlacklistConfig
{
    ref array<string> BlacklistedGUIDs;
    void BountyBlacklistConfig()
    {
        BlacklistedGUIDs = new array<string>();
    }
    void SaveConfig()
    {
        if (IsMissionClient())
        {
            return;
        }
        BountyConfig.CheckDirectories();
        JsonFileLoader<BountyBlacklistConfig>.JsonSaveFile(Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, this);
    }
    static BountyBlacklistConfig LoadConfig()
    {
        BountyBlacklistConfig config;
        int blacklistCount;
        if (IsMissionClient())
        {
            return null;
        }
        BountyConfig.CheckDirectories();
        config = new BountyBlacklistConfig();
        if (FileExist(Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE))
        {
            JsonFileLoader<BountyBlacklistConfig>.JsonLoadFile(Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, config);
            GetNinjins_Bounty_SystemLogger().LogInfo("BountyBlacklistConfig loaded from file.");
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("Blacklist.json not found. Creating default blacklist config.");
        }
        config.SaveConfig();
        BountyBlacklistConfig.LogConfig(config);
        blacklistCount = 0;
        if (config && config.BlacklistedGUIDs)
        {
            blacklistCount = config.BlacklistedGUIDs.Count();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyBlacklistConfig] Loaded " + blacklistCount.ToString() + " blacklisted player(s).");
        Print("[Bounty System] Loaded " + blacklistCount.ToString() + " blacklisted player(s) from Blacklist.json");
        return config;
    }
    bool IsBlacklisted(string guid)
    {
        if (!BlacklistedGUIDs || BlacklistedGUIDs.Count() == 0)
        {
            return false;
        }
        int i;
        string entry;
        int colonIndex;
        string entryGUID;
        for (i = 0; i < BlacklistedGUIDs.Count(); i++)
        {
            entry = BlacklistedGUIDs.Get(i);
            if (entry == guid)
            {
                return true;
            }
            colonIndex = entry.IndexOf(":");
            if (colonIndex >= 0 && colonIndex < entry.Length() - 1)
            {
                entryGUID = entry.Substring(colonIndex + 1, entry.Length() - (colonIndex + 1));
                if (entryGUID == guid)
                {
                    return true;
                }
            }
        }
        return false;
    }
    static void LogConfig(BountyBlacklistConfig config)
    {
        GetNinjins_Bounty_SystemLogger().LogInfo("-------------------------------------");
        GetNinjins_Bounty_SystemLogger().LogInfo("---------  Bounty Blacklist Settings -----------");
        GetNinjins_Bounty_SystemLogger().LogInfo("-------------------------------------");
        if (config && config.BlacklistedGUIDs)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("BlacklistedGUIDs Count: " + config.BlacklistedGUIDs.Count().ToString());
            int i;
            for (i = 0; i < config.BlacklistedGUIDs.Count(); i++)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("BlacklistedGUID " + i.ToString() + ": " + config.BlacklistedGUIDs.Get(i));
            }
        }
    }
}