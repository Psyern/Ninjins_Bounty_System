class BountyRewardContainerHelper
{
    private static void ApplyQuantityToItem(ItemBase item, int amount, float quantMin, float quantMax, string itemName)
    {
        Magazine mag;
        float quantityAbsolute;
        int maxAmmo;
        int maxEnergy;
        float energyNormalized;
        int maxQuantity;
        float quantityNormalized;
        if (!item || item.GetQuantityMax() <= 0)
            return;
        if (amount > 0)
        {
            if (Class.CastTo(mag, item))
            {
                maxAmmo = mag.GetAmmoMax();
                if (amount > maxAmmo)
                    amount = maxAmmo;
                mag.ServerSetAmmoCount(amount);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set magazine ammo (Amount): " + itemName + " x" + amount.ToString());
            }
            else if (item.HasEnergyManager())
            {
                maxEnergy = item.GetQuantityMax();
                energyNormalized = 0.0;
                if (maxEnergy > 0)
                {
                    energyNormalized = Math.Clamp((float)amount / (float)maxEnergy, 0.0, 1.0);
                }
                item.GetCompEM().SetEnergy0To1(energyNormalized);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set energy (Amount): " + itemName + " at " + (energyNormalized * 100.0).ToString() + "%");
            }
            else if (item.HasQuantity())
            {
                maxQuantity = item.GetQuantityMax();
                if (amount > maxQuantity)
                    amount = maxQuantity;
                if (amount <= 0 && item.ConfigGetBool("varQuantityDestroyOnMin"))
                    amount = 1;
                item.SetQuantity(amount);
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set quantity (Amount): " + itemName + " x" + amount.ToString());
            }
            return;
        }
        quantityNormalized = 0.0;
        if (quantMin > 0.0 && quantMax > 0.0 && quantMax >= quantMin)
            quantityNormalized = Math.RandomFloat(quantMin, quantMax);
        else if (quantMin > 0.0)
            quantityNormalized = quantMin;
        else if (quantMax > 0.0)
            quantityNormalized = quantMax;
        if (quantityNormalized <= 0.0)
            return;
        if (quantityNormalized > 1.0) quantityNormalized = 1.0;
        if (quantityNormalized < 0.0) quantityNormalized = 0.0;
        if (Class.CastTo(mag, item))
        {
            quantityAbsolute = Math.Round(Math.Lerp(0, mag.GetAmmoMax(), quantityNormalized));
            mag.ServerSetAmmoCount(quantityAbsolute);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set magazine ammo: " + itemName + " x" + quantityAbsolute.ToString() + " (" + (quantityNormalized * 100.0).ToString() + "%)");
        }
        else if (item.HasEnergyManager())
        {
            item.GetCompEM().SetEnergy0To1(quantityNormalized);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set energy: " + itemName + " at " + (quantityNormalized * 100.0).ToString() + "%");
        }
        else if (item.HasQuantity())
        {
            quantityAbsolute = Math.Round(Math.Lerp(0, item.GetQuantityMax(), quantityNormalized));
            if (quantityAbsolute <= 0 && item.ConfigGetBool("varQuantityDestroyOnMin"))
                quantityAbsolute = 1;
            item.SetQuantity(quantityAbsolute);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set quantity: " + itemName + " x" + quantityAbsolute.ToString() + " (" + (quantityNormalized * 100.0).ToString() + "%)");
        }
    }
    private static void ApplyHealthToItem(EntityAI item, float healthMin, float healthMax, string itemName, bool applyToAttachments = false)
    {
        float healthNormalized;
        float maxHealth;
        float healthAbsolute;
        TStringArray dmgZones;
        string dmgZone;
        int i;
        EntityAI attachment;
        int attachIdx;
        float attachMaxHealth;
        TStringArray attachDmgZones;
        string attachDmgZone;
        int j;
        if (!item || (healthMin <= 0.0 && healthMax <= 0.0))
            return;
        healthNormalized = 0.0;
        if (healthMin > 0.0 && healthMax > 0.0 && healthMax >= healthMin)
            healthNormalized = Math.RandomFloat(healthMin, healthMax);
        else if (healthMin > 0.0)
            healthNormalized = healthMin;
        else if (healthMax > 0.0)
            healthNormalized = healthMax;
        if (healthNormalized <= 0.0)
            return;
        if (healthNormalized > 1.0) healthNormalized = 1.0;
        if (healthNormalized < 0.0) healthNormalized = 0.0;
        maxHealth = MiscGameplayFunctions.GetTypeMaxGlobalHealth(item.GetType());
        if (maxHealth <= 0.0)
            return;
        healthAbsolute = maxHealth * healthNormalized;
        item.SetHealth("", "", healthAbsolute);
        dmgZones = {};
        item.GetDamageZones(dmgZones);
        for (i = 0; i < dmgZones.Count(); i++)
        {
            dmgZone = dmgZones.Get(i);
            item.SetHealth01(dmgZone, "Health", healthNormalized);
        }
        if (applyToAttachments && item.GetInventory())
        {
            for (attachIdx = 0; attachIdx < item.GetInventory().AttachmentCount(); attachIdx++)
            {
                attachment = item.GetInventory().GetAttachmentFromIndex(attachIdx);
                if (attachment)
                {
                    attachMaxHealth = MiscGameplayFunctions.GetTypeMaxGlobalHealth(attachment.GetType());
                    if (attachMaxHealth > 0.0)
                    {
                        attachment.SetHealth("", "", attachMaxHealth * healthNormalized);
                        attachDmgZones = {};
                        attachment.GetDamageZones(attachDmgZones);
                        for (j = 0; j < attachDmgZones.Count(); j++)
                        {
                            attachDmgZone = attachDmgZones.Get(j);
                            attachment.SetHealth01(attachDmgZone, "Health", healthNormalized);
                        }
                    }
                }
            }
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set health: " + itemName + " at " + (healthNormalized * 100.0).ToString() + "% (" + healthAbsolute.ToString() + "/" + maxHealth.ToString() + ")");
    }
    private static void ProcessAttachmentsRecursive(EntityAI parentEntity, array<ref BountyRewardAttachment> attachmentConfigs, string parentItemName, int depth)
    {
        if (!parentEntity || !attachmentConfigs || attachmentConfigs.Count() == 0)
            return;
        int j;
        ItemBase attachmentItemBase;
        EntityAI attachment;
        BountyRewardAttachment attachmentConfig;
        for (j = 0; j < attachmentConfigs.Count(); j++)
        {
            attachmentConfig = attachmentConfigs.Get(j);
            if (!attachmentConfig || attachmentConfig.ItemClassName == "")
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Invalid attachment config at index " + j.ToString() + " for " + parentItemName);
                continue;
            }
            float randomChance = Math.RandomFloat(0.0, 100.0);
            if (randomChance > attachmentConfig.SpawnChance)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Attachment " + attachmentConfig.ItemClassName + " failed spawn chance (" + randomChance.ToString() + " > " + attachmentConfig.SpawnChance.ToString() + "). Skipping.");
                continue;
            }
            attachment = parentEntity.GetInventory().CreateInInventory(attachmentConfig.ItemClassName);
            if (!attachment)
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Failed to create attachment: " + attachmentConfig.ItemClassName + " for " + parentItemName);
                continue;
            }
            attachmentItemBase = ItemBase.Cast(attachment);
            if (attachmentItemBase)
            {
                ApplyQuantityToItem(attachmentItemBase, attachmentConfig.Amount, attachmentConfig.QuantMin, attachmentConfig.QuantMax, attachmentConfig.ItemClassName);
            }
            ApplyHealthToItem(attachment, attachmentConfig.HealthMin, attachmentConfig.HealthMax, attachmentConfig.ItemClassName, false);
            attachment.SetSynchDirty();
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Attached " + attachmentConfig.ItemClassName + " to " + parentItemName + " (depth: " + depth.ToString() + ")");
            if (attachmentConfig.Attachments && attachmentConfig.Attachments.Count() > 0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Processing " + attachmentConfig.Attachments.Count().ToString() + " nested attachment configs for " + attachmentConfig.ItemClassName);
                ProcessAttachmentsRecursive(attachment, attachmentConfig.Attachments, attachmentConfig.ItemClassName, depth + 1);
            }
        }
    }
    static void PopulateContainer(EntityAI container, array<ref BountyRewardItem> rewardItems, bool ruinedContainer = true)
    {
        CargoBase cargo;
        int i;
        int j;
        int zoneIdx;
        int attachIdx;
        int attachZoneIdx;
        float quantityAbsolute;
        float quantityNormalized;
        float healthNormalized;
        float maxHealth;
        float healthAbsolute;
        float attachmentMaxHealth;
        float attachmentHealth;
        float attachmentHealthAbsolute;
        Magazine mag;
        ItemBase rewardItemBase;
        ItemBase attachmentItemBase;
        BountyRewardItem rewardItem;
        BountyRewardAttachment attachmentConfig;
        EntityAI rewardEntity;
        EntityAI attachment;
        InventoryLocation tempLocation;
        EntityAI tempItem;
        TStringArray dmgZones;
        TStringArray attachDmgZones;
        string dmgZone;
        string attachDmgZone;
        string addedItemsList;
        string failedItemsList;
        int itemsAddedCount;
        int itemsFailedCount;
        TStringArray itemsAdded;
        TStringArray itemsFailed;
        if (!IsMissionHost())
            return;
        if (!container)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Container is null!");
            return;
        }
        if (!rewardItems || rewardItems.Count() == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] No reward items to add!");
            return;
        }
        cargo = container.GetInventory().GetCargo();
        if (!cargo)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Container has no cargo! Class: " + container.GetType());
            return;
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Adding " + rewardItems.Count().ToString() + " reward items to container: " + container.GetType());
        itemsAddedCount = 0;
        itemsFailedCount = 0;
        itemsAdded = new TStringArray();
        itemsFailed = new TStringArray();
        for (i = 0; i < rewardItems.Count(); i++)
        {
            rewardItem = rewardItems.Get(i);
            if (!rewardItem || rewardItem.ItemClassName == "")
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Invalid reward item at index " + i.ToString());
                continue;
            }
            tempItem = EntityAI.Cast(g_Game.CreateObject(rewardItem.ItemClassName, vector.Zero, false, true));
            if (!tempItem)
            {
                itemsFailedCount++;
                itemsFailed.Insert(rewardItem.ItemClassName + " (class not found)");
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Item class not found: " + rewardItem.ItemClassName + ". Skipping item.");
                continue;
            }
            tempLocation = new InventoryLocation;
            bool canFit = container.GetInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.CARGO, tempLocation);
            if (!canFit)
            {
                itemsFailedCount++;
                itemsFailed.Insert(rewardItem.ItemClassName + " (no space in cargo)");
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] No space in cargo for item: " + rewardItem.ItemClassName + ". Container may be full. Skipping item.");
                g_Game.ObjectDelete(tempItem);
                continue;
            }
            g_Game.ObjectDelete(tempItem);
            rewardEntity = container.GetInventory().CreateEntityInCargo(rewardItem.ItemClassName);
            if (!rewardEntity)
            {
                itemsFailedCount++;
                itemsFailed.Insert(rewardItem.ItemClassName + " (failed to create in cargo)");
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Failed to create reward item in cargo (may be out of space): " + rewardItem.ItemClassName);
                continue;
            }
            itemsAddedCount++;
            itemsAdded.Insert(rewardItem.ItemClassName);
            rewardItemBase = ItemBase.Cast(rewardEntity);
            if (rewardItemBase)
            {
                ApplyQuantityToItem(rewardItemBase, rewardItem.Amount, rewardItem.QuantMin, rewardItem.QuantMax, rewardItem.ItemClassName);
            }
            ApplyHealthToItem(rewardEntity, rewardItem.HealthMin, rewardItem.HealthMax, rewardItem.ItemClassName, true);
            if (rewardItem.Attachments && rewardItem.Attachments.Count() > 0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Processing " + rewardItem.Attachments.Count().ToString() + " attachment configs for " + rewardItem.ItemClassName);
                ProcessAttachmentsRecursive(rewardEntity, rewardItem.Attachments, rewardItem.ItemClassName, 1);
            }
            rewardEntity.SetSynchDirty();
        }
        container.SetSynchDirty();
        if (itemsAddedCount == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Failed to add any reward items to container: " + container.GetType() + ". All " + rewardItems.Count().ToString() + " items failed to be added.");
            if (itemsFailedCount > 0)
            {
                failedItemsList = "";
                for (i = 0; i < itemsFailed.Count(); i++)
                {
                    if (i > 0)
                        failedItemsList = failedItemsList + ", ";
                    failedItemsList = failedItemsList + itemsFailed.Get(i);
                }
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Failed items: " + failedItemsList);
            }
        }
        else if (itemsFailedCount > 0)
        {
            addedItemsList = "";
            for (i = 0; i < itemsAdded.Count(); i++)
            {
                if (i > 0)
                    addedItemsList = addedItemsList + ", ";
                addedItemsList = addedItemsList + itemsAdded.Get(i);
            }
            failedItemsList = "";
            for (i = 0; i < itemsFailed.Count(); i++)
            {
                if (i > 0)
                    failedItemsList = failedItemsList + ", ";
                failedItemsList = failedItemsList + itemsFailed.Get(i);
            }
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Partially added reward items to container: " + container.GetType() + ". Added (" + itemsAddedCount.ToString() + "): " + addedItemsList + ". Failed (" + itemsFailedCount.ToString() + "): " + failedItemsList);
        }
        else
        {
            addedItemsList = "";
            for (i = 0; i < itemsAdded.Count(); i++)
            {
                if (i > 0)
                    addedItemsList = addedItemsList + ", ";
                addedItemsList = addedItemsList + itemsAdded.Get(i);
            }
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Successfully added " + itemsAddedCount.ToString() + " reward items to container: " + container.GetType() + ". Items: " + addedItemsList);
        }
        if (ruinedContainer)
        {
            maxHealth = MiscGameplayFunctions.GetTypeMaxGlobalHealth(container.GetType());
            if (maxHealth > 0.0)
            {
                container.SetHealth("", "", 0.0);
                dmgZones = {};
                container.GetDamageZones(dmgZones);
                for (zoneIdx = 0; zoneIdx < dmgZones.Count(); zoneIdx++)
                {
                    dmgZone = dmgZones.Get(zoneIdx);
                    container.SetHealth01(dmgZone, "Health", 0.0);
                }
                container.SetSynchDirty();
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set container to ruined (0 HP) after populating: " + container.GetType());
            }
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Container keeps full health after populating: " + container.GetType());
        }
    }
    private static void SetCurrencyQuantity(ItemBase item, int amount, string className)
    {
        if (!item)
            return;
        if (item.GetQuantityMax() > 0)
        {
            int quantityToSet = amount;
            int maxQuantity = item.GetQuantityMax();
            if (quantityToSet > maxQuantity)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Currency amount " + quantityToSet.ToString() + " exceeds max quantity " + maxQuantity.ToString() + " for " + className + ". Clamping to max.");
                quantityToSet = maxQuantity;
            }
            item.SetQuantity(quantityToSet);
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Set currency quantity: " + className + " x" + quantityToSet.ToString());
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Currency item " + className + " does not support quantity (GetQuantityMax() = 0). Spawning with default quantity.");
        }
    }
    static void AddCurrencyToPlayerInventory(PlayerBase player, array<ref BountyCurrencyReward> currencyRewards)
    {
        if (!IsMissionHost())
            return;
        if (!player)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Player is null for currency rewards!");
            return;
        }
        if (!currencyRewards || currencyRewards.Count() == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] No currency rewards to add to player inventory.");
            return;
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Adding " + currencyRewards.Count().ToString() + " currency rewards to player inventory: " + player.GetIdentity().GetName());
        int i;
        BountyCurrencyReward currencyReward;
        EntityAI currencyEntity;
        ItemBase itemBase;
        InventoryLocation tempLocation;
        EntityAI tempItem;
        for (i = 0; i < currencyRewards.Count(); i++)
        {
            currencyReward = currencyRewards.Get(i);
            if (!currencyReward || currencyReward.ClassName == "" || currencyReward.Amount <= 0)
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Invalid currency reward at index " + i.ToString());
                continue;
            }
            tempItem = EntityAI.Cast(g_Game.CreateObject(currencyReward.ClassName, vector.Zero, false, true));
            if (!tempItem)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Currency class not found: " + currencyReward.ClassName + ". Skipping currency.");
                continue;
            }
            tempLocation = new InventoryLocation;
            bool canFitInCargo = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.CARGO, tempLocation);
            if (!canFitInCargo)
            {
                canFitInCargo = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.ANY, tempLocation);
            }
            g_Game.ObjectDelete(tempItem);
            if (canFitInCargo)
            {
                currencyEntity = player.GetHumanInventory().CreateInInventory(currencyReward.ClassName);
                if (!currencyEntity)
                {
                    GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Failed to create currency item in player inventory: " + currencyReward.ClassName + ". Skipping currency.");
                    continue;
                }
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] No space in player inventory for currency: " + currencyReward.ClassName + ". Skipping currency.");
                continue;
            }
            itemBase = ItemBase.Cast(currencyEntity);
            if (itemBase)
            {
                SetCurrencyQuantity(itemBase, currencyReward.Amount, currencyReward.ClassName);
            }
            else
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Currency entity is not an ItemBase: " + currencyReward.ClassName);
            }
            currencyEntity.SetSynchDirty();
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Successfully processed all currency rewards for player: " + player.GetIdentity().GetName());
    }
    static bool AddItemsToPlayerInventory(PlayerBase player, array<ref BountyRewardItem> rewardItems, bool sendNotification = true)
    {
        if (!IsMissionHost())
            return false;
        if (!player || !player.GetIdentity())
            return false;
        if (!rewardItems || rewardItems.Count() == 0)
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] No reward items to add to inventory!");
            return false;
        }
        int i;
        BountyRewardItem rewardItem;
        EntityAI tempItem;
        InventoryLocation tempLocation;
        bool canFit;
        EntityAI rewardEntity;
        ItemBase rewardItemBase;
        BountyRewardAttachment attachmentConfig;
        int j;
        string playerName = player.GetIdentity().GetName();
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Checking if all " + rewardItems.Count().ToString() + " reward items can fit in player inventory: " + playerName);
        bool validationFailed = false;
        string failedItemName = "";
        for (i = 0; i < rewardItems.Count(); i++)
        {
            rewardItem = rewardItems.Get(i);
            if (!rewardItem || rewardItem.ItemClassName == "")
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Invalid reward item at index " + i.ToString() + ". Cannot add items to inventory.");
                validationFailed = true;
                break; 
            }
            tempItem = EntityAI.Cast(g_Game.CreateObject(rewardItem.ItemClassName, vector.Zero, false, true));
            if (!tempItem)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Item class not found: " + rewardItem.ItemClassName + ". Cannot add items to inventory.");
                validationFailed = true;
                break; 
            }
            tempLocation = new InventoryLocation;
            canFit = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.CARGO, tempLocation);
            if (!canFit)
            {
                canFit = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.ANY, tempLocation);
            }
            g_Game.ObjectDelete(tempItem);
            if (!canFit)
            {
                failedItemName = rewardItem.ItemClassName;
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] No space in player inventory for item: " + rewardItem.ItemClassName + ". All items must fit - cannot add partial reward.");
                validationFailed = true;
                break; 
            }
        }
        if (validationFailed)
        {
            if (sendNotification)
            {
                PlayerIdentity playerIdentity = player.GetIdentity();
                if (playerIdentity)
                {
                    BountyNotifications.SendNotificationInternal(BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL, playerIdentity);
                    GetRPCManager().SendRPC("Ninjins_Bounty_System", "BountyCloseBoardMenu", null, true, playerIdentity);
                }
            }
            return false; 
        }
        GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] All items validated - creating " + rewardItems.Count().ToString() + " items in player inventory: " + playerName);
        int itemsAddedCount = 0;
        for (i = 0; i < rewardItems.Count(); i++)
        {
            rewardItem = rewardItems.Get(i);
            tempItem = EntityAI.Cast(g_Game.CreateObject(rewardItem.ItemClassName, vector.Zero, false, true));
            if (!tempItem)
            {
                GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Item class not found during creation: " + rewardItem.ItemClassName + ". Skipping item.");
                continue;
            }
            tempLocation = new InventoryLocation;
            canFit = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.CARGO, tempLocation);
            if (!canFit)
            {
                canFit = player.GetHumanInventory().FindFreeLocationFor(tempItem, FindInventoryLocationType.ANY, tempLocation);
            }
            g_Game.ObjectDelete(tempItem);
            if (!canFit)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Inventory state changed - item " + rewardItem.ItemClassName + " can no longer fit. Treating as validation failure.");
                return false;
            }
            rewardEntity = player.GetHumanInventory().CreateInInventory(rewardItem.ItemClassName);
            if (!rewardEntity)
            {
                GetNinjins_Bounty_SystemLogger().LogWarning("[BountyRewardContainerHelper] Failed to create item in player inventory after validation: " + rewardItem.ItemClassName + ". Inventory state may have changed. Treating as validation failure.");
                return false;
            }
            rewardItemBase = ItemBase.Cast(rewardEntity);
            if (rewardItemBase)
            {
                ApplyQuantityToItem(rewardItemBase, rewardItem.Amount, rewardItem.QuantMin, rewardItem.QuantMax, rewardItem.ItemClassName);
            }
            ApplyHealthToItem(rewardEntity, rewardItem.HealthMin, rewardItem.HealthMax, rewardItem.ItemClassName, false);
            rewardEntity.SetSynchDirty();
            itemsAddedCount++;
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Added item to player inventory: " + rewardItem.ItemClassName);
            if (rewardItem.Attachments && rewardItem.Attachments.Count() > 0)
            {
                GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Processing " + rewardItem.Attachments.Count().ToString() + " attachment configs for " + rewardItem.ItemClassName);
                ProcessAttachmentsRecursive(rewardEntity, rewardItem.Attachments, rewardItem.ItemClassName, 1);
            }
        }
        if (itemsAddedCount == rewardItems.Count())
        {
            GetNinjins_Bounty_SystemLogger().LogInfo("[BountyRewardContainerHelper] Successfully added all " + itemsAddedCount.ToString() + " item(s) to player inventory: " + playerName);
            return true;
        }
        else
        {
            GetNinjins_Bounty_SystemLogger().LogError("[BountyRewardContainerHelper] Failed to add all items - expected " + rewardItems.Count().ToString() + " but only added " + itemsAddedCount.ToString() + ". This should not happen after validation!");
            return false; 
        }
    }
}