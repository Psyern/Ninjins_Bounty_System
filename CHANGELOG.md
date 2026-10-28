# Changelog — Ninjins Bounty System seit 11.08.2026

Changelog für Ninjins Bounty System und die neue Ninjins Bounty V3 Bridge.

## Hotfix 1.1.1 (28.10.2026)

**Server-Absturz behoben:** Auf manchen Servern brach der Start mit `Can't compile "Mission" script module` ab (`Can't find variable 'UABountyAdminMenu'`). Das passierte, wenn die Tastenbelegungs-Datei des Mods nicht registriert wurde. Die Taste für das Admin-Menü wird jetzt zur Laufzeit über ihren Namen gesucht.

Getestet auf DayZ 1.30 mit CF + COT, nur CF, mit Bundle + Bridge und mit Bundle ohne Bridge.

## Neu: Ninjins Bounty V3 Bridge

Neues, optionales Addon, das das Bounty System mit Ninjins Upgraded V3 verbindet (Core und PvP/PvE Upgraded Zones).

Kopfgelder richten sich nach den Safezones und PvE-Zonen von Ninjins V3. Die Rule-Breaker-Regeln greifen auch in Zonen, die einen Treffer sonst blocken würden.

Das Bounty System hat jetzt eine eigene Seite im Admin-Menü von Ninjins Core. Dort lassen sich alle Einstellungen, Benachrichtigungen, Spieler und die Blacklist im Spiel bearbeiten.

Admins aus der Core-Rechteverwaltung haben Zugriff, ohne zusätzlichen Eintrag in der Admins.json.

Ladereihenfolge: Ninjins_Core, Ninjins_PvP_PvE_Upgraded_Zones, Ninjins_Bounty_System, Ninjins_Bounty_V3_Bridge.
Nicht zusammen mit Ninjins_Advanced_Bounty laden.

## Neue Features

Alle neuen Features sind standardmäßig aus und lassen sich in der BountyConfig.json oder im Admin-Menü einschalten.

**Rache-Kopfgeld:** Wer mehrmals vom selben Spieler getötet wurde, kann am Board ein Kopfgeld auf diesen Spieler setzen. Wie viele Tode es braucht, stellt der Admin ein.

**Geldtöpfe:** Kopfgelder können eine Belohnung in Geld haben. Andere Spieler können Geld zu einem laufenden Kopfgeld dazulegen. Der Killer holt sich den Topf am Board ab.
Läuft das Kopfgeld ab oder wird es gelöscht, gibt es das Geld zurück. Gruppenmitglieder des Ziels können den Topf nicht kassieren.
Bezahlt wird über den Expansion Market, wenn er geladen ist, sonst mit Bounty-Tokens. Eine einstellbare Gebühr wird zusätzlich abgezogen.

**Kopfgeld auf dich selbst:** Spieler können am Board ein Kopfgeld auf sich selbst setzen.

**Loot-Kopfgelder:** Admins können Kopfgelder mit Item-Belohnungen aus vorgefertigten Loot-Paketen setzen (BountyLootPresets.json).

**Top-Killer der Woche:** Automatische Kopfgelder können gezielt den Spieler mit den meisten Kills der Woche treffen.

**Board:** neues Feld für die Belohnung, Knöpfe „Add Money to Bounty“ und „Bounty on Myself“, Markierungen für Kopfgelder mit Geldtopf oder Loot.

**Vier neue Board-Modelle:** Pro Platzierung in BountyBoardPlacements.json lässt sich über `BoardClassName` ein anderes Modell wählen: `Ninjins_Bounty_Board_Blackboard1` (Steckbrief-Brett an einem Pfosten), `Ninjins_Bounty_Board_Blackboard2` (Steckbrief-Wand im Holzrahmen), `Ninjins_Bounty_Board_Cactus` (Steckbriefe an einem Saguaro-Kaktus) und `Ninjins_Bounty_Board_Outlaw` (Steckbrief-Brett zwischen zwei Baumstamm-Pfosten).

## Geänderte Standardwerte

Neue Installationen starten mit ausgeschaltetem Bounty System. So lässt sich der Server erst einrichten, bevor Kopfgelder laufen.

Der Kopfgeld-Timer pausiert jetzt standardmäßig in Safezones. Das Ziel wird nicht mehr aus der Safezone teleportiert. Vorher konnte ein Ziel das Kopfgeld in der Safezone aussitzen, wenn der Teleport nicht griff.

Bestehende Configs behalten ihre gespeicherten Werte. Alte Configs bekommen die neuen Abschnitte beim Laden automatisch dazu.

## Fixes

Ohne NinjinsPvPPvE bekam der Killer oft keine Belohnung, und das Kopfgeld lief weiter. Der Kill wurde als Selbstmord gewertet, wenn die Engine die Waffe statt des Spielers als Killer gemeldet hat.

Kopfgelder mit einem Preis über 1 Token wurden nach dem Platzieren zurückgerollt, obwohl die Tokens schon abgezogen waren.

Mit sehr großen Beträgen ließ sich ein riesiger Anteil am Geldtopf buchen, ohne zu bezahlen. Beträge und Töpfe haben jetzt eine Obergrenze.

Im Token-Modus konnte ein Kopfgeld mit Belohnung kostenlos durchgehen, wenn die Tokens fürs Platzieren fehlten.

Über das normale Platzieren ließ sich ein Kopfgeld auf sich selbst setzen und so die Grenzen für Selbst-Kopfgelder umgehen.

Eingabefelder und Beschriftungen auf dem Board sind wieder lesbar. Vorher stand weiße Schrift auf hellem Pergament.

Andere Mods können jetzt sicher erkennen, ob das Bounty System geladen ist.

Der Mod läuft auch ohne NinjinsPvPPvE und läuft auf DayZ 1.30.
