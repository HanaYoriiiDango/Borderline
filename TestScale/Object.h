#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;


enum Worlds_Num { SADNESS, JOY, FEAR, CALM, ANGER, POWER }; // ������������� ���� 
string Emotion_Names[6] = { "������", "�������", "�����", "�����������", "����", "����" }; // �������� ������ 
string Worlds_Names[6] = { "��� ������", "��� �������", "��� ������", "��� �����������", "��� �����", "��� ����" }; // �������� �����

struct Portal_ { // ��������� ��� ���������� ����������� ����� ������ ����������� ������� Go �� ��������
    string name; // � ������� ���� ���, ������� � ����� �������� � ������� ��� ������������ ������ �����������
    int target; // ������ ������ ������� ����, ��� ��� � ������� ������� �� ���� � ��� ����� ����� ������������ � �������� ��������� ������ (������ ��� ���������)
    bool open = true; // ��� ���� ������� �������� �� �� �������� ��� ������ ��� ���

};

struct info { // ��������������� ��������� ��� ���������� ������

    string dialog_Text; // ����� ����� �������� ������� ����������
    int effect[6]; // ���� ������ �������� �� ������������ (����������� ������ � ������) ���� ��� ����� ���������� ����� ������ � ���� �������

};

class NPC { // ����� ��� ���������� �������� �� ���� ���������� ���� 
public:

    string name; // ��� ���������
    vector<info> words; // ��������� ������ � ����� ������ ����� ��������������� ���������

    NPC(string name) : name(name) {}; // ����������� ������� ���

    void text(string letter, int sadness, int joy, int fear, int calm, int anger, int power) { // � ������ ������� ����� (������� ����� ������� ��������)
        // ����� ������� �������� ��� ������������ ���� ��� ����� �������� ����� ��� ��� ��� ���� ������
        words.push_back({ letter, {sadness, joy, fear, calm, anger, power} }); // ��������� ��� ��� � words 

    }

    void info() { // ���� ����� ����� ����� ��������������� ��� �������� ��� ��������� � ��� �������

        cout << name << ": "; // ������� ��� ���������

        for (int i = 0; i < words.size(); i++) {

            cout << words[i].dialog_Text; // ������� ����� ���������

            for (int j = 0; j < 6; j++) {

                cout << "(" << words[i].effect[j] << ") "; // ������� �� ����� ������ ������ �������� ������� ������ �� �����

            }

            cout << "\n";
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
    vector<Portal_> portal; // ��������� ������ � ����� ������ ������� ��������� ��� �������� � ����� �������� ������ ����

};

Player Hero; // ������������� ��������� ������ 
Location Worlds[6]; // ������ � ������ ������


void Init_Game() {

    NPC Ela("PORNO");
    Ela.text("BLADIMIR PUTIN MOLODEC", 100, 50, 100, 99, 90, 99);
    //Ela.info();

    // ������ ���� � ������� ��� ���
    Worlds[SADNESS].name = "��� ������";
    Worlds[SADNESS].portal.push_back({ "��� �������", JOY });
    Worlds[SADNESS].portal.push_back({ "��� ������", FEAR });
    Worlds[SADNESS].portal.push_back({ "��� �����������", CALM });
    Worlds[SADNESS].portal.push_back({ "��� �����", ANGER });
    Worlds[SADNESS].portal.push_back({ "��� ����", POWER });

    Worlds[JOY].name = "��� �������";
    Worlds[JOY].portal.push_back({ "��� ������", SADNESS });
    Worlds[JOY].portal.push_back({ "��� ������", FEAR });
    Worlds[JOY].portal.push_back({ "��� �����������", CALM });
    Worlds[JOY].portal.push_back({ "��� �����", ANGER });
    Worlds[JOY].portal.push_back({ "��� ����", POWER });

    Worlds[FEAR].name = "��� ������";
    Worlds[FEAR].portal.push_back({ "��� ������", SADNESS });
    Worlds[FEAR].portal.push_back({ "��� �������", JOY });
    Worlds[FEAR].portal.push_back({ "��� �����������", CALM });
    Worlds[FEAR].portal.push_back({ "��� �����", ANGER });
    Worlds[FEAR].portal.push_back({ "��� ����", POWER });

    Worlds[CALM].name = "��� �����������";
    Worlds[CALM].portal.push_back({ "��� ������", SADNESS });
    Worlds[CALM].portal.push_back({ "��� �������", JOY });
    Worlds[CALM].portal.push_back({ "��� ������", FEAR });
    Worlds[CALM].portal.push_back({ "��� �����", ANGER });
    Worlds[CALM].portal.push_back({ "��� ����", POWER });

    Worlds[ANGER].name = "��� �����";
    Worlds[ANGER].portal.push_back({ "��� ������", SADNESS });
    Worlds[ANGER].portal.push_back({ "��� �������", JOY });
    Worlds[ANGER].portal.push_back({ "��� ������", FEAR });
    Worlds[ANGER].portal.push_back({ "��� �����������", CALM });
    Worlds[ANGER].portal.push_back({ "��� ����", POWER });

    Worlds[POWER].name = "��� ����";
    Worlds[POWER].portal.push_back({ "��� ������", SADNESS });
    Worlds[POWER].portal.push_back({ "��� �������", JOY });
    Worlds[POWER].portal.push_back({ "��� ������", FEAR });
    Worlds[POWER].portal.push_back({ "��� �����������", CALM });
    Worlds[POWER].portal.push_back({ "��� �����", ANGER });

}