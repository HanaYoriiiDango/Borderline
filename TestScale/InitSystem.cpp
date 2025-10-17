#include "Init.h" // здесь хранится вся инициализация
// в cpp храню весь функционал системы инициализации

void InitSystem::Info() { // Выводит всю информацию о инициализированных объектах

    for (int i = 0; i < Emotion.size(); i++) { // перебираю эмоции

        cout << Worlds[i].name << endl; // смотрю какое имя было инциализированно
        cout << "Link: " << Worlds[i].linked_emotion << endl; // линк мира с эмоцией
        cout << "PortalSize: " << Worlds[i].portal.size() << endl; //количество созданных портало в мире

        for (int j = 0; j < Worlds[i].portal.size(); j++) { // перебираю порталы

            cout << "PortaName: " << Worlds[i].portal[j].name << endl; // смотрю куда они ведут
            cout << "PortalTarget: " << Worlds[i].portal[j].target << endl;

        }
    }
}

void InitSystem::CreateWorlds() { // инициализирует миры вне зависимости от их количества

    for (int i = 0; i < Emotion.size(); i++) { // перебира эмоции, т.к. кол-во эмоций = кол-ву миров (они связаны)

        Worlds[i].name = Worlds_Names[i]; // назначаю миру имя 
        Worlds[i].linked_emotion = Emotion[i]; // назначаю миру линк (связь) с конкретной эмоцией

        CreatePortals(Worlds[i].linked_emotion); // передаю этот линк для создания порталов

    }
}

void InitSystem::CreatePortals(Emotion_ WorldEmotion) { // инициализирует порталы за исключением портала = линку мира 

    for (int i = 0; i < Emotion.size(); i++) { // перебираю эмоции

        if (WorldEmotion == i) { // если линк сходится с перебираемой эмоцией

            for (int j = 0; j < Emotion.size(); j++) { // перебираем снова эмоции 

                if (WorldEmotion != j) { // исключая линк, чтобы не создать в этом мире портал в самого себя

                    Worlds[WorldEmotion].portal.push_back({ Worlds_Names[j], Emotion[j] }); // добавляем порталы

                }
            }
        }
    }
}
