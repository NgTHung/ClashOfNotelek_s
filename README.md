<!-- ![Logo of the project](https://raw.githubusercontent.com/jehna/readme-best-practices/master/sample-logo.png) -->

# Clash of Notelek's
> A thrilling 2D adventure game built with SFML

## Overview

Clash of Notelek's is a simple yet engaging top-down arcade game developed in C++ for our Object-Oriented Programming final project. Players take control of Notelek's, a small skeleton, and must survive by defeating waves of slime enemies. This project demonstrates core OOP principles, software design patterns, and an AI-assisted development process.


## Features

- Engaging 2D gameplay with smooth animations
- Immersive sound effects and background music

## Technology Stack

- C++ for core game logic
- SFML for graphics rendering and audio
- CMake for cross-platform build management

## Installation and Setup

### Requirements

- C++ compiler (supporting C++20 or newer)
- CMake 3.28 or newer
- Git

### Getting the Source Code

To download the source code, you need to clone the project.

```shell
git clone https://github.com/NgTHung/OOP-Game
cd OOP-Game/
```

### Building the Project

After making some changes(or not), running these command will help you to build the code to test the game.

```shell
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Game

```shell
bin/main.exe
```

## Project Structure

- `assets/`: Game resources (sprites, sounds, fonts)
- `include/`: Header files organized by component
- `src/`: Source files organized by component
- `uml/`: UML diagrams documenting the architecture

## Game Controls

- WASD: Movement
- Left Click: Attack
- ESC: Pause game

## Architecture

The game follows a component-based architecture with clear separation of concerns:
- `Engine`: Core game loop and system management
- `State`: Game state management (menu, gameplay, etc.)
- `Graphic`: Rendering and animation systems
- `Event`: Input handling and event dispatching
- `Command`: Command pattern implementation for game actions
- `Resources`: Asset management and resource caching
- `Utility`: Helper functions and common utilities

## File Structure
```bash
OOP-Game
├── CMakeLists.txt
├── LICENSE
├── README.md
├── assets
│   ├── fonts
│   │   └── arial.ttf
│   ├── sound
│   │   ├── background-music.mp3
│   │   ├── button-press.mp3
│   │   ├── lose.mp3
│   │   ├── loseSound.mp3
│   │   ├── ouch.mp3
│   │   ├── running.mp3
│   │   ├── slimedead.mp3
│   │   ├── slime-hit.mp3
│   │   ├── weapon-hit.mp3
│   │   ├── win.mp3
│   │   └── winMusic.mp3
│   └── sprite
│       ├── board.png
│       ├── Box.png
│       ├── DeadScreen.png
│       ├── DeadSmokeVFX.png
│       ├── Exit_button.png
│       ├── grass.png
│       ├── healthbarface.png
│       ├── hi.json
│       ├── hi.png
│       ├── HitSmokeVFX.png
│       ├── Leaf1.png
│       ├── Leaf2.png
│       ├── Leaf3.png
│       ├── Leaf4.png
│       ├── Leaf5.png
│       ├── play_button.png
│       ├── PlayAgain_button.png
│       ├── Slime.png
│       ├── startscreen.png
│       ├── sword.png
│       ├── test_map.png
│       ├── TinyGrass.png
│       ├── Tree.png
│       ├── TroppyCup.png
│       └── WinBackGround.png
├── include
│   ├── Command
│   │   ├── Command.hpp
│   │   ├── PlayerCommand.hpp
│   │   └── SpriteCommand.hpp
│   ├── Engine
│   │   └── Engine.hpp
│   ├── Event
│   │   ├── CollisionEvent.hpp
│   │   ├── Event.hpp
│   │   ├── EventDispatcher.hpp
│   │   ├── EventQueue.hpp
│   │   ├── PlayerEvent.hpp
│   │   └── SpriteEvent.hpp
│   ├── External
│   │   └── json.hpp
│   ├── Graphic
│   │   ├── Base.hpp
│   │   ├── Board.hpp
│   │   ├── Button.hpp
│   │   ├── Collision.hpp
│   │   ├── Enemy.hpp
│   │   ├── HealthBar.hpp
│   │   ├── LeafFalling.hpp
│   │   ├── MapEntity.hpp
│   │   ├── Player.hpp
│   │   ├── PlayerHealthbar.hpp
│   │   ├── ScreenShake.hpp
│   │   ├── SlimeBar.hpp
│   │   ├── SmokeVFX.hpp
│   │   ├── Sprite.hpp
│   │   ├── TroppyCup.hpp
│   │   ├── Wall.hpp
│   │   ├── Water.hpp
│   │   └── Weapon.hpp
│   ├── Resources
│   │   ├── AudioHolder.hpp
│   │   ├── FontHolder.hpp
│   │   ├── ResourcesHolder.hpp
│   │   ├── ResourcesManager.hpp
│   │   └── TextureHolder.hpp
│   ├── State
│   │   ├── BaseState.hpp
│   │   ├── DeadScreen.hpp
│   │   ├── HomeScreen.hpp
│   │   ├── KnockbackHandler.hpp
│   │   ├── PlayerState.hpp
│   │   ├── Screen.hpp
│   │   ├── SpriteState.hpp
│   │   ├── StartScreen.hpp
│   │   └── WinScreen.hpp
│   └── Utility
│       ├── Environment.hpp
│       ├── IDGenerator.hpp
│       ├── Logger.hpp
│       └── ResourcesUtility.hpp
├── src
│   ├── main.cpp
│   ├── Command
│   │   ├── PlayerCommand.cpp
│   │   └── SpriteCommand.cpp
│   ├── Engine
│   │   └── Engine.cpp
│   ├── Event
│   │   ├── CollisionEvent.cpp
│   │   ├── EventDispatcher.cpp
│   │   ├── EventQueue.cpp
│   │   ├── PlayerEvent.cpp
│   │   └── SpriteEvent.cpp
│   ├── Graphic
│   │   ├── Base.cpp
│   │   ├── Board.cpp
│   │   ├── Button.cpp
│   │   ├── Collision.cpp
│   │   ├── Enemy.cpp
│   │   ├── HealthBar.cpp
│   │   ├── LeafFalling.cpp
│   │   ├── MapEntity.cpp
│   │   ├── Player.cpp
│   │   ├── PlayerHeathBar.cpp
│   │   ├── ScreenShake.cpp
│   │   ├── SlimeBar.cpp
│   │   ├── SmokeVFX.cpp
│   │   ├── Sprite.cpp
│   │   ├── TroppyCup.cpp
│   │   ├── Wall.cpp
│   │   ├── Water.cpp
│   │   └── Weapon.cpp
│   ├── Resources
│   │   ├── AudioHolder.cpp
│   │   ├── FontHolder.cpp
│   │   ├── ResourcesHolder.cpp
│   │   ├── ResourcesManager.cpp
│   │   └── TextureHolder.cpp
│   ├── State
│   │   ├── DeadScreen.cpp
│   │   ├── HomeScreen.cpp
│   │   ├── KnockbackHandler.cpp
│   │   ├── PlayerState.cpp
│   │   ├── Screen.cpp
│   │   ├── SpriteState.cpp
│   │   ├── StartScreen.cpp
│   │   └── WinsScreen.cpp
│   └── Utility
│       ├── IDGenerator.cpp
│       └── Logger.cpp
└── uml
    ├── Command.puml
    ├── Engine.puml
    ├── Event
    │   ├── BaseEvent.puml
    │   ├── CollisionEvent.puml
    │   ├── EventDispatcher.puml
    │   ├── EventQueue.puml
    │   ├── PlayerEvent.puml
    │   └── SpriteEvent.puml
    ├── Graphic
    │   ├── Base.puml
    │   ├── Board.puml
    │   ├── Button.puml
    │   ├── Collision.puml
    │   ├── Enemy.puml
    │   ├── HealthBar.puml
    │   ├── KnockbackHandler.puml
    │   ├── Leaf.puml
    │   ├── Player.puml
    │   ├── ScreenShake.puml
    │   ├── SlimeBar.puml
    │   ├── SmokeVFX.puml
    │   ├── Sprite.puml
    │   ├── TroppyCup.puml
    │   ├── Wall.puml
    │   ├── Water.puml
    │   └── Weapon.puml
    ├── Resources
    │   ├── AudioHolder.puml
    │   ├── FontHolder.puml
    │   ├── ResourcesHolder.puml
    │   ├── ResourcesManager.puml
    │   └── TextureHolder.puml
    ├── Screen
    │   ├── DeadScreen.puml
    │   ├── HomeScreen.puml
    │   ├── Screen.puml
    │   ├── StartScreen.puml
    │   └── WinScreen.puml
    ├── State
    │   ├── BaseState.puml
    │   ├── PlayerState.puml
    │   └── SpriteState.puml
    └── Utilities
        └── IDGenerator.puml

```

## Future Plans

- Additional levels and environments
- More enemy types and behaviors
- Character progression system
- Settings menu for customization
- Multiplayer support

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- SFML team for their excellent graphics library
- All contributors and testers
- HCMUS for supporting this project
