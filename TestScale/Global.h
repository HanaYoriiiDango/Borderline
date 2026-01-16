#pragma once
#include <vector>
#include <string>
#include <ctime> 

using namespace std;

// Перечисления
enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions };  

// Внешние объявления глобальных переменных
extern vector<Emotion_> Emotion;
extern string Emotion_Names[COUNT_Emotions]; 
extern string Worlds_Names[COUNT_Emotions];

// Структуры: 
struct Portal_ { // Структура порталов 
    string name;
    int target;
    bool open = true;
};

struct DialogAnswer { // Структура для ответов
    string text;
    Emotion_ emotion;
    bool sign; // true = увеличить, false = уменьшить
    int next_text_id; // Переход к следующему диалогу по айди
};

struct DialogText { // Структура для текста NPC
    int id;
    string text;
    Emotion_ emotion;
    bool sign; // true = увеличить, false = уменьшить
    vector<DialogAnswer> answers;
};

struct NPC { // Структура для NPC
    string id;
    string name;
    Emotion_ world_link; // Линк персонажа с миром 
    vector<DialogText> texts;
};

struct Player { // Структура игрока 
    int current_loc = SADNESS;
    int emotions[COUNT_Emotions] = { 50, 50, 50, 50, 50, 50 };
    bool life = true;
};

struct Location { // Структура локации 
    string name; 
    Emotion_ linked_emotion;
    bool is_locked = false;
    vector<Portal_> portal;
 
};

// Глобальные переменные
extern Player Hero;
extern Location Worlds[COUNT_Emotions];
extern vector<NPC> Characters; // Все NPC игры