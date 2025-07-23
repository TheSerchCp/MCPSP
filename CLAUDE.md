# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Minecraft implementation for PlayStation Portable (PSP) called "Minecraft: PlayStation Portable Edition". It's a C/C++ project built using the PSP SDK that recreates Minecraft gameplay on the PSP platform.

## Architecture

The project follows a modular architecture with these main components:

- **Aurora Engine**: Custom 3D graphics engine (`source/Aurora/`) handling rendering/graphics (`Graphics/`), mathematics (`Math/`), system management (`System/`), and utilities (`Utils/`)
- **LameCraft**: Core game logic (`LameCraft/`) including world generation, blocks, items, mobs, and game states
- **Third-party Libraries**: External libraries (`3libs/`) including noise generation (noisepp), PSP math functions (libpspmath), and PSP Game Engine (pge)

## Build System

The project uses a hierarchical Makefile system:

```bash
# Build everything (default)
make

# Build only the game
make build_game

# Build third-party libraries
make build_libs

# Clean build artifacts
make clean
make clean_all
```

The main makefile delegates:
- Library building to `3libs/*/Makefile`
- Game building to `MakefileGame`

## Key Components

### Core Game Classes
- `CraftWorld2`: Main world management and rendering
- `StatePlay`/`StatePlayCreative`: Gameplay states for survival/creative modes
- `StateMenu`: Main menu system
- `SimpleMeshChunk2`: Chunk-based world rendering
- `WorldGenerator`: Terrain and structure generation using noise

### Mob System
All mobs are in `LameCraft/mobs/` following a common pattern:
- Base classes: `LameMob`, `BaseEntity`
- Individual mobs: `Chicken2`, `Cow2`, `Creeper2`, `Pig2`, `Sheep2`, `Skeleton2`, `Spider2`, `Villager2`, `Wolf2`, `Zombie2`, etc.

### Block and Item System
- `BaseBlock`/`Blocks`: Block definitions and behavior
- `BaseItem`/`Items`: Item definitions and crafting
- `BlockEntity`: Special block entities (chests, furnaces, etc.)

### Audio System
- `SoundManager`: BGM and sound effect management
- Custom audio utilities in `sound_utils/`
- Supports PSP audio formats (.bgm, .wav)

## Development Notes

- Built for PSP firmware 3.71 with large memory mode enabled
- Uses PSP-specific libraries (pspgum, pspgu, pspaudio, etc.)
- Graphics rendering uses PSP's GU (Graphics Unit)
- Math operations optimized using PSP's VFPU (Vector Floating Point Unit)
- Asset loading supports textures, sounds, and language files

## Game Assets

Assets are organized in `GAME/Assets/`:
- `Textures/Default/`: Game textures (terrain, items, GUI, etc.)
- `Sounds/`: Audio files organized by category
- `Lang/`: Localization files for multiple languages
- `Fonts/`: PSP font files

## Save System

World saves are stored in `GAME/Save/world*/` with:
- `world.lms`: World data
- `playerdata.lms`: Player information
- `info.lms`: World metadata