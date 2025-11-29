#pragma once
#include "Global.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class TextManager {
public:
    // Общие методы
    void LoadAllNPCs();
    vector<NPC*> GetNPCsInWorld(Emotion_ world);
    NPC* GetNPCByID(const string& npcID);
    bool HasNPCInWorld(Emotion_ world);

private:
    // Внутренние методы
    vector<string> FindWorldFolders();
    vector<string> FindJSONFiles(const string& folderPath);
    NPC LoadNPCFromFile(const string& filepath);
    DialogText ParseDialogText(const json& textJson);
    DialogAnswer ParseAnswer(const json& answerJson);
    Emotion_ StringToEmotion(const string& emotionStr);
};

class InitSystem { // инициализация 
public:
    void Info();
    void CreateWorlds();
    void CreatePortals(Emotion_ WorldEmotion);

};

class StatisticsCollector {
public:
    GameSession Session;
    ofstream SaveStatistics;
    void StartSession();
    void EndSession();
    void SaveData();
    void ClearStatistics();

};

class GameLogicSystem { // игровая логика
private:
    Emotion_ ArrayNum;
    int dominationRate = 10;
    int passiveRate = 5;

protected:
    StatisticsCollector* statsCollector;

public:
    GameLogicSystem(StatisticsCollector* collector) : statsCollector(collector) {}

    vector<Emotion_> Positive;
    vector<Emotion_> Negative;
    Emotion_ GetOpposite(Emotion_ feels);
    bool LimitCheck(int value);
    bool HeroLocCheck();
    void LockedWorlds();
    void UnlockedWorlds();
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
    TextManager& textManager;
    GameLogicSystem& gameLogic;
    StatisticsCollector& statsCollector;

public:
    DialogSystem(TextManager& tm, GameLogicSystem& gl, StatisticsCollector& sc)
        :textManager(tm), gameLogic(gl), statsCollector(sc) {};
    
    void RunDialog(NPC* npc);
    void ProcessDialog();


};

class GameCore { // игровое ядро, все системы разделены по модулям 
private:
   
    StatisticsCollector Collector;  
    InitSystem Init;                
    TextManager Manager;            
    GameLogicSystem Logic;          
    DialogSystem Dialog;           
    string temp;

public:

    GameCore()
        : Logic(&Collector),
        Dialog(Manager, Logic, Collector) 
    {}

    void InitGame();
    void StartGame();
    void EndGame();
    void Help();
    void ProcessCommand();

};
