#pragma once
#include "Global.h"

class InitSystem { // инициализация
public:
    void Info();
    void CreateWorlds();
    void CreatePortals(Emotion_ WorldEmotion);
    void Dialogues();

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
    bool InputHandler(int choice, int npcID);

};

class OutputSystem { // обработка вывода
public:
    void OutputDialog(int npcID);
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
    void ProcessDialog();
    void Go();
    void ProcessCommand();
    void ProcessClear(); 
};

