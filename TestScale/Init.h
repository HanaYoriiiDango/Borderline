#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions }; // инициализирую эмоции,  count - для инициализации  
vector <Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER }; // но юзать буду именно массив, 
// все эмоции в нем расположены попарно и по логике: четное - позитивная эмоция, нечетная - негативная 

string Emotion_Names[COUNT_Emotions] = { "Радость", "Грусть", "Сила", "Страх", "Спокойствие", "Гнев", }; // названия эмоций 
string Worlds_Names[COUNT_Emotions] = { "Мир Радости", "Мир Грусти", "Мир Силы", "Мир Страха", "Мир Спокойствия", "Мир Гнева" }; // названия миров

struct Portal_ { // структура для реализации перемещения 

    string name; // куда ведет
    int target; // таргет на определенный мир
    bool open = true; // открыт или закрыт портал

};

struct Peplace { // структура реплик, к каждой реплики привязан айди
    Emotion_ id;
    string text;

};

struct NPC { // структура NPC 
    string name; // имя NPC
    vector <string> text_NPC; // текст NPC
    int ID;
    vector <Peplace> Answer; // Ответные реплики игрока

    void AddReplace(Emotion_ id, string t) { // Добавляет ответную реплику 

        Answer.push_back({ id, t });

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

class InitSystem {
public:
    void Info(); // 
    void CreateWorlds(); // инициализирует миры вне зависимости от их количества
    void CreatePortals(Emotion_ WorldEmotion); // инициализирует порталы за исключением портала = линку мира 
};

Player Hero; // Инициализирую персонажа игрока 
Location Worlds[COUNT_Emotions]; // Массив с мирами
InitSystem Init;
