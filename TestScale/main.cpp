#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <windows.h>

#include "Global.h"
#include "systems.h"

using namespace std;

int main() {
    // Настройки: gg
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((time(nullptr)));

    GameCore Game;
    Game.InitGame();
    Game.Help();
    string temp;

    // Игровой цикл:
    while (Hero.life) {
        cin >> temp;
        if (temp == "edit") Game.Edit();
        if (temp == "help") Game.Help();
        if (temp == "status") Game.StatusInfo();
        if (temp == "info") Game.InitInfo();
        if (temp == "go") Game.Go();
        if (temp == "start") Game.StartDialog();
    }
    return 0;
}