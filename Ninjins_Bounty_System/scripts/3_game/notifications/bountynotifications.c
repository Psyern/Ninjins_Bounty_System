class BountyNotifications
{
    static void SendNotificationInternal(int type, PlayerIdentity identity, string playerName = "", string victimName = "", float durationSeconds = 0.0, int clearedRewardCount = 0, int currentHits = 0, int bountyHitsThreshold = 0, int tokensRequired = 0, int tokensFound = 0, int cooldownSeconds = 0, string containerClassName = "", string errorDetails = "", float remainingDuration = 0.0, BountyType bountyType = BountyType.PLACED, bool rewardGiven = true)
    {
        string title;
        string message;
        string iconPath;
        string durationStr;
        string clearedRewardsStr;
        string requiredStr;
        string foundStr;
        string cooldownStr;
        int color;
        float duration;
        bool isEnabled;
        array<Man> players;
        int i;
        Man man;
        PlayerIdentity targetIdentity;
        if (!IsMissionHost())
            return;
        if (!identity && type != BOUNTY_NOTIFICATION_PLACED_BROADCAST && type != BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST)
            return;
        title = "";
        message = "";
        iconPath = "";
        color = ARGB(255, 255, 165, 0); 
        duration = 8.0;
        isEnabled = false;
        switch (type)
        {
            case BOUNTY_NOTIFICATION_PLACED_HUNTED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.PlacedBounty && g_BountyConfig.Notifications.PlacedBounty.Hunted && g_BountyConfig.Notifications.PlacedBounty.Hunted.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.PlacedBounty.Hunted.Title != "")
                    title = g_BountyConfig.Notifications.PlacedBounty.Hunted.Title;
                if (g_BountyConfig.Notifications.PlacedBounty.Hunted.Message != "")
                {
                    message = g_BountyConfig.Notifications.PlacedBounty.Hunted.Message;
                    durationStr = Math.Ceil(durationSeconds).ToString();
                    message.Replace("{DURATION}", durationStr);
                }
                if (g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLACED_EXPIRED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.PlacedBounty && g_BountyConfig.Notifications.PlacedBounty.Expired && g_BountyConfig.Notifications.PlacedBounty.Expired.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.PlacedBounty.Expired.Title != "")
                    title = g_BountyConfig.Notifications.PlacedBounty.Expired.Title;
                if (g_BountyConfig.Notifications.PlacedBounty.Expired.Message != "")
                    message = g_BountyConfig.Notifications.PlacedBounty.Expired.Message;
                if (g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD:
            {
                if (bountyType == BountyType.RULE_BREAKER && !rewardGiven)
                {
                    isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker.SurvivalReward && g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Enabled);
                    if (!isEnabled)
                        return;
                    if (g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title != "")
                        title = g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title;
                    if (g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message != "")
                        message = g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message;
                    if (g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath != "")
                        iconPath = g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
                }
                else
                {
                    isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.PlacedBounty && g_BountyConfig.Notifications.PlacedBounty.SurvivalReward && g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Enabled);
                    if (!isEnabled)
                        return;
                    if (g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title != "")
                        title = g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title;
                    if (g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message != "")
                        message = g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message;
                    if (g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath != "")
                        iconPath = g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
                }
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD:
            {
                if (bountyType == BountyType.RULE_BREAKER && !rewardGiven)
                {
                    isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker.KilledReward && g_BountyConfig.Notifications.RuleBreaker.KilledReward.Enabled);
                    if (!isEnabled)
                        return;
                    if (g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title != "")
                        title = g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title;
                    if (g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message != "")
                    {
                        message = g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message;
                        message.Replace("{VICTIM}", victimName);
                    }
                    if (g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath != "")
                        iconPath = g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath;
                }
                else
                {
                    isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.PlacedBounty && g_BountyConfig.Notifications.PlacedBounty.KilledReward && g_BountyConfig.Notifications.PlacedBounty.KilledReward.Enabled);
                    if (!isEnabled)
                        return;
                    if (g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title != "")
                        title = g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title;
                    if (g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message != "")
                    {
                        message = g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message;
                        message.Replace("{VICTIM}", victimName);
                    }
                    if (g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath != "")
                        iconPath = g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath;
                }
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLACED_BROADCAST:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Broadcasts && g_BountyConfig.Broadcasts.PlacedBounty && g_BountyConfig.Broadcasts.PlacedBounty.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Broadcasts.PlacedBounty.Message != "")
                {
                    message = g_BountyConfig.Broadcasts.PlacedBounty.Message;
                    message.Replace("{PLAYER}", playerName);
                    durationStr = Math.Ceil(durationSeconds).ToString();
                    message.Replace("{DURATION}", durationStr);
                }
                if (g_BountyConfig.Broadcasts.PlacedBounty.Title != "")
                    title = g_BountyConfig.Broadcasts.PlacedBounty.Title;
                if (g_BountyConfig.Broadcasts.PlacedBounty.IconPath != "")
                    iconPath = g_BountyConfig.Broadcasts.PlacedBounty.IconPath;
                players = new array<Man>();
                g_Game.GetPlayers(players);
                for (i = 0; i < players.Count(); i++)
                {
                    man = players.Get(i);
                    if (man && man.IsAlive())
                    {
                        targetIdentity = man.GetIdentity();
                        if (targetIdentity)
                        {
                            NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, targetIdentity);
                        }
                    }
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyNotifications] Broadcasted bounty placed notification to " + players.Count().ToString() + " players. Player: " + playerName + ", Duration: " + durationSeconds.ToString() + " seconds");
                break;
            }
            case BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker.Hunted && g_BountyConfig.Notifications.RuleBreaker.Hunted.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.RuleBreaker.Hunted.Title != "")
                    title = g_BountyConfig.Notifications.RuleBreaker.Hunted.Title;
                if (g_BountyConfig.Notifications.RuleBreaker.Hunted.Message != "")
                {
                    message = g_BountyConfig.Notifications.RuleBreaker.Hunted.Message;
                    durationStr = Math.Ceil(durationSeconds).ToString();
                    message.Replace("{DURATION}", durationStr);
                    if (g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty && clearedRewardCount > 0)
                    {
                        clearedRewardsStr = " Cleared Claim Rewards: " + clearedRewardCount.ToString();
                        message.Replace("{CLEARED_REWARDS}", clearedRewardsStr);
                    }
                    else
                    {
                        message.Replace("{CLEARED_REWARDS}", "");
                    }
                }
                if (g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker.Expired && g_BountyConfig.Notifications.RuleBreaker.Expired.Enabled);
                if (!isEnabled)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyNotifications] Rule breaker expiration notification is disabled.");
                    return;
                }
                if (g_BountyConfig.Notifications.RuleBreaker.Expired.Title != "")
                    title = g_BountyConfig.Notifications.RuleBreaker.Expired.Title;
                if (g_BountyConfig.Notifications.RuleBreaker.Expired.Message != "")
                    message = g_BountyConfig.Notifications.RuleBreaker.Expired.Message;
                if (g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath;
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyNotifications] Sending rule breaker bounty expiration notification to " + identity.GetName());
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker.HitWarning && g_BountyConfig.Notifications.RuleBreaker.HitWarning.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title != "")
                    title = g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title;
                if (g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message != "")
                {
                    message = g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message;
                    message.Replace("{HITS}", currentHits.ToString());
                    message.Replace("{BOUNTY_HITS}", bountyHitsThreshold.ToString());
                }
                if (g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath;
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyNotifications] Sending rule breaker hit warning notification to " + identity.GetName() + " (Hits: " + currentHits.ToString() + " / " + bountyHitsThreshold.ToString() + ")");
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Broadcasts && g_BountyConfig.Broadcasts.RuleBreaker && g_BountyConfig.Broadcasts.RuleBreaker.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Broadcasts.RuleBreaker.Message != "")
                {
                    message = g_BountyConfig.Broadcasts.RuleBreaker.Message;
                    message.Replace("{PLAYER}", playerName);
                    durationStr = Math.Ceil(durationSeconds).ToString();
                    message.Replace("{DURATION}", durationStr);
                }
                if (g_BountyConfig.Broadcasts.RuleBreaker.Title != "")
                    title = g_BountyConfig.Broadcasts.RuleBreaker.Title;
                if (g_BountyConfig.Broadcasts.RuleBreaker.IconPath != "")
                    iconPath = g_BountyConfig.Broadcasts.RuleBreaker.IconPath;
                players = new array<Man>();
                g_Game.GetPlayers(players);
                for (i = 0; i < players.Count(); i++)
                {
                    man = players.Get(i);
                    if (man && man.IsAlive())
                    {
                        targetIdentity = man.GetIdentity();
                        if (targetIdentity)
                        {
                            NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, targetIdentity);
                        }
                    }
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyNotifications] Broadcasted rule breaker bounty placed notification to " + players.Count().ToString() + " players. Player: " + playerName + ", Duration: " + durationSeconds.ToString() + " seconds");
                break;
            }
            case BOUNTY_NOTIFICATION_SKIP_SUCCESS:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.SkipBountySuccess && g_BountyConfig.Notifications.Other.SkipBountySuccess.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.SkipBountySuccess.Title != "")
                    title = g_BountyConfig.Notifications.Other.SkipBountySuccess.Title;
                if (g_BountyConfig.Notifications.Other.SkipBountySuccess.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.SkipBountySuccess.Message;
                    message.Replace("{PLAYER}", playerName);
                }
                if (g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.SkipBountyNoPlayers && g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title != "")
                    title = g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title;
                if (g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message != "")
                    message = g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message;
                if (g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_BOUNTY_SKIPPED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.BountySkipped && g_BountyConfig.Notifications.Other.BountySkipped.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.BountySkipped.Title != "")
                    title = g_BountyConfig.Notifications.Other.BountySkipped.Title;
                if (g_BountyConfig.Notifications.Other.BountySkipped.Message != "")
                    message = g_BountyConfig.Notifications.Other.BountySkipped.Message;
                if (g_BountyConfig.Notifications.Other.BountySkipped.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.BountySkipped.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.InsufficientTokens && g_BountyConfig.Notifications.Other.InsufficientTokens.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.InsufficientTokens.Title != "")
                    title = g_BountyConfig.Notifications.Other.InsufficientTokens.Title;
                if (g_BountyConfig.Notifications.Other.InsufficientTokens.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.InsufficientTokens.Message;
                    requiredStr = tokensRequired.ToString();
                    message.Replace("{REQUIRED}", requiredStr);
                    foundStr = tokensFound.ToString();
                    message.Replace("{FOUND}", foundStr);
                }
                if (g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.RewardHandsNotFree && g_BountyConfig.Notifications.Other.RewardHandsNotFree.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title != "")
                    title = g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title;
                if (g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message != "")
                    message = g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message;
                if (g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.PlayerOnCooldown && g_BountyConfig.Notifications.Other.PlayerOnCooldown.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title != "")
                    title = g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title;
                if (g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message;
                    message.Replace("{PLAYER}", playerName);
                    cooldownStr = cooldownSeconds.ToString();
                    message.Replace("{COOLDOWN}", cooldownStr);
                }
                if (g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.PlayerInSafeZone && g_BountyConfig.Notifications.Other.PlayerInSafeZone.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title != "")
                    title = g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title;
                if (g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message;
                    message.Replace("{PLAYER}", playerName);
                }
                if (g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.EnableConfigReloadSuccessNotification);
                if (!isEnabled)
                    return;
                title = "Config Reloaded";
                message = "All bounty system configs have been reloaded successfully from disk. New bounties will use the updated settings.";
                iconPath = "Ninjins_Bounty_System/gui/icons/bountycheckmark.edds";
                color = ARGB(255, 0, 255, 0);
                duration = 5.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE:
            {
                title = "Config Reload Failed";
                message = "Failed to reload one or more config files. Check server logs for details.";
                if (errorDetails != "")
                    message = message + " " + errorDetails;
                iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
                color = ARGB(255, 255, 0, 0);
                duration = 8.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_REWARD_CONTAINER_SPAWN_FAILURE:
            {
                title = "Reward Spawn Failed";
                message = "Your reward container could not be spawned. Your pending reward was kept so you can try again.";
                iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
                color = ARGB(255, 255, 0, 0);
                duration = 8.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_SURVIVAL_REWARD_CONTAINER_SPAWN_FAILURE:
            {
                title = "Reward Spawn Failed";
                message = "Your survival reward container could not be spawned. Your pending reward was kept so you can try again.";
                iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
                color = ARGB(255, 255, 0, 0);
                duration = 8.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.EnableCommandAccessDeniedNotification);
                if (!isEnabled)
                    return;
                title = "Access Denied";
                message = "You do not have permission to use this bounty system command.";
                iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
                color = ARGB(255, 255, 0, 0);
                duration = 5.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_BOUNTY_PERSISTED:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.BountyPersisted && g_BountyConfig.Notifications.Other.BountyPersisted.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.BountyPersisted.Title != "")
                    title = g_BountyConfig.Notifications.Other.BountyPersisted.Title;
                if (g_BountyConfig.Notifications.Other.BountyPersisted.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.BountyPersisted.Message;
                    durationStr = Math.Ceil(remainingDuration).ToString();
                    message.Replace("{DURATION}", durationStr);
                }
                if (g_BountyConfig.Notifications.Other.BountyPersisted.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.BountyPersisted.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory && g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title != "")
                    title = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message != "")
                    message = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.BountyPausedInTerritory && g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title != "")
                    title = g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title;
                if (g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message != "")
                    message = g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message;
                if (g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_BOUNTY_RESUMED_FROM_TERRITORY:
            {
                isEnabled = (g_BountyConfig && g_BountyConfig.Notifications && g_BountyConfig.Notifications.Other && g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory && g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled);
                if (!isEnabled)
                    return;
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title != "")
                    title = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message != "")
                {
                    message = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
                    durationStr = Math.Ceil(remainingDuration).ToString();
                    message.Replace("{DURATION}", durationStr);
                }
                if (g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath != "")
                    iconPath = g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
            case BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL:
            {
                title = "Reward Claim Failed";
                message = "Your inventory is full. Make space for all reward items to claim your reward.";
                iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
                color = ARGB(255, 255, 0, 0); 
                duration = 8.0;
                NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
                break;
            }
        }
    }
}