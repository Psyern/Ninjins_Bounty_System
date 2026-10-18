const string obfv_Ninjins_Bounty_System_WEEKLY_KILLS_FILE = obfv_Ninjins_Bounty_System_DATA_DIR + "WeeklyKills.json";
class obfc_BountyWeeklyKillEntry
{
	string PlayerId;
	string PlayerName;
	int Kills;
	void obfc_BountyWeeklyKillEntry()
	{
		PlayerId = "";
		PlayerName = "";
		Kills = 0;
	}
}
class obfc_BountyWeeklyKillStore
{
	int Week;
	ref array<ref obfc_BountyWeeklyKillEntry> Entries;
	void obfc_BountyWeeklyKillStore()
	{
		Week = 0;
		Entries = new array<ref obfc_BountyWeeklyKillEntry>;
	}
}
//! PvP kills per player for the current week (Monday 00:00 UTC), persisted for the
//! "top killer of the week" automated bounty target.
class obfc_BountyWeeklyKills
{
	protected static ref obfc_BountyWeeklyKillStore obfv_s_Store;
	protected static void obfm_EnsureCurrentWeek()
	{
		int currentWeek;
		if (!obfv_s_Store)
		{
			obfv_s_Store = new obfc_BountyWeeklyKillStore();
			if (FileExist(obfv_Ninjins_Bounty_System_WEEKLY_KILLS_FILE))
				JsonFileLoader<obfc_BountyWeeklyKillStore>.JsonLoadFile(obfv_Ninjins_Bounty_System_WEEKLY_KILLS_FILE, obfv_s_Store);
			if (!obfv_s_Store.Entries)
				obfv_s_Store.Entries = new array<ref obfc_BountyWeeklyKillEntry>;
		}
		currentWeek = obfc_BountyTime.obfm_GetWeekIndex();
		if (obfv_s_Store.Week == currentWeek)
			return;
		obfm_GetNinjins_Bounty_SystemLogger().obfm_LogInfo("[WeeklyKills] New week " + currentWeek.ToString() + " - resetting " + obfv_s_Store.Entries.Count().ToString() + " kill entries");
		obfv_s_Store.Week = currentWeek;
		obfv_s_Store.Entries.Clear();
		obfm_Save();
	}
	protected static void obfm_Save()
	{
		if (!obfv_s_Store)
			return;
		if (!FileExist(obfv_Ninjins_Bounty_System_DATA_DIR))
			MakeDirectory(obfv_Ninjins_Bounty_System_DATA_DIR);
		JsonFileLoader<obfc_BountyWeeklyKillStore>.JsonSaveFile(obfv_Ninjins_Bounty_System_WEEKLY_KILLS_FILE, obfv_s_Store);
	}
	protected static obfc_BountyWeeklyKillEntry obfm_FindEntry(string playerId)
	{
		foreach (obfc_BountyWeeklyKillEntry entry : obfv_s_Store.Entries)
		{
			if (entry && entry.PlayerId == playerId)
				return entry;
		}
		return null;
	}
	static void obfm_RegisterKill(string killerId, string killerName)
	{
		obfc_BountyWeeklyKillEntry entry;
		if (killerId == "")
			return;
		obfm_EnsureCurrentWeek();
		entry = obfm_FindEntry(killerId);
		if (!entry)
		{
			entry = new obfc_BountyWeeklyKillEntry();
			entry.PlayerId = killerId;
			obfv_s_Store.Entries.Insert(entry);
		}
		entry.PlayerName = killerName;
		entry.Kills = entry.Kills + 1;
		obfm_Save();
	}
	static int obfm_GetKills(string playerId)
	{
		obfc_BountyWeeklyKillEntry entry;
		obfm_EnsureCurrentWeek();
		entry = obfm_FindEntry(playerId);
		if (!entry)
			return 0;
		return entry.Kills;
	}
}
