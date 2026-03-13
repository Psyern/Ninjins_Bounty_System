[CF_RegisterModule(BountyModule)]
class BountyModule : CF_ModuleWorld
{
    static BountyModule s_Instance;
    ref BountyManager m_BountyManager;
    ref BountyAdminConfig m_BountyAdminConfig;
    ref BountyBlacklistConfig m_BountyBlacklistConfig;
    ref BountyBoardPlacementConfig m_BountyBoardPlacementConfig;
    ref array<Object> m_ConfigSpawnedBountyBoards;
    override void OnInit()
    {
        super.OnInit();
        s_Instance = this;
        m_ConfigSpawnedBountyBoards = new array<Object>();
        EnableInvokeConnect();
        EnableUpdate();
        EnableMissionStart();
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Module initialized");
    }
    static BountyModule GetInstance()
    {
        return s_Instance;
    }
    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);
        if (!IsMissionHost())
            return;
        GetNinjins_Bounty_SystemLogger().LogInfo("Ninjins_Bounty_System mod has started !");
        GetNinjins_Bounty_SystemLogger().LogInfo("Ninjins_Bounty_System mod has started!");
        InitBountyAdminConfig();
        InitBountyBlacklistConfig();
        g_BountyConfig = BountyConfig.LoadConfig();
        if (g_BountyConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("BountyConfig loaded. EnableBountySystem: " + g_BountyConfig.Core.EnableBountySystem.ToString() + ", Duration: " + g_BountyConfig.PlacedBounty.BountyDurationSeconds.ToString() + " seconds");
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("Failed to load BountyConfig!");
        }
        g_BountySuccessRewardConfig = BountySuccessRewardConfig.LoadConfig();
        if (g_BountySuccessRewardConfig)
        {
            int sectionCount = 0;
            if (g_BountySuccessRewardConfig.BountyRewardItems)
                sectionCount = g_BountySuccessRewardConfig.BountyRewardItems.Count();
            GetNinjins_Bounty_SystemLogger().LogInfo("BountySuccessRewardConfig loaded. RewardSections: " + sectionCount.ToString());
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("Failed to load BountySuccessRewardConfig!");
        }
        InitBountyBoardPlacementConfig();
        SpawnConfiguredBountyBoards();
        m_BountyManager = BountyManager.GetInstance();
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "RequestBountiedPlayers", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminAction", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminUpdateConfig", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestConfig", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BoardBountyAction", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyRequestOnlinePlayers", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestPlayers", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyRequestClaimAmount", this, SingleplayerExecutionType.Server);
        GetRPCManager().AddRPC("Ninjins_Bounty_System", "BountyAdminRequestBlacklist", this, SingleplayerExecutionType.Server);
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Registered all RPC handlers");
    }
    void InitBountyAdminConfig()
    {
        m_BountyAdminConfig = BountyAdminConfig.LoadConfig();
        g_BountyAdminConfig = m_BountyAdminConfig;
        if (!m_BountyAdminConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[ERROR] Failed to load BountyAdminConfig.");
        }
    }
    void InitBountyBlacklistConfig()
    {
        m_BountyBlacklistConfig = BountyBlacklistConfig.LoadConfig();
        g_BountyBlacklistConfig = m_BountyBlacklistConfig;
        if (!m_BountyBlacklistConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[ERROR] Failed to load BountyBlacklistConfig.");
        }
    }
    void InitBountyBoardPlacementConfig()
    {
        m_BountyBoardPlacementConfig = BountyBoardPlacementConfig.LoadConfig();
        g_BountyBoardPlacementConfig = m_BountyBoardPlacementConfig;
        if (!m_BountyBoardPlacementConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[ERROR] Failed to load BountyBoardPlacementConfig.");
        }
    }
    vector BuildBoardVector(array<float> values)
    {
        string vectorString = "0 0 0";
        if (values && values.Count() >= 3)
        {
            vectorString = values.Get(0).ToString() + " " + values.Get(1).ToString() + " " + values.Get(2).ToString();
        }
        return vectorString;
    }
    bool IsPlaceholderBoardPlacement(BountyBoardPlacement placement)
    {
        if (!placement || !placement.Position || placement.Position.Count() < 3)
            return true;
        return placement.Position.Get(0) == 0.0 && placement.Position.Get(1) == 0.0 && placement.Position.Get(2) == 0.0;
    }
    void ClearConfiguredBountyBoards()
    {
        int i;
        Object boardObject;
        if (!m_ConfigSpawnedBountyBoards)
            return;
        for (i = m_ConfigSpawnedBountyBoards.Count() - 1; i >= 0; i--)
        {
            boardObject = m_ConfigSpawnedBountyBoards.Get(i);
            if (boardObject)
            {
                g_Game.ObjectDelete(boardObject);
            }
            m_ConfigSpawnedBountyBoards.Remove(i);
        }
    }
    void SpawnConfiguredBountyBoards()
    {
        int i;
        BountyBoardPlacement placement;
        vector boardPosition;
        vector boardRotation;
        Object boardObject;
        if (!IsMissionHost())
            return;
        if (!m_ConfigSpawnedBountyBoards)
        {
            m_ConfigSpawnedBountyBoards = new array<Object>();
        }
        ClearConfiguredBountyBoards();
        if (!g_BountyBoardPlacementConfig || !g_BountyBoardPlacementConfig.BoardPlacements)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] No board placement config loaded - skipping configured board spawn.");
            return;
        }
        for (i = 0; i < g_BountyBoardPlacementConfig.BoardPlacements.Count(); i++)
        {
            placement = g_BountyBoardPlacementConfig.BoardPlacements.Get(i);
            if (!placement)
                continue;
            if (IsPlaceholderBoardPlacement(placement))
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Skipping placeholder board placement entry at index " + i.ToString());
                continue;
            }
            boardPosition = BuildBoardVector(placement.Position);
            boardRotation = BuildBoardVector(placement.Rotation);
            boardObject = GetGame().CreateObjectEx("Ninjins_Bounty_Board_Static", boardPosition, ECE_PLACE_ON_SURFACE);
            if (!boardObject)
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyModule] Failed to spawn configured bounty board at index " + i.ToString());
                continue;
            }
            boardObject.SetOrientation(boardRotation);
            m_ConfigSpawnedBountyBoards.Insert(boardObject);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Spawned configured bounty board #" + i.ToString() + " at " + boardPosition.ToString() + " with rotation " + boardRotation.ToString());
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Configured bounty board spawn complete. Spawned: " + m_ConfigSpawnedBountyBoards.Count().ToString());
    }
    string BuildPlayerListEntry(string displayName, string playerId)
    {
        return displayName + "||" + playerId;
    }
    PlayerBase FindOnlinePlayerByIdentifier(string identifier)
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
            if (identity.GetId() == identifier || identity.GetName() == identifier)
                return playerBase;
        }
        return null;
    }
    int GetPlayerTokenCount(PlayerBase player, out array<ItemBase> foundTokens)
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
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.BountyTokenClassNames)
        {
            tokenClassNames = g_BountyConfig.Core.BountyTokenClassNames;
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
    bool ConsumePlayerTokens(PlayerBase player, int tokensRequired, out int tokensRemoved)
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
        if (GetPlayerTokenCount(player, foundTokens) < tokensRequired)
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
        identity = player.GetIdentity();
        if (!player || !identity)
            return;
        if (!m_BountyAdminConfig)
        {
            InitBountyAdminConfig();
        }
        if (!m_BountyBlacklistConfig)
        {
            InitBountyBlacklistConfig();
        }
        playerGUID = identity.GetId();
        playerName = identity.GetName();
        if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.BlacklistedGUIDs)
        {
            updated = false;
            for (i = 0; i < g_BountyBlacklistConfig.BlacklistedGUIDs.Count(); i++)
            {
                entry = g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
                colonIndex = entry.IndexOf(":");
                if (colonIndex < 0)
                {
                    if (entry == playerGUID)
                    {
                        newEntry = playerName + ":" + playerGUID;
                        g_BountyBlacklistConfig.BlacklistedGUIDs.Set(i, newEntry);
                        updated = true;
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyBlacklist] Updated blacklist entry from old format to new format: " + entry + " -> " + newEntry);
                    }
                }
            }
            if (updated)
            {
                g_BountyBlacklistConfig.SaveConfig();
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyBlacklist] Saved blacklist config after updating format for player: " + playerName);
            }
        }
        isAdmin = false;
        if (m_BountyAdminConfig && m_BountyAdminConfig.IsAdmin(playerGUID))
        {
            isAdmin = true;
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdmin] Player " + identity.GetName() + " (" + playerGUID + ") is a bounty system admin.");
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdmin] Player " + identity.GetName() + " (" + playerGUID + ") is NOT a bounty system admin.");
            if (m_BountyAdminConfig && m_BountyAdminConfig.AdminGUIDs)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdmin] AdminGUIDs in config: " + m_BountyAdminConfig.AdminGUIDs.Count().ToString());
                for (i = 0; i < m_BountyAdminConfig.AdminGUIDs.Count(); i++)
                {
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdmin] Config GUID " + i.ToString() + ": " + m_BountyAdminConfig.AdminGUIDs.Get(i));
                }
            }
        }
        player.SetBountyAdminStatus(isAdmin);
        Param1<bool> adminParam = new Param1<bool>(isAdmin);
        g_Game.RPCSingleParam(player, BountyRPC.SYNC_ADMIN_STATUS, adminParam, true, identity);
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdmin] Sent admin status RPC to client: " + isAdmin.ToString());
        if (player.HasBounty())
        {
            Param1<bool> paramBounty = new Param1<bool>(true);
            g_Game.RPCSingleParam(player, BountyRPC.UPDATE_BOUNTY_STATE, paramBounty, true, identity);
            GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Restored bounty state on connect for " + identity.GetName());
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
        if (m_BountyManager)
        {
            m_BountyManager.Update(updateArgs.DeltaTime);
        }
    }
    void RequestBountiedPlayers(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        array<ref BountyPlayerData> bountiedPlayersData;
        array<Man> players;
        int i;
        Man man;
        PlayerBase player;
        PlayerIdentity identity;
        BountyPlayerData playerData;
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
        BountyUISettingsData uiData;
        Param1<BountyUISettingsData> uiParam;
        Param1<array<ref BountyPlayerData>> data;
        if (type != CallType.Server || !sender)
            return;
        if (!BountyConfig.IsSystemActive())
            return;
        if (!g_BountyConfig || !g_BountyConfig.Map || !g_BountyConfig.Map.BountyEnableMapDrawing)
            return;
        bountiedPlayersData = new array<ref BountyPlayerData>();
        players = new array<Man>();
        g_Game.GetPlayers(players);
        for (i = 0; i < players.Count(); i++)
        {
            man = players.Get(i);
            player = PlayerBase.Cast(man);
            if (player && player.HasBounty() && player.IsAlive())
            {
                identity = player.GetIdentity();
                if (!identity)
                    continue;
                playerData = new BountyPlayerData();
                playerData.PlayerID = identity.GetId();
                playerData.PlayerName = identity.GetName();
                playerData.Position = player.GetPosition();
                currentTime = g_Game.GetTime();
                if (player.m_BountyExpireTime > 0.0)
                {
                    playerData.TimeRemaining = (player.m_BountyExpireTime - currentTime) / 1000.0;
                    if (playerData.TimeRemaining < 0.0)
                        playerData.TimeRemaining = 0.0;
                }
                else
                {
                    playerData.TimeRemaining = 0.0;
                }
                if (g_BountyConfig)
                {
                    playerData.CircleRadius = g_BountyConfig.Map.BountyCircleRadius;
                    playerData.CircleColor = g_BountyConfig.Map.BountyCircleColor;
                    playerData.ReduceRadiusOverTime = g_BountyConfig.Map.BountyCircleReduceRadiusOverTime;
                    playerData.IncreaseRadiusOverTime = g_BountyConfig.Map.BountyCircleIncreaseRadiusOverTime;
                    playerData.CircleMinRadius = g_BountyConfig.Map.BountyCircleMinRadius;
                    if (player.IsRuleBreakerBounty())
                    {
                        playerData.BountyDurationSeconds = g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
                    }
                    else
                    {
                        playerData.BountyDurationSeconds = g_BountyConfig.PlacedBounty.BountyDurationSeconds;
                    }
                    playerData.CircleOffsetMinMultiplier = g_BountyConfig.Map.BountyCircleOffsetMinMultiplier;
                    playerData.CircleOffsetMaxMultiplier = g_BountyConfig.Map.BountyCircleOffsetMaxMultiplier;
                    minMult = playerData.CircleOffsetMinMultiplier;
                    maxMult = playerData.CircleOffsetMaxMultiplier;
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
                        playerData.CachedOffsetMultiplier = Math.RandomFloat(minMult, maxMult);
                        playerData.CachedOffsetAngle = Math.RandomFloat(0.0, Math.PI2);
                    }
                    else
                    {
                        playerData.CachedOffsetMultiplier = 0.0;
                        playerData.CachedOffsetAngle = 0.0;
                    }
                }
                bountiedPlayersData.Insert(playerData);
            }
        }
        requestingPlayer = PlayerBase.Cast(sender.GetPlayer());
        if (requestingPlayer)
        {
            data = new Param1<array<ref BountyPlayerData>>(bountiedPlayersData);
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "ReceiveBountiedPlayers", data, true, sender);
            GetNinjins_Bounty_SystemLogger().LogInfo("[MissionServer] Sent " + bountiedPlayersData.Count().ToString() + " bountied players to " + sender.GetName());
            if (g_BountyConfig && g_BountyConfig.UI)
            {
                posX = g_BountyConfig.UI.CountdownWidgetPositionX;
                posY = g_BountyConfig.UI.CountdownWidgetPositionY;
                width = g_BountyConfig.UI.CountdownWidgetWidth;
                height = g_BountyConfig.UI.CountdownWidgetHeight;
                bgColor = g_BountyConfig.UI.CountdownWidgetBackgroundColor;
                textColor = g_BountyConfig.UI.CountdownWidgetTextColor;
                uiData = new BountyUISettingsData(posX, posY, width, height, bgColor, textColor);
                uiParam = new Param1<BountyUISettingsData>(uiData);
                GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyConfigReloaded", uiParam, true, sender);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Sent UI settings to client: X=" + posX.ToString() + ", Y=" + posY.ToString() + ", Width=" + width.ToString() + ", Height=" + height.ToString() + ", BGColor=" + bgColor.ToString() + ", TextColor=" + textColor.ToString());
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
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminAction: Failed to read action parameter.");
            return;
        }
        action = actionParam.param1;
        player = PlayerBase.Cast(sender.GetPlayer());
        if (!player)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminAction: Player not found for identity: " + sender.GetName());
            return;
        }
        if (!player.IsBountyAdmin())
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminAction: Access denied for non-admin player: " + sender.GetName());
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
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
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    success = BountyManager.ApplyBountyToPlayer(targetPlayer, player, 0.0, "Admin test rule breaker bounty", BountyType.RULE_BREAKER);
                    if (success)
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Applied rule breaker bounty to " + targetPlayerName + " by admin " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Failed to apply rule breaker bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for ApplyTestRuleBreakerBounty");
            }
        }
        else if (action.IndexOf("AddBountySelectedPlayer:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("AddBountySelectedPlayer:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    success = BountyManager.ApplyBountyToPlayer(targetPlayer, player, 0.0, "Admin placed bounty", BountyType.PLACED);
                    if (success)
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Applied normal placed bounty to " + targetPlayerName + " by admin " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Failed to apply normal placed bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for AddBountySelectedPlayer");
            }
        }
        else if (action == "ClearBounty")
        {
            success = BountyManager.ClearBountyFromPlayer(player, player, "Admin cleared");
            if (success)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared bounty for " + sender.GetName());
            }
        }
        else if (action.IndexOf("ClearBountySelectedPlayer:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("ClearBountySelectedPlayer:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    success = BountyManager.ClearBountyFromPlayer(targetPlayer, player, "Admin cleared selected player");
                    if (success)
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared bounty for " + targetPlayerName + " by admin " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Failed to clear bounty for " + targetPlayerName + " (player may not have a bounty)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for ClearBountySelectedPlayer");
            }
        }
        else if (action == "ReloadConfigs")
        {
            BountyManager.ReloadAllConfigs(player);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Reloaded configs for " + sender.GetName());
        }
        else if (action.IndexOf("ClearAllCooldowns:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("ClearAllCooldowns:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    if (targetPlayer.IsBountyOnCooldown())
                    {
                        targetPlayer.ClearBountyCooldown();
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared cooldown for player " + targetPlayerName + " by admin " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Player " + targetPlayerName + " is not on cooldown (nothing to clear)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for ClearAllCooldowns");
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
                    if (onlinePlayer && onlinePlayer.IsBountyOnCooldown())
                    {
                        onlinePlayer.ClearBountyCooldown();
                        clearedCount = clearedCount + 1;
                        onlineIdentity = onlinePlayer.GetIdentity();
                        if (onlineIdentity)
                        {
                            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared cooldown for online player: " + onlineIdentity.GetName());
                        }
                    }
                }
            }
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared cooldowns for " + clearedCount.ToString() + " online player(s) by admin " + sender.GetName());
        }
        else if (action.IndexOf("ClearPlayerCooldown:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("ClearPlayerCooldown:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    if (targetPlayer.IsBountyOnCooldown())
                    {
                        targetPlayer.ClearBountyCooldown();
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Cleared cooldown for player " + targetPlayerName + " by admin " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Player " + targetPlayerName + " is not on cooldown (nothing to clear)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player not found: " + targetPlayerName);
                }
            }
        }
        else if (action.IndexOf("AddRewardPoint:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("AddRewardPoint:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    targetPlayer.AddPendingSuccessReward(1);
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Added reward point to " + targetPlayer.GetIdentity().GetName() + " by admin " + sender.GetName() + " (total pending: " + targetPlayer.GetTotalPendingRewardCount().ToString() + ")");
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for AddRewardPoint");
            }
        }
        else if (action.IndexOf("RemoveRewardPoint:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("RemoveRewardPoint:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer)
                {
                    if (targetPlayer.HasPendingRewards())
                    {
                        targetPlayer.RemovePendingSuccessReward(1);
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Removed success reward point from " + targetPlayer.GetIdentity().GetName() + " by admin " + sender.GetName() + " (remaining: " + targetPlayer.GetTotalPendingRewardCount().ToString() + ")");
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Player " + targetPlayer.GetIdentity().GetName() + " has no pending rewards to remove");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + targetPlayerName + " not found or not online");
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] No player name provided for RemoveRewardPoint");
            }
        }
        else if (action.IndexOf("AddToBlacklist:") == 0)
        {
            targetPlayerName = action;
            targetPlayerName.Replace("AddToBlacklist:", "");
            if (targetPlayerName != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerName);
                if (targetPlayer && targetPlayer.GetIdentity())
                {
                    playerGUID = targetPlayer.GetIdentity().GetId();
                    playerName = targetPlayer.GetIdentity().GetName();
                    entry = playerName + ":" + playerGUID;
                    alreadyBlacklisted = false;
                    if (g_BountyBlacklistConfig)
                    {
                        alreadyBlacklisted = g_BountyBlacklistConfig.IsBlacklisted(playerGUID);
                    }
                    if (!alreadyBlacklisted)
                    {
                        g_BountyBlacklistConfig.BlacklistedGUIDs.Insert(entry);
                        g_BountyBlacklistConfig.SaveConfig();
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Added " + playerName + " (" + playerGUID + ") to blacklist by admin " + sender.GetName());
                        blacklistResult = new Param1<array<string>>(g_BountyBlacklistConfig.BlacklistedGUIDs);
                        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", blacklistResult, true, sender);
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player " + playerName + " is already blacklisted");
                    }
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Player not found: " + actualPlayerName);
            }
        }
        else if (action.IndexOf("RemoveFromBlacklist:") == 0)
        {
            entry = action;
            entry.Replace("RemoveFromBlacklist:", "");
            if (entry != "" && g_BountyBlacklistConfig && g_BountyBlacklistConfig.BlacklistedGUIDs)
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
                for (i = g_BountyBlacklistConfig.BlacklistedGUIDs.Count() - 1; i >= 0; i--)
                {
                    existingEntry = g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
                    if (existingEntry.IndexOf(guidToRemove) >= 0)
                    {
                        g_BountyBlacklistConfig.BlacklistedGUIDs.Remove(i);
                        removed = true;
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminAction] Removed " + existingEntry + " from blacklist by admin " + sender.GetName());
                        break;
                    }
                }
                if (removed)
                {
                    g_BountyBlacklistConfig.SaveConfig();
                    blacklistResult = new Param1<array<string>>(g_BountyBlacklistConfig.BlacklistedGUIDs);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveBlacklist", blacklistResult, true, sender);
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminAction] Entry not found in blacklist: " + entry);
                }
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminAction: Unknown action: " + action);
        }
    }
    void BountyAdminUpdateConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<ref BountyConfig> configParam;
        BountyConfig updatedConfig;
        PlayerBase player;
        if (type != CallType.Server || !sender)
            return;
        if (!ctx.Read(configParam))
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminUpdateConfig: Failed to read config parameter.");
            return;
        }
        updatedConfig = configParam.param1;
        if (!updatedConfig)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminUpdateConfig: Config parameter is null.");
            return;
        }
        player = PlayerBase.Cast(sender.GetPlayer());
        if (!player)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminUpdateConfig: Player not found for identity: " + sender.GetName());
            return;
        }
        if (!player.IsBountyAdmin())
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminUpdateConfig: Access denied for non-admin player: " + sender.GetName());
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
            return;
        }
        if (g_BountyConfig)
        {
            if (updatedConfig.Core && g_BountyConfig.Core)
            {
                g_BountyConfig.Core.EnableBountySystem = updatedConfig.Core.EnableBountySystem;
                g_BountyConfig.Core.DisableSelfBounty = updatedConfig.Core.DisableSelfBounty;
                g_BountyConfig.Core.TeleportOutOfOwnTerritory = updatedConfig.Core.TeleportOutOfOwnTerritory;
                g_BountyConfig.Core.PauseBountyInTerritory = updatedConfig.Core.PauseBountyInTerritory;
                g_BountyConfig.Core.TeleportOutOfSafeZone = updatedConfig.Core.TeleportOutOfSafeZone;
                g_BountyConfig.Core.EnableAutomatedBountyPlacement = updatedConfig.Core.EnableAutomatedBountyPlacement;
                g_BountyConfig.Core.BountyCooldownSeconds = updatedConfig.Core.BountyCooldownSeconds;
                g_BountyConfig.Core.MaxBountiedPlayers = updatedConfig.Core.MaxBountiedPlayers;
                g_BountyConfig.Core.MinOnlinePlayersRequired = updatedConfig.Core.MinOnlinePlayersRequired;
                g_BountyConfig.Core.SkipBountyTokenRequired = updatedConfig.Core.SkipBountyTokenRequired;
                g_BountyConfig.Core.PlaceBountyTokenRequired = updatedConfig.Core.PlaceBountyTokenRequired;
                g_BountyConfig.Core.ResumeBountyDistanceFromTerritory = updatedConfig.Core.ResumeBountyDistanceFromTerritory;
                g_BountyConfig.Core.PausedBountyResumeCheckInterval = updatedConfig.Core.PausedBountyResumeCheckInterval;
                g_BountyConfig.Core.TeleportOutOfSafeZoneDistance = updatedConfig.Core.TeleportOutOfSafeZoneDistance;
                g_BountyConfig.Core.MinimumPlayerLifetimeSeconds = updatedConfig.Core.MinimumPlayerLifetimeSeconds;
                g_BountyConfig.Core.AutomatedBountyPlacementIntervalSeconds = updatedConfig.Core.AutomatedBountyPlacementIntervalSeconds;
            }
            if (updatedConfig.RuleBreaker && g_BountyConfig.RuleBreaker)
            {
                g_BountyConfig.RuleBreaker.EnableRuleBreakerHitThreshold = updatedConfig.RuleBreaker.EnableRuleBreakerHitThreshold;
                g_BountyConfig.RuleBreaker.EnablePvEToPvPRuleBreaker = updatedConfig.RuleBreaker.EnablePvEToPvPRuleBreaker;
                g_BountyConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty = updatedConfig.RuleBreaker.ClearPendingRewardsOnRuleBreakerBounty;
                g_BountyConfig.RuleBreaker.AllowPvEToPvEVictimKill = updatedConfig.RuleBreaker.AllowPvEToPvEVictimKill;
                g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds = updatedConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
                g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdTime = updatedConfig.RuleBreaker.RuleBreakerHitThresholdTime;
                g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits = updatedConfig.RuleBreaker.RuleBreakerHitThresholdWarningHits;
                g_BountyConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits = updatedConfig.RuleBreaker.RuleBreakerHitThresholdBountyHits;
                g_BountyConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits = updatedConfig.RuleBreaker.PvEToPvPInstantRuleBreakerHits;
                g_BountyConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease = updatedConfig.RuleBreaker.Expansion_EnableHardlineReputationDecrease;
                g_BountyConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount = updatedConfig.RuleBreaker.Expansion_HardlineReputationDecreaseAmount;
            }
            if (updatedConfig.PlacedBounty && g_BountyConfig.PlacedBounty)
            {
                g_BountyConfig.PlacedBounty.BountyDurationSeconds = updatedConfig.PlacedBounty.BountyDurationSeconds;
            }
            if (updatedConfig.Reward && g_BountyConfig.Reward)
            {
                g_BountyConfig.Reward.EnableSurvivalReward = updatedConfig.Reward.EnableSurvivalReward;
                g_BountyConfig.Reward.PvERuleBreakerGiveRewards = updatedConfig.Reward.PvERuleBreakerGiveRewards;
            }
            if (updatedConfig.Map && g_BountyConfig.Map)
            {
                g_BountyConfig.Map.BountyEnableMapDrawing = updatedConfig.Map.BountyEnableMapDrawing;
                g_BountyConfig.Map.BountyCircleReduceRadiusOverTime = updatedConfig.Map.BountyCircleReduceRadiusOverTime;
                g_BountyConfig.Map.BountyCircleIncreaseRadiusOverTime = updatedConfig.Map.BountyCircleIncreaseRadiusOverTime;
                g_BountyConfig.Map.BountyCircleRadius = updatedConfig.Map.BountyCircleRadius;
                g_BountyConfig.Map.BountyCircleMinRadius = updatedConfig.Map.BountyCircleMinRadius;
                g_BountyConfig.Map.BountyCircleColor = updatedConfig.Map.BountyCircleColor;
                g_BountyConfig.Map.BountyCircleDrawingWidth = updatedConfig.Map.BountyCircleDrawingWidth;
                g_BountyConfig.Map.BountyMapUpdateIntervalSeconds = updatedConfig.Map.BountyMapUpdateIntervalSeconds;
                g_BountyConfig.Map.BountyMapRequestCooldownSeconds = updatedConfig.Map.BountyMapRequestCooldownSeconds;
                g_BountyConfig.Map.BountyMapSyncIntervalSeconds = updatedConfig.Map.BountyMapSyncIntervalSeconds;
                g_BountyConfig.Map.BountyMapSyncIntervalNoBountiesSeconds = updatedConfig.Map.BountyMapSyncIntervalNoBountiesSeconds;
                g_BountyConfig.Map.BountyCircleOffsetMinMultiplier = updatedConfig.Map.BountyCircleOffsetMinMultiplier;
                g_BountyConfig.Map.BountyCircleOffsetMaxMultiplier = updatedConfig.Map.BountyCircleOffsetMaxMultiplier;
            }
            if (updatedConfig.UI && g_BountyConfig.UI)
            {
                g_BountyConfig.UI.CountdownWidgetPositionX = updatedConfig.UI.CountdownWidgetPositionX;
                g_BountyConfig.UI.CountdownWidgetPositionY = updatedConfig.UI.CountdownWidgetPositionY;
                g_BountyConfig.UI.CountdownWidgetWidth = updatedConfig.UI.CountdownWidgetWidth;
                g_BountyConfig.UI.CountdownWidgetHeight = updatedConfig.UI.CountdownWidgetHeight;
                g_BountyConfig.UI.CountdownWidgetBackgroundColor = updatedConfig.UI.CountdownWidgetBackgroundColor;
                g_BountyConfig.UI.CountdownWidgetTextColor = updatedConfig.UI.CountdownWidgetTextColor;
            }
            if (updatedConfig.Notifications && g_BountyConfig.Notifications)
            {
                if (updatedConfig.Notifications.PlacedBounty && g_BountyConfig.Notifications.PlacedBounty)
                {
                    if (updatedConfig.Notifications.PlacedBounty.Hunted && g_BountyConfig.Notifications.PlacedBounty.Hunted)
                    {
                        g_BountyConfig.Notifications.PlacedBounty.Hunted.Enabled = updatedConfig.Notifications.PlacedBounty.Hunted.Enabled;
                        g_BountyConfig.Notifications.PlacedBounty.Hunted.Title = updatedConfig.Notifications.PlacedBounty.Hunted.Title;
                        g_BountyConfig.Notifications.PlacedBounty.Hunted.Message = updatedConfig.Notifications.PlacedBounty.Hunted.Message;
                        g_BountyConfig.Notifications.PlacedBounty.Hunted.IconPath = updatedConfig.Notifications.PlacedBounty.Hunted.IconPath;
                    }
                    if (updatedConfig.Notifications.PlacedBounty.Expired && g_BountyConfig.Notifications.PlacedBounty.Expired)
                    {
                        g_BountyConfig.Notifications.PlacedBounty.Expired.Enabled = updatedConfig.Notifications.PlacedBounty.Expired.Enabled;
                        g_BountyConfig.Notifications.PlacedBounty.Expired.Title = updatedConfig.Notifications.PlacedBounty.Expired.Title;
                        g_BountyConfig.Notifications.PlacedBounty.Expired.Message = updatedConfig.Notifications.PlacedBounty.Expired.Message;
                        g_BountyConfig.Notifications.PlacedBounty.Expired.IconPath = updatedConfig.Notifications.PlacedBounty.Expired.IconPath;
                    }
                    if (updatedConfig.Notifications.PlacedBounty.SurvivalReward && g_BountyConfig.Notifications.PlacedBounty.SurvivalReward)
                    {
                        g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Enabled = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Enabled;
                        g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Title = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Title;
                        g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.Message = updatedConfig.Notifications.PlacedBounty.SurvivalReward.Message;
                        g_BountyConfig.Notifications.PlacedBounty.SurvivalReward.IconPath = updatedConfig.Notifications.PlacedBounty.SurvivalReward.IconPath;
                    }
                    if (updatedConfig.Notifications.PlacedBounty.KilledReward && g_BountyConfig.Notifications.PlacedBounty.KilledReward)
                    {
                        g_BountyConfig.Notifications.PlacedBounty.KilledReward.Enabled = updatedConfig.Notifications.PlacedBounty.KilledReward.Enabled;
                        g_BountyConfig.Notifications.PlacedBounty.KilledReward.Title = updatedConfig.Notifications.PlacedBounty.KilledReward.Title;
                        g_BountyConfig.Notifications.PlacedBounty.KilledReward.Message = updatedConfig.Notifications.PlacedBounty.KilledReward.Message;
                        g_BountyConfig.Notifications.PlacedBounty.KilledReward.IconPath = updatedConfig.Notifications.PlacedBounty.KilledReward.IconPath;
                    }
                }
                if (updatedConfig.Notifications.RuleBreaker && g_BountyConfig.Notifications.RuleBreaker)
                {
                    if (updatedConfig.Notifications.RuleBreaker.Hunted && g_BountyConfig.Notifications.RuleBreaker.Hunted)
                    {
                        g_BountyConfig.Notifications.RuleBreaker.Hunted.Enabled = updatedConfig.Notifications.RuleBreaker.Hunted.Enabled;
                        g_BountyConfig.Notifications.RuleBreaker.Hunted.Title = updatedConfig.Notifications.RuleBreaker.Hunted.Title;
                        g_BountyConfig.Notifications.RuleBreaker.Hunted.Message = updatedConfig.Notifications.RuleBreaker.Hunted.Message;
                        g_BountyConfig.Notifications.RuleBreaker.Hunted.IconPath = updatedConfig.Notifications.RuleBreaker.Hunted.IconPath;
                    }
                    if (updatedConfig.Notifications.RuleBreaker.HitWarning && g_BountyConfig.Notifications.RuleBreaker.HitWarning)
                    {
                        g_BountyConfig.Notifications.RuleBreaker.HitWarning.Enabled = updatedConfig.Notifications.RuleBreaker.HitWarning.Enabled;
                        g_BountyConfig.Notifications.RuleBreaker.HitWarning.Title = updatedConfig.Notifications.RuleBreaker.HitWarning.Title;
                        g_BountyConfig.Notifications.RuleBreaker.HitWarning.Message = updatedConfig.Notifications.RuleBreaker.HitWarning.Message;
                        g_BountyConfig.Notifications.RuleBreaker.HitWarning.IconPath = updatedConfig.Notifications.RuleBreaker.HitWarning.IconPath;
                    }
                    if (updatedConfig.Notifications.RuleBreaker.Expired && g_BountyConfig.Notifications.RuleBreaker.Expired)
                    {
                        g_BountyConfig.Notifications.RuleBreaker.Expired.Enabled = updatedConfig.Notifications.RuleBreaker.Expired.Enabled;
                        g_BountyConfig.Notifications.RuleBreaker.Expired.Title = updatedConfig.Notifications.RuleBreaker.Expired.Title;
                        g_BountyConfig.Notifications.RuleBreaker.Expired.Message = updatedConfig.Notifications.RuleBreaker.Expired.Message;
                        g_BountyConfig.Notifications.RuleBreaker.Expired.IconPath = updatedConfig.Notifications.RuleBreaker.Expired.IconPath;
                    }
                    if (updatedConfig.Notifications.RuleBreaker.SurvivalReward && g_BountyConfig.Notifications.RuleBreaker.SurvivalReward)
                    {
                        g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Enabled = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Enabled;
                        g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Title = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Title;
                        g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.Message = updatedConfig.Notifications.RuleBreaker.SurvivalReward.Message;
                        g_BountyConfig.Notifications.RuleBreaker.SurvivalReward.IconPath = updatedConfig.Notifications.RuleBreaker.SurvivalReward.IconPath;
                    }
                    if (updatedConfig.Notifications.RuleBreaker.KilledReward && g_BountyConfig.Notifications.RuleBreaker.KilledReward)
                    {
                        g_BountyConfig.Notifications.RuleBreaker.KilledReward.Enabled = updatedConfig.Notifications.RuleBreaker.KilledReward.Enabled;
                        g_BountyConfig.Notifications.RuleBreaker.KilledReward.Title = updatedConfig.Notifications.RuleBreaker.KilledReward.Title;
                        g_BountyConfig.Notifications.RuleBreaker.KilledReward.Message = updatedConfig.Notifications.RuleBreaker.KilledReward.Message;
                        g_BountyConfig.Notifications.RuleBreaker.KilledReward.IconPath = updatedConfig.Notifications.RuleBreaker.KilledReward.IconPath;
                    }
                }
                if (updatedConfig.Notifications.Other && g_BountyConfig.Notifications.Other)
                {
                    if (updatedConfig.Notifications.Other.InsufficientTokens && g_BountyConfig.Notifications.Other.InsufficientTokens)
                    {
                        g_BountyConfig.Notifications.Other.InsufficientTokens.Enabled = updatedConfig.Notifications.Other.InsufficientTokens.Enabled;
                        g_BountyConfig.Notifications.Other.InsufficientTokens.Title = updatedConfig.Notifications.Other.InsufficientTokens.Title;
                        g_BountyConfig.Notifications.Other.InsufficientTokens.Message = updatedConfig.Notifications.Other.InsufficientTokens.Message;
                        g_BountyConfig.Notifications.Other.InsufficientTokens.IconPath = updatedConfig.Notifications.Other.InsufficientTokens.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.SkipBountyNoPlayers && g_BountyConfig.Notifications.Other.SkipBountyNoPlayers)
                    {
                        g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Enabled = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Enabled;
                        g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Title = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Title;
                        g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.Message = updatedConfig.Notifications.Other.SkipBountyNoPlayers.Message;
                        g_BountyConfig.Notifications.Other.SkipBountyNoPlayers.IconPath = updatedConfig.Notifications.Other.SkipBountyNoPlayers.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.SkipBountySuccess && g_BountyConfig.Notifications.Other.SkipBountySuccess)
                    {
                        g_BountyConfig.Notifications.Other.SkipBountySuccess.Enabled = updatedConfig.Notifications.Other.SkipBountySuccess.Enabled;
                        g_BountyConfig.Notifications.Other.SkipBountySuccess.Title = updatedConfig.Notifications.Other.SkipBountySuccess.Title;
                        g_BountyConfig.Notifications.Other.SkipBountySuccess.Message = updatedConfig.Notifications.Other.SkipBountySuccess.Message;
                        g_BountyConfig.Notifications.Other.SkipBountySuccess.IconPath = updatedConfig.Notifications.Other.SkipBountySuccess.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.BountySkipped && g_BountyConfig.Notifications.Other.BountySkipped)
                    {
                        g_BountyConfig.Notifications.Other.BountySkipped.Enabled = updatedConfig.Notifications.Other.BountySkipped.Enabled;
                        g_BountyConfig.Notifications.Other.BountySkipped.Title = updatedConfig.Notifications.Other.BountySkipped.Title;
                        g_BountyConfig.Notifications.Other.BountySkipped.Message = updatedConfig.Notifications.Other.BountySkipped.Message;
                        g_BountyConfig.Notifications.Other.BountySkipped.IconPath = updatedConfig.Notifications.Other.BountySkipped.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.RewardHandsNotFree && g_BountyConfig.Notifications.Other.RewardHandsNotFree)
                    {
                        g_BountyConfig.Notifications.Other.RewardHandsNotFree.Enabled = updatedConfig.Notifications.Other.RewardHandsNotFree.Enabled;
                        g_BountyConfig.Notifications.Other.RewardHandsNotFree.Title = updatedConfig.Notifications.Other.RewardHandsNotFree.Title;
                        g_BountyConfig.Notifications.Other.RewardHandsNotFree.Message = updatedConfig.Notifications.Other.RewardHandsNotFree.Message;
                        g_BountyConfig.Notifications.Other.RewardHandsNotFree.IconPath = updatedConfig.Notifications.Other.RewardHandsNotFree.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.PlayerOnCooldown && g_BountyConfig.Notifications.Other.PlayerOnCooldown)
                    {
                        g_BountyConfig.Notifications.Other.PlayerOnCooldown.Enabled = updatedConfig.Notifications.Other.PlayerOnCooldown.Enabled;
                        g_BountyConfig.Notifications.Other.PlayerOnCooldown.Title = updatedConfig.Notifications.Other.PlayerOnCooldown.Title;
                        g_BountyConfig.Notifications.Other.PlayerOnCooldown.Message = updatedConfig.Notifications.Other.PlayerOnCooldown.Message;
                        g_BountyConfig.Notifications.Other.PlayerOnCooldown.IconPath = updatedConfig.Notifications.Other.PlayerOnCooldown.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.PlayerInSafeZone && g_BountyConfig.Notifications.Other.PlayerInSafeZone)
                    {
                        g_BountyConfig.Notifications.Other.PlayerInSafeZone.Enabled = updatedConfig.Notifications.Other.PlayerInSafeZone.Enabled;
                        g_BountyConfig.Notifications.Other.PlayerInSafeZone.Title = updatedConfig.Notifications.Other.PlayerInSafeZone.Title;
                        g_BountyConfig.Notifications.Other.PlayerInSafeZone.Message = updatedConfig.Notifications.Other.PlayerInSafeZone.Message;
                        g_BountyConfig.Notifications.Other.PlayerInSafeZone.IconPath = updatedConfig.Notifications.Other.PlayerInSafeZone.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.BountyPersisted && g_BountyConfig.Notifications.Other.BountyPersisted)
                    {
                        g_BountyConfig.Notifications.Other.BountyPersisted.Enabled = updatedConfig.Notifications.Other.BountyPersisted.Enabled;
                        g_BountyConfig.Notifications.Other.BountyPersisted.Title = updatedConfig.Notifications.Other.BountyPersisted.Title;
                        g_BountyConfig.Notifications.Other.BountyPersisted.Message = updatedConfig.Notifications.Other.BountyPersisted.Message;
                        g_BountyConfig.Notifications.Other.BountyPersisted.IconPath = updatedConfig.Notifications.Other.BountyPersisted.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.TeleportedOutOfTerritory && g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory)
                    {
                        g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Enabled;
                        g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Title = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Title;
                        g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.Message = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.Message;
                        g_BountyConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath = updatedConfig.Notifications.Other.TeleportedOutOfTerritory.IconPath;
                    }
                    if (updatedConfig.Notifications.Other.BountyPausedInTerritory && g_BountyConfig.Notifications.Other.BountyPausedInTerritory)
                    {
                        g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Enabled = updatedConfig.Notifications.Other.BountyPausedInTerritory.Enabled;
                        g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Title = updatedConfig.Notifications.Other.BountyPausedInTerritory.Title;
                        g_BountyConfig.Notifications.Other.BountyPausedInTerritory.Message = updatedConfig.Notifications.Other.BountyPausedInTerritory.Message;
                        g_BountyConfig.Notifications.Other.BountyPausedInTerritory.IconPath = updatedConfig.Notifications.Other.BountyPausedInTerritory.IconPath;
                    }
                }
            }
            if (updatedConfig.Broadcasts && g_BountyConfig.Broadcasts)
            {
                if (updatedConfig.Broadcasts.PlacedBounty && g_BountyConfig.Broadcasts.PlacedBounty)
                {
                    g_BountyConfig.Broadcasts.PlacedBounty.Enabled = updatedConfig.Broadcasts.PlacedBounty.Enabled;
                    g_BountyConfig.Broadcasts.PlacedBounty.Title = updatedConfig.Broadcasts.PlacedBounty.Title;
                    g_BountyConfig.Broadcasts.PlacedBounty.Message = updatedConfig.Broadcasts.PlacedBounty.Message;
                    g_BountyConfig.Broadcasts.PlacedBounty.IconPath = updatedConfig.Broadcasts.PlacedBounty.IconPath;
                }
                if (updatedConfig.Broadcasts.RuleBreaker && g_BountyConfig.Broadcasts.RuleBreaker)
                {
                    g_BountyConfig.Broadcasts.RuleBreaker.Enabled = updatedConfig.Broadcasts.RuleBreaker.Enabled;
                    g_BountyConfig.Broadcasts.RuleBreaker.Title = updatedConfig.Broadcasts.RuleBreaker.Title;
                    g_BountyConfig.Broadcasts.RuleBreaker.Message = updatedConfig.Broadcasts.RuleBreaker.Message;
                    g_BountyConfig.Broadcasts.RuleBreaker.IconPath = updatedConfig.Broadcasts.RuleBreaker.IconPath;
                }
            }
            g_BountyConfig.ValidateConfig();
            g_BountyConfig.SaveConfig();
            BountyManager.ReloadAllConfigs(player);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyAdminUpdateConfig] Config updated and reloaded by admin: " + sender.GetName());
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyAdminUpdateConfig] g_BountyConfig is null - cannot update config!");
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
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminRequestConfig: Player not found for identity: " + sender.GetName());
            return;
        }
        if (!player.IsBountyAdmin())
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminRequestConfig: Access denied for non-admin player: " + sender.GetName());
            return;
        }
        if (g_BountyConfig)
        {
            GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceiveConfig", new Param1<ref BountyConfig>(g_BountyConfig), true, sender);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] BountyAdminRequestConfig: Sent config to admin: " + sender.GetName());
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminRequestConfig: g_BountyConfig is null - cannot send config!");
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
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BoardBountyAction: Failed to read action parameter.");
            return;
        }
        action = actionParam.param1;
        player = PlayerBase.Cast(sender.GetPlayer());
        if (!player)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BoardBountyAction: Player not found for identity: " + sender.GetName());
            return;
        }
        if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.IsBlacklisted(sender.GetId()))
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BoardBountyAction: Blacklisted player " + sender.GetName() + " tried to use bounty board action: " + action);
            return;
        }
        bool success;
        string targetPlayerName = "";
        string targetPlayerIdentifier = "";
        PlayerBase targetPlayer = null;
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
            if (!player.HasBounty())
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to skip bounty but doesn't have one");
                return;
            }
            bountyType = player.GetBountyType();
            newDuration = 0.0;
            if (g_BountyConfig)
            {
                if (bountyType == BountyType.RULE_BREAKER)
                {
                    newDuration = g_BountyConfig.RuleBreaker.BountyRuleBreakerDurationSeconds;
                }
                else
                {
                    newDuration = g_BountyConfig.PlacedBounty.BountyDurationSeconds;
                }
            }
            if (newDuration <= 0.0)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Cannot skip bounty - invalid duration from config");
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
                if (candidatePlayer.HasBounty())
                    continue;
                if (candidatePlayer.IsBountyOnCooldown())
                    continue;
                availablePlayers.Insert(candidatePlayer);
            }
            if (availablePlayers.Count() == 0)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] No available players to transfer bounty to for " + sender.GetName() + " - tokens not consumed");
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS, sender);
                return;
            }
            tokensRequired = 0;
            if (g_BountyConfig)
            {
                tokensRequired = g_BountyConfig.Core.SkipBountyTokenRequired;
            }
            if (tokensRequired > 0)
            {
                totalTokenQuantity = GetPlayerTokenCount(player, foundTokens);
                if (totalTokenQuantity < tokensRequired)
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to skip bounty but doesn't have enough tokens. Required: " + tokensRequired.ToString() + ", Found: " + totalTokenQuantity.ToString());
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS, sender, "", "", 0.0, 0, 0, 0, tokensRequired, totalTokenQuantity);
                    return;
                }
            }
            randomIndex = Math.RandomInt(0, availablePlayers.Count());
            targetPlayer = availablePlayers.Get(randomIndex);
            if (!targetPlayer || !targetPlayer.GetIdentity())
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to get target player for bounty transfer");
                return;
            }
            targetPlayerName = targetPlayer.GetIdentity().GetName();
            BountyManager.ClearBountyFromPlayer(player, player, "Skipped - transferred to " + targetPlayerName, true);
            success = BountyManager.ApplyBountyToPlayer(targetPlayer, player, newDuration, "Transferred from " + skippingPlayerName + " (skipped)", bountyType, true);
            if (success)
            {
                if (tokensRequired > 0)
                {
                    tokensRemoved = ConsumePlayerTokens(player, tokensRequired, totalTokenQuantity);
                    if (tokensRemoved < tokensRequired)
                    {
                        GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to remove all required skip tokens after transfer. Required: " + tokensRequired.ToString() + ", Removed: " + tokensRemoved.ToString());
                        BountyManager.ClearBountyFromPlayer(targetPlayer, player, "Skip token rollback", true);
                        BountyManager.ApplyBountyToPlayer(player, player, newDuration, "Skip token rollback", bountyType, true);
                        return;
                    }
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Removed " + tokensRemoved.ToString() + " tokens from player " + sender.GetName());
                }
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_BOUNTY_SKIPPED, sender);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Transferred bounty from " + skippingPlayerName + " to " + targetPlayerName + " (skip action). New Duration: " + newDuration.ToString() + "s, BountyType: " + bountyType.ToString());
                BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_SKIP_SUCCESS, sender, targetPlayerName);
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to transfer bounty to " + targetPlayerName + " (system may be disabled or player lifetime not reached)");
            }
        }
        else if (action.IndexOf("PlaceBountyOnPlayer:") == 0)
        {
            tokensRequired = 0;
            tokensRemoved = 0;
            if (g_BountyConfig)
            {
                tokensRequired = g_BountyConfig.Core.PlaceBountyTokenRequired;
            }
            if (tokensRequired > 0)
            {
                totalTokenQuantity = GetPlayerTokenCount(player, foundTokens);
                if (totalTokenQuantity < tokensRequired)
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to place bounty but doesn't have enough tokens. Required: " + tokensRequired.ToString() + ", Found: " + totalTokenQuantity.ToString());
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS, sender, "", "", 0.0, 0, 0, 0, tokensRequired, totalTokenQuantity);
                    return;
                }
            }
            targetPlayerIdentifier = action;
            targetPlayerIdentifier.Replace("PlaceBountyOnPlayer:", "");
            if (targetPlayerIdentifier != "")
            {
                targetPlayer = FindOnlinePlayerByIdentifier(targetPlayerIdentifier);
                if (targetPlayer)
                {
                    actualPlayerName = targetPlayer.GetIdentity().GetName();
                    if (targetPlayer.IsBountyOnCooldown())
                    {
                        float cooldownRemaining = targetPlayer.GetBountyCooldownRemaining();
                        int cooldownSeconds = Math.Ceil(cooldownRemaining);
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Cannot place bounty on " + actualPlayerName + " - player is on cooldown (" + cooldownSeconds.ToString() + " seconds remaining)");
                        BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN, sender, actualPlayerName, "", 0.0, 0, 0, 0, 0, 0, cooldownSeconds);
                        return;
                    }
                    success = BountyManager.ApplyBountyToPlayer(targetPlayer, player, 0.0, "Bounty placed by " + sender.GetName() + " via bounty board", BountyType.PLACED);
                    if (success)
                    {
                        if (tokensRequired > 0)
                        {
                            tokensRemoved = ConsumePlayerTokens(player, tokensRequired, totalTokenQuantity);
                            if (tokensRemoved < tokensRequired)
                            {
                                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to remove all required placement tokens after applying bounty. Required: " + tokensRequired.ToString() + ", Removed: " + tokensRemoved.ToString());
                                BountyManager.ClearBountyFromPlayer(targetPlayer, player, "Placement token rollback", true);
                                return;
                            }
                            GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Removed " + tokensRemoved.ToString() + " tokens from player " + sender.GetName() + " for placing bounty");
                        }
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Placed bounty on " + actualPlayerName + " by " + sender.GetName());
                    }
                    else
                    {
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Failed to place bounty on " + actualPlayerName + " (system may be disabled or player lifetime not reached)");
                    }
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player not found: " + actualPlayerName);
                }
            }
        }
        else if (action == "ClaimRewards")
        {
            if (!player.HasPendingRewards())
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to claim rewards but has no pending rewards");
                return;
            }
            if (player.IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " is a rule breaker and tried to claim rewards, but PvERuleBreakerGiveRewards = 0. Blocking claim.");
                player.ClearPendingRewards();
                return;
            }
            bool spawnSuccess = false;
            if (player.HasPendingRewards())
            {
                spawnSuccess = BountyManager.SpawnBountyRewardGiftBox(player, false, false);
                if (spawnSuccess)
                {
                    player.ClaimPendingSuccessReward();
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Successfully claimed 1 success reward (chest only, no currency) for " + sender.GetName() + " (remaining: " + player.GetPendingSuccessRewardCount().ToString() + ")");
                    #ifdef EXPANSIONMODHARDLINE
                    if (g_BountySuccessRewardConfig && g_BountySuccessRewardConfig.EnableHardlineReputationReward && g_BountySuccessRewardConfig.HardlineReputationRewardAmount > 0)
                    {
                        player.Expansion_AddReputation(g_BountySuccessRewardConfig.HardlineReputationRewardAmount);
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Gave Hardline reputation reward of " + g_BountySuccessRewardConfig.HardlineReputationRewardAmount.ToString() + " to " + sender.GetName() + " for claiming success reward.");
                    }
                    #endif
                    updatedClaimAmount = player.GetTotalPendingRewardCount();
                    claimAmountResult = new Param1<int>(updatedClaimAmount);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", claimAmountResult, true, sender);
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to claim success reward for " + sender.GetName() + " (hands not free or spawn failed) - keeping pending reward");
                }
            }
        }
        else if (action == "ClaimCurrencyRewards")
        {
            if (!player.HasPendingRewards())
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " tried to claim currency rewards but has no pending rewards");
                return;
            }
            if (player.IsRuleBreakerBounty() && g_BountyConfig && g_BountyConfig.Reward && !g_BountyConfig.Reward.PvERuleBreakerGiveRewards)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Player " + sender.GetName() + " is a rule breaker and tried to claim currency rewards, but PvERuleBreakerGiveRewards = 0. Blocking claim.");
                player.ClearPendingRewards();
                return;
            }
            bool currencySuccess = false;
            if (player.HasPendingRewards())
            {
                currencySuccess = BountyManager.GiveCurrencyRewardsOnly(player, false);
                if (currencySuccess)
                {
                    player.ClaimPendingSuccessReward();
                    GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Successfully claimed 1 success reward currency for " + sender.GetName() + " (remaining: " + player.GetPendingSuccessRewardCount().ToString() + ")");
                    #ifdef EXPANSIONMODHARDLINE
                    if (g_BountySuccessRewardConfig && g_BountySuccessRewardConfig.EnableHardlineReputationReward && g_BountySuccessRewardConfig.HardlineReputationRewardAmount > 0)
                    {
                        player.Expansion_AddReputation(g_BountySuccessRewardConfig.HardlineReputationRewardAmount);
                        GetNinjins_Bounty_SystemLogger().LogInfo("[BoardBountyAction] Gave Hardline reputation reward of " + g_BountySuccessRewardConfig.HardlineReputationRewardAmount.ToString() + " to " + sender.GetName() + " for claiming success reward currency.");
                    }
                    #endif
                    updatedClaimAmount = player.GetTotalPendingRewardCount();
                    claimAmountResult = new Param1<int>(updatedClaimAmount);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", claimAmountResult, true, sender);
                }
                else
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BoardBountyAction] Failed to claim success reward currency for " + sender.GetName() + " (no currency configured) - keeping pending reward");
                }
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BoardBountyAction: Unknown action: " + action);
        }
    }
    string FormatCooldownTime(int totalSeconds)
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
        if (g_BountyConfig && g_BountyConfig.Core && g_BountyConfig.Core.DisableSelfBounty)
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
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Excluding requesting player from online list (DisableSelfBounty = true): " + requestingPlayerName);
                continue;
            }
            displayName = playerName;
            if (player.IsBountyOnCooldown())
            {
                cooldownRemaining = player.GetBountyCooldownRemaining();
                cooldownSeconds = Math.Ceil(cooldownRemaining);
                formattedCooldown = FormatCooldownTime(cooldownSeconds);
                displayName = playerName + " CD:" + formattedCooldown;
            }
            playerList.Insert(BuildPlayerListEntry(displayName, playerId));
        }
        result = new Param1<array<string>>(playerList);
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveOnlinePlayers", result, true, sender);
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Sent online players list to " + requestingPlayerName + ": " + playerList.Count().ToString() + " players (excludeSelf: " + excludeSelf.ToString() + ")");
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
        if (!requestingPlayer.IsBountyAdmin())
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminRequestPlayers: Access denied for non-admin player: " + sender.GetName());
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
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
            if (player.IsBountyOnCooldown())
            {
                cooldownRemaining = player.GetBountyCooldownRemaining();
                cooldownSeconds = Math.Ceil(cooldownRemaining);
                formattedCooldown = FormatCooldownTime(cooldownSeconds);
                displayName = playerName + " CD:" + formattedCooldown;
            }
            else
            {
                displayName = playerName + " (No Cooldown)";
            }
            playerList.Insert(BuildPlayerListEntry(displayName, playerId));
        }
        result = new Param1<array<string>>(playerList);
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyAdminReceivePlayers", result, true, sender);
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Sent admin players list to " + requestingPlayerName + ": " + playerList.Count().ToString() + " players");
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
        totalClaimAmount = requestingPlayer.GetTotalPendingRewardCount();
        result = new Param1<int>(totalClaimAmount);
        GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyReceiveClaimAmount", result, true, sender);
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Sent claim amount to " + sender.GetName() + ": " + totalClaimAmount.ToString());
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
        if (!requestingPlayer.IsBountyAdmin())
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyModule] BountyAdminRequestBlacklist: Access denied for non-admin player: " + sender.GetName());
            BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED, sender);
            return;
        }
        blacklistList = new array<string>();
        if (g_BountyBlacklistConfig && g_BountyBlacklistConfig.BlacklistedGUIDs)
        {
            players = new array<Man>();
            g_Game.GetPlayers(players);
            for (i = 0; i < g_BountyBlacklistConfig.BlacklistedGUIDs.Count(); i++)
            {
                entry = g_BountyBlacklistConfig.BlacklistedGUIDs.Get(i);
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
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyModule] Sent blacklisted players list to " + sender.GetName() + ": " + blacklistList.Count().ToString() + " players");
    }
}