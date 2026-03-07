static Ninjins_Bounty_SystemLoggingModule GetNinjins_Bounty_SystemLogger()
{
    return Ninjins_Bounty_SystemLoggingModule.Cast(CF_ModuleCoreManager.Get(Ninjins_Bounty_SystemLoggingModule));
}
[CF_RegisterModule(Ninjins_Bounty_SystemLoggingModule)]
class Ninjins_Bounty_SystemLoggingModule : CF_ModuleGame
{
    private int networkSync_LogLevel;
    ref Ninjins_Bounty_SystemLoggingSettings settings;
    FileHandle fileHandle;
    float dtime = 0;
    override void OnInit()
    {
        super.OnInit();
        EnableUpdate();
        EnableMissionStart();
    }
    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);
        fileHandle = CreateNewLogFile();
        if(IsMissionHost())
        {
            settings = Ninjins_Bounty_SystemLoggingSettings.Load();
            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }
    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;
		 Param1<int> data;
		 if (!ctx.Read(data))
            return;
		 networkSync_LogLevel = data.param1;
	}
    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }
    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);
        if(!IsMissionHost())
            return;
        if(!settings)
            return;
        dtime += update.DeltaTime;
        if(dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;
            settings = Ninjins_Bounty_SystemLoggingSettings.Load();
            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }
    void MakeDirectoryIfNotExists()
    {
        if(!FileExist(Ninjins_Bounty_System_ROOT_FOLDER))
            MakeDirectory(Ninjins_Bounty_System_ROOT_FOLDER);
        if(!FileExist(Ninjins_Bounty_System_LOG_FOLDER))
            MakeDirectory(Ninjins_Bounty_System_LOG_FOLDER);
        if(!FileExist(Ninjins_Bounty_System_LOGGER_CONFIG_DIR))
            MakeDirectory(Ninjins_Bounty_System_LOGGER_CONFIG_DIR);
        if(!FileExist(Ninjins_Bounty_System_LOGGER_LOG_DIR))
            MakeDirectory(Ninjins_Bounty_System_LOGGER_LOG_DIR);
    }
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }
    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }
    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();
        return dateStr + "-" + timeStr;
    }
    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();
        string filePath = string.Format(Ninjins_Bounty_System_LOGGER_LOG_FILE, GenerateFullTimestamp());
        fileHandle = OpenFile(filePath, FileMode.WRITE);
        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }
        return null;
    }
    void Log(string content, Ninjins_Bounty_SystemLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }
    void LogInfo(string content)
    {
        Log(content, Ninjins_Bounty_SystemLogLevel.Info);
    }
    void LogWarning(string content)
    {
        Log(content, Ninjins_Bounty_SystemLogLevel.Warn);
    }
    void LogError(string content)
    {
        Log(content, Ninjins_Bounty_SystemLogLevel.Error);
    }
    void LogDebug(string content)
    {
        Log(content, Ninjins_Bounty_SystemLogLevel.Debug);
    }
    string GetLogLevelString(Ninjins_Bounty_SystemLogLevel logLevel)
    {
        switch(logLevel)
        {
             case Ninjins_Bounty_SystemLogLevel.Debug:
                return "DEBUG";
            case Ninjins_Bounty_SystemLogLevel.Info:
                return "INFO";
            case Ninjins_Bounty_SystemLogLevel.Warn:
                return "WARNING";
            case Ninjins_Bounty_SystemLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }
        return "";
    }
}