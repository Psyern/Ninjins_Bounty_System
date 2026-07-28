modded class MissionServer
{
	private float obfv_m_BountyDamageTrackerCleanupTimer = 0.0;

	void ~MissionServer() {}
	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		string playerName;
		bool hadBounty;
		hadBounty = false;
		if (player)
		{
			hadBounty = player.obfm_HasBounty();
		}
		playerName = obfv_BOUNTY_PLAYER_NAME_UNKNOWN;
		if (identity)
		{
			playerName = identity.GetName();
		}
		super.PlayerDisconnected(player, identity, uid);
		if (!hadBounty)
			return;
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core)
			return;
		if (!obfv_g_BountyConfig.Core.PersistentBountyAfterLogOut)
			return;
		obfc_BountyNotifications.obfm_SendNotificationInternal(obfv_BOUNTY_NOTIFICATION_LOGOUT_BROADCAST, null, playerName);
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[Bounty] Player " + playerName + " logged out with an active bounty - it will return when they reconnect.");
	}
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		array<Man> players = new array<Man>();
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			PlayerBase player = PlayerBase.Cast(man);
			if (player)
			{
				if (player.obfm_HasBounty() || player.obfm_IsBountyOnCooldown())
				{
					player.obfm_UpdateBountyDuration(timeslice);
					player.obfm_UpdateBountyCooldown(timeslice);
				}
			}
		}		
		obfv_m_BountyDamageTrackerCleanupTimer += timeslice;
		if (obfv_m_BountyDamageTrackerCleanupTimer >= 5.0)
		{
			obfv_m_BountyDamageTrackerCleanupTimer = 0.0;
			obfc_BountyHitTracker hitTracker = obfc_BountyHitTracker.GetInstance();
			if (hitTracker)
			{
				hitTracker.obfm_CleanupExpiredEntries();
			}
		}
	}
};