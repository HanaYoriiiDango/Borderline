#pragma once
#include <vector>
#include <string>
#include <ctime> 
#include <map> 
#include <fstream>

using namespace std;

// Перечисления
enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions }; 

// Внешние объявления глобальных переменных
extern vector<Emotion_> Emotion;
extern vector<string> Folders;
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
    bool sign;
    string text;
};

struct Text_NPC {
    int ID;
    string text;
    vector<Peplace> Answer;


};

struct Player {
    int current_loc = SADNESS;
    int emotions[COUNT_Emotions] = { 50, 50, 50, 50, 50, 50 };
    bool life = true;
};

class NPC {
public:
    string name;
    int ID;
    vector<Text_NPC> text_NPC;
    void AddtextNPC(int id, string t);
    void AddReplace(int textID, Emotion_ id, bool sign, string t);

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
    int ID; // номер сессии
    time_t startTime, endTime; // Начало сессии / конец сессии
    double TimeMin; // перевод в минутах

    // Основная статистика
    int worldVisitSad;        // Сколько раз посещал sadness
    int worldVisitJoy;        // Сколько раз посещал joy и т.д
    int worldVisitPower;        
    int worldVisitFear;        
    int worldVisitCalm;        
    int worldVisitAnger;       
    int AllVisitCount;        // Сколько раз перемещался в общем 

    // Статистика по диалогам
    int counterChoices;                  // Всего принятых диалоговых решений

};

// Глобальные переменные
extern Player Hero;
extern Location Worlds[COUNT_Emotions];
