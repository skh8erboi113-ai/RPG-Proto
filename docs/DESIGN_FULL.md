# DESIGN_FULL

## Overview
**Project**: Modern Gothic RPG — Ashbourne vertical slice and full design blueprint.  
**Scope**: Open‑world action RPG blending gothic fantasy and near‑future tech. Core pillars: **Angelic vs Demonic alignment**, **player choice and consequence**, **skill trees and rituals**, **vertical slice: Ashbourne city**. This document provides high‑level systems, city design, mission templates, progression rules, and implementation notes for engineers, designers, and artists.

---

## Core Pillars and Player Experience
- **Player Agency**: meaningful choices with mechanical and narrative consequences; alignment meter tracks angelic/demonic actions and unlocks unique skills, rituals, and NPC reactions.  
- **Combat and Rituals**: hybrid combat (melee, ranged, tech) with ritual mechanics (exorcism, binding, resurrection) that require preparation, resources, and minigame skill.  
- **World Systems**: wanted system, dynamic loot, crafting and dual‑station rituals, persistent stashes and world events (e.g., GhostStorm, CorporateConvoy).  
- **Vertical Slice Goals**: deliver a 10–15 minute loop in Ashbourne demonstrating investigation, combat, exorcism minigame, crafting (Health Tonic), mount use, and a boss encounter.

---

## Major Systems (Design + Implementation Notes)

### Skills and Progression
- **Skill Trees**: Angelic, Demonic, Tech, Stealth, Melee, Ranged, Crafting. Skills scale 1..99 using parameterized formulas (see `docs/skills/FullSkillTrees.json`).  
- **XP and Levels**: Skill XP formula: \(\text{SkillXP}_n = \text{BaseSkillXP} \cdot r^{(n-1)}\) with BaseSkillXP=100, \(r=1.08\). Player level XP uses separate progression curve (configurable).  
- **Tier Milestones**: unlocks at levels 10, 25, 50, 75, 99. UI must show next‑tier preview and delta.  
- **Rituals and Ultimate Unlocks**: high‑tier abilities require rare materials and ritual circles; server validates ritual prerequisites.

### Combat and Abilities
- **Action Loop**: light/heavy attacks, dodge, block/parry, skill activation, consumables.  
- **Ability Parameters**: compute on demand using current stats and buffs; do not store computed per‑level values. Clamp cooldowns and success chances server‑side.  
- **Enemy Design**: mix of minor ghosts, elite spirits, human guards, and mechanical wardens. Use loot tables per city for drops.

### Crafting and Economy
- **Stations**: Forge, AlchemyTable, RitualCircle, TechBench, Garage. Dual‑station recipes reserve both stations for craft duration.  
- **Failure and Success**: high‑rarity recipes have failure chance; success scales with crafting skill. Partial material consumption on failure.  
- **Materials**: city‑themed sources (e.g., Spirit Ash in Ashbourne, Tech Core in Ironvale). Recipes and loot tables are machine‑readable JSON.

### Loot and World Events
- **Rarity Tiers**: Common → Mythic with base drop chances; world events and stashes can override mythic chance.  
- **Roll Order**: roll rarity first, then item within rarity pool. Adjust by enemy level and area bracket.  
- **Stashes**: world stashes respawn on a schedule; access methods gate rewards (Lockpick, Hack, Ritual, DivingGear, Parkour, KeyItem).

### Wanted System and Law
- **City Crime Points**: crimes add points per city; thresholds map to WantedLevel (Clean → Maximum). Points decay over time.  
- **Marshal Response**: wanted level influences spawn frequency and marshal strength. Server authoritative for spawn and bounty resolution.

### Save and Persistence
- **Serialization**: store skill ids and levels, inventory item ids and counts, quest states, and player appearance. Do not store computed skill effects.  
- **Atomic Saves**: use temp file + atomic rename to avoid corruption. Server must validate critical state changes.

---

## Ashbourne Vertical Slice — Mission Flow and Design

### Vertical Slice Scope
- **Playable Loop**: 10–15 minutes demonstrating investigation, combat, exorcism minigame, reagent gathering, boss encounter, and a meaningful choice at the end (bind or free spirit).  
- **Key Scenes**: outskirts approach, manor investigation, cathedral boss arena, ritual circle area, stash puzzle.

### Mission Flow (Sequence)
1. **Intro**: short cutscene; player arrives at Ashbourne outskirts; basic movement tutorial.  
2. **Investigation**: enter manor, collect 3 spectral clues (evidence items) to reveal ritual location.  
3. **Combat**: minor ghost encounter teaching melee combos and pistol use.  
4. **Exorcism Minigame**: place ritual circle, perform timed inputs or pattern matching to banish spirit; success weakens boss.  
5. **Gathering**: hunt 2 spectral beasts for reagents (HERB_A, MAT_SPIRIT_ASH).  
6. **Boss Encounter**: Cathedral Warden — use exorcism to remove shield phases, then finish with combat.  
7. **Wrap**: reward and branching choice (bind spirit for power or free it for alignment shift).

### Success Criteria
- Playable loop with clear feedback and pacing.  
- Stable 60 FPS on target hardware for prototype.  
- Server‑authoritative checks for exorcism outcomes and boss state.

---

## City Design Notes (Ashbourne example)
- **Theme**: occult, cathedral architecture, narrow alleys, ritual altars.  
- **Key NPCs**: Marshal lieutenant (wanted system), Ritualist (quest giver), Cathedral Warden (boss).  
- **Points of Interest**: manor investigation site, crypt stash, ritual circle, rooftop stash puzzle.  
- **Audio and Visual**: modern gothic palette — desaturated stone, stained glass, neon sigils; ambient ghost wails and low choir.

---

## UI and UX Guidelines
- **Skill UI**: show current level, next‑level delta, and milestone unlocks at 10/25/50/75/99.  
- **Ritual UI**: ritual preparation panel showing required materials, time, and success chance; minigame overlay during execution.  
- **Wanted UI**: city‑specific wanted meter with thresholds and visible consequences.  
- **Inventory/Crafting**: quick craft preview, success chance, and partial failure outcomes.

---

## Implementation and Engineering Notes
- **Compute on Demand**: derive skill effects at runtime using player stats and active buffs. Do not persist computed values.  
- **Server Validation**: all world‑affecting actions (possession, resurrection, mass AoE, loot rolls) must be server‑authoritative.  
- **Telemetry**: instrument skill usage, ritual success/failure, loot acquisition, and player choices for balance tuning.  
- **Testing**: unit tests for Stats, Inventory, CraftingManager; integration tests for save/load and wanted system.  
- **Build and CI**: CMake top‑level, game module CMake, GitHub Actions workflow to build and run unit tests.

---

## Roadmap and Next Steps
1. **Scaffold repo**: add design docs, JSON skill/loot/recipe files, vertical slice manifest and scripts (done).  
2. **Import placeholders**: add placeholder assets and run import scripts locally.  
3. **Implement core systems**: character controller, combat, skills, crafting, wanted system.  
4. **Vertical slice iteration**: implement mission flow, exorcism minigame, boss encounter, polish.  
5. **Playtest and telemetry**: collect data, tune skill scaling and loot rates.  
6. **Expand world**: add remaining cities, world events, and high‑tier rituals.

---

## Appendix: Quick references
- **Skill XP formula**: SkillXP\(_n\) = BaseSkillXP \(\cdot\) \(r^{(n-1)}\) (BaseSkillXP=100, r=1.08).  
- **Tier milestones**: 10, 25, 50, 75, 99.  
- **Key files**: `docs/skills/FullSkillTrees.json`, `docs/loot/FullLootTables.json`, `docs/crafting/FullRecipes.json`, `.github/workflows/ci.yml`, `vertical_slice/manifest.json`.

