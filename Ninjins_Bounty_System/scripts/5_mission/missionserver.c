modded class MissionServer
{
	private float m_BountyDamageTrackerCleanupTimer = 0.0;

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
				if (player.HasBounty() || player.IsBountyOnCooldown())
				{
					player.UpdateBountyDuration(timeslice);
					player.UpdateBountyCooldown(timeslice);
				}
			}
		}		
		m_BountyDamageTrackerCleanupTimer += timeslice;
		if (m_BountyDamageTrackerCleanupTimer >= 5.0)
		{
			m_BountyDamageTrackerCleanupTimer = 0.0;
			BountyHitTracker hitTracker = BountyHitTracker.GetInstance();
			if (hitTracker)
			{
				hitTracker.CleanupExpiredEntries();
			}
		}
	}
};