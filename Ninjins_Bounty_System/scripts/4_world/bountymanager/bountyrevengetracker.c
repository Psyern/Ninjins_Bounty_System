//! One killer's kills on one victim, as server time in seconds.
class obfc_BountyRevengeKillerRecord
{
	ref array<float> obfv_m_KillTimes;
	void obfc_BountyRevengeKillerRecord()
	{
		obfv_m_KillTimes = new array<float>();
	}
	//! windowSeconds <= 0 keeps every kill until the server restarts.
	void obfm_PruneExpired(float now, float windowSeconds)
	{
		int i;
		float killAge;
		if (windowSeconds <= 0.0)
			return;
		for (i = obfv_m_KillTimes.Count() - 1; i >= 0; i--)
		{
			killAge = now - obfv_m_KillTimes.Get(i);
			if (killAge > windowSeconds)
				obfv_m_KillTimes.Remove(i);
		}
	}
}
class obfc_BountyRevengeVictimRecord
{
	ref map<string, ref obfc_BountyRevengeKillerRecord> obfv_m_Killers;
	void obfc_BountyRevengeVictimRecord()
	{
		obfv_m_Killers = new map<string, ref obfc_BountyRevengeKillerRecord>();
	}
}
//! Server-only PvP kill counter per victim/killer pair, keyed by PlayerIdentity.GetId().
//! Kept in memory only: counts survive relogs but reset on server restart.
class obfc_BountyRevengeTracker
{
	protected static ref map<string, ref obfc_BountyRevengeVictimRecord> obfv_s_Victims;
	static bool obfm_IsEnabled()
	{
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.Core || !obfv_g_BountyConfig.RevengeBounty)
			return false;
		if (!obfv_g_BountyConfig.Core.EnableBountySystem)
			return false;
		return obfv_g_BountyConfig.RevengeBounty.EnableRevengeBounty;
	}
	static bool obfm_IsPlacementRestricted()
	{
		if (!obfm_IsEnabled())
			return false;
		return obfv_g_BountyConfig.RevengeBounty.RestrictPlacementToRevengeTargets;
	}
	static bool obfm_ShouldResetAfterRevenge()
	{
		if (!obfm_IsEnabled())
			return false;
		return obfv_g_BountyConfig.RevengeBounty.ResetKillsAfterRevengeBounty;
	}
	static int obfm_GetKillsRequired()
	{
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.RevengeBounty)
			return 1;
		if (obfv_g_BountyConfig.RevengeBounty.RevengeKillsRequired < 1)
			return 1;
		return obfv_g_BountyConfig.RevengeBounty.RevengeKillsRequired;
	}
	protected static float obfm_GetWindowSeconds()
	{
		if (!obfv_g_BountyConfig || !obfv_g_BountyConfig.RevengeBounty)
			return 0.0;
		return obfv_g_BountyConfig.RevengeBounty.RevengeKillWindowSeconds;
	}
	protected static float obfm_GetNow()
	{
		if (!g_Game)
			return 0.0;
		return g_Game.GetTime() / obfv_BOUNTY_MS_TO_SECONDS;
	}
	//! Returns the record with expired kills dropped, or null once no kill is left.
	protected static obfc_BountyRevengeKillerRecord obfm_FindRecord(string victimId, string killerId)
	{
		obfc_BountyRevengeVictimRecord victimRecord;
		obfc_BountyRevengeKillerRecord killerRecord;
		if (!obfv_s_Victims)
			return null;
		if (!obfv_s_Victims.Find(victimId, victimRecord))
			return null;
		if (!victimRecord.obfv_m_Killers.Find(killerId, killerRecord))
			return null;
		killerRecord.obfm_PruneExpired(obfm_GetNow(), obfm_GetWindowSeconds());
		if (killerRecord.obfv_m_KillTimes.Count() > 0)
			return killerRecord;
		obfm_ResetPair(victimId, killerId);
		return null;
	}
	//! Returns the number of counted kills of killerId on victimId including this one.
	static int obfm_RegisterKill(string victimId, string killerId)
	{
		obfc_BountyRevengeVictimRecord victimRecord;
		obfc_BountyRevengeKillerRecord killerRecord;
		float now;
		if (victimId == "" || killerId == "" || victimId == killerId)
			return 0;
		if (!obfv_s_Victims)
			obfv_s_Victims = new map<string, ref obfc_BountyRevengeVictimRecord>();
		if (!obfv_s_Victims.Find(victimId, victimRecord))
		{
			victimRecord = new obfc_BountyRevengeVictimRecord();
			obfv_s_Victims.Set(victimId, victimRecord);
		}
		if (!victimRecord.obfv_m_Killers.Find(killerId, killerRecord))
		{
			killerRecord = new obfc_BountyRevengeKillerRecord();
			victimRecord.obfv_m_Killers.Set(killerId, killerRecord);
		}
		now = obfm_GetNow();
		killerRecord.obfm_PruneExpired(now, obfm_GetWindowSeconds());
		killerRecord.obfv_m_KillTimes.Insert(now);
		return killerRecord.obfv_m_KillTimes.Count();
	}
	static int obfm_GetKillCount(string victimId, string killerId)
	{
		obfc_BountyRevengeKillerRecord killerRecord;
		killerRecord = obfm_FindRecord(victimId, killerId);
		if (!killerRecord)
			return 0;
		return killerRecord.obfv_m_KillTimes.Count();
	}
	static bool obfm_IsRevengeTarget(string victimId, string killerId)
	{
		int killCount;
		killCount = obfm_GetKillCount(victimId, killerId);
		return killCount >= obfm_GetKillsRequired();
	}
	static void obfm_ResetPair(string victimId, string killerId)
	{
		obfc_BountyRevengeVictimRecord victimRecord;
		if (!obfv_s_Victims)
			return;
		if (!obfv_s_Victims.Find(victimId, victimRecord))
			return;
		victimRecord.obfv_m_Killers.Remove(killerId);
		if (victimRecord.obfv_m_Killers.Count() == 0)
			obfv_s_Victims.Remove(victimId);
	}
}
