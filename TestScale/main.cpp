#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <windows.h>
#include <fstream>

#include "Global.h"
#include "systems.h"

using namespace std;

int main() {
    // Настройки:
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
        if (temp == "Edit") Game.Edit();
        if (temp == "Help") Game.Help();
        if (temp == "Status") Game.StatusInfo();
        if (temp == "Info") Game.InitInfo();
        if (temp == "Go") Game.Go();
        if (temp == "Start") Game.StartDialog();
    }
    return 0;
}