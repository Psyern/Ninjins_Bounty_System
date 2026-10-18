const string obfv_Ninjins_Bounty_System_POTS_FILE = obfv_Ninjins_Bounty_System_DATA_DIR + "BountyPots.json";
const string obfv_Ninjins_Bounty_System_PAYOUTS_FILE = obfv_Ninjins_Bounty_System_DATA_DIR + "BountyPayouts.json";
const float obfv_BOUNTY_POT_SWEEP_INTERVAL_SECONDS = 30.0;
const int obfv_BOUNTY_POT_SWEEP_GRACE_SECONDS = 60;
class obfc_BountyPotShare
{
	string PlayerId;
	string PlayerName;
	int Amount;
	void obfc_BountyPotShare()
	{
		PlayerId = "";
		PlayerName = "";
		Amount = 0;
	}
}
//! Money and admin loot riding on one bountied player.
class obfc_BountyPot
{
	string TargetId;
	string TargetName;
	int CreatedAt;
	bool SelfImposed;
	ref array<ref obfc_BountyPotShare> Shares;
	ref array<string> LootPresets;
	void obfc_BountyPot()
	{
		TargetId = "";
		TargetName = "";
		CreatedAt = 0;
		SelfImposed = false;
		Shares = new array<ref obfc_BountyPotShare>;
		LootPresets = new array<string>;
	}
	int obfm_GetTotal()
	{
		int total;
		total = 0;
		foreach (obfc_BountyPotShare share : Shares)
		{
			if (share)
				total = total + share.Amount;
		}
		return total;
	}
}
class obfc_BountyPotStore
{
	ref array<ref obfc_BountyPot> Pots;
	void obfc_BountyPotStore()
	{
		Pots = new array<ref obfc_BountyPot>;
	}
}
//! Money and loot a player won or got refunded, claimed at the bounty board (survives restarts and logouts).
class obfc_BountyPayout
{
	string PlayerId;
	string PlayerName;
	int Money;
	ref array<string> LootPresets;
	void obfc_BountyPayout()
	{
		PlayerId = "";
		PlayerName = "";
		Money = 0;
		LootPresets = new array<string>;
	}
}
class obfc_BountyPayoutStore
{
	ref array<ref obfc_BountyPayout> Payouts;
	void obfc_BountyPayoutStore()
	{
		Payouts = new array<ref obfc_BountyPayout>;
	}
}
//! Server-only. Pots are keyed by the target's PlayerIdentity.GetId() and resolved in
//! PlayerBase.obfm_ClearBounty (every bounty end) or EEKilled (player kill -> killer).
class obfc_BountyPotManager
{
	protected static ref obfc_BountyPotStore obfv_s_PotStore;
	protected static ref obfc_BountyPayoutStore obfv_s_PayoutStore;
	protected static ref array<string> obfv_s_SweepSuspects;
	protected static float obfv_s_SweepTimer;
	static bool obfm_IsEnabled()
	{
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.Pot)
			return false;
		if (!obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		return obfv_g_BountyConfig.Pot.EnableBountyPots;
	}
	static bool obfm_IsStackingAllowed()
	{
		if (!obfm_IsEnabled())
			return false;
		return obfv_g_BountyConfig.Pot.AllowStacking;
	}
	static bool obfm_IsSelfBountyAllowed()
	{
		if (!obfm_IsEnabled())
			return false;
		return obfv_g_BountyConfig.Pot.EnableSelfBounty;
	}
	static int obfm_GetFee(int amount)
	{
		int fee;
		float exactFee;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Pot || obfv_g_BountyConfig.Pot.FeePercent <= 0 || amount <= 0)
			return 0;
		exactFee = amount * obfv_g_BountyConfig.Pot.FeePercent / 100.0;
		fee = Math.Ceil(exactFee);
		return fee;
	}
	protected static void obfm_EnsureLoaded()
	{
		if (!obfv_s_PotStore)
		{
			obfv_s_PotStore = new obfc_BountyPotStore();
			if (FileExist(obfv_Ninjins_Bounty_System_POTS_FILE))
				JsonFileLoader<obfc_BountyPotStore>.JsonLoadFile(obfv_Ninjins_Bounty_System_POTS_FILE, obfv_s_PotStore);
			if (!obfv_s_PotStore.Pots)
				obfv_s_PotStore.Pots = new array<ref obfc_BountyPot>;
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] Loaded " + obfv_s_PotStore.Pots.Count().ToString() + " active pot(s)");
		}
		if (!obfv_s_PayoutStore)
		{
			obfv_s_PayoutStore = new obfc_BountyPayoutStore();
			if (FileExist(obfv_Ninjins_Bounty_System_PAYOUTS_FILE))
				JsonFileLoader<obfc_BountyPayoutStore>.JsonLoadFile(obfv_Ninjins_Bounty_System_PAYOUTS_FILE, obfv_s_PayoutStore);
			if (!obfv_s_PayoutStore.Payouts)
				obfv_s_PayoutStore.Payouts = new array<ref obfc_BountyPayout>;
		}
		if (!obfv_s_SweepSuspects)
			obfv_s_SweepSuspects = new array<string>;
	}
	protected static void obfm_EnsureDataDir()
	{
		if (!FileExist(obfv_Ninjins_Bounty_System_DATA_DIR))
			MakeDirectory(obfv_Ninjins_Bounty_System_DATA_DIR);
	}
	protected static void obfm_SavePots()
	{
		obfm_EnsureDataDir();
		JsonFileLoader<obfc_BountyPotStore>.JsonSaveFile(obfv_Ninjins_Bounty_System_POTS_FILE, obfv_s_PotStore);
	}
	protected static void obfm_SavePayouts()
	{
		obfm_EnsureDataDir();
		JsonFileLoader<obfc_BountyPayoutStore>.JsonSaveFile(obfv_Ninjins_Bounty_System_PAYOUTS_FILE, obfv_s_PayoutStore);
	}
	protected static int obfm_FindPotIndex(string targetId)
	{
		int i;
		obfc_BountyPot pot;
		obfm_EnsureLoaded();
		for (i = 0; i < obfv_s_PotStore.Pots.Count(); i++)
		{
			pot = obfv_s_PotStore.Pots.Get(i);
			if (pot && pot.TargetId == targetId)
				return i;
		}
		return -1;
	}
	static obfc_BountyPot obfm_FindPot(string targetId)
	{
		int index;
		if (targetId == "")
			return null;
		index = obfm_FindPotIndex(targetId);
		if (index < 0)
			return null;
		return obfv_s_PotStore.Pots.Get(index);
	}
	static int obfm_GetPotTotal(string targetId)
	{
		obfc_BountyPot pot;
		pot = obfm_FindPot(targetId);
		if (!pot)
			return 0;
		return pot.obfm_GetTotal();
	}
	static bool obfm_HasLoot(string targetId)
	{
		obfc_BountyPot pot;
		pot = obfm_FindPot(targetId);
		if (!pot)
			return false;
		return pot.LootPresets.Count() > 0;
	}
	static bool obfm_IsSelfImposed(string targetId)
	{
		obfc_BountyPot pot;
		pot = obfm_FindPot(targetId);
		if (!pot)
			return false;
		return pot.SelfImposed;
	}
	//! Returns "" when amount may go into the target's pot, otherwise the reason shown to the player.
	static string obfm_ValidateContribution(string targetId, int amount)
	{
		int potTotal;
		if (!obfm_IsEnabled())
			return "Money bounties are disabled on this server.";
		if (amount < obfv_g_BountyConfig.Pot.MinContribution)
			return "The minimum reward is " + obfv_g_BountyConfig.Pot.MinContribution.ToString() + " " + obfc_BountyMoney.obfm_GetCurrencyLabel() + ".";
		if (obfv_g_BountyConfig.Pot.MaxContribution > 0 && amount > obfv_g_BountyConfig.Pot.MaxContribution)
			return "The maximum reward is " + obfv_g_BountyConfig.Pot.MaxContribution.ToString() + " " + obfc_BountyMoney.obfm_GetCurrencyLabel() + ".";
		potTotal = obfm_GetPotTotal(targetId);
		if (obfv_g_BountyConfig.Pot.MaxPotTotal > 0 && potTotal + amount > obfv_g_BountyConfig.Pot.MaxPotTotal)
			return "This bounty can hold at most " + obfv_g_BountyConfig.Pot.MaxPotTotal.ToString() + " " + obfc_BountyMoney.obfm_GetCurrencyLabel() + " (currently " + potTotal.ToString() + ").";
		return "";
	}
	protected static obfc_BountyPot obfm_GetOrCreatePot(PlayerBase target)
	{
		obfc_BountyPot pot;
		PlayerIdentity targetIdentity;
		targetIdentity = target.GetIdentity();
		pot = obfm_FindPot(targetIdentity.GetId());
		if (pot)
			return pot;
		pot = new obfc_BountyPot();
		pot.TargetId = targetIdentity.GetId();
		pot.TargetName = targetIdentity.GetName();
		pot.CreatedAt = obfc_BountyTime.obfm_GetUnixTime();
		obfv_s_PotStore.Pots.Insert(pot);
		return pot;
	}
	//! Books money that was already taken from the contributor.
	static void obfm_AddShare(PlayerBase target, PlayerIdentity contributor, int amount, bool selfImposed)
	{
		obfc_BountyPot pot;
		obfc_BountyPotShare share;
		if (!target || !target.GetIdentity() || !contributor || amount <= 0)
			return;
		pot = obfm_GetOrCreatePot(target);
		if (selfImposed)
			pot.SelfImposed = true;
		share = new obfc_BountyPotShare();
		share.PlayerId = contributor.GetId();
		share.PlayerName = contributor.GetName();
		share.Amount = amount;
		pot.Shares.Insert(share);
		obfm_SavePots();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + share.PlayerName + " added " + amount.ToString() + " to the pot on " + pot.TargetName + " (total " + pot.obfm_GetTotal().ToString() + ", self-imposed: " + pot.SelfImposed.ToString() + ")");
	}
	static void obfm_AddLoot(PlayerBase target, string presetName)
	{
		obfc_BountyPot pot;
		if (!target || !target.GetIdentity() || presetName == "")
			return;
		pot = obfm_GetOrCreatePot(target);
		pot.LootPresets.Insert(presetName);
		obfm_SavePots();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] Loot preset " + presetName + " attached to the bounty on " + pot.TargetName);
	}
	protected static obfc_BountyPayout obfm_GetOrCreatePayout(string playerId, string playerName)
	{
		obfm_EnsureLoaded();
		foreach (obfc_BountyPayout existing : obfv_s_PayoutStore.Payouts)
		{
			if (existing && existing.PlayerId == playerId)
			{
				if (playerName != "")
					existing.PlayerName = playerName;
				return existing;
			}
		}
		obfc_BountyPayout payout;
		payout = new obfc_BountyPayout();
		payout.PlayerId = playerId;
		payout.PlayerName = playerName;
		obfv_s_PayoutStore.Payouts.Insert(payout);
		return payout;
	}
	protected static obfc_BountyPayout obfm_FindPayout(string playerId)
	{
		obfm_EnsureLoaded();
		foreach (obfc_BountyPayout payout : obfv_s_PayoutStore.Payouts)
		{
			if (payout && payout.PlayerId == playerId)
				return payout;
		}
		return null;
	}
	protected static PlayerIdentity obfm_FindOnlineIdentity(string playerId)
	{
		array<Man> players;
		PlayerIdentity identity;
		players = new array<Man>;
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			if (!man)
				continue;
			identity = man.GetIdentity();
			if (identity && identity.GetId() == playerId)
				return identity;
		}
		return null;
	}
	protected static void obfm_NotifyPlayer(int type, string playerId, string targetName, int amount)
	{
		PlayerIdentity identity;
		obfc_BountyNotifArgs args;
		identity = obfm_FindOnlineIdentity(playerId);
		if (!identity)
			return;
		args = new obfc_BountyNotifArgs();
		args.playerName = targetName;
		args.potAmount = amount;
		args.currencyLabel = obfc_BountyMoney.obfm_GetCurrencyLabel();
		obfc_BountyNotifications.obfm_SendNotificationInternal(type, identity, args);
	}
	//! Credits every share back to its contributor; includeTarget = false forfeits the target's own shares.
	protected static void obfm_RefundShares(obfc_BountyPot pot, bool includeTarget)
	{
		obfc_BountyPayout payout;
		foreach (obfc_BountyPotShare share : pot.Shares)
		{
			if (!share || share.Amount <= 0)
				continue;
			if (!includeTarget && share.PlayerId == pot.TargetId)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + share.Amount.ToString() + " from " + share.PlayerName + " forfeited (own share on " + pot.TargetName + ")");
				continue;
			}
			payout = obfm_GetOrCreatePayout(share.PlayerId, share.PlayerName);
			payout.Money = payout.Money + share.Amount;
			obfm_NotifyPlayer(obfv_BOUNTY_NOTIFICATION_POT_REFUND, share.PlayerId, pot.TargetName, share.Amount);
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] Refunded " + share.Amount.ToString() + " to " + share.PlayerName + " (bounty on " + pot.TargetName + ")");
		}
		obfm_SavePayouts();
	}
	//! Hands the whole pot (money and loot) to winnerId.
	protected static void obfm_PayOutPot(obfc_BountyPot pot, string winnerId, string winnerName)
	{
		obfc_BountyPayout payout;
		int total;
		total = pot.obfm_GetTotal();
		payout = obfm_GetOrCreatePayout(winnerId, winnerName);
		payout.Money = payout.Money + total;
		foreach (string presetName : pot.LootPresets)
		{
			payout.LootPresets.Insert(presetName);
		}
		obfm_SavePayouts();
		obfm_NotifyPlayer(obfv_BOUNTY_NOTIFICATION_POT_PAYOUT, winnerId, pot.TargetName, total);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + winnerName + " won the pot on " + pot.TargetName + ": " + total.ToString() + " money, " + pot.LootPresets.Count().ToString() + " loot preset(s)");
	}
	protected static void obfm_RemovePot(string targetId)
	{
		int index;
		index = obfm_FindPotIndex(targetId);
		if (index < 0)
			return;
		obfv_s_PotStore.Pots.Remove(index);
		obfm_SavePots();
	}
	//! Player kill of a bountied target: the killer takes everything unless they are in the target's group.
	static void obfm_ResolveOnKill(PlayerBase target, PlayerBase killer)
	{
		obfc_BountyPot pot;
		PlayerIdentity killerIdentity;
		if (!target || !target.GetIdentity() || !killer)
			return;
		pot = obfm_FindPot(target.GetIdentity().GetId());
		if (!pot)
			return;
		killerIdentity = killer.GetIdentity();
		if (!killerIdentity)
			return;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Pot && obfv_g_BountyConfig.Pot.BlockGroupPayout && target.obfm_NinjinBountyIsFriendlyKiller(killer))
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + killerIdentity.GetName() + " is in the group of " + pot.TargetName + " - pot refunded instead of paid (BlockGroupPayout)");
			obfm_RefundShares(pot, true);
		}
		else
		{
			obfm_PayOutPot(pot, killerIdentity.GetId(), killerIdentity.GetName());
		}
		obfm_RemovePot(pot.TargetId);
	}
	//! Every other bounty end. Escapes (suicide, logout, non-player death) forfeit the target's own shares.
	static void obfm_ResolveOnEnd(PlayerBase target, BountyEndReason endReason, bool survived)
	{
		obfc_BountyPot pot;
		if (!target || !target.GetIdentity())
			return;
		pot = obfm_FindPot(target.GetIdentity().GetId());
		if (!pot)
			return;
		if (endReason == BountyEndReason.EXPIRED && survived && obfv_g_BountyConfig && obfv_g_BountyConfig.Pot && obfv_g_BountyConfig.Pot.SurvivorKeepsPot)
			obfm_PayOutPot(pot, pot.TargetId, pot.TargetName);
		else if (endReason == BountyEndReason.EXPIRED || endReason == BountyEndReason.CLEARED)
			obfm_RefundShares(pot, true);
		else
			obfm_RefundShares(pot, false);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] Pot on " + pot.TargetName + " resolved - end reason " + typename.EnumToString(BountyEndReason, endReason));
		obfm_RemovePot(pot.TargetId);
	}
	static int obfm_GetPendingMoney(string playerId)
	{
		obfc_BountyPayout payout;
		payout = obfm_FindPayout(playerId);
		if (!payout)
			return 0;
		return payout.Money;
	}
	static int obfm_GetPendingLootCount(string playerId)
	{
		obfc_BountyPayout payout;
		payout = obfm_FindPayout(playerId);
		if (!payout)
			return 0;
		return payout.LootPresets.Count();
	}
	protected static void obfm_DropEmptyPayout(obfc_BountyPayout payout)
	{
		int index;
		if (payout.Money > 0 || payout.LootPresets.Count() > 0)
			return;
		index = obfv_s_PayoutStore.Payouts.Find(payout);
		if (index >= 0)
			obfv_s_PayoutStore.Payouts.Remove(index);
	}
	//! Pays out all pending pot money. Returns the amount handed over.
	static int obfm_ClaimMoney(PlayerBase player)
	{
		obfc_BountyPayout payout;
		int amount;
		if (!player || !player.GetIdentity())
			return 0;
		payout = obfm_FindPayout(player.GetIdentity().GetId());
		if (!payout || payout.Money <= 0)
			return 0;
		amount = payout.Money;
		payout.Money = 0;
		obfm_DropEmptyPayout(payout);
		obfm_SavePayouts();
		obfc_BountyMoney.obfm_GiveMoney(player, amount);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + player.GetIdentity().GetName() + " claimed " + amount.ToString() + " bounty money");
		return amount;
	}
	//! Spawns the next pending loot preset container in the player's hands. False when nothing was spawned.
	static bool obfm_ClaimLoot(PlayerBase player)
	{
		obfc_BountyPayout payout;
		obfc_BountyLootPreset preset;
		string presetName;
		EntityAI container;
		if (!player || !player.GetIdentity())
			return false;
		payout = obfm_FindPayout(player.GetIdentity().GetId());
		if (!payout || payout.LootPresets.Count() == 0)
			return false;
		presetName = payout.LootPresets.Get(0);
		preset = null;
		if (obfv_g_BountyLootPresetConfig)
			preset = obfv_g_BountyLootPresetConfig.obfm_FindPreset(presetName);
		if (!preset)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[BountyPot] Loot preset " + presetName + " no longer exists - dropping it from " + player.GetIdentity().GetName() + "'s payouts");
			payout.LootPresets.RemoveOrdered(0);
			obfm_DropEmptyPayout(payout);
			obfm_SavePayouts();
			return false;
		}
		if (player.GetHumanInventory().GetEntityInHands())
		{
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE, player.GetIdentity(), null);
			return false;
		}
		container = EntityAI.Cast(player.GetHumanInventory().CreateInHands(preset.ContainerClassName));
		if (!container)
		{
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[BountyPot] Could not create loot container " + preset.ContainerClassName + " for preset " + preset.Name);
			obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_REWARD_CONTAINER_SPAWN_FAILURE, player.GetIdentity(), null);
			return false;
		}
		obfc_BountyRewardContainerHelper.obfm_PopulateContainer(container, preset.Items, preset.RuinedContainer);
		payout.LootPresets.RemoveOrdered(0);
		obfm_DropEmptyPayout(payout);
		obfm_SavePayouts();
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[BountyPot] " + player.GetIdentity().GetName() + " claimed loot preset " + preset.Name);
		return true;
	}
	//! Refunds pots whose target is online without a bounty on two sweeps in a row (bounty warning that
	//! never started, bounty ended while the pot could not be resolved). Offline targets keep their pot.
	static void obfm_Update(float deltaTime)
	{
		array<string> stillSuspect;
		obfc_BountyPot pot;
		PlayerBase target;
		int now;
		int grace;
		int warningSeconds;
		int i;
		bool changed;
		obfv_s_SweepTimer = obfv_s_SweepTimer + deltaTime;
		if (obfv_s_SweepTimer < obfv_BOUNTY_POT_SWEEP_INTERVAL_SECONDS)
			return;
		obfv_s_SweepTimer = 0.0;
		obfm_EnsureLoaded();
		if (obfv_s_PotStore.Pots.Count() == 0)
		{
			obfv_s_SweepSuspects.Clear();
			return;
		}
		now = obfc_BountyTime.obfm_GetUnixTime();
		grace = obfv_BOUNTY_POT_SWEEP_GRACE_SECONDS;
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core)
		{
			warningSeconds = Math.Ceil(obfv_g_BountyConfig.Core.BountyWarningTimeSeconds);
			grace = grace + warningSeconds;
		}
		stillSuspect = new array<string>;
		changed = false;
		for (i = obfv_s_PotStore.Pots.Count() - 1; i >= 0; i--)
		{
			pot = obfv_s_PotStore.Pots.Get(i);
			if (!pot)
				continue;
			if (now - pot.CreatedAt < grace)
				continue;
			target = obfm_FindOnlineAlivePlayer(pot.TargetId);
			if (!target || target.obfm_HasBounty())
				continue;
			if (obfv_s_SweepSuspects.Find(pot.TargetId) < 0)
			{
				stillSuspect.Insert(pot.TargetId);
				continue;
			}
			obfm_GetNinjins_Bounty_SystemLogger().obfm_LogWarning("[BountyPot] " + pot.TargetName + " is online without a bounty - refunding the orphaned pot");
			obfm_RefundShares(pot, true);
			obfv_s_PotStore.Pots.Remove(i);
			changed = true;
		}
		obfv_s_SweepSuspects = stillSuspect;
		if (changed)
			obfm_SavePots();
	}
	protected static PlayerBase obfm_FindOnlineAlivePlayer(string playerId)
	{
		array<Man> players;
		PlayerBase player;
		players = new array<Man>;
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			player = PlayerBase.Cast(man);
			if (!player || !player.IsAlive() || !player.GetIdentity())
				continue;
			if (player.GetIdentity().GetId() == playerId)
				return player;
		}
		return null;
	}
}
