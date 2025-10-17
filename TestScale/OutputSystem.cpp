class OutputSystem { // система вывода информации
public:

    void OutputDialog(int npcID) {

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // перебираю всех персонажей в мире игрока

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { // сраниваю с айди 

                cout << Worlds[Hero.current_loc].character[i].text_NPC << endl; // вывожу текст персонажа  

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // перебираю ответьные реплики

                    cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl; // и вывожу их

                }
            }
        }
    }

    void OutputStates() { // вывод общего состояния игрока, шакал

        cout << "Текущее состояние: " << States_Names[Hero.states] << endl;

        for (int i = 0; i < Emotion.size(); i++) {

            cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // выводим текущие эмоции игрока

        }

        cout << "Ваши вещи: " << endl;

        for (int i = 0; i < Hero.items.size(); i++) {

            cout << left << setw(20) << Items_Names[i] << "\t" << 1 << endl; // выводим предметы игрока

        }
    }

    void CommandInfo() { // вывод списка команд

        cout << "Help - список команд \n";
        cout << "Edit - изменить эмоции / состояние\n";
        cout << "Info - информация о инициализированных объектах \n";
        cout << "Status - информация о состоянии персонажа \n";
        cout << "Go - для перемещения \n";
        cout << "Use - позволяет использовать предмет из инвенторя\n";
        cout << "Start - начать диалог с персонажем (если есть с кем поболтать)\n";
    }
};
