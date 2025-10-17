#pragma once

#include <iostream> // ����
#include <string> // ����
#include <vector> // ����
#include <iomanip> // �������������� ������ 
#include <cstdlib> //������ � ��������������
#include <ctime> //  ��� ������ � ���������
#include <thread>  // ��� ������������� std::this_thread::sleep_for 
#include <chrono>  // ��� ������������� std::chrono::seconds 
#include <windows.h> // ��� ��������� ����� � ������ ���������

using namespace std;

enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions }; // ������������� ������,  count - ��� ������� �������������  
vector <Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER }; // �� ����� ���� ������ ������, 
// ��� ������ � ��� ����������� ������� � �� ������: ������ - ���������� ������, �������� - ���������� 

// �������� ������ � �����
string Emotion_Names[COUNT_Emotions] = { "�������", "������", "����", "�����", "�����������", "����", }; 
string Worlds_Names[COUNT_Emotions] = { "��� �������", "��� ������", "��� ����", "��� ������", "��� �����������", "��� �����" }; 

struct Portal_ { // ��������� ��� ���������� �����������  

    string name; // ���� �����
    int target; // ������ �� ������������ ���
    bool open = true; // ������ ��� ������ ������

};

struct Peplace { // ��������� ������, � ������ ������� �������� ����
    Emotion_ id; // �� ����
    string text; // �������

};

struct NPC { // ��������� NPC 
    string name; // ��� NPC
    string text_NPC; // ����� NPC
    int ID; // ���� ���������
    vector <Peplace> Answer; // �������� ������� ������

    void AddReplace(Emotion_ id, string t) { // ��������� �������� ������� 

        Answer.push_back({ id, t }); // �����

    }
};

struct Player { // ��������� ��� ��������� ������

    int current_loc = SADNESS; // ������� ������� 
    int emotions[COUNT_Emotions] = { 50, 50, 50, 50, 50, 50 }; // ������������� ����� (��������� � �������, ��� �� 50)
    bool life = true; // ���� �� �����

};

struct Location { // ��������� ����� �� ������� ����� ����� ������������

    string name; // ��� ���� 
    Emotion_ linked_emotion;  // ����� ������ ������� � ���� �����
    bool is_locked = false; // ���� ��� �������� ����
    vector<Portal_> portal; // ������ ����� ��������� 
    vector <NPC> character; // ���������

};

// ����� ���������� ���������� � �����������: � ������ ����� ������ ���������� ������ (+�����������) 
// � ��� ��� ������ ���� ������� ���������� � ��������������� cpp ������
// ��� ���������� ������ ���������� ������ � ���� ������� ������ � �����������

class InitSystem { // ������� ������� �������������
public:
    void Info(); // ������� ��� ���������� �� ������������������ ��������
    void CreateWorlds(); // �������������� ���� ��� ����������� �� �� ����������
    void CreatePortals(Emotion_ WorldEmotion); // �������������� ������� �� ����������� ������� = ����� ���� 
};

class GameLogicSystem { // ������� ��������� ������� ������
private: // ��������������� ����������:
    Emotion_ ArrayNum; // ���������� ��� ������ � ��� ���������� ������
    int dominationRate = 10; // ���������� ��� ��������� �����������/��������� ������ 
    int passiveRate = 5; // ���� ��� ��� � �������������� ����������

public:// ������:
    vector<Emotion_> Positive; // ������� ��� ����������� ������ �� ���������� � ����������
    vector<Emotion_> Negative; // ��� ����� ����� �������������� ������ ���������
    Emotion_ GetOpposite(Emotion_ feels); // ��������� ���� ������ � ���������� ���������������
    bool LimitCheck(int value); // �������� ������ �� ���������� �������
    void HeroLocCheck(); //�������� �������������� ������ 
    void LockedWorlds(); // �������� �����
    void ChangeGamerule(); // ����� ���� ������ ������� ������� ������ �� �������� ���� 
    void Transfuse(Emotion_ feels); // "������ ��� �������������� ������"
    void Addition(Emotion_ feels, vector<Emotion_> Array); // ���������� ������������ ������
    void Subtraction(Emotion_ feels, vector<Emotion_> Array); // ���������� ������������ ������
    void ChangeEmotions(Emotion_ DominationEmotion, bool sign); // ��������� ������������ ������ � ���� ��� ����. ��������

};

class OutputSystem { // ������� ������ ����������
public:
    void OutputDialog(int npcID);// ����� ������� 
    void OutputStates(); // ����� �����
    void CommandInfo(); // ����� ������ ������
    
};

class InputSystem : GameLogicSystem { // ������� ��������� �����, ������� � �������� ��������� ������
public:
    bool InputHandler(int choice, int npcID); // ������������ ���� ������ �� ����� �������

};

Player Hero; // ������������� ��������� ������ 
Location Worlds[COUNT_Emotions]; // ������ � ������
