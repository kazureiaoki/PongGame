# 🎮 Pong Game

A classic **Pong** game with AI opponent, built from scratch in **C++17** using **SFML 3.0.2**.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![SFML](https://img.shields.io/badge/SFML-3.0-green)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

---

## ✨ Features

- Singleplayer: **Player vs AI bot**
- AI paddle with a **dead-zone** so it does not play perfectly
- Physics-based ball movement with **angle-dependent** paddle bounces
- **Score system** (first to 5 points wins)
- **Game Over** screen with winner announcement
- **Restart** game from keyboard (press **R**)
- **ESC** to quit instantly
- Short **post-goal pause** with a visible ball
- Randomized ball launch angle in range **[-45°, +45°]** after each goal

---

## 🎥 Demo

![Gameplay](screenshots/ponggame.gif)

![Screenshot](screenshots/ponggame.jpg)

---

## 🛠 Tech Stack

- **Language:** C++17 (OOP, inheritance, polymorphism, STL, smart pointers)
- **Graphics / Windowing:** SFML **3.0.2**
- **Build System:** CMake 3.21+
- **Compiler / IDE:** Visual Studio 2022 (MSVC, x64)
- **OS:** Windows 10/11 x64

---

## 🏗 Architecture

```
PongGame/
├── src/
│   ├── include/
│   │   ├── GameObject.h          # Abstract base for all game objects
│   │   ├── Ball.h                # Ball (physics, collisions)
│   │   ├── Paddle.h              # Paddles (player + AI)
│   │   ├── Game.h                # Main game class (loop, states)
│   │   ├── TextObject.h          # Base class for SFML text UI
│   │   ├── ScoreText.h           # Score display
│   │   ├── GameOverText.h        # Game Over banner
│   │   ├── RestartHintText.h     # "Press R to restart" hint
│   │   └── Constants.h           # All gameplay constants
│   ├── Ball.cpp
│   ├── Paddle.cpp
│   ├── Game.cpp
│   ├── TextObject.cpp
│   ├── ScoreText.cpp
│   ├── GameOverText.cpp
│   ├── RestartHintText.cpp
│   └── PongGame.cpp              # Entry point (main)
├── Fonts/
│   └── CaesarDressing-Regular.ttf
├── external/
│   └── SFML/                     # SFML as Git submodule
└── CMakeLists.txt
```

**Design Patterns:**

- `GameObject` is an abstract base class with `update()` and `draw()` for all entities.
- `Paddle`, `Ball`, and `TextObject` inherit from `GameObject`.
- `ScoreText`, `GameOverText`, `RestartHintText` inherit from `TextObject` to reuse UI logic.
- Game uses composition to own paddles, ball, and UI via `std::unique_ptr`.
- All “magic numbers” live in `Constants.h` as constexpr values.

Patterns used:

- Game Loop (`Game::run` → `handleEvents` → `update` → `render`)
- Inheritance & Polymorphism via `GameObject`
- Factory-like ball spawn with `enum class LaunchDirection`
- RAII with `std::unique_ptr` for SFML text objects
- DRY via shared `TextObject` base for all on-screen text

---

## 🚀 How to Run

### Requirements
- **Windows 10/11 x64**
- **Visual Studio 2022** with:
  - Desktop development with C++
  - CMake tools for Windows
- **Git** (with support for submodules)

### Step 1: Clone with Submodules
```
git clone --recursive https://github.com/kazureiaoki/PongGame.git
cd PongGame
```

> **Important:** Use `--recursive` to automatically download SFML as a submodule.

### Step 2: Generate Project with CMake
```
cmake -S . -B build -A x64
```

This will create a `build/` folder with the Visual Studio solution.

### Step 3: Open in Visual Studio
```
start build\PongGame.sln
```

Or manually: Open `build/PongGame.sln` in Visual Studio 2022.

### Step 4: Build and Run
1. Switch to **Release | x64** configuration
2. Right-click on **PongGame** → **Set as Startup Project**
3. Press **F5** (or **Ctrl+F5** to run without debugging)

The game will launch in a 1280x960 window.

CMake post-build step copies the Fonts/ folder next to the executable, so the game can be launched from any directory as long as the folder structure is preserved.

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| **W** | Move player paddle up |
| **S** | Move player paddle down |
| **R** | Restart after Game Over |
| **ESC** | Quit the game |

---

## 📚 What I Learned

- Designing a small **game architecture** with clear separation of responsibilities (input, update, render, UI, AI)
- Implementing an extensible **inheritance hierarchy** (`GameObject`, `Paddle`, `Ball`, `TextObject` and its descendants)
- Using **constants and strong types** (`constexpr` values, `enum class`) to avoid magic numbers and make code safer
- Managing UI and other heap-allocated resources with **RAII** and `std::unique_ptr`
- Integrating and building **SFML 3.0.2** via CMake and Git submodules on Windows


---

## 🎯 Future Improvements

- [ ] Main menu (Start/Settings/Quit)
- [ ] Local multiplayer (2 players)
- [ ] Sound effects (paddle hit, goal scored)
- [ ] Particle effects for ball trail
- [ ] Adjustable AI difficulty
- [ ] Observer patterns (for goals) / Factory (for object creation)
- [ ] High scores records
- [ ] Customization (colors, speed)

---

## 📄 License

This project was created as a technical assignment for a Junior C++ Developer position.  
Feel free to use it for learning purposes.

---

## 📧 Contact

**Author:** Daniella 

**LinkedIn:** https://www.linkedin.com/in/daniellatskhovriebova/ 

**Email:** daniellatskho@gmail.com

---

⭐ **If you like this project, give it a star!**
