#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Emotion_ { JOY, SADNESS, POWER, FEAR, CALM, ANGER, COUNT_Emotions }; // ������������� ������,  count - ��� �������������  
vector <Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER }; // �� ����� ���� ������ ������, 
// ��� ������ � ��� ����������� ������� � �� ������: ������ - ���������� ������, �������� - ���������� 

string Emotion_Names[COUNT_Emotions] = { "�������", "������", "����", "�����", "�����������", "����", }; // �������� ������ 
string Worlds_Names[COUNT_Emotions] = { "��� �������", "��� ������", "��� ����", "��� ������", "��� �����������", "��� �����" }; // �������� �����

struct Portal_ { // ��������� ��� ���������� ����������� 

    string name; // ���� �����
    int target; // ������ �� ������������ ���
    bool open = true; // ������ ��� ������ ������

};

struct Peplace { // ��������� ������, � ������ ������� �������� ����
    Emotion_ id;
    string text;

};

struct NPC { // ��������� NPC 
    string name; // ��� NPC
    vector <string> text_NPC; // ����� NPC
    int ID;
    vector <Peplace> Answer; // �������� ������� ������

    void AddReplace(Emotion_ id, string t) { // ��������� �������� ������� 

        Answer.push_back({ id, t });

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

class InitSystem {
public:
    void Info(); // 
    void CreateWorlds(); // �������������� ���� ��� ����������� �� �� ����������
    void CreatePortals(Emotion_ WorldEmotion); // �������������� ������� �� ����������� ������� = ����� ���� 
};

Player Hero; // ������������� ��������� ������ 
Location Worlds[COUNT_Emotions]; // ������ � ������
InitSystem Init;
