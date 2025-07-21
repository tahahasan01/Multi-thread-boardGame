# 🕹️ Multi-Threading Game

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-linux%20%7C%20macOS%20%7C%20windows-lightgrey)]()
[![C++](https://img.shields.io/badge/language-C++-blue)]()
[![SDL2](https://img.shields.io/badge/graphics-SDL2-red)]()

> A multiplayer item collection game built in **C++** using **SDL2** for graphics and audio.  
> Demonstrates real-time **multi-threading** with **POSIX threads** and basic inter-process communication.

---

## 📑 Table of Contents

- [Features](#-features)  
- [Requirements](#-requirements)  
- [Installation](#-installation)  
- [Usage](#-usage)  
- [Game Controls](#-game-controls)  
- [Game Rules](#-game-rules)  
- [Contributing](#-contributing)  
- [License](#-license)

---

## 🚀 Features

- 🎮 **Multiplayer Support** – Two players can play simultaneously.
- 🖼️ **Graphics & Audio** – Powered by **SDL2**.
- 🔀 **Multi-threading** – Player inputs handled using **POSIX threads**.
- 📏 **Dynamic Game Board** – Random board size per game.
- 🎯 **Item Collection** – Players score by collecting items.

---

## 🧰 Requirements

- **C++ Compiler** (`g++`, `clang++`, etc.)
- **SDL2 Library**
- **POSIX Threads** (`pthread`)

---

## 🛠️ Installation

### 1. Clone the Repository

```bash
git clone https://github.com/tahahasan01/Multi-Threading-Game.git
cd Multi-Threading-Game
```

### 2. Install SDL2

#### macOS

```bash
brew install sdl2
```

#### Linux

```bash
sudo apt-get install libsdl2-dev
```

#### Windows

Download and install SDL2 from:  
➡️ [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)

---

## ⚙️ Compile the Game

```bash
g++ -o game game.cpp -lpthread -lSDL2
```

---

## ▶️ Run the Game

```bash
./game
```

---

## 🎮 Game Controls

### Player 1
- `W` – Move Up  
- `A` – Move Left  
- `S` – Move Down  
- `D` – Move Right

### Player 2
- `↑` – Move Up  
- `←` – Move Left  
- `↓` – Move Down  
- `→` – Move Right

---

## 🏁 Game Rules

- Collect as many items as possible.
- Each item increases the player’s score.
- Game ends when all items are collected.
- Player with the highest score **wins**.

---

## 🤝 Contributing

Contributions are welcome!  
Please fork the repository and submit a **pull request** for any improvements or bug fixes.

---

## 📄 License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for details.
