const string obfv_Ninjins_Bounty_System_CONFIG_DIR = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Config\\";
const string obfv_Ninjins_Bounty_System_CONFIG_FILE = obfv_Ninjins_Bounty_System_CONFIG_DIR + "BountyConfig.json";
ref obfc_BountyConfig obfv_g_BountyConfig;
class obfc_BountyNotificationEntry
{
	bool Enabled;
	string Title;
	string Message;
	string IconPath; 
	void obfc_BountyNotificationEntry()
	{
		Enabled = true;
		Title = "";
		Message = "";
		IconPath = ""; 
	}
}
class obfc_BountyNotificationGroup
{
	ref obfc_BountyNotificationEntry Hunted;
	ref obfc_BountyNotificationEntry Expired;
	ref obfc_BountyNotificationEntry SurvivalReward;
	ref obfc_BountyNotificationEntry KilledReward;
	void obfc_BountyNotificationGroup()
	{
		Hunted = new obfc_BountyNotificationEntry();
		Expired = new obfc_BountyNotificationEntry();
		SurvivalReward = new obfc_BountyNotificationEntry();
		KilledReward = new obfc_BountyNotificationEntry();
	}
}
class obfc_BountyRuleBreakerNotificationGroup
{
	ref obfc_BountyNotificationEntry Hunted;
	ref obfc_BountyNotificationEntry HitWarning; 
	ref obfc_BountyNotificationEntry Expired;
	ref obfc_BountyNotificationEntry SurvivalReward;
	ref obfc_BountyNotificationEntry KilledReward;
	void obfc_BountyRuleBreakerNotificationGroup()
	{
		Hunted = new obfc_BountyNotificationEntry();
		HitWarning = new obfc_BountyNotificationEntry();
		Expired = new obfc_BountyNotificationEntry();
		SurvivalReward = new obfc_BountyNotificationEntry();
		KilledReward = new obfc_BountyNotificationEntry();
	}
}
class obfc_BountyOtherNotifications
{
	ref obfc_BountyNotificationEntry InsufficientTokens;
	ref obfc_BountyNotificationEntry SkipBountyNoPlayers;
	ref obfc_BountyNotificationEntry SkipBountySuccess;
	ref obfc_BountyNotificationEntry BountySkipped;
	ref obfc_BountyNotificationEntry RewardHandsNotFree;
	ref obfc_BountyNotificationEntry PlayerOnCooldown;
	ref obfc_BountyNotificationEntry PlayerInSafeZone; 
	ref obfc_BountyNotificationEntry BountyPersisted; 
	ref obfc_BountyNotificationEntry TeleportedOutOfTerritory; 
	ref obfc_BountyNotificationEntry BountyPausedInTerritory; 
	void obfc_BountyOtherNotifications()
	{
		InsufficientTokens = new obfc_BountyNotificationEntry();
		SkipBountyNoPlayers = new obfc_BountyNotificationEntry();
		SkipBountySuccess = new obfc_BountyNotificationEntry();
		BountySkipped = new obfc_BountyNotificationEntry();
		RewardHandsNotFree = new obfc_BountyNotificationEntry();
		PlayerOnCooldown = new obfc_BountyNotificationEntry();
		PlayerInSafeZone = new obfc_BountyNotificationEntry();
		BountyPersisted = new obfc_BountyNotificationEntry();
		TeleportedOutOfTerritory = new obfc_BountyNotificationEntry();
		BountyPausedInTerritory = new obfc_BountyNotificationEntry();
	}
}
class obfc_BountyBroadcastEntry
{
	bool Enabled;
	string Title;
	string Message;
	string IconPath; 
	void obfc_BountyBroadcastEntry()
	{
		Enabled = true;
		Title = "";
		Message = "";
		IconPath = ""; 
	}
}
class obfc_BountyBroadcasts
{
	ref obfc_BountyBroadcastEntry PlacedBounty;
	ref obfc_BountyBroadcastEntry RuleBreaker;
	void obfc_BountyBroadcasts()
	{
		PlacedBounty = new obfc_BountyBroadcastEntry();
		RuleBreaker = new obfc_BountyBroadcastEntry();
	}
}
class obfc_BountyNotificationConfig
{
	ref obfc_BountyNotificationGroup PlacedBounty;
	ref obfc_BountyRuleBreakerNotificationGroup RuleBreaker;
	ref obfc_BountyOtherNotifications Other;
	void obfc_BountyNotificationConfig()
	{
		PlacedBounty = new obfc_BountyNotificationGroup();
		RuleBreaker = new obfc_BountyRuleBreakerNotificationGroup();
		Other = new obfc_BountyOtherNotifications();
	}
}
class obfc_BountyRewardAttachment
{
	string ItemClassName; 
	float SpawnChance; 
	int Amount; 
	float QuantMin; 
	float QuantMax; 
	float HealthMin; 
	float HealthMax; 
	ref array<ref obfc_BountyRewardAttachment> Attachments; 
	void obfc_BountyRewardAttachment()
	{
		ItemClassName = "";
		SpawnChance = 100.0; 
		Amount = 0; 
		QuantMin = 0.0; 
		QuantMax = 0.0; 
		HealthMin = 0.0; 
		HealthMax = 0.0; 
		Attachments = new array<ref obfc_BountyRewardAttachment>;
	}
}
class obfc_BountyRewardItem
{
	string ItemClassName;
	float SpawnChance; 
	int Amount; 
	float QuantMin; 
	float QuantMax; 
	float HealthMin; 
	float HealthMax; 
	ref array<ref obfc_BountyRewardAttachment> Attachments; 
	void obfc_BountyRewardItem()
	{
		ItemClassName = "";
		SpawnChance = 100.0; 
		Amount = 0; 
		QuantMin = 0.0; 
		QuantMax = 0.0; 
		HealthMin = 0.0; 
		HealthMax = 0.0; 
		Attachments = new array<ref obfc_BountyRewardAttachment>;
	}
}
class obfc_BountyCurrencyReward
{
	string ClassName; 
	float SpawnChance; 
	int Amount; 
	void obfc_BountyCurrencyReward()
	{
		ClassName = "";
		SpawnChance = 100.0; 
		Amount = 0;
	}
}
class obfc_BountyRewardSection
{
	string Name; 
	string ContainerClassName; 
	float SpawnChance; 
	int ItemsMin; 
	int ItemsMax; 
	ref array<ref obfc_BountyRewardItem> LootItems; 
	void obfc_BountyRewardSection()
	{
		Name = "";
		ContainerClassName = "";
		SpawnChance = 100.0; 
		ItemsMin = 1;
		ItemsMax = 1;
		LootItems = new array<ref obfc_BountyRewardItem>;
	}
}
class obfc_BountyCoreSystemSettings
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
	bool obfm_TeleportOutOfOwnTerritory; 
	bool PauseBountyInTerritory; 
	float ResumeBountyDistanceFromTerritory; 
	float PausedBountyResumeCheckInterval; 
	bool obfm_TeleportOutOfSafeZone; 
	float TeleportOutOfSafeZoneDistance; 
	int MinimumPlayerLifetimeSeconds; 
	bool EnableAutomatedBountyPlacement; 
	float AutomatedBountyPlacementIntervalSeconds; 
	void obfc_BountyCoreSystemSettings()
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
		obfm_TeleportOutOfOwnTerritory = true; 
		PauseBountyInTerritory = true; 
		ResumeBountyDistanceFromTerritory = 50.0; 
		PausedBountyResumeCheckInterval = 5.0; 
		obfm_TeleportOutOfSafeZone = true; 
		TeleportOutOfSafeZoneDistance = 150.0; 
		MinimumPlayerLifetimeSeconds = 900; 
		EnableAutomatedBountyPlacement = false; 
		AutomatedBountyPlacementIntervalSeconds = 3600.0; 
	}
}
class obfc_BountyRuleBreakerSettings
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
	void obfc_BountyRuleBreakerSettings()
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
class obfc_BountyPlacedBountySettings
{
	float BountyDurationSeconds; 
	void obfc_BountyPlacedBountySettings()
	{
		BountyDurationSeconds = 60.0;
	}
}
class obfc_BountyRewardSettings
{
	bool EnableSurvivalReward; 
	bool PvERuleBreakerGiveRewards; 
	void obfc_BountyRewardSettings()
	{
		EnableSurvivalReward = true;
		PvERuleBreakerGiveRewards = false; 
	}
}
class obfc_BountyUISettings
{
	float CountdownWidgetPositionX; 
	float CountdownWidgetPositionY; 
	float CountdownWidgetWidth; 
	float CountdownWidgetHeight; 
	int CountdownWidgetBackgroundColor; 
	int CountdownWidgetTextColor; 
	void obfc_BountyUISettings()
	{
		CountdownWidgetPositionX = 0.0; 
		CountdownWidgetPositionY = 0.0; 
		CountdownWidgetWidth = 0.0; 
		CountdownWidgetHeight = 0.0; 
		CountdownWidgetBackgroundColor = 0; 
		CountdownWidgetTextColor = 0; 
	}
}
class obfc_BountyMapSettings
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
	void obfc_BountyMapSettings()
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
class obfc_BountyConfig
{
	ref obfc_BountyCoreSystemSettings Core;
	ref obfc_BountyRuleBreakerSettings RuleBreaker;
	ref obfc_BountyPlacedBountySettings PlacedBounty;
	ref obfc_BountyRewardSettings Reward;
	ref obfc_BountyMapSettings Map;
	ref obfc_BountyUISettings UI;
	ref obfc_BountyNotificationConfig Notifications;
	ref obfc_BountyBroadcasts Broadcasts;
	void obfc_BountyConfig()
	{
		Core = new obfc_BountyCoreSystemSettings();
		RuleBreaker = new obfc_BountyRuleBreakerSettings();
		PlacedBounty = new obfc_BountyPlacedBountySettings();
		Reward = new obfc_BountyRewardSettings();
		Map = new obfc_BountyMapSettings();
		UI = new obfc_BountyUISettings();
		Notifications = new obfc_BountyNotificationConfig();
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
		Broadcasts = new obfc_BountyBroadcasts();
		Broadcasts.PlacedBounty.Enabled = true;
		Broadcasts.PlacedBounty.Title = "Bounty Placed";
		Broadcasts.PlacedBounty.Message = "A bounty has been placed on {PLAYER} for {DURATION} seconds! Hunt them down!";
		Broadcasts.PlacedBounty.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
		Broadcasts.RuleBreaker.Enabled = true;
		Broadcasts.RuleBreaker.Title = "Rule Violation";
		Broadcasts.RuleBreaker.Message = "{PLAYER} has broken the rules! A rule breaker bounty has been placed on them for {DURATION} seconds!";
		Broadcasts.RuleBreaker.IconPath = "Ninjins_Bounty_System/gui/icons/bountyskull.edds";
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
		{
			return;
		}
		obfm_CheckDirectories();
		JsonFileLoader<obfc_BountyConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_CONFIG_FILE, this);
	}
	void obfm_ValidateConfig()
	{
		float temp;
		if (!Map)
			return;
		if (Core)
		{
		}
		if (Map.BountyCircleReduceRadiusOverTime && Map.BountyCircleIncreaseRadiusOverTime)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyConfig] Both BountyCircleReduceRadiusOverTime and BountyCircleIncreaseRadiusOverTime are enabled. Disabling BountyCircleIncreaseRadiusOverTime.");
			Map.BountyCircleIncreaseRadiusOverTime = false;
		}
		if (Map.BountyCircleOffsetMinMultiplier > Map.BountyCircleOffsetMaxMultiplier)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyConfig] BountyCircleOffsetMinMultiplier (" + Map.BountyCircleOffsetMinMultiplier.ToString() + ") is above BountyCircleOffsetMaxMultiplier (" + Map.BountyCircleOffsetMaxMultiplier.ToString() + "). Swapping values.");
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
	static obfc_BountyConfig obfm_LoadConfig()
	{
		if (IsMissionClient())
		{
			return null;
		}
		obfm_CheckDirectories();
		obfc_BountyConfig config;
		if (FileExist(obfv_Ninjins_Bounty_System_CONFIG_FILE))
		{
			config = new obfc_BountyConfig();
			JsonFileLoader<obfc_BountyConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_CONFIG_FILE, config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyConfig loaded from file.");
		}
		else
		{
			config = new obfc_BountyConfig();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyConfig.json not found. Creating default config.");
		}
		config.obfm_ValidateConfig();
		config.obfm_SaveConfig();
		obfm_LogConfigValues(config, false);
		return config;
	}
	static void obfm_LogConfigValues(obfc_BountyConfig config, bool isReload)
	{
		string prefix;
		if (!config)
			return;
		prefix = "[BountyConfig]";
		if (isReload)
		{
			prefix = "[Reload][BountyConfig]";
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Core System Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.Core)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableBountySystem: " + config.Core.EnableBountySystem.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCooldownSeconds: " + config.Core.BountyCooldownSeconds.ToString() + " (0=no cooldown)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   MaxBountiedPlayers: " + config.Core.MaxBountiedPlayers.ToString() + " (-1=unlimited, 0=disabled, >0=limit)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   MinOnlinePlayersRequired: " + config.Core.MinOnlinePlayersRequired.ToString() + " (0=no requirement, >0=minimum players needed)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   DisableSelfBounty: " + config.Core.DisableSelfBounty.ToString() + " (true=exclude self from list, false=allow self-bounty)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   SkipBountyTokenRequired: " + config.Core.SkipBountyTokenRequired.ToString() + " (0=no tokens required, >0=number of tokens needed)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PlaceBountyTokenRequired: " + config.Core.PlaceBountyTokenRequired.ToString() + " (0=no tokens required, >0=number of tokens needed)");
			if (config.Core.BountyTokenClassNames)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyTokenClassNames: " + config.Core.BountyTokenClassNames.Count().ToString() + " token types configured");
				int tokenIdx;
				for (tokenIdx = 0; tokenIdx < config.Core.BountyTokenClassNames.Count(); tokenIdx++)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "     Token[" + tokenIdx.ToString() + "]: " + config.Core.BountyTokenClassNames.Get(tokenIdx));
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyTokenClassNames: Not configured (using defaults)");
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableConfigReloadSuccessNotification: " + config.Core.EnableConfigReloadSuccessNotification.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableCommandAccessDeniedNotification: " + config.Core.EnableCommandAccessDeniedNotification.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableAutomatedBountyPlacement: " + config.Core.EnableAutomatedBountyPlacement.ToString() + " (true=server automatically places bounties, false=disabled)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   AutomatedBountyPlacementIntervalSeconds: " + config.Core.AutomatedBountyPlacementIntervalSeconds.ToString() + " (interval between automated bounty placements, must be >0 if enabled)");
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Rulebreaker Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.RuleBreaker)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableRuleBreakerHitThreshold: " + config.RuleBreaker.EnableRuleBreakerHitThreshold.ToString() + " (false=instant apply, true=use hit count threshold system)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnablePvEToPvPRuleBreaker: " + config.RuleBreaker.EnablePvEToPvPRuleBreaker.ToString() + " (false=PvE can attack PvP without penalty, true=PvE attacking PvP gets rule breaker bounty)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PvEToPvPInstantRuleBreakerHits: " + config.RuleBreaker.PvEToPvPInstantRuleBreakerHits.ToString() + " (0=use normal hit threshold, 1=instant rulebreaker on first PvE-to-PvP hit)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyRuleBreakerDurationSeconds: " + config.RuleBreaker.BountyRuleBreakerDurationSeconds.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   RuleBreakerHitThresholdTime: " + config.RuleBreaker.RuleBreakerHitThresholdTime.ToString() + " seconds (only used if EnableRuleBreakerHitThreshold is true, 0=apply immediately, >0=time window)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   RuleBreakerHitThresholdWarningHits: " + config.RuleBreaker.RuleBreakerHitThresholdWarningHits.ToString() + " hits (only used if EnableRuleBreakerHitThreshold is true, 0=no warning, >0=hits required for warning)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   RuleBreakerHitThresholdBountyHits: " + config.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + " hits (only used if EnableRuleBreakerHitThreshold is true, must be > RuleBreakerHitThresholdWarningHits)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   AllowPvEToPvEVictimKill: " + config.RuleBreaker.AllowPvEToPvEVictimKill.ToString() + " (false=damage blocked, true=allow victim to be killed while still applying bounty)");
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Placed Bounty Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.PlacedBounty)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyDurationSeconds: " + config.PlacedBounty.BountyDurationSeconds.ToString());
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Reward Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.Reward)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   EnableSurvivalReward: " + config.Reward.EnableSurvivalReward.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PvERuleBreakerGiveRewards: " + config.Reward.PvERuleBreakerGiveRewards.ToString());
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Map Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.Map)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyEnableMapDrawing: " + config.Map.BountyEnableMapDrawing.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleRadius: " + config.Map.BountyCircleRadius.ToString() + "m");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleMinRadius: " + config.Map.BountyCircleMinRadius.ToString() + "m");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleReduceRadiusOverTime: " + config.Map.BountyCircleReduceRadiusOverTime.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleIncreaseRadiusOverTime: " + config.Map.BountyCircleIncreaseRadiusOverTime.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleColor: " + config.Map.BountyCircleColor.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleDrawingWidth: " + config.Map.BountyCircleDrawingWidth.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyMapUpdateIntervalSeconds: " + config.Map.BountyMapUpdateIntervalSeconds.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyMapRequestCooldownSeconds: " + config.Map.BountyMapRequestCooldownSeconds.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyMapSyncIntervalSeconds: " + config.Map.BountyMapSyncIntervalSeconds.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyMapSyncIntervalNoBountiesSeconds: " + config.Map.BountyMapSyncIntervalNoBountiesSeconds.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleOffsetMinMultiplier: " + config.Map.BountyCircleOffsetMinMultiplier.ToString());
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountyCircleOffsetMaxMultiplier: " + config.Map.BountyCircleOffsetMaxMultiplier.ToString());
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " UI Settings:");
		if (config.UI)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetPositionX: " + config.UI.CountdownWidgetPositionX.ToString() + " (pixels, 0=default)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetPositionY: " + config.UI.CountdownWidgetPositionY.ToString() + " (pixels, 0=default)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetWidth: " + config.UI.CountdownWidgetWidth.ToString() + " (relative units 0.0-1.0, 0=layout default)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetHeight: " + config.UI.CountdownWidgetHeight.ToString() + " (relative units 0.0-1.0, 0=layout default)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetBackgroundColor: " + config.UI.CountdownWidgetBackgroundColor.ToString() + " (ARGB integer, 0=layout default, use ARGB calculator)");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   CountdownWidgetTextColor: " + config.UI.CountdownWidgetTextColor.ToString() + " (ARGB integer, 0=layout default, use ARGB calculator, example: -65536 for red)");
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Notification Settings (Nested Structure):");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.Notifications && config.Notifications.PlacedBounty)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " --- PLACED BOUNTY NOTIFICATIONS ---");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Hunted - Enabled: " + config.Notifications.PlacedBounty.Hunted.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.Hunted.Title + ", Message: " + config.Notifications.PlacedBounty.Hunted.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Expired - Enabled: " + config.Notifications.PlacedBounty.Expired.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.Expired.Title + ", Message: " + config.Notifications.PlacedBounty.Expired.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   SurvivalReward - Enabled: " + config.Notifications.PlacedBounty.SurvivalReward.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.SurvivalReward.Title + ", Message: " + config.Notifications.PlacedBounty.SurvivalReward.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   KilledReward - Enabled: " + config.Notifications.PlacedBounty.KilledReward.Enabled.ToString() + ", Title: " + config.Notifications.PlacedBounty.KilledReward.Title + ", Message: " + config.Notifications.PlacedBounty.KilledReward.Message);
		}
		if (config.Notifications && config.Notifications.RuleBreaker)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " --- RULE BREAKER NOTIFICATIONS ---");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Hunted - Enabled: " + config.Notifications.RuleBreaker.Hunted.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.Hunted.Title + ", Message: " + config.Notifications.RuleBreaker.Hunted.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   HitWarning - Enabled: " + config.Notifications.RuleBreaker.HitWarning.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.HitWarning.Title + ", Message: " + config.Notifications.RuleBreaker.HitWarning.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Expired - Enabled: " + config.Notifications.RuleBreaker.Expired.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.Expired.Title + ", Message: " + config.Notifications.RuleBreaker.Expired.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   SurvivalReward - Enabled: " + config.Notifications.RuleBreaker.SurvivalReward.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.SurvivalReward.Title + ", Message: " + config.Notifications.RuleBreaker.SurvivalReward.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   KilledReward - Enabled: " + config.Notifications.RuleBreaker.KilledReward.Enabled.ToString() + ", Title: " + config.Notifications.RuleBreaker.KilledReward.Title + ", Message: " + config.Notifications.RuleBreaker.KilledReward.Message);
		}
		if (config.Notifications && config.Notifications.Other)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " --- OTHER NOTIFICATIONS ---");
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   InsufficientTokens - Enabled: " + config.Notifications.Other.InsufficientTokens.Enabled.ToString() + ", Title: " + config.Notifications.Other.InsufficientTokens.Title + ", Message: " + config.Notifications.Other.InsufficientTokens.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   SkipBountyNoPlayers - Enabled: " + config.Notifications.Other.SkipBountyNoPlayers.Enabled.ToString() + ", Title: " + config.Notifications.Other.SkipBountyNoPlayers.Title + ", Message: " + config.Notifications.Other.SkipBountyNoPlayers.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   SkipBountySuccess - Enabled: " + config.Notifications.Other.SkipBountySuccess.Enabled.ToString() + ", Title: " + config.Notifications.Other.SkipBountySuccess.Title + ", Message: " + config.Notifications.Other.SkipBountySuccess.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   BountySkipped - Enabled: " + config.Notifications.Other.BountySkipped.Enabled.ToString() + ", Title: " + config.Notifications.Other.BountySkipped.Title + ", Message: " + config.Notifications.Other.BountySkipped.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   RewardHandsNotFree - Enabled: " + config.Notifications.Other.RewardHandsNotFree.Enabled.ToString() + ", Title: " + config.Notifications.Other.RewardHandsNotFree.Title + ", Message: " + config.Notifications.Other.RewardHandsNotFree.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PlayerOnCooldown - Enabled: " + config.Notifications.Other.PlayerOnCooldown.Enabled.ToString() + ", Title: " + config.Notifications.Other.PlayerOnCooldown.Title + ", Message: " + config.Notifications.Other.PlayerOnCooldown.Message);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PlayerInSafeZone - Enabled: " + config.Notifications.Other.PlayerInSafeZone.Enabled.ToString() + ", Title: " + config.Notifications.Other.PlayerInSafeZone.Title + ", Message: " + config.Notifications.Other.PlayerInSafeZone.Message);
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Broadcast Settings (Nested Structure):");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		if (config.Broadcasts && config.Broadcasts.PlacedBounty)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   PlacedBounty - Enabled: " + config.Broadcasts.PlacedBounty.Enabled.ToString() + ", Title: " + config.Broadcasts.PlacedBounty.Title + ", Message: " + config.Broadcasts.PlacedBounty.Message);
		}
		if (config.Broadcasts && config.Broadcasts.RuleBreaker)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   RuleBreaker - Enabled: " + config.Broadcasts.RuleBreaker.Enabled.ToString() + ", Title: " + config.Broadcasts.RuleBreaker.Title + ", Message: " + config.Broadcasts.RuleBreaker.Message);
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
	}
	static bool obfm_IsSystemActive()
	{
		array<Man> players;
		int onlinePlayerCount;
		if (!IsMissionHost())
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		if (obfv_g_BountyConfig.Core.MinOnlinePlayersRequired > 0)
		{
			players = new array<Man>();
			g_Game.GetPlayers(players);
			onlinePlayerCount = players.Count();
			if (onlinePlayerCount < obfv_g_BountyConfig.Core.MinOnlinePlayersRequired)
			{
				return false;
			}
		}
		return true;
	}
	static void obfm_CheckDirectories()
	{
		bool dirCreated;
		bool configDirCreated;
		if (!FileExist(obfv_Ninjins_Bounty_System_ROOT_FOLDER))
		{
			dirCreated = MakeDirectory(obfv_Ninjins_Bounty_System_ROOT_FOLDER);
			if (dirCreated)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Created root directory: " + obfv_Ninjins_Bounty_System_ROOT_FOLDER);
			}
		}
		if (!FileExist(obfv_Ninjins_Bounty_System_CONFIG_DIR))
		{
			configDirCreated = MakeDirectory(obfv_Ninjins_Bounty_System_CONFIG_DIR);
			if (configDirCreated)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Created config directory: " + obfv_Ninjins_Bounty_System_CONFIG_DIR);
			}
		}
	}
}
const string obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Config\\BountySuccessRewardConfig.json";
ref obfc_BountySuccessRewardConfig obfv_g_BountySuccessRewardConfig;
class obfc_BountySuccessRewardConfig
{
	bool RuinedContainerAsReward; 
	bool SpawnItemsDirectlyToInventory; 
	ref array<ref obfc_BountyRewardSection> BountyRewardItems; 
	ref array<ref obfc_BountyCurrencyReward> BountyCurrencyRewards; 
	int CurrencyMin; 
	int CurrencyMax; 
	bool EnableHardlineReputationReward; 
	int HardlineReputationRewardAmount; 
	void obfc_BountySuccessRewardConfig()
	{
		RuinedContainerAsReward = true; 
		SpawnItemsDirectlyToInventory = false; 
		BountyRewardItems = new array<ref obfc_BountyRewardSection>; 
		CurrencyMin = 1; 
		CurrencyMax = 1; 
		EnableHardlineReputationReward = false; 
		HardlineReputationRewardAmount = 50; 
		obfc_BountyRewardSection weaponsSection = new obfc_BountyRewardSection;
		weaponsSection.Name = "Weapons";
		weaponsSection.ContainerClassName = "NinjinsBountyCrate_250";
		weaponsSection.SpawnChance = 50.0;
		weaponsSection.ItemsMin = 1;
		weaponsSection.ItemsMax = 2;
		weaponsSection.LootItems = new array<ref obfc_BountyRewardItem>;
		obfc_BountyRewardItem akmReward = new obfc_BountyRewardItem;
		akmReward.ItemClassName = "AKM";
		akmReward.SpawnChance = 100.0;
		akmReward.Amount = 0;
		akmReward.QuantMin = 0.0;
		akmReward.QuantMax = 0.0;
		akmReward.HealthMin = 0.0;
		akmReward.HealthMax = 0.0;
		akmReward.Attachments = new array<ref obfc_BountyRewardAttachment>;
		weaponsSection.LootItems.Insert(akmReward);
		obfc_BountyRewardItem m4a1Reward = new obfc_BountyRewardItem;
		m4a1Reward.ItemClassName = "M4A1";
		m4a1Reward.SpawnChance = 100.0;
		m4a1Reward.Amount = 0;
		m4a1Reward.QuantMin = 0.0;
		m4a1Reward.QuantMax = 0.0;
		m4a1Reward.HealthMin = 0.0;
		m4a1Reward.HealthMax = 0.0;
		m4a1Reward.Attachments = new array<ref obfc_BountyRewardAttachment>;
		weaponsSection.LootItems.Insert(m4a1Reward);
		BountyRewardItems.Insert(weaponsSection);
		obfc_BountyRewardSection medicalSection = new obfc_BountyRewardSection;
		medicalSection.Name = "Medical";
		medicalSection.ContainerClassName = "NinjinsBountyCrate_500";
		medicalSection.SpawnChance = 50.0;
		medicalSection.ItemsMin = 1;
		medicalSection.ItemsMax = 5;
		medicalSection.LootItems = new array<ref obfc_BountyRewardItem>;
		obfc_BountyRewardItem bandageReward = new obfc_BountyRewardItem;
		bandageReward.ItemClassName = "BandageDressing";
		bandageReward.SpawnChance = 100.0;
		bandageReward.Amount = 0;
		bandageReward.QuantMin = 0.0;
		bandageReward.QuantMax = 0.0;
		bandageReward.HealthMin = 0.0;
		bandageReward.HealthMax = 0.0;
		bandageReward.Attachments = new array<ref obfc_BountyRewardAttachment>;
		medicalSection.LootItems.Insert(bandageReward);
		obfc_BountyRewardItem firstAidKitReward = new obfc_BountyRewardItem;
		firstAidKitReward.ItemClassName = "FirstAidKit";
		firstAidKitReward.SpawnChance = 100.0;
		firstAidKitReward.Amount = 0;
		firstAidKitReward.QuantMin = 0.0;
		firstAidKitReward.QuantMax = 0.0;
		firstAidKitReward.HealthMin = 0.0;
		firstAidKitReward.HealthMax = 0.0;
		firstAidKitReward.Attachments = new array<ref obfc_BountyRewardAttachment>;
		medicalSection.LootItems.Insert(firstAidKitReward);
		BountyRewardItems.Insert(medicalSection);
		BountyCurrencyRewards = new array<ref obfc_BountyCurrencyReward>;
		obfc_BountyCurrencyReward hryvniaReward = new obfc_BountyCurrencyReward;
		hryvniaReward.ClassName = "";
		hryvniaReward.Amount = 500;
		BountyCurrencyRewards.Insert(hryvniaReward);
		obfc_BountyCurrencyReward dollarReward = new obfc_BountyCurrencyReward;
		dollarReward.ClassName = "";
		dollarReward.Amount = 1000;
		BountyCurrencyRewards.Insert(dollarReward);
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
		{
			return;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		JsonFileLoader<obfc_BountySuccessRewardConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, this);
	}
	static obfc_BountySuccessRewardConfig obfm_LoadConfig()
	{
		if (IsMissionClient())
		{
			return null;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		obfc_BountySuccessRewardConfig config;
		if (FileExist(obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE))
		{
			config = new obfc_BountySuccessRewardConfig();
			JsonFileLoader<obfc_BountySuccessRewardConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountySuccessRewardConfig loaded from file.");
		}
		else
		{
			config = new obfc_BountySuccessRewardConfig();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountySuccessRewardConfig.json not found. Creating default config.");
		}
		config.obfm_SaveConfig();
		obfm_LogConfigValues(config, false);
		return config;
	}
	static void obfm_LogConfigValues(obfc_BountySuccessRewardConfig config, bool isReload)
	{
		string prefix;
		int itemCount;
		int currencyCount;
		int i;
		obfc_BountyCurrencyReward currency;
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
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " Success Reward Settings:");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " RuinedContainerAsReward: " + config.RuinedContainerAsReward.ToString() + " (1=ruin after populating, 0=keep full health)");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " RewardSections Count: " + sectionCount.ToString());
		if (config.BountyRewardItems && sectionCount > 0)
		{
			int sectionIdx;
			obfc_BountyRewardSection section;
			for (sectionIdx = 0; sectionIdx < sectionCount; sectionIdx++)
			{
				section = config.BountyRewardItems.Get(sectionIdx);
				if (section)
				{
					int lootItemCount = 0;
					if (section.LootItems)
						lootItemCount = section.LootItems.Count();
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Section [" + sectionIdx.ToString() + "]: " + section.Name + " (Container: " + section.ContainerClassName + ", SpawnChance: " + section.SpawnChance.ToString() + "%, ItemsMin: " + section.ItemsMin.ToString() + ", ItemsMax: " + section.ItemsMax.ToString() + ", LootItems: " + lootItemCount.ToString() + ")");
				}
			}
		}
		currencyCount = 0;
		if (config.BountyCurrencyRewards)
		{
			currencyCount = config.BountyCurrencyRewards.Count();
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " BountyCurrencyRewards Count: " + currencyCount.ToString());
		if (config.BountyCurrencyRewards && currencyCount > 0)
		{
			for (i = 0; i < currencyCount; i++)
			{
				currency = config.BountyCurrencyRewards.Get(i);
				if (currency)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Currency [" + i.ToString() + "]: " + currency.ClassName + " x" + currency.Amount.ToString());
				}
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
	}
}
const string obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Config\\Admins.json";
ref obfc_BountyAdminConfig obfv_g_BountyAdminConfig;
class obfc_BountyAdminConfig
{
	ref array<string> AdminGUIDs;
	void obfc_BountyAdminConfig()
	{
		AdminGUIDs = new array<string>();
		AdminGUIDs.Insert("ADMIN_GUID_OR_STEAMID64_1_HERE_BOTH_FORMATS_ARE_ACCEPTED");
		AdminGUIDs.Insert("ADMIN_GUID_OR_STEAMID64_2_HERE_BOTH_FORMATS_ARE_ACCEPTED");
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
		{
			return;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		JsonFileLoader<obfc_BountyAdminConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE, this);
	}
	static obfc_BountyAdminConfig obfm_LoadConfig()
	{
		obfc_BountyAdminConfig config;
		int adminCount;
		if (IsMissionClient())
		{
			return null;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		config = new obfc_BountyAdminConfig();
		if (FileExist(obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE))
		{
			JsonFileLoader<obfc_BountyAdminConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE, config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyAdminConfig loaded from file.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Admins.json not found. Creating default admin config.");
		}
		config.obfm_SaveConfig();
		obfc_BountyAdminConfig.obfm_LogConfig(config);
		adminCount = 0;
		if (config && config.AdminGUIDs)
		{
			adminCount = config.AdminGUIDs.Count();
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminConfig] Loaded " + adminCount.ToString() + " admin(s).");
		Print("[Bounty System] Loaded " + adminCount.ToString() + " admin(s) from Admins.json");
		return config;
	}
	bool obfm_IsAdmin(string guid)
	{
		if (!AdminGUIDs || AdminGUIDs.Count() == 0)
		{
			return false;
		}
		return AdminGUIDs.Find(guid) != -1;
	}
	//! Accepts both the hashed DayZ GUID (GetId) and the plaintext SteamID64 (GetPlainId)
	bool obfm_IsAdminIdentity(PlayerIdentity identity)
	{
		if (!identity)
		{
			return false;
		}
		if (obfm_IsAdmin(identity.GetId()))
		{
			return true;
		}
		return obfm_IsAdmin(identity.GetPlainId());
	}
	static void obfm_LogConfig(obfc_BountyAdminConfig config)
	{
		int i;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("-------------------------------------");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("---------  Bounty Admin Settings -----------");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("-------------------------------------");
		if (config && config.AdminGUIDs)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("AdminGUIDs Count: " + config.AdminGUIDs.Count().ToString());
			for (i = 0; i < config.AdminGUIDs.Count(); i++)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("AdminGUID " + i.ToString() + ": " + config.AdminGUIDs.Get(i));
			}
		}
	}
}
const string obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Config\\Blacklist.json";
ref obfc_BountyBlacklistConfig obfv_g_BountyBlacklistConfig;
class obfc_BountyBlacklistConfig
{
	ref array<string> BlacklistedGUIDs;
	void obfc_BountyBlacklistConfig()
	{
		BlacklistedGUIDs = new array<string>();
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
		{
			return;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		JsonFileLoader<obfc_BountyBlacklistConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, this);
	}
	static obfc_BountyBlacklistConfig obfm_LoadConfig()
	{
		obfc_BountyBlacklistConfig config;
		int blacklistCount;
		if (IsMissionClient())
		{
			return null;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		config = new obfc_BountyBlacklistConfig();
		if (FileExist(obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE))
		{
			JsonFileLoader<obfc_BountyBlacklistConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyBlacklistConfig loaded from file.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Blacklist.json not found. Creating default blacklist config.");
		}
		config.obfm_SaveConfig();
		obfc_BountyBlacklistConfig.obfm_LogConfig(config);
		blacklistCount = 0;
		if (config && config.BlacklistedGUIDs)
		{
			blacklistCount = config.BlacklistedGUIDs.Count();
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyBlacklistConfig] Loaded " + blacklistCount.ToString() + " blacklisted player(s).");
		Print("[Bounty System] Loaded " + blacklistCount.ToString() + " blacklisted player(s) from Blacklist.json");
		return config;
	}
	bool obfm_IsBlacklisted(string guid)
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
	//! Accepts both the hashed DayZ GUID (GetId) and the plaintext SteamID64 (GetPlainId)
	bool obfm_IsBlacklistedIdentity(PlayerIdentity identity)
	{
		if (!identity)
		{
			return false;
		}
		if (obfm_IsBlacklisted(identity.GetId()))
		{
			return true;
		}
		return obfm_IsBlacklisted(identity.GetPlainId());
	}
	static void obfm_LogConfig(obfc_BountyBlacklistConfig config)
	{
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("-------------------------------------");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("---------  Bounty Blacklist Settings -----------");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("-------------------------------------");
		if (config && config.BlacklistedGUIDs)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BlacklistedGUIDs Count: " + config.BlacklistedGUIDs.Count().ToString());
			int i;
			for (i = 0; i < config.BlacklistedGUIDs.Count(); i++)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BlacklistedGUID " + i.ToString() + ": " + config.BlacklistedGUIDs.Get(i));
			}
		}
	}
}
const string obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Config\\BountyBoardPlacements.json";
ref obfc_BountyBoardPlacementConfig obfv_g_BountyBoardPlacementConfig;
class obfc_BountyBoardPlacement
{
	ref array<float> Position;
	ref array<float> Rotation;
	void obfc_BountyBoardPlacement()
	{
		Position = new array<float>;
		Position.Insert(0.0);
		Position.Insert(0.0);
		Position.Insert(0.0);
		Rotation = new array<float>;
		Rotation.Insert(0.0);
		Rotation.Insert(0.0);
		Rotation.Insert(0.0);
	}
}
class obfc_BountyBoardPlacementConfig
{
	int VersionID;
	ref array<ref obfc_BountyBoardPlacement> BoardPlacements;
	void obfc_BountyBoardPlacementConfig()
	{
		VersionID = 1;
		BoardPlacements = new array<ref obfc_BountyBoardPlacement>;
		BoardPlacements.Insert(new obfc_BountyBoardPlacement());
	}
	void obfm_SaveConfig()
	{
		if (IsMissionClient())
		{
			return;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		JsonFileLoader<obfc_BountyBoardPlacementConfig>.JsonSaveFile(obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE, this);
	}
	void obfm_ValidateConfig()
	{
		int i;
		obfc_BountyBoardPlacement placement;
		if (VersionID <= 0)
		{
			VersionID = 1;
		}
		if (!BoardPlacements)
		{
			BoardPlacements = new array<ref obfc_BountyBoardPlacement>;
		}
		for (i = 0; i < BoardPlacements.Count(); i++)
		{
			placement = BoardPlacements.Get(i);
			if (!placement)
			{
				placement = new obfc_BountyBoardPlacement();
				BoardPlacements.Set(i, placement);
			}
			if (!placement.Position)
			{
				placement.Position = new array<float>;
			}
			if (!placement.Rotation)
			{
				placement.Rotation = new array<float>;
			}
			while (placement.Position.Count() < 3)
			{
				placement.Position.Insert(0.0);
			}
			while (placement.Rotation.Count() < 3)
			{
				placement.Rotation.Insert(0.0);
			}
		}
	}
	static obfc_BountyBoardPlacementConfig obfm_LoadConfig()
	{
		obfc_BountyBoardPlacementConfig config;
		if (IsMissionClient())
		{
			return null;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		config = new obfc_BountyBoardPlacementConfig();
		if (FileExist(obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE))
		{
			JsonFileLoader<obfc_BountyBoardPlacementConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE, config);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyBoardPlacements.json loaded from file.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyBoardPlacements.json not found. Creating default board placement config.");
		}
		config.obfm_ValidateConfig();
		config.obfm_SaveConfig();
		obfm_LogConfig(config, false);
		return config;
	}
	static void obfm_LogConfig(obfc_BountyBoardPlacementConfig config, bool isReload)
	{
		string prefix;
		int i;
		obfc_BountyBoardPlacement placement;
		prefix = "[BountyBoardPlacementConfig]";
		if (isReload)
		{
			prefix = "[Reload][BountyBoardPlacementConfig]";
		}
		if (!config)
			return;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " VersionID: " + config.VersionID.ToString());
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " BoardPlacements Count: " + config.BoardPlacements.Count().ToString());
		for (i = 0; i < config.BoardPlacements.Count(); i++)
		{
			placement = config.BoardPlacements.Get(i);
			if (!placement)
				continue;
			if (!placement.Position || placement.Position.Count() < 3)
				continue;
			if (!placement.Rotation || placement.Rotation.Count() < 3)
				continue;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + "   Board[" + i.ToString() + "] Position: [" + placement.Position.Get(0).ToString() + ", " + placement.Position.Get(1).ToString() + ", " + placement.Position.Get(2).ToString() + "] Rotation: [" + placement.Rotation.Get(0).ToString() + ", " + placement.Rotation.Get(1).ToString() + ", " + placement.Rotation.Get(2).ToString() + "]");
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo(prefix + " ========================================");
	}
}