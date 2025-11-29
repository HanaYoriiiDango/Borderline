#include "systems.h"
#include <filesystem>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

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

Emotion_ TextManager::StringToEmotion(const string& emotionStr) {
    if (emotionStr == "SADNESS") return SADNESS;
    if (emotionStr == "JOY") return JOY;
    if (emotionStr == "FEAR") return FEAR;
    if (emotionStr == "POWER") return POWER;
    if (emotionStr == "CALM") return CALM;
    if (emotionStr == "ANGER") return ANGER;
    return COUNT_Emotions;
}

DialogAnswer TextManager::ParseAnswer(const json& answerJson) {
    DialogAnswer answer;
    answer.text = answerJson["text"];
    answer.emotion = StringToEmotion(answerJson["emotion"]);
    answer.sign = answerJson["sign"];
    answer.next_text_id = answerJson["next_text_id"]; 
    return answer;
}

DialogText TextManager::ParseDialogText(const json& textJson) {
    DialogText text;
    text.id = textJson["id"];
    text.text = textJson["text"];

    for (const auto& answerJson : textJson["answers"]) {
        text.answers.push_back(ParseAnswer(answerJson));
    }

    return text;
}

NPC TextManager::LoadNPCFromFile(const string& filepath) {
    NPC npc;

    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Не могу открыть: " << filepath << endl;
        return npc;
    }

    try {
        json jsonData;
        file >> jsonData;

        npc.id = jsonData["id"];
        npc.name = jsonData["name"];
        npc.world_link = StringToEmotion(jsonData["world_link"]);

        for (const auto& textJson : jsonData["texts"]) {
            npc.texts.push_back(ParseDialogText(textJson));
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка в файле " << filepath << ": " << e.what() << endl;
    }

    return npc;
}

vector<string> TextManager::FindJSONFiles(const string& folderPath) {
    vector<string> files;

    if (!fs::exists(folderPath)) return files;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            files.push_back(entry.path().filename().string());
        }
    }

    return files;
}
vector<string> TextManager::FindWorldFolders() { 
    vector<string> worlds;
    string basePath = "data/dialogs/";

    if (!fs::exists(basePath)) return worlds;

    for (const auto& entry : fs::directory_iterator(basePath)) {
        if (entry.is_directory()) {
            worlds.push_back(entry.path().filename().string());
        }
    }

    return worlds;
}

void TextManager::LoadAllNPCs() {
    auto worldFolders = FindWorldFolders();
    int totalLoaded = 0;

    for (const string& world : worldFolders) {
        string path = "data/dialogs/" + world + "/";
        auto files = FindJSONFiles(path);

        if (!files.empty()) {
            cout << world << ": " << files.size() << " NPC" << endl;
        }

        for (const string& file : files) {
            NPC npc = LoadNPCFromFile(path + file);
            if (!npc.id.empty()) {
                Characters.push_back(move(npc));
                totalLoaded++;
            }
        }
    }

    cout << "Всего загружено: " << totalLoaded << " NPC из " << worldFolders.size() << " миров" << endl;
}

vector<NPC*> TextManager::GetNPCsInWorld(Emotion_ world) {
    vector<NPC*> result;

    for (NPC& npc : Characters) {
        if (npc.world_link == world) {
            result.push_back(&npc);
        }
    }

    return result;
}

bool TextManager::HasNPCInWorld(Emotion_ world) {
    return !GetNPCsInWorld(world).empty();
}

NPC* TextManager::GetNPCByID(const string& npcID) {
    for (NPC& npc : Characters) {
        if (npc.id == npcID) {
            return &npc;
        }
    }
    return nullptr; // не найден
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

    Hero.life = false;

}

// Реализации методов GameCore
void GameCore::InitGame() {

    Init.CreateWorlds();
    Manager.LoadAllNPCs();

}

void GameCore::StartGame() {

    Collector.StartSession();

}

void GameCore::EndGame() {

    Collector.EndSession();
    Collector.SaveData();
    Hero.life = false;

}

void GameCore::Help() {

    cout << "help - список команд \n";
    cout << "info - информация о инициализированных объектах \n";
    cout << "status - информация о состоянии персонажа \n";
    cout << "go - для перемещения \n";
    cout << "start - начать диалог с персонажем (если есть с кем поболтать)\n";
    cout << "exit - завершить игровую сессию\n";

}

void GameLogicSystem::StatusInfo() {
    for (int i = 0; i < Emotion.size(); i++) {

        cout << left << setw(40) << Emotion_Names[i] << "\t" <<
            ((Hero.emotions[i] > 98 || Hero.emotions[i] < 2) ? "Disabled" : to_string(Hero.emotions[i])) << endl;

    }
}

void DialogSystem::ProcessDialog() {

    // Проверяем есть ли NPC в текущем мире
    if (!textManager.HasNPCInWorld(Worlds[Hero.current_loc].linked_emotion)) {
        cout << "Здесь не с кем поговорить." << endl;
        return;
    }

    // Получаем всех NPC в этом мире
    vector<NPC*> availableNPCs = textManager.GetNPCsInWorld(Worlds[Hero.current_loc].linked_emotion);

    // Если NPC один сразу начинаем диалог
    if (availableNPCs.size() == 1) {
        gameLogic.StatusInfo();
        RunDialog(availableNPCs[0]);
        gameLogic.StatusInfo();

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
            gameLogic.StatusInfo();
            RunDialog(availableNPCs[choice - 1]);
            gameLogic.StatusInfo();

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
            
           
            gameLogic.ChangeEmotions(selectedAnswer.emotion, selectedAnswer.sign);
            
            
            currentTextID = selectedAnswer.next_text_id;
            
            
            if (currentTextID == -1) {
                cout << "(Диалог завершён)" << endl;
                break;
            }
        } else {
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}

void GameCore::ProcessCommand() {

    cin >> temp;
    if (temp == "help" || temp == "Help") Help();
    if (temp == "status" || temp == "Status") Logic.StatusInfo();
    if (temp == "info" || temp == "Info") Init.Info();
    if (temp == "go" || temp == "Go") Logic.ProcessGo();
    if (temp == "start" || temp == "Start") Dialog.ProcessDialog();
    if (temp == "exit" || temp == "Exit") EndGame();
    if (temp == "CLEAR23") Collector.ClearStatistics();
}