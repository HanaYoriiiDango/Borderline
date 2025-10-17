#include "Init.h"

void OutputSystem::OutputDialog(int npcID) {

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // ��������� ���� ���������� � ���� ������

        if (Worlds[Hero.current_loc].character[i].ID == npcID) { // �������� � ���� 

            cout << Worlds[Hero.current_loc].character[i].text_NPC << endl; // ������ ����� ���������  

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // ��������� ��������� �������

                cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl; // � ������ ��

            }
        }
    }
}

void OutputSystem::OutputStates() { // ����� �����

    for (int i = 0; i < Emotion.size(); i++) {

        // ������� ������� ������ ������
        cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; 

    }
}

void OutputSystem::CommandInfo() { // ����� ������ ������

    cout << "Help - ������ ������ \n";
    cout << "Edit - �������� ������ / ���������\n";
    cout << "Info - ���������� � ������������������ �������� \n";
    cout << "Status - ���������� � ��������� ��������� \n";
    cout << "Go - ��� ����������� \n";
    cout << "Use - ��������� ������������ ������� �� ���������\n";
    cout << "Start - ������ ������ � ���������� (���� ���� � ��� ���������)\n";
}

