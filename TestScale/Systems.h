#pragma once
#include "Global.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;


class TextManager {
private:
    json DialogData;  

public:
    bool DialogLoader(const string& filename);
    string GetNPCtext(const string& npcID, int textID);
    int GetNPCcount(const string& npcID);
    vector<string> GetAnswers(const string& npcID, int textID);
};

class InitSystem { // инициализация 
private:
    TextManager DialogManager;


public:
    void Dialogues();
    TextManager& GetDialogManager() { return DialogManager; }

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

};

class InputSystem : public GameLogicSystem { // обработка ввода, связана с игровой логикой
public:
    InputSystem(StatisticsCollector* collector) : GameLogicSystem(collector) {}
    void InputHandler(int choice, int npcID, int textID);

};

class OutputSystem : NPC { // обработка вывода
public:

    void OutputDialog(int npcID, int textID);
    void OutputStates();
    void CommandInfo();

};

class GameCore { // игровое ядро, все системы разделены по модулям 
private:
    InitSystem Init;
    OutputSystem Output;
    StatisticsCollector Collector;
    GameLogicSystem Logic;
    InputSystem Input;
    string temp;


public:

    GameCore() : Logic(&Collector), Input(&Collector) {}

    void InitGame();
    void StartGame();
    void EndGame();
    void Edit();
    void Help();
    void StatusInfo();
    void InitInfo();
    int DialogList(int npcID, int textID, int action = -1);
    void ShowDialog(const string& npcId, int textId);
    void Go();
    void ProcessCommand();
    void ProcessClear();
    void ProcessDialog();

};
