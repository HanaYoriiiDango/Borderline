#pragma once
#include "GameCore.h"

void GameCore::InitGame() { // здесь прописываю всю инициализацию

    Init.CreateWorlds(); // автоматическая инциализация всех миров и порталов

    Worlds[SADNESS].character.push_back({ "Beam1", "Полуразложившееся бревно лежит под угрюмым небом", 0 });

    Worlds[SADNESS].character[0].AddReplace(SADNESS, " (Сарказм) : Ну что, старина - бревно ? Нашел отличную компанию для беседы.Тебя тоже сюда выбросило за ненадобностью ?");
    Worlds[SADNESS].character[0].AddReplace(FEAR, " (Раздраженно): И чего молчишь? Все вокруг только и умеют, что молчать! Скажи хоть что-нибудь! ");
    Worlds[SADNESS].character[0].AddReplace(ANGER, " (С опаской): Ты... ты ведь не превратишься сейчас в кого-нибудь? В монстра?");

    Worlds[SADNESS].character.push_back({ "Beam2", "(Бревно молчит. Ветер шелестит листьями)", 1 });

    Worlds[SADNESS].character[1].AddReplace(JOY, " (С горяча пнуть бревно ботинком): [Пнуть]");
    Worlds[SADNESS].character[1].AddReplace(POWER, " (Грустно сесть рядом): Знаешь, а ведь ты идеальный собеседник. Тебя невозможно разачаровать");
    Worlds[SADNESS].character[1].AddReplace(CALM, " (Прислушиваясь к себе): Стоп. А что если это ловушка? Надо бы проверить окрестности");

    Worlds[SADNESS].character.push_back({ "Beam3", "...", 2 });

    Worlds[SADNESS].character[2].AddReplace(SADNESS, " (C горькой иронией):  Вот и поговорили. Как всегда, я один несу свою чушь в пустоту");
    Worlds[SADNESS].character[2].AddReplace(FEAR, " (Взяв себя в руки): Ладно... ладно. Сосредоточься. Нужно идти дальше.");
    Worlds[SADNESS].character[2].AddReplace(ANGER, " (Смирившись): Тишина... Иногда она лучше любых слов");

}

void GameCore::Edit() {

    string temp; // переменные для ввода
    int choice1;
    int choice2;

    for (int i = 0; i < Emotion.size(); i++) { // демострирую текущие значения всех шкал

        cout << i + 1 << ")" << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // выводим текущие эмоции игрока

    }

    cout << "Какую эмоцию хотите изменить? (номер)" << endl;

    cin >> choice1; // какую из шкал изменить

    if (choice1 > 0 && choice1 < Emotion.size()) { // проверка чтобы выбор соответствовал списку

        cout << "Какое значение установить для выбранной шкалы?" << endl;
        cin >> choice2; // новое значение для шкалы

        int num = choice1 - 1; // нивелирует тот факт что я ввожу 1 и он не получает ноль (тк в коде для демонстрации i + 1)

        Hero.emotions[num] = choice2; // Меняю значение на нужное и уведомляю об этом пользователя
        cout << "Установлено новое значение для шкалы " << Emotion_Names[num] << ": " << Hero.emotions[num] << endl;
    }
}

void GameCore::Help() { // Вывод всех команд

    Output.CommandInfo(); // вывожу список

}

void GameCore::StatusInfo() {

    Output.OutputStates(); // вывожу шкалы и состояние игрока

}

void GameCore::InitInfo() {

    Init.Info(); // инфа о всех инициализированных обьектаз

}


void GameCore::StartDialog() {

    bool start = true;

    if (!Worlds[Hero.current_loc].character.empty()) {

        while (start) {

            int choice;
            OutputSystem Nemo;

            cout << "____Поляна на окраине Мира Грусти____" << endl;
            cout << "Немо подходит к бревну. Он выглядит растерянным и усталым" << endl;

            Output.OutputStates();
            Output.OutputDialog(0); // Вывожу фразу персонажа и доступные игроку реплики

            cin >> choice; // ожидаем ответа игрока 
            if (Input.InputHandler(choice, 0)) start = true; // обрабатываем ввод
            else {
                cout << "Диалог окончен" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(1); // Вывожу фразу персонажа и доступные игроку реплики

            cin >> choice; // ожидаем ответа игрока 
            if (Input.InputHandler(choice, 1)) start = true; // обрабатываем ввод
            else {
                cout << "Диалог окончен" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(2); // Вывожу фразу персонажа и доступные игроку реплики

            cin >> choice; // ожидаем ответа игрока 
            if (Input.InputHandler(choice, 2)) start = true; // обрабатываем ввод
            else {
                cout << "Диалог окончен" << endl;
                start = false;
            }
        }
    }
    else {

        cout << "Похоже в этом одиноком мире не с кем разговаривать(" << endl;

    }
}

void GameCore::Go() {

    for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) { // код для демонстрации открытых/закрытых миров

        cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
            << (!Worlds[i].is_locked ? "Мир открыт \n" : "Мир закрыт \n") << endl;

    }

    cout << "В какой мир желаешь переместиться? \n";
    int choice;
    cin >> choice; // ожидаем ввода числового номера из ранее перечисленных миров

    if (choice > 0 || choice <= Worlds[Hero.current_loc].portal.size()) { // проверяем чтобы ввод соответствовал номерам миров

        int target_index = choice - 1;  // нивелирует тот факт что я ввожу 1 а меня перемещает в ноль (тк в коде для демонстрации i + 1) wwwwwe
        Portal_& portal = Worlds[Hero.current_loc].portal[target_index]; // записываю верный таргет


        if (portal.open && !Worlds[portal.target].is_locked) { // портал и мир в который игрок хочет переместиться должны быть открытыми 
            Hero.current_loc = portal.target;
            cout << "Ты переместился в " << Worlds_Names[Hero.current_loc] << endl;
        }
        else {
            cout << "Этот мир закрыт!\n";
        }
    }

}
