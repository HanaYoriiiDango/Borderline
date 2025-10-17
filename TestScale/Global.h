#pragma once
#include <vector>
#include <string>

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

// Глобальные переменные
extern Player Hero;
extern Location Worlds[COUNT_Emotions];

