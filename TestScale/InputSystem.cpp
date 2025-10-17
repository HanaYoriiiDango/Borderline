#include "Init.h"

bool InputSystem::InputHandler(int choice, int npcID) {

    int counter = 0; // счетчик

    if (choice == 0) return false;
    if (choice != 0) choice -= 1; // тк в демонтрации j + 1

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // перебираю персонажей в мире игрока

        if (Worlds[Hero.current_loc].character[i].ID == npcID) { //проверка на айди 

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // перебираю ответные реплики игрока персонажу

                if (choice == j) { // сравниваю ввод с репликой 

                    ChangeEmotions(Worlds[Hero.current_loc].character[i].Answer[j].id, true); // записываю ID в функцию, true - по умолчанию
                    counter++;

                }
            }
        }
    }
    if (counter == 1) return true; // счетчик == 1 возвращаем true (условия прошли)

}
