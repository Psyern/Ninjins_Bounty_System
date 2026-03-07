modded class MissionServer
{
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
		static float damageTrackerCleanupTimer = 0.0;
		damageTrackerCleanupTimer += timeslice;
		if (damageTrackerCleanupTimer >= 5.0)
		{
			damageTrackerCleanupTimer = 0.0;
			BountyHitTracker hitTracker = BountyHitTracker.GetInstance();
			if (hitTracker)
			{
				hitTracker.CleanupExpiredEntries();
			}
		}
	}
};