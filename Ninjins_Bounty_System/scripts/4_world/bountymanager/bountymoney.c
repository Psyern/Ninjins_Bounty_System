//! Money used by bounty pots: Expansion Market currencies when that mod is loaded and
//! Pot.UseExpansionMarketMoney is on, otherwise the configured bounty tokens.
class obfc_BountyMoney
{
	static bool obfm_UsesExpansionMarket()
	{
		#ifdef EXPANSIONMODMARKET
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Pot || !obfv_g_BountyConfig.Pot.UseExpansionMarketMoney)
			return false;
		if (ExpansionMarketModule.GetInstance())
			return true;
		#endif
		return false;
	}
	static string obfm_GetCurrencyLabel()
	{
		if (obfm_UsesExpansionMarket())
			return "money";
		return "token(s)";
	}
	static int obfm_GetPlayerMoney(PlayerBase player)
	{
		obfc_BountyModule bountyModule;
		array<ItemBase> foundTokens;
		if (!player)
			return 0;
		#ifdef EXPANSIONMODMARKET
		array<int> monies;
		if (obfm_UsesExpansionMarket())
			return ExpansionMarketModule.GetInstance().GetPlayerWorth(player, monies, null, true);
		#endif
		bountyModule = obfc_BountyModule.GetInstance();
		if (!bountyModule)
			return 0;
		return bountyModule.obfm_GetPlayerTokenCount(player, foundTokens);
	}
	//! Removes exactly amount (Expansion hands out change itself). False leaves the player's money untouched.
	static bool obfm_TakeMoney(PlayerBase player, int amount)
	{
		obfc_BountyModule bountyModule;
		int tokensRemoved;
		if (amount <= 0)
			return true;
		if (!player)
			return false;
		if (obfm_GetPlayerMoney(player) < amount)
			return false;
		#ifdef EXPANSIONMODMARKET
		if (obfm_UsesExpansionMarket())
			return ExpansionMarketModule.GetInstance().RemoveMoney(amount, player);
		#endif
		bountyModule = obfc_BountyModule.GetInstance();
		if (!bountyModule)
			return false;
		if (bountyModule.obfm_ConsumePlayerTokens(player, amount, tokensRemoved))
			return true;
		if (tokensRemoved > 0)
			obfm_GiveMoney(player, tokensRemoved);
		return false;
	}
	//! Spawns amount into the inventory; what does not fit lands next to the player.
	static void obfm_GiveMoney(PlayerBase player, int amount)
	{
		if (!player || amount <= 0)
			return;
		#ifdef EXPANSIONMODMARKET
		EntityAI parent;
		if (obfm_UsesExpansionMarket())
		{
			parent = player;
			ExpansionMarketModule.GetInstance().SpawnMoney(player, parent, amount, true, null, null, true);
			return;
		}
		#endif
		obfm_GiveTokens(player, amount);
	}
	protected static void obfm_GiveTokens(PlayerBase player, int amount)
	{
		string tokenClassName;
		int remaining;
		int stackSize;
		EntityAI tokenEntity;
		ItemBase tokenItem;
		tokenClassName = "Ninjins_Bounty_Token_Gold";
		if (obfv_g_BountyConfig && obfv_g_BountyConfig.Core && obfv_g_BountyConfig.Core.BountyTokenClassNames && obfv_g_BountyConfig.Core.BountyTokenClassNames.Count() > 0)
			tokenClassName = obfv_g_BountyConfig.Core.BountyTokenClassNames.Get(0);
		remaining = amount;
		while (remaining > 0)
		{
			tokenEntity = player.GetHumanInventory().CreateInInventory(tokenClassName);
			if (!tokenEntity)
				tokenEntity = EntityAI.Cast(g_Game.CreateObjectEx(tokenClassName, player.GetPosition(), ECE_PLACE_ON_SURFACE));
			tokenItem = ItemBase.Cast(tokenEntity);
			if (!tokenItem)
			{
				obfm_GetNinjins_Bounty_SystemLogger().obfm_LogError("[BountyMoney] Could not spawn token " + tokenClassName + " - " + remaining.ToString() + " token(s) not paid out");
				return;
			}
			stackSize = 1;
			if (tokenItem.HasQuantity())
			{
				stackSize = tokenItem.GetQuantityMax();
				if (stackSize > remaining)
					stackSize = remaining;
				if (stackSize < 1)
					stackSize = 1;
				tokenItem.SetQuantity(stackSize);
			}
			remaining = remaining - stackSize;
		}
	}
}
