modded class MissionServer
{
	private float obfv_m_BountyDamageTrackerCleanupTimer = 0.0;

	void ~MissionServer() {}
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