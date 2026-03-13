class BountyPreservedData
{
    float RemainingDuration;
    BountyType Type;
    float StartTime; 
    float OriginalDuration; 
    void BountyPreservedData(float duration = 0.0, BountyType bountyType = BountyType.PLACED, float startTime = 0.0, float originalDuration = 0.0)
    {
        RemainingDuration = duration;
        Type = bountyType;
        StartTime = startTime;
        OriginalDuration = originalDuration;
    }
}
class TerritoryCacheData
{
    int TerritoryID;
    string OwnerID;
    ref array<string> MemberIDs;
    vector Position;
    float TerritorySize;
    void TerritoryCacheData()
    {
        MemberIDs = new array<string>();
    }
}
class BountyManager
{
    private static ref BountyManager s_Instance;
    private ref map<string, ref BountyPreservedData> m_PreservedBounties; 
    private float m_LastPausedBountyResumeCheckTime = 0.0; 
    private float m_LastSafeZoneCheckTime = 0.0; 
    private ref set<PlayerBase> m_PlayersInSafeZones; 
    private ref map<PlayerBase, string> m_PlayerSafezoneTypes; 
    private ref set<PlayerBase> m_PlayersInOwnTerritory; 
    private ref map<int, ref TerritoryCacheData> m_TerritoryCache; 
    private ref map<string, ref array<int>> m_PlayerTerritoryCache; 
    private float m_LastAutomatedBountyPlacementTime = 0.0; 
    private const float SAFEZONE_CHECK_INTERVAL_EXPANSION = 12.0; 
    void BountyManager()
    {
        m_PreservedBounties = new map<string, ref BountyPreservedData>();
        m_LastPausedBountyResumeCheckTime = 0.0;
        m_LastSafeZoneCheckTime = 0.0;
        m_PlayersInSafeZones = new set<PlayerBase>();
        m_PlayerSafezoneTypes = new map<PlayerBase, string>();
        m_PlayersInOwnTerritory = new set<PlayerBase>();
        m_TerritoryCache = new map<int, ref TerritoryCacheData>();
        m_PlayerTerritoryCache = new map<string, ref array<int>>();
        m_LastAutomatedBountyPlacementTime = 0.0;
    }
    static BountyManager GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new BountyManager();
        }
        return s_Instance;
    }
    void Update(float deltaTime)
    {
        float currentTime;
        array<Man> players;
        Man man;
        PlayerBase player;
        int i;
        bool shouldCheckPausedBountyResume;
        float checkInterval;
        float timeSinceLastPausedCheck;
        bool shouldCheckSafeZoneExpansion;
        float timeSinceLastExpansionCheck;
        PlayerIdentity identity;
        string playerName;
        bool isNinjinsSafeZone;
        bool isExpansionSafeZone;
        bool isInSafeZone;
        int safezoneIndex;
        bool wasInSafeZone;
        string exitedSafezoneType;
        bool isCurrentlyNinjinsSafeZone;
        bool isCurrentlyInExpansionSafeZone;
        string safezoneType;
        if (!IsMissionHost())
            return;
        if (!BountyConfig.IsSystemActive())
            return;
        currentTime = g_Game.GetTime();
        players = new array<Man>();
        g_Game.GetPlayers(players);
        shouldCheckPausedBountyResume = false;
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.PauseBountyInTerritory)
        {
            checkInterval = 5.0; 
            if (g_BountyConfig.Core.PausedBountyResumeCheckInterval > 0.0)
            {
                checkInterval = g_BountyConfig.Core.PausedBountyResumeCheckInterval;
            }
            timeSinceLastPausedCheck = (currentTime - m_LastPausedBountyResumeCheckTime) / 1000.0; 
            if (timeSinceLastPausedCheck >= checkInterval)
            {
                shouldCheckPausedBountyResume = true;
                m_LastPausedBountyResumeCheckTime = currentTime;
            }
        }
        shouldCheckSafeZoneExpansion = false;
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZone && m_PlayersInSafeZones.Count() > 0)
        {
            timeSinceLastExpansionCheck = (currentTime - m_LastSafeZoneCheckTime) / 1000.0; 
            if (timeSinceLastExpansionCheck >= SAFEZONE_CHECK_INTERVAL_EXPANSION)
            {
                shouldCheckSafeZoneExpansion = true;
                m_LastSafeZoneCheckTime = currentTime;
            }
        }
        for (i = 0; i < players.Count(); i++)
        {
            man = players.Get(i);
            player = PlayerBase.Cast(man);
            if (player && player.HasBounty())
            {
                if (player.IsAlive())
                {
                    identity = player.GetIdentity();
                    playerName = "Unknown";
                    if (identity)
                        playerName = identity.GetName();
                    if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfOwnTerritory)
                    {
                        bool isInOwnTerritory = false;
                        #ifdef EXPANSIONMODBASEBUILDING
                        isInOwnTerritory = IsPlayerInOwnExpansionTerritory(player);
                        #endif
                        if (!isInOwnTerritory)
                        {
                            isInOwnTerritory = player.IsPlayerInOwnTerritory();
                        }
                        int territoryIndex = m_PlayersInOwnTerritory.Find(player);
                        bool wasInOwnTerritory = territoryIndex >= 0;
                        if (isInOwnTerritory && !wasInOwnTerritory)
                        {
                            m_PlayersInOwnTerritory.Insert(player);
                            if (!player.IsBountyPaused())
                            {
                                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " entered their own territory - teleporting out...");
                                player.TeleportOutOfOwnTerritory();
                            }
                            else
                            {
                                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " entered their own territory but bounty is paused - allowing them to stay");
                            }
                        }
                        else if (!isInOwnTerritory && wasInOwnTerritory)
                        {
                            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " left their own territory");
                            m_PlayersInOwnTerritory.Remove(territoryIndex);
                            if (player.IsBountyPaused())
                            {
                                player.ResumeBounty();
                            }
                        }
                        else if (isInOwnTerritory && wasInOwnTerritory)
                        {
                            if (!player.IsBountyPaused())
                            {
                                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " is still in their own territory - teleporting out...");
                                player.TeleportOutOfOwnTerritory();
                            }
                        }
                    }
                    if (shouldCheckPausedBountyResume && player.IsBountyPaused())
                    {
                        player.ResumeBounty();
                    }
                        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZone)
                        {
                            isNinjinsSafeZone = player.NinjinBountyIsPlayerInNinjinsSafeZone();
                            isExpansionSafeZone = PlayerBase.NinjinsBountyExpansionIsInSafezone(player);
                            isInSafeZone = isNinjinsSafeZone || isExpansionSafeZone; 
                            safezoneIndex = m_PlayersInSafeZones.Find(player);
                            wasInSafeZone = safezoneIndex >= 0;
                            if (isNinjinsSafeZone)
                                safezoneType = "NinjinsPvPPvE";
                            else
                                safezoneType = "Expansion";
                            if (isInSafeZone && !wasInSafeZone)
                            {
                                if (isNinjinsSafeZone && player.NinjinBountyIsOnSafeZoneExitTimer())
                                {
                                    m_PlayersInSafeZones.Insert(player);
                                    m_PlayerSafezoneTypes.Set(player, safezoneType); 
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " entered " + safezoneType + " safezone but has active exit timer (netSync_IsSZOnExit = true) - adding to tracking set, skipping teleport");
                                }
                                else
                                {
                                    m_PlayersInSafeZones.Insert(player);
                                    m_PlayerSafezoneTypes.Set(player, safezoneType); 
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " entered " + safezoneType + " safezone - adding to tracking set");
                                    player.TeleportOutOfSafeZone();
                                }
                            }
                            else if (!isInSafeZone && wasInSafeZone)
                            {
                                exitedSafezoneType = "Unknown";
                                if (m_PlayerSafezoneTypes.Contains(player))
                                {
                                    exitedSafezoneType = m_PlayerSafezoneTypes.Get(player);
                                }
                                else
                                {
                                    exitedSafezoneType = safezoneType;
                                }
                                m_PlayersInSafeZones.Remove(safezoneIndex);
                                m_PlayerSafezoneTypes.Remove(player);
                                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " exited " + exitedSafezoneType + " safezone - removing from tracking set");
                            }
                            if (wasInSafeZone && shouldCheckSafeZoneExpansion)
                            {
                                isCurrentlyNinjinsSafeZone = player.NinjinBountyIsPlayerInNinjinsSafeZone();
                                isCurrentlyInExpansionSafeZone = PlayerBase.NinjinsBountyExpansionIsInSafezone(player);
                                int removeIndex = -1;
                                if (isCurrentlyInExpansionSafeZone && !isCurrentlyNinjinsSafeZone)
                                {
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " still in Expansion safezone after " + SAFEZONE_CHECK_INTERVAL_EXPANSION + " seconds - teleporting out...");
                                    player.TeleportOutOfSafeZone();
                                }
                                else if (!isCurrentlyInExpansionSafeZone && !isCurrentlyNinjinsSafeZone)
                                {
                                    removeIndex = m_PlayersInSafeZones.Find(player);
                                    if (removeIndex >= 0)
                                        m_PlayersInSafeZones.Remove(removeIndex);
                                    m_PlayerSafezoneTypes.Remove(player); 
                                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " no longer in Expansion safezone (periodic check) - removing from tracking set, stopping checks");
                                }
                                else if (isCurrentlyNinjinsSafeZone)
                                {
                                    if (player.NinjinBountyIsOnSafeZoneExitTimer())
                                    {
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " is in NinjinsPvPPvE safezone with active exit timer (netSync_IsSZOnExit = true) - skipping teleport, will check again after exit timer expires");
                                    }
                                    else
                                    {
                                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Bountied player " + playerName + " is in NinjinsPvPPvE safezone without exit timer (netSync_IsSZOnExit = false) - teleporting out...");
                                        player.TeleportOutOfSafeZone();
                                    }
                                }
                            }
                        }
                }
                else
                {
                    int deadPlayerIndex = m_PlayersInSafeZones.Find(player);
                    if (deadPlayerIndex >= 0)
                    {
                        m_PlayersInSafeZones.Remove(deadPlayerIndex);
                        m_PlayerSafezoneTypes.Remove(player); 
                    }
                    int deadTerritoryIndex = m_PlayersInOwnTerritory.Find(player);
                    if (deadTerritoryIndex >= 0)
                    {
                        m_PlayersInOwnTerritory.Remove(deadTerritoryIndex);
                    }
                }
            }
            else
            {
                int noBountyIndex = m_PlayersInSafeZones.Find(player);
                if (noBountyIndex >= 0)
                {
                    m_PlayersInSafeZones.Remove(noBountyIndex);
                    m_PlayerSafezoneTypes.Remove(player); 
                }
                int noBountyTerritoryIndex = m_PlayersInOwnTerritory.Find(player);
                if (noBountyTerritoryIndex >= 0)
                {
                    m_PlayersInOwnTerritory.Remove(noBountyTerritoryIndex);
                }
            }
        }
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.EnableAutomatedBountyPlacement && g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds > 0.0)
        {
            float intervalMs = g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds * 1000.0; 
            float timeSinceLastPlacement = currentTime - m_LastAutomatedBountyPlacementTime;
            if (m_LastAutomatedBountyPlacementTime == 0.0 || timeSinceLastPlacement >= intervalMs)
            {
                PlayerBase selectedPlayer = SelectEligiblePlayerForAutomatedBounty();
                if (selectedPlayer)
                {
                    bool success = ApplyBountyToPlayer(selectedPlayer, null, 0.0, "Automated server bounty placement", BountyType.PLACED);
                    if (success)
                    {
                        m_LastAutomatedBountyPlacementTime = currentTime;
                        PlayerIdentity selectedIdentity = selectedPlayer.GetIdentity();
                        string selectedName = "Unknown";
                        if (selectedIdentity)
                            selectedName = selectedIdentity.GetName();
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Automated bounty placed on " + selectedName + " (interval: " + g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds.ToString() + "s)");
                    }
                    else
                    {
                        m_LastAutomatedBountyPlacementTime = currentTime - (intervalMs * 0.9);
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyManager] Automated bounty placement failed - will retry in " + (g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds * 0.1).ToString() + "s");
                    }
                }
                else
                {
                    m_LastAutomatedBountyPlacementTime = currentTime;
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Automated bounty placement skipped - no eligible players found");
                }
            }
        }
        array<string> keysToRemove = new array<string>();
        string playerId;
        BountyPreservedData data;
        for (i = 0; i < m_PreservedBounties.Count(); i++)
        {
            playerId = m_PreservedBounties.GetKey(i);
            data = m_PreservedBounties.GetElement(i);
            if (data && data.RemainingDuration <= 0.0)
            {
                keysToRemove.Insert(playerId);
            }
        }
        for (i = 0; i < keysToRemove.Count(); i++)
        {
            playerId = keysToRemove.Get(i);
            m_PreservedBounties.Remove(playerId);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cleaned up preserved bounty for player ID: " + playerId);
        }
    }
    int GetBountiedPlayerCount()
    {
        if (!IsMissionHost())
            return 0;
        int count = 0;
        array<Man> players = new array<Man>();
        g_Game.GetPlayers(players);
        int i;
        Man man;
        PlayerBase player;
        for (i = 0; i < players.Count(); i++)
        {
            man = players.Get(i);
            player = PlayerBase.Cast(man);
            if (player && player.HasBounty() && player.IsAlive())
            {
                count++;
            }
        }
        return count;
    }
    void PreserveBountyForPlayer(string playerId, float remainingDuration, BountyType bountyType, float startTime = 0.0, float originalDuration = 0.0)
    {
        if (!IsMissionHost())
            return;
        if (remainingDuration <= 0.0)
            return;
        m_PreservedBounties.Set(playerId, new BountyPreservedData(remainingDuration, bountyType, startTime, originalDuration));
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Preserved bounty for player ID: " + playerId + " - RemainingDuration: " + remainingDuration.ToString() + "s, BountyType: " + bountyType.ToString() + ", StartTime: " + startTime.ToString() + "s, OriginalDuration: " + originalDuration.ToString() + "s");
    }
    BountyPreservedData GetPreservedBountyForPlayer(string playerId)
    {
        if (!IsMissionHost())
            return null;
        BountyPreservedData data = m_PreservedBounties.Get(playerId);
        if (data)
        {
            m_PreservedBounties.Remove(playerId);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Retrieved preserved bounty for player ID: " + playerId + " - RemainingDuration: " + data.RemainingDuration.ToString() + "s");
        }
        return data;
    }
    private PlayerBase SelectEligiblePlayerForAutomatedBounty()
    {
        if (!IsMissionHost())
            return null;
        array<Man> allPlayers = new array<Man>();
        g_Game.GetPlayers(allPlayers);
        array<PlayerBase> eligiblePlayers = new array<PlayerBase>();
        Man man;
        PlayerBase player;
        PlayerIdentity identity;
        int i;
        for (i = 0; i < allPlayers.Count(); i++)
        {
            man = allPlayers.Get(i);
            player = PlayerBase.Cast(man);
            if (!player || !player.IsAlive())
                continue;
            identity = player.GetIdentity();
            if (!identity)
                continue;
            if (player.HasBounty())
                continue;
            if (player.IsBountyOnCooldown())
                continue;
            if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(identity.GetId()))
                continue;
            if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.MinimumPlayerLifetimeSeconds > 0)
            {
                int playerLifetime = player.StatGet("playtime");
                if (playerLifetime < g_BountyConfig.Core.MinimumPlayerLifetimeSeconds)
                    continue;
            }
            if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZone)
            {
                if (player.NinjinBountyIsPlayerInSafezone())
                    continue;
            }
            eligiblePlayers.Insert(player);
        }
        if (eligiblePlayers.Count() > 0)
        {
            int randomIndex = Math.RandomInt(0, eligiblePlayers.Count());
            return eligiblePlayers.Get(randomIndex);
        }
        return null;
    }
    static bool ApplyBountyToPlayer(PlayerBase targetPlayer, PlayerBase sourcePlayer = null, float durationSeconds = 0.0, string reason = "", BountyType bountyType = BountyType.PLACED, bool ignoreMaxBountiedLimit = false)
    {
        PlayerIdentity targetIdentity;
        string targetName;
        bool isAdminPlacing;
        int playerLifetime;
        if (!IsMissionHost())
            return false;
        if (!targetPlayer || !targetPlayer.GetIdentity())
            return false;
        if (!BountyConfig.IsSystemActive())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot apply bounty - system is not active (disabled or minimum players not met)");
            return false;
        }
        targetIdentity = targetPlayer.GetIdentity();
        targetName = "Unknown";
        if (targetIdentity)
        {
            targetName = targetIdentity.GetName();
        }
        if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(targetIdentity.GetId()))
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is blacklisted");
            return false;
        }
        if (bountyType != BountyType.RULE_BREAKER && g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.MinimumPlayerLifetimeSeconds > 0)
        {
            isAdminPlacing = false;
            if (sourcePlayer && sourcePlayer.GetIdentity() && g_BountyAdminConfig)
            {
                isAdminPlacing = g_BountyAdminConfig.IsAdmin(sourcePlayer.GetIdentity().GetId());
            }
            if (!isAdminPlacing)
            {
                playerLifetime = targetPlayer.StatGet("playtime"); 
                if (playerLifetime < g_BountyConfig.Core.MinimumPlayerLifetimeSeconds)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player lifetime (" + playerLifetime.ToString() + "s) is less than required (" + g_BountyConfig.Core.MinimumPlayerLifetimeSeconds.ToString() + "s)");
                    return false;
                }
            }
            else
            {
                string adminName = "Unknown";
                if (sourcePlayer && sourcePlayer.GetIdentity())
                {
                    adminName = sourcePlayer.GetIdentity().GetName();
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Admin " + adminName + " is placing bounty - bypassing lifetime check for " + targetName);
            }
        }
        if (bountyType != BountyType.RULE_BREAKER && targetPlayer.IsBountyOnCooldown())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is on cooldown");
            if (sourcePlayer && sourcePlayer.GetIdentity())
            {
                int cooldownSeconds = Math.Ceil(targetPlayer.GetBountyCooldownRemaining());
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN, sourcePlayer.GetIdentity(), targetName, "", 0.0, 0, 0, 0, 0, 0, cooldownSeconds);
            }
            return false;
        }
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.TeleportOutOfSafeZone)
        {
            if (targetPlayer.NinjinBountyIsPlayerInSafezone())
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is in a safezone");
                if (sourcePlayer && sourcePlayer.GetIdentity())
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE, sourcePlayer.GetIdentity(), targetName);
                }
                return false;
            }
        }
        if (durationSeconds <= 0.0)
        {
            if (g_BountyConfig)
            {
                if (bountyType == BountyType.RULE_BREAKER)
                {
                    durationSeconds = g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
                }
                else
                {
                    durationSeconds = g_BountyConfig.PlacedBounty.BountyDurationSeconds;
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyManager] Cannot apply bounty - config not loaded!");
                return false;
            }
        }
        int clearedRewardCount = 0;
        if (bountyType == BountyType.RULE_BREAKER && g_BountyConfig && g_BountyConfig.RuleBreaker && g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty)
        {
            clearedRewardCount = targetPlayer.GetTotalPendingRewardCount();
            if (clearedRewardCount > 0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Clearing " + clearedRewardCount.ToString() + " pending reward(s) for " + targetName + " due to rule breaker bounty");
                targetPlayer.m_PendingSuccessRewardCount = 0;
                targetPlayer.SetSynchDirty();
            }
        }
        targetPlayer.SetBountyWithType(durationSeconds, bountyType, false, clearedRewardCount, ignoreMaxBountiedLimit);
        string sourceName = "System";
        if (sourcePlayer && sourcePlayer.GetIdentity())
        {
            sourceName = sourcePlayer.GetIdentity().GetName();
        }
        string logReason = reason;
        if (logReason == "")
        {
            logReason = "Unknown";
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Applied bounty to " + targetName + " for " + durationSeconds.ToString() + " seconds. Source: " + sourceName + ", Reason: " + logReason);
        return true;
    }
    static bool ClearBountyFromPlayer(PlayerBase targetPlayer, PlayerBase sourcePlayer = null, string reason = "", bool skipRewards = false)
    {
        PlayerIdentity targetIdentity;
        string targetName;
        string sourceName;
        string logReason;
        if (!IsMissionHost())
            return false;
        if (!targetPlayer || !targetPlayer.GetIdentity())
            return false;
        if (!targetPlayer.HasBounty())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cannot clear bounty - player does not have a bounty");
            return false;
        }
        targetPlayer.ClearBounty(skipRewards, BountyEndReason.CLEARED);
        targetIdentity = targetPlayer.GetIdentity();
        targetName = "Unknown";
        if (targetIdentity)
        {
            targetName = targetIdentity.GetName();
        }
        sourceName = "System";
        if (sourcePlayer && sourcePlayer.GetIdentity())
        {
            sourceName = sourcePlayer.GetIdentity().GetName();
        }
        logReason = reason;
        if (logReason == "")
        {
            logReason = "Unknown";
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Cleared bounty from " + targetName + ". Source: " + sourceName + ", Reason: " + logReason);
        return true;
    }
    static void ReloadAllConfigs(PlayerBase requestingPlayer = null)
    {
        if (!IsMissionHost())
            return;
        GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] Reloading all bounty system configs from disk...");
        bool allSuccess = true;
        BountyConfig.CheckDirectories();
        if (FileExist(Ninjins_Bounty_System_CONFIG_FILE))
        {
            BountyConfig newBountyConfig = new BountyConfig();
            JsonFileLoader<BountyConfig>.JsonLoadFile(Ninjins_Bounty_System_CONFIG_FILE, newBountyConfig);
            if (newBountyConfig)
            {
                newBountyConfig.ValidateConfig();
                g_BountyConfig = newBountyConfig;
                GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] BountyConfig reloaded from disk. EnableBountySystem: " + g_BountyConfig.Core.EnableBountySystem.ToString() + ", Duration: " + g_BountyConfig.PlacedBounty.BountyDurationSeconds.ToString() + " seconds");
                BountyConfig.LogConfigValues(g_BountyConfig, true);
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Reload] Failed to reload BountyConfig from disk!");
                allSuccess = false;
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Reload] BountyConfig.json file not found!");
            allSuccess = false;
        }
        BountyConfig.CheckDirectories();
        if (FileExist(Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE))
        {
            BountySuccessRewardConfig newSuccessConfig = new BountySuccessRewardConfig();
            JsonFileLoader<BountySuccessRewardConfig>.JsonLoadFile(Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, newSuccessConfig);
            if (newSuccessConfig)
            {
                g_BountySuccessRewardConfig = newSuccessConfig;
                int sectionCount = 0;
                if (g_BountySuccessRewardConfig.BountyRewardItems)
                    sectionCount = g_BountySuccessRewardConfig.BountyRewardItems.Count();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] BountySuccessRewardConfig reloaded from disk. RewardSections: " + sectionCount.ToString());
                BountySuccessRewardConfig.LogConfigValues(g_BountySuccessRewardConfig, true);
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Reload] Failed to reload BountySuccessRewardConfig from disk!");
                allSuccess = false;
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Reload] BountySuccessRewardConfig.json file not found!");
            allSuccess = false;
        }
        BountyConfig.CheckDirectories();
        if (FileExist(Ninjins_Bounty_System_ADMIN_CONFIG_FILE))
        {
            BountyAdminConfig newAdminConfig = new BountyAdminConfig();
            JsonFileLoader<BountyAdminConfig>.JsonLoadFile(Ninjins_Bounty_System_ADMIN_CONFIG_FILE, newAdminConfig);
            if (newAdminConfig)
            {
                g_BountyAdminConfig = newAdminConfig;
                int adminCount = 0;
                if (g_BountyAdminConfig && g_BountyAdminConfig.AdminGUIDs)
                {
                    adminCount = g_BountyAdminConfig.AdminGUIDs.Count();
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] BountyAdminConfig reloaded from disk. AdminGUIDs: " + adminCount.ToString());
                array<Man> players = new array<Man>();
                g_Game.GetPlayers(players);
                int i;
                Man man;
                PlayerBase playerBase;
                PlayerIdentity playerIdentity;
                for (i = 0; i < players.Count(); i++)
                {
                    man = players.Get(i);
                    playerBase = PlayerBase.Cast(man);
                    if (playerBase)
                    {
                        playerIdentity = playerBase.GetIdentity();
                        if (playerIdentity)
                        {
                            bool isAdmin = g_BountyAdminConfig.IsAdmin(playerIdentity.GetId());
                            playerBase.SetBountyAdminStatus(isAdmin);
                        }
                    }
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Reload] Failed to reload BountyAdminConfig from disk!");
                allSuccess = false;
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Reload] Admins.json file not found!");
            allSuccess = false;
        }
        BountyConfig.CheckDirectories();
        if (FileExist(Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE))
        {
            BountyBlacklistConfig newBlacklistConfig = new BountyBlacklistConfig();
            JsonFileLoader<BountyBlacklistConfig>.JsonLoadFile(Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, newBlacklistConfig);
            if (newBlacklistConfig)
            {
                g_BountyBlacklistConfig = newBlacklistConfig;
                int blacklistCount = 0;
                if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.BlacklistedGUIDs)
                {
                    blacklistCount = g_BountyBlacklistConfig.BlacklistedGUIDs.Count();
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] BountyBlacklistConfig reloaded from disk. BlacklistedGUIDs: " + blacklistCount.ToString());
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Reload] Failed to reload BountyBlacklistConfig from disk!");
                allSuccess = false;
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Reload] Blacklist.json file not found!");
            allSuccess = false;
        }
        BountyConfig.CheckDirectories();
        if (FileExist(Ninjins_Bounty_System_BOARD_CONFIG_FILE))
        {
            BountyBoardPlacementConfig newBoardConfig = new BountyBoardPlacementConfig();
            JsonFileLoader<BountyBoardPlacementConfig>.JsonLoadFile(Ninjins_Bounty_System_BOARD_CONFIG_FILE, newBoardConfig);
            if (newBoardConfig)
            {
                newBoardConfig.ValidateConfig();
                g_BountyBoardPlacementConfig = newBoardConfig;
                BountyBoardPlacementConfig.LogConfig(g_BountyBoardPlacementConfig, true);
                BountyModule bountyModule = BountyModule.GetInstance();
                if (bountyModule)
                {
                    bountyModule.SpawnConfiguredBountyBoards();
                }
                GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] BountyBoardPlacements.json reloaded from disk. BoardPlacements: " + g_BountyBoardPlacementConfig.BoardPlacements.Count().ToString());
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Reload] Failed to reload BountyBoardPlacements.json from disk!");
                allSuccess = false;
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Reload] BountyBoardPlacements.json file not found!");
            allSuccess = false;
        }
        if (requestingPlayer)
        {
            PlayerIdentity identity = requestingPlayer.GetIdentity();
            if (identity)
            {
                if (allSuccess)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] All configs reloaded successfully from disk!");
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] Note: Existing bounties will use their original duration. New bounties will use the updated duration.");
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS, identity);
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[Reload] Some configs failed to reload. Check logs for details.");
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE, identity);
                }
            }
        }
        if (allSuccess && g_BountyConfig && g_BountyConfig.UI)
        {
            array<Man> configReloadPlayers = new array<Man>();
            g_Game.GetPlayers(configReloadPlayers);
            int configReloadI;
            int rpcSentCount = 0;
            float posX = g_BountyConfig.UI.CountdownWidgetPositionX;
            float posY = g_BountyConfig.UI.CountdownWidgetPositionY;
            float width = g_BountyConfig.UI.CountdownWidgetWidth;
            float height = g_BountyConfig.UI.CountdownWidgetHeight;
            int bgColor = g_BountyConfig.UI.CountdownWidgetBackgroundColor;
            int textColor = g_BountyConfig.UI.CountdownWidgetTextColor;
            for (configReloadI = 0; configReloadI < configReloadPlayers.Count(); configReloadI++)
            {
                Man configReloadMan = configReloadPlayers.Get(configReloadI);
                PlayerBase configReloadPlayerBase = PlayerBase.Cast(configReloadMan);
                if (configReloadPlayerBase)
                {
                    PlayerIdentity configReloadPlayerIdentity = configReloadPlayerBase.GetIdentity();
                    if (configReloadPlayerIdentity)
                    {
                        BountyUISettingsData uiData = new BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
                        Param1<BountyUISettingsData> uiParam = new Param1<BountyUISettingsData>(uiData);
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, configReloadPlayerIdentity);
                        rpcSentCount++;
                    }
                }
            }
            GetNinjins_Bounty_SystemLogger().LogInfo("[Reload] Sent BountyConfigReloaded RPC to " + rpcSentCount.ToString() + " client(s) with UI settings: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
        }
    }
    static array<ref BountyCurrencyReward> SelectCurrencyRewards(array<ref BountyCurrencyReward> currencyRewards, int currencyMin, int currencyMax)
    {
        array<ref BountyCurrencyReward> currenciesToGive = new array<ref BountyCurrencyReward>;
        if (!currencyRewards || currencyRewards.Count() == 0)
            return currenciesToGive;
        int currenciesToPick;
        if (currencyMax > currencyMin)
            currenciesToPick = Math.RandomInt(currencyMin, currencyMax + 1);
        else
            currenciesToPick = currencyMin;
        if (currenciesToPick > currencyRewards.Count())
            currenciesToPick = currencyRewards.Count();
        if (currenciesToPick <= 0)
            return currenciesToGive;
        int currencyRetryCount = 0;
        int maxCurrencyRetries = 20; 
        while (currenciesToGive.Count() == 0 && currencyRetryCount < maxCurrencyRetries)
        {
            currencyRetryCount++;
            currenciesToGive.Clear();
            array<ref BountyCurrencyReward> availableCurrencies = new array<ref BountyCurrencyReward>;
            int i;
            BountyCurrencyReward currency;
            for (i = 0; i < currencyRewards.Count(); i++)
            {
                currency = currencyRewards.Get(i);
                if (currency && currency.ClassName != "")
                {
                    availableCurrencies.Insert(currency);
                }
            }
            int j;
            int pickedCount = 0;
            BountyCurrencyReward selectedCurrency;
            array<ref BountyCurrencyReward> tempAvailableCurrencies = new array<ref BountyCurrencyReward>;
            for (i = 0; i < availableCurrencies.Count(); i++)
            {
                tempAvailableCurrencies.Insert(availableCurrencies.Get(i));
            }
            while (pickedCount < currenciesToPick && tempAvailableCurrencies.Count() > 0)
            {
                selectedCurrency = SelectRandomCurrencyReward(tempAvailableCurrencies);
                if (selectedCurrency)
                {
                    currenciesToGive.Insert(selectedCurrency);
                    for (j = tempAvailableCurrencies.Count() - 1; j >= 0; j--)
                    {
                        if (tempAvailableCurrencies.Get(j) == selectedCurrency)
                        {
                            tempAvailableCurrencies.Remove(j);
                            break;
                        }
                    }
                    pickedCount = pickedCount + 1;
                }
                else
                {
                    break;
                }
            }
        }
        if (currencyRetryCount >= maxCurrencyRetries && currenciesToGive.Count() == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Failed to pick currencies after " + maxCurrencyRetries.ToString() + " retries!");
        }
        return currenciesToGive;
    }
    static BountyRewardItem SelectRandomRewardItem(array<ref BountyRewardItem> rewardItems)
    {
        if (!rewardItems || rewardItems.Count() == 0)
            return null;
        float totalChance = 0.0;
        int i;
        BountyRewardItem item;
        for (i = 0; i < rewardItems.Count(); i++)
        {
            item = rewardItems.Get(i);
            if (item && item.ItemClassName != "")
            {
                totalChance += item.SpawnChance;
            }
        }
        if (totalChance <= 0.0)
        {
            for (i = 0; i < rewardItems.Count(); i++)
            {
                item = rewardItems.Get(i);
                if (item && item.ItemClassName != "")
                {
                    return item;
                }
            }
            return null;
        }
        float randomValue = Math.RandomFloat(0.0, totalChance);
        float accumulatedChance = 0.0;
        for (i = 0; i < rewardItems.Count(); i++)
        {
            item = rewardItems.Get(i);
            if (item && item.ItemClassName != "")
            {
                accumulatedChance += item.SpawnChance;
                if (randomValue <= accumulatedChance)
                {
                    return item;
                }
            }
        }
        for (i = rewardItems.Count() - 1; i >= 0; i--)
        {
            item = rewardItems.Get(i);
            if (item && item.ItemClassName != "")
            {
                return item;
            }
        }
        return null;
    }
    static BountyCurrencyReward SelectRandomCurrencyReward(array<ref BountyCurrencyReward> currencyRewards)
    {
        if (!currencyRewards || currencyRewards.Count() == 0)
            return null;
        float totalChance = 0.0;
        int i;
        BountyCurrencyReward currency;
        for (i = 0; i < currencyRewards.Count(); i++)
        {
            currency = currencyRewards.Get(i);
            if (currency && currency.ClassName != "")
            {
                totalChance += currency.SpawnChance;
            }
        }
        if (totalChance <= 0.0)
        {
            for (i = 0; i < currencyRewards.Count(); i++)
            {
                currency = currencyRewards.Get(i);
                if (currency && currency.ClassName != "")
                {
                    return currency;
                }
            }
            return null;
        }
        float randomValue = Math.RandomFloat(0.0, totalChance);
        float accumulatedChance = 0.0;
        for (i = 0; i < currencyRewards.Count(); i++)
        {
            currency = currencyRewards.Get(i);
            if (currency && currency.ClassName != "")
            {
                accumulatedChance += currency.SpawnChance;
                if (randomValue <= accumulatedChance)
                {
                    return currency;
                }
            }
        }
        for (i = currencyRewards.Count() - 1; i >= 0; i--)
        {
            currency = currencyRewards.Get(i);
            if (currency && currency.ClassName != "")
            {
                return currency;
            }
        }
        return null;
    }
    static bool SpawnBountyRewardGiftBox(PlayerBase player, bool isSurvivalReward = false, bool giveCurrency = true)
    {
        if (!IsMissionHost())
            return false;
        if (!player || !player.GetIdentity())
            return false;
        if (!g_BountyConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Config not loaded!");
            return false;
        }
        if (isSurvivalReward)
        {
            if (!g_BountyConfig || !g_BountyConfig.Reward || !g_BountyConfig.Reward.EnableSurvivalReward)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Success reward (survival type) is disabled.");
                return false;
            }
        }
        PlayerIdentity identity = player.GetIdentity();
        if (player.IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
        {
            string playerName = "Unknown";
            if (identity)
                playerName = identity.GetName();
            string rewardType;
            if (isSurvivalReward)
                rewardType = "survival";
            else
                rewardType = "kill"; 
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Player " + playerName + " is a rule breaker - blocking " + rewardType + " reward (PvERuleBreakerGiveRewards = false)");
            return false;
        }
        if (!g_BountySuccessRewardConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] BountySuccessRewardConfig not loaded!");
            return false;
        }
        array<ref BountyRewardSection> rewardSections = g_BountySuccessRewardConfig.BountyRewardItems;
        bool useSectionSystem = rewardSections && rewardSections.Count() > 0;
        array<ref BountyCurrencyReward> currencyRewards = g_BountySuccessRewardConfig.BountyCurrencyRewards;
        bool ruinedContainerAsReward = g_BountySuccessRewardConfig.RuinedContainerAsReward;
        bool spawnItemsDirectlyToInventory = g_BountySuccessRewardConfig.SpawnItemsDirectlyToInventory;
        int currencyMin = g_BountySuccessRewardConfig.CurrencyMin;
        int currencyMax = g_BountySuccessRewardConfig.CurrencyMax;
        if (currencyMin < 0)
            currencyMin = 0;
        if (currencyMax < currencyMin)
            currencyMax = currencyMin;
        if (!useSectionSystem)
        {
            rewardSections = new array<ref BountyRewardSection>;
            BountyRewardSection defaultSection = new BountyRewardSection;
            defaultSection.Name = "Default";
            defaultSection.ContainerClassName = "SeaChest";
            defaultSection.SpawnChance = 100.0;
            defaultSection.ItemsMin = 1;
            defaultSection.ItemsMax = 1;
            defaultSection.LootItems = new array<ref BountyRewardItem>;
            BountyRewardItem defaultReward = new BountyRewardItem;
            if (isSurvivalReward)
            {
                defaultReward.ItemClassName = "BandageDressing";
            }
            else
            {
                defaultReward.ItemClassName = "AKM";
            }
            defaultReward.SpawnChance = 100.0;
            defaultReward.Attachments = new array<ref BountyRewardAttachment>;
            defaultSection.LootItems.Insert(defaultReward);
            rewardSections.Insert(defaultSection);
            useSectionSystem = true;
        }
        int i; 
        array<ref BountyCurrencyReward> currenciesToGive; 
        EntityAI itemInHands; 
        if (useSectionSystem)
        {
            int sectionIdx;
            BountyRewardSection section;
            int itemsToPickFromSection;
            int sectionItemMin;
            int sectionItemMax;
            array<ref BountyRewardItem> sectionItemsToSpawn;
            BountyRewardItem sectionItem;
            BountyRewardItem selectedSectionItem;
            int sectionPickedCount;
            int sectionJ;
            array<ref BountyRewardItem> availableSectionItems;
            EntityAI sectionContainer;
            string sectionContainerClassName;
            bool sectionHasItems;
            BountyRewardSection selectedSection = null;
            bool sectionSuccess = false;
            int maxSectionRetries = 10; 
            int sectionRetryCount = 0;
            while (!sectionSuccess && sectionRetryCount < maxSectionRetries)
            {
                sectionRetryCount++;
                selectedSection = null;
                float totalWeight = 0.0;
                float randomRoll;
                float currentWeight = 0.0;
                for (sectionIdx = 0; sectionIdx < rewardSections.Count(); sectionIdx++)
                {
                    section = rewardSections.Get(sectionIdx);
                    if (!section || !section.LootItems || section.LootItems.Count() == 0)
                        continue;
                    totalWeight = totalWeight + section.SpawnChance;
                }
                if (totalWeight > 0.0)
                {
                    randomRoll = Math.RandomFloat(0.0, totalWeight);
                    currentWeight = 0.0;
                    for (sectionIdx = 0; sectionIdx < rewardSections.Count(); sectionIdx++)
                    {
                        section = rewardSections.Get(sectionIdx);
                        if (!section || !section.LootItems || section.LootItems.Count() == 0)
                            continue;
                        currentWeight = currentWeight + section.SpawnChance;
                        if (randomRoll <= currentWeight)
                        {
                            selectedSection = section;
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Section " + section.Name + " selected (SpawnChance: " + section.SpawnChance.ToString() + "%, total weight: " + totalWeight.ToString() + ", rolled: " + randomRoll.ToString() + ", retry: " + sectionRetryCount.ToString() + ")");
                            break;
                        }
                    }
                }
                if (selectedSection)
                {
                    section = selectedSection;
                    sectionContainerClassName = section.ContainerClassName;
                    if (sectionContainerClassName == "")
                    {
                        GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Section " + section.Name + " has no ContainerClassName! Using default: SeaChest");
                        sectionContainerClassName = "SeaChest"; 
                    }
                    sectionItemMin = section.ItemsMin;
                    sectionItemMax = section.ItemsMax;
                    if (sectionItemMin < 0)
                        sectionItemMin = 0;
                    if (sectionItemMax < sectionItemMin)
                        sectionItemMax = sectionItemMin;
                    int itemsToPick = sectionItemMin;
                    if (sectionItemMax > sectionItemMin)
                        itemsToPick = Math.RandomInt(sectionItemMin, sectionItemMax + 1);
                    if (itemsToPick > section.LootItems.Count())
                        itemsToPick = section.LootItems.Count();
                    sectionItemsToSpawn = new array<ref BountyRewardItem>;
                    int itemRetryCount = 0;
                    int maxItemRetries = 20; 
                    while (sectionItemsToSpawn.Count() == 0 && itemRetryCount < maxItemRetries)
                    {
                        itemRetryCount++;
                        sectionItemsToSpawn.Clear();
                        if (itemsToPick > 0)
                        {
                            availableSectionItems = new array<ref BountyRewardItem>;
                            for (i = 0; i < section.LootItems.Count(); i++)
                            {
                                sectionItem = section.LootItems.Get(i);
                                if (sectionItem && sectionItem.ItemClassName != "")
                                {
                                    availableSectionItems.Insert(sectionItem);
                                }
                            }
                            sectionPickedCount = 0;
                            array<ref BountyRewardItem> tempAvailableItems = new array<ref BountyRewardItem>;
                            for (i = 0; i < availableSectionItems.Count(); i++)
                            {
                                tempAvailableItems.Insert(availableSectionItems.Get(i));
                            }
                            while (sectionPickedCount < itemsToPick && tempAvailableItems.Count() > 0)
                            {
                                selectedSectionItem = SelectRandomRewardItem(tempAvailableItems);
                                if (selectedSectionItem)
                                {
                                    sectionItemsToSpawn.Insert(selectedSectionItem);
                                    for (sectionJ = tempAvailableItems.Count() - 1; sectionJ >= 0; sectionJ--)
                                    {
                                        if (tempAvailableItems.Get(sectionJ) == selectedSectionItem)
                                        {
                                            tempAvailableItems.Remove(sectionJ);
                                            break;
                                        }
                                    }
                                    sectionPickedCount = sectionPickedCount + 1;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                    if (itemRetryCount >= maxItemRetries && sectionItemsToSpawn.Count() == 0)
                    {
                        GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Failed to pick items from section " + section.Name + " after " + maxItemRetries.ToString() + " retries!");
                    }
                    sectionHasItems = sectionItemsToSpawn.Count() > 0;
                    if (sectionHasItems)
                    {
                        if (spawnItemsDirectlyToInventory)
                        {
                            bool sendNotification = false; 
                            bool inventorySuccess = BountyRewardContainerHelper.AddItemsToPlayerInventory(player, sectionItemsToSpawn, sendNotification);
                            if (inventorySuccess)
                            {
                                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Added " + sectionItemsToSpawn.Count().ToString() + " item(s) directly to player inventory for section " + section.Name);
                                sectionSuccess = true; 
                            }
                            else
                            {
                                GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] Failed to add items to player inventory for section " + section.Name + " (no space available). Retrying section selection...");
                                sectionSuccess = false; 
                            }
                        }
                        else
                        {
                            itemInHands = player.GetHumanInventory().GetEntityInHands();
                            if (itemInHands)
                            {
                                GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] Player " + player.GetIdentity().GetName() + " tried to claim reward but hands are not free");
                                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE, identity);
                                if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
                                {
                                    currenciesToGive = SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
                                    if (currenciesToGive && currenciesToGive.Count() > 0)
                                    {
                                        BountyRewardContainerHelper.AddCurrencyToPlayerInventory(player, currenciesToGive);
                                    }
                                }
                                return false;
                            }
                            sectionContainer = EntityAI.Cast(player.GetHumanInventory().CreateInHands(sectionContainerClassName));
                            if (!sectionContainer)
                            {
                                GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] Failed to create container for section " + section.Name + ": " + sectionContainerClassName);
                                if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
                                {
                                    currenciesToGive = SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
                                    if (currenciesToGive && currenciesToGive.Count() > 0)
                                    {
                                        BountyRewardContainerHelper.AddCurrencyToPlayerInventory(player, currenciesToGive);
                                    }
                                }
                                return false;
                            }
                            BountyRewardContainerHelper.PopulateContainer(sectionContainer, sectionItemsToSpawn, ruinedContainerAsReward);
                            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Created container for section " + section.Name + " (" + sectionContainerClassName + ") with " + sectionItemsToSpawn.Count().ToString() + " items");
                            sectionSuccess = true; 
                        }
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] Selected section " + section.Name + " has no items to spawn! Retrying section selection...");
                        sectionSuccess = false; 
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] No section was selected! Retrying...");
                    sectionSuccess = false; 
                }
            } 
            if (!sectionSuccess && sectionRetryCount >= maxSectionRetries)
            {
                GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Failed to get a section with items after " + maxSectionRetries.ToString() + " retries! Not consuming reward.");
                if (identity)
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL, identity);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyCloseBoardMenu", null, true, identity);
                }
                return false; 
            }
            if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
            {
                            currenciesToGive = SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
                if (currenciesToGive && currenciesToGive.Count() > 0)
                {
                    BountyRewardContainerHelper.AddCurrencyToPlayerInventory(player, currenciesToGive);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Added " + currenciesToGive.Count().ToString() + " currency rewards to player inventory (CurrencyMin: " + currencyMin.ToString() + ", CurrencyMax: " + currencyMax.ToString() + ")");
                }
            }
            return true; 
        }
        GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] No reward sections configured and no fallback available!");
        return false;
    }
    static bool GiveCurrencyRewardsOnly(PlayerBase player, bool isSurvivalReward = false)
    {
        if (!IsMissionHost())
            return false;
        if (!player || !player.GetIdentity())
            return false;
        if (!g_BountyConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] Config not loaded!");
            return false;
        }
        PlayerIdentity identity = player.GetIdentity();
        string playerName = identity.GetName();
        if (player.IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
        {
            string rewardType = "currency";
            if (isSurvivalReward)
                rewardType = "survival currency";
            else
                rewardType = "kill currency";
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Player " + playerName + " is a rule breaker - blocking " + rewardType + " reward (PvERuleBreakerGiveRewards = false)");
            return false;
        }
        array<ref BountyCurrencyReward> currencyRewards;
        if (!g_BountySuccessRewardConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[Bounty Reward] BountySuccessRewardConfig not loaded!");
            return false;
        }
        currencyRewards = g_BountySuccessRewardConfig.BountyCurrencyRewards;
        int currencyMin = g_BountySuccessRewardConfig.CurrencyMin;
        int currencyMax = g_BountySuccessRewardConfig.CurrencyMax;
        if (currencyMin < 0)
            currencyMin = 0;
        if (currencyMax < currencyMin)
            currencyMax = currencyMin;
        bool hasCurrencyRewards = currencyRewards && currencyRewards.Count() > 0;
        if (!hasCurrencyRewards)
        {
            string rewardTypeStr;
            if (isSurvivalReward)
                rewardTypeStr = "survival";
            else
                rewardTypeStr = "kill";
            GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] No currency rewards configured for " + rewardTypeStr + " rewards!");
            return false;
        }
        array<ref BountyCurrencyReward> currenciesToGive = SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
        if (!currenciesToGive || currenciesToGive.Count() == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[Bounty Reward] No currency rewards selected after applying selection logic!");
            return false;
        }
        BountyRewardContainerHelper.AddCurrencyToPlayerInventory(player, currenciesToGive);
        string currencyCountStr = currenciesToGive.Count().ToString();
        GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty Reward] Added " + currencyCountStr + " currency rewards directly to player inventory for " + playerName);
        return true; 
    }
    #ifdef EXPANSIONMODBASEBUILDING
    void RefreshTerritoryCache()
    {
        if (!IsMissionHost())
            return;
        m_TerritoryCache.Clear();
        m_PlayerTerritoryCache.Clear();
        Managed territoryModule = CF_ModuleCoreManager.Get(ExpansionTerritoryModule);
        if (!territoryModule)
            return;
        float territorySize = 150.0; 
        Managed territorySettings = GetExpansionSettings().GetTerritory();
        if (territorySettings)
        {
            EnScript.GetClassVar(territorySettings, "TerritorySize", 0, territorySize);
        }
        map<int, TerritoryFlag> territoryFlags;
        g_Script.CallFunction(territoryModule, "GetAllTerritoryFlags", territoryFlags, null);
        if (!territoryFlags)
            return;
        foreach (int territoryID, TerritoryFlag flag: territoryFlags)
        {
            if (!flag || !flag.HasExpansionTerritoryInformation())
                continue;
            ExpansionTerritory territory = flag.GetTerritory();
            if (!territory)
                continue;
            TerritoryCacheData cacheData = new TerritoryCacheData();
            cacheData.TerritoryID = territoryID;
            cacheData.Position = territory.GetPosition();
            cacheData.TerritorySize = territorySize;
            EnScript.GetClassVar(territory, "TerritoryOwnerID", 0, cacheData.OwnerID);
            array<Man> allPlayers = new array<Man>();
            GetGame().GetPlayers(allPlayers);
            for (int playerIdx = 0; playerIdx < allPlayers.Count(); playerIdx++)
            {
                PlayerBase p = PlayerBase.Cast(allPlayers.Get(playerIdx));
                if (!p || !p.GetIdentity())
                    continue;
                string pID = p.GetIdentity().GetId();
                if (pID == cacheData.OwnerID)
                    continue;
                bool isMember = false;
                g_Script.CallFunction(territory, "IsMember", isMember, pID);
                if (isMember)
                {
                    cacheData.MemberIDs.Insert(pID);
                }
            }
            m_TerritoryCache.Set(territoryID, cacheData);
            if (cacheData.OwnerID != "")
            {
                if (!m_PlayerTerritoryCache.Contains(cacheData.OwnerID))
                {
                    m_PlayerTerritoryCache.Set(cacheData.OwnerID, new array<int>());
                }
                array<int> ownerTerritories = m_PlayerTerritoryCache.Get(cacheData.OwnerID);
                ownerTerritories.Insert(territoryID);
            }
            for (int j = 0; j < cacheData.MemberIDs.Count(); j++)
            {
                string memberID = cacheData.MemberIDs.Get(j);
                if (memberID != "")
                {
                    if (!m_PlayerTerritoryCache.Contains(memberID))
                    {
                        m_PlayerTerritoryCache.Set(memberID, new array<int>());
                    }
                    array<int> memberTerritories = m_PlayerTerritoryCache.Get(memberID);
                    memberTerritories.Insert(territoryID);
                }
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyManager] Refreshed territory cache: " + m_TerritoryCache.Count() + " territories, " + m_PlayerTerritoryCache.Count() + " players");
    }
    array<int> GetCachedPlayerTerritories(string playerID)
    {
        if (m_TerritoryCache.Count() == 0)
        {
            RefreshTerritoryCache();
        }
        if (m_PlayerTerritoryCache.Contains(playerID))
        {
            return m_PlayerTerritoryCache.Get(playerID);
        }
        return null;
    }
    TerritoryCacheData GetCachedTerritoryData(int territoryID)
    {
        if (m_TerritoryCache.Contains(territoryID))
        {
            return m_TerritoryCache.Get(territoryID);
        }
        return null;
    }
    bool IsPlayerInOwnExpansionTerritory(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return false;
        if (m_TerritoryCache.Count() == 0)
        {
            RefreshTerritoryCache();
        }
        string playerID = player.GetIdentity().GetId();
        vector playerPos = player.GetPosition();
        array<int> playerTerritories = GetCachedPlayerTerritories(playerID);
        if (!playerTerritories || playerTerritories.Count() == 0)
            return false;
        int i;
        int territoryID;
        TerritoryCacheData cacheData;
        float distSq;
        float territorySizeSq;
        for (i = 0; i < playerTerritories.Count(); i++)
        {
            territoryID = playerTerritories.Get(i);
            cacheData = GetCachedTerritoryData(territoryID);
            if (!cacheData)
                continue;
            distSq = vector.DistanceSq(cacheData.Position, playerPos);
            territorySizeSq = cacheData.TerritorySize * cacheData.TerritorySize;
            if (distSq <= territorySizeSq)
            {
                return true;
            }
        }
        return false;
    }
    #endif
}