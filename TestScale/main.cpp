#include "Command.h"
//#include <windows.h>
//#include <wingdi.h> 
//linker::system::subsystem  - Windows(/ SUBSYSTEM:WINDOWS) - ������� wWinMain, � �� main
//configuration::advanced::character set - not set - ���� ���������� � ���������� 
//linker::input::additional dependensies Msimg32.lib; Winmm.lib

int main() {
    setlocale(LC_ALL, "RU");
    srand(static_cast<unsigned int>(time(nullptr)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    InitGame();
    StartGame();
    
}