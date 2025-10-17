#pragma once
#include "GameCore.h"

void GameCore::InitGame() { // ����� ���������� ��� �������������

    Init.CreateWorlds(); // �������������� ������������ ���� ����� � ��������

    Worlds[SADNESS].character.push_back({ "Beam1", "����������������� ������ ����� ��� ������� �����", 0 });

    Worlds[SADNESS].character[0].AddReplace(SADNESS, " (�������) : �� ���, ������� - ������ ? ����� �������� �������� ��� ������.���� ���� ���� ��������� �� ������������� ?");
    Worlds[SADNESS].character[0].AddReplace(FEAR, " (�����������): � ���� �������? ��� ������ ������ � �����, ��� �������! ����� ���� ���-������! ");
    Worlds[SADNESS].character[0].AddReplace(ANGER, " (� �������): ��... �� ���� �� ������������ ������ � ����-������? � �������?");

    Worlds[SADNESS].character.push_back({ "Beam2", "(������ ������. ����� �������� ��������)", 1 });

    Worlds[SADNESS].character[1].AddReplace(JOY, " (� ������ ����� ������ ��������): [�����]");
    Worlds[SADNESS].character[1].AddReplace(POWER, " (������� ����� �����): ������, � ���� �� ��������� ����������. ���� ���������� ������������");
    Worlds[SADNESS].character[1].AddReplace(CALM, " (������������� � ����): ����. � ��� ���� ��� �������? ���� �� ��������� �����������");

    Worlds[SADNESS].character.push_back({ "Beam3", "...", 2 });

    Worlds[SADNESS].character[2].AddReplace(SADNESS, " (C ������� �������):  ��� � ����������. ��� ������, � ���� ���� ���� ���� � �������");
    Worlds[SADNESS].character[2].AddReplace(FEAR, " (���� ���� � ����): �����... �����. �������������. ����� ���� ������.");
    Worlds[SADNESS].character[2].AddReplace(ANGER, " (����������): ������... ������ ��� ����� ����� ����");

}

void GameCore::Edit() {

    string temp; // ���������� ��� �����
    int choice1;
    int choice2;

    for (int i = 0; i < Emotion.size(); i++) { // ����������� ������� �������� ���� ����

        cout << i + 1 << ")" << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // ������� ������� ������ ������

    }

    cout << "����� ������ ������ ��������? (�����)" << endl;

    cin >> choice1; // ����� �� ���� ��������

    if (choice1 > 0 && choice1 < Emotion.size()) { // �������� ����� ����� �������������� ������

        cout << "����� �������� ���������� ��� ��������� �����?" << endl;
        cin >> choice2; // ����� �������� ��� �����

        int num = choice1 - 1; // ���������� ��� ���� ��� � ����� 1 � �� �� �������� ���� (�� � ���� ��� ������������ i + 1)

        Hero.emotions[num] = choice2; // ����� �������� �� ������ � ��������� �� ���� ������������
        cout << "����������� ����� �������� ��� ����� " << Emotion_Names[num] << ": " << Hero.emotions[num] << endl;
    }
}

void GameCore::Help() { // ����� ���� ������

    Output.CommandInfo(); // ������ ������

}

void GameCore::StatusInfo() {

    Output.OutputStates(); // ������ ����� � ��������� ������

}

void GameCore::InitInfo() {

    Init.Info(); // ���� � ���� ������������������ ��������

}


void GameCore::StartDialog() {

    bool start = true;

    if (!Worlds[Hero.current_loc].character.empty()) {

        while (start) {

            int choice;
            OutputSystem Nemo;

            cout << "____������ �� ������� ���� ������____" << endl;
            cout << "���� �������� � ������. �� �������� ����������� � �������" << endl;

            Output.OutputStates();
            Output.OutputDialog(0); // ������ ����� ��������� � ��������� ������ �������

            cin >> choice; // ������� ������ ������ 
            if (Input.InputHandler(choice, 0)) start = true; // ������������ ����
            else {
                cout << "������ �������" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(1); // ������ ����� ��������� � ��������� ������ �������

            cin >> choice; // ������� ������ ������ 
            if (Input.InputHandler(choice, 1)) start = true; // ������������ ����
            else {
                cout << "������ �������" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(2); // ������ ����� ��������� � ��������� ������ �������

            cin >> choice; // ������� ������ ������ 
            if (Input.InputHandler(choice, 2)) start = true; // ������������ ����
            else {
                cout << "������ �������" << endl;
                start = false;
            }
        }
    }
    else {

        cout << "������ � ���� �������� ���� �� � ��� �������������(" << endl;

    }
}

void GameCore::Go() {

    for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) { // ��� ��� ������������ ��������/�������� �����

        cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
            << (!Worlds[i].is_locked ? "��� ������ \n" : "��� ������ \n") << endl;

    }

    cout << "� ����� ��� ������� �������������? \n";
    int choice;
    cin >> choice; // ������� ����� ��������� ������ �� ����� ������������� �����

    if (choice > 0 || choice <= Worlds[Hero.current_loc].portal.size()) { // ��������� ����� ���� �������������� ������� �����

        int target_index = choice - 1;  // ���������� ��� ���� ��� � ����� 1 � ���� ���������� � ���� (�� � ���� ��� ������������ i + 1) wwwwwe
        Portal_& portal = Worlds[Hero.current_loc].portal[target_index]; // ��������� ������ ������


        if (portal.open && !Worlds[portal.target].is_locked) { // ������ � ��� � ������� ����� ����� ������������� ������ ���� ��������� 
            Hero.current_loc = portal.target;
            cout << "�� ������������ � " << Worlds_Names[Hero.current_loc] << endl;
        }
        else {
            cout << "���� ��� ������!\n";
        }
    }

}
