class obfc_BountyNotifications
{
	static bool obfm_IsBroadcastType(int type)
	{
		if (type == obfv_BOUNTY_NOTIFICATION_PLACED_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_EXPIRED_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_WIN_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_SUICIDE_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_LOGOUT_BROADCAST)
			return true;
		if (type == obfv_BOUNTY_NOTIFICATION_WARNING_BROADCAST)
			return true;
		return false;
	}
	//! Sends an already resolved title/message to every connected player.
	static void obfm_BroadcastToAll(string title, string message, string iconPath, int color, float duration)
	{
		array<Man> players;
		int i;
		Man man;
		PlayerIdentity targetIdentity;
		players = new array<Man>();
		g_Game.GetPlayers(players);
		for (i = 0; i < players.Count(); i++)
		{
			man = players.Get(i);
			if (!man)
				continue;
			targetIdentity = man.GetIdentity();
			if (!targetIdentity)
				continue;
			NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, targetIdentity);
		}
	}
	static void obfm_SendNotificationInternal(int type, PlayerIdentity identity, string playerName = "", string victimName = "", float durationSeconds = 0.0, int clearedRewardCount = 0, int currentHits = 0, int bountyHitsThreshold = 0, int tokensRequired = 0, int tokensFound = 0, int cooldownSeconds = 0, string containerClassName = "", string errorDetails = "", float remainingDuration = 0.0, BountyType bountyType = BountyType.PLACED, bool rewardGiven = true, string winnerName = "")
	{
		string title;
		string message;
		string iconPath;
		string durationStr;
		string clearedRewardsStr;
		string requiredStr;
		string foundStr;
		string cooldownStr;
		string suicidePhrase;
		int color;
		float duration;
		bool isEnabled;
		array<Man> players;
		int i;
		Man man;
		PlayerIdentity targetIdentity;
		if (!IsMissionHost())
			return;
		if (!identity && !obfm_IsBroadcastType(type))
			return;
		title = "";
		message = "";
		iconPath = "";
		color = ARGB(255, 255, 165, 0); 
		duration = 8.0;
		isEnabled = false;
		switch (type)
		{
			case obfv_BOUNTY_NOTIFICATION_PLACED_HUNTED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.PlacedBounty && obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted && obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Title != "")
					title = obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Title;
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Message;
					durationStr = Math.Ceil(durationSeconds).ToString();
					message.Replace("{DURATION}", durationStr);
				}
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLACED_EXPIRED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.PlacedBounty && obfv_g_BountyConfig.Notifications.PlacedBounty.Expired && obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Title != "")
					title = obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Title;
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Message != "")
					message = obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Message;
				if (obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD:
			{
				if (bountyType == BountyType.RULE_BREAKER && !rewardGiven)
				{
					isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward && obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Enabled);
					if (!isEnabled)
						return;
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title != "")
						title = obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title;
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message != "")
						message = obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message;
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath != "")
						iconPath = obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
				}
				else
				{
					isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.PlacedBounty && obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward && obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Enabled);
					if (!isEnabled)
						return;
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title != "")
						title = obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title;
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message != "")
						message = obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message;
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath != "")
						iconPath = obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
				}
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD:
			{
				if (bountyType == BountyType.RULE_BREAKER && !rewardGiven)
				{
					isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward && obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Enabled);
					if (!isEnabled)
						return;
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title != "")
						title = obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title;
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message != "")
					{
						message = obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message;
						message.Replace("{VICTIM}", victimName);
					}
					if (obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath != "")
						iconPath = obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath;
				}
				else
				{
					isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.PlacedBounty && obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward && obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Enabled);
					if (!isEnabled)
						return;
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title != "")
						title = obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title;
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message != "")
					{
						message = obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message;
						message.Replace("{VICTIM}", victimName);
					}
					if (obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath != "")
						iconPath = obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath;
				}
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLACED_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.PlacedBounty && obfv_g_BountyConfig.Broadcasts.PlacedBounty.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.PlacedBounty.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.PlacedBounty.Message;
					message.Replace("{PLAYER}", playerName);
					durationStr = Math.Ceil(durationSeconds).ToString();
					message.Replace("{DURATION}", durationStr);
				}
				if (obfv_g_BountyConfig.Broadcasts.PlacedBounty.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.PlacedBounty.Title;
				if (obfv_g_BountyConfig.Broadcasts.PlacedBounty.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.PlacedBounty.IconPath;
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
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty placed notification to " + players.Count().ToString() + " players. Player: " + playerName + ", Duration: " + durationSeconds.ToString() + " seconds");
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted && obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Title != "")
					title = obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Title;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Message;
					durationStr = Math.Ceil(durationSeconds).ToString();
					message.Replace("{DURATION}", durationStr);
					if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty && clearedRewardCount > 0)
					{
						clearedRewardsStr = " Cleared Claim Rewards: " + clearedRewardCount.ToString();
						message.Replace("{CLEARED_REWARDS}", clearedRewardsStr);
					}
					else
					{
						message.Replace("{CLEARED_REWARDS}", "");
					}
				}
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker.Expired && obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Enabled);
				if (!isEnabled)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Rule breaker expiration notification is disabled.");
					return;
				}
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Title != "")
					title = obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Title;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Message != "")
					message = obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Message;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Sending rule breaker bounty expiration notification to " + identity.GetName());
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning && obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title != "")
					title = obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title;
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message;
					message.Replace("{HITS}", currentHits.ToString());
					message.Replace("{BOUNTY_HITS}", bountyHitsThreshold.ToString());
				}
				if (obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Sending rule breaker hit warning notification to " + identity.GetName() + " (Hits: " + currentHits.ToString() + " / " + bountyHitsThreshold.ToString() + ")");
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.RuleBreaker && obfv_g_BountyConfig.Broadcasts.RuleBreaker.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.RuleBreaker.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.RuleBreaker.Message;
					message.Replace("{PLAYER}", playerName);
					durationStr = Math.Ceil(durationSeconds).ToString();
					message.Replace("{DURATION}", durationStr);
				}
				if (obfv_g_BountyConfig.Broadcasts.RuleBreaker.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.RuleBreaker.Title;
				if (obfv_g_BountyConfig.Broadcasts.RuleBreaker.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.RuleBreaker.IconPath;
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
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted rule breaker bounty placed notification to " + players.Count().ToString() + " players. Player: " + playerName + ", Duration: " + durationSeconds.ToString() + " seconds");
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_EXPIRED_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.Expired && obfv_g_BountyConfig.Broadcasts.Expired.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.Expired.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.Expired.Message;
					message.Replace("{PLAYER}", playerName);
				}
				if (obfv_g_BountyConfig.Broadcasts.Expired.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.Expired.Title;
				if (obfv_g_BountyConfig.Broadcasts.Expired.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.Expired.IconPath;
				obfm_BroadcastToAll(title, message, iconPath, color, duration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty expired notification. Player: " + playerName);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_WIN_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.Win && obfv_g_BountyConfig.Broadcasts.Win.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.Win.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.Win.Message;
					message.Replace("{PLAYER}", playerName);
					message.Replace("{WINNER}", winnerName);
				}
				if (obfv_g_BountyConfig.Broadcasts.Win.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.Win.Title;
				if (obfv_g_BountyConfig.Broadcasts.Win.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.Win.IconPath;
				obfm_BroadcastToAll(title, message, iconPath, color, duration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty win notification. Player: " + playerName + ", Winner: " + winnerName);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_SUICIDE_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.Suicide && obfv_g_BountyConfig.Broadcasts.Suicide.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.Suicide.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.Suicide.Message;
					message.Replace("{PLAYER}", playerName);
					suicidePhrase = "";
					if (obfv_g_BountyConfig.Core)
						suicidePhrase = obfv_g_BountyConfig.Core.obfm_GetRandomSuicidePhrase();
					message.Replace("{SUICIDE_PHRASE}", suicidePhrase);
				}
				if (obfv_g_BountyConfig.Broadcasts.Suicide.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.Suicide.Title;
				if (obfv_g_BountyConfig.Broadcasts.Suicide.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.Suicide.IconPath;
				obfm_BroadcastToAll(title, message, iconPath, color, duration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty suicide notification. Player: " + playerName);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_LOGOUT_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.Logout && obfv_g_BountyConfig.Broadcasts.Logout.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.Logout.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.Logout.Message;
					message.Replace("{PLAYER}", playerName);
				}
				if (obfv_g_BountyConfig.Broadcasts.Logout.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.Logout.Title;
				if (obfv_g_BountyConfig.Broadcasts.Logout.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.Logout.IconPath;
				obfm_BroadcastToAll(title, message, iconPath, color, duration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty logout notification. Player: " + playerName);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_WARNING_BROADCAST:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts.Warning && obfv_g_BountyConfig.Broadcasts.Warning.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Broadcasts.Warning.Message != "")
				{
					message = obfv_g_BountyConfig.Broadcasts.Warning.Message;
					message.Replace("{PLAYER}", playerName);
					durationStr = Math.Ceil(durationSeconds).ToString();
					message.Replace("{TIME}", durationStr);
				}
				if (obfv_g_BountyConfig.Broadcasts.Warning.Title != "")
					title = obfv_g_BountyConfig.Broadcasts.Warning.Title;
				if (obfv_g_BountyConfig.Broadcasts.Warning.IconPath != "")
					iconPath = obfv_g_BountyConfig.Broadcasts.Warning.IconPath;
				obfm_BroadcastToAll(title, message, iconPath, color, duration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyNotifications] Broadcasted bounty warning notification. Player: " + playerName + ", Time: " + durationSeconds.ToString() + "s");
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_SAFEZONE:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone && obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.Title;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.Message;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.BountyPausedInSafeZone.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_SKIP_SUCCESS:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess && obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Title;
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Message;
					message.Replace("{PLAYER}", playerName);
				}
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers && obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title;
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message;
				if (obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_BOUNTY_SKIPPED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.BountySkipped && obfv_g_BountyConfig.Notifications.Other.BountySkipped.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.BountySkipped.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.BountySkipped.Title;
				if (obfv_g_BountyConfig.Notifications.Other.BountySkipped.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.BountySkipped.Message;
				if (obfv_g_BountyConfig.Notifications.Other.BountySkipped.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.BountySkipped.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.InsufficientTokens && obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Title;
				if (obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Message;
					requiredStr = tokensRequired.ToString();
					message.Replace("{REQUIRED}", requiredStr);
					foundStr = tokensFound.ToString();
					message.Replace("{FOUND}", foundStr);
				}
				if (obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree && obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title;
				if (obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message;
				if (obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown && obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title;
				if (obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message;
					message.Replace("{PLAYER}", playerName);
					cooldownStr = cooldownSeconds.ToString();
					message.Replace("{COOLDOWN}", cooldownStr);
				}
				if (obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone && obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title;
				if (obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message;
					message.Replace("{PLAYER}", playerName);
				}
				if (obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.EnableConfigReloadSuccessNotification);
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
			case obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE:
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
			case obfv_BOUNTY_NOTIFICATION_REWARD_CONTAINER_SPAWN_FAILURE:
			{
				title = "Reward Spawn Failed";
				message = "Your reward container could not be spawned. Your pending reward was kept so you can try again.";
				iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
				color = ARGB(255, 255, 0, 0);
				duration = 8.0;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_SURVIVAL_REWARD_CONTAINER_SPAWN_FAILURE:
			{
				title = "Reward Spawn Failed";
				message = "Your survival reward container could not be spawned. Your pending reward was kept so you can try again.";
				iconPath = "Ninjins_Bounty_System/gui/icons/bountyerror.edds";
				color = ARGB(255, 255, 0, 0);
				duration = 8.0;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.EnableCommandAccessDeniedNotification);
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
			case obfv_BOUNTY_NOTIFICATION_BOUNTY_PERSISTED:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.BountyPersisted && obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Title;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Message;
					durationStr = Math.Ceil(remainingDuration).ToString();
					message.Replace("{DURATION}", durationStr);
				}
				if (obfv_g_BountyConfig.Notifications.Other.BountyPersisted.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.BountyPersisted.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory && obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory && obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message != "")
					message = obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message;
				if (obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_BOUNTY_RESUMED_FROM_TERRITORY:
			{
				isEnabled = (obfv_g_BountyConfig && obfv_g_BountyConfig.Notifications && obfv_g_BountyConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory && obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled);
				if (!isEnabled)
					return;
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title != "")
					title = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message != "")
				{
					message = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
					durationStr = Math.Ceil(remainingDuration).ToString();
					message.Replace("{DURATION}", durationStr);
				}
				if (obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath != "")
					iconPath = obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
				NotificationSystem.Create(new StringLocaliser(title), new StringLocaliser(message), iconPath, color, duration, identity);
				break;
			}
			case obfv_BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL:
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