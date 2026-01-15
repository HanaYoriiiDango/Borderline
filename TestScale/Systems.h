#pragma once
#include "Global.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class TextManager {
private:
    // Внутренние методы
    vector<string> FindWorldFolders();
    vector<string> FindJSONFiles(const string& folderPath);
    NPC LoadNPCFromFile(const string& filepath);
    DialogText ParseDialogText(const json& textJson);
    DialogAnswer ParseAnswer(const json& answerJson);
    Emotion_ StringToEmotion(const string& emotionStr);

public:
    // Общие методы
    void LoadAllNPCs();
    vector<NPC*> GetNPCsInWorld(Emotion_ world);
    NPC* GetNPCByID(const string& npcID);
    bool HasNPCInWorld(Emotion_ world);
};

class InitSystem { // инициализация 
public:
    void Info();
    void CreateWorlds();
    void CreatePortals(Emotion_ WorldEmotion);

};

class GameLogicSystem { // игровая логика
private:

    // вспом. переменные и массивы
    Emotion_ ArrayNum;
    int dominationRate = 5;
    int passiveRate = 2;
    vector<Emotion_> Positive;
    vector<Emotion_> Negative;

public:

    Emotion_ GetOpposite(Emotion_ feels);
    bool LimitCheck(int value);
    bool HeroLocCheck();
    void LockedValue(Emotion_ feels);
    Emotion_ DetectedEmotion(int feels);
    void MovingPlayer();
    void ChangeGamerule();
    void Transfuse(Emotion_ feels);
    void Addition(Emotion_ feels, vector<Emotion_> Array);
    void Subtraction(Emotion_ feels, vector<Emotion_> Array);
    void ChangeEmotions(Emotion_ DominationEmotion, bool sign);
    void ProcessGo();
    void StatusInfo();

};

class DialogSystem {
private:
    // Зависимости:
    TextManager& d_textManager;
    GameLogicSystem& d_gameLogic;


public:
    DialogSystem(TextManager& tm, GameLogicSystem& gl)
        : d_textManager(tm), d_gameLogic(gl) {};
    
    void RunDialog(NPC* npc);
    void ProcessDialog();


};

class GameCore { // игровое ядро, все системы разделены по модулям 
private:
    // Игровое ядро должно именно ВЛАДЕТЬ своими модулями - композиция  
    InitSystem Init;                
    TextManager Manager;            
    GameLogicSystem Logic;          
    DialogSystem Dialog;           
    string temp;

public:

    GameCore()
        : Dialog(Manager, Logic) 
    {}

    void InitGame();
    void EndGame();
    void Help();
    void ProcessCommand();

};

