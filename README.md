# Ninjins Bounty System (Maintained Fork)

**DayZ Mod (Server-Authoritative Gameplay)**

This repository contains the **Ninjins Bounty System**, a server-focused bounty / contract gameplay system for DayZ.

> **Maintenance notice (DayZ 1.29+)**
>
> With the DayZ **1.29** update, I have taken over maintenance and updates of this mod. **Ninjin is stepping into “retirement”** and will no longer actively maintain the project.
>
> This fork’s goal is compatibility, stability, and minimal disruption for existing communities.

---

## Overview

The **Ninjins Bounty System** adds a bounty board driven gameplay loop to your server:

- Players can interact with a **Bounty Board** object.
- **Players can place a bounty (set a “price on someone’s head”) on other players.**
- Bounties/contracts are tracked by the system.
- Completing a bounty results in rewards delivered through the mod’s reward flow (e.g., via a **Bounty Crate** / reward container).
- The mod is designed to be **server-authoritative** (the server validates kills/completions and controls reward payout).

The mod ships with custom assets (board/crate/token) and a full script setup under the standard DayZ script layers.

---

## Features

### Player-Driven Bounty Creation
- Players can **create bounties on other players** using the **Bounty Board**.
- Bounty creation is **validated on the server** (prevents client-side spoofing).
- Typical requirements can include a deposit / payment (cash/items/tokens) depending on your server setup.

### Bounty Board Gameplay
- **Placeable / spawnable bounty board** model.
- Players use the board as the primary interaction point for creating and accepting/monitoring bounties.

### Bounty Completion & Validation
- Bounty completion is tied to **server-verified conditions** (e.g., target player death and the killer identity).
- The server decides if a kill counts and when a bounty is marked as completed.

### Bounty Rewards
- Rewards are delivered through a dedicated container (commonly used as a **bounty crate** / reward crate workflow).
- Supports custom textures/materials for a unique presentation.

### Token / Item Content
- Includes a custom token model/item (useful for:
  - bounty deposits,
  - proof-of-completion,
  - currency-like rewards,
  - trade-in progression,
  - integration with other economy systems).

### Server-First Design
- The mod is built with strict **server/client separation** in mind.
- Sensitive logic (validation, reward payout, persistence) is handled on the **server**.

---

## How It Works (High Level)

### UI / Player Flow (Typical)
1. Player opens/interacts with the **Bounty Board**.
2. Player selects a target player.
3. Player sets the bounty amount (and potentially pays a deposit).
4. The server validates and stores the bounty.
5. When the target is killed, the server validates the kill and triggers completion.
6. Rewards are paid out using the mod’s reward flow (e.g., via crate/token/items).

> The exact UI layout and button names may vary by mod version and server customization.

### Admin / Server Control
Depending on your server rules, admins may be able to:
- enable/disable player-created bounties,
- restrict bounty creation (minimum amount, cooldowns, safezone restrictions),
- remove/expire invalid bounties,
- adjust reward multipliers or tax.

---

## Configuration

This mod ships with a base configuration (`config.cpp`) and data assets.

Common configuration areas (depending on the script implementation in this version):

- Bounty creation rules
  - minimum / maximum bounty value
  - cooldowns
  - taxes/fees
  - deposits (items, money, token)
- Reward rules
  - payout type (items/token/crate)
  - reward scaling
  - blacklist/whitelist of allowed reward items
- Persistence
  - save interval
  - bounty expiration time

> If you have a server-side JSON or profile configuration for this mod, keep it under your server profile (recommended) and document the path in this section.

---

## Mod Content / Assets

This mod includes (among other content):

- **Bounty Board** model and materials
- **Bounty Crate** model and textures
- **Bounty Token** model and config
- GUI resources (icons and layouts)

Directory highlights:

- `data/` – models, textures, rvmats
- `gui/` – icons and UI layouts
- `scripts/3_game`, `scripts/4_world`, `scripts/5_mission` – code split by DayZ script layer
- `config.cpp` – mod config

---

## Installation

### Requirements
- A DayZ Server with mod support.
- Clients must load the mod to see assets and UI.

> If your server uses additional frameworks (e.g., Community Framework / Expansion), keep them properly ordered and ensure no signature mismatch.

### Server Setup
1. Copy the mod folder(s) to your server’s `@Mods` directory (or your chosen mod directory).
2. Add the mod to your server start parameters.
3. Ensure keys are installed (if you distribute signed builds).

### Client Setup
- Clients subscribe/download via your chosen distribution method (e.g., Steam Workshop) and load it in the launcher.

---

## Persistence / Save Compatibility

This fork aims to maintain **backward compatibility** with servers that already ran Ninjins Bounty System.

- Avoid renaming class names and config classnames.
- Avoid changing networked variable layouts unless absolutely necessary.

If you are migrating from an older version:
- Always backup:
  - your `mpmissions` folder,
  - your `profile` / server profile folder,
  - and any database files used by your persistence setup.

---

## Administration / Usage

Operational recommendations:

- Place the **Bounty Board** in a controlled area (trader/hub) so players can reliably access it.
- Decide on your server policy:
  - Are bounties allowed in safezones?
  - Are bounties refundable if the target is offline for a long time?
  - Do you want a minimum bounty amount to reduce spam?
- Tune reward value to fit your server economy.

---

## Compatibility

Designed for:
- **DayZ 1.29+** (maintenance target)

Compatibility depends on:
- other mods editing similar UI paths,
- economy mods that override item definitions,
- server frameworks.

If you encounter conflicts:
- collect logs,
- identify overlap in classnames and UI resources,
- and open an issue with details.

---

## Development Notes

Project layout:

- DayZ script layers:
  - `scripts/3_game`
  - `scripts/4_world`
  - `scripts/5_mission`
- Mod config:
  - `config.cpp`
- Asset pipeline:
  - `data/` and subfolders for models/textures/materials

### Versioning
- This fork will track DayZ updates (starting with 1.29) and apply **minimal, targeted fixes**.

---

## Credits

- **Original author:** Ninjin
- **Maintenance (DayZ 1.29+):** This fork’s maintainer (you)

Thanks to the DayZ modding community for tooling and shared knowledge.

---

## License

If the original mod includes licensing terms or usage restrictions, they apply here as well.

If you are the maintainer and want to clarify licensing for this fork, add a dedicated `LICENSE` file.

---

## Support / Issues

If something breaks after a DayZ update:

1. Provide your server RPT log excerpt.
2. Include mod load order.
3. Explain reproduction steps.
4. Mention your DayZ server build version.

Open an issue with the above information.
