# Top-Down Shooter


![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-0E1128?logo=unrealengine&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green)

**Top-Down Shooter** is a project developed using the Unreal Engine, designed to create an engaging top-down shooter game. This project focuses on advanced gameplay mechanics, AI interactions, and immersive player experiences.


## Live Demo

[![Watch Gameplay Demo](https://img.youtube.com/vi/_h-xcQ6VQqE/maxresdefault.jpg)](https://youtu.be/_h-xcQ6VQqE)

> Click the thumbnail above to watch the full demo video.

## Key Components

### Config
- **Configuration Files:** Contains settings and configurations for the project.

### Content
- **Game Assets:** Includes models, textures, and other assets used in the game (Note: Some assets may not be fully functional or correctly displayed).

### Source
- **PlayerController.cpp:** Manages player movement, shooting, and interactions.
- **EnemyAIController.cpp:** Implements AI behaviors for enemy characters, including pathfinding and attacking.
- **GameManager.cpp:** Oversees game state, score tracking, and level progression.

### UEProject.uproject
- **Project File:** The main project file for the Unreal Engine project.

## Features

- **Top-Down Perspective:** Classic top-down shooter gameplay with modern enhancements.
- **Advanced AI:** Sophisticated enemy AI for challenging and dynamic interactions.
- **Interactive Environment:** Includes destructible objects and interactive elements.

Please note that while the code has been correctly pushed, some assets and the map might be broken or not fully functional. 
[YouTube Video](https://youtu.be/_h-xcQ6VQqE?si=wzEjOUhzlgymsMcH)

![5](https://github.com/khaled71612000/Top-Down-Shooter/assets/59780800/0f227863-b521-4a9a-a0a5-f89cc7cb928d)
![image](https://github.com/khaled71612000/Top-Down-Shooter/assets/59780800/12237efd-1f6f-49ef-aaa4-99b5b32ab6d8)
![image](https://github.com/khaled71612000/Top-Down-Shooter/assets/59780800/e09bd833-6609-49c1-9b83-3ba99d646230)
![image](https://github.com/khaled71612000/Top-Down-Shooter/assets/59780800/706cb751-c014-4e9a-a48d-6959b103911a)
![image](https://github.com/khaled71612000/Top-Down-Shooter/assets/59780800/15c8d290-202d-4a14-b6ce-635e5116a60e)


## Screenshots

![Screenshot 1](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Beam01.png)

![Screenshot 2](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise00.png)

![Screenshot 3](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise000.png)

![Screenshot 4](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise01.png)

![Screenshot 5](https://raw.githubusercontent.com/khaled71612000/Top-Down-Shooter/HEAD/Content/sA_PickupSet_1/Materials/Textures/Noise02.png)


## Tech Stack

| Technology | Role |
|---|---|
| Unreal Engine 4/5 | Game engine (Blueprints + C++) |
| C++ | Gameplay systems, custom components |
| HLSL / USF | Custom shader authoring |
| Git LFS | Large asset version control |


## Getting Started

### Prerequisites
- [Unreal Engine](https://www.unrealengine.com/en-US/download) 4.x or 5.x
- Visual Studio 2019 or 2022 with **Desktop development with C++**
- Git LFS (`git lfs install`)

### Setup
```bash
git lfs install
git clone https://github.com/khaled71612000/Top-Down-Shooter.git
```
1. Right-click the `.uproject` → **Generate Visual Studio project files**
2. Open `.sln` → Build (**Development Editor | Win64**)
3. Launch via Unreal Editor
