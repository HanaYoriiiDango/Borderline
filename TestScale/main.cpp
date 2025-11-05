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
    // Настройки: ggg
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((time(nullptr)));

    GameCore Game;
    Game.StartGame();
    Game.InitGame();
    Game.Help();

    // Игровой цикл:
    while (Hero.life) {

        Game.ProcessCommand();

    }
    return 0;
}