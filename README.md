# 🎮 Pong Game

A classic **Pong** game with AI opponent, built from scratch in **C++17** using **SFML 3.0**.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![SFML](https://img.shields.io/badge/SFML-3.0-green)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

---

## ✨ Features

- **AI Opponent** with realistic behavior (tracks ball position with dead-zone)
- **Physics-based ball movement** with angle-dependent paddle collision
- **Score tracking** (first to 5 points wins)
- **Game Over screen** with winner announcement
- **Randomized ball angles** after each goal
- **Delta time** for frame-independent movement

---

## 🎥 Demo

![Gameplay](screenshots/ponggame.gif)

![Screenshot](screenshots/ponggame.png)

---

## 🛠 Tech Stack

- **C++17** (OOP, STL, smart pointers)
- **SFML 3.0.2** (graphics, window management, events)
- **Visual Studio 2022** (MSVC compiler)

---

## 🏗 Architecture

PongGame/
├── Game.h / Game.cpp # Main game class (game loop, logic, rendering)
├── Paddle.h # Paddle class (movement, clamping)
├── Ball.h # Ball class (physics, collision detection)
├── PongGame.cpp # Entry point (main)
└── Fonts/ # Assets

**Design Patterns:**
- Game Loop Pattern
- Encapsulation (each class handles its own logic)
- RAII (`std::unique_ptr` for resource management)

---

## 🚀 How to Run

### Prerequisites
- Windows 10/11 x64
- Visual Studio 2022 (or later)
- SFML 3.0.2 (installed via NuGet)

### Steps
1. Clone the repository
2. Open `PongGame.sln` in Visual Studio
3. Switch to **Release | x64** configuration
4. Press **F5** or **Ctrl+F5**

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| **W** | Move player paddle up |
| **S** | Move player paddle down |

---

## 📚 What I Learned

- Implementing a **game loop** with delta time
- **Collision detection** and response (angle-based bouncing)
- Working with **external libraries** (SFML)
- Managing resources with **smart pointers** (`std::unique_ptr`)
- Structuring code with **OOP principles**

---

## 🎯 Future Improvements

- [ ] Main menu (Start/Settings/Quit)
- [ ] Local multiplayer (2 players)
- [ ] Sound effects (paddle hit, goal scored)
- [ ] Particle effects for ball trail
- [ ] Adjustable AI difficulty

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
