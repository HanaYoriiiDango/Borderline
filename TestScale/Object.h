#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <ctime>
#include <thread>  // Для использования std::this_thread::sleep_for 
#include <chrono>  // Для использования std::chrono::seconds 


using namespace std;


enum Worlds_Num { SADNESS, JOY, FEAR, CALM, ANGER, POWER }; // инициализирую миры 
string Emotion_Names[6] = { "Грусть", "Радость", "Страх", "Спокойствие", "Гнев", "Сила" }; // названия эмоций 
string Worlds_Names[6] = { "Мир Грусти", "Мир Радости", "Мир Страха", "Мир Спокойствия", "Мир Гнева", "Мир Силы" }; // названия миров
bool end_game = false;

struct Portal_ { // структура для реализации перемещения между мирами посредством команды Go по порталам
    string name; // у портала есть имя, которое я смогу выводить в консоли для демонстрации выбора перемещения
    int target; // таргет играет ключеву роль, так как у каждого портала он свой и его можно легко приравнивать к текущему положению игрока (менять его положение)
    bool open = true; // это флаг который отвечате за то доступен мир игроку или нет

};

class NPC { // класс для реализации диалогов от лица персонажей игры 
public:

    string name; // имя персонажа
    vector<string> letter; // здесь будет хранится реплеки персонажей

    NPC(string name) : name(name) {}; // конструктор ожидает имя

    void text(string words) { // в методе ожидаем текст (который будет говорит персонаж)
        
        letter.push_back({ words }); 

    }

        void textOut(string temp) {

            for (int i = 0; i < temp.size(); i++) {

                cout << temp[i];
                cout.flush();  // Обновление вывода 
                this_thread::sleep_for(std::chrono::microseconds(500));  // Задержка на 1 секунду 
            }
        }

    void info() { // этот метод нужен чтобы непосредственно уже выводить имя персонажа и его реплику

        textOut(name); // выводим имя персонажа

        cout << ": "; // Далее текст 

        for (int i = 0; i < letter.size(); i++) {

            textOut(letter[i]);
            cout << endl;
        }
    }
};

struct Player { // Структура для персонажа игрока

    string name; // имя главного героя
    int current_loc = ANGER; // текущая позиция главного героя
    int emotions[6] = { 50, 50, 50, 50, 50, 50 }; // эмоциональные шкалы главного героя (находятся в балансе, все по 50)
    bool life = true;

};

struct Location { // структура для реализации миров по которым игрок будет перемещаться
    string name; // у каждого мира есть свое имя 
    Worlds_Num linked_emotion;  // Какая эмоция связана с этим миром
    bool is_locked = false; // флаг для закрытия мира
    vector<Portal_> portal; // векторный массив с типом данных прошлой структуры для привязки к мирам

};

Player Hero; // Инициализирую персонажа игрока 
//Location Worlds[6]; // Массив с нашими мирами

Worlds_Num get_opposite_emotion(Worlds_Num world) { // принимает одну эмоцию а возвращает противоположную

    switch (world) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return CALM;
    case (CALM): return FEAR;
    case (ANGER): return POWER;
    case (POWER): return ANGER;

    }
}

Location Worlds[6];

void InitPortal(Worlds_Num emotion) {

    switch (emotion) {
    case (SADNESS):
        Worlds[SADNESS].portal.push_back({ "Мир Радости", JOY });
        Worlds[SADNESS].portal.push_back({ "Мир Страха", FEAR });
        Worlds[SADNESS].portal.push_back({ "Мир Спокойствия", CALM });
        Worlds[SADNESS].portal.push_back({ "Мир Гнева", ANGER });
        Worlds[SADNESS].portal.push_back({ "Мир Силы", POWER });

    case (JOY):
        Worlds[JOY].portal.push_back({ "Мир Грусти", SADNESS });
        Worlds[JOY].portal.push_back({ "Мир Страха", FEAR });
        Worlds[JOY].portal.push_back({ "Мир Спокойствия", CALM });
        Worlds[JOY].portal.push_back({ "Мир Гнева", ANGER });
        Worlds[JOY].portal.push_back({ "Мир Силы", POWER });

    case (FEAR):
        Worlds[FEAR].portal.push_back({ "Мир Грусти", SADNESS });
        Worlds[FEAR].portal.push_back({ "Мир Радости", JOY });
        Worlds[FEAR].portal.push_back({ "Мир Спокойствия", CALM });
        Worlds[FEAR].portal.push_back({ "Мир Гнева", ANGER });
        Worlds[FEAR].portal.push_back({ "Мир Силы", POWER });

    case (CALM):
        Worlds[CALM].portal.push_back({ "Мир Грусти", SADNESS });
        Worlds[CALM].portal.push_back({ "Мир Радости", JOY });
        Worlds[CALM].portal.push_back({ "Мир Страха", FEAR });
        Worlds[CALM].portal.push_back({ "Мир Гнева", ANGER });
        Worlds[CALM].portal.push_back({ "Мир Силы", POWER });

    case (ANGER):
        Worlds[ANGER].portal.push_back({ "Мир Грусти", SADNESS });
        Worlds[ANGER].portal.push_back({ "Мир Радости", JOY });
        Worlds[ANGER].portal.push_back({ "Мир Страха", FEAR });
        Worlds[ANGER].portal.push_back({ "Мир Спокойствия", CALM });
        Worlds[ANGER].portal.push_back({ "Мир Силы", POWER });

    case (POWER):
        Worlds[POWER].portal.push_back({ "Мир Грусти", SADNESS });
        Worlds[POWER].portal.push_back({ "Мир Радости", JOY });
        Worlds[POWER].portal.push_back({ "Мир Страха", FEAR });
        Worlds[POWER].portal.push_back({ "Мир Спокойствия", CALM });
        Worlds[POWER].portal.push_back({ "Мир Гнева", ANGER });

    }
}

void InitWorlds(string name, Worlds_Num emotion, bool flag) {

    Worlds[emotion].name = name;
    Worlds[emotion].linked_emotion = emotion;
    Worlds[emotion].is_locked = flag;

    InitPortal(emotion);

}

void InitGame() {

    InitWorlds("Мир Грусти", SADNESS, false);
    InitWorlds("Мир Радости", JOY, false);
    InitWorlds("Мир Страха", FEAR, false);
    InitWorlds("Мир Спокойствия", CALM, false);
    InitWorlds("Мир Гнева", ANGER, false);
    InitWorlds("Мир Силы", POWER, false);  

}