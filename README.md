🕹️ Multi-Threading Game
A multiplayer item collection game built in C++ using SDL2 for graphics and audio. This project demonstrates multi-threading using POSIX threads (pthreads) and inter-process communication to handle player inputs and real-time game updates.

📑 Table of Contents
Features

Requirements

Installation

Usage

Game Controls

Game Rules

Contributing

License

🚀 Features
🎮 Multiplayer Support: Two players can play simultaneously.

🖼️ Graphics & Audio: Uses SDL2 for rendering and sound.

🔀 Multi-threading: Player inputs handled using POSIX threads.

🔄 Dynamic Game Board: Board size is randomly generated at game start.

🎯 Item Collection: Players collect items to score points.

🧰 Requirements
C++ Compiler (e.g., g++)

SDL2 Library

POSIX Threads (pthread)

🛠️ Installation
1. Clone the Repository
bash
Copy
Edit
git clone https://github.com/tahahasan01/Multi-Threading-Game.git
cd Multi-Threading-Game
2. Install SDL2
macOS
bash
Copy
Edit
brew install sdl2
Linux
bash
Copy
Edit
sudo apt-get install libsdl2-dev
Windows
Download and install SDL2 from the official site: https://www.libsdl.org/download-2.0.php

⚙️ Compilation
Compile the game using:

bash
Copy
Edit
g++ -o game game.cpp -lpthread -lSDL2
▶️ Usage
Run the game:

bash
Copy
Edit
./game
🎮 Game Controls
Player 1:
W - Up
A - Left
S - Down
D - Right

Player 2:
↑ - Up
← - Left
↓ - Down
→ - Right

🏁 Game Rules
The objective is to collect as many items as possible.

Each item collected increases a player's score.

The game ends when all items are collected.

The player with the highest score wins.

🤝 Contributing
Contributions are welcome!
Please fork the repository and submit a pull request for any improvements or bug fixes.

📄 License
This project is licensed under the MIT License.
See the LICENSE file for details
