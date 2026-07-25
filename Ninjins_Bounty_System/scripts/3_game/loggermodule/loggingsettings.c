class obfc_Ninjins_Bounty_SystemLoggingSettings 
{
	int logLevel = 4;
	int refreshRateInSeconds = 60;
	void obfm_MakeDirectoryIfNotExists()
	{
		if(!FileExist( obfv_Ninjins_Bounty_System_ROOT_FOLDER))
			MakeDirectory( obfv_Ninjins_Bounty_System_ROOT_FOLDER);
		if(!FileExist( obfv_Ninjins_Bounty_System_LOG_FOLDER))
			MakeDirectory( obfv_Ninjins_Bounty_System_LOG_FOLDER);
		if(!FileExist( obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR))
			MakeDirectory( obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR);
		if(!FileExist( obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR))
			MakeDirectory( obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR);
	}
	void obfm_Save()
	{
		JsonFileLoader<obfc_Ninjins_Bounty_SystemLoggingSettings>.JsonSaveFile( obfv_Ninjins_Bounty_System_LOGGER_CONFIG_FILE, this);
	}
	static obfc_Ninjins_Bounty_SystemLoggingSettings obfm_Load()
	{
		obfc_Ninjins_Bounty_SystemLoggingSettings obfv_settings = new obfc_Ninjins_Bounty_SystemLoggingSettings();
		obfv_settings.obfm_MakeDirectoryIfNotExists();
		if(FileExist( obfv_Ninjins_Bounty_System_LOGGER_CONFIG_FILE))
		{
			JsonFileLoader<obfc_Ninjins_Bounty_SystemLoggingSettings>.JsonLoadFile( obfv_Ninjins_Bounty_System_LOGGER_CONFIG_FILE, obfv_settings);
			return obfv_settings;
		}
		obfv_settings.obfm_Save();
		return obfv_settings;
	}
}