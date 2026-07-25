static obfc_Ninjins_Bounty_SystemLoggingModule obfm_GetNinjins_Bounty_SystemLogger()
{
	return obfc_Ninjins_Bounty_SystemLoggingModule.Cast(CF_ModuleCoreManager.Get(obfc_Ninjins_Bounty_SystemLoggingModule));
}
[CF_RegisterModule(obfc_Ninjins_Bounty_SystemLoggingModule)]
class obfc_Ninjins_Bounty_SystemLoggingModule : CF_ModuleGame
{
	private int networkSync_LogLevel;
	ref obfc_Ninjins_Bounty_SystemLoggingSettings obfv_settings;
	FileHandle obfv_fileHandle;
	float obfv_dtime = 0;
	override void OnInit()
	{
		super.OnInit();
		EnableUpdate();
		EnableMissionStart();
	}
	override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);
		obfv_fileHandle = obfm_CreateNewLogFile();
		if(IsMissionHost())
		{
			obfv_settings = obfc_Ninjins_Bounty_SystemLoggingSettings.obfm_Load();
			networkSync_LogLevel = obfv_settings.logLevel;
			obfm_SynchLogLevel();       
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
	void obfm_SynchLogLevel()
	{
		GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
	}
	override void OnUpdate(Class sender, CF_EventArgs args)
	{
		super.OnUpdate(sender, args);
		CF_EventUpdateArgs update = CF_EventUpdateArgs.Cast(args);
		if(!update)
			return;
		if(!IsMissionHost())
			return;
		if(!obfv_settings)
			return;
		obfv_dtime += update.DeltaTime;
		if(obfv_dtime >= obfv_settings.refreshRateInSeconds)
		{
			obfv_dtime = 0;
			obfv_settings = obfc_Ninjins_Bounty_SystemLoggingSettings.obfm_Load();
			networkSync_LogLevel = obfv_settings.logLevel;
			obfm_SynchLogLevel();
		}
	}
	void obfm_MakeDirectoryIfNotExists()
	{
		if(!FileExist(obfv_Ninjins_Bounty_System_ROOT_FOLDER))
			MakeDirectory(obfv_Ninjins_Bounty_System_ROOT_FOLDER);
		if(!FileExist(obfv_Ninjins_Bounty_System_LOG_FOLDER))
			MakeDirectory(obfv_Ninjins_Bounty_System_LOG_FOLDER);
		if(!FileExist(obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR))
			MakeDirectory(obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR);
		if(!FileExist(obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR))
			MakeDirectory(obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR);
	}
	string obfm_GenerateShortDateString()
	{
		int year;
		int month;
		int day;
		GetYearMonthDay(year, month, day);
		return "" + year + "_" + month + "_" + day;
	}
	string obfm_GenerateShortTimeString()
	{
		int hour;
		int minute;
		int second;
		GetHourMinuteSecond(hour, minute, second);
		return "" + hour + "_" + minute + "_" + second;
	}
	string obfm_GenerateFullTimestamp()
	{
		string dateStr = obfm_GenerateShortDateString();
		string timeStr = obfm_GenerateShortTimeString();
		return dateStr + "-" + timeStr;
	}
	FileHandle obfm_CreateNewLogFile()
	{
		obfm_MakeDirectoryIfNotExists();
		string filePath = string.Format(obfv_Ninjins_Bounty_System_LOGGER_LOG_FILE, obfm_GenerateFullTimestamp());
		obfv_fileHandle = OpenFile(filePath, FileMode.WRITE);
		if(obfv_fileHandle != 0)
		{
			FPrintln(obfv_fileHandle, "Creation Time: " + obfm_GenerateFullTimestamp());
			return obfv_fileHandle;
		}
		return null;
	}
	void obfm_Log(string content, Ninjins_Bounty_SystemLogLevel logLevel)
	{
		if(logLevel < networkSync_LogLevel)
			return;
		string timestamp = obfm_GenerateShortTimeString();
		FPrintln(obfv_fileHandle, timestamp + " | " + obfm_GetLogLevelString(logLevel) + " | " + content);
	}
	void obfm_LogInfo(string content)
	{
		obfm_Log(content, Ninjins_Bounty_SystemLogLevel.Info);
	}
	void obfm_LogWarning(string content)
	{
		obfm_Log(content, Ninjins_Bounty_SystemLogLevel.Warn);
	}
	void obfm_LogError(string content)
	{
		obfm_Log(content, Ninjins_Bounty_SystemLogLevel.Error);
	}
	void obfm_LogDebug(string content)
	{
		obfm_Log(content, Ninjins_Bounty_SystemLogLevel.Debug);
	}
	string obfm_GetLogLevelString(Ninjins_Bounty_SystemLogLevel logLevel)
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