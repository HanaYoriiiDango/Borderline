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
        if (temp == "edit" || temp == "Edit") Game.Edit();
        if (temp == "help" || temp == "Help") Game.Help();
        if (temp == "status" || temp == "Status") Game.StatusInfo();
        if (temp == "info" || temp == "Info") Game.InitInfo();
        if (temp == "go" || temp == "Go") Game.Go();
        if (temp == "start" || temp == "Start") Game.StartDialog();
    }
    return 0;
}