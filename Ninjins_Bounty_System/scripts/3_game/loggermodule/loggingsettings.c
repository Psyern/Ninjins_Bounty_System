class Ninjins_Bounty_SystemLoggingSettings 
{
    int logLevel = 4;
    int refreshRateInSeconds = 60;
    void MakeDirectoryIfNotExists()
    {
        if(!FileExist( Ninjins_Bounty_System_ROOT_FOLDER))
            MakeDirectory( Ninjins_Bounty_System_ROOT_FOLDER);
        if(!FileExist( Ninjins_Bounty_System_LOG_FOLDER))
            MakeDirectory( Ninjins_Bounty_System_LOG_FOLDER);
        if(!FileExist( Ninjins_Bounty_System_LOGGER_CONFIG_DIR))
            MakeDirectory( Ninjins_Bounty_System_LOGGER_CONFIG_DIR);
        if(!FileExist( Ninjins_Bounty_System_LOGGER_LOG_DIR))
            MakeDirectory( Ninjins_Bounty_System_LOGGER_LOG_DIR);
    }
    void Save()
    {
        JsonFileLoader<Ninjins_Bounty_SystemLoggingSettings>.JsonSaveFile( Ninjins_Bounty_System_LOGGER_CONFIG_FILE, this);
    }
    static Ninjins_Bounty_SystemLoggingSettings Load()
    {
        Ninjins_Bounty_SystemLoggingSettings settings = new Ninjins_Bounty_SystemLoggingSettings();
        settings.MakeDirectoryIfNotExists();
        if(FileExist( Ninjins_Bounty_System_LOGGER_CONFIG_FILE))
        {
            JsonFileLoader<Ninjins_Bounty_SystemLoggingSettings>.JsonLoadFile( Ninjins_Bounty_System_LOGGER_CONFIG_FILE, settings);
            return settings;
        }
        settings.Save();
        return settings;
    }
}