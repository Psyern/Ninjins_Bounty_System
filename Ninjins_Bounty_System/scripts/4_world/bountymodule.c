[CF_RegisterModule(obfc_BountyModule)]
class obfc_BountyModule : CF_ModuleWorld
{
	static obfc_BountyModule obfv_s_Instance;
	ref obfc_BountyManager obfv_m_BountyManager;
	ref obfc_BountyAdminConfig obfv_m_BountyAdminConfig;
	ref obfc_BountyBlacklistConfig obfv_m_BountyBlacklistConfig;
	ref obfc_BountyBoardPlacementConfig obfv_m_BountyBoardPlacementConfig;
	ref array<Object> obfv_m_ConfigSpawnedBountyBoards;
	override void OnInit()
	{
		super.OnInit();
		obfv_s_Instance = this;
		obfv_m_ConfigSpawnedBountyBoards = new array<Object>();
		EnableInvokeConnect();
		EnableUpdate();
		EnableMissionStart();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Module initialized");
	}
	static obfc_BountyModule GetInstance()
	{
		return obfv_s_Instance;
	}
	override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);
		if (!IsMissionHost())
			return;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Ninjins_Bounty_System mod has started !");
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("Ninjins_Bounty_System mod has started!");
		obfm_InitBountyAdminConfig();
		obfm_InitBountyBlacklistConfig();
		obfv_g_BountyConfig = obfc_BountyConfig.obfm_LoadConfig();
		if (obfv_g_BountyConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountyConfig loaded. EnableBountySystem: " + obfv_g_BountyConfig.Core.EnableBountySystem.ToString() + ", Duration: " + obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds.ToString() + " seconds");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("Failed to load BountyConfig!");
		}
		obfv_g_BountySuccessRewardConfig = obfc_BountySuccessRewardConfig.obfm_LoadConfig();
		if (obfv_g_BountySuccessRewardConfig)
		{
			int sectionCount = 0;
			if (obfv_g_BountySuccessRewardConfig.BountyRewardItems)
				sectionCount = obfv_g_BountySuccessRewardConfig.BountyRewardItems.Count();
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("BountySuccessRewardConfig loaded. RewardSections: " + sectionCount.ToString());
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("Failed to load BountySuccessRewardConfig!");
		}
		obfv_g_BountyZoneConfig = obfc_BountyZoneConfig.obfm_LoadConfig();
		if (!obfv_g_BountyZoneConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("Failed to load BountyZoneConfig!");
		}
		obfm_InitBountyBoardPlacementConfig();
		obfm_SpawnConfiguredBountyBoards();
		obfv_m_BountyManager = obfc_BountyManager.GetInstance();
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminAction", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminUpdateConfig", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestConfig", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BoardBountyAction", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestPlayers", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyRequestClaimAmount", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyRequestPricing", this, SingleplayerExecutionType.Server);
		GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestBlacklist", this, SingleplayerExecutionType.Server);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Registered all RPC handlers");
	}
	void obfm_InitBountyAdminConfig()
	{
		obfv_m_BountyAdminConfig = obfc_BountyAdminConfig.obfm_LoadConfig();
		obfv_g_BountyAdminConfig = obfv_m_BountyAdminConfig;
		if (!obfv_m_BountyAdminConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[ERROR] Failed to load BountyAdminConfig.");
		}
	}
	void obfm_InitBountyBlacklistConfig()
	{
		obfv_m_BountyBlacklistConfig = obfc_BountyBlacklistConfig.obfm_LoadConfig();
		obfv_g_BountyBlacklistConfig = obfv_m_BountyBlacklistConfig;
		if (!obfv_m_BountyBlacklistConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[ERROR] Failed to load BountyBlacklistConfig.");
		}
	}
	void obfm_InitBountyBoardPlacementConfig()
	{
		obfv_m_BountyBoardPlacementConfig = obfc_BountyBoardPlacementConfig.obfm_LoadConfig();
		obfv_g_BountyBoardPlacementConfig = obfv_m_BountyBoardPlacementConfig;
		if (!obfv_m_BountyBoardPlacementConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[ERROR] Failed to load BountyBoardPlacementConfig.");
		}
	}
	vector obfm_BuildBoardVector(array<float> values)
	{
		string vectorString = "0 0 0";
		if (values && values.Count() >= 3)
		{
			vectorString = values.Get(0).ToString() + " " + values.Get(1).ToString() + " " + values.Get(2).ToString();
		}
			return vectorString.ToVector();
	}
	bool obfm_IsPlaceholderBoardPlacement(obfc_BountyBoardPlacement placement)
	{
		if (!placement || !placement.Position || placement.Position.Count() < 3)
			return true;
		return placement.Position.Get(0) == 0.0 && placement.Position.Get(1) == 0.0 && placement.Position.Get(2) == 0.0;
	}
	void obfm_ClearConfiguredBountyBoards()
	{
		int i;
		Object boardObject;
		if (!obfv_m_ConfigSpawnedBountyBoards)
			return;
		for (i = obfv_m_ConfigSpawnedBountyBoards.Count() - 1; i >= 0; i--)
		{
			boardObject = obfv_m_ConfigSpawnedBountyBoards.Get(i);
			if (boardObject)
			{
				g_Game.ObjectDelete(boardObject);
			}
			obfv_m_ConfigSpawnedBountyBoards.Remove(i);
		}
	}
	void obfm_SpawnConfiguredBountyBoards()
	{
		int i;
		obfc_BountyBoardPlacement placement;
		vector boardPosition;
		vector boardRotation;
		Object boardObject;
		if (!IsMissionHost())
			return;
		if (!obfv_m_ConfigSpawnedBountyBoards)
		{
			obfv_m_ConfigSpawnedBountyBoards = new array<Object>();
		}
		obfm_ClearConfiguredBountyBoards();
		if (!obfv_g_BountyBoardPlacementConfig || !obfv_g_BountyBoardPlacementConfig.BoardPlacements)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] No board placement config loaded - skipping configured board spawn.");
			return;
		}
		for (i = 0; i < obfv_g_BountyBoardPlacementConfig.BoardPlacements.Count(); i++)
		{
			placement = obfv_g_BountyBoardPlacementConfig.BoardPlacements.Get(i);
			if (!placement)
				continue;
			if (obfm_IsPlaceholderBoardPlacement(placement))
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Skipping placeholder board placement entry at index " + i.ToString());
				continue;
			}
			boardPosition = obfm_BuildBoardVector(placement.Position);
			boardRotation = obfm_BuildBoardVector(placement.Rotation);
			boardObject = g_Game.CreateObjectEx("Ninjins_Bounty_Board_Static", boardPosition, ECE_PLACE_ON_SURFACE);
			if (!boardObject)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[BountyModule] Failed to spawn configured bounty board at index " + i.ToString());
				continue;
			}
			boardObject.SetOrientation(boardRotation);
			obfv_m_ConfigSpawnedBountyBoards.Insert(boardObject);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Spawned configured bounty board #" + i.ToString() + " at " + boardPosition.ToString() + " with rotation " + boardRotation.ToString());
		}
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Configured bounty board spawn complete. Spawned: " + obfv_m_ConfigSpawnedBountyBoards.Count().ToString());
	}
	string obfm_BuildPlayerListEntry(string displayName, string playerId)
	{
		return displayName + "||" + playerId;
	}
	PlayerBase obfm_FindOnlinePlayerByIdentifier(string identifier)
	{
		array<Man> players = new array<Man>();
		g_Game.GetPlayers(players);
		int i;
		Man man;
		PlayerBase playerBase;
		PlayerIdentity identity;
		for (i = 0; i < players.Count(); i++)
		{
			man = players.Get(i);
			if (!man || !man.IsAlive())
				continue;
			playerBase = PlayerBase.Cast(man);
			if (!playerBase)
				continue;
			identity = playerBase.GetIdentity();
			if (!identity)
				continue;
			if (identity.GetId() == identifier || identity.GetPlainId() == identifier || identity.GetName() == identifier)
				return playerBase;
		}
		return null;
	}
	int obfm_GetPlayerTokenCount(PlayerBase player, out array<ItemBase> foundTokens)
	{
		array<string> tokenClassNames;
		GameInventory inventory;
		array<EntityAI> allInventoryItems;
		ItemBase item;
		string itemClassName;
		int i;
		int j;
		int totalTokenQuantity;
		bool alreadyAdded;
		float itemQuantity;
		foundTokens = new array<ItemBase>;
		if (!player)
			return 0;
		totalTokenQuantity = 0;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.BountyTokenClassNames)
		{
			tokenClassNames = obfv_g_BountyConfig.Core.BountyTokenClassNames;
		}
		else
		{
			tokenClassNames = new array<string>;
			tokenClassNames.Insert("Ninjins_Bounty_Token_Gold");
			tokenClassNames.Insert("Ninjins_Bounty_Token_Red");
			tokenClassNames.Insert("Ninjins_Bounty_Token_Silver");
		}
		inventory = player.GetInventory();
		if (!inventory)
			return 0;
		allInventoryItems = new array<EntityAI>;
		inventory.EnumerateInventory(InventoryTraversalType.PREORDER, allInventoryItems);
		for (i = 0; i < allInventoryItems.Count(); i++)
		{
			item = ItemBase.Cast(allInventoryItems.Get(i));
			if (!item)
				continue;
			itemClassName = item.GetType();
			for (j = 0; j < tokenClassNames.Count(); j++)
			{
				if (itemClassName == tokenClassNames.Get(j))
				{
					alreadyAdded = false;
					for (int existingIndex = 0; existingIndex < foundTokens.Count(); existingIndex++)
					{
						if (foundTokens.Get(existingIndex) == item)
						{
							alreadyAdded = true;
							break;
						}
					}
					if (!alreadyAdded)
					{
						foundTokens.Insert(item);
						itemQuantity = item.GetQuantity();
						if (itemQuantity < 1.0)
							itemQuantity = 1.0;
						totalTokenQuantity = totalTokenQuantity + Math.Round(itemQuantity);
					}
					break;
				}
			}
		}
		return totalTokenQuantity;
	}
	bool obfm_ConsumePlayerTokens(PlayerBase player, int tokensRequired, out int tokensRemoved)
	{
		array<ItemBase> foundTokens;
		ItemBase item;
		int j;
		float itemQuantity;
		int stackQuantity;
		int neededFromStack;
		tokensRemoved = 0;
		if (tokensRequired <= 0)
			return true;
		if (obfm_GetPlayerTokenCount(player, foundTokens) < tokensRequired)
			return false;
		for (j = 0; j < foundTokens.Count() && tokensRemoved < tokensRequired; j++)
		{
			item = foundTokens.Get(j);
			if (!item)
				continue;
			itemQuantity = item.GetQuantity();
			if (itemQuantity < 1.0)
				itemQuantity = 1.0;
			stackQuantity = Math.Round(itemQuantity);
			neededFromStack = tokensRequired - tokensRemoved;
			if (neededFromStack > stackQuantity)
				neededFromStack = stackQuantity;
			if (neededFromStack >= stackQuantity)
			{
				g_Game.ObjectDelete(item);
				tokensRemoved = tokensRemoved + stackQuantity;
			}
			else
			{
				item.AddQuantity(-neededFromStack);
				tokensRemoved = tokensRemoved + neededFromStack;
			}
		}
		return tokensRemoved >= tokensRequired;
	}
	override void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		super.OnInvokeConnect(sender, args);
		if (!IsMissionHost())
			return;
		CF_EventPlayerArgs playerArgs;
		PlayerBase player;
		PlayerIdentity identity;
		int i;
		string entry;
		int colonIndex;
		bool updated;
		string playerGUID;
		string playerName;
		bool isAdmin;
		string newEntry;
		playerArgs = CF_EventPlayerArgs.Cast(args);
		if (!playerArgs || !playerArgs.Player)
			return;
		player = PlayerBase.Cast(playerArgs.Player);
		if (!player)
			return;
		identity = player.GetIdentity();
		if (!identity)
			return;
		if (!obfv_m_BountyAdminConfig)
		{
			obfm_InitBountyAdminConfig();
		}
		if (!obfv_m_BountyBlacklistConfig)
		{
			obfm_InitBountyBlacklistConfig();
		}
		playerGUID = identity.GetId();
		playerName = identity.GetName();
		if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.BlacklistedGUIDs)
		{
			updated = false;
			for (i = 0; i < obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Count(); i++)
			{
				entry = obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
				colonIndex = entry.IndexOf(":");
				if (colonIndex < 0)
				{
					if (entry == playerGUID)
					{
						newEntry = playerName + ":" + playerGUID;
						obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Set(i, newEntry);
						updated = true;
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyBlacklist] Updated blacklist entry from old format to new format: " + entry + " -> " + newEntry);
					}
				}
			}
			if (updated)
			{
				obfv_g_BountyBlacklistConfig.obfm_SaveConfig();
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyBlacklist] Saved blacklist config after updating format for player: " + playerName);
			}
		}
		isAdmin = false;
		if (obfv_m_BountyAdminConfig && obfv_m_BountyAdminConfig.obfm_IsAdminIdentity(identity))
		{
			isAdmin = true;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdmin] Player " + identity.GetName() + " (GUID: " + playerGUID + " | SteamID64: " + identity.GetPlainId() + ") is a bounty system admin.");
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdmin] Player " + identity.GetName() + " (GUID: " + playerGUID + " | SteamID64: " + identity.GetPlainId() + ") is NOT a bounty system admin. Admins.json accepts either value.");
			if (obfv_m_BountyAdminConfig && obfv_m_BountyAdminConfig.AdminGUIDs)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdmin] AdminGUIDs in config: " + obfv_m_BountyAdminConfig.AdminGUIDs.Count().ToString());
				for (i = 0; i < obfv_m_BountyAdminConfig.AdminGUIDs.Count(); i++)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdmin] Config GUID " + i.ToString() + ": " + obfv_m_BountyAdminConfig.AdminGUIDs.Get(i));
				}
			}
		}
		player.obfm_SetBountyAdminStatus(isAdmin);
		Param1<bool> adminParam = new Param1<bool>(isAdmin);
		g_Game.RPCSingleParam(player, BountyRPC.SYNC_ADMIN_STATUS, adminParam, true, identity);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdmin] Sent admin status RPC to client: " + isAdmin.ToString());
		if (player.obfm_HasBounty())
		{
			Param1<bool> paramBounty = new Param1<bool>(true);
			g_Game.RPCSingleParam(player, BountyRPC.UPDATE_BOUNTY_STATE, paramBounty, true, identity);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Restored bounty state on connect for " + identity.GetName());
		}
	}
	override void OnUpdate(Class sender, CF_EventArgs args)
	{
		super.OnUpdate(sender, args);
		if (!IsMissionHost())
			return;
		CF_EventUpdateArgs updateArgs = CF_EventUpdateArgs.Cast(args);
		if (!updateArgs)
			return;
		if (obfv_m_BountyManager)
		{
			obfv_m_BountyManager.Update(updateArgs.DeltaTime);
		}
	}
	void RequestBountiedPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		array<ref obfc_BountyPlayerData> bountiedPlayersData;
		array<Man> players;
		int i;
		Man man;
		PlayerBase player;
		PlayerIdentity identity;
		obfc_BountyPlayerData playerData;
		float currentTime;
		float minMult;
		float maxMult;
		float temp;
		PlayerBase requestingPlayer;
		float posX;
		float posY;
		float width;
		float height;
		int bgColor;
		int textColor;
		obfc_BountyUISettingsData uiData;
		Param1<obfc_BountyUISettingsData> uiParam;
		Param1<array<ref obfc_BountyPlayerData>> data;
		if (type != CallType.Server || !sender)
			return;
		if (!obfc_BountyConfig.obfm_IsSystemActive())
			return;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Map || !obfv_g_BountyConfig.Map.BountyEnableMapDrawing)
			return;
		bountiedPlayersData = new array<ref obfc_BountyPlayerData>();
		players = new array<Man>();
		g_Game.GetPlayers(players);
		for (i = 0; i < players.Count(); i++)
		{
			man = players.Get(i);
			player = PlayerBase.Cast(man);
			if (player && player.obfm_HasBounty() && player.IsAlive())
			{
				identity = player.GetIdentity();
				if (!identity)
					continue;
				playerData = new obfc_BountyPlayerData();
				playerData.obfv_PlayerID = identity.GetId();
				playerData.obfv_PlayerName = identity.GetName();
				playerData.Position = player.GetPosition();
				currentTime = g_Game.GetTime();
				if (player.obfv_m_BountyExpireTime > 0.0)
				{
					playerData.obfv_TimeRemaining = (player.obfv_m_BountyExpireTime - currentTime) / 1000.0;
					if (playerData.obfv_TimeRemaining < 0.0)
						playerData.obfv_TimeRemaining = 0.0;
				}
				else
				{
					playerData.obfv_TimeRemaining = 0.0;
				}
				if (obfv_g_BountyConfig)
				{
					playerData.obfv_CircleRadius = obfv_g_BountyConfig.Map.BountyCircleRadius;
					playerData.obfv_CircleColor = obfv_g_BountyConfig.Map.BountyCircleColor;
					playerData.obfv_ReduceRadiusOverTime = obfv_g_BountyConfig.Map.BountyCircleReduceRadiusOverTime;
					playerData.obfv_IncreaseRadiusOverTime = obfv_g_BountyConfig.Map.BountyCircleIncreaseRadiusOverTime;
					playerData.obfv_CircleMinRadius = obfv_g_BountyConfig.Map.BountyCircleMinRadius;
					if (player.obfm_IsRuleBreakerBounty())
					{
						playerData.BountyDurationSeconds = obfv_g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
					}
					else
					{
						playerData.BountyDurationSeconds = obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds;
					}
					playerData.obfv_CircleOffsetMinMultiplier = obfv_g_BountyConfig.Map.BountyCircleOffsetMinMultiplier;
					playerData.obfv_CircleOffsetMaxMultiplier = obfv_g_BountyConfig.Map.BountyCircleOffsetMaxMultiplier;
					minMult = playerData.obfv_CircleOffsetMinMultiplier;
					maxMult = playerData.obfv_CircleOffsetMaxMultiplier;
					if (minMult > maxMult)
					{
						temp = minMult;
						minMult = maxMult;
						maxMult = temp;
					}
					if (minMult < 0.0) minMult = 0.0;
					if (maxMult > 1.0) maxMult = 1.0;
					if (minMult > 1.0) minMult = 1.0;
					if (maxMult < 0.0) maxMult = 0.0;
					if (maxMult > 0.0)
					{
						playerData.obfv_CachedOffsetMultiplier = Math.RandomFloat(minMult, maxMult);
						playerData.obfv_CachedOffsetAngle = Math.RandomFloat(0.0, Math.PI2);
					}
					else
					{
						playerData.obfv_CachedOffsetMultiplier = 0.0;
						playerData.obfv_CachedOffsetAngle = 0.0;
					}
				}
				bountiedPlayersData.Insert(playerData);
			}
		}
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (requestingPlayer)
		{
			data = new Param1<array<ref obfc_BountyPlayerData>>(bountiedPlayersData);
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "ReceiveBountiedPlayers", data, true, sender);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[MissionServer] Sent " + bountiedPlayersData.Count().ToString() + " bountied players to " + sender.GetName());
			if (obfv_g_BountyConfig && obfv_g_BountyConfig.UI)
			{
				posX = obfv_g_BountyConfig.UI.CountdownWidgetPositionX;
				posY = obfv_g_BountyConfig.UI.CountdownWidgetPositionY;
				width = obfv_g_BountyConfig.UI.CountdownWidgetWidth;
				height = obfv_g_BountyConfig.UI.CountdownWidgetHeight;
				bgColor = obfv_g_BountyConfig.UI.CountdownWidgetBackgroundColor;
				textColor = obfv_g_BountyConfig.UI.CountdownWidgetTextColor;
				uiData = new obfc_BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
				uiParam = new Param1<obfc_BountyUISettingsData>(uiData);
				GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, sender);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent UI settings to client: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
			}
		}
	}
	void BountyAdminAction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if (type != CallType.Server || !sender)
			return;
		Param1<string> actionParam;
		string action;
		PlayerBase player;
		if (!ctx.Read(actionParam))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminAction: Failed to read action parameter.");
			return;
		}
		action = actionParam.param1;
		player = PlayerBase.Cast(sender.GetPlayer());
		if (!player)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminAction: Player not found for identity: " + sender.GetName());
			return;
		}
		if (!player.obfm_IsBountyAdmin())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminAction: Access denied for non-admin player: " + sender.GetName());
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
			return;
		}
		bool success;
		string targetPlayerName = "";
		PlayerBase targetPlayer = null;
		int i;
		Man man;
		PlayerBase playerBase;
		PlayerIdentity identity;
		string candidateName = "";
		PlayerBase candidatePlayer = null;
		PlayerIdentity candidateIdentity = null;
		array<Man> players;
		string entry = "";
		string existingEntry = "";
		Param1<array<string>> blacklistResult;
		string actualPlayerName = "";
		string guidToRemove = "";
		string playerGUID = "";
		string playerName = "";
		int cdIndex;
		int noCooldownIndex;
		int colonIndex;
		bool alreadyBlacklisted;
		bool removed;
		if (action.IndexOf("ApplyTestRuleBreakerBounty:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("ApplyTestRuleBreakerBounty:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer)
				{
					success = obfc_BountyManager.obfm_ApplyBountyToPlayer(targetPlayer, player, 0.0, "Admin test rule breaker bounty", BountyType.RULE_BREAKER);
					if (success)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Applied rule breaker bounty to " + targetPlayerName + " by admin " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Failed to apply rule breaker bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for ApplyTestRuleBreakerBounty");
			}
		}
		else if (action.IndexOf("AddBountySelectedPlayer:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("AddBountySelectedPlayer:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer)
				{
					success = obfc_BountyManager.obfm_ApplyBountyToPlayer(targetPlayer, player, 0.0, "Admin placed bounty", BountyType.PLACED);
					if (success)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Applied normal placed bounty to " + targetPlayerName + " by admin " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Failed to apply normal placed bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for AddBountySelectedPlayer");
			}
		}
		else if (action == "ClearBounty")
		{
			success = obfc_BountyManager.obfm_ClearBountyFromPlayer(player, player, "Admin cleared");
			if (success)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared bounty for " + sender.GetName());
			}
		}
		else if (action.IndexOf("ClearBountySelectedPlayer:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("ClearBountySelectedPlayer:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer)
				{
					success = obfc_BountyManager.obfm_ClearBountyFromPlayer(targetPlayer, player, "Admin cleared selected player");
					if (success)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared bounty for " + targetPlayerName + " by admin " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Failed to clear bounty for " + targetPlayerName + " (player may not have a bounty)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for ClearBountySelectedPlayer");
			}
		}
		else if (action == "ReloadConfigs")
		{
			obfc_BountyManager.obfm_ReloadAllConfigs(player);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Reloaded configs for " + sender.GetName());
		}
		else if (action.IndexOf("ClearAllCooldowns:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("ClearAllCooldowns:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer)
				{
					if (targetPlayer.obfm_IsBountyOnCooldown())
					{
						targetPlayer.obfm_ClearBountyCooldown();
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared cooldown for player " + targetPlayerName + " by admin " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Player " + targetPlayerName + " is not on cooldown (nothing to clear)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for ClearAllCooldowns");
			}
		}
		else if (action == "ClearAllCooldowns")
		{
			array<Man> allPlayers = new array<Man>();
			g_Game.GetPlayers(allPlayers);
			int clearedCount = 0;
			PlayerBase onlinePlayer;
			PlayerIdentity onlineIdentity;
			for (i = 0; i < allPlayers.Count(); i++)
			{
				man = allPlayers.Get(i);
				if (man && man.IsAlive())
				{
					onlinePlayer = PlayerBase.Cast(man);
					if (onlinePlayer && onlinePlayer.obfm_IsBountyOnCooldown())
					{
						onlinePlayer.obfm_ClearBountyCooldown();
						clearedCount = clearedCount + 1;
						onlineIdentity = onlinePlayer.GetIdentity();
						if (onlineIdentity)
						{
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared cooldown for online player: " + onlineIdentity.GetName());
						}
					}
				}
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared cooldowns for " + clearedCount.ToString() + " online player(s) by admin " + sender.GetName());
		}
		else if (action.IndexOf("ClearPlayerCooldown:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("ClearPlayerCooldown:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer)
				{
					if (targetPlayer.obfm_IsBountyOnCooldown())
					{
						targetPlayer.obfm_ClearBountyCooldown();
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Cleared cooldown for player " + targetPlayerName + " by admin " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Player " + targetPlayerName + " is not on cooldown (nothing to clear)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player not found: " + targetPlayerName);
				}
			}
		}
		else if (action.IndexOf("AddRewardPoint:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("AddRewardPoint:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer && targetPlayer.GetIdentity())
				{
					targetPlayer.obfm_AddPendingSuccessReward(1);
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Added reward point to " + targetPlayer.GetIdentity().GetName() + " by admin " + sender.GetName() + " (total pending: " + targetPlayer.obfm_GetTotalPendingRewardCount().ToString() + ")");
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for AddRewardPoint");
			}
		}
		else if (action.IndexOf("RemoveRewardPoint:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("RemoveRewardPoint:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer && targetPlayer.GetIdentity())
				{
					if (targetPlayer.obfm_HasPendingRewards())
					{
						targetPlayer.obfm_RemovePendingSuccessReward(1);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Removed success reward point from " + targetPlayer.GetIdentity().GetName() + " by admin " + sender.GetName() + " (remaining: " + targetPlayer.obfm_GetTotalPendingRewardCount().ToString() + ")");
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Player " + targetPlayer.GetIdentity().GetName() + " has no pending rewards to remove");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] No player name provided for RemoveRewardPoint");
			}
		}
		else if (action.IndexOf("AddToBlacklist:") == 0)
		{
			targetPlayerName = action;
			targetPlayerName.Replace("AddToBlacklist:", "");
			if (targetPlayerName != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerName);
				if (targetPlayer && targetPlayer.GetIdentity())
				{
					playerGUID = targetPlayer.GetIdentity().GetId();
					playerName = targetPlayer.GetIdentity().GetName();
					entry = playerName + ":" + playerGUID;
					alreadyBlacklisted = false;
					if (obfv_g_BountyBlacklistConfig)
					{
						alreadyBlacklisted = obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(targetPlayer.GetIdentity());
					}
					if (!alreadyBlacklisted)
					{
						obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Insert(entry);
						obfv_g_BountyBlacklistConfig.obfm_SaveConfig();
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Added " + playerName + " (" + playerGUID + ") to blacklist by admin " + sender.GetName());
						blacklistResult = new Param1<array<string>>(obfv_g_BountyBlacklistConfig.BlacklistedGUIDs);
						GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", blacklistResult, true, sender);
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player " + playerName + " is already blacklisted");
					}
				}
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Player not found: " + actualPlayerName);
			}
		}
		else if (action.IndexOf("RemoveFromBlacklist:") == 0)
		{
			entry = action;
			entry.Replace("RemoveFromBlacklist:", "");
			if (entry != "" && obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.BlacklistedGUIDs)
			{
				colonIndex = entry.IndexOf(":");
				guidToRemove = "";
				if (colonIndex >= 0 && colonIndex < entry.Length() - 1)
				{
					guidToRemove = entry.Substring(colonIndex + 1, entry.Length() - (colonIndex + 1));
				}
				else
				{
					guidToRemove = entry;
				}
				removed = false;
				for (i = obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Count() - 1; i >= 0; i--)
				{
					existingEntry = obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
					if (existingEntry.IndexOf(guidToRemove) >= 0)
					{
						obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Remove(i);
						removed = true;
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminAction] Removed " + existingEntry + " from blacklist by admin " + sender.GetName());
						break;
					}
				}
				if (removed)
				{
					obfv_g_BountyBlacklistConfig.obfm_SaveConfig();
					blacklistResult = new Param1<array<string>>(obfv_g_BountyBlacklistConfig.BlacklistedGUIDs);
					GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", blacklistResult, true, sender);
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminAction] Entry not found in blacklist: " + entry);
				}
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminAction: Unknown action: " + action);
		}
	}
	void BountyAdminUpdateConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<ref obfc_BountyConfig> configParam;
		obfc_BountyConfig updatedConfig;
		PlayerBase player;
		if (type != CallType.Server || !sender)
			return;
		if (!ctx.Read(configParam))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminUpdateConfig: Failed to read config parameter.");
			return;
		}
		updatedConfig = configParam.param1;
		if (!updatedConfig)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminUpdateConfig: Config parameter is null.");
			return;
		}
		player = PlayerBase.Cast(sender.GetPlayer());
		if (!player)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminUpdateConfig: Player not found for identity: " + sender.GetName());
			return;
		}
		if (!player.obfm_IsBountyAdmin())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminUpdateConfig: Access denied for non-admin player: " + sender.GetName());
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
			return;
		}
		if (obfv_g_BountyConfig)
		{
			if (updatedConfig.Core && obfv_g_BountyConfig.Core)
			{
				obfv_g_BountyConfig.Core.EnableBountySystem = updatedConfig.Core.EnableBountySystem;
				obfv_g_BountyConfig.Core.DisableSelfBounty = updatedConfig.Core.DisableSelfBounty;
				obfv_g_BountyConfig.Core.obfm_TeleportOutOfOwnTerritory = updatedConfig.Core.obfm_TeleportOutOfOwnTerritory;
				obfv_g_BountyConfig.Core.PauseBountyInTerritory = updatedConfig.Core.PauseBountyInTerritory;
				obfv_g_BountyConfig.Core.obfm_TeleportOutOfSafeZone = updatedConfig.Core.obfm_TeleportOutOfSafeZone;
				obfv_g_BountyConfig.Core.EnableAutomatedBountyPlacement = updatedConfig.Core.EnableAutomatedBountyPlacement;
				obfv_g_BountyConfig.Core.BountyCooldownSeconds = updatedConfig.Core.BountyCooldownSeconds;
				obfv_g_BountyConfig.Core.MaxBountiedPlayers = updatedConfig.Core.MaxBountiedPlayers;
				obfv_g_BountyConfig.Core.MinOnlinePlayersRequired = updatedConfig.Core.MinOnlinePlayersRequired;
				obfv_g_BountyConfig.Core.SkipBountyTokenRequired = updatedConfig.Core.SkipBountyTokenRequired;
				obfv_g_BountyConfig.Core.PlaceBountyTokenRequired = updatedConfig.Core.PlaceBountyTokenRequired;
				obfv_g_BountyConfig.Core.ResumeBountyDistanceFromTerritory = updatedConfig.Core.ResumeBountyDistanceFromTerritory;
				obfv_g_BountyConfig.Core.PausedBountyResumeCheckInterval = updatedConfig.Core.PausedBountyResumeCheckInterval;
				obfv_g_BountyConfig.Core.TeleportOutOfSafeZoneDistance = updatedConfig.Core.TeleportOutOfSafeZoneDistance;
				obfv_g_BountyConfig.Core.MinimumPlayerLifetimeSeconds = updatedConfig.Core.MinimumPlayerLifetimeSeconds;
				obfv_g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds = updatedConfig.Core.AutomatedBountyPlacementIntervalSeconds;
				//! Fields without an admin-menu widget are deliberately NOT merged from the client payload -
				//! the client would send constructor defaults and wipe them. They stay in the live config,
				//! get written back by SaveConfig() below and are re-read by ReloadAllConfigs().
			}
			if (updatedConfig.RuleBreaker && obfv_g_BountyConfig.RuleBreaker)
			{
				obfv_g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold = updatedConfig.RuleBreaker.EnableRuleBreakerHitThreshold;
				obfv_g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker = updatedConfig.RuleBreaker.EnablePvEToPvPRuleBreaker;
				obfv_g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = updatedConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty;
				obfv_g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill = updatedConfig.RuleBreaker.AllowPvEToPvEVictimKill;
				obfv_g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds = updatedConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
				obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime = updatedConfig.RuleBreaker.RuleBreakerHitThresholdTime;
				obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits = updatedConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits;
				obfv_g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits = updatedConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
				obfv_g_BountyConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits = updatedConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits;
				obfv_g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease = updatedConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease;
				obfv_g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = updatedConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount;
			}
			if (updatedConfig.PlacedBounty && obfv_g_BountyConfig.PlacedBounty)
			{
				obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds = updatedConfig.PlacedBounty.BountyDurationSeconds;
			}
			if (updatedConfig.Reward && obfv_g_BountyConfig.Reward)
			{
				obfv_g_BountyConfig.Reward.EnableSurvivalReward = updatedConfig.Reward.EnableSurvivalReward;
				obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards = updatedConfig.Reward.PvERuleBreakerGiveRewards;
			}
			if (updatedConfig.Map && obfv_g_BountyConfig.Map)
			{
				obfv_g_BountyConfig.Map.BountyEnableMapDrawing = updatedConfig.Map.BountyEnableMapDrawing;
				obfv_g_BountyConfig.Map.BountyCircleReduceRadiusOverTime = updatedConfig.Map.BountyCircleReduceRadiusOverTime;
				obfv_g_BountyConfig.Map.BountyCircleIncreaseRadiusOverTime = updatedConfig.Map.BountyCircleIncreaseRadiusOverTime;
				obfv_g_BountyConfig.Map.BountyCircleRadius = updatedConfig.Map.BountyCircleRadius;
				obfv_g_BountyConfig.Map.BountyCircleMinRadius = updatedConfig.Map.BountyCircleMinRadius;
				obfv_g_BountyConfig.Map.BountyCircleColor = updatedConfig.Map.BountyCircleColor;
				obfv_g_BountyConfig.Map.BountyCircleDrawingWidth = updatedConfig.Map.BountyCircleDrawingWidth;
				obfv_g_BountyConfig.Map.BountyMapUpdateIntervalSeconds = updatedConfig.Map.BountyMapUpdateIntervalSeconds;
				obfv_g_BountyConfig.Map.BountyMapRequestCooldownSeconds = updatedConfig.Map.BountyMapRequestCooldownSeconds;
				obfv_g_BountyConfig.Map.BountyMapSyncIntervalSeconds = updatedConfig.Map.BountyMapSyncIntervalSeconds;
				obfv_g_BountyConfig.Map.BountyMapSyncIntervalNoBountiesSeconds = updatedConfig.Map.BountyMapSyncIntervalNoBountiesSeconds;
				obfv_g_BountyConfig.Map.BountyCircleOffsetMinMultiplier = updatedConfig.Map.BountyCircleOffsetMinMultiplier;
				obfv_g_BountyConfig.Map.BountyCircleOffsetMaxMultiplier = updatedConfig.Map.BountyCircleOffsetMaxMultiplier;
			}
			if (updatedConfig.UI && obfv_g_BountyConfig.UI)
			{
				obfv_g_BountyConfig.UI.CountdownWidgetPositionX = updatedConfig.UI.CountdownWidgetPositionX;
				obfv_g_BountyConfig.UI.CountdownWidgetPositionY = updatedConfig.UI.CountdownWidgetPositionY;
				obfv_g_BountyConfig.UI.CountdownWidgetWidth = updatedConfig.UI.CountdownWidgetWidth;
				obfv_g_BountyConfig.UI.CountdownWidgetHeight = updatedConfig.UI.CountdownWidgetHeight;
				obfv_g_BountyConfig.UI.CountdownWidgetBackgroundColor = updatedConfig.UI.CountdownWidgetBackgroundColor;
				obfv_g_BountyConfig.UI.CountdownWidgetTextColor = updatedConfig.UI.CountdownWidgetTextColor;
			}
			if (updatedConfig.Notifications && obfv_g_BountyConfig.Notifications)
			{
				if (updatedConfig.Notifications.PlacedBounty && obfv_g_BountyConfig.Notifications.PlacedBounty)
				{
					if (updatedConfig.Notifications.PlacedBounty.Hunted && obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted)
					{
						obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Enabled = updatedConfig.Notifications.PlacedBounty.Hunted.Enabled;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Title = updatedConfig.Notifications.PlacedBounty.Hunted.Title;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.Message = updatedConfig.Notifications.PlacedBounty.Hunted.Message;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath = updatedConfig.Notifications.PlacedBounty.Hunted.IconPath;
					}
					if (updatedConfig.Notifications.PlacedBounty.Expired && obfv_g_BountyConfig.Notifications.PlacedBounty.Expired)
					{
						obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Enabled = updatedConfig.Notifications.PlacedBounty.Expired.Enabled;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Title = updatedConfig.Notifications.PlacedBounty.Expired.Title;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.Message = updatedConfig.Notifications.PlacedBounty.Expired.Message;
						obfv_g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath = updatedConfig.Notifications.PlacedBounty.Expired.IconPath;
					}
					if (updatedConfig.Notifications.PlacedBounty.SurvivalReward && obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward)
					{
						obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Enabled = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Enabled;
						obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Title;
						obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Message;
						obfv_g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath = updatedConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
					}
					if (updatedConfig.Notifications.PlacedBounty.KilledReward && obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward)
					{
						obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Enabled = updatedConfig.Notifications.PlacedBounty.KilledReward.Enabled;
						obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title = updatedConfig.Notifications.PlacedBounty.KilledReward.Title;
						obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message = updatedConfig.Notifications.PlacedBounty.KilledReward.Message;
						obfv_g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath = updatedConfig.Notifications.PlacedBounty.KilledReward.IconPath;
					}
				}
				if (updatedConfig.Notifications.RuleBreaker && obfv_g_BountyConfig.Notifications.RuleBreaker)
				{
					if (updatedConfig.Notifications.RuleBreaker.Hunted && obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted)
					{
						obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Enabled = updatedConfig.Notifications.RuleBreaker.Hunted.Enabled;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Title = updatedConfig.Notifications.RuleBreaker.Hunted.Title;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.Message = updatedConfig.Notifications.RuleBreaker.Hunted.Message;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath = updatedConfig.Notifications.RuleBreaker.Hunted.IconPath;
					}
					if (updatedConfig.Notifications.RuleBreaker.HitWarning && obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning)
					{
						obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Enabled = updatedConfig.Notifications.RuleBreaker.HitWarning.Enabled;
						obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title = updatedConfig.Notifications.RuleBreaker.HitWarning.Title;
						obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message = updatedConfig.Notifications.RuleBreaker.HitWarning.Message;
						obfv_g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath = updatedConfig.Notifications.RuleBreaker.HitWarning.IconPath;
					}
					if (updatedConfig.Notifications.RuleBreaker.Expired && obfv_g_BountyConfig.Notifications.RuleBreaker.Expired)
					{
						obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Enabled = updatedConfig.Notifications.RuleBreaker.Expired.Enabled;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Title = updatedConfig.Notifications.RuleBreaker.Expired.Title;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.Message = updatedConfig.Notifications.RuleBreaker.Expired.Message;
						obfv_g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath = updatedConfig.Notifications.RuleBreaker.Expired.IconPath;
					}
					if (updatedConfig.Notifications.RuleBreaker.SurvivalReward && obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward)
					{
						obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Enabled = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Enabled;
						obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Title;
						obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Message;
						obfv_g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath = updatedConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
					}
					if (updatedConfig.Notifications.RuleBreaker.KilledReward && obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward)
					{
						obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Enabled = updatedConfig.Notifications.RuleBreaker.KilledReward.Enabled;
						obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title = updatedConfig.Notifications.RuleBreaker.KilledReward.Title;
						obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message = updatedConfig.Notifications.RuleBreaker.KilledReward.Message;
						obfv_g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath = updatedConfig.Notifications.RuleBreaker.KilledReward.IconPath;
					}
				}
				if (updatedConfig.Notifications.Other && obfv_g_BountyConfig.Notifications.Other)
				{
					if (updatedConfig.Notifications.Other.InsufficientTokens && obfv_g_BountyConfig.Notifications.Other.InsufficientTokens)
					{
						obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Enabled = updatedConfig.Notifications.Other.InsufficientTokens.Enabled;
						obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Title = updatedConfig.Notifications.Other.InsufficientTokens.Title;
						obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.Message = updatedConfig.Notifications.Other.InsufficientTokens.Message;
						obfv_g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath = updatedConfig.Notifications.Other.InsufficientTokens.IconPath;
					}
					if (updatedConfig.Notifications.Other.SkipBountyNoPlayers && obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers)
					{
						obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Enabled = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Enabled;
						obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Title;
						obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Message;
						obfv_g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath = updatedConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
					}
					if (updatedConfig.Notifications.Other.SkipBountySuccess && obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess)
					{
						obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Enabled = updatedConfig.Notifications.Other.SkipBountySuccess.Enabled;
						obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Title = updatedConfig.Notifications.Other.SkipBountySuccess.Title;
						obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.Message = updatedConfig.Notifications.Other.SkipBountySuccess.Message;
						obfv_g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath = updatedConfig.Notifications.Other.SkipBountySuccess.IconPath;
					}
					if (updatedConfig.Notifications.Other.BountySkipped && obfv_g_BountyConfig.Notifications.Other.BountySkipped)
					{
						obfv_g_BountyConfig.Notifications.Other.BountySkipped.Enabled = updatedConfig.Notifications.Other.BountySkipped.Enabled;
						obfv_g_BountyConfig.Notifications.Other.BountySkipped.Title = updatedConfig.Notifications.Other.BountySkipped.Title;
						obfv_g_BountyConfig.Notifications.Other.BountySkipped.Message = updatedConfig.Notifications.Other.BountySkipped.Message;
						obfv_g_BountyConfig.Notifications.Other.BountySkipped.IconPath = updatedConfig.Notifications.Other.BountySkipped.IconPath;
					}
					if (updatedConfig.Notifications.Other.RewardHandsNotFree && obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree)
					{
						obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Enabled = updatedConfig.Notifications.Other.RewardHandsNotFree.Enabled;
						obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title = updatedConfig.Notifications.Other.RewardHandsNotFree.Title;
						obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message = updatedConfig.Notifications.Other.RewardHandsNotFree.Message;
						obfv_g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath = updatedConfig.Notifications.Other.RewardHandsNotFree.IconPath;
					}
					if (updatedConfig.Notifications.Other.PlayerOnCooldown && obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown)
					{
						obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Enabled = updatedConfig.Notifications.Other.PlayerOnCooldown.Enabled;
						obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title = updatedConfig.Notifications.Other.PlayerOnCooldown.Title;
						obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message = updatedConfig.Notifications.Other.PlayerOnCooldown.Message;
						obfv_g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath = updatedConfig.Notifications.Other.PlayerOnCooldown.IconPath;
					}
					if (updatedConfig.Notifications.Other.PlayerInSafeZone && obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone)
					{
						obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Enabled = updatedConfig.Notifications.Other.PlayerInSafeZone.Enabled;
						obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title = updatedConfig.Notifications.Other.PlayerInSafeZone.Title;
						obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message = updatedConfig.Notifications.Other.PlayerInSafeZone.Message;
						obfv_g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath = updatedConfig.Notifications.Other.PlayerInSafeZone.IconPath;
					}
					if (updatedConfig.Notifications.Other.BountyPersisted && obfv_g_BountyConfig.Notifications.Other.BountyPersisted)
					{
						obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Enabled = updatedConfig.Notifications.Other.BountyPersisted.Enabled;
						obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Title = updatedConfig.Notifications.Other.BountyPersisted.Title;
						obfv_g_BountyConfig.Notifications.Other.BountyPersisted.Message = updatedConfig.Notifications.Other.BountyPersisted.Message;
						obfv_g_BountyConfig.Notifications.Other.BountyPersisted.IconPath = updatedConfig.Notifications.Other.BountyPersisted.IconPath;
					}
					if (updatedConfig.Notifications.Other.TeleportedOutOfTerritory && obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory)
					{
						obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled;
						obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
						obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
						obfv_g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
					}
					if (updatedConfig.Notifications.Other.BountyPausedInTerritory && obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory)
					{
						obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Enabled = updatedConfig.Notifications.Other.BountyPausedInTerritory.Enabled;
						obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title = updatedConfig.Notifications.Other.BountyPausedInTerritory.Title;
						obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message = updatedConfig.Notifications.Other.BountyPausedInTerritory.Message;
						obfv_g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath = updatedConfig.Notifications.Other.BountyPausedInTerritory.IconPath;
					}
				}
			}
			if (updatedConfig.Broadcasts && obfv_g_BountyConfig.Broadcasts)
			{
				if (updatedConfig.Broadcasts.PlacedBounty && obfv_g_BountyConfig.Broadcasts.PlacedBounty)
				{
					obfv_g_BountyConfig.Broadcasts.PlacedBounty.Enabled = updatedConfig.Broadcasts.PlacedBounty.Enabled;
					obfv_g_BountyConfig.Broadcasts.PlacedBounty.Title = updatedConfig.Broadcasts.PlacedBounty.Title;
					obfv_g_BountyConfig.Broadcasts.PlacedBounty.Message = updatedConfig.Broadcasts.PlacedBounty.Message;
					obfv_g_BountyConfig.Broadcasts.PlacedBounty.IconPath = updatedConfig.Broadcasts.PlacedBounty.IconPath;
				}
				if (updatedConfig.Broadcasts.RuleBreaker && obfv_g_BountyConfig.Broadcasts.RuleBreaker)
				{
					obfv_g_BountyConfig.Broadcasts.RuleBreaker.Enabled = updatedConfig.Broadcasts.RuleBreaker.Enabled;
					obfv_g_BountyConfig.Broadcasts.RuleBreaker.Title = updatedConfig.Broadcasts.RuleBreaker.Title;
					obfv_g_BountyConfig.Broadcasts.RuleBreaker.Message = updatedConfig.Broadcasts.RuleBreaker.Message;
					obfv_g_BountyConfig.Broadcasts.RuleBreaker.IconPath = updatedConfig.Broadcasts.RuleBreaker.IconPath;
				}
				//! Expired/Win/Suicide/Logout/Warning have no admin-menu widgets - see the Core note above.
			}
			obfv_g_BountyConfig.obfm_ValidateConfig();
			obfv_g_BountyConfig.obfm_SaveConfig();
			obfc_BountyManager.obfm_ReloadAllConfigs(player);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyAdminUpdateConfig] Config updated and reloaded by admin: " + sender.GetName());
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyAdminUpdateConfig] g_BountyConfig is null - cannot update config!");
		}
	}
	void BountyAdminRequestConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase player;
		if (type != CallType.Server || !sender)
			return;
		player = PlayerBase.Cast(sender.GetPlayer());
		if (!player)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminRequestConfig: Player not found for identity: " + sender.GetName());
			return;
		}
		if (!player.obfm_IsBountyAdmin())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminRequestConfig: Access denied for non-admin player: " + sender.GetName());
			return;
		}
		if (obfv_g_BountyConfig)
		{
			GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveConfig", new Param1<ref obfc_BountyConfig>(obfv_g_BountyConfig), true, sender);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] BountyAdminRequestConfig: Sent config to admin: " + sender.GetName());
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminRequestConfig: g_BountyConfig is null - cannot send config!");
		}
	}
	void BoardBountyAction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param1<string> actionParam;
		string action;
		PlayerBase player;
		if (type != CallType.Server || !sender)
			return;
		if (!ctx.Read(actionParam))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BoardBountyAction: Failed to read action parameter.");
			return;
		}
		action = actionParam.param1;
		player = PlayerBase.Cast(sender.GetPlayer());
		if (!player)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BoardBountyAction: Player not found for identity: " + sender.GetName());
			return;
		}
		if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.obfm_IsBlacklistedIdentity(sender))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BoardBountyAction: Blacklisted player " + sender.GetName() + " tried to use bounty board action: " + action);
			return;
		}
		bool success;
		string targetPlayerName = "";
		string targetPlayerIdentifier = "";
		PlayerBase targetPlayer = null;
		int requestedMinutes = 0;
		int minuteSeparatorIndex = -1;
		int costPerMinute = 0;
		string requestedMinutesStr = "";
		float requestedDurationSeconds = 0.0;
		int i;
		Man man;
		PlayerBase playerBase;
		PlayerIdentity identity;
		string candidateName = "";
		PlayerBase candidatePlayer = null;
		PlayerIdentity candidateIdentity = null;
		int tokensRequired = 0;
		array<ItemBase> foundTokens;
		ItemBase item;
		string itemClassName = "";
		int j;
		int tokensRemoved = 0;
		BountyType bountyType = BountyType.PLACED;
		float newDuration = 0.0;
		array<Man> allPlayers;
		array<PlayerBase> availablePlayers;
		PlayerIdentity skippingIdentity;
		string skippingPlayerName = "";
		int randomIndex = 0;
		array<Man> players;
		array<string> tokenClassNames;
		int k;
		int m;
		bool alreadyAdded = false;
		GameInventory inventory;
		array<EntityAI> allInventoryItems;
		int totalTokenQuantity = 0;
		float itemQuantity = 0.0;
		int stackQuantity = 0;
		int neededFromStack = 0;
		int updatedClaimAmount = 0;
		Param1<int> claimAmountResult;
		string actualPlayerName = "";
		int cdIndex;
		if (action == "SkipBounty")
		{
			if (!player.obfm_HasBounty())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to skip bounty but doesn't have one");
				return;
			}
			bountyType = player.obfm_GetBountyType();
			newDuration = 0.0;
			if (obfv_g_BountyConfig)
			{
				if (bountyType == BountyType.RULE_BREAKER)
				{
					newDuration = obfv_g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
				}
				else
				{
					newDuration = obfv_g_BountyConfig.PlacedBounty.BountyDurationSeconds;
				}
			}
			if (newDuration <= 0.0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Cannot skip bounty - invalid duration from config");
				return;
			}
			allPlayers = new array<Man>();
			g_Game.GetPlayers(allPlayers);
			availablePlayers = new array<PlayerBase>();
			skippingIdentity = player.GetIdentity();
			skippingPlayerName = "";
			if (skippingIdentity)
			{
				skippingPlayerName = skippingIdentity.GetName();
			}
			for (i = 0; i < allPlayers.Count(); i++)
			{
				man = allPlayers.Get(i);
				candidatePlayer = PlayerBase.Cast(man);
				if (!candidatePlayer || !candidatePlayer.IsAlive())
					continue;
				candidateIdentity = candidatePlayer.GetIdentity();
				if (!candidateIdentity)
					continue;
				candidateName = candidateIdentity.GetName();
				if (candidateName == "" || candidateName == skippingPlayerName)
					continue;
				if (candidatePlayer.obfm_HasBounty())
					continue;
				if (candidatePlayer.obfm_IsBountyOnCooldown())
					continue;
				availablePlayers.Insert(candidatePlayer);
			}
			if (availablePlayers.Count() == 0)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] No available players to transfer bounty to for " + sender.GetName() + " - tokens not consumed");
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS, sender);
				return;
			}
			tokensRequired = 0;
			if (obfv_g_BountyConfig)
			{
				tokensRequired = obfv_g_BountyConfig.Core.SkipBountyTokenRequired;
			}
			if (tokensRequired > 0)
			{
				totalTokenQuantity = obfm_GetPlayerTokenCount(player, foundTokens);
				if (totalTokenQuantity < tokensRequired)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to skip bounty but doesn't have enough tokens. Required: " + tokensRequired.ToString() + ", Found: " + totalTokenQuantity.ToString());
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS, sender, "", "", 0.0, 0, 0, 0, tokensRequired, totalTokenQuantity);
					return;
				}
			}
			randomIndex = Math.RandomInt(0, availablePlayers.Count());
			targetPlayer = availablePlayers.Get(randomIndex);
			if (!targetPlayer || !targetPlayer.GetIdentity())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to get target player for bounty transfer");
				return;
			}
			targetPlayerName = targetPlayer.GetIdentity().GetName();
			obfc_BountyManager.obfm_ClearBountyFromPlayer(player, player, "Skipped - transferred to " + targetPlayerName, true);
			success = obfc_BountyManager.obfm_ApplyBountyToPlayer(targetPlayer, player, newDuration, "Transferred from " + skippingPlayerName + " (skipped)", bountyType, true);
			if (success)
			{
				if (tokensRequired > 0)
				{
					tokensRemoved = obfm_ConsumePlayerTokens(player, tokensRequired, totalTokenQuantity);
					if (tokensRemoved < tokensRequired)
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to remove all required skip tokens after transfer. Required: " + tokensRequired.ToString() + ", Removed: " + tokensRemoved.ToString());
						obfc_BountyManager.obfm_ClearBountyFromPlayer(targetPlayer, player, "Skip token rollback", true);
						obfc_BountyManager.obfm_ApplyBountyToPlayer(player, player, newDuration, "Skip token rollback", bountyType, true);
						return;
					}
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Removed " + tokensRemoved.ToString() + " tokens from player " + sender.GetName());
				}
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_BOUNTY_SKIPPED, sender);
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Transferred bounty from " + skippingPlayerName + " to " + targetPlayerName + " (skip action). New Duration: " + newDuration.ToString() + "s, BountyType: " + bountyType.ToString());
				obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_SKIP_SUCCESS, sender, targetPlayerName);
			}
			else
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to transfer bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
			}
		}
		else if (action.IndexOf("PlaceBountyOnPlayer:") == 0)
		{
			tokensRequired = 0;
			tokensRemoved = 0;
			requestedMinutes = 0;
			requestedDurationSeconds = 0.0;
			targetPlayerIdentifier = action;
			targetPlayerIdentifier.Replace("PlaceBountyOnPlayer:", "");
			//! Optional "@@<minutes>" suffix - only sent while per-minute pricing is active.
			minuteSeparatorIndex = targetPlayerIdentifier.IndexOf("@@");
			if (minuteSeparatorIndex >= 0)
			{
				requestedMinutesStr = targetPlayerIdentifier.Substring(minuteSeparatorIndex + 2, targetPlayerIdentifier.Length() - (minuteSeparatorIndex + 2));
				requestedMinutes = requestedMinutesStr.ToInt();
				targetPlayerIdentifier = targetPlayerIdentifier.Substring(0, minuteSeparatorIndex);
			}
			if (obfv_g_BountyConfig)
			{
				costPerMinute = obfv_g_BountyConfig.Core.BountyRequestCostPerMinute;
				if (costPerMinute > 0)
				{
					if (requestedMinutes < obfv_g_BountyConfig.Core.BountyRequestMinMinutes)
						requestedMinutes = obfv_g_BountyConfig.Core.BountyRequestMinMinutes;
					if (requestedMinutes > obfv_g_BountyConfig.Core.BountyRequestMaxMinutes)
						requestedMinutes = obfv_g_BountyConfig.Core.BountyRequestMaxMinutes;
					tokensRequired = costPerMinute * requestedMinutes;
					requestedDurationSeconds = requestedMinutes * 60.0;
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Per-minute pricing active - " + requestedMinutes.ToString() + " minute(s) x " + costPerMinute.ToString() + " token(s) = " + tokensRequired.ToString() + " token(s)");
				}
				else
				{
					tokensRequired = obfv_g_BountyConfig.Core.PlaceBountyTokenRequired;
				}
			}
			if (tokensRequired > 0)
			{
				totalTokenQuantity = obfm_GetPlayerTokenCount(player, foundTokens);
				if (totalTokenQuantity < tokensRequired)
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to place bounty but doesn't have enough tokens. Required: " + tokensRequired.ToString() + ", Found: " + totalTokenQuantity.ToString());
					obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS, sender, "", "", 0.0, 0, 0, 0, tokensRequired, totalTokenQuantity);
					return;
				}
			}
			if (targetPlayerIdentifier != "")
			{
				targetPlayer = obfm_FindOnlinePlayerByIdentifier(targetPlayerIdentifier);
				if (targetPlayer && targetPlayer.GetIdentity())
				{
					actualPlayerName = targetPlayer.GetIdentity().GetName();
					if (targetPlayer.obfm_IsBountyOnCooldown())
					{
						float cooldownRemaining = targetPlayer.obfm_GetBountyCooldownRemaining();
						int cooldownSeconds = Math.Ceil(cooldownRemaining);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Cannot place bounty on " + actualPlayerName + " - player is on cooldown (" + cooldownSeconds.ToString() + " seconds remaining)");
						obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN, sender, actualPlayerName, "", 0.0, 0, 0, 0, 0, 0, cooldownSeconds);
						return;
					}
					success = obfc_BountyManager.obfm_ApplyBountyToPlayer(targetPlayer, player, requestedDurationSeconds, "Bounty placed by " + sender.GetName() + " via bounty board", BountyType.PLACED);
					if (success)
					{
						if (tokensRequired > 0)
						{
							tokensRemoved = obfm_ConsumePlayerTokens(player, tokensRequired, totalTokenQuantity);
							if (tokensRemoved < tokensRequired)
							{
								obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to remove all required placement tokens after applying bounty. Required: " + tokensRequired.ToString() + ", Removed: " + tokensRemoved.ToString());
								obfc_BountyManager.obfm_ClearBountyFromPlayer(targetPlayer, player, "Placement token rollback", true);
								return;
							}
							obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Removed " + tokensRemoved.ToString() + " tokens from player " + sender.GetName() + " for placing bounty");
						}
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Placed bounty on " + actualPlayerName + " by " + sender.GetName());
					}
					else
					{
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Failed to place bounty on " + actualPlayerName + " (system may be disabled or player lifetime not reached)");
					}
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player not found: " + actualPlayerName);
				}
			}
		}
		else if (action == "ClaimRewards")
		{
			if (!player.obfm_HasPendingRewards())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to claim rewards but has no pending rewards");
				return;
			}
			if (player.obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " is a rule breaker and tried to claim rewards, but PvERuleBreakerGiveRewards = 0. Blocking claim.");
				player.obfm_ClearPendingRewards();
				return;
			}
			bool spawnSuccess = false;
			if (player.obfm_HasPendingRewards())
			{
				spawnSuccess = obfc_BountyManager.obfm_SpawnBountyRewardGiftBox(player, false, false);
				if (spawnSuccess)
				{
					player.obfm_ClaimPendingSuccessReward();
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Successfully claimed 1 success reward (chest only, no currency) for " + sender.GetName() + " (remaining: " + player.obfm_GetPendingSuccessRewardCount().ToString() + ")");
					#ifdef EXPANSIONMODHARDLINE
					if (obfv_g_BountySuccessRewardConfig && obfv_g_BountySuccessRewardConfig.EnableHardlineReputationReward && obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount > 0)
					{
						player.Expansion_AddReputation(obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Gave Hardline reputation reward of " + obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount.ToString() + " to " + sender.GetName() + " for claiming success reward.");
					}
					#endif
					updatedClaimAmount = player.obfm_GetTotalPendingRewardCount();
					claimAmountResult = new Param1<int>(updatedClaimAmount);
					GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", claimAmountResult, true, sender);
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to claim success reward for " + sender.GetName() + " (hands not free or spawn failed) - keeping pending reward");
				}
			}
		}
		else if (action == "ClaimCurrencyRewards")
		{
			if (!player.obfm_HasPendingRewards())
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to claim currency rewards but has no pending rewards");
				return;
			}
			if (player.obfm_IsRuleBreakerBounty() && obfv_g_BountyConfig && obfv_g_BountyConfig.Reward && !obfv_g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Player " + sender.GetName() + " is a rule breaker and tried to claim currency rewards, but PvERuleBreakerGiveRewards = 0. Blocking claim.");
				player.obfm_ClearPendingRewards();
				return;
			}
			bool currencySuccess = false;
			if (player.obfm_HasPendingRewards())
			{
				currencySuccess = obfc_BountyManager.obfm_GiveCurrencyRewardsOnly(player, false);
				if (currencySuccess)
				{
					player.obfm_ClaimPendingSuccessReward();
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Successfully claimed 1 success reward currency for " + sender.GetName() + " (remaining: " + player.obfm_GetPendingSuccessRewardCount().ToString() + ")");
					#ifdef EXPANSIONMODHARDLINE
					if (obfv_g_BountySuccessRewardConfig && obfv_g_BountySuccessRewardConfig.EnableHardlineReputationReward && obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount > 0)
					{
						player.Expansion_AddReputation(obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount);
						obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BoardBountyAction] Gave Hardline reputation reward of " + obfv_g_BountySuccessRewardConfig.HardlineReputationRewardAmount.ToString() + " to " + sender.GetName() + " for claiming success reward currency.");
					}
					#endif
					updatedClaimAmount = player.obfm_GetTotalPendingRewardCount();
					claimAmountResult = new Param1<int>(updatedClaimAmount);
					GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", claimAmountResult, true, sender);
				}
				else
				{
					obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BoardBountyAction] Failed to claim success reward currency for " + sender.GetName() + " (no currency configured) - keeping pending reward");
				}
			}
		}
		else
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BoardBountyAction: Unknown action: " + action);
		}
	}
	string obfm_FormatCooldownTime(int totalSeconds)
	{
		int days;
		int hours;
		int minutes;
		int seconds;
		if (totalSeconds <= 0)
			return "0s";
		days = totalSeconds / 86400; 
		hours = (totalSeconds % 86400) / 3600; 
		minutes = (totalSeconds % 3600) / 60; 
		seconds = totalSeconds % 60;
		if (days > 0)
		{
			return days.ToString() + "d";
		}
		else if (hours > 0)
		{
			return hours.ToString() + "h";
		}
		else if (minutes > 0)
		{
			return minutes.ToString() + "m";
		}
		else
		{
			return seconds.ToString() + "s";
		}
	}
	void BountyRequestOnlinePlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase requestingPlayer;
		PlayerIdentity requestingIdentity;
		string requestingPlayerName;
		bool excludeSelf;
		array<string> playerList;
		array<Man> players;
		PlayerBase player;
		PlayerIdentity identity;
		string playerName;
		string displayName;
		string playerId;
		float cooldownRemaining;
		int cooldownSeconds;
		string formattedCooldown;
		Param1<array<string>> result;
		if (type != CallType.Server || !sender)
			return;
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (!requestingPlayer)
			return;
		requestingIdentity = requestingPlayer.GetIdentity();
		if (!requestingIdentity)
			return;
		requestingPlayerName = requestingIdentity.GetName();
		excludeSelf = false;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.DisableSelfBounty)
		{
			excludeSelf = true;
		}
		playerList = new array<string>();
		players = new array<Man>();
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			player = PlayerBase.Cast(man);
			if (!player || !player.IsAlive())
				continue;
			identity = player.GetIdentity();
			if (!identity)
				continue;
			playerName = identity.GetName();
			playerId = identity.GetId();
			if (playerName == "")
				continue;
			if (excludeSelf && playerName == requestingPlayerName)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Excluding requesting player from online list (DisableSelfBounty = true): " + requestingPlayerName);
				continue;
			}
			displayName = playerName;
			if (player.obfm_IsBountyOnCooldown())
			{
				cooldownRemaining = player.obfm_GetBountyCooldownRemaining();
				cooldownSeconds = Math.Ceil(cooldownRemaining);
				formattedCooldown = obfm_FormatCooldownTime(cooldownSeconds);
				displayName = playerName + " CD:" + formattedCooldown;
			}
			playerList.Insert(obfm_BuildPlayerListEntry(displayName, playerId));
		}
		result = new Param1<array<string>>(playerList);
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveOnlinePlayers", result, true, sender);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent online players list to " + requestingPlayerName + ": " + playerList.Count().ToString() + " players (excludeSelf: " + excludeSelf.ToString() + ")");
	}
	void BountyAdminRequestPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase requestingPlayer;
		PlayerIdentity requestingIdentity;
		string requestingPlayerName;
		array<string> playerList;
		array<Man> players;
		PlayerBase player;
		PlayerIdentity identity;
		string playerName;
		string displayName;
		string playerId;
		float cooldownRemaining;
		int cooldownSeconds;
		string formattedCooldown;
		Param1<array<string>> result;
		if (type != CallType.Server || !sender)
			return;
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (!requestingPlayer)
			return;
		if (!requestingPlayer.obfm_IsBountyAdmin())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminRequestPlayers: Access denied for non-admin player: " + sender.GetName());
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
			return;
		}
		requestingIdentity = requestingPlayer.GetIdentity();
		if (!requestingIdentity)
			return;
		requestingPlayerName = requestingIdentity.GetName();
		playerList = new array<string>();
		players = new array<Man>();
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			player = PlayerBase.Cast(man);
			if (!player || !player.IsAlive())
				continue;
			identity = player.GetIdentity();
			if (!identity)
				continue;
			playerName = identity.GetName();
			playerId = identity.GetId();
			if (playerName == "")
				continue;
			displayName = playerName;
			if (player.obfm_IsBountyOnCooldown())
			{
				cooldownRemaining = player.obfm_GetBountyCooldownRemaining();
				cooldownSeconds = Math.Ceil(cooldownRemaining);
				formattedCooldown = obfm_FormatCooldownTime(cooldownSeconds);
				displayName = playerName + " CD:" + formattedCooldown;
			}
			else
			{
				displayName = playerName + " (No Cooldown)";
			}
			playerList.Insert(obfm_BuildPlayerListEntry(displayName, playerId));
		}
		result = new Param1<array<string>>(playerList);
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceivePlayers", result, true, sender);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent admin players list to " + requestingPlayerName + ": " + playerList.Count().ToString() + " players");
	}
	void BountyRequestClaimAmount(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase requestingPlayer;
		int totalClaimAmount;
		Param1<int> result;
		if (type != CallType.Server || !sender)
			return;
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (!requestingPlayer)
			return;
		totalClaimAmount = requestingPlayer.obfm_GetTotalPendingRewardCount();
		result = new Param1<int>(totalClaimAmount);
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", result, true, sender);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent claim amount to " + sender.GetName() + ": " + totalClaimAmount.ToString());
	}
	//! Sends the board pricing model to the client so it can show the duration input and live cost.
	void BountyRequestPricing(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase requestingPlayer;
		int costPerMinute;
		int minMinutes;
		int maxMinutes;
		Param3<int, int, int> result;
		if (type != CallType.Server || !sender)
			return;
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (!requestingPlayer)
			return;
		costPerMinute = 0;
		minMinutes = 1;
		maxMinutes = 1;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core)
		{
			costPerMinute = obfv_g_BountyConfig.Core.BountyRequestCostPerMinute;
			minMinutes = obfv_g_BountyConfig.Core.BountyRequestMinMinutes;
			maxMinutes = obfv_g_BountyConfig.Core.BountyRequestMaxMinutes;
		}
		result = new Param3<int, int, int>(costPerMinute, minMinutes, maxMinutes);
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceivePricing", result, true, sender);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent board pricing to " + sender.GetName() + ": " + costPerMinute.ToString() + " token(s)/minute, range " + minMinutes.ToString() + "-" + maxMinutes.ToString());
	}
	void BountyAdminRequestBlacklist(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		PlayerBase requestingPlayer;
		array<string> blacklistList;
		array<Man> players;
		PlayerBase player;
		PlayerIdentity identity;
		string playerGUID;
		string playerName;
		string entry;
		int i;
		int j;
		bool found;
		int colonIndex;
		Param1<array<string>> result;
		if (type != CallType.Server || !sender)
			return;
		requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
		if (!requestingPlayer)
			return;
		if (!requestingPlayer.obfm_IsBountyAdmin())
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyModule] BountyAdminRequestBlacklist: Access denied for non-admin player: " + sender.GetName());
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
			return;
		}
		blacklistList = new array<string>();
		if (obfv_g_BountyBlacklistConfig && obfv_g_BountyBlacklistConfig.BlacklistedGUIDs)
		{
			players = new array<Man>();
			g_Game.GetPlayers(players);
			for (i = 0; i < obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Count(); i++)
			{
				entry = obfv_g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
				colonIndex = entry.IndexOf(":");
				if (colonIndex >= 0 && colonIndex < entry.Length() - 1)
				{
					blacklistList.Insert(entry);
				}
				else
				{
					found = false;
					for (j = 0; j < players.Count(); j++)
					{
						player = PlayerBase.Cast(players.Get(j));
						if (player && player.GetIdentity())
						{
							playerGUID = player.GetIdentity().GetId();
							if (playerGUID == entry)
							{
								playerName = player.GetIdentity().GetName();
								blacklistList.Insert(playerName + ":" + playerGUID);
								found = true;
								break;
							}
						}
					}
					if (!found)
					{
						blacklistList.Insert("Unknown:" + entry);
					}
				}
			}
		}
		result = new Param1<array<string>>(blacklistList);
		GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", result, true, sender);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyModule] Sent blacklisted players list to " + sender.GetName() + ": " + blacklistList.Count().ToString() + " players");
	}
}