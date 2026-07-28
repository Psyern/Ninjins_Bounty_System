class obfc_BountyPreservedData
{
	float obfv_RemainingDuration;
	BountyType obfv_Type;
	float obfv_StartTime; 
	float obfv_OriginalDuration; 
	void obfc_BountyPreservedData(float duration = 0.0, BountyType bountyType = BountyType.PLACED, float startTime = 0.0, float originalDuration = 0.0)
	{
		obfv_RemainingDuration = duration;
		obfv_Type = bountyType;
		obfv_StartTime = startTime;
		obfv_OriginalDuration = originalDuration;
	}
}
class obfc_TerritoryCacheData
{
	int obfv_TerritoryID;
	string obfv_OwnerID;
	ref array<string> obfv_MemberIDs;
	vector Position;
	float obfv_TerritorySize;
	void obfc_TerritoryCacheData()
	{
		obfv_MemberIDs = new array<string>();
	}
}
class obfc_BountyManager
{
	private static ref obfc_BountyManager obfv_s_Instance;
	private ref map<string, ref obfc_BountyPreservedData> obfv_m_PreservedBounties; 
	private float obfv_m_LastPausedBountyResumeCheckTime = 0.0; 
	private float obfv_m_LastSafeZoneCheckTime = 0.0; 
	private ref set<PlayerBase> obfv_m_PlayersInSafeZones; 
	private ref map<PlayerBase, string> obfv_m_PlayerSafezoneTypes; 
	private ref set<PlayerBase> obfv_m_PlayersInOwnTerritory; 
	private ref map<int, ref obfc_TerritoryCacheData> obfv_m_TerritoryCache; 
	private ref map<string, ref array<int>> obfv_m_PlayerTerritoryCache; 
	private float obfv_m_LastAutomatedBountyPlacementTime = 0.0; 
	private const float obfv_SAFEZONE_CHECK_INTERVAL_EXPANSION = 12.0; 
	void obfc_BountyManager()
	{
		obfv_m_PreservedBounties = new map<string, ref obfc_BountyPreservedData>();
		obfv_m_LastPausedBountyResumeCheckTime = 0.0;
		obfv_m_LastSafeZoneCheckTime = 0.0;
		obfv_m_PlayersInSafeZones = new set<PlayerBase>();
		obfv_m_PlayerSafezoneTypes = new map<PlayerBase, string>();
		obfv_m_PlayersInOwnTerritory = new set<PlayerBase>();
		obfv_m_TerritoryCache = new map<int, ref obfc_TerritoryCacheData>();
		obfv_m_PlayerTerritoryCache = new map<string, ref array<int>>();
		obfv_m_LastAutomatedBountyPlacementTime = 0.0;
	}
	static obfc_BountyManager GetInstance()
	{
		if (!obfv_s_Instance)
		{
			obfv_s_Instance = new obfc_BountyManager();
		}
		return obfv_s_Instance;
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
		if (!obfc_BountyConfig.obfm_IsSystemActive())
			return;
		currentTime = g_Game.GetTime();
		players = new array<Man>();
		g_Game.GetPlayers(players);
		shouldCheckPausedBountyResume = false;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && (obfv_g_BountyConfig.Core.PauseBountyInTerritory || obfv_g_BountyConfig.Core.PauseBountyInSafeZone))
		{
			checkInterval = 5.0; 
			if (obfv_g_BountyConfig.Core.PausedBountyResumeCheckInterval > 0.0)
			{
				checkInterval = obfv_g_BountyConfig.Core.PausedBountyResumeCheckInterval;
			}
			timeSinceLastPausedCheck = (currentTime - obfv_m_LastPausedBountyResumeCheckTime) / 1000.0; 
			if (timeSinceLastPausedCheck >= checkInterval)
			{
				shouldCheckPausedBountyResume = true;
				obfv_m_LastPausedBountyResumeCheckTime = currentTime;
			}
		}
		shouldCheckSafeZoneExpansion = false;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone && obfv_m_PlayersInSafeZones.Count() > 0)
		{
			timeSinceLastExpansionCheck = (currentTime - obfv_m_LastSafeZoneCheckTime) / 1000.0; 
			if (timeSinceLastExpansionCheck >= obfv_SAFEZONE_CHECK_INTERVAL_EXPANSION)
			{
				shouldCheckSafeZoneExpansion = true;
				obfv_m_LastSafeZoneCheckTime = currentTime;
			}
		}
		for (i = 0; i < players.Count(); i++)
		{
			man = players.Get(i);
			player = PlayerBase.Cast(man);
			if (player && player.obfm_HasBounty())
			{
				if (player.IsAlive())
				{
					identity = player.GetIdentity();
					playerName = "Unknown";
					if (identity)
						playerName = identity.GetName();
					if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfOwnTerritory)
					{
						bool isInOwnTerritory = false;
						#ifdef EXPANSIONMODBASEBUILDING
						isInOwnTerritory = obfm_IsPlayerInOwnExpansionTerritory(player);
						#endif
						if (!isInOwnTerritory)
						{
							isInOwnTerritory = player.obfm_IsPlayerInOwnTerritory();
						}
						int territoryIndex = obfv_m_PlayersInOwnTerritory.Find(player);
						bool wasInOwnTerritory = territoryIndex >= 0;
						if (isInOwnTerritory && !wasInOwnTerritory)
						{
							obfv_m_PlayersInOwnTerritory.Insert(player);
							if (!player.obfm_IsBountyPaused())
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " entered their own territory - teleporting out...");
								player.obfm_TeleportOutOfOwnTerritory();
							}
							else
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " entered their own territory but bounty is paused - allowing them to stay");
							}
						}
						else if (!isInOwnTerritory && wasInOwnTerritory)
						{
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " left their own territory");
							obfv_m_PlayersInOwnTerritory.Remove(territoryIndex);
							if (player.obfm_IsBountyPaused())
							{
								player.obfm_ResumeBounty();
							}
						}
						else if (isInOwnTerritory && wasInOwnTerritory)
						{
							if (!player.obfm_IsBountyPaused())
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " is still in their own territory - teleporting out...");
								player.obfm_TeleportOutOfOwnTerritory();
							}
						}
					}
					if (shouldCheckPausedBountyResume && player.obfm_IsBountyPaused())
					{
						player.obfm_ResumeBounty();
					}
						if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.PauseBountyInSafeZone)
						{
							isInSafeZone = player.obfm_NinjinBountyIsPlayerInSafezone();
							safezoneIndex = obfv_m_PlayersInSafeZones.Find(player);
							wasInSafeZone = safezoneIndex >= 0;
							if (isInSafeZone && !wasInSafeZone)
							{
								obfv_m_PlayersInSafeZones.Insert(player);
								if (!player.obfm_IsBountyPaused())
								{
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " entered a safezone - pausing bounty timer");
									player.obfm_PauseBounty();
									if (identity)
									{
										obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_SAFEZONE, identity);
									}
								}
							}
							else if (!isInSafeZone && wasInSafeZone)
							{
								obfv_m_PlayersInSafeZones.Remove(safezoneIndex);
								obfv_m_PlayerSafezoneTypes.Remove(player);
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " left the safezone - resuming bounty timer");
								if (player.obfm_IsBountyPaused())
								{
									player.obfm_ResumeBounty();
								}
							}
						}
						else if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone)
						{
							isNinjinsSafeZone = player.obfm_NinjinBountyIsPlayerInNinjinsSafeZone();
							isExpansionSafeZone = PlayerBase.obfm_NinjinsBountyExpansionIsInSafezone(player);
							isInSafeZone = isNinjinsSafeZone || isExpansionSafeZone;
							safezoneIndex = obfv_m_PlayersInSafeZones.Find(player);
							wasInSafeZone = safezoneIndex >= 0;
							if (isNinjinsSafeZone)
								safezoneType = "NinjinsPvPPvE";
							else
								safezoneType = "Expansion";
							if (isInSafeZone && !wasInSafeZone)
							{
								if (isNinjinsSafeZone && player.obfm_NinjinBountyIsOnSafeZoneExitTimer())
								{
									obfv_m_PlayersInSafeZones.Insert(player);
									obfv_m_PlayerSafezoneTypes.Set(player, safezoneType); 
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " entered " + safezoneType + " safezone but has active exit timer (netSync_IsSZOnExit = true) - adding to tracking set, skipping teleport");
								}
								else
								{
									obfv_m_PlayersInSafeZones.Insert(player);
									obfv_m_PlayerSafezoneTypes.Set(player, safezoneType); 
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " entered " + safezoneType + " safezone - adding to tracking set");
									player.obfm_TeleportOutOfSafeZone();
								}
							}
							else if (!isInSafeZone && wasInSafeZone)
							{
								exitedSafezoneType = "Unknown";
								if (obfv_m_PlayerSafezoneTypes.Contains(player))
								{
									exitedSafezoneType = obfv_m_PlayerSafezoneTypes.Get(player);
								}
								else
								{
									exitedSafezoneType = safezoneType;
								}
								obfv_m_PlayersInSafeZones.Remove(safezoneIndex);
								obfv_m_PlayerSafezoneTypes.Remove(player);
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " exited " + exitedSafezoneType + " safezone - removing from tracking set");
							}
							if (wasInSafeZone && shouldCheckSafeZoneExpansion)
							{
								isCurrentlyNinjinsSafeZone = player.obfm_NinjinBountyIsPlayerInNinjinsSafeZone();
								isCurrentlyInExpansionSafeZone = PlayerBase.obfm_NinjinsBountyExpansionIsInSafezone(player);
								int removeIndex = -1;
								if (isCurrentlyInExpansionSafeZone && !isCurrentlyNinjinsSafeZone)
								{
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " still in Expansion safezone after " + obfv_SAFEZONE_CHECK_INTERVAL_EXPANSION + " seconds - teleporting out...");
									player.obfm_TeleportOutOfSafeZone();
								}
								else if (!isCurrentlyInExpansionSafeZone && !isCurrentlyNinjinsSafeZone)
								{
									removeIndex = obfv_m_PlayersInSafeZones.Find(player);
									if (removeIndex >= 0)
										obfv_m_PlayersInSafeZones.Remove(removeIndex);
									obfv_m_PlayerSafezoneTypes.Remove(player); 
									obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " no longer in Expansion safezone (periodic check) - removing from tracking set, stopping checks");
								}
								else if (isCurrentlyNinjinsSafeZone)
								{
									if (player.obfm_NinjinBountyIsOnSafeZoneExitTimer())
									{
										obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " is in NinjinsPvPPvE safezone with active exit timer (netSync_IsSZOnExit = true) - skipping teleport, will check again after exit timer expires");
									}
									else
									{
										obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bountied player " + playerName + " is in NinjinsPvPPvE safezone without exit timer (netSync_IsSZOnExit = false) - teleporting out...");
										player.obfm_TeleportOutOfSafeZone();
									}
								}
							}
						}
				}
				else
				{
					int deadPlayerIndex = obfv_m_PlayersInSafeZones.Find(player);
					if (deadPlayerIndex >= 0)
					{
						obfv_m_PlayersInSafeZones.Remove(deadPlayerIndex);
						obfv_m_PlayerSafezoneTypes.Remove(player); 
					}
					int deadTerritoryIndex = obfv_m_PlayersInOwnTerritory.Find(player);
					if (deadTerritoryIndex >= 0)
					{
						obfv_m_PlayersInOwnTerritory.Remove(deadTerritoryIndex);
					}
				}
			}
			else
			{
				int noBountyIndex = obfv_m_PlayersInSafeZones.Find(player);
				if (noBountyIndex >= 0)
				{
					obfv_m_PlayersInSafeZones.Remove(noBountyIndex);
					obfv_m_PlayerSafezoneTypes.Remove(player); 
				}
				int noBountyTerritoryIndex = obfv_m_PlayersInOwnTerritory.Find(player);
				if (noBountyTerritoryIndex >= 0)
				{
					obfv_m_PlayersInOwnTerritory.Remove(noBountyTerritoryIndex);
				}
			}
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.EnableAutomatedBountyPlacement && obfv_g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds > 0.0)
		{
			float intervalMs = obfv_g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds * 1000.0; 
			float timeSinceLastPlacement = currentTime - obfv_m_LastAutomatedBountyPlacementTime;
			if (obfv_m_LastAutomatedBountyPlacementTime == 0.0 || timeSinceLastPlacement >= intervalMs)
			{
				PlayerBase selectedPlayer = obfm_SelectEligiblePlayerForAutomatedBounty();
				if (selectedPlayer)
				{
					bool success = obfm_ApplyBountyToPlayer(selectedPlayer, null, 0.0, "Automated server bounty placement", BountyType.PLACED);
					if (success)
					{
						obfv_m_LastAutomatedBountyPlacementTime = currentTime;
						PlayerIdentity selectedIdentity = selectedPlayer.GetIdentity();
						string selectedName = "Unknown";
						if (selectedIdentity)
							selectedName = selectedIdentity.GetName();
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Automated bounty placed on " + selectedName + " (interval: " + obfv_g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds.ToString() + "s)");
					}
					else
					{
						obfv_m_LastAutomatedBountyPlacementTime = currentTime - (intervalMs * 0.9);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyManager] Automated bounty placement failed - will retry in " + (obfv_g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds * 0.1).ToString() + "s");
					}
				}
				else
				{
					obfv_m_LastAutomatedBountyPlacementTime = currentTime;
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Automated bounty placement skipped - no eligible players found");
				}
			}
		}
		array<string> keysToRemove = new array<string>();
		string playerId;
		obfc_BountyPreservedData data;
		for (i = 0; i < obfv_m_PreservedBounties.Count(); i++)
		{
			playerId = obfv_m_PreservedBounties.GetKey(i);
			data = obfv_m_PreservedBounties.GetElement(i);
			if (data && data.obfv_RemainingDuration <= 0.0)
			{
				keysToRemove.Insert(playerId);
			}
		}
		for (i = 0; i < keysToRemove.Count(); i++)
		{
			playerId = keysToRemove.Get(i);
			obfv_m_PreservedBounties.Remove(playerId);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cleaned up preserved bounty for player ID: " + playerId);
		}
	}
	int obfm_GetBountiedPlayerCount()
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
			if (player && player.obfm_HasBounty() && player.IsAlive())
			{
				count++;
			}
		}
		return count;
	}
	void obfm_PreserveBountyForPlayer(string playerId, float remainingDuration, BountyType bountyType, float startTime = 0.0, float originalDuration = 0.0)
	{
		if (!IsMissionHost())
			return;
		if (remainingDuration <= 0.0)
			return;
		obfv_m_PreservedBounties.Set(playerId, new obfc_BountyPreservedData(remainingDuration, bountyType, startTime, originalDuration));
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Preserved bounty for player ID: " + playerId + " - RemainingDuration: " + remainingDuration.ToString() + "s, BountyType: " + bountyType.ToString() + ", StartTime: " + startTime.ToString() + "s, OriginalDuration: " + originalDuration.ToString() + "s");
	}
	obfc_BountyPreservedData obfm_GetPreservedBountyForPlayer(string playerId)
	{
		if (!IsMissionHost())
			return null;
		obfc_BountyPreservedData data = obfv_m_PreservedBounties.Get(playerId);
		if (data)
		{
			obfv_m_PreservedBounties.Remove(playerId);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Retrieved preserved bounty for player ID: " + playerId + " - RemainingDuration: " + data.obfv_RemainingDuration.ToString() + "s");
		}
		return data;
	}
	private PlayerBase obfm_SelectEligiblePlayerForAutomatedBounty()
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
			if (player.obfm_HasBounty())
				continue;
			if (player.obfm_IsBountyOnCooldown())
				continue;
			if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(identity))
				continue;
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds > 0)
			{
				int playerLifetime = player.StatGet("playtime");
				if (playerLifetime < obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds)
					continue;
			}
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone)
			{
				if (player.obfm_NinjinBountyIsPlayerInSafezone())
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
	//! Deferred entry point used by the BountyWarningTimeSeconds countdown - re-runs every eligibility
	//! check (the target may have died, logged out or entered a safezone during the warning).
	void obfm_ApplyBountyAfterWarning(PlayerBase targetPlayer, PlayerBase sourcePlayer, float durationSeconds, string reason, BountyType bountyType, bool ignoreMaxBountiedLimit)
	{
		if (!targetPlayer || !targetPlayer.GetIdentity() || !targetPlayer.IsAlive())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Warned bounty target is no longer available - bounty not applied");
			return;
		}
		obfm_ApplyBountyToPlayer(targetPlayer, sourcePlayer, durationSeconds, reason, bountyType, ignoreMaxBountiedLimit, true);
	}
	static bool obfm_ApplyBountyToPlayer(PlayerBase targetPlayer, PlayerBase sourcePlayer = null, float durationSeconds = 0.0, string reason = "", BountyType bountyType = BountyType.PLACED, bool ignoreMaxBountiedLimit = false, bool skipWarning = false)
	{
		PlayerIdentity targetIdentity;
		string targetName;
		bool isAdminPlacing;
		int playerLifetime;
		obfc_BountyManager warningManager;
		int warningDelayMs;
		if (!IsMissionHost())
			return false;
		if (!targetPlayer || !targetPlayer.GetIdentity())
			return false;
		if (!obfc_BountyConfig.obfm_IsSystemActive())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot apply bounty - system is not active (disabled or minimum players not met)");
			return false;
		}
		targetIdentity = targetPlayer.GetIdentity();
		targetName = "Unknown";
		if (targetIdentity)
		{
			targetName = targetIdentity.GetName();
		}
		if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(targetIdentity))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is blacklisted");
			return false;
		}
		if (bountyType != BountyType.RULE_BREAKER && obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds > 0)
		{
			isAdminPlacing = false;
			if (sourcePlayer && sourcePlayer.GetIdentity() && obfv_g_BountyAdminConfig)
			{
				isAdminPlacing = obfv_g_BountyAdminConfig.obfm_IsAdminIdentity(sourcePlayer.GetIdentity());
			}
			if (!isAdminPlacing)
			{
				playerLifetime = targetPlayer.StatGet("playtime"); 
				if (playerLifetime < obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player lifetime (" + playerLifetime.ToString() + "s) is less than required (" + obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds.ToString() + "s)");
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
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Admin " + adminName + " is placing bounty - bypassing lifetime check for " + targetName);
			}
		}
		if (bountyType != BountyType.RULE_BREAKER && targetPlayer.obfm_IsBountyOnCooldown())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is on cooldown");
			if (sourcePlayer && sourcePlayer.GetIdentity())
			{
				int cooldownSeconds = Math.Ceil(targetPlayer.obfm_GetBountyCooldownRemaining());
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN, sourcePlayer.GetIdentity(), targetName, "", 0.0, 0, 0, 0, 0, 0, cooldownSeconds);
			}
			return false;
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone)
		{
			if (targetPlayer.obfm_NinjinBountyIsPlayerInSafezone())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot apply bounty to " + targetName + " - player is in a safezone");
				if (sourcePlayer && sourcePlayer.GetIdentity())
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE, sourcePlayer.GetIdentity(), targetName);
				}
				return false;
			}
		}
		if (durationSeconds <= 0.0)
		{
			if (obfv_g_BountyConfig)
			{
				if (bountyType == BountyType.RULE_BREAKER)
				{
					durationSeconds = obfv_g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
				}
				else
				{
					durationSeconds = obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds;
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[BountyManager] Cannot apply bounty - config not loaded!");
				return false;
			}
		}
		if (!skipWarning && bountyType != BountyType.RULE_BREAKER && obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.BountyWarningTimeSeconds > 0.0)
		{
			warningManager = obfc_BountyManager.GetInstance();
			if (warningManager && g_Game && g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY))
			{
				warningDelayMs = Math.Round(obfv_g_BountyConfig.Core.BountyWarningTimeSeconds * obfv_BOUNTY_MS_TO_SECONDS);
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_WARNING_BROADCAST, null, targetName, "", obfv_g_BountyConfig.Core.BountyWarningTimeSeconds);
				g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(warningManager.obfm_ApplyBountyAfterWarning, warningDelayMs, false, targetPlayer, sourcePlayer, durationSeconds, reason, bountyType, ignoreMaxBountiedLimit);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Bounty on " + targetName + " announced - applying in " + obfv_g_BountyConfig.Core.BountyWarningTimeSeconds.ToString() + "s");
				return true;
			}
		}
		int clearedRewardCount = 0;
		if (bountyType == BountyType.RULE_BREAKER && obfv_g_BountyConfig && obfv_g_BountyConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty)
		{
			clearedRewardCount = targetPlayer.obfm_GetTotalPendingRewardCount();
			if (clearedRewardCount > 0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Clearing " + clearedRewardCount.ToString() + " pending reward(s) for " + targetName + " due to rule breaker bounty");
				targetPlayer.obfv_m_PendingSuccessRewardCount = 0;
				targetPlayer.SetSynchDirty();
			}
		}
		targetPlayer.obfm_SetBountyWithType(durationSeconds, bountyType, false, clearedRewardCount, ignoreMaxBountiedLimit);
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
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Applied bounty to " + targetName + " for " + durationSeconds.ToString() + " seconds. Source: " + sourceName + ", Reason: " + logReason);
		return true;
	}
	static bool obfm_ClearBountyFromPlayer(PlayerBase targetPlayer, PlayerBase sourcePlayer = null, string reason = "", bool skipRewards = false)
	{
		PlayerIdentity targetIdentity;
		string targetName;
		string sourceName;
		string logReason;
		if (!IsMissionHost())
			return false;
		if (!targetPlayer || !targetPlayer.GetIdentity())
			return false;
		if (!targetPlayer.obfm_HasBounty())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cannot clear bounty - player does not have a bounty");
			return false;
		}
		targetPlayer.obfm_ClearBounty(skipRewards, BountyEndReason.CLEARED);
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
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Cleared bounty from " + targetName + ". Source: " + sourceName + ", Reason: " + logReason);
		return true;
	}
	static void obfm_ReloadAllConfigs(PlayerBase requestingPlayer = null)
	{
		if (!IsMissionHost())
			return;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] Reloading all bounty system configs from disk...");
		bool allSuccess = true;
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_CONFIG_FILE))
		{
			obfc_BountyConfig newBountyConfig = new obfc_BountyConfig();
			JsonFileLoader<obfc_BountyConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_CONFIG_FILE, newBountyConfig);
			if (newBountyConfig)
			{
				newBountyConfig.obfm_ValidateConfig();
				obfv_g_BountyConfig = newBountyConfig;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] BountyConfig reloaded from disk. EnableBountySystem: " + obfv_g_BountyConfig.Core.EnableBountySystem.ToString() + ", Duration: " + obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds.ToString() + " seconds");
				obfc_BountyConfig.obfm_LogConfigValues(obfv_g_BountyConfig, true);
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountyConfig from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] BountyConfig.json file not found!");
			allSuccess = false;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE))
		{
			obfc_BountySuccessRewardConfig newSuccessConfig = new obfc_BountySuccessRewardConfig();
			JsonFileLoader<obfc_BountySuccessRewardConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_SUCCESS_REWARD_CONFIG_FILE, newSuccessConfig);
			if (newSuccessConfig)
			{
				obfv_g_BountySuccessRewardConfig = newSuccessConfig;
				int sectionCount = 0;
				if (obfv_g_BountySuccessRewardConfig.BountyRewardItems)
					sectionCount = obfv_g_BountySuccessRewardConfig.BountyRewardItems.Count();
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] BountySuccessRewardConfig reloaded from disk. RewardSections: " + sectionCount.ToString());
				obfc_BountySuccessRewardConfig.obfm_LogConfigValues(obfv_g_BountySuccessRewardConfig, true);
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountySuccessRewardConfig from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] BountySuccessRewardConfig.json file not found!");
			allSuccess = false;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE))
		{
			obfc_BountyAdminConfig newAdminConfig = new obfc_BountyAdminConfig();
			JsonFileLoader<obfc_BountyAdminConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_ADMIN_CONFIG_FILE, newAdminConfig);
			if (newAdminConfig)
			{
				obfv_g_BountyAdminConfig = newAdminConfig;
				int adminCount = 0;
				if (obfv_g_BountyAdminConfig && obfv_g_BountyAdminConfig.AdminGUIDs)
				{
					adminCount = obfv_g_BountyAdminConfig.AdminGUIDs.Count();
				}
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] BountyAdminConfig reloaded from disk. AdminGUIDs: " + adminCount.ToString());
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
							bool isAdmin = obfv_g_BountyAdminConfig.obfm_IsAdminIdentity(playerIdentity);
							playerBase.obfm_SetBountyAdminStatus(isAdmin);
						}
					}
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountyAdminConfig from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Admins.json file not found!");
			allSuccess = false;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE))
		{
			obfc_BountyBlacklistConfig newBlacklistConfig = new obfc_BountyBlacklistConfig();
			JsonFileLoader<obfc_BountyBlacklistConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_BLACKLIST_CONFIG_FILE, newBlacklistConfig);
			if (newBlacklistConfig)
			{
				obfv_g_BountyBlacklistConfig = newBlacklistConfig;
				int blacklistCount = 0;
				if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.BlacklistedGUIDs)
				{
					blacklistCount = obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Count();
				}
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] BountyBlacklistConfig reloaded from disk. BlacklistedGUIDs: " + blacklistCount.ToString());
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountyBlacklistConfig from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Blacklist.json file not found!");
			allSuccess = false;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_ZONE_CONFIG_FILE))
		{
			obfc_BountyZoneConfig newZoneConfig = new obfc_BountyZoneConfig();
			JsonFileLoader<obfc_BountyZoneConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_ZONE_CONFIG_FILE, newZoneConfig);
			if (newZoneConfig)
			{
				newZoneConfig.obfm_ValidateConfig();
				obfv_g_BountyZoneConfig = newZoneConfig;
				obfc_BountyZoneConfig.obfm_LogConfig(obfv_g_BountyZoneConfig);
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountyZoneConfig from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] BountyZones.json file not found!");
			allSuccess = false;
		}
		obfc_BountyConfig.obfm_CheckDirectories();
		if (FileExist(obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE))
		{
			obfc_BountyBoardPlacementConfig newBoardConfig = new obfc_BountyBoardPlacementConfig();
			JsonFileLoader<obfc_BountyBoardPlacementConfig>.JsonLoadFile(obfv_Ninjins_Bounty_System_BOARD_CONFIG_FILE, newBoardConfig);
			if (newBoardConfig)
			{
				newBoardConfig.obfm_ValidateConfig();
				obfv_g_BountyBoardPlacementConfig = newBoardConfig;
				obfc_BountyBoardPlacementConfig.obfm_LogConfig(obfv_g_BountyBoardPlacementConfig, true);
				obfc_BountyModule bountyModule = obfc_BountyModule.GetInstance();
				if (bountyModule)
				{
					bountyModule.obfm_SpawnConfiguredBountyBoards();
				}
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] BountyBoardPlacements.json reloaded from disk. BoardPlacements: " + obfv_g_BountyBoardPlacementConfig.BoardPlacements.Count().ToString());
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] Failed to reload BountyBoardPlacements.json from disk!");
				allSuccess = false;
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Reload] BountyBoardPlacements.json file not found!");
			allSuccess = false;
		}
		if (requestingPlayer)
		{
			PlayerIdentity identity = requestingPlayer.GetIdentity();
			if (identity)
			{
				if (allSuccess)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] All configs reloaded successfully from disk!");
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] Note: Existing bounties will use their original duration. New bounties will use the updated duration.");
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS, identity);
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Reload] Some configs failed to reload. Check logs for details.");
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE, identity);
				}
			}
		}
		if (allSuccess && obfv_g_BountyConfig && obfv_g_BountyConfig.UI)
		{
			array<Man> configReloadPlayers = new array<Man>();
			g_Game.GetPlayers(configReloadPlayers);
			int configReloadI;
			int rpcSentCount = 0;
			float posX = obfv_g_BountyConfig.UI.CountdownWidgetPositionX;
			float posY = obfv_g_BountyConfig.UI.CountdownWidgetPositionY;
			float width = obfv_g_BountyConfig.UI.CountdownWidgetWidth;
			float height = obfv_g_BountyConfig.UI.CountdownWidgetHeight;
			int bgColor = obfv_g_BountyConfig.UI.CountdownWidgetBackgroundColor;
			int textColor = obfv_g_BountyConfig.UI.CountdownWidgetTextColor;
			for (configReloadI = 0; configReloadI < configReloadPlayers.Count(); configReloadI++)
			{
				Man configReloadMan = configReloadPlayers.Get(configReloadI);
				PlayerBase configReloadPlayerBase = PlayerBase.Cast(configReloadMan);
				if (configReloadPlayerBase)
				{
					PlayerIdentity configReloadPlayerIdentity = configReloadPlayerBase.GetIdentity();
					if (configReloadPlayerIdentity)
					{
						obfc_BountyUISettingsData uiData = new obfc_BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
						Param1<obfc_BountyUISettingsData> uiParam = new Param1<obfc_BountyUISettingsData>(uiData);
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, configReloadPlayerIdentity);
						rpcSentCount++;
					}
				}
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Reload] Sent BountyConfigReloaded RPC to " + rpcSentCount.ToString() + " client(s) with UI settings: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
		}
	}
	static array<ref obfc_BountyCurrencyReward> obfm_SelectCurrencyRewards(array<ref obfc_BountyCurrencyReward> currencyRewards, int currencyMin, int currencyMax)
	{
		array<ref obfc_BountyCurrencyReward> currenciesToGive = new array<ref obfc_BountyCurrencyReward>;
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
			array<ref obfc_BountyCurrencyReward> availableCurrencies = new array<ref obfc_BountyCurrencyReward>;
			int i;
			obfc_BountyCurrencyReward currency;
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
			obfc_BountyCurrencyReward selectedCurrency;
			array<ref obfc_BountyCurrencyReward> tempAvailableCurrencies = new array<ref obfc_BountyCurrencyReward>;
			for (i = 0; i < availableCurrencies.Count(); i++)
			{
				tempAvailableCurrencies.Insert(availableCurrencies.Get(i));
			}
			while (pickedCount < currenciesToPick && tempAvailableCurrencies.Count() > 0)
			{
				selectedCurrency = obfm_SelectRandomCurrencyReward(tempAvailableCurrencies);
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
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Failed to pick currencies after " + maxCurrencyRetries.ToString() + " retries!");
		}
		return currenciesToGive;
	}
	static obfc_BountyRewardItem obfm_SelectRandomRewardItem(array<ref obfc_BountyRewardItem> rewardItems)
	{
		if (!rewardItems || rewardItems.Count() == 0)
			return null;
		float totalChance = 0.0;
		int i;
		obfc_BountyRewardItem item;
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
	static obfc_BountyCurrencyReward obfm_SelectRandomCurrencyReward(array<ref obfc_BountyCurrencyReward> currencyRewards)
	{
		if (!currencyRewards || currencyRewards.Count() == 0)
			return null;
		float totalChance = 0.0;
		int i;
		obfc_BountyCurrencyReward currency;
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
	static bool obfm_SpawnBountyRewardGiftBox(PlayerBase player, bool isSurvivalReward = false, bool giveCurrency = true)
	{
		if (!IsMissionHost())
			return false;
		if (!player || !player.GetIdentity())
			return false;
		if (!obfv_g_BountyConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Config not loaded!");
			return false;
		}
		if (isSurvivalReward)
		{
			if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Reward || !obfv_g_BountyConfig.Reward.EnableSurvivalReward)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Success reward (survival type) is disabled.");
				return false;
			}
		}
		PlayerIdentity identity = player.GetIdentity();
		if (player.obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
		{
			string playerName = "Unknown";
			if (identity)
				playerName = identity.GetName();
			string rewardType;
			if (isSurvivalReward)
				rewardType = "survival";
			else
				rewardType = "kill"; 
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Player " + playerName + " is a rule breaker - blocking " + rewardType + " reward (PvERuleBreakerGiveRewards = false)");
			return false;
		}
		if (!obfv_g_BountySuccessRewardConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] BountySuccessRewardConfig not loaded!");
			return false;
		}
		array<ref obfc_BountyRewardSection> rewardSections = obfv_g_BountySuccessRewardConfig.BountyRewardItems;
		bool useSectionSystem = rewardSections && rewardSections.Count() > 0;
		array<ref obfc_BountyCurrencyReward> currencyRewards = obfv_g_BountySuccessRewardConfig.BountyCurrencyRewards;
		bool ruinedContainerAsReward = obfv_g_BountySuccessRewardConfig.RuinedContainerAsReward;
		bool spawnItemsDirectlyToInventory = obfv_g_BountySuccessRewardConfig.SpawnItemsDirectlyToInventory;
		int currencyMin = obfv_g_BountySuccessRewardConfig.CurrencyMin;
		int currencyMax = obfv_g_BountySuccessRewardConfig.CurrencyMax;
		if (currencyMin < 0)
			currencyMin = 0;
		if (currencyMax < currencyMin)
			currencyMax = currencyMin;
		if (!useSectionSystem)
		{
			rewardSections = new array<ref obfc_BountyRewardSection>;
			obfc_BountyRewardSection defaultSection = new obfc_BountyRewardSection;
			defaultSection.Name = "Default";
			defaultSection.ContainerClassName = "SeaChest";
			defaultSection.SpawnChance = 100.0;
			defaultSection.ItemsMin = 1;
			defaultSection.ItemsMax = 1;
			defaultSection.LootItems = new array<ref obfc_BountyRewardItem>;
			obfc_BountyRewardItem defaultReward = new obfc_BountyRewardItem;
			if (isSurvivalReward)
			{
				defaultReward.ItemClassName = "BandageDressing";
			}
			else
			{
				defaultReward.ItemClassName = "AKM";
			}
			defaultReward.SpawnChance = 100.0;
			defaultReward.Attachments = new array<ref obfc_BountyRewardAttachment>;
			defaultSection.LootItems.Insert(defaultReward);
			rewardSections.Insert(defaultSection);
			useSectionSystem = true;
		}
		int i; 
		array<ref obfc_BountyCurrencyReward> currenciesToGive; 
		EntityAI itemInHands; 
		if (useSectionSystem)
		{
			int sectionIdx;
			obfc_BountyRewardSection section;
			int itemsToPickFromSection;
			int sectionItemMin;
			int sectionItemMax;
			array<ref obfc_BountyRewardItem> sectionItemsToSpawn;
			obfc_BountyRewardItem sectionItem;
			obfc_BountyRewardItem selectedSectionItem;
			int sectionPickedCount;
			int sectionJ;
			array<ref obfc_BountyRewardItem> availableSectionItems;
			EntityAI sectionContainer;
			string sectionContainerClassName;
			bool sectionHasItems;
			obfc_BountyRewardSection selectedSection = null;
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
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Section " + section.Name + " selected (SpawnChance: " + section.SpawnChance.ToString() + "%, total weight: " + totalWeight.ToString() + ", rolled: " + randomRoll.ToString() + ", retry: " + sectionRetryCount.ToString() + ")");
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
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Section " + section.Name + " has no ContainerClassName! Using default: SeaChest");
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
					sectionItemsToSpawn = new array<ref obfc_BountyRewardItem>;
					int itemRetryCount = 0;
					int maxItemRetries = 20; 
					while (sectionItemsToSpawn.Count() == 0 && itemRetryCount < maxItemRetries)
					{
						itemRetryCount++;
						sectionItemsToSpawn.Clear();
						if (itemsToPick > 0)
						{
							availableSectionItems = new array<ref obfc_BountyRewardItem>;
							for (i = 0; i < section.LootItems.Count(); i++)
							{
								sectionItem = section.LootItems.Get(i);
								if (sectionItem && sectionItem.ItemClassName != "")
								{
									availableSectionItems.Insert(sectionItem);
								}
							}
							sectionPickedCount = 0;
							array<ref obfc_BountyRewardItem> tempAvailableItems = new array<ref obfc_BountyRewardItem>;
							for (i = 0; i < availableSectionItems.Count(); i++)
							{
								tempAvailableItems.Insert(availableSectionItems.Get(i));
							}
							while (sectionPickedCount < itemsToPick && tempAvailableItems.Count() > 0)
							{
								selectedSectionItem = obfm_SelectRandomRewardItem(tempAvailableItems);
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
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Failed to pick items from section " + section.Name + " after " + maxItemRetries.ToString() + " retries!");
					}
					sectionHasItems = sectionItemsToSpawn.Count() > 0;
					if (sectionHasItems)
					{
						if (spawnItemsDirectlyToInventory)
						{
							bool sendNotification = false; 
							bool inventorySuccess = obfc_BountyRewardContainerHelper.obfm_AddItemsToPlayerInventory(player, sectionItemsToSpawn, sendNotification);
							if (inventorySuccess)
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Added " + sectionItemsToSpawn.Count().ToString() + " item(s) directly to player inventory for section " + section.Name);
								sectionSuccess = true; 
							}
							else
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] Failed to add items to player inventory for section " + section.Name + " (no space available). Retrying section selection...");
								sectionSuccess = false; 
							}
						}
						else
						{
							itemInHands = player.GetHumanInventory().GetEntityInHands();
							if (itemInHands)
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] Player " + player.GetIdentity().GetName() + " tried to claim reward but hands are not free");
								obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE, identity);
								if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
								{
									currenciesToGive = obfm_SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
									if (currenciesToGive && currenciesToGive.Count() > 0)
									{
										obfc_BountyRewardContainerHelper.obfm_AddCurrencyToPlayerInventory(player, currenciesToGive);
									}
								}
								return false;
							}
							sectionContainer = EntityAI.Cast(player.GetHumanInventory().CreateInHands(sectionContainerClassName));
							if (!sectionContainer)
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] Failed to create container for section " + section.Name + ": " + sectionContainerClassName);
								if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
								{
									currenciesToGive = obfm_SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
									if (currenciesToGive && currenciesToGive.Count() > 0)
									{
										obfc_BountyRewardContainerHelper.obfm_AddCurrencyToPlayerInventory(player, currenciesToGive);
									}
								}
								return false;
							}
							obfc_BountyRewardContainerHelper.obfm_PopulateContainer(sectionContainer, sectionItemsToSpawn, ruinedContainerAsReward);
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Created container for section " + section.Name + " (" + sectionContainerClassName + ") with " + sectionItemsToSpawn.Count().ToString() + " items");
							sectionSuccess = true; 
						}
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] Selected section " + section.Name + " has no items to spawn! Retrying section selection...");
						sectionSuccess = false; 
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] No section was selected! Retrying...");
					sectionSuccess = false; 
				}
			} 
			if (!sectionSuccess && sectionRetryCount >= maxSectionRetries)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Failed to get a section with items after " + maxSectionRetries.ToString() + " retries! Not consuming reward.");
				if (identity)
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL, identity);
					GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyCloseBoardMenu", null, true, identity);
				}
				return false; 
			}
			if (giveCurrency && currencyRewards && currencyRewards.Count() > 0)
			{
							currenciesToGive = obfm_SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
				if (currenciesToGive && currenciesToGive.Count() > 0)
				{
					obfc_BountyRewardContainerHelper.obfm_AddCurrencyToPlayerInventory(player, currenciesToGive);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Added " + currenciesToGive.Count().ToString() + " currency rewards to player inventory (CurrencyMin: " + currencyMin.ToString() + ", CurrencyMax: " + currencyMax.ToString() + ")");
				}
			}
			return true; 
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] No reward sections configured and no fallback available!");
		return false;
	}
	static bool obfm_GiveCurrencyRewardsOnly(PlayerBase player, bool isSurvivalReward = false)
	{
		if (!IsMissionHost())
			return false;
		if (!player || !player.GetIdentity())
			return false;
		if (!obfv_g_BountyConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] Config not loaded!");
			return false;
		}
		PlayerIdentity identity = player.GetIdentity();
		string playerName = identity.GetName();
		if (player.obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
		{
			string rewardType = "currency";
			if (isSurvivalReward)
				rewardType = "survival currency";
			else
				rewardType = "kill currency";
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Player " + playerName + " is a rule breaker - blocking " + rewardType + " reward (PvERuleBreakerGiveRewards = false)");
			return false;
		}
		array<ref obfc_BountyCurrencyReward> currencyRewards;
		if (!obfv_g_BountySuccessRewardConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[Bounty Reward] BountySuccessRewardConfig not loaded!");
			return false;
		}
		currencyRewards = obfv_g_BountySuccessRewardConfig.BountyCurrencyRewards;
		int currencyMin = obfv_g_BountySuccessRewardConfig.CurrencyMin;
		int currencyMax = obfv_g_BountySuccessRewardConfig.CurrencyMax;
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
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] No currency rewards configured for " + rewardTypeStr + " rewards!");
			return false;
		}
		array<ref obfc_BountyCurrencyReward> currenciesToGive = obfm_SelectCurrencyRewards(currencyRewards, currencyMin, currencyMax);
		if (!currenciesToGive || currenciesToGive.Count() == 0)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty Reward] No currency rewards selected after applying selection logic!");
			return false;
		}
		obfc_BountyRewardContainerHelper.obfm_AddCurrencyToPlayerInventory(player, currenciesToGive);
		string currencyCountStr = currenciesToGive.Count().ToString();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty Reward] Added " + currencyCountStr + " currency rewards directly to player inventory for " + playerName);
		return true; 
	}
	#ifdef EXPANSIONMODBASEBUILDING
	void obfm_RefreshTerritoryCache()
	{
		if (!IsMissionHost())
			return;
		obfv_m_TerritoryCache.Clear();
		obfv_m_PlayerTerritoryCache.Clear();
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
		array<Man> allPlayers = new array<Man>();
		g_Game.GetPlayers(allPlayers);
		foreach (int territoryID, TerritoryFlag flag: territoryFlags)
		{
			if (!flag || !flag.HasExpansionTerritoryInformation())
				continue;
			ExpansionTerritory territory = flag.GetTerritory();
			if (!territory)
				continue;
			obfc_TerritoryCacheData cacheData = new obfc_TerritoryCacheData();
			cacheData.obfv_TerritoryID = territoryID;
			cacheData.Position = territory.GetPosition();
			cacheData.obfv_TerritorySize = territorySize;
			EnScript.GetClassVar(territory, "TerritoryOwnerID", 0, cacheData.obfv_OwnerID);
			for (int playerIdx = 0; playerIdx < allPlayers.Count(); playerIdx++)
			{
				PlayerBase p = PlayerBase.Cast(allPlayers.Get(playerIdx));
				if (!p || !p.GetIdentity())
					continue;
				string pID = p.GetIdentity().GetId();
				if (pID == cacheData.obfv_OwnerID)
					continue;
				bool isMember = false;
				g_Script.CallFunction(territory, "IsMember", isMember, pID);
				if (isMember)
				{
					cacheData.obfv_MemberIDs.Insert(pID);
				}
			}
			obfv_m_TerritoryCache.Set(territoryID, cacheData);
			if (cacheData.obfv_OwnerID != "")
			{
				if (!obfv_m_PlayerTerritoryCache.Contains(cacheData.obfv_OwnerID))
				{
					obfv_m_PlayerTerritoryCache.Set(cacheData.obfv_OwnerID, new array<int>());
				}
				array<int> ownerTerritories = obfv_m_PlayerTerritoryCache.Get(cacheData.obfv_OwnerID);
				ownerTerritories.Insert(territoryID);
			}
			for (int j = 0; j < cacheData.obfv_MemberIDs.Count(); j++)
			{
				string memberID = cacheData.obfv_MemberIDs.Get(j);
				if (memberID != "")
				{
					if (!obfv_m_PlayerTerritoryCache.Contains(memberID))
					{
						obfv_m_PlayerTerritoryCache.Set(memberID, new array<int>());
					}
					array<int> memberTerritories = obfv_m_PlayerTerritoryCache.Get(memberID);
					memberTerritories.Insert(territoryID);
				}
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyManager] Refreshed territory cache: " + obfv_m_TerritoryCache.Count() + " territories, " + obfv_m_PlayerTerritoryCache.Count() + " players");
	}
	array<int> obfm_GetCachedPlayerTerritories(string playerID)
	{
		if (obfv_m_TerritoryCache.Count() == 0)
		{
			obfm_RefreshTerritoryCache();
		}
		if (obfv_m_PlayerTerritoryCache.Contains(playerID))
		{
			return obfv_m_PlayerTerritoryCache.Get(playerID);
		}
		return null;
	}
	obfc_TerritoryCacheData obfm_GetCachedTerritoryData(int territoryID)
	{
		if (obfv_m_TerritoryCache.Contains(territoryID))
		{
			return obfv_m_TerritoryCache.Get(territoryID);
		}
		return null;
	}
	bool obfm_IsPlayerInOwnExpansionTerritory(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
			return false;
		if (obfv_m_TerritoryCache.Count() == 0)
		{
			obfm_RefreshTerritoryCache();
		}
		string playerID = player.GetIdentity().GetId();
		vector playerPos = player.GetPosition();
		array<int> playerTerritories = obfm_GetCachedPlayerTerritories(playerID);
		if (!playerTerritories || playerTerritories.Count() == 0)
			return false;
		int i;
		int territoryID;
		obfc_TerritoryCacheData cacheData;
		float distSq;
		float territorySizeSq;
		for (i = 0; i < playerTerritories.Count(); i++)
		{
			territoryID = playerTerritories.Get(i);
			cacheData = obfm_GetCachedTerritoryData(territoryID);
			if (!cacheData)
				continue;
			distSq = vector.DistanceSq(cacheData.Position, playerPos);
			territorySizeSq = cacheData.obfv_TerritorySize * cacheData.obfv_TerritorySize;
			if (distSq <= territorySizeSq)
			{
				return true;
			}
		}
		return false;
	}
	#endif
}