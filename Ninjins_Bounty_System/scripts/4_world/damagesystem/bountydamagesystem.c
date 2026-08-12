class obfc_BountyHitEntry
{
	PlayerBase obfv_attacker;
	PlayerBase obfv_victim;
	int obfv_hitCount;
	float obfv_firstHitTime; 
	float obfv_lastHitTime; 
	bool obfv_warningSent; 
	bool obfv_shouldSendWarning; 
	void obfc_BountyHitEntry(PlayerBase _attacker, PlayerBase _victim)
	{
		float currentTime;
		obfv_attacker = _attacker;
		obfv_victim = _victim;
		obfv_hitCount = 0;
		currentTime = g_Game.GetTime();
		obfv_firstHitTime = currentTime;
		obfv_lastHitTime = currentTime;
		obfv_warningSent = false;
		obfv_shouldSendWarning = false;
	}
}
class obfc_BountyHitTracker
{
	private static ref obfc_BountyHitTracker obfv_s_Instance;
	private ref array<ref obfc_BountyHitEntry> obfv_m_HitEntries;
	static obfc_BountyHitTracker GetInstance()
	{
		if (!obfv_s_Instance)
		{
			obfv_s_Instance = new obfc_BountyHitTracker();
		}
		return obfv_s_Instance;
	}
	void obfc_BountyHitTracker()
	{
		obfv_m_HitEntries = new array<ref obfc_BountyHitEntry>;
	}
	bool obfm_RecordHit(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		obfc_BountyHitEntry entry;
		bool obfv_shouldSendWarning;
		if (!IsMissionHost())
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		if (!obfv_attacker || !obfv_victim || obfv_attacker == obfv_victim)
			return false;
		if (!obfv_g_BountyConfig.RuleBreaker || !obfv_g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
		{
			return true; 
		}
		if (obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime <= 0.0)
		{
			return true; 
		}
		entry = obfm_FindOrCreateEntry(obfv_attacker, obfv_victim);
		if (!entry)
			return false;
		entry.obfv_hitCount++;
		entry.obfv_lastHitTime = g_Game.GetTime();
		obfv_shouldSendWarning = false;
		if (!entry.obfv_warningSent && obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits > 0)
		{
			if (entry.obfv_hitCount >= obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits)
			{
				entry.obfv_warningSent = true;
				obfv_shouldSendWarning = true;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyHitTracker] Warning threshold met: " + entry.obfv_hitCount.ToString() + " hits (warning should be sent)");
			}
		}
		entry.obfv_shouldSendWarning = obfv_shouldSendWarning;
		return obfm_CheckThreshold(entry);
	}
	obfc_BountyHitEntry obfm_FindOrCreateEntry(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		int i;
		obfc_BountyHitEntry entry;
		obfc_BountyHitEntry newEntry;
		for (i = 0; i < obfv_m_HitEntries.Count(); i++)
		{
			entry = obfv_m_HitEntries.Get(i);
			if (entry && entry.obfv_attacker == obfv_attacker && entry.obfv_victim == obfv_victim)
			{
				return entry;
			}
		}
		newEntry = new obfc_BountyHitEntry(obfv_attacker, obfv_victim);
		obfv_m_HitEntries.Insert(newEntry);
		return newEntry;
	}
	bool obfm_CheckThreshold(obfc_BountyHitEntry entry)
	{
		float currentTime;
		float timeWindow;
		float timeSinceFirstHit;
		int bountyHitsThreshold;
		if (!entry || !obfv_g_BountyConfig)
			return false;
		currentTime = g_Game.GetTime();
		timeWindow = obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime * 1000.0; 
		timeSinceFirstHit = currentTime - entry.obfv_firstHitTime;
		if (timeSinceFirstHit > timeWindow)
		{
			entry.obfv_hitCount = 0;
			entry.obfv_firstHitTime = currentTime;
			entry.obfv_lastHitTime = currentTime;
			entry.obfv_warningSent = false;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyHitTracker] Time window expired for attacker-victim pair. Resetting hit tracking.");
			return false;
		}
		bountyHitsThreshold = obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
		if (bountyHitsThreshold <= 0)
		{
			return true;
		}
		if (entry.obfv_hitCount >= bountyHitsThreshold)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyHitTracker] Hit threshold met: " + entry.obfv_hitCount.ToString() + " >= " + bountyHitsThreshold.ToString() + " within " + (timeSinceFirstHit / 1000.0).ToString() + " seconds");
			return true;
		}
		return false;
	}
	void obfm_ClearEntry(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		int i;
		obfc_BountyHitEntry entry;
		for (i = obfv_m_HitEntries.Count() - 1; i >= 0; i--)
		{
			entry = obfv_m_HitEntries.Get(i);
			if (entry && entry.obfv_attacker == obfv_attacker && entry.obfv_victim == obfv_victim)
			{
				obfv_m_HitEntries.Remove(i);
				return;
			}
		}
	}
	void obfm_CleanupExpiredEntries()
	{
		float currentTime;
		float timeWindow;
		int i;
		obfc_BountyHitEntry entry;
		float timeSinceLastHit;
		PlayerIdentity attackerIdentity;
		PlayerIdentity victimIdentity;
		string attackerName;
		string victimName;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.RuleBreaker || !obfv_g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold || obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime <= 0.0)
			return;
		currentTime = g_Game.GetTime();
		timeWindow = obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime * 1000.0; 
		for (i = obfv_m_HitEntries.Count() - 1; i >= 0; i--)
		{
			entry = obfv_m_HitEntries.Get(i);
			if (!entry)
			{
				obfv_m_HitEntries.Remove(i);
				continue;
			}
			timeSinceLastHit = currentTime - entry.obfv_lastHitTime;
			if (timeSinceLastHit > timeWindow)
			{
				attackerName = "Unknown";
				victimName = "Unknown";
				if (entry.obfv_attacker)
				{
					attackerIdentity = entry.obfv_attacker.GetIdentity();
					if (attackerIdentity)
						attackerName = attackerIdentity.GetName();
				}
				if (entry.obfv_victim)
				{
					victimIdentity = entry.obfv_victim.GetIdentity();
					if (victimIdentity)
						victimName = victimIdentity.GetName();
				}
				obfv_m_HitEntries.Remove(i);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyHitTracker] Cleaned up expired hit entry: " + attackerName + " -> " + victimName + " (Total hits: " + entry.obfv_hitCount.ToString() + ", no hits for " + (timeSinceLastHit / 1000.0).ToString() + " seconds)");
			}
		}
	}
	int obfm_GetHitCountForPair(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		obfc_BountyHitEntry entry = obfm_FindOrCreateEntry(obfv_attacker, obfv_victim);
		if (entry)
		{
			return entry.obfv_hitCount;
		}
		return 0;
	}
	bool obfm_ShouldSendWarning(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		obfc_BountyHitEntry entry = obfm_FindOrCreateEntry(obfv_attacker, obfv_victim);
		if (entry && entry.obfv_shouldSendWarning)
		{
			entry.obfv_shouldSendWarning = false; 
			return true;
		}
		return false;
	}
}
class obfc_BountyDamageHandler
{
	private static ref obfc_BountyDamageHandler obfv_s_Instance;
	static obfc_BountyDamageHandler GetInstance()
	{
		if (!obfv_s_Instance)
		{
			obfv_s_Instance = new obfc_BountyDamageHandler();
		}
		return obfv_s_Instance;
	}
	bool obfm_CheckAndApplyBounty(PlayerBase obfv_attacker, PlayerBase obfv_victim, EntityAI source, string ammo)
	{
		bool attackerInPvE;
		bool victimInPvE;
		PlayerIdentity victimIdentity;
		string victimName;
		string reason;
		if (!IsMissionHost())
			return true;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return true;
		if (!obfv_attacker || !obfv_victim || obfv_attacker == obfv_victim)
			return true;
		attackerInPvE = obfv_attacker.obfm_BountyPlayerInPvEZone();
		victimInPvE = obfv_victim.obfm_BountyPlayerInPvEZone();
		if (attackerInPvE && victimInPvE)
		{
			if (obfv_victim.obfm_HasBounty())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyDamageHandler] Victim has bounty - not applying bounty to attacker.");
				return true;
			}
			if (!obfv_attacker.obfm_HasBounty())
			{
				victimIdentity = obfv_victim.GetIdentity();
				victimName = "Unknown";
				if (victimIdentity)
					victimName = victimIdentity.GetName();
				reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
				obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason);
			}
		}
		return true;
	}
	bool obfm_ShouldAllowDamageToBountiedPlayer(PlayerBase obfv_attacker, PlayerBase obfv_victim)
	{
		if (!IsMissionHost())
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		if (!obfv_attacker || !obfv_victim || obfv_attacker == obfv_victim)
			return false;
		if (obfv_attacker.GetIdentity() && obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(obfv_attacker.GetIdentity()))
		{
			string victimName = "unknown";
			if (obfv_victim.GetIdentity())
			{
				victimName = obfv_victim.GetIdentity().GetName();
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyDamageSystem] Blacklisted player " + obfv_attacker.GetIdentity().GetName() + " tried to damage bountied player " + victimName + " - blocking damage");
			return false;
		}
		if (obfv_victim.obfm_HasBounty())
		{
			return true;
		}
		return false;
	}
	//! Bounty opinion when zone stance already denied (or old DamageUtils is deciding). Returns true when bounty chose allow/deny; openHitOut is that choice.
	bool obfm_TryOpenDeniedZoneHit(PlayerBase obfv_victim, PlayerBase obfv_attacker, out bool openHitOut)
	{
		PlayerIdentity victimIdentity;
		PlayerIdentity attackerIdentity;
		string victimName;
		string reason;
		string enablePvEToPvPRuleBreakerStr;
		obfc_BountyHitTracker hitTracker;
		bool shouldApplyBounty;
		int obfv_hitCount;
		int bountyHitsThreshold;
		bool attackerIsBlacklisted;
		bool attackerInPvE;
		bool victimInPvE;

		openHitOut = false;
		if (!IsMissionHost())
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		if (!obfv_attacker || !obfv_victim || obfv_attacker == obfv_victim)
			return false;
		if (obfm_ShouldAllowDamageToBountiedPlayer(obfv_attacker, obfv_victim))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Allowing damage to bountied player from attacker. No bounty applied to attacker.");
			openHitOut = true;
			return true;
		}
		attackerInPvE = obfv_attacker.obfm_BountyPlayerInPvEZone();
		victimInPvE = obfv_victim.obfm_BountyPlayerInPvEZone();
		if (!attackerInPvE && !victimInPvE)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Both attacker and victim in PvP state - allowing damage (bountied players can fight PvP players).");
			openHitOut = true;
			return true;
		}
		if (obfv_attacker.obfm_HasBounty() && victimInPvE)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bountied player attacking PvE player - blocking damage.");
			openHitOut = false;
			return true;
		}
		if (attackerInPvE && victimInPvE)
		{
			if (obfv_victim.obfm_HasBounty())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Victim has bounty - allowing damage without applying bounty to attacker.");
				openHitOut = true;
				return true;
			}
			if (!obfv_attacker.obfm_HasBounty())
			{
				attackerIsBlacklisted = false;
				if (obfv_attacker.GetIdentity() && obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(obfv_attacker.GetIdentity()))
				{
					attackerIsBlacklisted = true;
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Blacklisted attacker attacking PvE player - skipping warnings/bounties, but normal PvE rules still apply.");
				}
				if (!attackerIsBlacklisted)
				{
					if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
					{
						hitTracker = obfc_BountyHitTracker.GetInstance();
						shouldApplyBounty = hitTracker.obfm_RecordHit(obfv_attacker, obfv_victim);
						obfv_hitCount = hitTracker.obfm_GetHitCountForPair(obfv_attacker, obfv_victim);
						if (hitTracker.obfm_ShouldSendWarning(obfv_attacker, obfv_victim))
						{
							attackerIdentity = obfv_attacker.GetIdentity();
							if (attackerIdentity && (!obfv_g_BountyBlacklistConfig || !obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(attackerIdentity)))
							{
								bountyHitsThreshold = obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
								obfc_BountyNotifArgs notifArgs1;
								notifArgs1 = new obfc_BountyNotifArgs();
								notifArgs1.currentHits = obfv_hitCount;
								notifArgs1.bountyHitsThreshold = bountyHitsThreshold;
								obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING, attackerIdentity, notifArgs1);
							}
						}
						if (shouldApplyBounty)
						{
							victimIdentity = obfv_victim.GetIdentity();
							victimName = "Unknown";
							if (victimIdentity)
								victimName = victimIdentity.GetName();
							reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
							obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
							#ifdef EXPANSIONMODHARDLINE
							if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
							{
								obfv_attacker.Expansion_DecreaseReputation(obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Decreased Hardline reputation by " + obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for attacker (threshold met).");
							}
							#endif
							hitTracker.obfm_ClearEntry(obfv_attacker, obfv_victim);
							if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill)
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker (hit threshold met: " + obfv_hitCount.ToString() + " hits >= " + obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Allowing damage (AllowPvEToPvEVictimKill enabled).");
								openHitOut = true;
								return true;
							}
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker (hit threshold met: " + obfv_hitCount.ToString() + " hits >= " + obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Blocking damage without reflection.");
							openHitOut = false;
							return true;
						}
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PvE rule violation detected but threshold not met yet. Hits: " + obfv_hitCount.ToString() + " / " + obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + ". Blocking damage without applying bounty.");
						openHitOut = false;
						return true;
					}
					victimIdentity = obfv_victim.GetIdentity();
					victimName = "Unknown";
					if (victimIdentity)
						victimName = victimIdentity.GetName();
					reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
					obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
					#ifdef EXPANSIONMODHARDLINE
					if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
					{
						obfv_attacker.Expansion_DecreaseReputation(obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Decreased Hardline reputation by " + obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for attacker (instant apply).");
					}
					#endif
					if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker (instant apply - threshold system disabled). Allowing damage (AllowPvEToPvEVictimKill enabled).");
						openHitOut = true;
						return true;
					}
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker (instant apply - threshold system disabled). Blocking damage without reflection.");
					openHitOut = false;
					return true;
				}
			}
		}
		if (attackerInPvE && !victimInPvE)
		{
			if (obfv_g_BountyConfig.RuleBreaker)
				enablePvEToPvPRuleBreakerStr = obfv_g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker.ToString();
			else
				enablePvEToPvPRuleBreakerStr = "null";
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PvE-to-PvP attack detected: Attacker in PvE=" + attackerInPvE.ToString() + ", Victim in PvE=" + victimInPvE.ToString() + ", EnablePvEToPvPRuleBreaker=" + enablePvEToPvPRuleBreakerStr);
			if (obfv_victim.obfm_HasBounty())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Victim has bounty - allowing damage without applying bounty to attacker.");
				openHitOut = true;
				return true;
			}
			if (obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker)
			{
				if (!obfv_attacker.obfm_HasBounty())
				{
					attackerIsBlacklisted = false;
					if (obfv_attacker.GetIdentity() && obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(obfv_attacker.GetIdentity()))
					{
						attackerIsBlacklisted = true;
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Blacklisted attacker attacking PvP player from PvE - skipping warnings/bounties, but normal PvE rules still apply.");
					}
					if (!attackerIsBlacklisted)
					{
						if (obfv_g_BountyConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits == 1)
						{
							victimIdentity = obfv_victim.GetIdentity();
							victimName = "Unknown";
							if (victimIdentity)
								victimName = victimIdentity.GetName();
							reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
							obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
							#ifdef EXPANSIONMODHARDLINE
							if (obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
							{
								obfv_attacker.Expansion_DecreaseReputation(obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Decreased Hardline reputation by " + obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (instant apply).");
							}
							#endif
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied instant rulebreaker bounty to PvE attacker attacking PvP player (PvEToPvPInstantRuleBreakerHits=1). Blocking damage without reflection.");
							openHitOut = false;
							return true;
						}
						if (obfv_g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
						{
							hitTracker = obfc_BountyHitTracker.GetInstance();
							shouldApplyBounty = hitTracker.obfm_RecordHit(obfv_attacker, obfv_victim);
							obfv_hitCount = hitTracker.obfm_GetHitCountForPair(obfv_attacker, obfv_victim);
							if (hitTracker.obfm_ShouldSendWarning(obfv_attacker, obfv_victim))
							{
								attackerIdentity = obfv_attacker.GetIdentity();
								if (attackerIdentity && (!obfv_g_BountyBlacklistConfig || !obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(attackerIdentity)))
								{
									bountyHitsThreshold = obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
									obfc_BountyNotifArgs notifArgs2;
									notifArgs2 = new obfc_BountyNotifArgs();
									notifArgs2.currentHits = obfv_hitCount;
									notifArgs2.bountyHitsThreshold = bountyHitsThreshold;
									obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING, attackerIdentity, notifArgs2);
								}
							}
							if (shouldApplyBounty)
							{
								victimIdentity = obfv_victim.GetIdentity();
								victimName = "Unknown";
								if (victimIdentity)
									victimName = victimIdentity.GetName();
								reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
								obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
								#ifdef EXPANSIONMODHARDLINE
								if (obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
								{
									obfv_attacker.Expansion_DecreaseReputation(obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Decreased Hardline reputation by " + obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (threshold met).");
								}
								#endif
								hitTracker.obfm_ClearEntry(obfv_attacker, obfv_victim);
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker attacking PvP player (hit threshold met: " + obfv_hitCount.ToString() + " hits >= " + obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Blocking damage without reflection.");
								openHitOut = false;
								return true;
							}
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PvE to PvP rule violation detected but threshold not met yet. Hits: " + obfv_hitCount.ToString() + " / " + obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + ". Blocking damage without applying bounty.");
							openHitOut = false;
							return true;
						}
						victimIdentity = obfv_victim.GetIdentity();
						victimName = "Unknown";
						if (victimIdentity)
							victimName = victimIdentity.GetName();
						reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
						obfc_BountyManager.obfm_ApplyBountyToPlayer(obfv_attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
						#ifdef EXPANSIONMODHARDLINE
						if (obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
						{
							obfv_attacker.Expansion_DecreaseReputation(obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Decreased Hardline reputation by " + obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (instant apply).");
						}
						#endif
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Applied bounty to PvE attacker attacking PvP player (instant apply - threshold system disabled). Blocking damage without reflection.");
						openHitOut = false;
						return true;
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PvE attacker already has bounty - blocking damage without applying new bounty.");
					openHitOut = false;
					return true;
				}
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PvE-to-PvP rule breaker is disabled - blocking damage without applying bounty.");
			openHitOut = false;
			return true;
		}
		return false;
	}
}
#ifdef NinjinsPvPPvE
modded class DamageUtils
{
	//! Parameter name must match parent DamageUtils (victim), not obfv_victim - EnScript fails otherwise.
	override bool ShouldAllowDamage(PlayerBase victim, TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		obfc_BountyDamageHandler bountyHandler;
		DamageUtils dmgUtils;
		AttackerContext ctx;
		PlayerBase attacker;
		bool openHit;
		bool bountyDecided;
		bool attackerIsPlayer;
		bool victimIsPlayer;
		bool attackerIsAI;
		bool victimIsAI;
		bool victimIsBlacklisted;
		string attackerName;

		openHit = false;
		bountyDecided = false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
			return super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		bountyHandler = obfc_BountyDamageHandler.GetInstance();
		dmgUtils = DamageUtils.GetInstance();
		ctx = dmgUtils.ResolveAttacker(source);
		dmgUtils.GrenadeAttackerContext(ctx, source);
		attacker = ctx.Player;
		attackerIsPlayer = ctx.IsPlayer() && ctx.Player != null;
		victimIsPlayer = false;
		if (victim)
			victimIsPlayer = victim.IsInherited(PlayerBase);
		#ifdef EXPANSIONMODAI
		attackerIsAI = ctx.IsAI() && ctx.AI != null;
		victimIsAI = false;
		if (victim)
			victimIsAI = victim.IsInherited(eAIBase);
		#else
		attackerIsAI = false;
		victimIsAI = false;
		#endif
		if (attackerIsAI || victimIsAI)
			return super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		if (victim && attacker && attacker != victim && victim.GetIdentity())
		{
			victimIsBlacklisted = false;
			if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(victim.GetIdentity()))
				victimIsBlacklisted = true;
			if (victimIsBlacklisted && g_MainConfig && g_MainConfig.EnableReflectDamage)
			{
				dmgUtils.ReflectDamageToAttacker(attacker, damageResult);
				if (attacker.GetIdentity())
					attackerName = attacker.GetIdentity().GetName();
				else
					attackerName = "Unknown";
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Blacklisted player " + victim.GetIdentity().GetName() + " took damage from " + attackerName + " - reflecting damage (reflect damage enabled)");
				return false;
			}
		}
		if (attackerIsPlayer && victimIsPlayer && attacker && victim && attacker != victim)
		{
			bountyDecided = bountyHandler.obfm_TryOpenDeniedZoneHit(victim, attacker, openHit);
			if (bountyDecided)
				return openHit;
		}
		return super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
}
#endif
