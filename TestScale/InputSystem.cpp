#include "Init.h"

bool InputSystem::InputHandler(int choice, int npcID) {

    int counter = 0; // �������

    if (choice == 0) return false;
    if (choice != 0) choice -= 1; // �� � ����������� j + 1

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // ��������� ���������� � ���� ������

        if (Worlds[Hero.current_loc].character[i].ID == npcID) { //�������� �� ���� 

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // ��������� �������� ������� ������ ���������

                if (choice == j) { // ��������� ���� � �������� 

                    ChangeEmotions(Worlds[Hero.current_loc].character[i].Answer[j].id, true); // ��������� ID � �������, true - �� ���������
                    counter++;

                }
            }
        }
    }
    if (counter == 1) return true; // ������� == 1 ���������� true (������� ������)

}
