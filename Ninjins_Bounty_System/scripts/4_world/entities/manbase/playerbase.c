modded class PlayerBase
{
	bool netSync_HasBounty = false;
	float netSync_BountyRemainingDuration = 0.0; 
	float obfv_m_BountyExpireTime = 0.0; 
	float obfv_m_BountyRemainingDuration = 0.0; 
	float obfv_m_BountyStartTime = 0.0; 
	float obfv_m_BountyOriginalDuration = 0.0; 
	BountyType obfv_m_BountyType = BountyType.PLACED; 
	BountyEndReason obfv_m_BountyEndReason = BountyEndReason.EXPIRED; 
	float obfv_m_BountyCooldownRemaining = 0.0; 
	bool netSync_BountyIsAdmin = false; 
	int obfv_m_PendingSuccessRewardCount = 0; 
	bool obfv_m_BountyPaused = false;
#ifndef NinjinsPvPPvE
	// Fallback declarations: NinjinsPvPPvE declares these members on PlayerBase itself;
	// redeclaring them while that mod is loaded is a compile error.
	bool netSync_IsInSafeZone = false;
	bool netSync_IsSZOnExit = false;
#endif
	bool netSync_BountyPaused = false;
	void PlayerBase()
	{
		netSync_HasBounty = false;
		netSync_BountyRemainingDuration = 0.0;
		obfv_m_BountyExpireTime = 0.0;
		obfv_m_BountyRemainingDuration = 0.0;
		obfv_m_BountyType = BountyType.PLACED;
		obfv_m_BountyEndReason = BountyEndReason.EXPIRED;
		obfv_m_BountyCooldownRemaining = 0.0;
		netSync_BountyIsAdmin = false;
		obfv_m_PendingSuccessRewardCount = 0;
		obfv_m_BountyPaused = false;
		netSync_BountyPaused = false;
		netSync_IsInSafeZone = false;
		netSync_IsSZOnExit = false;
	}
	override void SetActions(out TInputActionMap InputActionMap) {
		super.SetActions(InputActionMap);
		AddAction(obfc_ActionOpenBountyMenu, InputActionMap);
	}    
	bool obfm_IsBountyAdmin()
	{
		return netSync_BountyIsAdmin;
	}
	void obfm_SetBountyAdminStatus(bool isAdmin)
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
	bool obfm_HasBounty()
	{
		if (!IsMissionHost())
			return netSync_HasBounty;
		if (netSync_HasBounty && obfv_m_BountyRemainingDuration > 0.0)
		{
			return true;
		}
		else if (netSync_HasBounty && obfv_m_BountyRemainingDuration <= 0.0)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] HasBounty - Bounty expired! Remaining duration: " + obfv_m_BountyRemainingDuration.ToString() + "s");
			obfm_ClearBounty(false, BountyEndReason.EXPIRED);
			return false;
		}
		return netSync_HasBounty;
	}
	bool obfm_IsRuleBreakerBounty()
	{
		return obfv_m_BountyType == BountyType.RULE_BREAKER;
	}
	BountyType obfm_GetBountyType()
	{
		return obfv_m_BountyType;
	}
	BountyEndReason obfm_GetBountyEndReason()
	{
		return obfv_m_BountyEndReason;
	}
	float obfm_GetBountyRemainingDuration()
	{
		return obfv_m_BountyRemainingDuration;
	}
	void obfm_UpdateBountyDurationBeforeDeath()
	{
		float currentTime;
		float calculatedRemainingDuration;
		if (!IsMissionHost())
			return;
		if (netSync_HasBounty && obfv_m_BountyRemainingDuration > 0.0)
		{
			currentTime = g_Game.GetTime(); 
			if (obfv_m_BountyExpireTime > 0.0 && obfv_m_BountyExpireTime > currentTime)
			{
				calculatedRemainingDuration = (obfv_m_BountyExpireTime - currentTime) / obfv_BOUNTY_MS_TO_SECONDS; 
				if (calculatedRemainingDuration > 0.0)
				{
					obfv_m_BountyRemainingDuration = calculatedRemainingDuration;
					if (netSync_BountyRemainingDuration != obfv_m_BountyRemainingDuration)
					{
						netSync_BountyRemainingDuration = obfv_m_BountyRemainingDuration;
						SetSynchDirty();
					}
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Updated remaining duration to " + obfv_m_BountyRemainingDuration.ToString() + "s (from expireTime: " + obfv_m_BountyExpireTime.ToString() + "ms, currentTime: " + currentTime.ToString() + "ms, difference: " + (obfv_m_BountyExpireTime - currentTime).ToString() + "ms)");
				}
				else
				{
					obfv_m_BountyRemainingDuration = 0.0;
					netSync_BountyRemainingDuration = 0.0;
					obfv_m_BountyExpireTime = 0.0;
					SetSynchDirty();
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Bounty has expired");
				}
			}
			else if (obfv_m_BountyExpireTime > 0.0 && obfv_m_BountyExpireTime <= currentTime)
			{
				obfv_m_BountyRemainingDuration = 0.0;
				netSync_BountyRemainingDuration = 0.0;
				obfv_m_BountyExpireTime = 0.0;
				SetSynchDirty();
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] UpdateBountyDurationBeforeDeath: Bounty expired (expireTime in past)");
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty] UpdateBountyDurationBeforeDeath: ExpireTime not available, using m_BountyRemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s");
			}
		}
	}
	void obfm_UpdateBountyDuration(float deltaTime)
	{
		float currentTime;
		float oldDuration;
		PlayerIdentity identity;
		if (!IsMissionHost())
			return;
		if (!IsAlive())
			return;
		if (netSync_HasBounty && obfv_m_BountyRemainingDuration > 0.0)
		{
			currentTime = g_Game.GetTime();
			if (obfv_m_BountyPaused)
			{
				obfv_m_BountyExpireTime = currentTime + (obfv_m_BountyRemainingDuration * obfv_BOUNTY_MS_TO_SECONDS);
				return;
			}
			oldDuration = obfv_m_BountyRemainingDuration;
			obfv_m_BountyRemainingDuration = obfv_m_BountyRemainingDuration - deltaTime;
			if (netSync_BountyRemainingDuration != obfv_m_BountyRemainingDuration)
			{
				netSync_BountyRemainingDuration = obfv_m_BountyRemainingDuration;
				SetSynchDirty();
			}
			obfv_m_BountyExpireTime = currentTime + (obfv_m_BountyRemainingDuration * obfv_BOUNTY_MS_TO_SECONDS);
			if (obfv_m_BountyRemainingDuration <= 0.0)
			{
				obfv_m_BountyRemainingDuration = 0.0;
				netSync_BountyRemainingDuration = 0.0; 
				obfv_m_BountyExpireTime = 0.0;
				SetSynchDirty();
				identity = GetIdentity();
				if (identity)
				{
					Param1<float> paramCountdown = new Param1<float>(0.0);
					GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
				}
				obfm_ClearBounty(false, BountyEndReason.EXPIRED);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bounty duration expired for player.");
			}
		}
	}
	bool obfm_IsBountyOnCooldown()
	{
		if (!IsMissionHost())
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || obfv_g_BountyConfig.Core.BountyCooldownSeconds <= 0.0)
		{
			if (obfv_m_BountyCooldownRemaining > 0.0)
				obfv_m_BountyCooldownRemaining = 0.0;
			return false;
		}
		if (obfv_m_BountyCooldownRemaining <= 0.0)
		{
			return false;
		}
		return true;
	}
	float obfm_GetBountyCooldownRemaining()
	{
		if (!IsMissionHost())
			return 0.0;
		return obfv_m_BountyCooldownRemaining;
	}
	void obfm_ClearBountyCooldown()
	{
		if (!IsMissionHost())
			return;
		obfv_m_BountyCooldownRemaining = 0.0;
		PlayerIdentity cooldownIdentity = GetIdentity();
		if (cooldownIdentity)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cooldown cleared for player: " + cooldownIdentity.GetName());
		}
	}
	void obfm_UpdateBountyCooldown(float deltaTime)
	{
		if (!IsMissionHost())
			return;
		if (obfv_m_BountyCooldownRemaining > 0.0)
		{
			obfv_m_BountyCooldownRemaining = obfv_m_BountyCooldownRemaining - deltaTime;
			if (obfv_m_BountyCooldownRemaining <= 0.0)
			{
				obfv_m_BountyCooldownRemaining = 0.0;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cooldown expired for player.");
			}
		}
	}
	void obfm_SetBounty(float durationSeconds, bool isRuleBreaker = false, bool skipNotifications = false)
	{
		BountyType bountyType = BountyType.PLACED;
		if (isRuleBreaker)
			bountyType = BountyType.RULE_BREAKER;
		obfm_SetBountyWithType(durationSeconds, bountyType, skipNotifications);
	}
	void obfm_SetBountyWithType(float durationSeconds, BountyType bountyType = BountyType.PLACED, bool skipNotifications = false, int clearedRewardCount = 0, bool ignoreMaxBountiedLimit = false)
	{
		bool alreadyHasBounty;
		obfc_BountyManager bountyManager;
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
		if (!obfc_BountyConfig.obfm_IsSystemActive())
			return;
		alreadyHasBounty = obfm_HasBounty();
		if (obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.MaxBountiedPlayers == 0)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cannot set bounty - bounties are disabled (MaxBountiedPlayers = 0)");
			return;
		}
		else if (obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.MaxBountiedPlayers > 0 && bountyType != BountyType.RULE_BREAKER && !ignoreMaxBountiedLimit)
		{
			bountyManager = obfc_BountyManager.GetInstance();
			currentBountiedCount = bountyManager.obfm_GetBountiedPlayerCount();
			if (!alreadyHasBounty && currentBountiedCount >= obfv_g_BountyConfig.Core.MaxBountiedPlayers)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cannot set bounty - maximum bountied players limit reached (" + currentBountiedCount.ToString() + "/" + obfv_g_BountyConfig.Core.MaxBountiedPlayers.ToString() + ")");
				return;
			}
		}
		currentTime = g_Game.GetTime(); 
		currentTimeSeconds = currentTime / obfv_BOUNTY_MS_TO_SECONDS; 
		if (obfv_m_BountyRemainingDuration > 0.0)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player already has active bounty with remaining duration: " + obfv_m_BountyRemainingDuration.ToString() + "s - preserving it instead of resetting to " + durationSeconds.ToString() + "s");
			obfv_m_BountyStartTime = currentTimeSeconds;
			obfv_m_BountyOriginalDuration = obfv_m_BountyRemainingDuration; 
		}
		else
		{
			obfv_m_BountyRemainingDuration = durationSeconds; 
			obfv_m_BountyStartTime = currentTimeSeconds; 
			obfv_m_BountyOriginalDuration = durationSeconds; 
		}
		netSync_BountyRemainingDuration = obfv_m_BountyRemainingDuration; 
		obfv_m_BountyExpireTime = currentTime + (obfv_m_BountyRemainingDuration * 1000.0); 
		SetSynchDirty();
		obfv_m_BountyType = bountyType; 
		identity = GetIdentity();
		playerName = "Unknown";
		if (identity)
			playerName = identity.GetName();
		configRewardStr = "null";
		if (obfv_g_BountyConfig)
		{
			configRewardStr = "false";
			if (obfv_g_BountyConfig.Reward && obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
				configRewardStr = "true";
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] SetBounty - Player: " + playerName + ", BountyType: " + obfv_m_BountyType.ToString() + ", PvERuleBreakerGiveRewards: " + configRewardStr);
		if (obfv_m_BountyType == BountyType.RULE_BREAKER)
		{
			obfv_m_BountyCooldownRemaining = 0.0; 
		}
		else if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.BountyCooldownSeconds > 0.0)
		{
			obfv_m_BountyCooldownRemaining = obfv_g_BountyConfig.Core.BountyCooldownSeconds;
		}
		else
		{
			obfv_m_BountyCooldownRemaining = 0.0;
		}
		netSync_HasBounty = true;
		SetSynchDirty();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] SetBounty - CurrentTime: " + currentTime.ToString() + "ms, Duration: " + durationSeconds.ToString() + "s, ExpireTime: " + obfv_m_BountyExpireTime.ToString() + "ms");
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
				if (obfv_m_BountyType == BountyType.RULE_BREAKER)
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED, identity, "", "", durationSeconds, clearedRewardCount);
				}
				else
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_HUNTED, identity, "", "", durationSeconds);
				}
				if (!alreadyHasBounty)
				{
					if (obfv_m_BountyType == BountyType.RULE_BREAKER)
					{
						obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST, null, playerName, "", durationSeconds);
					}
					else
					{
						obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_BROADCAST, null, playerName, "", durationSeconds);
					}
				}
			}
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfOwnTerritory)
		{
			inOwnTerritory = false;
			territorySize = -1.0;
			flagPos = "0 0 0";
			#ifdef EXPANSIONMODBASEBUILDING
			territoryModule = CF_ModuleCoreManager.Get(ExpansionTerritoryModule);
			if (territoryModule && identity)
			{
				playerPos = GetPosition();
				playerUID = identity.GetId();
				territorySize = obfv_BOUNTY_DEFAULT_TERRITORY_SIZE; 
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
				inOwnTerritory = obfm_IsPlayerInOwnTerritory();
			}
			pauseBountyInTerritoryStr = "false";
			if (obfv_g_BountyConfig.Core.PauseBountyInTerritory)
				pauseBountyInTerritoryStr = "true";
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Territory check - Player " + playerName + " in own territory: " + inOwnTerritory.ToString() + ", PauseBountyInTerritory: " + pauseBountyInTerritoryStr);
			if (inOwnTerritory)
			{
				if (obfv_g_BountyConfig.Core.PauseBountyInTerritory)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " is in own territory when bounty was placed - pausing bounty timer...");
					obfm_PauseBounty();
					if (identity)
					{
						obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY, identity);
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " is in own territory when bounty was placed - teleporting out...");
					obfm_TeleportOutOfOwnTerritory(territorySize, flagPos);
				}
			}
		}
		else
		{
			configStatus = "null";
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core)
				configStatus = obfv_g_BountyConfig.Core.obfm_TeleportOutOfOwnTerritory.ToString();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Territory check - Player " + playerName + " - TeleportOutOfOwnTerritory config: " + configStatus);
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.PauseBountyInSafeZone)
		{
			if (obfm_NinjinBountyIsPlayerInSafezone())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " is in a safezone when bounty was placed - pausing bounty timer...");
				obfm_PauseBounty();
				if (identity)
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_SAFEZONE, identity);
				}
			}
		}
		else if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone)
		{
			if (obfm_NinjinBountyIsPlayerInSafezone())
			{
				isNinjinsSafeZone = false;
				ninjinsState = false;
				if (EnScript.GetClassVar(this, "netSync_IsInSafeZone", 0, ninjinsState))
				{
					isNinjinsSafeZone = ninjinsState;
				}
				if (isNinjinsSafeZone)
				{
					if (obfm_NinjinBountyIsOnSafeZoneExitTimer())
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " is in NinjinsPvPPvE safezone when bounty was placed but has active exit timer (netSync_IsSZOnExit = true) - skipping teleport");
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " is in safezone when bounty was placed - teleporting out...");
						obfm_TeleportOutOfSafeZone();
					}
				}
			}
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " has been marked with a bounty for " + durationSeconds.ToString() + " seconds.");
	}
	void obfm_ClearBounty(bool skipRewards = false, BountyEndReason endReason = BountyEndReason.CLEARED)
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
		obfv_m_BountyExpireTime = 0.0;
		obfv_m_BountyRemainingDuration = 0.0;
		obfv_m_BountyStartTime = 0.0;
		obfv_m_BountyOriginalDuration = 0.0;
		SetSynchDirty();
		identity = GetIdentity();
		playerName = "Unknown";
		playerSurvived = IsAlive(); 
		wasBountyType = obfv_m_BountyType;
		obfv_m_BountyEndReason = endReason;
		obfv_m_BountyType = BountyType.PLACED;
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
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " was a rule breaker - sending rule breaker expiration notification. EndReason: " + endReason.ToString());
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED, identity);
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " was NOT a rule breaker - sending regular expiration notification. EndReason: " + endReason.ToString());
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_EXPIRED, identity);
			}
			shouldGiveReward = true;
			if (skipRewards)
			{
				shouldGiveReward = false;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " skipped bounty - skipping success reward (survival type)");
			}
			else if (wasBountyType == BountyType.RULE_BREAKER && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
			{
				shouldGiveReward = false;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " was a rule breaker - skipping success reward (survival type) (PvERuleBreakerGiveRewards = false)");
			}
			if (playerSurvived && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && obfv_g_BountyConfig.Reward.EnableSurvivalReward)
			{
				if (shouldGiveReward)
				{
					obfm_AddPendingSuccessReward(1);
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, wasBountyType, true);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " survived bounty - set pending success reward (survival type) (must claim at bounty board).");
				}
				else
				{
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, wasBountyType, false);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " survived rule breaker bounty - no reward given.");
				}
			}
		}
		if (endReason == BountyEndReason.EXPIRED)
		{
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_EXPIRED_BROADCAST, null, playerName);
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bounty cleared for player " + playerName + ".");
	}
	//! Keeps the bounty alive across a death that must not count as a win (suicide, friendly fire).
	//! Freezes the remaining duration and hands it to the manager so it is restored on respawn.
	void obfm_PreserveBountyThroughDeath(string reasonLabel)
	{
		PlayerIdentity victimIdentity;
		string victimName;
		string playerId;
		float currentTime;
		float actualRemainingDuration;
		float calculatedFromExpireTime;
		obfc_BountyManager bountyManager;
		if (!IsMissionHost())
			return;
		victimIdentity = GetIdentity();
		victimName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
		playerId = "";
		if (victimIdentity)
		{
			victimName = victimIdentity.GetName();
			playerId = victimIdentity.GetId();
		}
		currentTime = g_Game.GetTime();
		actualRemainingDuration = obfv_m_BountyRemainingDuration;
		if (obfv_m_BountyExpireTime > 0.0 && obfv_m_BountyExpireTime > currentTime)
		{
			calculatedFromExpireTime = (obfv_m_BountyExpireTime - currentTime) / obfv_BOUNTY_MS_TO_SECONDS;
			if (calculatedFromExpireTime > 0.0)
			{
				actualRemainingDuration = calculatedFromExpireTime;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Calculated remaining duration from expireTime: " + actualRemainingDuration.ToString() + "s (expireTime: " + obfv_m_BountyExpireTime.ToString() + "ms, currentTime: " + currentTime.ToString() + "ms, m_BountyRemainingDuration was: " + obfv_m_BountyRemainingDuration.ToString() + "s)");
			}
		}
		if (actualRemainingDuration < 0.0)
			actualRemainingDuration = 0.0;
		obfv_m_BountyRemainingDuration = actualRemainingDuration;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + victimName + " died (" + reasonLabel + ") while having a bounty. Bounty timer preserved - will resume on respawn. RemainingDuration: " + actualRemainingDuration.ToString() + "s");
		if (actualRemainingDuration > 0.0)
		{
			netSync_HasBounty = true;
			SetSynchDirty();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Ensured netSync_HasBounty=true before death to preserve bounty state for CF ModStorage");
		}
		if (playerId != "" && actualRemainingDuration > 0.0)
		{
			bountyManager = obfc_BountyManager.GetInstance();
			if (bountyManager)
			{
				bountyManager.obfm_PreserveBountyForPlayer(playerId, actualRemainingDuration, obfv_m_BountyType, obfv_m_BountyStartTime, obfv_m_BountyOriginalDuration);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Preserved bounty in BountyManager - RemainingDuration: " + actualRemainingDuration.ToString() + "s, StartTime: " + obfv_m_BountyStartTime.ToString() + "s, OriginalDuration: " + obfv_m_BountyOriginalDuration.ToString() + "s");
			}
		}
	}
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		obfm_UpdateBountyDurationBeforeDeath();
		PlayerIdentity victimIdentity;
		PlayerIdentity killerIdentity;
		string victimName;
		string killerName;
		PlayerBase killerPlayer;
		bool shouldGiveReward;
		bool isSuicide;
		if (!IsMissionHost())
			return;
		if (!obfm_HasBounty())
			return;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Core.EnableBountySystem)
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
		victimIdentity = GetIdentity();
		victimName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
		if (victimIdentity)
			victimName = victimIdentity.GetName();
		if (isSuicide)
		{
			//! DontCountSuicide = true keeps the bounty running, so no "bounty has ended" broadcast here.
			if (obfv_g_BountyConfig.Core.DontCountSuicide)
			{
				obfm_PreserveBountyThroughDeath("suicide");
				return;
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + victimName + " died without a player killer and DontCountSuicide is disabled - ending bounty without reward.");
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_SUICIDE_BROADCAST, null, victimName);
			obfm_ClearBounty(true, BountyEndReason.SUICIDE);
			return;
		}
		if (obfv_g_BountyConfig.Core.DontCountFriendlyFire && obfm_NinjinBountyIsFriendlyKiller(killerPlayer))
		{
			killerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
			killerIdentity = killerPlayer.GetIdentity();
			if (killerIdentity)
				killerName = killerIdentity.GetName();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bountied player " + victimName + " was killed by group member " + killerName + " - no reward given and bounty continues (DontCountFriendlyFire = true).");
			obfm_PreserveBountyThroughDeath("friendly fire");
			return;
		}
		if (killerPlayer && killerPlayer != this && killerPlayer.GetIdentity())
		{
			victimIdentity = GetIdentity();
			killerIdentity = killerPlayer.GetIdentity();
			victimName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
			killerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
			if (victimIdentity)
				victimName = victimIdentity.GetName();
			if (killerIdentity)
				killerName = killerIdentity.GetName();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bountied player " + victimName + " was killed by " + killerName + ".");
			shouldGiveReward = true;
			if (killerPlayer.obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
			{
				shouldGiveReward = false;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Killer " + killerName + " is a rule breaker - skipping success reward (kill type) (PvERuleBreakerGiveRewards = false)");
			}
			else if (obfv_m_BountyType == BountyType.RULE_BREAKER && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
			{
				shouldGiveReward = false;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Victim " + victimName + " was a rule breaker - skipping success reward (kill type) for " + killerName + " (PvERuleBreakerGiveRewards = false)");
			}
			if (shouldGiveReward)
			{
				killerPlayer.obfm_AddPendingSuccessReward(1);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Set pending success reward (kill type) for " + killerName + " (must claim at bounty board)");
			}
			if (killerIdentity)
			{
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD, killerIdentity, "", victimName, 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, obfv_m_BountyType, shouldGiveReward);
			}
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_WIN_BROADCAST, null, victimName, "", 0.0, 0, 0, 0, 0, 0, 0, "", "", 0.0, obfv_m_BountyType, true, killerName);
		}
		obfm_ClearBounty(false, BountyEndReason.KILLED);
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
						string playerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
						if (identity)
						{
							playerName = identity.GetName();
						}
						if (IsMissionHost())
						{
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Bounty state changed for " + playerName + ": " + netSync_HasBounty);
						}
						else
						{
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty][Client] Bounty state changed: " + netSync_HasBounty);
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
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty][Client] Admin status synced from server: " + netSync_BountyIsAdmin.ToString());
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
		CF_ModStorage ctx = storage["Ninjins_Bounty_System"];
		if (!ctx)
			return;
		//! PersistentBountyAfterLogOut = false: keep the save format intact but drop the bounty itself,
		//! so it neither survives the logout nor a server restart. Cooldown/pending rewards still persist.
		bool saveHasBounty = netSync_HasBounty;
		float saveRemainingDuration = obfv_m_BountyRemainingDuration;
		BountyType saveBountyType = obfv_m_BountyType;
		float saveStartTime = obfv_m_BountyStartTime;
		float saveOriginalDuration = obfv_m_BountyOriginalDuration;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && !obfv_g_BountyConfig.Core.PersistentBountyAfterLogOut)
		{
			saveHasBounty = false;
			saveRemainingDuration = 0.0;
			saveBountyType = BountyType.PLACED;
			saveStartTime = 0.0;
			saveOriginalDuration = 0.0;
			if (netSync_HasBounty)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] PersistentBountyAfterLogOut is disabled - bounty is not written to CF ModStorage");
			}
		}
		ctx.Write(saveHasBounty);
		ctx.Write(saveRemainingDuration);
		ctx.Write(saveBountyType);
		ctx.Write(saveStartTime);
		ctx.Write(saveOriginalDuration);
		ctx.Write(obfv_m_BountyCooldownRemaining);
		ctx.Write(obfv_m_PendingSuccessRewardCount);
		// Second int slot kept for save-format compatibility (loader sums both slots);
		// writing the count twice would double it on every save/load cycle.
		int pendingRewardPadding = 0;
		ctx.Write(pendingRewardPadding);
		string bountyTypeStr = obfv_BOUNTY_TYPE_STRING_PLACED;
		if (saveBountyType == BountyType.RULE_BREAKER)
			bountyTypeStr = obfv_BOUNTY_TYPE_STRING_RULE_BREAKER;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Saved player data (CF ModStorage) - HasBounty: " + saveHasBounty.ToString() + ", BountyRemainingDuration: " + saveRemainingDuration.ToString() + "s, BountyType: " + bountyTypeStr + ", BountyCooldownRemaining: " + obfv_m_BountyCooldownRemaining.ToString() + "s, PendingSuccessRewardCount: " + obfv_m_PendingSuccessRewardCount.ToString());
	}
	override bool CF_OnStoreLoad(CF_ModStorageMap storage)
	{
		if (!super.CF_OnStoreLoad(storage))
			return false;
		if (!IsMissionHost())
			return true;
		PlayerIdentity identity = GetIdentity();
		string playerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
		if (identity)
			playerName = identity.GetName();
		CF_ModStorage ctx = storage["Ninjins_Bounty_System"];
		if (!ctx)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - No CF ModStorage context found for " + playerName + " - player has no saved bounty data");
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
				obfv_m_BountyRemainingDuration = 0.0;
				obfv_m_BountyExpireTime = 0.0;
				obfv_m_BountyType = BountyType.PLACED;
				obfv_m_BountyStartTime = 0.0;
				obfv_m_BountyOriginalDuration = 0.0;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Failed to read bounty state from CF ModStorage for " + playerName + " - initialized to false");
				return false;
			}
		}
		string savedBountyTypeStr = obfv_BOUNTY_TYPE_STRING_PLACED;
		if (savedBountyType == BountyType.RULE_BREAKER)
			savedBountyTypeStr = obfv_BOUNTY_TYPE_STRING_RULE_BREAKER;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() for " + playerName + " - savedHasBounty: " + savedHasBounty.ToString() + ", savedBountyRemainingDuration: " + savedBountyRemainingDuration.ToString() + "s, savedBountyType: " + savedBountyTypeStr + ", savedBountyStartTime: " + savedBountyStartTime.ToString() + "s, savedBountyOriginalDuration: " + savedBountyOriginalDuration.ToString() + "s");
		if (savedHasBounty && savedBountyRemainingDuration > 0.0)
		{
			netSync_HasBounty = true;
			obfv_m_BountyType = savedBountyType;
			bool appearsStale = false;
			if (savedBountyOriginalDuration > obfv_BOUNTY_SECONDS_PER_DAY && savedBountyStartTime > 0.0) 
			{
				float difference = savedBountyOriginalDuration - savedBountyRemainingDuration;
				float percentUsed = (difference / savedBountyOriginalDuration) * 100.0;
				if (percentUsed < obfv_BOUNTY_STALE_DURATION_THRESHOLD_PERCENT) 
				{
					appearsStale = true;
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[Bounty] CF_OnStoreLoad() - Saved remaining duration appears stale (only " + percentUsed.ToString() + "% used), recalculating from start time");
				}
			}
			if (appearsStale && savedBountyOriginalDuration > 86400.0 && savedBountyStartTime > 0.0)
			{
				float currentTimeSeconds = g_Game.GetTime() / obfv_BOUNTY_MS_TO_SECONDS; 
				float elapsedTime = currentTimeSeconds - savedBountyStartTime;
				float recalculatedRemaining = savedBountyOriginalDuration - elapsedTime;
				if (recalculatedRemaining > 0.0)
				{
					obfv_m_BountyRemainingDuration = recalculatedRemaining;
					obfv_m_BountyStartTime = savedBountyStartTime; 
					obfv_m_BountyOriginalDuration = savedBountyOriginalDuration; 
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Recalculated remaining duration for large bounty (stale detection): " + obfv_m_BountyRemainingDuration.ToString() + "s (original saved: " + savedBountyRemainingDuration.ToString() + "s, elapsed: " + elapsedTime.ToString() + "s)");
				}
				else
				{
					obfv_m_BountyRemainingDuration = 0.0;
					obfv_m_BountyStartTime = 0.0;
					obfv_m_BountyOriginalDuration = 0.0;
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Large bounty expired during downtime (elapsed: " + elapsedTime.ToString() + "s > original: " + savedBountyOriginalDuration.ToString() + "s)");
				}
			}
			else
			{
				obfv_m_BountyRemainingDuration = savedBountyRemainingDuration;
				obfv_m_BountyStartTime = savedBountyStartTime;
				if (savedBountyOriginalDuration > 0.0)
					obfv_m_BountyOriginalDuration = savedBountyOriginalDuration;
				else
					obfv_m_BountyOriginalDuration = savedBountyRemainingDuration;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Using saved remaining duration (timer paused while offline): " + obfv_m_BountyRemainingDuration.ToString() + "s");
			}
			float currentTime = g_Game.GetTime();
			obfv_m_BountyExpireTime = currentTime + (obfv_m_BountyRemainingDuration * obfv_BOUNTY_MS_TO_SECONDS);
			SetSynchDirty();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Restored bounty state for " + playerName + " - RemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s, BountyType: " + savedBountyTypeStr);
		}
		else if (savedHasBounty && savedBountyRemainingDuration <= 0.0)
		{
			netSync_HasBounty = false;
			obfv_m_BountyRemainingDuration = 0.0;
			obfv_m_BountyExpireTime = 0.0;
			obfv_m_BountyType = BountyType.PLACED;
			obfv_m_BountyEndReason = BountyEndReason.EXPIRED;
			obfv_m_BountyStartTime = 0.0;
			obfv_m_BountyOriginalDuration = 0.0;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - Bounty expired during downtime for " + playerName + " - cleared");
		}
		else
		{
			netSync_HasBounty = false;
			obfv_m_BountyRemainingDuration = 0.0;
			obfv_m_BountyExpireTime = 0.0;
			obfv_m_BountyType = BountyType.PLACED;
			obfv_m_BountyStartTime = 0.0;
			obfv_m_BountyOriginalDuration = 0.0;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CF_OnStoreLoad() - No saved bounty for " + playerName + " - initialized to false");
		}
		if (!ctx.Read(obfv_m_BountyCooldownRemaining))
		{
			obfv_m_BountyCooldownRemaining = 0.0;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] No saved BountyCooldownRemaining found - initialized to 0");
		}
		else
		{
			if (obfv_m_BountyCooldownRemaining < 0.0)
				obfv_m_BountyCooldownRemaining = 0.0;
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.BountyCooldownSeconds <= 0.0)
			{
				obfv_m_BountyCooldownRemaining = 0.0;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cooldown disabled in config - reset BountyCooldownRemaining");
			}
			else if (obfv_m_BountyCooldownRemaining > 0.0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Loaded player data - BountyCooldownRemaining: " + obfv_m_BountyCooldownRemaining.ToString() + "s (cooldown will continue)");
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
				obfv_m_PendingSuccessRewardCount = combinedCount;
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Loaded pending rewards (old boolean format) - Combined into unified count: " + obfv_m_PendingSuccessRewardCount.ToString());
			}
			else
			{
				obfv_m_PendingSuccessRewardCount = 0;
			}
		}
		else
		{
			if (savedPendingSuccessRewardKillCount < 0)
				savedPendingSuccessRewardKillCount = 0;
			if (savedPendingSuccessRewardSurvivalCount < 0)
				savedPendingSuccessRewardSurvivalCount = 0;
			obfv_m_PendingSuccessRewardCount = savedPendingSuccessRewardKillCount + savedPendingSuccessRewardSurvivalCount;
			if (obfv_m_PendingSuccessRewardCount > 0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Loaded pending rewards (old format, combined) - SuccessRewardCount: " + obfv_m_PendingSuccessRewardCount.ToString() + " (was: kill=" + savedPendingSuccessRewardKillCount.ToString() + ", survival=" + savedPendingSuccessRewardSurvivalCount.ToString() + ")");
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
		string playerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
		string playerId = "";
		if (identity)
		{
			playerName = identity.GetName();
			playerId = identity.GetId();
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] OnConnect() called for " + playerName + " - netSync_HasBounty: " + netSync_HasBounty.ToString() + ", m_BountyRemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s");
		if (obfv_m_BountyRemainingDuration <= 0.0 && playerId != "")
		{
			obfc_BountyManager bountyManager = obfc_BountyManager.GetInstance();
			if (bountyManager)
			{
				obfc_BountyPreservedData preservedData = bountyManager.obfm_GetPreservedBountyForPlayer(playerId);
				if (preservedData && preservedData.obfv_RemainingDuration > 0.0)
				{
					obfv_m_BountyRemainingDuration = preservedData.obfv_RemainingDuration;
					obfv_m_BountyType = preservedData.obfv_Type;
					obfv_m_BountyStartTime = preservedData.obfv_StartTime;
					obfv_m_BountyOriginalDuration = preservedData.obfv_OriginalDuration;
					if (preservedData.obfv_OriginalDuration > 86400.0 && preservedData.obfv_StartTime > 0.0)
					{
						float currentTimeSeconds = g_Game.GetTime() / 1000.0;
						float elapsedTime = currentTimeSeconds - preservedData.obfv_StartTime;
						float recalculatedRemaining = preservedData.obfv_OriginalDuration - elapsedTime;
						if (recalculatedRemaining > 0.0)
						{
							obfv_m_BountyRemainingDuration = recalculatedRemaining;
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Recalculated remaining duration from preserved timestamp: " + obfv_m_BountyRemainingDuration.ToString() + "s (original preserved: " + preservedData.obfv_RemainingDuration.ToString() + "s, elapsed: " + elapsedTime.ToString() + "s)");
						}
					}
					netSync_HasBounty = true;
					SetSynchDirty();
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Restored bounty from BountyManager preserved data for " + playerName + " - RemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s, BountyType: " + obfv_m_BountyType.ToString() + ", StartTime: " + obfv_m_BountyStartTime.ToString() + "s, OriginalDuration: " + obfv_m_BountyOriginalDuration.ToString() + "s");
				}
			}
		}
		if (obfv_m_BountyRemainingDuration > 0.0)
		{
			netSync_HasBounty = true;
			float currentTime = g_Game.GetTime();
			obfv_m_BountyExpireTime = currentTime + (obfv_m_BountyRemainingDuration * obfv_BOUNTY_MS_TO_SECONDS);
			SetSynchDirty();
			Param1<bool> paramBounty = new Param1<bool>(true);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "UpdateBountyState", paramBounty, true, identity);
			Param1<float> paramCountdown = new Param1<float>(obfv_m_BountyRemainingDuration);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_PERSISTED, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", obfv_m_BountyRemainingDuration);
			string bountyTypeStr = "PLACED";
			if (obfv_m_BountyType == BountyType.RULE_BREAKER)
				bountyTypeStr = "RULE_BREAKER";
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Restored bounty on respawn for " + playerName + " - RemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s, BountyType: " + bountyTypeStr);
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] OnConnect() - No bounty to restore for " + playerName + " (m_BountyRemainingDuration: " + obfv_m_BountyRemainingDuration.ToString() + "s)");
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.UI && identity)
		{
			float posX = obfv_g_BountyConfig.UI.CountdownWidgetPositionX;
			float posY = obfv_g_BountyConfig.UI.CountdownWidgetPositionY;
			float width = obfv_g_BountyConfig.UI.CountdownWidgetWidth;
			float height = obfv_g_BountyConfig.UI.CountdownWidgetHeight;
			int bgColor = obfv_g_BountyConfig.UI.CountdownWidgetBackgroundColor;
			int textColor = obfv_g_BountyConfig.UI.CountdownWidgetTextColor;
			obfc_BountyUISettingsData uiData = new obfc_BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
			Param1<obfc_BountyUISettingsData> uiParam = new Param1<obfc_BountyUISettingsData>(uiData);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, identity);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Sent UI settings to client on connect: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
		}
	}
	bool obfm_HasPendingRewards()
	{
		return obfv_m_PendingSuccessRewardCount > 0;
	}
	int obfm_GetPendingSuccessRewardCount()
	{
		return obfv_m_PendingSuccessRewardCount;
	}
	int obfm_GetTotalPendingRewardCount()
	{
		return obfv_m_PendingSuccessRewardCount;
	}
	void obfm_AddPendingSuccessReward(int amount = 1)
	{
		if (!IsMissionHost())
			return;
		if (amount < 0)
			amount = 0;
		obfv_m_PendingSuccessRewardCount = obfv_m_PendingSuccessRewardCount + amount;
		SetSynchDirty();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Added pending success reward: " + amount.ToString() + " (total: " + obfv_m_PendingSuccessRewardCount.ToString() + ")");
	}
	void obfm_RemovePendingSuccessReward(int amount = 1)
	{
		if (!IsMissionHost())
			return;
		if (amount < 0)
			amount = 0;
		if (obfv_m_PendingSuccessRewardCount >= amount)
		{
			obfv_m_PendingSuccessRewardCount = obfv_m_PendingSuccessRewardCount - amount;
		}
		else
		{
			obfv_m_PendingSuccessRewardCount = 0;
		}
		SetSynchDirty();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Removed pending success reward: " + amount.ToString() + " (remaining: " + obfv_m_PendingSuccessRewardCount.ToString() + ")");
	}
	void obfm_ClaimPendingSuccessReward()
	{
		if (!IsMissionHost())
			return;
		if (obfv_m_PendingSuccessRewardCount > 0)
		{
			obfv_m_PendingSuccessRewardCount = obfv_m_PendingSuccessRewardCount - 1;
			SetSynchDirty();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Claimed 1 success reward (remaining: " + obfv_m_PendingSuccessRewardCount.ToString() + ")");
		}
	}
	void obfm_ClearPendingRewards()
	{
		if (!IsMissionHost())
			return;
		if (obfm_HasBounty() && obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Prevented clearing pending rewards - player has rule breaker bounty and PvERuleBreakerGiveRewards is enabled");
			return;
		}
		obfv_m_PendingSuccessRewardCount = 0;
		SetSynchDirty();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Cleared all pending rewards");
	}
	bool obfm_IsPlayerInOwnTerritory()
	{
		if (obfm_NinjinsBountyRearmedIsInOwnTerritory(this))
		{
			return true;
		}
		if (obfm_NinjinsBountyBasicTerritoriesIsInOwnTerritory(this))
		{
			return true;
		}
		return false;
	}
	void obfm_PauseBounty()
	{
		PlayerIdentity identity;
		if (!IsMissionHost())
			return;
		if (!netSync_HasBounty)
			return;
		obfv_m_BountyPaused = true;
		netSync_BountyPaused = true;
		SetSynchDirty();
		identity = GetIdentity();
		if (identity)
		{
			Param1<bool> paramPaused = new Param1<bool>(true);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdatePaused", paramPaused, true, identity);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Paused bounty timer for player " + identity.GetName());
		}
	}
	bool obfm_IsFarEnoughFromTerritory()
	{
		float requiredDistance;
		vector playerPos;
		string playerUID;
		obfc_BountyManager bountyManager;
		array<int> playerTerritoryIDs;
		float territorySize;
		obfc_TerritoryCacheData firstTerritory;
		float minDistanceRequired;
		float minDistanceRequiredSq;
		int i;
		int territoryID;
		obfc_TerritoryCacheData cacheData;
		float distSq;
		PlayerIdentity farIdentity;
		if (!IsMissionHost())
			return false;
		if (!netSync_HasBounty)
			return false;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core)
			return false;
		farIdentity = GetIdentity();
		if (!farIdentity)
			return false;
		requiredDistance = obfv_g_BountyConfig.Core.ResumeBountyDistanceFromTerritory;
		if (requiredDistance <= 0.0)
			requiredDistance = obfv_BOUNTY_DEFAULT_TELEPORT_DISTANCE;
		playerPos = GetPosition();
		playerUID = farIdentity.GetId();
		#ifdef EXPANSIONMODBASEBUILDING
		bountyManager = obfc_BountyManager.GetInstance();
		if (bountyManager)
		{
			playerTerritoryIDs = bountyManager.obfm_GetCachedPlayerTerritories(playerUID);
			if (playerTerritoryIDs && playerTerritoryIDs.Count() > 0)
			{
				territorySize = 150.0; 
				if (playerTerritoryIDs.Count() > 0)
				{
					firstTerritory = bountyManager.obfm_GetCachedTerritoryData(playerTerritoryIDs.Get(0));
					if (firstTerritory)
					{
						territorySize = firstTerritory.obfv_TerritorySize;
					}
				}
				minDistanceRequired = territorySize + requiredDistance; 
				minDistanceRequiredSq = minDistanceRequired * minDistanceRequired;
				for (i = 0; i < playerTerritoryIDs.Count(); i++)
				{
					territoryID = playerTerritoryIDs.Get(i);
					cacheData = bountyManager.obfm_GetCachedTerritoryData(territoryID);
					if (!cacheData)
						continue;
					distSq = vector.DistanceSq(cacheData.Position, playerPos);
					if (distSq <= minDistanceRequiredSq)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + farIdentity.GetName() + " is too close to territory (distance: " + Math.Sqrt(distSq).ToString() + "m, required: " + minDistanceRequired.ToString() + "m)");
						return false;
					}
				}
			}
		}
		#endif
		if (obfm_IsPlayerInOwnTerritory())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + farIdentity.GetName() + " is still in their own territory (non-Expansion)");
			return false;
		}
		if (!obfc_BountyConfig.obfm_IsFarEnoughFromStaticTerritories(playerPos, playerUID, farIdentity.GetPlainId(), requiredDistance))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + farIdentity.GetName() + " is too close to one of their static territory zones (required: " + requiredDistance.ToString() + "m beyond edge)");
			return false;
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] IsFarEnoughFromTerritory - Player " + farIdentity.GetName() + " is far enough from all territories (required: " + requiredDistance.ToString() + "m beyond edge)");
		return true;
	}
	void obfm_ResumeBounty()
	{
		PlayerIdentity identity;
		if (!IsMissionHost())
			return;
		if (!netSync_HasBounty)
			return;
		if (!obfv_m_BountyPaused)
			return;
		identity = GetIdentity();
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.PauseBountyInSafeZone)
		{
			if (obfm_NinjinBountyIsPlayerInSafezone())
			{
				if (identity)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] ResumeBounty - Player " + identity.GetName() + " is still in a safezone, not resuming yet");
				}
				return;
			}
		}
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.obfm_TeleportOutOfOwnTerritory)
		{
			if (!obfm_IsFarEnoughFromTerritory())
			{
				if (identity)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] ResumeBounty - Player " + identity.GetName() + " is not far enough from territory, not resuming yet");
				}
				return;
			}
		}
		obfv_m_BountyPaused = false;
		netSync_BountyPaused = false;
		SetSynchDirty();
		if (identity)
		{
			Param1<bool> paramPaused = new Param1<bool>(false);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdatePaused", paramPaused, true, identity);
			Param1<float> paramCountdown = new Param1<float>(obfv_m_BountyRemainingDuration);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyUpdateCountdown", paramCountdown, true, identity);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Resumed bounty timer for player " + identity.GetName() + " (remaining: " + obfv_m_BountyRemainingDuration.ToString() + "s)");
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_PERSISTED, identity, "", "", 0.0, 0, 0, 0, 0, 0, 0, "", "", obfv_m_BountyRemainingDuration);
		}
	}
	bool obfm_IsBountyPaused()
	{
		return obfv_m_BountyPaused;
	}
	void obfm_TeleportOutOfOwnTerritory(float territorySize = -1.0, vector flagPosition = "0 0 0")
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
		int obfv_radius;
		int angle;
		float radians;
		vector testPos;
		vector groundPos;
		bool isOutsideTerritory;
		float randomAngle;
		float distance;
		if (!IsMissionHost())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Not server, skipping");
			return;
		}
		identity = GetIdentity();
		playerName = "Unknown";
		if (identity)
			playerName = identity.GetName();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Starting teleport for player " + playerName);
		currentPos = GetPosition();
		teleportPos = currentPos;
		if (territorySize > 0)
			effectiveTerritorySize = territorySize;
		else
			effectiveTerritorySize = GameConstants.REFRESHER_RADIUS;
		teleportDistance = effectiveTerritorySize + obfv_BOUNTY_DEFAULT_TELEPORT_DISTANCE; 
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Current position: " + currentPos.ToString() + ", Territory size: " + effectiveTerritorySize.ToString() + ", Teleport distance: " + teleportDistance.ToString());
		if (flagPosition != "0 0 0")
		{
			direction = currentPos - flagPosition;
			direction[1] = 0; 
			direction.Normalize();
			teleportPos = flagPosition + (direction * teleportDistance);
			groundY = g_Game.SurfaceY(teleportPos[0], teleportPos[2]);
			teleportPos[1] = groundY + 0.5;
		}
		else
		{
			foundSafePos = false;
			for (obfv_radius = obfv_BOUNTY_TELEPORT_SEARCH_MIN_RADIUS; obfv_radius <= obfv_BOUNTY_TELEPORT_SEARCH_MAX_RADIUS; obfv_radius += obfv_BOUNTY_TELEPORT_SEARCH_RADIUS_STEP)
			{
				for (angle = 0; angle < obfv_BOUNTY_DEGREES_IN_CIRCLE; angle += obfv_BOUNTY_TELEPORT_SEARCH_ANGLE_STEP)
				{
					radians = angle * Math.DEG2RAD;
					testPos = currentPos;
					testPos[0] = testPos[0] + (Math.Cos(radians) * obfv_radius);
					testPos[2] = testPos[2] + (Math.Sin(radians) * obfv_radius);
					groundY = g_Game.SurfaceY(testPos[0], testPos[2]);
					groundPos = Vector(testPos[0], groundY + obfv_BOUNTY_GROUND_OFFSET, testPos[2]); 
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
				randomAngle = Math.RandomFloat(0, obfv_BOUNTY_DEGREES_IN_CIRCLE) * Math.DEG2RAD;
				distance = obfv_BOUNTY_FALLBACK_TELEPORT_DISTANCE;
				teleportPos = currentPos;
				teleportPos[0] = teleportPos[0] + (Math.Cos(randomAngle) * distance);
				teleportPos[2] = teleportPos[2] + (Math.Sin(randomAngle) * distance);
				groundY = g_Game.SurfaceY(teleportPos[0], teleportPos[2]);
				teleportPos[1] = groundY + obfv_BOUNTY_GROUND_OFFSET;
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
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Player " + playerName + " is in vehicle, teleporting vehicle from " + currentPos.ToString() + " to " + teleportPos.ToString());
					transport.SetPosition(teleportPos);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported vehicle (with player " + playerName + ") out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
					SetPosition(teleportPos);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
				SetPosition(teleportPos);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfOwnTerritory - Teleporting player " + playerName + " from " + currentPos.ToString() + " to " + teleportPos.ToString());
			SetPosition(teleportPos);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of their own territory. From: " + currentPos.ToString() + " To: " + teleportPos.ToString());
		}
		identity = GetIdentity();
		if (identity)
		{
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY, identity);
		}
	}
	void obfm_TeleportOutOfSafeZone()
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
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfSafeZone - Teleporting player " + playerName + " out of safezone");
		currentPos = GetPosition();
		teleportPos = currentPos;
		distance = obfv_BOUNTY_DEFAULT_TELEPORT_DISTANCE;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.TeleportOutOfSafeZoneDistance > 0.0)
		{
			distance = obfv_g_BountyConfig.Core.TeleportOutOfSafeZoneDistance;
		}
		direction = GetDirection();
		direction[1] = 0; 
		direction.Normalize();
		teleportPos = currentPos - (direction * distance);
		groundY = g_Game.SurfaceY(teleportPos[0], teleportPos[2]);
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
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] TeleportOutOfSafeZone - Player " + playerName + " is in vehicle, teleporting vehicle from " + currentPos.ToString() + " to " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
					transport.SetPosition(teleportPos);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported vehicle (with player " + playerName + ") out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
				}
				else
				{
					SetPosition(teleportPos);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
				}
			}
			else
			{
				SetPosition(teleportPos);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
			}
		}
		else
		{
			SetPosition(teleportPos);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Teleported player " + playerName + " out of safezone. From: " + currentPos.ToString() + " To: " + teleportPos.ToString() + " (distance: " + distance.ToString() + "m)");
		}
		if (g_Game && g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY))
		{
			g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.obfm_CheckSafeZoneAfterTeleport, obfv_BOUNTY_SAFEZONE_CHECK_DELAY_MS, false);
		}
	}
	void obfm_CheckSafeZoneAfterTeleport()
	{
		PlayerIdentity identity;
		string playerName;
		bool isInNinjinsSafeZone;
		if (!IsMissionHost())
			return;
		if (!obfm_HasBounty() || !IsAlive())
			return;
		identity = GetIdentity();
		playerName = "Unknown";
		if (identity)
			playerName = identity.GetName();
		isInNinjinsSafeZone = obfm_NinjinBountyIsPlayerInNinjinsSafeZone();
		if (!isInNinjinsSafeZone)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is no longer in NinjinsPvPPvE safezone (netSync_IsInSafeZone = false) - stopping checks");
			return;
		}
		if (obfm_NinjinBountyIsOnSafeZoneExitTimer())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is in NinjinsPvPPvE safezone with active exit timer (netSync_IsSZOnExit = true) - skipping teleport, will check again in 2 seconds");
			if (g_Game && g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY))
			{
				g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.obfm_CheckSafeZoneAfterTeleport, obfv_BOUNTY_SAFEZONE_CHECK_DELAY_MS, false);
			}
			return;
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] CheckSafeZoneAfterTeleport - Player " + playerName + " is in NinjinsPvPPvE safezone (netSync_IsInSafeZone = true) without exit timer (netSync_IsSZOnExit = false) - teleporting out...");
		obfm_TeleportOutOfSafeZone(); 
	}
	//! Rearmed and Basic Territories expose no script API. Both are covered through the
	//! StaticTerritoryZones list in BountyConfig.json (position + radius + owner GUIDs).
	static bool obfm_NinjinsBountyStaticIsInOwnTerritory(PlayerBase player)
	{
		PlayerIdentity identity;
		if (!player)
			return false;
		identity = player.GetIdentity();
		if (!identity)
			return false;
		return obfc_BountyConfig.obfm_IsPositionInOwnStaticTerritory(player.GetPosition(), identity.GetId(), identity.GetPlainId());
	}
	static bool obfm_NinjinsBountyRearmedIsInOwnTerritory(PlayerBase player)
	{
		return obfm_NinjinsBountyStaticIsInOwnTerritory(player);
	}
	static bool obfm_NinjinsBountyBasicTerritoriesIsInOwnTerritory(PlayerBase player)
	{
		return obfm_NinjinsBountyStaticIsInOwnTerritory(player);
	}
	static bool obfm_NinjinsBountyExpansionIsSameParty(PlayerBase attacker, PlayerBase victim)
	{
		if (!attacker || !victim)
			return false;
		#ifdef EXPANSIONMODGROUPS
		int attackerPartyID = attacker.Expansion_GetPartyID();
		int victimPartyID = victim.Expansion_GetPartyID();
		if (attackerPartyID != -1 && attackerPartyID == victimPartyID)
			return true;
		#endif
		return false;
	}
	static bool obfm_NinjinsBountyLBIsSameGroup(PlayerBase attacker, PlayerBase victim)
	{
		if (!attacker || !victim)
			return false;
		#ifdef LBmaster_Groups
		PlayerIdentity attackerIdentity = attacker.GetIdentity();
		PlayerIdentity victimIdentity = victim.GetIdentity();
		if (!attackerIdentity || !victimIdentity)
			return false;
		LBGroupManager groupManager = LBGroupManager.Get();
		if (!groupManager)
			return false;
		LBGroup attackerGroup = groupManager.GetPlayersGroup(attackerIdentity.GetPlainId());
		if (!attackerGroup)
			return false;
		LBGroup victimGroup = groupManager.GetPlayersGroup(victimIdentity.GetPlainId());
		if (!victimGroup)
			return false;
		if (attackerGroup.shortname == "")
			return false;
		if (attackerGroup.shortname == victimGroup.shortname)
			return true;
		#endif
		return false;
	}
	//! True when the killer is a group/party mate of this player (Expansion parties, LB Advanced Groups).
	bool obfm_NinjinBountyIsFriendlyKiller(PlayerBase killer)
	{
		if (!killer || killer == this)
			return false;
		if (obfm_NinjinsBountyExpansionIsSameParty(killer, this))
			return true;
		if (obfm_NinjinsBountyLBIsSameGroup(killer, this))
			return true;
		return false;
	}
	static bool obfm_NinjinsBountyExpansionIsInSafezone(PlayerBase player)
	{
		if (!player)
			return false;
		bool result = false;
		EnScript.GetClassVar(player, "m_Expansion_IsInSafeZone", 0, result);
		return result;
	}
	bool obfm_NinjinBountyIsPlayerInNinjinsSafeZone()
	{
		return netSync_IsInSafeZone;
	}
	bool obfm_NinjinBountyIsOnSafeZoneExitTimer()
	{
		return netSync_IsSZOnExit;
	}
	bool obfm_NinjinBountyIsPlayerInSafezone()
	{
		if (obfm_NinjinBountyIsPlayerInNinjinsSafeZone())
		{
			return true;
		}
		if (obfm_NinjinsBountyExpansionIsInSafezone(this))
		{
			return true;
		}
		//! Dr Jones Trader / TraderPlus / Rearmed are covered via StaticSafeZones in BountyConfig.json.
		if (obfc_BountyConfig.obfm_IsPositionInStaticSafeZone(GetPosition()))
		{
			return true;
		}
		return false;
	}
}