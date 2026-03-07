#ifdef EXPANSIONMODBASEBUILDING
modded class ExpansionTerritoryModule
{
    override void RPC_CreateTerritory(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_CreateTerritory(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after territory creation");
            }
        }
    }
    override private void RPC_AcceptInvite(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_AcceptInvite(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after member accepted invite");
            }
        }
    }
    override private void RPC_KickMember(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_KickMember(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after member was kicked");
            }
        }
    }
    override private void RPC_Leave(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_Leave(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after member left");
            }
        }
    }
    override protected void RPC_DeleteTerritoryPlayer(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_DeleteTerritoryPlayer(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after territory deletion (player)");
            }
        }
    }
    override protected void RPC_DeleteTerritoryAdmin(PlayerIdentity senderRPC, Object target, ParamsReadContext ctx)
    {
        super.RPC_DeleteTerritoryAdmin(senderRPC, target, ctx);
        if (g_Game.IsDedicatedServer())
        {
            BountyManager bountyManager = BountyManager.GetInstance();
            if (bountyManager)
            {
                bountyManager.RefreshTerritoryCache();
                GetNinjins_Bounty_SystemLogger().LogInfo("[Bounty] Territory cache refreshed after territory deletion (admin)");
            }
        }
    }
}
#endif