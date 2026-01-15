#include "systems.h"
#include <iostream>

using namespace std;

void DialogSystem::ProcessDialog() {

    // Проверяем есть ли NPC в текущем мире
    if (!d_textManager.HasNPCInWorld(Worlds[Hero.current_loc].linked_emotion)) {
        cout << "Здесь не с кем поговорить." << endl;
        return;
    }

    // Получаем всех NPC в этом мире
    vector<NPC*> availableNPCs = d_textManager.GetNPCsInWorld(Worlds[Hero.current_loc].linked_emotion);

    // Если NPC один сразу начинаем диалог
    if (availableNPCs.size() == 1) {
        RunDialog(availableNPCs[0]);

    }
    // Если несколько показываем выбор
    else {
        cout << "Вы можете поговорить с:" << endl;
        for (int i = 0; i < availableNPCs.size(); i++) {
            cout << (i + 1) << ") " << availableNPCs[i]->name << endl;
        }

        int choice;
        cin >> choice;

        if (choice > 0 && choice <= availableNPCs.size()) {
            RunDialog(availableNPCs[choice - 1]);

        }
    }
}

void DialogSystem::RunDialog(NPC* npc) {
    if (!npc || npc->texts.empty()) return;

    int currentTextID = 0;

    while (true) {
        // Находим текущий текст
        DialogText* currentText = nullptr;

        for (DialogText& text : npc->texts) {
            if (text.id == currentTextID) {
                currentText = &text;
                break;
            }
        }

        if (!currentText) {
            cout << "(Диалог завершён)" << endl;
            break;
        }


        // Показываем текст и ответы
        cout << currentText->text << endl << endl;

        d_gameLogic.ChangeEmotions(currentText->emotion, currentText->sign);
        d_gameLogic.StatusInfo();

        if (currentText->answers.empty()) {
            cout << "(Диалог завершён)" << endl;
            break;
        }

        for (int i = 0; i < currentText->answers.size(); i++) {
            cout << (i + 1) << ") " << currentText->answers[i].text << endl;
        }

        // Получаем выбор игрока
        cout << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice > 0 && choice <= currentText->answers.size()) {
            DialogAnswer& selectedAnswer = currentText->answers[choice - 1];


            d_gameLogic.ChangeEmotions(selectedAnswer.emotion, selectedAnswer.sign);


            currentTextID = selectedAnswer.next_text_id;


            if (currentTextID == -1) {
                cout << "(Диалог завершён)" << endl;
                break;
            }
        }
        else {
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}