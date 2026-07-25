const string obfv_Ninjins_Bounty_System_ROOT_FOLDER = "$profile:Ninjins_Bounty_System\\";
const string obfv_Ninjins_Bounty_System_LOG_FOLDER = obfv_Ninjins_Bounty_System_ROOT_FOLDER + "Logging\\";
const string obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR = obfv_Ninjins_Bounty_System_LOG_FOLDER + "Config\\";
const string obfv_Ninjins_Bounty_System_LOGGER_CONFIG_FILE = obfv_Ninjins_Bounty_System_LOGGER_CONFIG_DIR + "LoggingSettings.json";
const string obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR = obfv_Ninjins_Bounty_System_LOG_FOLDER + "Logs\\";
const string obfv_Ninjins_Bounty_System_LOGGER_LOG_FILE = obfv_Ninjins_Bounty_System_LOGGER_LOG_DIR + "Ninjins_Bounty_System_%1.log";
const int obfv_BOUNTY_NOTIFICATION_PLACED_HUNTED = 0;
const int obfv_BOUNTY_NOTIFICATION_PLACED_EXPIRED = 1;
const int obfv_BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD = 2;
const int obfv_BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD = 3;
const int obfv_BOUNTY_NOTIFICATION_PLACED_BROADCAST = 4;
const int obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED = 5;
const int obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED = 6;
const int obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING = 7;
const int obfv_BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST = 8;
const int obfv_BOUNTY_NOTIFICATION_SKIP_SUCCESS = 9;
const int obfv_BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS = 10;
const int obfv_BOUNTY_NOTIFICATION_BOUNTY_SKIPPED = 11;
const int obfv_BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS = 12;
const int obfv_BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE = 13;
const int obfv_BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN = 14;
const int obfv_BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE = 15;
const int obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS = 16;
const int obfv_BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE = 17;
const int obfv_BOUNTY_NOTIFICATION_REWARD_CONTAINER_SPAWN_FAILURE = 18;
const int obfv_BOUNTY_NOTIFICATION_SURVIVAL_REWARD_CONTAINER_SPAWN_FAILURE = 19;
const int obfv_BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED = 20;
const int obfv_BOUNTY_NOTIFICATION_BOUNTY_PERSISTED = 21;
const int obfv_BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY = 22;
const int obfv_BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY = 23;
const int obfv_BOUNTY_NOTIFICATION_BOUNTY_RESUMED_FROM_TERRITORY = 24;
const int obfv_BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL = 25;
const float obfv_BOUNTY_MS_TO_SECONDS = 1000.0; 
const float obfv_BOUNTY_SECONDS_PER_HOUR = 3600.0; 
const float obfv_BOUNTY_SECONDS_PER_DAY = 86400.0; 
const int obfv_BOUNTY_SAFEZONE_CHECK_DELAY_MS = 2000; 
const float obfv_BOUNTY_DEFAULT_TELEPORT_DISTANCE = 50.0; 
const float obfv_BOUNTY_FALLBACK_TELEPORT_DISTANCE = 200.0; 
const float obfv_BOUNTY_DEFAULT_TERRITORY_SIZE = 150.0; 
const float obfv_BOUNTY_GROUND_OFFSET = 0.5; 
const int obfv_BOUNTY_TELEPORT_SEARCH_MIN_RADIUS = 50; 
const int obfv_BOUNTY_TELEPORT_SEARCH_MAX_RADIUS = 500; 
const int obfv_BOUNTY_TELEPORT_SEARCH_RADIUS_STEP = 50; 
const int obfv_BOUNTY_TELEPORT_SEARCH_ANGLE_STEP = 45; 
const int obfv_BOUNTY_DEGREES_IN_CIRCLE = 360; 
const float obfv_BOUNTY_STALE_DURATION_THRESHOLD_PERCENT = 1.0; 
const string obfv_BOUNTY_PLAYER_NAME_UNKNOWN = "Unknown";
const string obfv_BOUNTY_TYPE_STRING_PLACED = "PLACED";
const string obfv_BOUNTY_TYPE_STRING_RULE_BREAKER = "RULE_BREAKER";
enum BountyType
{
	PLACED,         
	RULE_BREAKER    
}
enum BountyEndReason
{
	EXPIRED,        
	KILLED,         
	SUICIDE,        
	CLEARED,        
	LOGOUT          
}
enum BountyRPC
{           
	UPDATE_BOUNTY_STATE = 33115511,
	SYNC_BOUNTIED_PLAYERS,
	SYNC_ADMIN_STATUS,
	UPDATE_BOUNTY_COUNTDOWN
}
class obfc_BountyUISettingsData
{
	float obfv_PositionX;
	float obfv_PositionY;
	float obfv_Width;
	float obfv_Height;
	int obfv_BackgroundColor;
	int obfv_TextColor;
	void obfc_BountyUISettingsData(float posX = 0.0, float posY = 0.0, float width = 0.0, float height = 0.0, int bgColor = 0, int textColor = 0)
	{
		obfv_PositionX = posX;
		obfv_PositionY = posY;
		obfv_Width = width;
		obfv_Height = height;
		obfv_BackgroundColor = bgColor;
		obfv_TextColor = textColor;
	}
}
class obfc_BountyPlayerData
{
	string obfv_PlayerID;
	string obfv_PlayerName;
	vector Position;
	float obfv_TimeRemaining;
	float obfv_CircleRadius;
	int obfv_CircleColor;
	bool obfv_ReduceRadiusOverTime;
	bool obfv_IncreaseRadiusOverTime;
	float obfv_CircleMinRadius;
	float BountyDurationSeconds;
	float obfv_CircleOffsetMinMultiplier;
	float obfv_CircleOffsetMaxMultiplier;
	float obfv_CachedOffsetMultiplier; 
	float obfv_CachedOffsetAngle; 
	vector obfv_CircleCenter; 
	void obfc_BountyPlayerData()
	{
		obfv_PlayerID = "";
		obfv_PlayerName = "";
		Position = "0 0 0";
		obfv_TimeRemaining = 0.0;
		obfv_CircleRadius = 100.0;
		obfv_CircleColor = ARGB(255, 255, 0, 0);
		obfv_ReduceRadiusOverTime = false;
		obfv_IncreaseRadiusOverTime = false;
		obfv_CircleMinRadius = 10.0;
		BountyDurationSeconds = 60.0;
		obfv_CircleOffsetMinMultiplier = 0.0;
		obfv_CircleOffsetMaxMultiplier = 0.0;
		obfv_CachedOffsetMultiplier = 0.0;
		obfv_CachedOffsetAngle = 0.0;
		obfv_CircleCenter = "0 0 0";
	}
}
class obfc_BountyMapBridge
{
	private static ref array<ref obfc_BountyPlayerData> obfv_s_BountiedPlayersData;
	static void obfm_SetBountiedPlayers(array<ref obfc_BountyPlayerData> players)
	{
		if (!IsMissionClient())
			return;
		if (!obfv_s_BountiedPlayersData)
		{
			obfv_s_BountiedPlayersData = new array<ref obfc_BountyPlayerData>();
		}
		obfv_s_BountiedPlayersData.Clear();
		if (players)
		{
			int i;
			obfc_BountyPlayerData playerData;
			for (i = 0; i < players.Count(); i++)
			{
				playerData = players.Get(i);
				if (playerData)
				{
					obfv_s_BountiedPlayersData.Insert(playerData);
				}
			}
		}
	}
	static array<ref obfc_BountyPlayerData> obfm_GetBountiedPlayers()
	{
		if (!obfv_s_BountiedPlayersData)
		{
			obfv_s_BountiedPlayersData = new array<ref obfc_BountyPlayerData>();
		}
		return obfv_s_BountiedPlayersData;
	}
}