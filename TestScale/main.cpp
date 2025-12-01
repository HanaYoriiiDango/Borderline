#include <windows.h>
#include "Global.h"
#include "Systems.h"
#include <cstdlib>
#include <ctime>

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