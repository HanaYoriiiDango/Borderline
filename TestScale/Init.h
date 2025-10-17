#pragma once

#include <iostream> // база
#include <string> // база
#include <vector> // база
#include <iomanip> // форматирование вывода 
#include <cstdlib> //рандом и преобразования
#include <ctime> //  для работы с таймерами
#include <thread>  // Для использования std::this_thread::sleep_for 
#include <chrono>  // Для использования std::chrono::seconds 
#include <windows.h> // для настройки ввода и вывода кириллицы

using namespace std;

enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions }; // инициализирую эмоции,  count - для быстрой инициализации  
vector <Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER }; // но юзать буду именно массив, 
// все эмоции в нем расположены попарно и по логике: четное - позитивная эмоция, нечетная - негативная 

// названия эмоций и миров
string Emotion_Names[COUNT_Emotions] = { "Радость", "Грусть", "Сила", "Страх", "Спокойствие", "Гнев", }; 
string Worlds_Names[COUNT_Emotions] = { "Мир Радости", "Мир Грусти", "Мир Силы", "Мир Страха", "Мир Спокойствия", "Мир Гнева" }; 

struct Portal_ { // структура для реализации перемещения  

    string name; // куда ведет
    int target; // таргет на определенный мир
    bool open = true; // открыт или закрыт портал

};

struct Peplace { // структура реплик, к каждой реплики привязан айди
    Emotion_ id; // ее айди
    string text; // реплика

};

struct NPC { // структура NPC 
    string name; // имя NPC
    string text_NPC; // текст NPC
    int ID; // айди персонажа
    vector <Peplace> Answer; // Ответные реплики игрока

    void AddReplace(Emotion_ id, string t) { // Добавляет ответную реплику 

        Answer.push_back({ id, t }); // пушим

    }
};

struct Player { // Структура для персонажа игрока

    int current_loc = SADNESS; // текущая локация 
    int emotions[COUNT_Emotions] = { 50, 50, 50, 50, 50, 50 }; // эмоциональные шкалы (находятся в балансе, все по 50)
    bool life = true; // флаг на жизнь

};

struct Location { // структура миров по которым игрок будет перемещаться

    string name; // Имя мира 
    Emotion_ linked_emotion;  // Какая эмоция связана с этим миром
    bool is_locked = false; // флаг для закрытия мира
    vector<Portal_> portal; // связка миров порталами 
    vector <NPC> character; // персонажи

};

// Метод разделения объявления и определения: в классе пишем только объявление метода (+параметрика) 
// а вот уже логику этих методов распиывать в соответствующих cpp файлах
// при обьявлении метода желательно давать к нему краткий комент о функционале

class InitSystem { // система быстрой инициализации
public:
    void Info(); // выводит всю информацию об инициализированных объектах
    void CreateWorlds(); // инициализирует миры вне зависимости от их количества
    void CreatePortals(Emotion_ WorldEmotion); // инициализирует порталы за исключением портала = линку мира 
};

class GameLogicSystem { // система обработки игровой логики
private: // вспомогательные переменные:
    Emotion_ ArrayNum; // переменная для записи в нее конкретных эмоций
    int dominationRate = 10; // переменные для изменения доминантной/пассивной эмоции 
    int passiveRate = 5; // пока что они с фиксированными значениями

public:// логика:
    vector<Emotion_> Positive; // массивы для группировки эмоций на негативные и позитивные
    vector<Emotion_> Negative; // они нужны чтобы оптимизировать логику паттернов
    Emotion_ GetOpposite(Emotion_ feels); // принимает одну эмоцию а возвращает противоположную
    bool LimitCheck(int value); // проверка эмоций на достижение лимитов
    void HeroLocCheck(); //проверка местоположения игрока 
    void LockedWorlds(); // закрытие миров
    void ChangeGamerule(); // здесь буду менять игровые правила исходя из значений шкал 
    void Transfuse(Emotion_ feels); // "Эмоции как переливающиеся сосуды"
    void Addition(Emotion_ feels, vector<Emotion_> Array); // увеличение доминирующей эмоции
    void Subtraction(Emotion_ feels, vector<Emotion_> Array); // уменьшение доминирующей эмоции
    void ChangeEmotions(Emotion_ DominationEmotion, bool sign); // принимает доминирующую эмоцию и знак для фикс. значений

};

class OutputSystem { // система вывода информации
public:
    void OutputDialog(int npcID);// вывод диалога 
    void OutputStates(); // вывод шакал
    void CommandInfo(); // вывод списка команд
    
};

class InputSystem : GameLogicSystem { // система обработки ввода, связана с системой обработки логики
public:
    bool InputHandler(int choice, int npcID); // Обрабатывает ввод игрока во время диалога

};

Player Hero; // Инициализирую персонажа игрока 
Location Worlds[COUNT_Emotions]; // Массив с мирами
