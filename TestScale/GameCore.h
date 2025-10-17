#pragma once
#include "Init.h"

class GameCore { // Класс ядра, в котором я инкапсулирую все системы  
private:
    InitSystem Init; // система инициализации всех игровых объектов
    InputSystem Input; // система обработки ввода
    OutputSystem Output; // система обработки вывода 
    GameLogicSystem Logic; // система для обработки игровой логики 

public: // Здесь я расписываю все основные команды 
    void InitGame(); // здесь прописываю всю инициализацию
    void Edit(); // изменение шкал напрямую
    void Help(); // Вывод всех команд
    void StatusInfo(); // вывод шкал
    void InitInfo(); // вывод информации о инициализированных объектах
    void StartDialog(); // начинает диалог, если есть с кем поболтать
    void Go(); // перемещение между мирами

};