#pragma once
#include <vector>
#include <string>
#include <ctime> 
#include <map>

using namespace std;

// Перечисления
enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions };

// Внешние объявления глобальных переменных
extern vector<Emotion_> Emotion;
extern string Emotion_Names[COUNT_Emotions];
extern string Worlds_Names[COUNT_Emotions];

// Структуры
struct Portal_ {
    string name;
    int target;
    bool open = true;
};

struct Peplace {
    Emotion_ id;
    string text;
};

struct NPC {
    string name;
    string text_NPC;
    int ID;
    vector<Peplace> Answer;
    void AddReplace(Emotion_ id, string t);
};

struct Player {
    int current_loc = SADNESS;
    int emotions[COUNT_Emotions] = { 50, 50, 50, 50, 50, 50 };
    bool life = true;
};

struct Location {
    string name;
    Emotion_ linked_emotion;
    bool is_locked = false;
    vector<Portal_> portal;
    vector<NPC> character;
};

struct GameSession { 
    // Основная информация о сессии
    string sessionId; // номер сессии
    time_t startTime, endTime; // Начало сессии / конец сессии
    double TimeMin; // перевод в минутах

    // Основная статистика
    int worldVisitCount;        // Сколько раз посещал каждый мир
    map<string, double> timeInWorld;         // Время в каждом мире (минуты)
    vector<string> worldHistory;   // История перемещений между мирами

    // Статистика по диалогам
    int counterChoices;                  // Всего принятых диалоговых решений
    map<string, int> popularChoices;        // Как часто выбирался каждый вариант
    map<string, vector<string>> choiceChains;// Цепочки решений (что выбирал после чего)

};

// Глобальные переменные
extern Player Hero;
extern Location Worlds[COUNT_Emotions];

