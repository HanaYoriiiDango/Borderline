#pragma once

#include "object.h"

Worlds_Num get_opposite_world(Worlds_Num world) { // ��������� ���� ������ � ���������� ���������������

    switch (world) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return CALM;
    case (CALM): return FEAR;
    case (ANGER): return POWER;
    case (POWER): return ANGER;

    }
}

void Check_movement() {

    for (int i = 0; i < 6; i++) {     // ��������� ��� ������ �� ���������� �������
        Worlds_Num emotion = static_cast<Worlds_Num>(i);
        int emotion_value = Hero.emotions[i];

        if ((emotion_value <= 0 || emotion_value >= 100) && !Worlds[i].is_locked) {// ���� ������ �������� ������� � � ��� ��� �� ������������

            Worlds[i].is_locked = true; // 1. ��������� ��� ���� ������

            Worlds_Num opposite_emotion = get_opposite_world(emotion); // 2. ��������� ��������������� ���
            Worlds[static_cast<int>(opposite_emotion)].is_locked = true;

            Hero.emotions[emotion] = 50; // 3. ���������� ������
            Hero.emotions[opposite_emotion] = 50;

            if (Hero.current_loc == i || Hero.current_loc == static_cast<int>(opposite_emotion)) { // 4. ���� ����� ��������� � ����� �� ����������� ����� - ����������
                vector<int> available_worlds;
                for (int j = 0; j < 6; j++) {
                    if (!Worlds[j].is_locked) {
                        available_worlds.push_back(j);
                    }
                }

                if (!available_worlds.empty()) {
                    int random_index = rand() % available_worlds.size();
                    Hero.current_loc = available_worlds[random_index];
                    cout << ">> ������� � " << Worlds_Names[Hero.current_loc]
                        << " ��-�� ���������� " << Worlds_Names[i]
                        << " � " << Worlds_Names[opposite_emotion] << endl;
                }
                else {
                    cout << ">> ��� ���� �������! ���� ���������.\n";
                    // ���������� ����
                }
            }
            else {
                cout << ">> " << Worlds_Names[i] << " � "
                    << Worlds_Names[opposite_emotion] << " �������!\n";
            }
        }
    }
}

void Change_emotions(Worlds_Num emotion, char math, int x) { // �������� ����� ������, ��� ��������� ������ � �� ����� �� ������� �� ��������

    // ����� � ����� ��������� ������� ������������ �������� ��, ����� ����� ����������� ��� ������������� � ������� char math

    if (Worlds[static_cast<int>(emotion)].is_locked) {
        return;
    }

    if (math != '+' && math != '-') return; // �������� �� ��������� ������ ����

    int new_value = Hero.emotions[emotion];

    if (math == '+') new_value += x; // ���������� ����� �������� ��� ����� � ����������
    else new_value -= x; // ���������� ����� �������� ��� ����� � ����������

    if (new_value < 0) new_value = 0; // ��������� ����� � ����� ���������, ���� ����� ������� �� ������� 100 ��� 0
    if (new_value > 100) new_value = 100;

    Hero.emotions[emotion] = new_value; // � ������ ���������� ����� �������� � ������ ������

    Worlds_Num opposite_emotion = get_opposite_world(emotion); // ������ ��� �������������� ������
    Hero.emotions[opposite_emotion] = 100 - Hero.emotions[emotion];

    if (emotion == Worlds[Hero.current_loc].linked_emotion) {  // �������� ��������� ������ ��� ������ �������� ����
        Check_movement();
    }

}

void Start_dialog() {

    bool start = true; // ���������� ��� ���������� ����� ������� 

    while (start) {

        for (int i = 0; i < 6; i++) {

            cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // ������� ������� ������ ������

        }

        int choice;

        NPC Ela("Ela");
        Ela.text("�� ���? (������ 1 / 2..., 0 - exit) ", 60, 40, 60, 40, 60, 40);
        Ela.info();
        cout << "1) SADNESS (+10)" << endl;
        cout << "2) JOY (-10)" << endl;
        cout << "3) FEAR (+10)" << endl;
        cout << "4) ANGER (-10)" << endl;
        cout << "5) POWER (+10)" << endl;
        cout << "6) CALM (-10)" << endl;
        cin >> choice; // ������� ������ ������ �� ������ ���������

        if (choice >= 0 || choice <= 6) { // ��������� ����� ���� �������������� ���������� ��������� ������ ������� 

            switch (choice) {
            case(1):
                Change_emotions(SADNESS, '+', 10);
                //Change_emotions(JOY, '-', 10); //????
                cout << "Sadness: " << Hero.emotions[SADNESS] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            case(2):
                Change_emotions(JOY, '-', 10);
                //Change_emotions(JOY, '+', 10); //????
                cout << "Joy: " << Hero.emotions[JOY] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            case(3):
                Change_emotions(FEAR, '+', 10);
                //Change_emotions(JOY, '-', 10); //????
                cout << "FEAR: " << Hero.emotions[FEAR] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            case(4):
                Change_emotions(ANGER, '-', 10);
                //Change_emotions(ANGER, '+', 10);
                cout << "ANGER: " << Hero.emotions[ANGER] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            case(5):
                Change_emotions(POWER, '+', 10);
                //Change_emotions(POWER, '-', 10);
                cout << "POWER: " << Hero.emotions[POWER] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            case(6):
                Change_emotions(CALM, '-', 10);
                //Change_emotions(CALM, '+', 10);
                cout << "CALM: " << Hero.emotions[CALM] << "\n"; // ������� ��� ���������� ����� �� �� ������
                break;
            }
        }
        if (choice == 0) { // ����� � �������

            start = false;

        }
    }

}

void Command_Go() {

    for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

        cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
            << (!Worlds[i].is_locked ? "��� ������ \n" : "��� ������ \n") << endl;

    }

    cout << "� ����� ��� ������� �������������? \n";
    int choice;
    cin >> choice; // ������� ����� ��������� ������ �� ����� ������������� �����

    if (choice > 0 || choice <= Worlds[Hero.current_loc].portal.size()) { // ��������� ����� ���� �������������� ������� �����

        int target_index = choice - 1;  // ���������� ��� ���� ��� � ����� 1 � ���� ���������� � ���� (�� � ���� ��� ������������ i + 1) wwwwwe
        Portal_& portal = Worlds[Hero.current_loc].portal[target_index];

        if (portal.open && !Worlds[portal.target].is_locked) {
            Hero.current_loc = portal.target;
            cout << "�� ������������ � " << Worlds_Names[Hero.current_loc] << endl;
        }
        else {
            cout << "���� ��� ������!\n";
        }
    }
}

void Start_Game() {

    string temp; // ���������� ��� ����� ������ 

    while (Hero.life) {

        cout << "��� ���������� ����� �� ����������, ��� � ���� \n";
        cout << "Go - ��� ����������� \n";
        cout << "Loc - ������� ������� ��������� ������ \n";
        cout << "Start - ������ ������ � ���������� \n";
        cin >> temp; // ������� ����� ����� �� ������ 

        if (temp == "Go") Command_Go(); // ������� ��� ��������� ���� ��� ������ � ��������� ������������ �� ��� ����� ��� ������� ������  
        if (temp == "Loc") cout << "Current loc: " << Hero.current_loc << endl; // ������� ������ ��� ������� ���������
        if (temp == "Start") Start_dialog(); // �������� ������ � ����������
    }
}