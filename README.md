# SAKIRO-TEXT-BASED

# 🗡️ Sekiro: Shadows Die Twice — C++ Console Edition

A lightweight, terminal-based turn-based combat simulator inspired by FromSoftware's **Sekiro: Shadows Die Twice**, implemented in modular C++.

![C++ Version](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![IDE Support](https://img.shields.io/badge/Dev--C%2B%2B-Compatible-brightgreen.svg)

---

## 🎮 Gameplay Features

- **Posture System:** Lowering enemy HP slows down their posture recovery. Breaking maximum posture unlocks an instant **Shinobi Execution**.
- **Deflect Mechanics:** Time your guard to negate incoming health damage and inflict heavy posture buildup on the boss.
- **Prosthetic Tools:** Spend **Spirit Emblems** to deploy utility items like the **Loaded Shuriken**.
- **Gourd Management:** Limited consumable healing during encounters.

---

## 🛠️ Build & Run Instructions

### Option 1: Dev-C++ (Windows)

1. Open **Dev-C++**.
2. Go to `File > New > Project...`
3. Select **Console Application**, choose **C++ Project**, and set project name to `SekiroCLI`.
4. Right-click project root in Project Explorer > **Add to Project**:
   - Add `include/SekiroGame.hpp`
   - Add `src/SekiroGame.cpp`
   - Add `src/main.cpp`
5. Press `F11` (**Compile & Run**).

---

### Option 2: Command Line (GCC / Clang)

```bash
# Clone the repository
git clone [https://github.com/your-username/sekiro-cpp-cli.git](https://github.com/your-username/sekiro-cpp-cli.git)
cd sekiro-cpp-cli

# Compile using g++
g++ -std=c++17 src/main.cpp src/SekiroGame.cpp -Iinclude -o sekiro

# Run Executable
# On Windows:
sekiro.exe
# On Linux/macOS:
./sekiro
