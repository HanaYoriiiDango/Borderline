#include "systems.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

//Реализация методов TextManager
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