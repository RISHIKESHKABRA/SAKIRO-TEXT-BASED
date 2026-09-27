#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct Entity {
    string name;
    int hp;
    int maxHp;
    int posture;
    int maxPosture;
};

void drawBar(string label, int current, int maxVal) {
    cout << label << " [";
    int slots = 20;
    int filled = (current * slots) / maxVal;
    if (filled > slots) filled = slots;
    if (filled < 0) filled = 0;

    for (int i = 0; i < slots; i++) {
        if (i < filled) cout << "#";
        else cout << "-";
    }
    cout << "] (" << current << "/" << maxVal << ")\n";
}

int main() {
    srand((unsigned int)time(0));

    Entity wolf = {"Wolf (Sekiro)", 100, 100, 0, 100};
    Entity boss = {"General Tenzen Yamauchi", 150, 150, 0, 120};
    int gourds = 3;

    cout << "===============================================\n";
    cout << "         SEKIRO: SHADOWS DIE TWICE             \n";
    cout << "             Console Edition                   \n";
    cout << "===============================================\n\n";

    while (wolf.hp > 0 && boss.hp > 0) {
        cout << "-----------------------------------------------\n";
        drawBar(wolf.name + " HP     ", wolf.hp, wolf.maxHp);
        drawBar(wolf.name + " POSTURE", wolf.posture, wolf.maxPosture);
        cout << "Healing Gourds remaining: " << gourds << "\n\n";

        drawBar(boss.name + " HP     ", boss.hp, boss.maxHp);
        drawBar(boss.name + " POSTURE", boss.posture, boss.maxPosture);
        cout << "-----------------------------------------------\n";

        cout << "Choose Action:\n";
        cout << "1. Katana Attack\n";
        cout << "2. Prepare Guard / Deflect\n";
        cout << "3. Use Healing Gourd\n";
        cout << "> ";

        int choice;
        cin >> choice;

        cout << "\n";

        // Enemy action determination
        int bossAction = rand() % 2; // 0 = Heavy Attack, 1 = Light Attack

        if (choice == 1) { // Player Attacks
            cout << "Wolf strikes with the Kusabimaru!\n";
            boss.hp -= 15;
            boss.posture += 20;

            if (bossAction == 0) {
                cout << boss.name << " counters with a heavy slash! (-25 HP)\n";
                wolf.hp -= 25;
                wolf.posture += 15;
            } else {
                cout << boss.name << " swings back! (-15 HP)\n";
                wolf.hp -= 15;
                wolf.posture += 10;
            }
        } 
        else if (choice == 2) { // Player Deflects
            cout << "Wolf readies deflect stance...\n";
            if (bossAction == 0 || bossAction == 1) {
                cout << "PERFECT DEFLECT! Clang! You broken the enemy momentum!\n";
                boss.posture += 35;
                wolf.posture += 5; // Minimal posture accumulation on deflect
            }
        } 
        else if (choice == 3) { // Player Heals
            if (gourds > 0) {
                gourds--;
                wolf.hp = min(wolf.maxHp, wolf.hp + 50);
                cout << "Wolf drinks from Healing Gourd (+50 HP).\n";
            } else {
                cout << "No Gourds remaining!\n";
            }
        }

        // Posture Check / Deathblow trigger
        if (boss.posture >= boss.maxPosture) {
            cout << "\n***********************************************\n";
            cout << "   ENEMY POSTURE BROKEN! [R1] DEATHBLOW!      \n";
            cout << "***********************************************\n";
            boss.hp = 0;
            break;
        }

        if (wolf.posture >= wolf.maxPosture) {
            cout << "\nYour posture was broken! Sekiro staggers!\n";
            wolf.hp -= 30;
            wolf.posture = 0;
        }

        Sleep(1000);
    }

    if (boss.hp <= 0) {
        cout << "\nVICTORY ACHIEVED - " << boss.name << " Slain!\n";
    } else {
        cout << "\nDEATH - Shadows Die Twice...\n";
    }

    return 0;
}
