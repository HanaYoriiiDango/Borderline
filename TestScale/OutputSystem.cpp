class OutputSystem { // ������� ������ ����������
public:

    void OutputDialog(int npcID) {

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // ��������� ���� ���������� � ���� ������

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { // �������� � ���� 

                cout << Worlds[Hero.current_loc].character[i].text_NPC << endl; // ������ ����� ���������  

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // ��������� ��������� �������

                    cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl; // � ������ ��

                }
            }
        }
    }

    void OutputStates() { // ����� ������ ��������� ������, �����

        cout << "������� ���������: " << States_Names[Hero.states] << endl;

        for (int i = 0; i < Emotion.size(); i++) {

            cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // ������� ������� ������ ������

        }

        cout << "���� ����: " << endl;

        for (int i = 0; i < Hero.items.size(); i++) {

            cout << left << setw(20) << Items_Names[i] << "\t" << 1 << endl; // ������� �������� ������

        }
    }

    void CommandInfo() { // ����� ������ ������

        cout << "Help - ������ ������ \n";
        cout << "Edit - �������� ������ / ���������\n";
        cout << "Info - ���������� � ������������������ �������� \n";
        cout << "Status - ���������� � ��������� ��������� \n";
        cout << "Go - ��� ����������� \n";
        cout << "Use - ��������� ������������ ������� �� ���������\n";
        cout << "Start - ������ ������ � ���������� (���� ���� � ��� ���������)\n";
    }
};
