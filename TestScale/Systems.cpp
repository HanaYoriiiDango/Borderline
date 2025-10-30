#include "systems.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Реализации методов InitSystem 
void InitSystem::Info() {

    for (int i = 0; i < Emotion.size(); i++) {

        cout << Worlds[i].name << endl;
        cout << "Link: " << Worlds[i].linked_emotion << endl;
        cout << "PortalSize: " << Worlds[i].portal.size() << endl;

        for (int j = 0; j < Worlds[i].portal.size(); j++) {

            cout << "PortaName: " << Worlds[i].portal[j].name << endl;
            cout << "PortalTarget: " << Worlds[i].portal[j].target << endl;

        }
    }
}

void InitSystem::CreateWorlds() {

    for (int i = 0; i < Emotion.size(); i++) {

        Worlds[i].name = Worlds_Names[i];
        Worlds[i].linked_emotion = Emotion[i];

        CreatePortals(Worlds[i].linked_emotion);
    }
}

void InitSystem::CreatePortals(Emotion_ WorldEmotion) {

    for (int i = 0; i < Emotion.size(); i++) {

        if (WorldEmotion == i) {

            for (int j = 0; j < Emotion.size(); j++) {

                if (WorldEmotion != j) {

                    Worlds[WorldEmotion].portal.push_back({ Worlds_Names[j], Emotion[j] });

                }
            }
        }
    }
}

// Реализации методов NPC
void NPC::AddReplace(Emotion_ id, string t) {

    Answer.push_back({ id, t });

}

// Реализации методов GameLogicSystem
Emotion_ GameLogicSystem::GetOpposite(Emotion_ feels) {

    switch (feels) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return POWER;
    case (POWER): return FEAR;
    case (ANGER): return CALM;
    case (CALM): return ANGER;
    }

}

bool GameLogicSystem::LimitCheck(int value) {

    if (value <= 0 || value >= 100) return true;
    else return false;

}

void GameLogicSystem::HeroLocCheck() {

    for (int i = 0; i < Emotion.size(); i++) {

        Emotion_ opposite = GetOpposite((Emotion_)i);

        if (Hero.current_loc == i || Hero.current_loc == (opposite)) {

            vector<int> available_worlds;

            for (int j = 0; j < 6; j++) {

                if (!Worlds[j].is_locked) {
                    available_worlds.push_back(j);
                }

            }
            if (!available_worlds.empty()) {

                int random_index = rand() % available_worlds.size();
                Hero.current_loc = available_worlds[random_index];

                cout << ">> Переход в " << Worlds_Names[Hero.current_loc]
                    << " из-за блокировки " << Worlds_Names[i]
                    << " и " << Worlds_Names[opposite] << endl;

            }
            else {
                Hero.life = false;
                cout << ">> Все миры закрыты! Игра завершена.\n";
            }
        }
        else {
            cout << ">> " << Worlds_Names[i] << " и "
                << Worlds_Names[opposite] << " закрыты!\n";
        }
    }
}

void GameLogicSystem::LockedWorlds() {

    for (int i = 0; i < Emotion.size(); i++) {

        HeroLocCheck();

        if (!Worlds[i].is_locked) {

            Worlds[i].is_locked = true;
            Emotion_ OppositeWorld = GetOpposite(Emotion[i]);
            Worlds[OppositeWorld].is_locked = true;

        }
    }
}

void GameLogicSystem::ChangeGamerule() {

    for (int i = 0; i < Emotion.size(); i++) {

        int OpenLimit = Hero.emotions[i];
        OpenLimit -= 2;

        if (LimitCheck(OpenLimit)) {

            LockedWorlds();



        }
    }
}

void GameLogicSystem::Transfuse(Emotion_ feels) {

    Emotion_ opposite_emotion = GetOpposite(feels);
    Hero.emotions[opposite_emotion] = 100 - Hero.emotions[feels];

}

void GameLogicSystem::Addition(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] += dominationRate;
    Transfuse(feels);

    for (int i = 0; i < Array.size(); i++) {

        ArrayNum = Array[i];

        if (ArrayNum != feels) {

            Hero.emotions[ArrayNum] -= passiveRate;
            Transfuse(ArrayNum);

        }
    }
}

void GameLogicSystem::Subtraction(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] -= dominationRate;
    Transfuse(feels);

    for (int j = 0; j < Array.size(); j++) {

        ArrayNum = Array[j];

        if (ArrayNum != feels) {

            Hero.emotions[ArrayNum] += passiveRate;
            Transfuse(ArrayNum);

        }
    }
}

void GameLogicSystem::ChangeEmotions(Emotion_ DominationEmotion, bool sign) {

    for (int i = 0; i < Emotion.size(); i++) {

        if (Emotion[i] % 2 == 0) {

            Positive.push_back({ Emotion[i] });

        }
        else {

            Negative.push_back({ Emotion[i] });

        }
    }
    if (DominationEmotion % 2 == 0) {

        sign ? Addition(DominationEmotion, Positive) : Subtraction(DominationEmotion, Positive);

    }
    else {

        sign ? Addition(DominationEmotion, Negative) : Subtraction(DominationEmotion, Negative);

    }

    vector<Emotion_>().swap(Positive);
    vector<Emotion_>().swap(Negative);
}

// Реализации методов OutputSystem
void OutputSystem::OutputDialog(int npcID) {

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) {

        if (Worlds[Hero.current_loc].character[i].ID == npcID) {

            cout << Worlds[Hero.current_loc].character[i].text_NPC << endl;

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) {

                cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl;
            }
        }
    }
}

void OutputSystem::OutputStates() {

    for (int i = 0; i < Emotion.size(); i++) {

        cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl;

    }
}

void OutputSystem::CommandInfo() {

    cout << "help - список команд \n";
    cout << "edit - изменить эмоции\n";
    cout << "info - информация о инициализированных объектах \n";
    cout << "status - информация о состоянии персонажа \n";
    cout << "go - для перемещения \n";
    cout << "start - начать диалог с персонажем (если есть с кем поболтать)\n";
    cout << "exit - завершить игровую сессию\n";

}

// Реализации методов InputSystem
bool InputSystem::InputHandler(int choice, int npcID) {

    int counter = 0;
    if (choice == 0) return false;
    if (choice != 0) choice -= 1;

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) {

        if (Worlds[Hero.current_loc].character[i].ID == npcID) {

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) {

                if (choice == j) {

                    ChangeEmotions(Worlds[Hero.current_loc].character[i].Answer[j].id, true);
                    counter++;

                }
            }
        }
    }
    if (counter == 1) return true;
}

// Реализации методов StatisticsCollector
void StatisticsCollector::StartSession() {

    Session.startTime = time(0); 
    Session.ID = Session.startTime; 

    cout << "=== Начата новая игровая сессия ===" << endl;
    cout << "ID сессии: " << Session.ID << endl;

}

void StatisticsCollector::EndSession() {

    Session.endTime = time(0);
    Session.TimeMin = difftime(Session.endTime, Session.startTime) / 60.0;

    cout << "=== Игровая сессия завершена ===" << endl;
    cout << "endTime: " << Session.endTime << endl;
    cout << "TimeMin: " << Session.TimeMin << endl;

}

void StatisticsCollector::SaveData() {

    SaveStatistics.open("SaveStatistics.txt", ios::app);

    if (SaveStatistics.is_open()) {

        SaveStatistics << " Игровая сессия №: " << Session.ID << endl;
        SaveStatistics << " Start time: " << Session.startTime << endl;
        SaveStatistics << " End time: " << Session.endTime << endl;
        SaveStatistics << " End of time in minutes: " << Session.TimeMin << endl;
        
        SaveStatistics.close();

    }
    else {
        cout << "Файл не открыт или не существует" << endl;

    }
}

// Реализации методов GameCore
void GameCore::InitGame() {

    Init.CreateWorlds();

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

void GameCore::StartGame() {

    Collector.StartSession();

}

void GameCore::EndGame() {

    Collector.EndSession();
    Collector.SaveData();
    Hero.life = false;

}

void GameCore::Edit() {

    string temp;
    int choice1;
    int choice2;

    for (int i = 0; i < Emotion.size(); i++) {

        cout << i + 1 << ")" << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl;

    }

    cout << "Какую эмоцию хотите изменить? (номер)" << endl;
    cin >> choice1;

    if (choice1 > 0 && choice1 < Emotion.size()) {

        cout << "Какое значение установить для выбранной шкалы?" << endl;
        cin >> choice2;
        int num = choice1 - 1;
        Hero.emotions[num] = choice2;
        cout << "Установлено новое значение для шкалы " << Emotion_Names[num] << ": " << Hero.emotions[num] << endl;

    }
}

void GameCore::Help() {
    Output.CommandInfo();
}

void GameCore::StatusInfo() {
    Output.OutputStates();
}

void GameCore::InitInfo() {
    Init.Info();
}

void GameCore::StartDialog() {

    bool start = true;

    if (!Worlds[Hero.current_loc].character.empty()) {

        while (start) {

            int choice;

            cout << "____Поляна на окраине Мира Грусти____" << endl;
            cout << "Немо подходит к бревну. Он выглядит растерянным и усталым" << endl;

            Output.OutputStates();
            Output.OutputDialog(0);
            cin >> choice;
            if (Input.InputHandler(choice, 0)) start = true;
            else {
                cout << "Диалог окончен" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(1);
            cin >> choice;
            if (Input.InputHandler(choice, 1)) start = true;
            else {
                cout << "Диалог окончен" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(2);
            cin >> choice;
            if (Input.InputHandler(choice, 2)) start = true;
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

    for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

        cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
        << (!Worlds[i].is_locked ? "Мир открыт \n" : "Мир закрыт \n") << endl;

    }

    cout << "В какой мир желаешь переместиться? \n";
    int choice;

    cin >> choice;

    if (choice > 0 || choice <= Worlds[Hero.current_loc].portal.size()) {

        int target_index = choice - 1;
        Portal_& portal = Worlds[Hero.current_loc].portal[target_index];

        if (portal.open && !Worlds[portal.target].is_locked) {

            Hero.current_loc = portal.target;
            cout << "Ты переместился в " << Worlds_Names[Hero.current_loc] << endl;

        }
        else {
            cout << "Этот мир закрыт!\n";
        }
    }
}
