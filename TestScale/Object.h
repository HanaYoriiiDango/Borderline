#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <ctime>
#include <thread>  // ��� ������������� std::this_thread::sleep_for 
#include <chrono>  // ��� ������������� std::chrono::seconds 


using namespace std;


enum Worlds_Num { SADNESS, JOY, FEAR, CALM, ANGER, POWER }; // ������������� ���� 
string Emotion_Names[6] = { "������", "�������", "�����", "�����������", "����", "����" }; // �������� ������ 
string Worlds_Names[6] = { "��� ������", "��� �������", "��� ������", "��� �����������", "��� �����", "��� ����" }; // �������� �����
bool end_game = false;

struct Portal_ { // ��������� ��� ���������� ����������� ����� ������ ����������� ������� Go �� ��������
    string name; // � ������� ���� ���, ������� � ����� �������� � ������� ��� ������������ ������ �����������
    int target; // ������ ������ ������� ����, ��� ��� � ������� ������� �� ���� � ��� ����� ����� ������������ � �������� ��������� ������ (������ ��� ���������)
    bool open = true; // ��� ���� ������� �������� �� �� �������� ��� ������ ��� ���

};

class NPC { // ����� ��� ���������� �������� �� ���� ���������� ���� 
public:

    string name; // ��� ���������
    vector<string> letter; // ����� ����� �������� ������� ����������

    NPC(string name) : name(name) {}; // ����������� ������� ���

    void text(string words) { // � ������ ������� ����� (������� ����� ������� ��������)
        
        letter.push_back({ words }); 

    }

        void textOut(string temp) {

            for (int i = 0; i < temp.size(); i++) {

                cout << temp[i];
                cout.flush();  // ���������� ������ 
                this_thread::sleep_for(std::chrono::microseconds(500));  // �������� �� 1 ������� 
            }
        }

    void info() { // ���� ����� ����� ����� ��������������� ��� �������� ��� ��������� � ��� �������

        textOut(name); // ������� ��� ���������

        cout << ": "; // ����� ����� 

        for (int i = 0; i < letter.size(); i++) {

            textOut(letter[i]);
            cout << endl;
        }
    }
};

struct Player { // ��������� ��� ��������� ������

    string name; // ��� �������� �����
    int current_loc = ANGER; // ������� ������� �������� �����
    int emotions[6] = { 50, 50, 50, 50, 50, 50 }; // ������������� ����� �������� ����� (��������� � �������, ��� �� 50)
    bool life = true;

};

struct Location { // ��������� ��� ���������� ����� �� ������� ����� ����� ������������
    string name; // � ������� ���� ���� ���� ��� 
    Worlds_Num linked_emotion;  // ����� ������ ������� � ���� �����
    bool is_locked = false; // ���� ��� �������� ����
    vector<Portal_> portal; // ��������� ������ � ����� ������ ������� ��������� ��� �������� � �����

};

Player Hero; // ������������� ��������� ������ 
//Location Worlds[6]; // ������ � ������ ������

Worlds_Num get_opposite_emotion(Worlds_Num world) { // ��������� ���� ������ � ���������� ���������������

    switch (world) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return CALM;
    case (CALM): return FEAR;
    case (ANGER): return POWER;
    case (POWER): return ANGER;

    }
}

Location Worlds[6];

void InitPortal(Worlds_Num emotion) {

    switch (emotion) {
    case (SADNESS):
        Worlds[SADNESS].portal.push_back({ "��� �������", JOY });
        Worlds[SADNESS].portal.push_back({ "��� ������", FEAR });
        Worlds[SADNESS].portal.push_back({ "��� �����������", CALM });
        Worlds[SADNESS].portal.push_back({ "��� �����", ANGER });
        Worlds[SADNESS].portal.push_back({ "��� ����", POWER });

    case (JOY):
        Worlds[JOY].portal.push_back({ "��� ������", SADNESS });
        Worlds[JOY].portal.push_back({ "��� ������", FEAR });
        Worlds[JOY].portal.push_back({ "��� �����������", CALM });
        Worlds[JOY].portal.push_back({ "��� �����", ANGER });
        Worlds[JOY].portal.push_back({ "��� ����", POWER });

    case (FEAR):
        Worlds[FEAR].portal.push_back({ "��� ������", SADNESS });
        Worlds[FEAR].portal.push_back({ "��� �������", JOY });
        Worlds[FEAR].portal.push_back({ "��� �����������", CALM });
        Worlds[FEAR].portal.push_back({ "��� �����", ANGER });
        Worlds[FEAR].portal.push_back({ "��� ����", POWER });

    case (CALM):
        Worlds[CALM].portal.push_back({ "��� ������", SADNESS });
        Worlds[CALM].portal.push_back({ "��� �������", JOY });
        Worlds[CALM].portal.push_back({ "��� ������", FEAR });
        Worlds[CALM].portal.push_back({ "��� �����", ANGER });
        Worlds[CALM].portal.push_back({ "��� ����", POWER });

    case (ANGER):
        Worlds[ANGER].portal.push_back({ "��� ������", SADNESS });
        Worlds[ANGER].portal.push_back({ "��� �������", JOY });
        Worlds[ANGER].portal.push_back({ "��� ������", FEAR });
        Worlds[ANGER].portal.push_back({ "��� �����������", CALM });
        Worlds[ANGER].portal.push_back({ "��� ����", POWER });

    case (POWER):
        Worlds[POWER].portal.push_back({ "��� ������", SADNESS });
        Worlds[POWER].portal.push_back({ "��� �������", JOY });
        Worlds[POWER].portal.push_back({ "��� ������", FEAR });
        Worlds[POWER].portal.push_back({ "��� �����������", CALM });
        Worlds[POWER].portal.push_back({ "��� �����", ANGER });

    }
}

void InitWorlds(string name, Worlds_Num emotion, bool flag) {

    Worlds[emotion].name = name;
    Worlds[emotion].linked_emotion = emotion;
    Worlds[emotion].is_locked = flag;

    InitPortal(emotion);

}

void InitGame() {

    InitWorlds("��� ������", SADNESS, false);
    InitWorlds("��� �������", JOY, false);
    InitWorlds("��� ������", FEAR, false);
    InitWorlds("��� �����������", CALM, false);
    InitWorlds("��� �����", ANGER, false);
    InitWorlds("��� ����", POWER, false);  

}