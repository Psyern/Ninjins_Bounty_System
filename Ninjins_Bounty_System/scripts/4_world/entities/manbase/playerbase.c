modded class PlayerBase
{
    bool netSync_HasBounty = false;
    float netSync_BountyRemainingDuration = 0.0; 
    float m_BountyExpireTime = 0.0; 
    float m_BountyRemainingDuration = 0.0; 
    float m_BountyStartTime = 0.0; 
    float m_BountyOriginalDuration = 0.0; 
    BountyType m_BountyType = BountyType.PLACED; 
    BountyEndReason m_BountyEndReason = BountyEndReason.EXPIRED; 
    float m_BountyCooldownRemaining = 0.0; 
    bool netSync_BountyIsAdmin = false; 
    int m_PendingSuccessRewardCount = 0; 
    bool m_BountyPaused = false; 
    bool netSync_IsInSafeZone = false; 
    bool netSync_IsSZOnExit = false; 
    bool netSync_BountyPaused = false; 
    void PlayerBase()
    {
        netSync_HasBounty = false;
        netSync_BountyRemainingDuration = 0.0;
        m_BountyExpireTime = 0.0;
        m_BountyRemainingDuration = 0.0;
        m_BountyType = BountyType.PLACED;
        m_BountyEndReason = BountyEndReason.EXPIRED;
        m_BountyCooldownRemaining = 0.0;
        netSync_BountyIsAdmin = false;
        m_PendingSuccessRewardCount = 0;
        m_BountyPaused = false;
        netSync_BountyPaused = false;
        netSync_IsInSafeZone = false;
        netSync_IsSZOnExit = false;
    }
    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);
        AddAction(ActionOpenBountyMenu, InputActionMap);
    }    
    bool IsBountyAdmin()
    {
        return netSync_BountyIsAdmin;
    }
    void SetBountyAdminStatus(bool isAdmin)
    {
        if (IsMissionHost())
        {
            if (netSync_BountyIsAdmin != isAdmin)
            {
                netSync_BountyIsAdmin = isAdmin;
                SetSynchDirty(); 
            }
        }
        else
        {
            netSync_BountyIsAdmin = isAdmin;
        }
    }
    bool HasBounty()
    {
        if (!IsMissionHost())
            return netSync_HasBounty;
        if (netSync_HasBounty && m_BountyRemainingDuration > 0.0)
        {
            return true;
        }
        else if (netSync_HasBounty && m_BountyRemainingDuration <= 0.0)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] HasBounty - Bounty expired! Remaining duration: " + m_BountyRemainingDuration.ToString() + "s");
            ClearBounty(false, BountyEndReason.EXPIRED);
            return false;
        }
        return netSync_HasBounty;
    }
    bool IsRuleBreakerBounty()
    {
        return m_BountyType == BountyType.RULE_BREAKER;
    }
    BountyType GetBountyType()
    {
        return m_BountyType;
    }
    BountyEndReason GetBountyEndReason()
    {
        return m_BountyEndReason;
    }
    float GetBountyRemainingDuration()
    {
        return m_BountyRemainingDuration;
    }
    void UpdateBountyDurationBeforeDeath()
    {
        float currentTime;
        float calculatedRemainingDuration;
        if (!IsMissionHost())
            return;
        if (netSync_HasBounty && m_BountyRemainingDuration > 0.0)
        {
            currentTime = g_Game.GetTime(); 
            if (m_BountyExpireTime > 0.0 && m_BountyExpireTime > currentTime)
            {
                calculatedRemainingDuration = (m_BountyExpireTime - currentTime) / BOUNTY_MS_TO_SECONDS; 
                if (calculatedRemainingDuration > 0.0)
                {
                    m_BountyRemainingDuration = calculatedRemainingDuration;
                    if (netSync_BountyRemainingDuration != m_BountyRemainingDuration)
                    {
                        netSync_BountyRemainingDuration = m_BountyRemainingDuration;
                        SetSynchDirty();
                    }
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Updated remaining duration to " + m_BountyRemainingDuration.ToString() + "s (from expireTime: " + m_BountyExpireTime.ToString() + "ms, currentTime: " + currentTime.ToString() + "ms, difference: " + (m_BountyExpireTime - currentTime).ToString() + "ms)");
                }
                else
                {
                    m_BountyRemainingDuration = 0.0;
                    netSync_BountyRemainingDuration = 0.0;
                    m_BountyExpireTime = 0.0;
                    SetSynchDirty();
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Bounty has expired");
                }
            }
            else if (m_BountyExpireTime > 0.0 && m_BountyExpireTime <= currentTime)
            {
                m_BountyRemainingDuration = 0.0;
                netSync_BountyRemainingDuration = 0.0;
                m_BountyExpireTime = 0.0;
                SetSynchDirty();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Bounty expired (expireTime in past)");
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty] UpdateBountyDurationBeforeDeath: ExpireTime not available, using m_BountyRemainingDuration: " + m_BountyRemainingDuration.ToString() + "s");
            }
        }
    }
    void UpdateBountyDuration(float deltaTime)
    {
        float currentTime;
        float oldDuration;
        PlayerIdentity identity;
        if (!IsMissionHost())
            return;
        if (!IsAlive())
            return;
        if (netSync_HasBounty && m_BountyRemainingDuration > 0.0)
        {
            currentTime = g_Game.GetTime();
            if (m_BountyPaused)
            {
                m_BountyExpireTime = currentTime + (m_BountyRemainingDuration * BOUNTY_MS_TO_SECONDS);
                return;
            }
            oldDuration = m_BountyRemainingDuration;
            m_BountyRemainingDuration = m_BountyRemainingDuration - deltaTime;
            if (netSync_BountyRemainingDuration != m_BountyRemainingDuration)
            {
                netSync_BountyRemainingDuration = m_BountyRemainingDuration;
                SetSynchDirty();
            }
            m_BountyExpireTime = currentTime + (m_BountyRemainingDuration * BOUNTY_MS_TO_SECONDS);
            if (m_BountyRemainingDuration <= 0.0)
            {
                m_BountyRemainingDuration = 0.0;
                netSync_BountyRemainingDuration = 0.0; 
                m_BountyExpireTime = 0.0;
                SetSynchDirty();
                identity = GetIdentity();
                if (identity)
                {
                    Param1<float> paramCountdown = new Param1<float>(0.0);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
                }
                ClearBounty(false, BountyEndReason.EXPIRED);
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Bounty duration expired for player.");
            }
        }
    }
    bool IsBountyOnCooldown()
    {
        if (!IsMissionHost())
            return false;
        if (!g_BountyConfig || !g_BountyConfig.Core || g_BountyConfig.Core.BountyCooldownSeconds <= 0.0)
        {
            if (m_BountyCooldownRemaining > 0.0)
                m_BountyCooldownRemaining = 0.0;
            return false;
        }
        if (m_BountyCooldownRemaining <= 0.0)
        {
            return false;
        }
        return true;
    }
    float GetBountyCooldownRemaining()
    {
        if (!IsMissionHost())
            return 0.0;
        return m_BountyCooldownRemaining;
    }
    void ClearBountyCooldown()
    {
        if (!IsMissionHost())
            return;
        m_BountyCooldownRemaining = 0.0;
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cooldown cleared for player: " + GetIdentity().GetName());
    }
    void UpdateBountyCooldown(float deltaTime)
    {
        if (!IsMissionHost())
            return;
        if (m_BountyCooldownRemaining > 0.0)
        {
            m_BountyCooldownRemaining = m_BountyCooldownRemaining - deltaTime;
            if (m_BountyCooldownRemaining <= 0.0)
            {
                m_BountyCooldownRemaining = 0.0;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cooldown expired for player.");
            }
        }
    }
    void SetBounty(float durationSeconds, bool isRuleBreaker = false, bool skipNotifications = false)
    {
        BountyType bountyType = BountyType.PLACED;
        if (isRuleBreaker)
            bountyType = BountyType.RULE_BREAKER;
        SetBountyWithType(durationSeconds, bountyType, skipNotifications);
    }
    void SetBountyWithType(float durationSeconds, BountyType bountyType = BountyType.PLACED, bool skipNotifications = false, int clearedRewardCount = 0)
    {
        bool alreadyHasBounty;
        BountyManager bountyManager;
        int currentBountiedCount;
        float currentTime;
        float currentTimeSeconds;
        PlayerIdentity identity;
        string playerName;
        string configRewardStr;
        bool inOwnTerritory;
        float territorySize;
        vector flagPos;
        Managed territoryModule;
        vector playerPos;
        string playerUID;
        Managed territorySettings;
        float territorySizeSq;
        map<int, TerritoryFlag> territoryFlags;
        float distSq;
        bool isOwner;
        string ownerID;
        bool isMember;
        string pauseBountyInTerritoryStr;
        string configStatus;
        bool isNinjinsSafeZone;
        bool ninjinsState;
        if (!IsMissionHost())
            return;
        if (!BountyConfig.IsSystemActive())
            return;
        alreadyHasBounty = HasBounty();
        if (g_BountyConfig.Core && g_BountyConfig.Core.MaxBountiedPlayers == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cannot set bounty - bounties are disabled (MaxBountiedPlayers = 0)");
            return;
        }
        else if (g_BountyConfig.Core && g_BountyConfig.Core.MaxBountiedPlayers > 0 && bountyType != BountyType.RULE_BREAKER)
        {
            bountyManager = BountyManager.GetInstance();
            currentBountiedCount = bountyManager.GetBountiedPlayerCount();
            if (!alreadyHasBounty && currentBountiedCount >= g_BountyConfig.Core.MaxBountiedPlayers)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cannot set bounty - maximum bountied players limit reached (" + currentBountiedCount.ToString() + "/" + g_BountyConfig.Core.MaxBountiedPlayers.ToString() + ")");
                return;
            }
        }
        currentTime = g_Game.GetTime(); 
        currentTimeSeconds = currentTime / BOUNTY_MS_TO_SECONDS; 
        if (m_BountyRemainingDuration > 0.0)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player already has active bounty with remaining duration: " + m_BountyRemainingDuration.ToString() + "s - preserving it instead of resetting to " + durationSeconds.ToString() + "s");
            m_BountyStartTime = currentTimeSeconds;
            m_BountyOriginalDuration = m_BountyRemainingDuration; 
        }
        else
        {
            m_BountyRemainingDuration = durationSeconds; 
            m_BountyStartTime = currentTimeSeconds; 
            m_BountyOriginalDuration = durationSeconds; 
        }
        netSync_BountyRemainingDuration = m_BountyRemainingDuration; 
        m_BountyExpireTime = currentTime + (m_BountyRemainingDuration * 1000.0); 
        SetSynchDirty();
        m_BountyType = bountyType; 
        identity = GetIdentity();
        playerName = "Unknown";
        if (identity)
            playerName = identity.GetName();
        configRewardStr = "null";
        if (g_BountyConfig)
        {
            configRewardStr = "false";
            if (g_BountyConfig.Reward && g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
                configRewardStr = "true";
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] SetBounty - Player: " + playerName + ", BountyType: " + m_BountyType.ToString() + ", PvERuleBreakerGiveRewards: " + configRewardStr);
        if (m_BountyType == BountyType.RULE_BREAKER)
        {
            m_BountyCooldownRemaining = 0.0; 
        }
        else if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.BountyCooldownSeconds > 0.0)
        {
            m_BountyCooldownRemaining = g_BountyConfig.Core.BountyCooldownSeconds;
        }
        else
        {
            m_BountyCooldownRemaining = 0.0;
        }
        netSync_HasBounty = true;
        SetSynchDirty();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] SetBounty - CurrentTime: " + currentTime.ToString() + "ms, Duration: " + durationSeconds.ToString() + "s, ExpireTime: " + m_BountyExpireTime.ToString() + "ms");
        identity = GetIdentity();
        if (identity)
        {
            playerName = identity.GetName();
            Param1<bool> paramBounty = new Param1<bool>(true);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "UpdateBountyState", paramBounty, true, identity);
            Param1<float> paramCountdown = new Param1<float>(durationSeconds);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
            if (!skipNotifications)
            {
                if (m_BountyType == BountyType.RULE_BREAKER)
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED, identity, "", "", durationSeconds, clearedRewardCount);
                }
                else
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_HUNTED, identity, "", "", durationSeconds);
                }
                if (!alreadyHasBounty)
                {
                    if (m_BountyType == BountyType.RULE_BREAKER)
                    {
                        BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST, null, playerName, "", durationSeconds);
                    }
                    else
                    {
                        BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_BROADCAST, null, playerName, "", durationSeconds);
                    }
                }
            }
        }
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfOwnTerritory)
        {
            inOwnTerritory = false;
            territorySize = -1.0;
            flagPos = "0 0 0";
            #ifdef EXPANSIONMODBASEBUILDING
            territoryModule = CF_ModuleCoreManager.Get(ExpansionTerritoryModule);
            if (territoryModule)
            {
                playerPos = GetPosition();
                playerUID = GetIdentity().GetId();
                territorySize = BOUNTY_DEFAULT_TERRITORY_SIZE; 
                territorySettings = GetExpansionSettings().GetTerritory();
                if (territorySettings)
                {
                    EnScript.GetClassVar(territorySettings, "TerritorySize", 0, territorySize);
                }
                territorySizeSq = territorySize * territorySize; 
                g_Script.CallFunction(territoryModule, "GetAllTerritoryFlags", territoryFlags, null);
                if (territoryFlags)
                {
                    foreach (int territoryID, TerritoryFlag flag: territoryFlags)
                    {
                        if (!flag)
                            continue;
                        if (flag.HasExpansionTerritoryInformation())
                        {
                            ExpansionTerritory territory = flag.GetTerritory();
                            if (!territory)
                                continue;
                            distSq = vector.DistanceSq(territory.GetPosition(), playerPos);
                            isOwner = false;
                            EnScript.GetClassVar(territory, "TerritoryOwnerID", 0, ownerID);
                            isOwner = (ownerID == playerUID);
                            isMember = false;
                            if (!isOwner)
                            {
                                g_Script.CallFunction(territory, "IsMember", isMember, playerUID);
                            }
                            if (distSq <= territorySizeSq && (isOwner || isMember))
                            {
                                inOwnTerritory = true;
                                flagPos = flag.GetPosition(); 
                                break;
                            }
                        }
                    }
                }
            }
            #endif
            if (!inOwnTerritory)
            {
                inOwnTerritory = IsPlayerInOwnTerritory();
            }
            pauseBountyInTerritoryStr = "false";
            if (g_BountyConfig.Core.PauseBountyInTerritory)
                pauseBountyInTerritoryStr = "true";
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory check - Player " + playerName + " in own territory: " + inOwnTerritory.ToString() + ", PauseBountyInTerritory: " + pauseBountyInTerritoryStr);
            if (inOwnTerritory)
            {
                if (g_BountyConfig.Core.PauseBountyInTerritory)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " is in own territory when bounty was placed - pausing bounty timer...");
                    PauseBounty();
                    if (identity)
                    {
                        BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY, identity);
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " is in own territory when bounty was placed - teleporting out...");
                    TeleportOutOfOwnTerritory(territorySize, flagPos);
                }
            }
        }
        else
        {
            configStatus = "null";
            if (g_BountyConfig && g_BountyConfig.Core)
                configStatus = g_BountyConfig.Core.TeleportOutOfOwnTerritory.ToString();
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory check - Player " + playerName + " - TeleportOutOfOwnTerritory config: " + configStatus);
        }
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZone)
        {
            if (NinjinBountyIsPlayerInSafezone())
            {
                isNinjinsSafeZone = false;
                ninjinsState = false;
                if (EnScript.GetClassVar(this, "netSync_IsInSafeZone", 0, ninjinsState))
                {
                    isNinjinsSafeZone = ninjinsState;
                }
                if (isNinjinsSafeZone)
                {
                    if (NinjinBountyIsOnSafeZoneExitTimer())
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " is in NinjinsPvPPvE safezone when bounty was placed but has active exit timer (netSync_IsSZOnExit = true) - skipping teleport");
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " is in safezone when bounty was placed - teleporting out...");
                        TeleportOutOfSafeZone();
                    }
                }
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " has been marked with a bounty for " + durationSeconds.ToString() + " seconds.");
    }
    void ClearBounty(bool skipRewards = false, BountyEndReason endReason = BountyEndReason.CLEARED)
    {
        PlayerIdentity identity;
        string playerName;
        bool playerSurvived;
        BountyType wasBountyType;
        bool shouldGiveReward;
        if (!IsMissionHost())
            return;
        if (!netSync_HasBounty)
            return;
        netSync_HasBounty = false;
        netSync_BountyRemainingDuration = 0.0;
        m_BountyExpireTime = 0.0;
        m_BountyRemainingDuration = 0.0;
        m_BountyStartTime = 0.0;
        m_BountyOriginalDuration = 0.0;
        SetSynchDirty();
        identity = GetIdentity();
        playerName = "Unknown";
        playerSurvived = IsAlive(); 
        wasBountyType = m_BountyType;
        m_BountyEndReason = endReason;
        m_BountyType = BountyType.PLACED;
        SetSynchDirty();
        identity = GetIdentity();
        if (identity)
        {
            playerName = identity.GetName();
            Param1<bool> paramBounty = new Param1<bool>(false);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "UpdateBountyState", paramBounty, true, identity);
            Param1<float> paramCountdown = new Param1<float>(0.0);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
            if (wasBountyType == BountyType.RULE_BREAKER)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " was a rule breaker - sending rule breaker expiration notification. EndReason: " + endReason.ToString());
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED, identity);
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " was NOT a rule breaker - sending regular expiration notification. EndReason: " + endReason.ToString());
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_EXPIRED, identity);
            }
            shouldGiveReward = true;
            if (skipRewards)
            {
                shouldGiveReward = false;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " skipped bounty - skipping success reward (survival type)");
            }
            else if (wasBountyType == BountyType.RULE_BREAKER && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
            {
                shouldGiveReward = false;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " was a rule breaker - skipping success reward (survival type) (PvERuleBreakerGiveRewards = false)");
            }
            if (playerSurvived && g_BountyConfig && g_BountyConfig.Reward && g_BountyConfig.Reward.EnableSurvivalReward)
            {
                if (shouldGiveReward)
                {
                    AddPendingSuccessReward(1);
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, wasBountyType, true);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " survived bounty - set pending success reward (survival type) (must claim at bounty board).");
                }
                else
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, wasBountyType, false);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + playerName + " survived rule breaker bounty - no reward given.");
                }
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Bounty cleared for player " + playerName + ".");
    }
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        UpdateBountyDurationBeforeDeath();
        PlayerIdentity victimIdentity;
        PlayerIdentity killerIdentity;
        string victimName;
        string killerName;
        PlayerBase killerPlayer;
        bool shouldGiveReward;
        bool isSuicide;
        string playerId;
        float currentTime;
        float actualRemainingDuration;
        float calculatedFromExpireTime;
        if (!IsMissionHost())
            return;
        if (!HasBounty())
            return;
        if (!g_BountyConfig || !g_BountyConfig.Core || !g_BountyConfig.Core.EnableBountySystem)
            return;
        #ifdef NinjinsPvPPvE
        DamageUtils dmgUtils;
        AttackerContext ctx;
        dmgUtils = DamageUtils.GetInstance();
        ctx = dmgUtils.ResolveAttacker(EntityAI.Cast(killer));
        dmgUtils.GrenadeAttackerContext(ctx, EntityAI.Cast(killer));
        killerPlayer = ctx.Player;
        #else
        killerPlayer = null;
        if (killer && killer.IsInherited(SurvivorBase))
        {
            killerPlayer = PlayerBase.Cast(killer);
        }
        #endif
        isSuicide = (!killerPlayer || killerPlayer == this);
        if (isSuicide)
        {
            victimIdentity = GetIdentity();
            victimName = BOUNTY_PLAYER_NAME_UNKNOWN;
            playerId = "";
            if (victimIdentity)
            {
                victimName = victimIdentity.GetName();
                playerId = victimIdentity.GetId();
            }
            currentTime = g_Game.GetTime(); 
            actualRemainingDuration = m_BountyRemainingDuration;
            if (m_BountyExpireTime > 0.0 && m_BountyExpireTime > currentTime)
            {
                calculatedFromExpireTime = (m_BountyExpireTime - currentTime) / 1000.0;
                if (calculatedFromExpireTime > 0.0)
                {
                    actualRemainingDuration = calculatedFromExpireTime;
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Calculated remaining duration from expireTime: " + actualRemainingDuration.ToString() + "s (expireTime: " + m_BountyExpireTime.ToString() + "ms, currentTime: " + currentTime.ToString() + "ms, m_BountyRemainingDuration was: " + m_BountyRemainingDuration.ToString() + "s)");
                }
            }
            if (actualRemainingDuration < 0.0)
                actualRemainingDuration = 0.0;
            m_BountyRemainingDuration = actualRemainingDuration;
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Player " + victimName + " committed suicide while having a bounty. Bounty timer preserved - will resume on respawn. RemainingDuration: " + actualRemainingDuration.ToString() + "s");
            if (!netSync_HasBounty && actualRemainingDuration > 0.0)
            {
                netSync_HasBounty = true;
                SetSynchDirty();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Restored netSync_HasBounty flag after suicide detection");
            }
            if (actualRemainingDuration > 0.0)
            {
                netSync_HasBounty = true;
                SetSynchDirty();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Ensured netSync_HasBounty=true before death to preserve bounty state for CF ModStorage");
            }
            if (playerId != "" && actualRemainingDuration > 0.0)
            {
                BountyManager bountyManager = BountyManager.GetInstance();
                if (bountyManager)
                {
                    bountyManager.PreserveBountyForPlayer(playerId, actualRemainingDuration, m_BountyType, m_BountyStartTime, m_BountyOriginalDuration);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Preserved bounty in BountyManager - RemainingDuration: " + actualRemainingDuration.ToString() + "s, StartTime: " + m_BountyStartTime.ToString() + "s, OriginalDuration: " + m_BountyOriginalDuration.ToString() + "s");
                }
            }
            return; 
        }
        if (killerPlayer && killerPlayer != this && killerPlayer.GetIdentity())
        {
            victimIdentity = GetIdentity();
            killerIdentity = killerPlayer.GetIdentity();
            victimName = BOUNTY_PLAYER_NAME_UNKNOWN;
            killerName = BOUNTY_PLAYER_NAME_UNKNOWN;
            if (victimIdentity)
                victimName = victimIdentity.GetName();
            if (killerIdentity)
                killerName = killerIdentity.GetName();
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Bountied player " + victimName + " was killed by " + killerName + ".");
            shouldGiveReward = true;
            if (killerPlayer.IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
            {
                shouldGiveReward = false;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Killer " + killerName + " is a rule breaker - skipping success reward (kill type) (PvERuleBreakerGiveRewards = false)");
            }
            else if (m_BountyType == BountyType.RULE_BREAKER && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
            {
                shouldGiveReward = false;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Victim " + victimName + " was a rule breaker - skipping success reward (kill type) for " + killerName + " (PvERuleBreakerGiveRewards = false)");
            }
            if (shouldGiveReward)
            {
                killerPlayer.AddPendingSuccessReward(1);
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Set pending success reward (kill type) for " + killerName + " (must claim at bounty board)");
            }
            if (killerIdentity)
            {
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD, killerIdentity, "", victimName, 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, m_BountyType, shouldGiveReward);
            }
        }
        ClearBounty(false, BountyEndReason.KILLED);
    }
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);
        switch (rpc_type)
        {
            case BountyRPC.UPDATE_BOUNTY_STATE:
            {
                Param1<bool> paramBounty;
                if (ctx.Read(paramBounty))
                {
                    if (netSync_HasBounty != paramBounty.param1)
                    {
                        netSync_HasBounty = paramBounty.param1;
                        SetSynchDirty();
                        PlayerIdentity identity = GetIdentity();
                        string playerName = BOUNTY_PLAYER_NAME_UNKNOWN;
                        if (identity)
                        {
                            playerName = identity.GetName();
                        }
                        if (IsMissionHost())
                        {
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Bounty state changed for " + playerName + ": " + netSync_HasBounty);
                        }
                        else
                        {
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty][Client] Bounty state changed: " + netSync_HasBounty);
                        }
                    }
                }
                break;
            }
            case BountyRPC.SYNC_ADMIN_STATUS:
            {
                if (IsMissionHost())
                    break;
                Param1<bool> adminParam;
                if (ctx.Read(adminParam))
                {
                    netSync_BountyIsAdmin = adminParam.param1;
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty][Client] Admin status synced from server: " + netSync_BountyIsAdmin.ToString());
                }
                break;
            }
        }
    }
    override void CF_OnStoreSave(CF_ModStorageMap storage)
    {
        super.CF_OnStoreSave(storage);
        if (!IsMissionHost())
            return;
        auto ctx = storage["Ninjins_Bounty_System"];
        if (!ctx)
            return;
        ctx.Write(netSync_HasBounty);
        ctx.Write(m_BountyRemainingDuration); 
        ctx.Write(m_BountyType); 
        ctx.Write(m_BountyStartTime); 
        ctx.Write(m_BountyOriginalDuration); 
        ctx.Write(m_BountyCooldownRemaining);
        ctx.Write(m_PendingSuccessRewardCount);
        ctx.Write(m_PendingSuccessRewardCount); 
        string bountyTypeStr = BOUNTY_TYPE_STRING_PLACED;
        if (m_BountyType == BountyType.RULE_BREAKER)
            bountyTypeStr = BOUNTY_TYPE_STRING_RULE_BREAKER;
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Saved player data (CF ModStorage) - HasBounty: " + netSync_HasBounty.ToString() + ", BountyRemainingDuration: " + m_BountyRemainingDuration.ToString() + "s, BountyType: " + bountyTypeStr + ", BountyCooldownRemaining: " + m_BountyCooldownRemaining.ToString() + "s, PendingSuccessRewardCount: " + m_PendingSuccessRewardCount.ToString());
    }
    override bool CF_OnStoreLoad(CF_ModStorageMap storage)
    {
        if (!super.CF_OnStoreLoad(storage))
            return false;
        if (!IsMissionHost())
            return true;
        PlayerIdentity identity = GetIdentity();
        string playerName = BOUNTY_PLAYER_NAME_UNKNOWN;
        if (identity)
            playerName = identity.GetName();
        auto ctx = storage["Ninjins_Bounty_System"];
        if (!ctx)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - No CF ModStorage context found for " + playerName + " - player has no saved bounty data");
            return true;
        }
        bool savedHasBounty = false;
        float savedBountyRemainingDuration = 0.0;
        BountyType savedBountyType = BountyType.PLACED;
        float savedBountyStartTime = 0.0;
        float savedBountyOriginalDuration = 0.0;
        bool readNewFormat = ctx.Read(savedHasBounty) && ctx.Read(savedBountyRemainingDuration) && ctx.Read(savedBountyType) && ctx.Read(savedBountyStartTime) && ctx.Read(savedBountyOriginalDuration);
        if (!readNewFormat)
        {
            savedBountyStartTime = 0.0;
            savedBountyOriginalDuration = 0.0;
            if (!ctx.Read(savedHasBounty) || !ctx.Read(savedBountyRemainingDuration) || !ctx.Read(savedBountyType))
            {
                netSync_HasBounty = false;
                m_BountyRemainingDuration = 0.0;
                m_BountyExpireTime = 0.0;
                m_BountyType = BountyType.PLACED;
                m_BountyStartTime = 0.0;
                m_BountyOriginalDuration = 0.0;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Failed to read bounty state from CF ModStorage for " + playerName + " - initialized to false");
                return false;
            }
        }
        string savedBountyTypeStr = BOUNTY_TYPE_STRING_PLACED;
        if (savedBountyType == BountyType.RULE_BREAKER)
            savedBountyTypeStr = BOUNTY_TYPE_STRING_RULE_BREAKER;
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() for " + playerName + " - savedHasBounty: " + savedHasBounty.ToString() + ", savedBountyRemainingDuration: " + savedBountyRemainingDuration.ToString() + "s, savedBountyType: " + savedBountyTypeStr + ", savedBountyStartTime: " + savedBountyStartTime.ToString() + "s, savedBountyOriginalDuration: " + savedBountyOriginalDuration.ToString() + "s");
        if (savedHasBounty && savedBountyRemainingDuration > 0.0)
        {
            netSync_HasBounty = true;
            m_BountyType = savedBountyType;
            bool appearsStale = false;
            if (savedBountyOriginalDuration > BOUNTY_SECONDS_PER_DAY && savedBountyStartTime > 0.0) 
            {
                float difference = savedBountyOriginalDuration - savedBountyRemainingDuration;
                float percentUsed = (difference / savedBountyOriginalDuration) * 100.0;
                if (percentUsed < BOUNTY_STALE_DURATION_THRESHOLD_PERCENT) 
                {
                    appearsStale = true;
                    GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty] CF_OnStoreLoad() - Saved remaining duration appears stale (only " + percentUsed.ToString() + "% used), recalculating from start time");
                }
            }
            if (appearsStale && savedBountyOriginalDuration > 86400.0 && savedBountyStartTime > 0.0)
            {
                float currentTimeSeconds = g_Game.GetTime() / BOUNTY_MS_TO_SECONDS; 
                float elapsedTime = currentTimeSeconds - savedBountyStartTime;
                float recalculatedRemaining = savedBountyOriginalDuration - elapsedTime;
                if (recalculatedRemaining > 0.0)
                {
                    m_BountyRemainingDuration = recalculatedRemaining;
                    m_BountyStartTime = savedBountyStartTime; 
                    m_BountyOriginalDuration = savedBountyOriginalDuration; 
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Recalculated remaining duration for large bounty (stale detection): " + m_BountyRemainingDuration.ToString() + "s (original saved: " + savedBountyRemainingDuration.ToString() + "s, elapsed: " + elapsedTime.ToString() + "s)");
                }
                else
                {
                    m_BountyRemainingDuration = 0.0;
                    m_BountyStartTime = 0.0;
                    m_BountyOriginalDuration = 0.0;
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Large bounty expired during downtime (elapsed: " + elapsedTime.ToString() + "s > original: " + savedBountyOriginalDuration.ToString() + "s)");
                }
            }
            else
            {
                m_BountyRemainingDuration = savedBountyRemainingDuration;
                m_BountyStartTime = savedBountyStartTime;
                if (savedBountyOriginalDuration > 0.0)
                    m_BountyOriginalDuration = savedBountyOriginalDuration;
                else
                    m_BountyOriginalDuration = savedBountyRemainingDuration;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Using saved remaining duration (timer paused while offline): " + m_BountyRemainingDuration.ToString() + "s");
            }
            float currentTime = g_Game.GetTime();
            m_BountyExpireTime = currentTime + (m_BountyRemainingDuration * BOUNTY_MS_TO_SECONDS);
            SetSynchDirty();
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Restored bounty state for " + playerName + " - RemainingDuration: " + m_BountyRemainingDuration.ToString() + "s, BountyType: " + savedBountyTypeStr);
        }
        else if (savedHasBounty && savedBountyRemainingDuration <= 0.0)
        {
            netSync_HasBounty = false;
            m_BountyRemainingDuration = 0.0;
            m_BountyExpireTime = 0.0;
            m_BountyType = BountyType.PLACED;
            m_BountyEndReason = BountyEndReason.EXPIRED;
            m_BountyStartTime = 0.0;
            m_BountyOriginalDuration = 0.0;
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - Bounty expired during downtime for " + playerName + " - cleared");
        }
        else
        {
            netSync_HasBounty = false;
            m_BountyRemainingDuration = 0.0;
            m_BountyExpireTime = 0.0;
            m_BountyType = BountyType.PLACED;
            m_BountyStartTime = 0.0;
            m_BountyOriginalDuration = 0.0;
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CF_OnStoreLoad() - No saved bounty for " + playerName + " - initialized to false");
        }
        if (!ctx.Read(m_BountyCooldownRemaining))
        {
            m_BountyCooldownRemaining = 0.0;
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] No saved BountyCooldownRemaining found - initialized to 0");
        }
        else
        {
            if (m_BountyCooldownRemaining < 0.0)
                m_BountyCooldownRemaining = 0.0;
            if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.BountyCooldownSeconds <= 0.0)
            {
                m_BountyCooldownRemaining = 0.0;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cooldown disabled in config - reset BountyCooldownRemaining");
            }
            else if (m_BountyCooldownRemaining > 0.0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Loaded player data - BountyCooldownRemaining: " + m_BountyCooldownRemaining.ToString() + "s (cooldown will continue)");
            }
        }
        int savedPendingSuccessRewardKillCount = 0;
        int savedPendingSuccessRewardSurvivalCount = 0;
        if (!ctx.Read(savedPendingSuccessRewardKillCount) || !ctx.Read(savedPendingSuccessRewardSurvivalCount))
        {
            bool savedPendingSuccessRewardKill = false;
            bool savedPendingSuccessRewardSurvival = false;
            if (ctx.Read(savedPendingSuccessRewardKill) && ctx.Read(savedPendingSuccessRewardSurvival))
            {
                int combinedCount = 0;
                if (savedPendingSuccessRewardKill)
                    combinedCount = combinedCount + 1;
                if (savedPendingSuccessRewardSurvival)
                    combinedCount = combinedCount + 1;
                m_PendingSuccessRewardCount = combinedCount;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Loaded pending rewards (old boolean format) - Combined into unified count: " + m_PendingSuccessRewardCount.ToString());
            }
            else
            {
                m_PendingSuccessRewardCount = 0;
            }
        }
        else
        {
            if (savedPendingSuccessRewardKillCount < 0)
                savedPendingSuccessRewardKillCount = 0;
            if (savedPendingSuccessRewardSurvivalCount < 0)
                savedPendingSuccessRewardSurvivalCount = 0;
            m_PendingSuccessRewardCount = savedPendingSuccessRewardKillCount + savedPendingSuccessRewardSurvivalCount;
            if (m_PendingSuccessRewardCount > 0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Loaded pending rewards (old format, combined) - SuccessRewardCount: " + m_PendingSuccessRewardCount.ToString() + " (was: kill=" + savedPendingSuccessRewardKillCount.ToString() + ", survival=" + savedPendingSuccessRewardSurvivalCount.ToString() + ")");
            }
        }
        return true;
    }
    override void OnConnect()
    {
        super.OnConnect();
        if (!IsMissionHost())
            return;
        PlayerIdentity identity = GetIdentity();
        string playerName = BOUNTY_PLAYER_NAME_UNKNOWN;
        string playerId = "";
        if (identity)
        {
            playerName = identity.GetName();
            playerId = identity.GetId();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] OnConnect() called for " + playerName + " - netSync_HasBounty: " + netSync_HasBounty.ToString() + ", m_BountyRemainingDuration: " + m_BountyRemainingDuration.ToString() + "s");
        if (m_BountyRemainingDuration <= 0.0 && playerId != "")
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                BountyPreservedData preservedData = bountyManager.GetPreservedBountyForPlayer(playerId);
                if (preservedData && preservedData.RemainingDuration > 0.0)
                {
                    m_BountyRemainingDuration = preservedData.RemainingDuration;
                    m_BountyType = preservedData.Type;
                    m_BountyStartTime = preservedData.StartTime;
                    m_BountyOriginalDuration = preservedData.OriginalDuration;
                    if (preservedData.OriginalDuration > 86400.0 && preservedData.StartTime > 0.0)
                    {
                        float currentTimeSeconds = g_Game.GetTime() / 1000.0;
                        float elapsedTime = currentTimeSeconds - preservedData.StartTime;
                        float recalculatedRemaining = preservedData.OriginalDuration - elapsedTime;
                        if (recalculatedRemaining > 0.0)
                        {
                            m_BountyRemainingDuration = recalculatedRemaining;
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Recalculated remaining duration from preserved timestamp: " + m_BountyRemainingDuration.ToString() + "s (original preserved: " + preservedData.RemainingDuration.ToString() + "s, elapsed: " + elapsedTime.ToString() + "s)");
                        }
                    }
                    netSync_HasBounty = true;
                    SetSynchDirty();
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Restored bounty from BountyManager preserved data for " + playerName + " - RemainingDuration: " + m_BountyRemainingDuration.ToString() + "s, BountyType: " + m_BountyType.ToString() + ", StartTime: " + m_BountyStartTime.ToString() + "s, OriginalDuration: " + m_BountyOriginalDuration.ToString() + "s");
                }
            }
        }
        if (m_BountyRemainingDuration > 0.0)
        {
            netSync_HasBounty = true;
            float currentTime = g_Game.GetTime();
            m_BountyExpireTime = currentTime + (m_BountyRemainingDuration * BOUNTY_MS_TO_SECONDS);
            SetSynchDirty();
            Param1<bool> paramBounty = new Param1<bool>(true);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "UpdateBountyState", paramBounty, true, identity);
            Param1<float> paramCountdown = new Param1<float>(m_BountyRemainingDuration);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_BOUNTY_PERSISTED, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", m_BountyRemainingDuration);
            string bountyTypeStr = "PLACED";
            if (m_BountyType == BountyType.RULE_BREAKER)
                bountyTypeStr = "RULE_BREAKER";
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Restored bounty on respawn for " + playerName + " - RemainingDuration: " + m_BountyRemainingDuration.ToString() + "s, BountyType: " + bountyTypeStr);
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] OnConnect() - No bounty to restore for " + playerName + " (m_BountyRemainingDuration: " + m_BountyRemainingDuration.ToString() + "s)");
        }
        if (g_BountyConfig && g_BountyConfig.UI && identity)
        {
            float posX = g_BountyConfig.UI.CountdownWidgetPositionX;
            float posY = g_BountyConfig.UI.CountdownWidgetPositionY;
            float width = g_BountyConfig.UI.CountdownWidgetWidth;
            float height = g_BountyConfig.UI.CountdownWidgetHeight;
            int bgColor = g_BountyConfig.UI.CountdownWidgetBackgroundColor;
            int textColor = g_BountyConfig.UI.CountdownWidgetTextColor;
            BountyUISettingsData uiData = new BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
            Param1<BountyUISettingsData> uiParam = new Param1<BountyUISettingsData>(uiData);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, identity);
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Sent UI settings to client on connect: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
        }
    }
    bool HasPendingRewards()
    {
        return m_PendingSuccessRewardCount > 0;
    }
    int GetPendingSuccessRewardCount()
    {
        return m_PendingSuccessRewardCount;
    }
    int GetTotalPendingRewardCount()
    {
        return m_PendingSuccessRewardCount;
    }
    void AddPendingSuccessReward(int amount = 1)
    {
        if (!IsMissionHost())
            return;
        if (amount < 0)
            amount = 0;
        m_PendingSuccessRewardCount = m_PendingSuccessRewardCount + amount;
        SetSynchDirty();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Added pending success reward: " + amount.ToString() + " (total: " + m_PendingSuccessRewardCount.ToString() + ")");
    }
    void RemovePendingSuccessReward(int amount = 1)
    {
        if (!IsMissionHost())
            return;
        if (amount < 0)
            amount = 0;
        if (m_PendingSuccessRewardCount >= amount)
        {
            m_PendingSuccessRewardCount = m_PendingSuccessRewardCount - amount;
        }
        else
        {
            m_PendingSuccessRewardCount = 0;
        }
        SetSynchDirty();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Removed pending success reward: " + amount.ToString() + " (remaining: " + m_PendingSuccessRewardCount.ToString() + ")");
    }
    void ClaimPendingSuccessReward()
    {
        if (!IsMissionHost())
            return;
        if (m_PendingSuccessRewardCount > 0)
        {
            m_PendingSuccessRewardCount = m_PendingSuccessRewardCount - 1;
            SetSynchDirty();
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Claimed 1 success reward (remaining: " + m_PendingSuccessRewardCount.ToString() + ")");
        }
    }
    void ClearPendingRewards()
    {
        if (!IsMissionHost())
            return;
        if (HasBounty() && IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Prevented clearing pending rewards - player has rule breaker bounty and PvERuleBreakerGiveRewards is enabled");
            return;
        }
        m_PendingSuccessRewardCount = 0;
        SetSynchDirty();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Cleared all pending rewards");
    }
    bool IsPlayerInOwnTerritory()
    {
        if (NinjinsBountyRearmedIsInOwnTerritory(this))
        {
            return true;
        }
        if (NinjinsBountyBasicTerritoriesIsInOwnTerritory(this))
        {
            return true;
        }
        return false;
    }
    void PauseBounty()
    {
        PlayerIdentity identity;
        if (!IsMissionHost())
            return;
        if (!netSync_HasBounty)
            return;
        m_BountyPaused = true;
        netSync_BountyPaused = true;
        SetSynchDirty();
        identity = GetIdentity();
        if (identity)
        {
            Param1<bool> paramPaused = new Param1<bool>(true);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdatePaused", paramPaused, true, identity);
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Paused bounty timer for player " + GetIdentity().GetName());
    }
    bool IsFarEnoughFromTerritory()
    {
        float requiredDistance;
        vector playerPos;
        string playerUID;
        BountyManager bountyManager;
        array<int> playerTerritoryIDs;
        float territorySize;
        TerritoryCacheData firstTerritory;
        float minDistanceRequired;
        float minDistanceRequiredSq;
        int i;
        int territoryID;
        TerritoryCacheData cacheData;
        float distSq;
        if (!IsMissionHost())
            return false;
        if (!netSync_HasBounty)
            return false;
        if (!g_BountyConfig || !g_BountyConfig.Core)
            return false;
        requiredDistance = g_BountyConfig.Core.ResumeBountyDistanceFromTerritory;
        if (requiredDistance <= 0.0)
            requiredDistance = BOUNTY_DEFAULT_TELEPORT_DISTANCE; 
        playerPos = GetPosition();
        playerUID = GetIdentity().GetId();
        #ifdef EXPANSIONMODBASEBUILDING
        bountyManager = BountyManager.GetInstance();
        if (bountyManager)
        {
            playerTerritoryIDs = bountyManager.GetCachedPlayerTerritories(playerUID);
            if (playerTerritoryIDs && playerTerritoryIDs.Count() > 0)
            {
                territorySize = 150.0; 
                if (playerTerritoryIDs.Count() > 0)
                {
                    firstTerritory = bountyManager.GetCachedTerritoryData(playerTerritoryIDs.Get(0));
                    if (firstTerritory)
                    {
                        territorySize = firstTerritory.TerritorySize;
                    }
                }
                minDistanceRequired = territorySize + requiredDistance; 
                minDistanceRequiredSq = minDistanceRequired * minDistanceRequired;
                for (i = 0; i < playerTerritoryIDs.Count(); i++)
                {
                    territoryID = playerTerritoryIDs.Get(i);
                    cacheData = bountyManager.GetCachedTerritoryData(territoryID);
                    if (!cacheData)
                        continue;
                    distSq = vector.DistanceSq(cacheData.Position, playerPos);
                    if (distSq <= minDistanceRequiredSq)
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + GetIdentity().GetName() + " is too close to territory (distance: " + Math.Sqrt(distSq).ToString() + "m, required: " + minDistanceRequired.ToString() + "m)");
                        return false;
                    }
                }
            }
        }
        #endif
        if (IsPlayerInOwnTerritory())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + GetIdentity().GetName() + " is still in their own territory (non-Expansion)");
            return false;
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + GetIdentity().GetName() + " is far enough from all territories (required: " + requiredDistance.ToString() + "m beyond edge)");
        return true;
    }
    void ResumeBounty()
    {
        PlayerIdentity identity;
        if (!IsMissionHost())
            return;
        if (!netSync_HasBounty)
            return;
        if (!m_BountyPaused)
            return;
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfOwnTerritory)
        {
            if (!IsFarEnoughFromTerritory())
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] ResumeBounty - Player " + GetIdentity().GetName() + " is not far enough from territory, not resuming yet");
                return;
            }
        }
        m_BountyPaused = false;
        netSync_BountyPaused = false;
        SetSynchDirty();
        identity = GetIdentity();
        if (identity)
        {
            Param1<bool> paramPaused = new Param1<bool>(false);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdatePaused", paramPaused, true, identity);
            Param1<float> paramCountdown = new Param1<float>(m_BountyRemainingDuration);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Resumed bounty timer for player " + GetIdentity().GetName() + " (remaining: " + m_BountyRemainingDuration.ToString() + "s)");
        if (identity)
        {
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_BOUNTY_PERSISTED, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", m_BountyRemainingDuration);
        }
    }
    bool IsBountyPaused()
    {
        return m_BountyPaused;
    }
    void TeleportOutOfOwnTerritory(float territorySize = -1.0, vector flagPosition = "0 0 0")
    {
        PlayerIdentity identity;
        string playerName;
        vector currentPos;
        vector teleportPos;
        float groundY;
        float effectiveTerritorySize;
        float teleportDistance;
        vector direction;
        bool foundSafePos;
        int radius;
        int angle;
        float radians;
        vector testPos;
        vector groundPos;
        bool isOutsideTerritory;
        float randomAngle;
        float distance;
        if (!IsMissionHost())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Not server, skipping");
            return;
        }
        identity = GetIdentity();
        playerName = "Unknown";
        if (identity)
            playerName = identity.GetName();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Starting teleport for player " + playerName);
        currentPos = GetPosition();
        teleportPos = currentPos;
        if (territorySize > 0)
            effectiveTerritorySize = territorySize;
        else
            effectiveTerritorySize = GameConstants.REFRESHER_RADIUS;
        teleportDistance = effectiveTerritorySize + BOUNTY_DEFAULT_TELEPORT_DISTANCE; 
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Current position: " + currentPos.ToString() + ", Territory size: " + effectiveTerritorySize.ToString() + ", Teleport distance: " + teleportDistance.ToString());
        if (flagPosition != "0 0 0")
        {
            direction = currentPos - flagPosition;
            direction[1] = 0; 
            direction.Normalize();
            teleportPos = flagPosition + (direction * teleportDistance);
            groundY = GetGame().SurfaceY(teleportPos[0], teleportPos[2]);
            teleportPos[1] = groundY + 0.5;
        }
        else
        {
            foundSafePos = false;
            for (radius = BOUNTY_TELEPORT_SEARCH_MIN_RADIUS; radius <= BOUNTY_TELEPORT_SEARCH_MAX_RADIUS; radius += BOUNTY_TELEPORT_SEARCH_RADIUS_STEP)
            {
                for (angle = 0; angle < BOUNTY_DEGREES_IN_CIRCLE; angle += BOUNTY_TELEPORT_SEARCH_ANGLE_STEP)
                {
                    radians = angle * Math.DEG2RAD;
                    testPos = currentPos;
                    testPos[0] = testPos[0] + (Math.Cos(radians) * radius);
                    testPos[2] = testPos[2] + (Math.Sin(radians) * radius);
                    groundY = GetGame().SurfaceY(testPos[0], testPos[2]);
                    groundPos = Vector(testPos[0], groundY + BOUNTY_GROUND_OFFSET, testPos[2]); 
                    isOutsideTerritory = true;
                    if (isOutsideTerritory)
                    {
                        teleportPos = groundPos;
                        foundSafePos = true;
                        break;
                    }
                }
                if (foundSafePos)
                {
                    break;
                }
            }
            if (!foundSafePos)
            {
                randomAngle = Math.RandomFloat(0, BOUNTY_DEGREES_IN_CIRCLE) * Math.DEG2RAD;
                distance = BOUNTY_FALLBACK_TELEPORT_DISTANCE;
                teleportPos = currentPos;
                teleportPos[0] = teleportPos[0] + (Math.Cos(randomAngle) * distance);
                teleportPos[2] = teleportPos[2] + (Math.Sin(randomAngle) * distance);
                groundY = GetGame().SurfaceY(teleportPos[0], teleportPos[2]);
                teleportPos[1] = groundY + BOUNTY_GROUND_OFFSET;
            }
        }
        HumanCommandVehicle hcv;
        Transport transport;
        if (IsInTransport())
        {
            hcv = GetCommand_Vehicle();
            if (hcv)
            {
                transport = hcv.GetTransport();
                if (transport)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Player " + playerName + " is in vehicle, teleporting vehicle from " + currentPos.ToString() + " to " + teleportPos.ToString());
                    transport.SetPosition(teleportPos);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported vehicle (with player " + playerName + ") out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
                    SetPosition(teleportPos);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
                SetPosition(teleportPos);
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
            SetPosition(teleportPos);
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
        }
        identity = GetIdentity();
        if (identity)
        {
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY, identity);
        }
    }
    void TeleportOutOfSafeZone()
    {
        PlayerIdentity identity;
        string playerName;
        vector currentPos;
        vector teleportPos;
        float distance;
        vector direction;
        float groundY;
        if (!IsMissionHost())
            return;
        identity = GetIdentity();
        playerName = "Unknown";
        if (identity)
            playerName = identity.GetName();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfSafeZone - Teleporting player " + playerName + " out of safezone");
        currentPos = GetPosition();
        teleportPos = currentPos;
        distance = BOUNTY_DEFAULT_TELEPORT_DISTANCE;
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZoneDistance > 0.0)
        {
            distance = g_BountyConfig.Core.TeleportOutOfSafeZoneDistance;
        }
        direction = GetDirection();
        direction[1] = 0; 
        direction.Normalize();
        teleportPos = currentPos - (direction * distance);
        groundY = GetGame().SurfaceY(teleportPos[0], teleportPos[2]);
        teleportPos[1] = groundY + 0.5;
        HumanCommandVehicle hcv;
        Transport transport;
        if (IsInTransport())
        {
            hcv = GetCommand_Vehicle();
            if (hcv)
            {
                transport = hcv.GetTransport();
                if (transport)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] TeleportOutOfSafeZone - Player " + playerName + " is in vehicle, teleporting vehicle from " + currentPos.ToString() + " to " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
                    transport.SetPosition(teleportPos);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported vehicle (with player " + playerName + ") out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
                }
                else
                {
                    SetPosition(teleportPos);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
                }
            }
            else
            {
                SetPosition(teleportPos);
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
            }
        }
        else
        {
            SetPosition(teleportPos);
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
        }
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CheckSafeZoneAfterTeleport, BOUNTY_SAFEZONE_CHECK_DELAY_MS, false);
    }
    void CheckSafeZoneAfterTeleport()
    {
        PlayerIdentity identity;
        string playerName;
        bool isInNinjinsSafeZone;
        if (!IsMissionHost())
            return;
        if (!HasBounty() || !IsAlive())
            return;
        identity = GetIdentity();
        playerName = "Unknown";
        if (identity)
            playerName = identity.GetName();
        isInNinjinsSafeZone = NinjinBountyIsPlayerInNinjinsSafeZone();
        if (!isInNinjinsSafeZone)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is no longer in NinjinsPvPPvE safezone (netSync_IsInSafeZone = false) - stopping checks");
            return;
        }
        if (NinjinBountyIsOnSafeZoneExitTimer())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is in NinjinsPvPPvE safezone with active exit timer (netSync_IsSZOnExit = true) - skipping teleport, will check again in 2 seconds");
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CheckSafeZoneAfterTeleport, BOUNTY_SAFEZONE_CHECK_DELAY_MS, false);
            return; 
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is in NinjinsPvPPvE safezone (netSync_IsInSafeZone = true) without exit timer (netSync_IsSZOnExit = false) - teleporting out...");
        TeleportOutOfSafeZone(); 
    }
    static bool NinjinsBountyRearmedIsInOwnTerritory(PlayerBase player)
    {
        return false;
    }
    static bool NinjinsBountyBasicTerritoriesIsInOwnTerritory(PlayerBase player)
    {
        return false;
    }
    static bool NinjinsBountyExpansionIsInSafezone(PlayerBase player)
    {
        if (!player)
            return false;
        bool result = false;
        EnScript.GetClassVar(player, "m_Expansion_IsInSafeZone", 0, result);
        return result;
    }
    bool NinjinBountyIsPlayerInNinjinsSafeZone()
    {
        return netSync_IsInSafeZone;
    }
    bool NinjinBountyIsOnSafeZoneExitTimer()
    {
        return netSync_IsSZOnExit;
    }
    bool NinjinBountyIsPlayerInSafezone()
    {
        if (NinjinBountyIsPlayerInNinjinsSafeZone())
        {
            return true;
        }
        if (NinjinsBountyExpansionIsInSafezone(this))
        {
            return true;
        }
        return false;
    }
}