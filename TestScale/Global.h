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

// Структуры
struct Portal_ {
    string name;
    int target;
    bool open = true;
};

// Структура для ответов
struct DialogAnswer {
    string text;
    Emotion_ emotion;
    bool sign; // true = увеличить, false = уменьшить
    int next_text_id;
};

// Структура для текста NPC
struct DialogText {
    int id;
    string text;
    Emotion_ emotion;
    bool sign; // true = увеличить, false = уменьшить
    vector<DialogAnswer> answers;
};

// Структура для NPC
struct NPC {
    string id;
    string name;
    Emotion_ world_link; // Линк персонажа с миром 
    vector<DialogText> texts;
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
 
};

// Глобальные переменные
extern Player Hero;
extern Location Worlds[COUNT_Emotions];
extern vector<NPC> Characters; // Все NPC игры