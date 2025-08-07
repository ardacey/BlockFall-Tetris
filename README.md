# BlockFall - Tetris Game

A C++ implementation of the classic Tetris puzzle game with customizable blocks and grid configurations.

## 📋 Table of Contents
- [Features](#features)
- [Game Components](#game-components)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [File Structure](#file-structure)
- [Configuration Files](#configuration-files)
- [Building from Source](#building-from-source)
- [Game Controls](#game-controls)
- [Leaderboard](#leaderboard)
- [License](#license)

## ✨ Features

- **Classic Tetris Gameplay**: Drop and arrange falling blocks to clear lines
- **Custom Block Shapes**: Define your own block patterns via configuration files
- **Flexible Grid Size**: Customizable game board dimensions
- **Gravity Mode**: Toggle gravity effects on/off
- **Leaderboard System**: Track high scores and player names
- **Power-up System**: Special power-up blocks for enhanced gameplay
- **Console-based Interface**: Clean ASCII art representation using `██` and `▒▒` characters

## 🎮 Game Components

### Core Classes
- **BlockFall**: Main game engine handling game logic and state
- **GameController**: Manages gameplay flow and user interactions
- **Block**: Represents game pieces with multiple rotations
- **Leaderboard**: Manages high score tracking
- **LeaderboardEntry**: Individual score records

### Key Features
- **Multiple Block Rotations**: Each block can have different rotation states
- **Dynamic Grid Management**: Real-time grid updates and collision detection
- **Score System**: Points awarded for completed lines and strategic moves
- **Player Management**: Personalized gaming experience with name entry

## 🚀 Installation

### Prerequisites
- C++ compiler (GCC, MSVC, or Clang)
- Windows/Linux/Mac OS

### Quick Start
1. **Clone or download** this repository
2. **Navigate** to the BlockFall directory
3. **Run** the pre-compiled executable:
   ```bash
   ./blockfall.exe
   ```

## 🎯 How to Play

1. **Launch the game** by running `blockfall.exe`
2. **Enter your name** when prompted
3. **Use keyboard controls** to manipulate falling blocks:
   - Move blocks left/right
   - Rotate blocks
   - Drop blocks faster
4. **Complete horizontal lines** to clear them and score points
5. **Avoid filling up** the grid to the top
6. **Try to achieve** a high score for the leaderboard!

## 📁 File Structure

```
BlockFall-Tetris-main/
├── LICENSE                     # MIT License file
├── README.md                   # This file
└── BlockFall/
    ├── main.cpp               # Entry point
    ├── blockfall.exe          # Compiled executable
    ├── BlockFall.h/.cpp       # Main game engine
    ├── GameController.h/.cpp  # Game flow controller
    ├── Block.h               # Block class definition
    ├── Leaderboard.h/.cpp    # Score management
    ├── LeaderboardEntry.h/.cpp # Individual score entries
    ├── grid.dat              # Initial grid configuration
    ├── blocks.dat            # Block shape definitions
    ├── leaderboard.txt       # Saved high scores
    └── characters/           # Character art assets
        └── main/
            ├── main_clear.dat
            ├── main_standby1.dat
            └── main_standby2.dat
```

## ⚙️ Configuration Files

### `grid.dat`
Defines the initial game grid layout:
- `0` represents empty cells
- `1` represents occupied cells
- Default: 24x28 grid (rows x columns)

### `blocks.dat`
Contains block shape definitions in a specific format:
```
[block_pattern]
```
Example patterns:
- `[10 10 11]` - L-shaped block
- `[1111]` - Line block
- `[110 011]` - Z-shaped block

### `leaderboard.txt`
Stores high scores in the format:
```
PlayerName Score
```

## 🔨 Building from Source

If you want to compile the project yourself:

### Windows (Visual Studio)
```bash
cl main.cpp BlockFall.cpp GameController.cpp Leaderboard.cpp LeaderboardEntry.cpp -o blockfall.exe
```

### Linux/Mac (GCC)
```bash
g++ -std=c++11 main.cpp BlockFall.cpp GameController.cpp Leaderboard.cpp LeaderboardEntry.cpp -o blockfall
```

### Alternative Build
```bash
# Create object files
g++ -c *.cpp

# Link all objects
g++ -o blockfall *.o
```

## 🎮 Game Controls

*Note: Specific controls may vary based on implementation. Check the GameController class for exact key mappings.*

Common Tetris controls typically include:
- **Arrow Keys**: Move left/right, rotate, soft drop
- **Space**: Hard drop
- **Enter**: Confirm selections
- **ESC**: Exit game

## 🏆 Leaderboard

The game features a persistent leaderboard system that:
- **Saves scores** automatically to `leaderboard.txt`
- **Tracks player names** with their respective scores
- **Persists between** game sessions
- **Displays rankings** during gameplay

## 🛠️ Technical Details

- **Language**: C++11 or later
- **Platform**: Cross-platform (Windows, Linux, Mac)
- **Architecture**: Object-oriented design with modular components
- **Memory Management**: Proper resource management with destructors
- **File I/O**: Configuration and save data handled via file streams

## 🤝 Contributing

Feel free to contribute to this project by:
1. **Forking** the repository
2. **Creating** a feature branch
3. **Making** your improvements
4. **Submitting** a pull request

Potential areas for improvement:
- Enhanced graphics/UI
- Additional block shapes
- Multiplayer support
- Sound effects
- Advanced scoring system

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Arda Ceylan**

---

**Enjoy playing BlockFall Tetris!** 🎮✨

*For issues or questions, please create an issue in the repository.*
