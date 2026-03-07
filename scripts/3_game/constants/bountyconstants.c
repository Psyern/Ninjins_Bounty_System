const string Ninjins_Bounty_System_ROOT_FOLDER = "$profile:Ninjins_Bounty_System\\";
const string Ninjins_Bounty_System_LOG_FOLDER = Ninjins_Bounty_System_ROOT_FOLDER + "Logging\\";
const string Ninjins_Bounty_System_LOGGER_CONFIG_DIR = Ninjins_Bounty_System_LOG_FOLDER + "Config\\";
const string Ninjins_Bounty_System_LOGGER_CONFIG_FILE = Ninjins_Bounty_System_LOGGER_CONFIG_DIR + "LoggingSettings.json";
const string Ninjins_Bounty_System_LOGGER_LOG_DIR = Ninjins_Bounty_System_LOG_FOLDER + "Logs\\";
const string Ninjins_Bounty_System_LOGGER_LOG_FILE = Ninjins_Bounty_System_LOGGER_LOG_DIR + "Ninjins_Bounty_System_%1.log";
const int BOUNTY_NOTIFICATION_PLACED_HUNTED = 0;
const int BOUNTY_NOTIFICATION_PLACED_EXPIRED = 1;
const int BOUNTY_NOTIFICATION_PLACED_SURVIVAL_REWARD = 2;
const int BOUNTY_NOTIFICATION_PLACED_KILLED_REWARD = 3;
const int BOUNTY_NOTIFICATION_PLACED_BROADCAST = 4;
const int BOUNTY_NOTIFICATION_RULE_BREAKER_HUNTED = 5;
const int BOUNTY_NOTIFICATION_RULE_BREAKER_EXPIRED = 6;
const int BOUNTY_NOTIFICATION_RULE_BREAKER_HIT_WARNING = 7;
const int BOUNTY_NOTIFICATION_RULE_BREAKER_BROADCAST = 8;
const int BOUNTY_NOTIFICATION_SKIP_SUCCESS = 9;
const int BOUNTY_NOTIFICATION_SKIP_NO_PLAYERS = 10;
const int BOUNTY_NOTIFICATION_BOUNTY_SKIPPED = 11;
const int BOUNTY_NOTIFICATION_INSUFFICIENT_TOKENS = 12;
const int BOUNTY_NOTIFICATION_REWARD_HANDS_NOT_FREE = 13;
const int BOUNTY_NOTIFICATION_PLAYER_ON_COOLDOWN = 14;
const int BOUNTY_NOTIFICATION_PLAYER_IN_SAFEZONE = 15;
const int BOUNTY_NOTIFICATION_CONFIG_RELOAD_SUCCESS = 16;
const int BOUNTY_NOTIFICATION_CONFIG_RELOAD_FAILURE = 17;
const int BOUNTY_NOTIFICATION_REWARD_CONTAINER_SPAWN_FAILURE = 18;
const int BOUNTY_NOTIFICATION_SURVIVAL_REWARD_CONTAINER_SPAWN_FAILURE = 19;
const int BOUNTY_NOTIFICATION_COMMAND_ACCESS_DENIED = 20;
const int BOUNTY_NOTIFICATION_BOUNTY_PERSISTED = 21;
const int BOUNTY_NOTIFICATION_TELEPORTED_OUT_OF_TERRITORY = 22;
const int BOUNTY_NOTIFICATION_BOUNTY_PAUSED_IN_TERRITORY = 23;
const int BOUNTY_NOTIFICATION_BOUNTY_RESUMED_FROM_TERRITORY = 24;
const int BOUNTY_NOTIFICATION_REWARD_INVENTORY_FULL = 25;
const float BOUNTY_MS_TO_SECONDS = 1000.0; 
const float BOUNTY_SECONDS_PER_HOUR = 3600.0; 
const float BOUNTY_SECONDS_PER_DAY = 86400.0; 
const int BOUNTY_SAFEZONE_CHECK_DELAY_MS = 2000; 
const float BOUNTY_DEFAULT_TELEPORT_DISTANCE = 50.0; 
const float BOUNTY_FALLBACK_TELEPORT_DISTANCE = 200.0; 
const float BOUNTY_DEFAULT_TERRITORY_SIZE = 150.0; 
const float BOUNTY_GROUND_OFFSET = 0.5; 
const int BOUNTY_TELEPORT_SEARCH_MIN_RADIUS = 50; 
const int BOUNTY_TELEPORT_SEARCH_MAX_RADIUS = 500; 
const int BOUNTY_TELEPORT_SEARCH_RADIUS_STEP = 50; 
const int BOUNTY_TELEPORT_SEARCH_ANGLE_STEP = 45; 
const int BOUNTY_DEGREES_IN_CIRCLE = 360; 
const float BOUNTY_STALE_DURATION_THRESHOLD_PERCENT = 1.0; 
const string BOUNTY_PLAYER_NAME_UNKNOWN = "Unknown";
const string BOUNTY_TYPE_STRING_PLACED = "PLACED";
const string BOUNTY_TYPE_STRING_RULE_BREAKER = "RULE_BREAKER";
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
class BountyUISettingsData
{
    float PositionX;
    float PositionY;
    float Width;
    float Height;
    int BackgroundColor;
    int TextColor;
    void BountyUISettingsData(float posX = 0.0, float posY = 0.0, float width = 0.0, float height = 0.0, int bgColor = 0, int textColor = 0)
    {
        PositionX = posX;
        PositionY = posY;
        Width = width;
        Height = height;
        BackgroundColor = bgColor;
        TextColor = textColor;
    }
}
class BountyPlayerData
{
    string PlayerID;
    string PlayerName;
    vector Position;
    float TimeRemaining;
    float CircleRadius;
    int CircleColor;
    bool ReduceRadiusOverTime;
    bool IncreaseRadiusOverTime;
    float CircleMinRadius;
    float BountyDurationSeconds;
    float CircleOffsetMinMultiplier;
    float CircleOffsetMaxMultiplier;
    float CachedOffsetMultiplier; 
    float CachedOffsetAngle; 
    vector CircleCenter; 
    void BountyPlayerData()
    {
        PlayerID = "";
        PlayerName = "";
        Position = "0 0 0";
        TimeRemaining = 0.0;
        CircleRadius = 100.0;
        CircleColor = ARGB(255, 255, 0, 0);
        ReduceRadiusOverTime = false;
        IncreaseRadiusOverTime = false;
        CircleMinRadius = 10.0;
        BountyDurationSeconds = 60.0;
        CircleOffsetMinMultiplier = 0.0;
        CircleOffsetMaxMultiplier = 0.0;
        CachedOffsetMultiplier = 0.0;
        CachedOffsetAngle = 0.0;
        CircleCenter = "0 0 0";
    }
}
class BountyMapBridge
{
    private static ref array<ref BountyPlayerData> s_BountiedPlayersData;
    static void SetBountiedPlayers(array<ref BountyPlayerData> players)
    {
        if (!IsMissionClient())
            return;
        if (!s_BountiedPlayersData)
        {
            s_BountiedPlayersData = new array<ref BountyPlayerData>();
        }
        s_BountiedPlayersData.Clear();
        if (players)
        {
            int i;
            BountyPlayerData playerData;
            for (i = 0; i < players.Count(); i++)
            {
                playerData = players.Get(i);
                if (playerData)
                {
                    s_BountiedPlayersData.Insert(playerData);
                }
            }
        }
    }
    static array<ref BountyPlayerData> GetBountiedPlayers()
    {
        if (!s_BountiedPlayersData)
        {
            s_BountiedPlayersData = new array<ref BountyPlayerData>();
        }
        return s_BountiedPlayersData;
    }
}