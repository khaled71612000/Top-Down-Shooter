# Top Down Shooter

> An engaging top-down shooter in Unreal Engine C++ with enemy AI, projectile systems, health management, and wave-based combat.

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-0E1128?logo=unrealengine&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green)

## Overview

An engaging top-down shooter in Unreal Engine C++ with enemy AI, projectile systems, health management, and wave-based combat.

Built with **Unreal Engine** and **C++**, demonstrating professional game development patterns: the Actor-Component model, Unreal's reflection system (UPROPERTY/UFUNCTION), Blueprint interoperability, and optimized gameplay systems.

## Features

- Unreal Engine gameplay framework (GameMode, GameState, PlayerController)
- Custom C++ Actor and Component classes
- Blueprint-C++ interoperability
- Physics and collision systems
- Optimized asset loading

## Technologies Used

| Technology | Details |
|------------|---------|
| Unreal Engine | 4.x / 5.x |
| C++ | Modern C++17 |
| Blueprints | Visual scripting |
| Chaos Physics | Physics simulation |

## Screenshots / Demo

![Screenshot 1](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Beam01.png)

![Screenshot 2](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise00.png)

![Screenshot 3](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise000.png)

![Screenshot 4](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise01.png)

![Screenshot 5](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise02.png)

## Getting Started

### Prerequisites

- [Unreal Engine](https://www.unrealengine.com/en-US/download) 4.x or 5.x
- Visual Studio 2019 or 2022 with **Desktop development with C++**
- Git LFS

### Installation

```bash
git lfs install
git clone https://github.com/khaled71612000/Top-Down-Shooter.git
cd Top-Down-Shooter
```

1. Right-click `.uproject` → **Generate Visual Studio project files**
2. Open `.sln` in Visual Studio
3. Set config: **Development Editor | Win64**
4. Build (Ctrl+Shift+B) then launch the editor

## Project Structure

```
Top-Down-Shooter/
├── Source/                  # C++ source files
  Source/UEProject/Bomb.cpp
  Source/UEProject/Bomb.h
  Source/UEProject/Bullet.cpp
  Source/UEProject/Bullet.h
  Source/UEProject/CharacterKhaled.cpp
  Source/UEProject/CharacterKhaled.h
├── Content/                 # Assets, blueprints, levels
├── Config/                  # Project settings
└── Top-Down-Shooter.uproject
```

## License

[MIT License](LICENSE)
