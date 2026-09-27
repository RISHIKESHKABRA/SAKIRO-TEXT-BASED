#include "../include/SekiroGame.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    void sleepMs(int ms) { Sleep(ms); }
#else
    #include <unistd.h>
    void sleepMs(int ms) { usleep(ms * 1000); }
#endif

SekiroGame::SekiroGame() {
    wolf = {"Wolf (Sekiro)", 100, 100, 0, 100, 10};
    boss = {"General Tenzen Yamauchi", 160, 160, 0, 120, 0};
    gourds = 3;
    isRunning = true;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void SekiroGame::drawBar(const std::string& label, int current, int maxVal) const {
    std::cout << label << " [";
    const int slots = 20;
    int filled = (current * slots) / maxVal;
    filled = std::clamp(filled, 0, slots);

    for (int i = 0; i < slots; ++i) {
        if (i < filled) std::cout << "#";
        else std::cout << "-";
    }
    std::cout << "] (" << current << "/" << maxVal << ")\n";
}

void SekiroGame::renderUI() const {
    std::cout << "\n===============================================\n";
    std::cout << "         SEKIRO: SHADOWS DIE TWICE             \n";
    std::cout << "             Console Edition                   \n";
    std::cout << "===============================================\n\n";

    drawBar(wolf.name + " HP     ", wolf.hp, wolf.maxHp);
    drawBar(wolf.name + " POSTURE", wolf.posture, wolf.maxPosture);
    std::cout << "Healing Gourds: " << gourds << " | Spirit Emblems: " << wolf.spiritEmblems << "\n\n";

    drawBar(boss.name + " HP     ", boss.hp, boss.maxHp);
    drawBar(boss.name + " POSTURE", boss.posture, boss.maxPosture);
    std::cout << "-----------------------------------------------\n";
}

void SekiroGame::processTurn(int choice) {
    int bossAction = std::rand() % 3; // 0: Light Attack, 1: Heavy Attack, 2: Sweep Attack

    std::cout << "\n--- TURN OUTCOME ---\n";

    switch (choice) {
        case 1: // Katana Attack
            std::cout << "> Wolf slashes with the Kusabimaru!\n";
            boss.hp -= 15;
            boss.posture += 18;

            if (bossAction == 1) {
                std::cout << "> " << boss.name << " hyper-armors through and counters! (-25 HP)\n";
                wolf.hp -= 25;
                wolf.posture += 15;
            } else {
                std::cout << "> " << boss.name << " strikes back! (-12 HP)\n";
                wolf.hp -= 12;
                wolf.posture += 10;
            }
            break;

        case 2: // Deflect / Parry
            std::cout << "> Wolf readies a perfect deflect...\n";
            if (bossAction == 0 || bossAction == 1) {
                std::cout << "> *CLANG!* Perfect Deflect! Boss posture heavily damaged!\n";
                boss.posture += 30;
                wolf.posture += 2;
            } else {
                std::cout << "> Boss executed a Sweep Attack! Deflect failed! (-30 HP)\n";
                wolf.hp -= 30;
                wolf.posture += 20;
            }
            break;

        case 3: // Loaded Shuriken (Prosthetic Tool)
            if (wolf.spiritEmblems >= 2) {
                wolf.spiritEmblems -= 2;
                std::cout << "> Wolf launches Loaded Shuriken! Interrupts enemy! (-20 HP)\n";
                boss.hp -= 20;
                boss.posture += 10;
            } else {
                std::cout << "> Not enough Spirit Emblems!\n";
            }
            break;

        case 4: // Heal
            if (gourds > 0) {
                gourds--;
                wolf.hp = std::min(wolf.maxHp, wolf.hp + 50);
                std::cout << "> Wolf quaffs Healing Gourd (+50 HP).\n";
            } else {
                std::cout << "> No Healing Gourds remaining!\n";
            }
            break;

        default:
            std::cout << "> Invalid action! You lose your turn!\n";
            break;
    }

    // Check Posture Breaks
    if (boss.posture >= boss.maxPosture) {
        handleDeathblow();
    } else if (wolf.posture >= wolf.maxPosture) {
        std::cout << "\n> WARNING: Wolf's posture broke! Staggered! (-35 HP)\n";
        wolf.hp -= 35;
        wolf.posture = 0;
    }

    if (wolf.hp <= 0) {
        std::cout << "\n===============================================\n";
        std::cout << "                 DEATH                         \n";
        std::cout << "       Shadows Die Twice...                    \n";
        std::cout << "===============================================\n";
        isRunning = false;
    }
}

void SekiroGame::handleDeathblow() {
    std::cout << "\n***********************************************\n";
    std::cout << "   ENEMY POSTURE BROKEN! [R1] SHINOBI EXECUTION! \n";
    std::cout << "***********************************************\n";
    boss.hp = 0;
    std::cout << "\nVICTORY ACHIEVED - " << boss.name << " Slain!\n";
    isRunning = false;
}

void SekiroGame::start() {
    while (isRunning) {
        renderUI();
        std::cout << "Actions:\n";
        std::cout << "1. Katana Attack\n";
        std::cout << "2. Deflect / Parry\n";
        std::cout << "3. Prosthetic: Loaded Shuriken (2 Emblems)\n";
        std::cout << "4. Healing Gourd\n";
        std::cout << "Select action (1-4): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        processTurn(choice);
        sleepMs(1200);
    }
}
