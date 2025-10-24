#pragma once
#include "Global.h"

class InitSystem { // �������������
public:
    void Info();
    void CreateWorlds();
    void CreatePortals(Emotion_ WorldEmotion);
};

class GameLogicSystem { // ������� ������
private:
    Emotion_ ArrayNum;
    int dominationRate = 10;
    int passiveRate = 5;

public:
    vector<Emotion_> Positive;
    vector<Emotion_> Negative;
    Emotion_ GetOpposite(Emotion_ feels);
    bool LimitCheck(int value);
    void HeroLocCheck();
    void LockedWorlds();
    void ChangeGamerule();
    void Transfuse(Emotion_ feels);
    void Addition(Emotion_ feels, vector<Emotion_> Array);
    void Subtraction(Emotion_ feels, vector<Emotion_> Array);
    void ChangeEmotions(Emotion_ DominationEmotion, bool sign);
};

class InputSystem : public GameLogicSystem { // ��������� �����, ������� � ������� �������
public:
    bool InputHandler(int choice, int npcID);

};

class OutputSystem { // ��������� ������
public:
    void OutputDialog(int npcID);
    void OutputStates();
    void CommandInfo();
};

class StatisticsCollector {
private: 
    GameSession Session;

public:
    void StartSession();
    void EndSession();

};

class GameCore { // ������� ����, ��� ������� ��������� �� �������
private:
    InitSystem Init;
    InputSystem Input;
    OutputSystem Output;
    GameLogicSystem Logic;
    StatisticsCollector Collector;

public:
    void InitGame();
    void StartGame();
    void EndGame();
    void Edit();
    void Help();
    void StatusInfo();
    void InitInfo();
    void StartDialog();
    void Go();
};

