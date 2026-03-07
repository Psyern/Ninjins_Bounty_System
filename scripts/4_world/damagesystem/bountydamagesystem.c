class BountyHitEntry
{
    PlayerBase attacker;
    PlayerBase victim;
    int hitCount;
    float firstHitTime; 
    float lastHitTime; 
    bool warningSent; 
    bool shouldSendWarning; 
    void BountyHitEntry(PlayerBase _attacker, PlayerBase _victim)
    {
        float currentTime;
        attacker = _attacker;
        victim = _victim;
        hitCount = 0;
        currentTime = g_Game.GetTime();
        firstHitTime = currentTime;
        lastHitTime = currentTime;
        warningSent = false;
        shouldSendWarning = false;
    }
}
class BountyHitTracker
{
    private static ref BountyHitTracker s_Instance;
    private ref array<ref BountyHitEntry> m_HitEntries;
    static BountyHitTracker GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new BountyHitTracker();
        }
        return s_Instance;
    }
    void BountyHitTracker()
    {
        m_HitEntries = new array<ref BountyHitEntry>;
    }
    bool RecordHit(PlayerBase attacker, PlayerBase victim)
    {
        BountyHitEntry entry;
        bool shouldSendWarning;
        if (!IsMissionHost())
            return false;
        if (!g_BountyConfig || !g_BountyConfig.Core || !g_BountyConfig.Core.EnableBountySystem)
            return false;
        if (!attacker || !victim || attacker == victim)
            return false;
        if (!g_BountyConfig.RuleBreaker || !g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
        {
            return true; 
        }
        if (g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime <= 0.0)
        {
            return true; 
        }
        entry = FindOrCreateEntry(attacker, victim);
        if (!entry)
            return false;
        entry.hitCount++;
        entry.lastHitTime = g_Game.GetTime();
        shouldSendWarning = false;
        if (!entry.warningSent && g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits > 0)
        {
            if (entry.hitCount >= g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits)
            {
                entry.warningSent = true;
                shouldSendWarning = true;
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyHitTracker] Warning threshold met: " + entry.hitCount.ToString() + " hits (warning should be sent)");
            }
        }
        entry.shouldSendWarning = shouldSendWarning;
        return CheckThreshold(entry);
    }
    BountyHitEntry FindOrCreateEntry(PlayerBase attacker, PlayerBase victim)
    {
        int i;
        BountyHitEntry entry;
        BountyHitEntry newEntry;
        for (i = 0; i < m_HitEntries.Count(); i++)
        {
            entry = m_HitEntries.Get(i);
            if (entry && entry.attacker == attacker && entry.victim == victim)
            {
                return entry;
            }
        }
        newEntry = new BountyHitEntry(attacker, victim);
        m_HitEntries.Insert(newEntry);
        return newEntry;
    }
    bool CheckThreshold(BountyHitEntry entry)
    {
        float currentTime;
        float timeWindow;
        float timeSinceFirstHit;
        int bountyHitsThreshold;
        if (!entry || !g_BountyConfig)
            return false;
        currentTime = g_Game.GetTime();
        timeWindow = g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime * 1000.0; 
        timeSinceFirstHit = currentTime - entry.firstHitTime;
        if (timeSinceFirstHit > timeWindow)
        {
            entry.hitCount = 0;
            entry.firstHitTime = currentTime;
            entry.lastHitTime = currentTime;
            entry.warningSent = false;
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyHitTracker] Time window expired for attacker-victim pair. Resetting hit tracking.");
            return false;
        }
        bountyHitsThreshold = g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
        if (bountyHitsThreshold <= 0)
        {
            return true;
        }
        if (entry.hitCount >= bountyHitsThreshold)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyHitTracker] Hit threshold met: " + entry.hitCount.ToString() + " >= " + bountyHitsThreshold.ToString() + " within " + (timeSinceFirstHit / 1000.0).ToString() + " seconds");
            return true;
        }
        return false;
    }
    void ClearEntry(PlayerBase attacker, PlayerBase victim)
    {
        int i;
        BountyHitEntry entry;
        for (i = m_HitEntries.Count() - 1; i >= 0; i--)
        {
            entry = m_HitEntries.Get(i);
            if (entry && entry.attacker == attacker && entry.victim == victim)
            {
                m_HitEntries.Remove(i);
                return;
            }
        }
    }
    void CleanupExpiredEntries()
    {
        float currentTime;
        float timeWindow;
        int i;
        BountyHitEntry entry;
        float timeSinceLastHit;
        PlayerIdentity attackerIdentity;
        PlayerIdentity victimIdentity;
        string attackerName;
        string victimName;
        if (!g_BountyConfig || !g_BountyConfig.RuleBreaker || !g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold || g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime <= 0.0)
            return;
        currentTime = g_Game.GetTime();
        timeWindow = g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime * 1000.0; 
        for (i = m_HitEntries.Count() - 1; i >= 0; i--)
        {
            entry = m_HitEntries.Get(i);
            if (!entry)
            {
                m_HitEntries.Remove(i);
                continue;
            }
            timeSinceLastHit = currentTime - entry.lastHitTime;
            if (timeSinceLastHit > timeWindow)
            {
                attackerName = "Unknown";
                victimName = "Unknown";
                if (entry.attacker)
                {
                    attackerIdentity = entry.attacker.GetIdentity();
                    if (attackerIdentity)
                        attackerName = attackerIdentity.GetName();
                }
                if (entry.victim)
                {
                    victimIdentity = entry.victim.GetIdentity();
                    if (victimIdentity)
                        victimName = victimIdentity.GetName();
                }
                m_HitEntries.Remove(i);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyHitTracker] Cleaned up expired hit entry: " + attackerName + " -> " + victimName + " (Total hits: " + entry.hitCount.ToString() + ", no hits for " + (timeSinceLastHit / 1000.0).ToString() + " seconds)");
            }
        }
    }
    int GetHitCountForPair(PlayerBase attacker, PlayerBase victim)
    {
        BountyHitEntry entry = FindOrCreateEntry(attacker, victim);
        if (entry)
        {
            return entry.hitCount;
        }
        return 0;
    }
    bool ShouldSendWarning(PlayerBase attacker, PlayerBase victim)
    {
        BountyHitEntry entry = FindOrCreateEntry(attacker, victim);
        if (entry && entry.shouldSendWarning)
        {
            entry.shouldSendWarning = false; 
            return true;
        }
        return false;
    }
}
class BountyDamageHandler
{
    private static ref BountyDamageHandler s_Instance;
    static BountyDamageHandler GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new BountyDamageHandler();
        }
        return s_Instance;
    }
    bool CheckAndApplyBounty(PlayerBase attacker, PlayerBase victim, EntityAI source, string ammo)
    {
        bool attackerInPvE;
        bool victimInPvE;
        PlayerIdentity victimIdentity;
        string victimName;
        string reason;
        if (!IsMissionHost())
            return true;
        if (!g_BountyConfig || !g_BountyConfig.Core || !g_BountyConfig.Core.EnableBountySystem)
            return true;
        if (!attacker || !victim || attacker == victim)
            return true;
        #ifdef NinjinsPvPPvE
        attackerInPvE = attacker.netSync_IsInPvEZone;
        victimInPvE = victim.netSync_IsInPvEZone;
        #else
        attackerInPvE = false;
        victimInPvE = false;
        #endif
        if (attackerInPvE && victimInPvE)
        {
            if (victim.HasBounty())
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyDamageHandler] Victim has bounty - not applying bounty to attacker.");
                return true;
            }
            if (!attacker.HasBounty())
            {
                victimIdentity = victim.GetIdentity();
                victimName = "Unknown";
                if (victimIdentity)
                    victimName = victimIdentity.GetName();
                reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
                BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason);
            }
        }
        return true;
    }
    bool ShouldAllowDamageToBountiedPlayer(PlayerBase attacker, PlayerBase victim)
    {
        if (!IsMissionHost())
            return false;
        if (!g_BountyConfig || !g_BountyConfig.Core || !g_BountyConfig.Core.EnableBountySystem)
            return false;
        if (!attacker || !victim || attacker == victim)
            return false;
        if (attacker.GetIdentity() && g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(attacker.GetIdentity().GetId()))
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyDamageSystem] Blacklisted player " + attacker.GetIdentity().GetName() + " tried to damage bountied player " + victim.GetIdentity().GetName() + " - blocking damage");
            return false;
        }
        if (victim.HasBounty())
        {
            return true;
        }
        return false;
    }
}
#ifdef NinjinsPvPPvE
modded class DamageUtils
{
    override bool ShouldAllowDamage(PlayerBase victim, TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        PlayerIdentity victimIdentity;
        PlayerIdentity attackerIdentity;
        string victimName;
        string reason;
        bool isExplosive;
        BountyHitTracker hitTracker;
        bool shouldApplyBounty;
        int hitCount;
        int bountyHitsThreshold;
        bool attackerIsBlacklisted;
        BountyDamageHandler bountyHandler;
        DamageUtils dmgUtils;
        AttackerContext ctx;
        PlayerBase attacker;
        bool attackerInPvE;
        bool victimInPvE;
        victimName = "";
        reason = "";
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.EnableBountySystem)
        {
            bountyHandler = BountyDamageHandler.GetInstance();
            dmgUtils = DamageUtils.GetInstance();
            ctx = dmgUtils.ResolveAttacker(source);
            dmgUtils.GrenadeAttackerContext(ctx, source);
            attacker = ctx.Player;
            bool attackerIsPlayer = ctx.IsPlayer() && ctx.Player != null;
            bool victimIsPlayer = victim.IsInherited(PlayerBase);
            #ifdef EXPANSIONMODAI
            bool attackerIsAI = ctx.IsAI() && ctx.AI != null;
            bool victimIsAI = victim.IsInherited(eAIBase);
            #else
            bool attackerIsAI = false;
            bool victimIsAI = false;
            #endif
            if (attackerIsAI || victimIsAI)
            {
                return super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
            }
            #ifdef NinjinsPvPPvE
            if (victim && attacker && attacker != victim && victim.GetIdentity())
            {
                bool victimIsBlacklisted = false;
                if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(victim.GetIdentity().GetId()))
                {
                    victimIsBlacklisted = true;
                }
                if (victimIsBlacklisted && g_MainConfig && g_MainConfig.EnableReflectDamage)
                {
                    dmgUtils.ReflectDamageToAttacker(attacker, damageResult);
                    string attackerName;
                    if (attacker.GetIdentity())
                        attackerName = attacker.GetIdentity().GetName();
                    else
                        attackerName = "Unknown";
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Blacklisted player " + victim.GetIdentity().GetName() + " took damage from " + attackerName + " - reflecting damage (reflect damage enabled)");
                    return false; 
                }
            }
            #endif
            if (attackerIsPlayer && victimIsPlayer && attacker && victim && attacker != victim)
            {
                if (bountyHandler.ShouldAllowDamageToBountiedPlayer(attacker, victim))
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Allowing damage to bountied player from attacker. No bounty applied to attacker.");
                    return true;
                }
                #ifdef NinjinsPvPPvE
                attackerInPvE = attacker.netSync_IsInPvEZone;
                victimInPvE = victim.netSync_IsInPvEZone;
                #else
                attackerInPvE = false;
                victimInPvE = false;
                #endif
                if (!attackerInPvE && !victimInPvE)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Both attacker and victim in PvP state - allowing damage (bountied players can fight PvP players).");
                    return true; 
                }
                if (attacker.HasBounty() && victimInPvE)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Bountied player attacking PvE player - blocking damage and reflecting.");
                    super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
                    return false;
                }
                if (attackerInPvE && victimInPvE)
                {
                    if (victim.HasBounty())
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Victim has bounty - allowing damage without applying bounty to attacker.");
                        return true; 
                    }
                    if (!attacker.HasBounty())
                    {
                        attackerIsBlacklisted = false;
                        if (attacker.GetIdentity() && g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(attacker.GetIdentity().GetId()))
                        {
                            attackerIsBlacklisted = true;
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Blacklisted attacker attacking PvE player - skipping warnings/bounties, but normal PvE rules still apply.");
                        }
                        if (!attackerIsBlacklisted)
                        {
                            if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
                            {
                                hitTracker = BountyHitTracker.GetInstance();
                                shouldApplyBounty = hitTracker.RecordHit(attacker, victim);
                                hitCount = hitTracker.GetHitCountForPair(attacker, victim);
                                if (hitTracker.ShouldSendWarning(attacker, victim))
                                {
                                    attackerIdentity = attacker.GetIdentity();
                                    if (attackerIdentity && (!g_BountyBlacklistConfig || !g_BountyBlacklistConfig.IsBlacklisted(attackerIdentity.GetId())))
                                    {
                                        bountyHitsThreshold = g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
                                        BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING, attackerIdentity, "", "", 0.0, 0, hitCount, bountyHitsThreshold);
                                    }
                                }
                                if (shouldApplyBounty)
                                {
                                    victimIdentity = victim.GetIdentity();
                                    victimName = "Unknown";
                                    if (victimIdentity)
                                        victimName = victimIdentity.GetName();
                                    reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
                                    BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
                                    #ifdef EXPANSIONMODHARDLINE
                                    if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
                                    {
                                        attacker.Expansion_DecreaseReputation(g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Decreased Hardline reputation by " + g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for attacker (threshold met).");
                                    }
                                    #endif
                                    hitTracker.ClearEntry(attacker, victim);
                                    if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill)
                                    {
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker (hit threshold met: " + hitCount.ToString() + " hits >= " + g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Allowing damage (AllowPvEToPvEVictimKill enabled).");
                                        return true; 
                                    }
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker (hit threshold met: " + hitCount.ToString() + " hits >= " + g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Blocking damage without reflection.");
                                    return false;
                                }
                                else
                                {
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] PvE rule violation detected but threshold not met yet. Hits: " + hitCount.ToString() + " / " + g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + ". Blocking damage without applying bounty.");
                                    return false;
                                }
                            }
                            else
                            {
                                victimIdentity = victim.GetIdentity();
                                victimName = "Unknown";
                                if (victimIdentity)
                                    victimName = victimIdentity.GetName();
                                reason = "PvE rule violation (attacked " + victimName + " in PvE zone)";
                                BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
                                #ifdef EXPANSIONMODHARDLINE
                                if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
                                {
                                    attacker.Expansion_DecreaseReputation(g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Decreased Hardline reputation by " + g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for attacker (instant apply).");
                                }
                                #endif
                                if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill)
                                {
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker (instant apply - threshold system disabled). Allowing damage (AllowPvEToPvEVictimKill enabled).");
                                    return true; 
                                }
                                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker (instant apply - threshold system disabled). Blocking damage without reflection.");
                                return false;
                            }
                        }
                    }
                }
                if (attackerInPvE && !victimInPvE)
                {
                    string enablePvEToPvPRuleBreakerStr;
                    if (g_BountyConfig.RuleBreaker)
                        enablePvEToPvPRuleBreakerStr = g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker.ToString();
                    else
                        enablePvEToPvPRuleBreakerStr = "null";
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] PvE-to-PvP attack detected: Attacker in PvE=" + attackerInPvE.ToString() + ", Victim in PvE=" + victimInPvE.ToString() + ", EnablePvEToPvPRuleBreaker=" + enablePvEToPvPRuleBreakerStr);
                    if (victim.HasBounty())
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Victim has bounty - allowing damage without applying bounty to attacker.");
                        return true; 
                    }
                    if (g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker)
                    {
                        if (!attacker.HasBounty())
                        {
                            attackerIsBlacklisted = false;
                            if (attacker.GetIdentity() && g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(attacker.GetIdentity().GetId()))
                            {
                                attackerIsBlacklisted = true;
                                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Blacklisted attacker attacking PvP player from PvE - skipping warnings/bounties, but normal PvE rules still apply.");
                            }
                            if (!attackerIsBlacklisted)
                            {
                                if (g_BountyConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits == 1)
                                {
                                    victimIdentity = victim.GetIdentity();
                                    victimName = "Unknown";
                                    if (victimIdentity)
                                        victimName = victimIdentity.GetName();
                                    reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
                                    BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
                                    #ifdef EXPANSIONMODHARDLINE
                                    if (g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
                                    {
                                        attacker.Expansion_DecreaseReputation(g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Decreased Hardline reputation by " + g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (instant apply).");
                                    }
                                    #endif
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied instant rulebreaker bounty to PvE attacker attacking PvP player (PvEToPvPInstantRuleBreakerHits=1). Blocking damage without reflection.");
                                    return false;
                                }
                                if (g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold)
                                {
                                    hitTracker = BountyHitTracker.GetInstance();
                                    shouldApplyBounty = hitTracker.RecordHit(attacker, victim);
                                    hitCount = hitTracker.GetHitCountForPair(attacker, victim);
                                    if (hitTracker.ShouldSendWarning(attacker, victim))
                                    {
                                        attackerIdentity = attacker.GetIdentity();
                                        if (attackerIdentity && (!g_BountyBlacklistConfig || !g_BountyBlacklistConfig.IsBlacklisted(attackerIdentity.GetId())))
                                        {
                                            bountyHitsThreshold = g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
                                            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING, attackerIdentity, "", "", 0.0, 0, hitCount, bountyHitsThreshold);
                                        }
                                    }
                                    if (shouldApplyBounty)
                                    {
                                        victimIdentity = victim.GetIdentity();
                                        victimName = "Unknown";
                                        if (victimIdentity)
                                            victimName = victimIdentity.GetName();
                                        reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
                                        BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
                                        #ifdef EXPANSIONMODHARDLINE
                                        if (g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
                                        {
                                            attacker.Expansion_DecreaseReputation(g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
                                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Decreased Hardline reputation by " + g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (threshold met).");
                                        }
                                        #endif
                                        hitTracker.ClearEntry(attacker, victim);
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker attacking PvP player (hit threshold met: " + hitCount.ToString() + " hits >= " + g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + "). Blocking damage without reflection.");
                                        return false;
                                    }
                                    else
                                    {
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] PvE to PvP rule violation detected but threshold not met yet. Hits: " + hitCount.ToString() + " / " + g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits.ToString() + ". Blocking damage without applying bounty.");
                                        return false;
                                    }
                                }
                                else
                                {
                                    victimIdentity = victim.GetIdentity();
                                    victimName = "Unknown";
                                    if (victimIdentity)
                                        victimName = victimIdentity.GetName();
                                    reason = "PvE to PvP rule violation (attacked " + victimName + " who is in PvP zone)";
                                    BountyManager.ApplyBountyToPlayer(attacker, null, 0.0, reason, BountyType.RULE_BREAKER);
                                    #ifdef EXPANSIONMODHARDLINE
                                    if (g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease && g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount > 0)
                                    {
                                        attacker.Expansion_DecreaseReputation(g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount);
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Decreased Hardline reputation by " + g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount.ToString() + " for PvE-to-PvP attacker (instant apply).");
                                    }
                                    #endif
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Applied bounty to PvE attacker attacking PvP player (instant apply - threshold system disabled). Blocking damage without reflection.");
                                    return false;
                                }
                            }
                        }
                        else
                        {
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] PvE attacker already has bounty - blocking damage without applying new bounty.");
                            return false;
                        }
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] PvE-to-PvP rule breaker is disabled - blocking damage without applying bounty.");
                        return false; 
                    }
                }
            }
        }
        return super.ShouldAllowDamage(victim, damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
    }
}
#endif