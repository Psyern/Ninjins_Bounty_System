# Ninjins_Bounty_System - Anpassungen fuer die v3 Bridge

Nur die Aenderungen in **Ninjins_Bounty_System**, die die Bridge braucht (Hooks + Compile-Fixes).  
Alles andere im dirty Working Tree (Admin-UI Rewrite, Maps, Config-Masse, Line-Endings) gehoert **nicht** dazu.

Load-Order v3:

`Ninjins_Core` + `Ninjins_PvP_PvE_Upgraded_Zones` + `Ninjins_Bounty_System` + `Ninjins_Bounty_V3_Bridge`

Nicht zusammen mit `Ninjins_Advanced_Bounty` laden.

---

## 1. PlayerBase - ueberschreibbare Hooks

Datei: `scripts/4_World/entities/manbase/PlayerBase.c`

| Methode | Base-Verhalten | Bridge override |
|---|---|---|
| `obfm_MayRunBountyAdminTools()` | `obfm_IsBountyAdmin()` (Bounty `Admins.json`) | + Core Admin-Menu Permission |
| `obfm_BountyPlayerInPvEZone()` | `GetClassVar(..., "netSync_IsInPvEZone", ...)` (altes PvPPvE) | `NinjinsUpgraded_IsInPvEZone()` |
| `obfm_NinjinBountyIsPlayerInNinjinsSafeZone()` | `GetClassVar(..., "netSync_IsInSafeZone", ...)` | `NinjinsUpgraded_IsInSafeZone()` |
| `obfm_NinjinBountyIsOnSafeZoneExitTimer()` | `GetClassVar(..., "netSync_IsSZOnExit", ...)` | `NinjinsUpgraded_SafeExitActive()` |

Pause / Teleport / Placement nutzen diese Helpers statt hardcodierter alter NetSync-Felder.

---

## 2. Damage - `obfm_TryOpenDeniedZoneHit`

Datei: `scripts/4_World/DamageSystem/BountyDamageSystem.c`

- Neue Methode `obfm_TryOpenDeniedZoneHit(victim, attacker, out openHitOut)`.
- Enthaelt die Bounty-Logik, wenn Zone den Hit schon denied hat (oder old `DamageUtils` entscheidet).
- Return `true` = Bounty hat entschieden; `openHitOut` = allow/deny.
- Old-Pfad `#ifdef NinjinsPvPPvE`: `DamageUtils.ShouldAllowDamage` ruft nur noch diesen Wrapper.
- PvE-Checks gehen ueber `player.obfm_BountyPlayerInPvEZone()`.

Bridge (`Ninjins_Bounty_V3_Bridge` PlayerBase) ruft dieselbe Methode aus `NinjinsUpgraded_ZoneHitOpen` auf.

---

## 3. Admin-RPCs - Permission ueber Hook

Datei: `scripts/4_World/BountyModule.c`

Statt nur `obfm_IsBountyAdmin()` pruefen Admin-RPCs jetzt:

`player.obfm_MayRunBountyAdminTools()`

Betroffen u.a.:

- Admin Action
- Request Players
- Request Blacklist
- weitere Admin-RPC Gates im Module

Damit kann die Bridge Core-Admins durchlassen, ohne Bounty-`Admins.json` zu zwingen.

---

## 4. MissionGameplay - UI Hooks fuer Sidebar

Datei: `scripts/5_Mission/missionGameplay.c`

RPC-Empfang leitet weiter in ueberschreibbare Methoden:

- `BountyAdminReceivePlayers` -> `obfm_OnBountyAdminPlayersReceived(players)`
- `BountyAdminReceiveBlacklist` -> `obfm_OnBountyAdminBlacklistReceived(blacklistedPlayers)`

Base: fuellt das alte Hotkey-`obfc_BountyAdminMenu`.  
Bridge: `override` und fuellt zusaetzlich die Server-Sidebar Form.

---

## 5. Compile-Fixes (nicht Bridge-Logik, aber noetig)

### Notifications - 16-Arg Limit

Datei: `scripts/3_Game/Notifications/BountyNotifications.c`  
(+ Call-Sites in PlayerBase, BountyModule, BountyManager, MissionServer, DamageSystem, RewardHelper)

- Neu: `obfc_BountyNotifArgs` Bag-Klasse.
- `obfm_SendNotificationInternal(type, identity, args)` statt 17 Einzelparameter.
- Call-Sites bauen `notifArgs` und setzen Felder.

Ohne das kompiliert das Game-Modul nicht (EnScript max 16 Args).

### Board Menu - SetHandler

Datei: `scripts/5_Mission/GUI/NinjinsBountyBoardMenu.c`

- `obfv_m_BountyMinutes.SetHandler(this)` entfernt.
- `UIScriptedMenu` ist kein `ScriptedWidgetEventHandler`; `OnChange` reicht im offenen Menu.

---

## Dateien (Bridge-relevant)

```
scripts/4_World/entities/manbase/PlayerBase.c
scripts/4_World/DamageSystem/BountyDamageSystem.c
scripts/4_World/BountyModule.c
scripts/5_Mission/missionGameplay.c
scripts/3_Game/Notifications/BountyNotifications.c
scripts/5_Mission/GUI/NinjinsBountyBoardMenu.c
```

Call-Site Updates fuer Notif-Args (Folge von Punkt 5):

```
scripts/4_World/BountyManager/BountyManager.c
scripts/4_World/BountyManager/BountyRewardContainerHelper.c
scripts/5_Mission/MissionServer.c
```

(+ die gleichen Notif-Umschreibungen in PlayerBase / BountyModule / DamageSystem)

---

## Was die Bridge selbst macht (nicht in Bounty_System)

Addon: `src/Ninjins_Bounty_V3_Bridge/`

- Override der Hooks oben (PvE / Safezone / Admin).
- `NinjinsUpgraded_ZoneHitOpen` -> `obfm_TryOpenDeniedZoneHit`.
- Server-Sidebar Config + Admin Actions (RPCs an `"Ninjins_Bounty_System"`).
- Ask / Save / Reload Config RPCs fuer die Sidebar.
