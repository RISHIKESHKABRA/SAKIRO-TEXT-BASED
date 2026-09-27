#ifndef SEKIRO_GAME_HPP
#define SEKIRO_GAME_HPP

#include <string>

struct Character {
    std::string name;
    int hp;
    int maxHp;
    int posture;
    int maxPosture;
    int spiritEmblems;
};

class SekiroGame {
private:
    Character wolf;
    Character boss;
    int gourds;
    bool isRunning;

    void drawBar(const std::string& label, int current, int maxVal) const;
    void renderUI() const;
    void processTurn(int choice);
    void handleDeathblow();

public:
    SekiroGame();
    void start();
};

#endif // SEKIRO_GAME_HPP
