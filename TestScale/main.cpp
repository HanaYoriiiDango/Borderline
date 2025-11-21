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
#include "Systems.h"

using namespace std;  

int main() {
    // Настройки:    
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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