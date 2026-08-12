# Ninjins Bounty System

<p align="center">
  <img src="psyern_ninjin_bounty_mod.png" alt="Psyern × Ninjin — Ninjins Bounty System" width="900">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/DayZ-1.29+-0074D9?style=for-the-badge&logo=steam&logoColor=white" alt="DayZ 1.29+">
  <img src="https://img.shields.io/badge/Enforce_Script-Enfusion-FF851B?style=for-the-badge" alt="Enforce Script">
  <img src="https://img.shields.io/badge/Requires-Community_Framework-9B59B6?style=for-the-badge" alt="Requires CF">
  <img src="https://img.shields.io/badge/Maintained_Fork-1.29+-2ECC40?style=for-the-badge" alt="Maintained Fork">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Expansion-Safezones_%7C_Territories_%7C_Parties_%7C_Hardline-E74C3C?style=flat-square" alt="Expansion">
  <img src="https://img.shields.io/badge/LB_Master-Advanced_Groups_%7C_Map-1ABC9C?style=flat-square" alt="LB Master">
  <img src="https://img.shields.io/badge/NinjinsPvPPvE-Safezones_%7C_Rule_Breaker-F39C12?style=flat-square" alt="NinjinsPvPPvE">
  <img src="https://img.shields.io/badge/VanillaPP-Map_Drawing-3498DB?style=flat-square" alt="VanillaPP Map">
  <img src="https://img.shields.io/badge/Ninjins_Upgraded_v3-Bridge_Addon-8E44AD?style=flat-square" alt="Ninjins Upgraded v3 Bridge">
</p>

<p align="center">
  <b>A server-authoritative bounty / manhunt system for DayZ</b><br>
  Players put a price on another player's head at a bounty board. The server validates the hunt,
  the kill and the payout — the client only draws the UI.
</p>

<p align="center">
  <a href="https://deadmans-echo.de">
    <img src="https://img.shields.io/badge/Community-Deadmans_Echo-F0C040?style=for-the-badge" alt="Deadmans Echo">
  </a>
</p>

> **Maintenance notice (DayZ 1.29+)**
>
> With the DayZ **1.29** update, maintenance and updates of this mod moved to **Psyern**.
> **Ninjin (Naij0)** — the original author — is back and now develops this mod together with
> **Psyern**. The goal stays compatibility, stability and minimal disruption for communities
> already running the mod.

---

## Repository Layout

```text
Ninjins_Bounty/                        ← repository root (this README)
├── Ninjins_Bounty_System/             ← the DayZ mod (pack this folder)
│   ├── config.cpp                     ← CfgPatches / CfgMods / CfgVehicles
│   ├── data/                          ← board, crate & token models + textures
│   ├── gui/                           ← icons and .layout files
│   └── scripts/                       ← 3_game / 4_world / 5_mission
├── Ninjins_Bounty_V3_Bridge/          ← optional addon: Ninjins Upgraded v3 integration
│   ├── config.cpp                     ← requires Bounty System + Core + Upgraded Zones
│   ├── gui/layouts/Admin/             ← server sidebar form + group label
│   ├── scripts/                       ← Common / 3_Game / 4_World / 5_Mission
│   └── BOUNTY_SYSTEM_CHANGES.md       ← which base-mod hooks the bridge relies on
└── README.md
```

The bounty mod is a **single PBO source folder**. No companion service, no web backend — everything
runs inside the DayZ server. The **v3 bridge** is a second, optional PBO that is only needed on
servers running the Ninjins Upgraded v3 stack — see
[Ninjins Upgraded v3 Bridge](#ninjins-upgraded-v3-bridge).

---

## Features

<table>
<tr>
<td width="33%" valign="top">

### Bounty Gameplay
- Player-placed bounties at the board
- Per-minute or flat token pricing
- Skip the current bounty for tokens
- Rule Breaker bounties (PvE offenders)
- Automated bounty placement
- Bounty warning countdown
- Live countdown HUD widget
- Map circle with shrinking radius
- Survival reward if the timer runs out

</td>
<td width="33%" valign="top">

### Rules & Zones
- Safezone pause **or** teleport-out
- Territory pause / teleport-out
- Static zones for API-less mods
- Friendly-fire kills don't count
- Suicide doesn't end the bounty
- Bounty survives logout & restart
- Cooldown per player
- Minimum lifetime & player count
- Blacklist (SteamID64 **or** GUID)

</td>
<td width="33%" valign="top">

### Admin & Ops
- In-game admin menu (keybind)
- Live config editing over RPC
- Reload all configs without restart
- Place / clear bounties on players
- Clear cooldowns
- Blacklist management in-game
- Daily rotating log file
- Auto-spawned board placements
- Overridable integration hooks
- Obfuscation-ready source

</td>
</tr>
</table>

### Notifications

Every entry is individually toggleable and carries its own `Title`, `Message` and `IconPath`.

| Group | Notification | Trigger |
|---|---|---|
| `PlacedBounty` | Hunted | A bounty was placed on the player |
| `PlacedBounty` | Expired | The bounty timer ran out |
| `PlacedBounty` | SurvivalReward | Player survived their own bounty |
| `PlacedBounty` | KilledReward | Player claimed a bounty kill |
| `RuleBreaker` | Hunted / HitWarning / Expired / SurvivalReward / KilledReward | Rule Breaker equivalents + hit-threshold warning |
| `Other` | InsufficientTokens | Not enough bounty tokens |
| `Other` | SkipBountyNoPlayers / SkipBountySuccess / BountySkipped | Skip flow |
| `Other` | RewardHandsNotFree | Hands occupied while claiming |
| `Other` | PlayerOnCooldown | Target is on bounty cooldown |
| `Other` | PlayerInSafeZone | Target sits in a safezone |
| `Other` | BountyPersisted | Bounty restored after relog |
| `Other` | TeleportedOutOfTerritory | Player was moved out of their territory |
| `Other` | BountyPausedInTerritory | Timer paused inside own territory |
| `Other` | BountyPausedInSafeZone | Timer paused inside a safezone |

### Broadcasts

Server-wide messages. Placeholders are replaced at send time.

| Broadcast | Placeholders | Trigger |
|---|---|---|
| `PlacedBounty` | `{PLAYER}` | A player bounty went live |
| `RuleBreaker` | `{PLAYER}` | A Rule Breaker bounty went live |
| `Warning` | `{PLAYER}` `{TIME}` | `BountyWarningTimeSeconds` countdown started |
| `Expired` | `{PLAYER}` | Bounty timer ran out |
| `Win` | `{PLAYER}` `{WINNER}` | Bounty target was killed by a player |
| `Suicide` | `{PLAYER}` `{SUICIDE_PHRASE}` | Target died without a player killer |
| `Logout` | `{PLAYER}` | Target logged out while bountied |

---

## Quick Start

```
1. Add Ninjins_Bounty_System to your server mod load order (after CF)
2. Start the server once → all JSON configs generate under $profile:Ninjins_Bounty_System\Config\
3. Set Core.EnableBountySystem to true in BountyConfig.json (it ships disabled)
4. Put your SteamID64 or GUID into Admins.json
5. Place a bounty board (BountyBoardPlacements.json or in-world object)
6. Bind the Admin Menu key in Settings → Controls → "Bounty Mod" → restart → done
```

---

## Mod Structure

```text
Ninjins_Bounty_System/
├── config.cpp                          ← CfgPatches / CfgMods / CfgVehicles
├── data/
│   ├── inputs.xml                      ← Admin Menu keybind ("Bounty Mod" group)
│   ├── ninjins_bounty_board/           ← board model + textures
│   ├── ninjins_bounty_crate/           ← reward crate model + textures
│   └── ninjins_bounty_token/           ← token model, textures, config.cpp
├── gui/
│   ├── icons/                          ← bountyskull / bountycheckmark / bountyerror (.edds)
│   └── layouts/
│       ├── ninjinsbountyboard.layout   ← bounty board menu
│       ├── bountyadminmenu.layout      ← admin menu
│       ├── bountycountdowntimer.layout ← HUD countdown widget
│       └── bountymapcanvasonly.layout  ← map drawing canvas
└── scripts/
    ├── 3_game/
    │   ├── constants/       bountyconstants.c        ← paths, notification IDs, BountyRPC enum
    │   ├── general configs/ bountyconfig.c           ← every JSON config class
    │   ├── loggermodule/    loggingmodule.c, loggingsettings.c, enum.c
    │   └── notifications/   bountynotifications.c
    ├── 4_world/
    │   ├── actions/         actionopenbountymenu.c, actionconstructor.c
    │   ├── anims/           anim.c
    │   ├── bountymanager/   bountymanager.c, bountyrewardcontainerhelper.c
    │   ├── damagesystem/    bountydamagesystem.c     ← rule breaker hit tracking
    │   ├── entities/        playerbase.c, ninjins_bounty_board_static.c
    │   ├── bountymodule.c                            ← CF RPC hub + admin actions
    │   └── expansionterritorymodule.c
    └── 5_mission/
        ├── gui/             bountyadminmenu.c, ninjinsbountyboardmenu.c
        ├── mapdrawer/       bountymapsystem.c
        ├── plugins/maps/    vanilla, expansion, lb, vanillaplusplus
        ├── missiongameplay.c                         ← client RPC + keybind
        └── missionserver.c                           ← server init
```

## Profile Structure

```text
profiles/Ninjins_Bounty_System/
├── Config/
│   ├── BountyConfig.json               ← core, rules, rewards, map, UI, notifications
│   ├── BountySuccessRewardConfig.json  ← reward sections, loot items, currency
│   ├── BountyZones.json                ← static safezones / territories
│   ├── Admins.json                     ← admin SteamID64s / GUIDs
│   ├── Blacklist.json                  ← players excluded from bounties
│   └── BountyBoardPlacements.json      ← auto-spawned board positions
└── Logging/
    ├── Config/LoggingSettings.json
    └── Logs/Ninjins_Bounty_System_2026-08-09.log
```

---

## Configuration

All configs are plain JSON and are generated with defaults on first server start.
Missing keys in an existing file are filled with their defaults on load, so updating the mod never
requires hand-editing.

### `BountyConfig.json` → `Core`

| Field | Default | Description |
|---|---|---|
| `EnableBountySystem` | `false` | Master switch — **off by default**, enable it once the rest of the config fits your server |
| `BountyCooldownSeconds` | `3600` | Per-player cooldown before a new bounty can target them |
| `MaxBountiedPlayers` | `-1` | Concurrent bounties, `-1` = unlimited |
| `MinOnlinePlayersRequired` | `1` | Minimum online players for a bounty to start |
| `DisableSelfBounty` | `true` | Block placing a bounty on yourself |
| `PlaceBountyTokenRequired` | `20` | Flat token price to place a bounty |
| `SkipBountyTokenRequired` | `10` | Token price to skip the current bounty |
| `BountyTokenClassNames` | `["Ninjins_Bounty_Token_Gold"]` | Item classnames accepted as tokens |
| `MinimumPlayerLifetimeSeconds` | `900` | Fresh spawns below this lifetime can't be bountied |
| `PersistentBountyAfterLogOut` | `true` | Bounty survives logout and server restart |
| `DontCountSuicide` | `true` | Non-player death keeps the bounty running |
| `DontCountFriendlyFire` | `true` | Group/party kill pays nothing and doesn't end the bounty |
| `PauseBountyInSafeZone` | `false` | Pause the timer in a safezone instead of teleporting out |
| `TeleportOutOfSafeZone` | `true` | Teleport bountied players out of safezones |
| `TeleportOutOfSafeZoneDistance` | `150.0` | Distance to move them |
| `PauseBountyInTerritory` | `true` | Pause the timer inside the player's own territory |
| `TeleportOutOfOwnTerritory` | `true` | Teleport bountied players out of their own territory |
| `ResumeBountyDistanceFromTerritory` | `50.0` | Distance from the edge before the timer resumes |
| `PausedBountyResumeCheckInterval` | `5.0` | Seconds between paused-state re-checks |
| `BountyWarningTimeSeconds` | `0.0` | `0` = no warning, `> 0` = broadcast first, apply after N seconds |
| `BountyRequestCostPerMinute` | `0` | `> 0` enables per-minute pricing at the board |
| `BountyRequestMinMinutes` | `1` | Lower clamp for the board duration field |
| `BountyRequestMaxMinutes` | `60` | Upper clamp for the board duration field |
| `EnableAutomatedBountyPlacement` | `false` | Server places bounties on its own |
| `AutomatedBountyPlacementIntervalSeconds` | `3600.0` | Interval for automated placement |
| `SuicidePhrases` | 8 phrases | One is picked at random for `Broadcasts.Suicide` |
| `EnableConfigReloadSuccessNotification` | `true` | Confirm config reloads to the admin |
| `EnableCommandAccessDeniedNotification` | `true` | Tell non-admins their command was rejected |

> **Mutually exclusive:** `PauseBountyInSafeZone` and `TeleportOutOfSafeZone`. If both are enabled,
> the pause wins and the teleport is disabled automatically with a warning in the log.

> **Per-minute pricing:** while `BountyRequestCostPerMinute > 0`, the bounty board shows a duration
> field with a live cost readout and the server charges `minutes × cost`. Set it to `0` to keep the
> flat `PlaceBountyTokenRequired` price and the fixed `PlacedBounty.BountyDurationSeconds`.

### `BountyConfig.json` → `RuleBreaker`

Rule Breaker bounties punish players who break the server's PvE rules.

| Field | Default | Description |
|---|---|---|
| `EnablePvEToPvPRuleBreaker` | `true` | Attacking in a PvE zone flags the attacker |
| `PvEToPvPInstantRuleBreakerHits` | `0` | Hits until an instant bounty, `0` = immediately |
| `EnableRuleBreakerHitThreshold` | `false` | Enable the hits-over-time threshold |
| `RuleBreakerHitThresholdTime` | `10.0` | Time window in seconds |
| `RuleBreakerHitThresholdWarningHits` | `10` | Hits inside the window that trigger a warning |
| `RuleBreakerHitThresholdBountyHits` | `15` | Hits inside the window that trigger the bounty |
| `BountyRuleBreakerDurationSeconds` | `3600.0` | Rule Breaker bounty duration |
| `ClearPendingRewardsOnRuleBreakerBounty` | `false` | Wipe unclaimed rewards when flagged |
| `AllowPvEToPvEVictimKill` | `false` | Let the victim retaliate without being flagged |
| `Expansion_EnableHardlineReputationDecrease` | `false` | Deduct Expansion Hardline reputation |
| `Expansion_HardlineReputationDecreaseAmount` | `10` | Amount deducted |

### `BountyConfig.json` → `PlacedBounty` · `Reward` · `UI` · `Map`

| Section | Field | Default | Description |
|---|---|---|---|
| `PlacedBounty` | `BountyDurationSeconds` | `60.0` | Duration for a flat-priced bounty |
| `Reward` | `EnableSurvivalReward` | `true` | Reward the target for surviving |
| `Reward` | `PvERuleBreakerGiveRewards` | `false` | Pay out on Rule Breaker bounties |
| `UI` | `CountdownWidgetPositionX/Y` | `0.0` | HUD countdown position |
| `UI` | `CountdownWidgetWidth/Height` | `0.0` | HUD countdown size |
| `UI` | `CountdownWidgetBackgroundColor` | `0` | ARGB background |
| `UI` | `CountdownWidgetTextColor` | `0` | ARGB text |
| `Map` | `BountyEnableMapDrawing` | `true` | Draw the bounty circle on the map |
| `Map` | `BountyCircleRadius` | `100.0` | Starting radius in meters |
| `Map` | `BountyCircleMinRadius` | `10.0` | Lower bound while shrinking |
| `Map` | `BountyCircleReduceRadiusOverTime` | `true` | Circle tightens as the timer runs |
| `Map` | `BountyCircleIncreaseRadiusOverTime` | `false` | Circle widens instead |
| `Map` | `BountyCircleColor` | `ARGB(255,255,0,0)` | Circle color |
| `Map` | `BountyCircleDrawingWidth` | `2` | Line width |
| `Map` | `BountyCircleOffsetMinMultiplier` | `0.1` | Random offset of the circle center (min) |
| `Map` | `BountyCircleOffsetMaxMultiplier` | `0.9` | Random offset of the circle center (max) |
| `Map` | `BountyMapUpdateIntervalSeconds` | `10.0` | Position refresh rate |
| `Map` | `BountyMapRequestCooldownSeconds` | `10.0` | Client request throttle |
| `Map` | `BountyMapSyncIntervalSeconds` | `10.0` | Server sync interval with active bounties |
| `Map` | `BountyMapSyncIntervalNoBountiesSeconds` | `10.0` | Sync interval while idle |

### `BountyZones.json`

Safezone and territory mods **without a script API** (Dr Jones Trader, TraderPlus, Rearmed, Basic
Territories) are covered by re-entering their coordinates here.

```json
{
    "StaticSafeZones": [
        { "Name": "Green Mountain Trader", "Position": [3707.0, 402.0, 5972.0], "Radius": 250.0, "OwnerGUIDs": [] }
    ],
    "StaticTerritoryZones": [
        { "Name": "Base North", "Position": [7500.0, 200.0, 8200.0], "Radius": 150.0, "OwnerGUIDs": ["76561198000000000"] }
    ]
}
```

`OwnerGUIDs` is only evaluated for territory zones and accepts SteamID64 **or** DayZ GUID.
Safezones ignore it and apply to everyone.

> **Why a separate file:** the admin menu round-trips `BountyConfig.json` over RPC and merges it
> field by field. These lists have no admin widget, so keeping them out of that file prevents an
> admin save from wiping them.

### `BountySuccessRewardConfig.json`

| Field | Default | Description |
|---|---|---|
| `RuinedContainerAsReward` | `true` | Spawn the reward crate in ruined state (no re-use) |
| `SpawnItemsDirectlyToInventory` | `false` | Skip the crate and hand items over directly |
| `BountyRewardItems` | 2 sections | Reward sections (see below) |
| `BountyCurrencyRewards` | `[]` | Currency classnames paid out on claim |
| `CurrencyMin` / `CurrencyMax` | `1` / `1` | Currency amount range |
| `EnableHardlineReputationReward` | `false` | Grant Expansion Hardline reputation |
| `HardlineReputationRewardAmount` | `50` | Amount granted |

Each **section** picks its own container and rolls a number of loot items:

| Field | Description |
|---|---|
| `Name` | Section label (e.g. `"Weapons"`, `"Medical"`) |
| `ContainerClassName` | `NinjinsBountyCrate_250` / `_500` / `_1000` |
| `SpawnChance` | Chance the section rolls at all (%) |
| `ItemsMin` / `ItemsMax` | How many items are drawn from `LootItems` |
| `LootItems[]` | `ItemClassName`, `SpawnChance`, `Amount`, `QuantMin/Max`, `HealthMin/Max`, `Attachments[]` |

`Attachments[]` is recursive — attachments can carry their own attachments (optics on a rifle,
magazines in a vest).

### `Admins.json` / `Blacklist.json`

```json
{ "AdminGUIDs": ["76561198000000000", "AbCdEf0123456789..."] }
```

Both files accept **SteamID64 and DayZ GUID** in the same list — the server tries the hashed GUID
first, then the plain Steam ID. The connect log prints both identifiers so either can be copied
straight out of it.

### `BountyBoardPlacements.json`

Auto-spawns bounty boards at the given `Position` / `Rotation` on server start — useful when your
map has no static board object placed.

### `LoggingSettings.json`

| Field | Default | Description |
|---|---|---|
| `logLevel` | `4` | `0` Debug · `1` Info · `2` Warn · `3` Error · `4` = file logging off |
| `refreshRateInSeconds` | `60` | Log file flush interval |

Log path: `profiles/Ninjins_Bounty_System/Logging/Logs/Ninjins_Bounty_System_YYYY-MM-DD.log`

---

## Migrating from the legacy 2022 mod

Every setting from the original `BountySettings.json` has an equivalent here. Unless noted, the key
lives under `Core` in `BountyConfig.json`.

| Legacy setting | Here |
|---|---|
| `MinimumPlayerCount` | `MinOnlinePlayersRequired` |
| `RequiredPlayerLifetime` | `MinimumPlayerLifetimeSeconds` |
| `BountyExpirationTime` | `PlacedBounty.BountyDurationSeconds` |
| `PersistentBountyAfterLogOut` | `PersistentBountyAfterLogOut` |
| `DisableTimerInSafezone` | `PauseBountyInSafeZone` |
| `DisableTimerInTerritory` | `PauseBountyInTerritory` |
| `DontCountFriendlyFire` | `DontCountFriendlyFire` |
| `DontCountSuicide` | `DontCountSuicide` |
| `BountyWarningTime` | `BountyWarningTimeSeconds` |
| `PlayerPositionRefreshTimer` | `Map.BountyMapUpdateIntervalSeconds` |
| `NotificationHeader` / `NotificationIcon` | per-message `Title` / `IconPath` |
| `BountyExpiredMessage` | `Broadcasts.Expired` |
| `BountyWinMessage` | `Broadcasts.Win` (`{PLAYER}`, `{WINNER}`) |
| `BountySuicideMessage` | `Broadcasts.Suicide` (`{PLAYER}`, `{SUICIDE_PHRASE}`) |
| `BountyWarningMessage` | `Broadcasts.Warning` (`{PLAYER}`, `{TIME}`) |
| `BountyLogoutMessage` | `Broadcasts.Logout` (`{PLAYER}`) |
| `SuicidePhrases` | `SuicidePhrases` |
| `BountyRewards` | `BountySuccessRewardConfig.json` |
| `BountyBlacklist` | `Blacklist.json` |
| `BountyRequestCostPerMinute` | `BountyRequestCostPerMinute` (+ `Min`/`MaxMinutes`) |

---

## Bounty Board

<p align="center">
  <img src="Ninjins_Bounty_System/gui/layouts/ninjinsbountyboardimage.png" alt="Bounty Board" width="800">
</p>

The board is the player-facing entry point. Look at it and use the interaction action to open it.

| Button | What it does |
|---|---|
| **Place Bounty** | Pick an online target, pay tokens, start the bounty |
| **Duration (minutes)** | Only visible while per-minute pricing is active — shows the live cost |
| **Skip** | Pay `SkipBountyTokenRequired` to skip the current bounty |
| **Claim Rewards** | Hand over the reward crate / items you earned |
| **Claim Money** | Pay out the currency rewards you earned |

Board and crate classnames:

| Classname | What it is |
|---|---|
| `Ninjins_Bounty_Board_Static` | The bounty board object (indestructible) |
| `NinjinsBountyCrate_250` / `_500` / `_1000` | Reward crates, 10×25 / 10×50 / 10×100 cargo |
| `Ninjins_Bounty_Token_Silver` / `_Gold` / `_Red` | Bounty tokens |

---

## Admin Menu

Bind the key under **Settings → Controls → "Bounty Mod" → Bounty Admin Menu** (unbound by default).
Access requires your SteamID64 or GUID in `Admins.json`.

| Tab | What you can do |
|---|---|
| **Normal Settings** | Edit `Core`, `RuleBreaker`, `PlacedBounty`, `Reward` and `Map` values live and save them back to `BountyConfig.json` |
| **Notifications** | Edit notification and broadcast texts |
| **Blacklist** | Add / remove players from `Blacklist.json` in-game |

Actions available from the player list:

| Action | Effect |
|---|---|
| Add Bounty (selected player) | Places a normal `PLACED` bounty |
| Apply Test Rule Breaker Bounty | Places a `RULE_BREAKER` bounty for testing |
| Clear Bounty | Removes the active bounty |
| Clear Player Cooldown / Clear All Cooldowns | Resets bounty cooldowns |
| Reload Configs | Re-reads every JSON config from disk without a restart |

---

## Map Integration

The bounty circle is drawn on whichever map the server runs. Each integration is compiled in behind
its own define, so an unused map mod costs nothing.

| Map | Define | File |
|---|---|---|
| Vanilla DayZ map | — | `plugins/maps/bountymapmenu.c` |
| DayZ Expansion map | `EXPANSIONMODNAVIGATION` | `plugins/maps/expansion/bountyexpansionmapmenu.c` |
| LB Master map | — | `plugins/maps/lb/bountylbmap.c` |
| Vanilla++ map | `VanillaPPMap` | `plugins/maps/vanillaplusplus/bountyvanillaplusplusmap.c` |

Detected automatically at runtime:

| Feature | Source |
|---|---|
| Safezones | **Expansion**, **NinjinsPvPPvE**, `BountyZones.json` |
| Territories | **Expansion Base Building**, `BountyZones.json` |
| Friendly fire | **Expansion Parties** (`EXPANSIONMODGROUPS`), **LB Advanced Groups** (`LBmaster_Groups`) |
| Reputation | **Expansion Hardline** (`EXPANSIONMODHARDLINE`) |

---

## Installation

### Requirements

| | |
|---|---|
| **DayZ** | 1.29+ |
| **Required** | [Community Framework](https://steamcommunity.com/workshop/filedetails/?id=1559212036) — used for RPC and ModStorage persistence |
| **Optional** | DayZ Expansion, NinjinsPvPPvE, LB Advanced Groups, LB / Vanilla++ maps |
| **Optional (v3)** | Ninjins Core + Ninjins PvP/PvE Upgraded Zones — then pack `Ninjins_Bounty_V3_Bridge` as a second mod |

### Server Setup

1. Copy `Ninjins_Bounty_System` into your server's mod directory (packed as `@Ninjins_Bounty_System`)
2. Load it **after** Community Framework in the mod load order
3. Start the server once — all configs generate under `$profile:Ninjins_Bounty_System\`
4. Set `Core.EnableBountySystem` to `true` in `Config/BountyConfig.json` — it ships disabled
5. Add your SteamID64 or GUID to `Config/Admins.json`
6. Restart, bind the admin key, tune the config in-game or on disk

Running the Ninjins Upgraded v3 stack? Pack `Ninjins_Bounty_V3_Bridge` as a second mod and load it
last — see [Ninjins Upgraded v3 Bridge](#ninjins-upgraded-v3-bridge).

### Client Setup

Clients need the mod loaded to see the board, crate, token, UI and map drawing. Distribute it the
same way as any other client-side mod (Steam Workshop or your own launcher).

---

## Persistence & Save Compatibility

Bounty state is stored per player through **CF ModStorage** — bounty flag, remaining duration,
bounty type, cooldown and pending rewards.

- Class names and networked variable layouts are kept stable on purpose; renaming them breaks
  existing saves.
- `PersistentBountyAfterLogOut = false` drops only the bounty itself — the save format stays
  identical, so cooldowns and pending rewards still persist.
- Before migrating, back up `mpmissions`, your server `profiles` folder and any persistence database.

---

## Integration by Other Mods

The mod exposes its RPCs through the CF RPC manager under the `Ninjins_Bounty_System` module:

| RPC | Direction | Purpose |
|---|---|---|
| `RequestBountiedPlayers` | Client → Server | Fetch the current bounty list |
| `BoardBountyAction` | Client → Server | Place / skip / claim from the board |
| `BountyRequestPricing` | Client → Server | Fetch per-minute pricing and the minute range |
| `BountyRequestOnlinePlayers` | Client → Server | Target picker list |
| `BountyRequestClaimAmount` | Client → Server | Pending reward count |
| `BountyAdminAction` | Client → Server | Admin actions (place, clear, reload, cooldowns, blacklist) |
| `BountyAdminRequestConfig` / `BountyAdminUpdateConfig` | Client ↔ Server | Admin menu config round-trip |
| `BountyAdminRequestPlayers` / `BountyAdminRequestBlacklist` | Client → Server | Admin lists |

Native RPC IDs live in the `BountyRPC` enum starting at `33115511`
(`UPDATE_BOUNTY_STATE`, `SYNC_BOUNTIED_PLAYERS`, `SYNC_ADMIN_STATUS`, `UPDATE_BOUNTY_COUNTDOWN`).

Guard your own integration with the mod define:

```c
#ifdef Ninjins_Bounty_System
if (player.netSync_HasBounty)
{
    // react to bountied players
}
#endif
```

### Overridable Hooks

Instead of hard-wiring foreign mods into the bounty code, the parts that depend on another mod's
zone / permission / damage API sit behind overridable methods. A companion mod modded-classes
`PlayerBase` and overrides only what it needs — the base implementations keep working when the
companion mod is absent.

| Hook | Base implementation | What it decides |
|---|---|---|
| `PlayerBase.obfm_MayRunBountyAdminTools()` | `obfm_IsBountyAdmin()` (`Admins.json`) | Who may run the admin RPCs |
| `PlayerBase.obfm_BountyPlayerInPvEZone()` | `netSync_IsInPvEZone` read via `EnScript.GetClassVar` | Whether a player counts as being in a PvE zone |
| `PlayerBase.obfm_NinjinBountyIsPlayerInNinjinsSafeZone()` | `netSync_IsInSafeZone` read via `EnScript.GetClassVar` | Safezone pause / teleport-out |
| `PlayerBase.obfm_NinjinBountyIsOnSafeZoneExitTimer()` | `netSync_IsSZOnExit` read via `EnScript.GetClassVar` | Safezone exit-timer grace |
| `obfc_BountyDamageHandler.obfm_TryOpenDeniedZoneHit(victim, attacker, out openHit)` | Rule Breaker logic for a hit a zone mod already denied | Returns `true` when the bounty system decided; `openHit` is allow/deny |
| `MissionGameplay.obfm_OnBountyAdminPlayersReceived(players)` | Fills the hotkey admin menu | Where the admin player list is rendered |
| `MissionGameplay.obfm_OnBountyAdminBlacklistReceived(blacklisted)` | Fills the hotkey admin menu | Where the blacklist is rendered |

> **Why `EnScript.GetClassVar`:** the `netSync_*` members belong to NinjinsPvPPvE, not to this mod.
> Reading them reflectively keeps the bounty system compiling and running when that mod is not
> loaded, instead of requiring a `#ifdef` around every access.

---

## Ninjins Upgraded v3 Bridge

`Ninjins_Bounty_V3_Bridge` is an **optional second PBO** that connects the bounty system to the
**Ninjins Upgraded v3** stack (Core + Upgraded Zones). It contains no gameplay of its own — it only
overrides the hooks above and adds an admin panel module to the Core server sidebar.

Servers that do **not** run Ninjins Upgraded v3 should ignore this folder entirely.

### Load Order

```
Ninjins_Core + Ninjins_PvP_PvE_Upgraded_Zones + Ninjins_Bounty_System + Ninjins_Bounty_V3_Bridge
```

> **Do not load `Ninjins_Advanced_Bounty` alongside the bridge.** Both claim the same bounty role and
> the same hooks; loading them together produces conflicting overrides.

### What the Bridge Overrides

| Hook | Bridge behaviour |
|---|---|
| `obfm_MayRunBountyAdminTools()` | `Admins.json` **or** the Core `ADMIN_MENU_ACCESS` permission — Core admins no longer need a bounty-specific entry |
| `obfm_BountyPlayerInPvEZone()` | `NinjinsUpgraded_IsInPvEZone()` |
| `obfm_NinjinBountyIsPlayerInNinjinsSafeZone()` | `NinjinsUpgraded_IsInSafeZone()` |
| `obfm_NinjinBountyIsOnSafeZoneExitTimer()` | `NinjinsUpgraded_SafeExitActive()` |
| `NinjinsUpgraded_ZoneHitOpen(...)` | Calls `obfm_TryOpenDeniedZoneHit()`; falls through to `super` when the bounty system has no opinion |
| `obfm_OnBountyAdminPlayersReceived()` / `...BlacklistReceived()` | Additionally feeds the sidebar form |
| `MissionServer.NinjinsUpgraded_CoreReloadMainAndActions()` | Reloads `BountyConfig.json` together with the Core config reload |

### Admin Sidebar Module

The bridge registers a panel module in the Core admin shell (`NinjinsUpgraded_AdminModRegHook`) that
edits the live `obfc_BountyConfig` — `Core`, `RuleBreaker`, `PlacedBounty`, `Reward`, `Map`, the HUD
countdown widget, suicide phrases, and the notification / broadcast texts — plus the player and
blacklist actions, which are forwarded to the existing `Ninjins_Bounty_System` admin RPCs.

### Bridge RPCs

All under the RPC space `Ninjins_Bounty_V3_Bridge` (`NinjinsBntyV3_Const.RPC_SPACE`).

| RPC | Direction | Purpose |
|---|---|---|
| `NinjinsBntyV3_AskCfg` | Client → Server | Request the current bounty config for the sidebar |
| `NinjinsBntyV3_SaveCfg` | Client → Server | Write the edited config back to disk |
| `NinjinsBntyV3_ReloadCfg` | Client → Server | Re-read every bounty config from disk |
| `NinjinsBntyV3_RecvCfg` | Server → Client | Config payload for the form |
| `NinjinsBntyV3_RecvSave` | Server → Client | Save result (ok / failed) |

Player and blacklist actions reuse the base mod's RPCs (`BountyAdminAction`,
`BountyAdminRequestPlayers`, `BountyAdminRequestBlacklist`) under the `Ninjins_Bounty_System` space.

### Bridge Structure

```text
Ninjins_Bounty_V3_Bridge/
├── config.cpp                                   ← requiredAddons: Bounty System, Core, Upgraded Zones
├── gui/layouts/Admin/
│   ├── ninjins_bounty_v3_bridge_form.layout     ← sidebar form
│   └── ninjins_bnty_v3_group_label.layout       ← group header row
└── scripts/
    ├── Common/Debug.c                           ← defines Ninjins_Bounty_V3_Bridge
    ├── 3_Game/NinjinsBntyV3_Const.c             ← RPC space constant
    ├── 4_World/entities/manbase/playerbase.c    ← the hook overrides
    └── 5_Mission/
        ├── Admin/Ninjins_Bounty_V3_Bridge/      ← panel module, notification UI, message rows
        ├── Ninjins_Bounty_V3_Bridge/            ← admin shell registration
        ├── missiongameplay.c                    ← client RPC handlers
        └── missionserver.c                      ← server RPC handlers + config reload
```

`BOUNTY_SYSTEM_CHANGES.md` inside the folder documents which base-mod changes the bridge depends on.

---

## Obfuscation

The source is prepared for **PBO Tools** symbol obfuscation. Renaming is opt-in by prefix:

| Prefix | Applies to |
|---|---|
| `obfc_` | Classes |
| `obfm_` | Methods |
| `obfv_` | Variables and constants |

Deliberately left readable: modded classes, overrides, CF RPC handlers resolved from string
literals, JSON config keys, `netSync_` members, config.cpp-bound classnames, enums, and names shared
with foreign types.

The full exclusion list and the packing procedure for interdependent mods are kept outside this
repository.

---

## Support / Issues

If something breaks after a DayZ update, open an issue with:

1. The relevant excerpt from your server RPT
2. `Ninjins_Bounty_System_<date>.log` with `logLevel` set to `0`
3. Your full mod load order
4. Reproduction steps and your DayZ server build version

---

## Credits

<p align="center">
  <b>Original author:</b> Ninjin (Naij0)<br><br>
  <b>Maintainer (DayZ 1.29+):</b> <a href="https://steamcommunity.com/profiles/76561198043039918/">Psyern</a><br><br>
  <b>Community:</b> <a href="https://deadmans-echo.de">Deadmans Echo</a><br><br>
  Thanks to the DayZ modding community for the tooling and shared knowledge.
</p>

---

## License

The original **Ninjins Bounty System** shipped without an explicit license file. Whatever terms the
original author set for the mod continue to apply to this maintained fork.

If you are the maintainer and want to settle licensing for this fork, add a dedicated `LICENSE`
file at the repository root and reference it here.
