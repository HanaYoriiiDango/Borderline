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

// Реализации методов текстового менеджера 
// Загрузка JSON файла
bool TextManager::DialogLoader(const string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return false;
    }

    try {
        file >> DialogData;  // ← ВСЁ! Всего одна строка!
        cout << "Диалоги загружены: " << filename << endl;
        return true;
    }
    catch (const exception& e) {
        cout << "Ошибка загрузки JSON: " << e.what() << endl;
        return false;
    }
}

// Получение текста NPC
string TextManager::GetNPCtext(const string& npcID, int textID) {
    try {
        // Автоматические проверки и преобразования
        return DialogData["npcs"][npcID]["texts"][textID]["text"];
    }
    catch (const exception& e) {
        return "Текст не найден";
    }
}

// Количество текстов у NPC
int TextManager::GetNPCcount(const string& npcID) {
    try {
        return DialogData["npcs"][npcID]["texts"].size();
    }
    catch (...) {
        return 0;
    }
}

// Получение ответов
vector<string> TextManager::GetAnswers(const string& npcID, int textID) {
    vector<string> answers;

    try {
        // Автоматически конвертирует JSON array в vector<string>
        auto jsonAnswers = DialogData["npcs"][npcID]["texts"][textID]["answers"];
        for (const auto& answer : jsonAnswers) {
            answers.push_back(answer["text"]);
        }
    }
    catch (...) {
        // Просто возвращаем пустой вектор в случае ошибки
    }

    return answers;
}

// Реализации методов NPC
void NPC::AddReplace(int textID, Emotion_ id, bool sign, string t) {

    text_NPC[textID].Answer.push_back({ id, sign, t });

}

void NPC::AddtextNPC(int id, string t) {

    text_NPC.push_back({ id, t });

}

void InitSystem::Dialogues() {

    if (DialogManager.DialogLoader("data/dialogs.json")) {

        cout << "Загрузка диалогов прошла успешно!" << endl;

    }

    /* Worlds[SADNESS].character.emplace_back();
     Worlds[SADNESS].character[0].name = "Beam";
     Worlds[SADNESS].character[0].ID = 0;

     Worlds[SADNESS].character[0].AddtextNPC( 0, "Полуразложившееся бревно лежит под угрюмым небом");
     Worlds[SADNESS].character[0].AddtextNPC( 1, "(Бревно молчит. Ветер шелестит листьями)");
     Worlds[SADNESS].character[0].AddtextNPC( 2, "От бревна откалывается щепка");
     Worlds[SADNESS].character[0].AddtextNPC( 3, "...");

     Worlds[SADNESS].character[0].AddReplace(0, SADNESS, true, " (Сарказм) : Ну что, старина - бревно ? Нашел отличную компанию для беседы.Тебя тоже сюда выбросило за ненадобностью ?");
     Worlds[SADNESS].character[0].AddReplace(0, ANGER, true, " (Раздраженно): И чего молчишь? Все вокруг только и умеют, что молчать! Скажи хоть что-нибудь! ");
     Worlds[SADNESS].character[0].AddReplace(0, FEAR, true, " (С опаской): Ты... ты ведь не превратишься сейчас в кого-нибудь? В монстра?");

     Worlds[SADNESS].character[0].AddReplace(1, ANGER, true, " (С горяча пнуть бревно ботинком): [Пнуть]");
     Worlds[SADNESS].character[0].AddReplace(1, ANGER, false, " (Грустно сесть рядом): Знаешь, а ведь ты идеальный собеседник. Тебя невозможно разачаровать");
     Worlds[SADNESS].character[0].AddReplace(1, FEAR, true," (Прислушиваясь к себе): Стоп. А что если это ловушка? Надо бы проверить окрестности");

     Worlds[SADNESS].character[0].AddReplace(2, FEAR, true," (В ужасе): Ой... Прости... Я не хотел... Я не хотел ломать...");
     Worlds[SADNESS].character[0].AddReplace(2, ANGER, true, " (С новым приливом ярости): Да сгнивай ты тут, кому ты нужен!");
     Worlds[SADNESS].character[0].AddReplace(2, FEAR, false," (С облегчением): Фух... Кажется, ничего страшного.Просто дерево.");

     Worlds[SADNESS].character[0].AddReplace(3, SADNESS, true, " (C горькой иронией):  Вот и поговорили. Как всегда, я один несу свою чушь в пустоту");
     Worlds[SADNESS].character[0].AddReplace(3, FEAR, false, " (Взяв себя в руки): Ладно... ладно. Сосредоточься. Нужно идти дальше.");
     Worlds[SADNESS].character[0].AddReplace(3, CALM, false, " (Смирившись): Тишина... Иногда она лучше любых слов");*/

}

// Реализации методов GameLogicSystem
Emotion_ GameLogicSystem::GetOpposite(Emotion_ feels) {
    switch (feels) {
    case SADNESS: return JOY;
    case JOY: return SADNESS;
    case FEAR: return POWER;
    case POWER: return FEAR;
    case ANGER: return CALM;
    case CALM: return ANGER;
    default: cout << "ERROR: Unknown emotion in GetOpposite: " << feels << endl;
    }
}
bool GameLogicSystem::LimitCheck(int value) {

    if (value <= 2 || value >= 98) return true;
    else return false;

}

bool GameLogicSystem::HeroLocCheck() {

    return Worlds[Hero.current_loc].is_locked;

}

Emotion_ GameLogicSystem::DetectedEmotion(int feels) {

    if (LimitCheck(Hero.emotions[feels])) return (Emotion_)feels;
    return COUNT_Emotions;

}

void GameLogicSystem::LockedWorlds() { // Закрывает миры 

    for (int i = 0; i < Emotion.size(); i++) { // перебирает все эмоции

        Emotion_ feels = DetectedEmotion(i); // смотрит достигли ли они предела, если да - return emotion
        if (feels == COUNT_Emotions) continue; // если таких эмоций нет, то пропускаем иттерацию

        if (!Worlds[feels].is_locked) {

            Worlds[feels].is_locked = true;
            Emotion_ OppositeWorld = GetOpposite(Emotion[feels]);
            Worlds[OppositeWorld].is_locked = true;
            cout << "Мир " << Worlds[feels].name << " и " << Worlds[OppositeWorld].name << " закрыты!" << endl;
            cout << Emotion_Names[feels] << " и " << Emotion_Names[OppositeWorld] << " достигли своих пределов!" << endl;

        }
    }
}

void GameLogicSystem::UnlockedWorlds() {

    for (int i = 0; i < Emotion.size(); i++) { // перебирает все эмоции

        if (Worlds[i].is_locked) {

            Worlds[i].is_locked = false;
            Emotion_ OppositeWorld = GetOpposite(Emotion[i]);
            Worlds[OppositeWorld].is_locked = false;
            cout << "Мир " << Worlds[i].name << " и " << Worlds[OppositeWorld].name << " открыты!" << endl;
            cout << Emotion_Names[i] << " и " << Emotion_Names[OppositeWorld] << " восстановились!" << endl;

        }
    }
}

void GameLogicSystem::LockedValue(Emotion_ feels) {

    int value = Hero.emotions[feels];

    if (value < 0) value = 0;
    if (value > 100) value = 100;

    Hero.emotions[feels] = value;

}

void GameLogicSystem::MovingPlayer() {
    vector<int> available_worlds;

    // Собираем все открытые миры
    for (int j = 0; j < Emotion.size(); j++) {
        if (!Worlds[j].is_locked) {
            available_worlds.push_back(j);
        }
    }

    if (!available_worlds.empty()) {
        int random_index = rand() % available_worlds.size();
        Hero.current_loc = available_worlds[random_index];
        cout << ">> Переход в " << Worlds_Names[Hero.current_loc] << endl;

        vector<int>().swap(available_worlds);

    }
    else {
        Hero.life = false;
        vector<int>().swap(available_worlds);

        cout << ">> Все миры закрыты! Игра завершена.\n";
    }
}

void GameLogicSystem::ChangeGamerule() {

    // ПРОПУСКАЕМ УЖЕ ОБРАБОТАННЫЕ ПАРЫ МИРОВ
    bool processedPairs[COUNT_Emotions] = { false };

    // Сначала проверяем какие миры нужно ЗАКРЫТЬ
    for (int i = 0; i < Emotion.size(); i++) {
        if (processedPairs[i]) continue; // уже обработали эту пару

        if (LimitCheck(Hero.emotions[i])) {
            Emotion_ feels = (Emotion_)i;
            Emotion_ OppositeWorld = GetOpposite(feels);

            if (feels >= 0 && feels < COUNT_Emotions &&
                OppositeWorld >= 0 && OppositeWorld < COUNT_Emotions) {

                // Закрываем оба мира и помечаем пару как обработанную
                if (!Worlds[feels].is_locked || !Worlds[OppositeWorld].is_locked) {
                    Worlds[feels].is_locked = true;
                    Worlds[OppositeWorld].is_locked = true;
                    processedPairs[feels] = true;
                    processedPairs[OppositeWorld] = true;
                    cout << "Закрыты: " << Worlds[feels].name << " и " << Worlds[OppositeWorld].name << endl;
                }
            }
        }
    }

    // Сбрасываем флаги для открытия
    bool processedPairsOpen[COUNT_Emotions] = { false };

    // Затем проверяем какие миры нужно ОТКРЫТЬ
    for (int i = 0; i < Emotion.size(); i++) {
        if (processedPairsOpen[i]) continue; // ✅ уже обработали эту пару

        if (Hero.emotions[i] > 10 && Hero.emotions[i] < 90) {
            Emotion_ OppositeWorld = GetOpposite((Emotion_)i);

            if (i >= 0 && i < COUNT_Emotions &&
                OppositeWorld >= 0 && OppositeWorld < COUNT_Emotions) {

                // Открываем оба мира и помечаем пару как обработанную
                if (Worlds[i].is_locked || Worlds[OppositeWorld].is_locked) {
                    Worlds[i].is_locked = false;
                    Worlds[OppositeWorld].is_locked = false;
                    processedPairsOpen[i] = true;
                    processedPairsOpen[OppositeWorld] = true;
                    cout << "Открыты: " << Worlds[i].name << " и " << Worlds[OppositeWorld].name << endl;
                }
            }
        }
    }

    // Проверка игрока
    if (Worlds[Hero.current_loc].is_locked) {
        cout << "Игрок был в закрытом мире: " << Worlds_Names[Hero.current_loc] << endl;
        MovingPlayer();
    }
}


void GameLogicSystem::Transfuse(Emotion_ feels) {

    Emotion_ opposite_emotion = GetOpposite(feels);
    int new_value = 100 - Hero.emotions[feels];
    Hero.emotions[opposite_emotion] = new_value;
    LockedValue(feels);
    LockedValue(opposite_emotion);

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

    ChangeGamerule(); // изменяем игровые правила

}

void GameLogicSystem::ProcessGo() {

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
            statsCollector->Session.AllVisitCount++;

            switch (Hero.current_loc) {
            case SADNESS: statsCollector->Session.worldVisitSad++; break;
            case JOY: statsCollector->Session.worldVisitJoy++; break;
            case POWER: statsCollector->Session.worldVisitPower++; break;
            case FEAR: statsCollector->Session.worldVisitFear++; break;
            case CALM: statsCollector->Session.worldVisitCalm++; break;
            case ANGER: statsCollector->Session.worldVisitAnger++; break;
            }

            cout << "Ты переместился в " << Worlds_Names[Hero.current_loc] << endl;

        }
        else {
            cout << "Этот мир закрыт!\n";
        }
    }
}

// Реализации методов OutputSystem 
void OutputSystem::OutputDialog(int npcID, int textID) {

    for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) {

        if (Worlds[Hero.current_loc].character[i].ID == npcID) {

            cout << Worlds[Hero.current_loc].character[i].text_NPC[textID].text << endl << endl;

            for (int j = 0; j < Worlds[Hero.current_loc].character[i].text_NPC[textID].Answer.size(); j++) {

                cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].text_NPC[textID].Answer[j].text << endl;
            }
        }
    }
}

void OutputSystem::OutputStates() {

    for (int i = 0; i < Emotion.size(); i++) {

        cout << left << setw(20) << Emotion_Names[i] << "\t" <<
            ((Hero.emotions[i] > 98 || Hero.emotions[i] < 2) ? "Disabled" : to_string(Hero.emotions[i])) << endl;

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
void InputSystem::InputHandler(int choice, int npcID, int textID) {

    int actualChoice = choice - 1;

    Emotion_ selectedEmotion = COUNT_Emotions;
    bool flag;
    int originalLocation = Hero.current_loc;

    for (int i = 0; i < Worlds[originalLocation].character.size(); i++) {
        if (Worlds[originalLocation].character[i].ID == npcID) {
            for (int j = 0; j < Worlds[originalLocation].character[i].text_NPC[textID].Answer.size(); j++) {
                if (actualChoice == j) {
                    selectedEmotion = Worlds[originalLocation].character[i].text_NPC[textID].Answer[j].id;
                    flag = Worlds[originalLocation].character[i].text_NPC[textID].Answer[j].sign;
                    break;
                }
            }
            break;
        }
    }

    if (selectedEmotion != COUNT_Emotions) {
        ChangeEmotions(selectedEmotion, flag);
        statsCollector->Session.counterChoices++;
    }
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

        SaveStatistics << "_________________________________________________ " << endl;
        SaveStatistics << " Игровая сессия №: " << Session.ID << endl;
        SaveStatistics << " Start time: " << Session.startTime << endl;

        SaveStatistics << "Visit Sadness: " << Session.worldVisitSad << endl;
        SaveStatistics << "Visit Joy: " << Session.worldVisitJoy << endl;
        SaveStatistics << "Visit Power: " << Session.worldVisitPower << endl;
        SaveStatistics << "Visit Anger: " << Session.worldVisitAnger << endl;
        SaveStatistics << "Visit Fear: " << Session.worldVisitFear << endl;
        SaveStatistics << "Visit Calm:" << Session.worldVisitCalm << endl;
        SaveStatistics << "Всего перемещений по мирам: " << Session.AllVisitCount << endl;

        SaveStatistics << "выбрано ответных реплик: " << Session.counterChoices << endl;

        SaveStatistics << " End time: " << Session.endTime << endl;
        SaveStatistics << " End of time in minutes: " << Session.TimeMin << endl;
        SaveStatistics << "_________________________________________________ " << endl;

        SaveStatistics.close();

    }
    else {
        cout << "Файл не открыт или не существует" << endl;

    }
}

void StatisticsCollector::ClearStatistics() {

    SaveStatistics.open("SaveStatistics.txt", ios::trunc);

    if (SaveStatistics.is_open()) {
        SaveStatistics << "Статистика очищена " << "\n";
        SaveStatistics << "Игровая сессия №: " << Session.ID << "\n";
        SaveStatistics.close();
        cout << "✓ Statistics cleared!\n";

    }
}

// Реализации методов GameCore
void GameCore::InitGame() {

    Init.CreateWorlds();
    Init.Dialogues();

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

    cout << "Номер эмоции которую хотите изменить?" << endl;
    cin >> choice1;

    if (choice1 > 0 && choice1 < Emotion.size()) {

        cout << "Какое значение установить для выбранной шкалы? (изменит сразу всю пару на указанное значение)" << endl;
        cin >> choice2;
        int num = choice1 - 1;

        Emotion_ Opposite_num = Logic.GetOpposite((Emotion_)num);
        Hero.emotions[num] = choice2;
        Hero.emotions[Opposite_num] = choice2;
        cout << "Установлено новое значение для шкал: " << Emotion_Names[num] << ": " << Hero.emotions[num]
            << " и " << Emotion_Names[Opposite_num] << ": " << Hero.emotions[Opposite_num] << endl;
        Logic.ChangeGamerule();
    }
    else {
        cout << "Выбор неккоректный, пиши команду заново" << endl;

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

int GameCore::DialogList(int npcID, int textID, int action) {

    int choice;

    cout << endl;

    Output.OutputStates();
    cout << endl;

    Output.OutputDialog(npcID, textID);

    cin >> choice;
    Input.InputHandler(choice, npcID, textID);

    if (action == choice) return action;

}

void GameCore::ShowDialog(const string& npcId, int textId) {  

    TextManager& dialogManager = Init.GetDialogManager();

    string npcText = dialogManager.GetNPCtext(npcId, textId);
    cout << "Здесь имя челика" << npcText << endl;

    vector<string> answers = dialogManager.GetAnswers(npcId, textId);

    for (int i = 0; i < answers.size(); i++) {
        std::cout << (i + 1) << ") " << answers[i] << std::endl;
    }
    
}

void GameCore::ProcessDialog() {

    if (Hero.current_loc == SADNESS) {

        ShowDialog("sadness_log", 0);

    }
}

void GameCore::Go() {

    Logic.ProcessGo();

}

void GameCore::ProcessClear() {

    Collector.ClearStatistics();

}

void GameCore::ProcessCommand() {

    cin >> temp;
    if (temp == "edit" || temp == "Edit") Edit();
    if (temp == "help" || temp == "Help") Help();
    if (temp == "status" || temp == "Status") StatusInfo();
    if (temp == "info" || temp == "Info") InitInfo();
    if (temp == "go" || temp == "Go") Go();
    if (temp == "start" || temp == "Start") ProcessDialog();
    if (temp == "exit" || temp == "Exit") EndGame();
    if (temp == "CLEAR23") ProcessClear();
}