#include "systems.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ���������� ������� InitSystem
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

// ���������� ������� NPC
void NPC::AddReplace(Emotion_ id, string t) {

    Answer.push_back({ id, t });

}

// ���������� ������� GameLogicSystem
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

                cout << ">> ������� � " << Worlds_Names[Hero.current_loc]
                    << " ��-�� ���������� " << Worlds_Names[i]
                    << " � " << Worlds_Names[opposite] << endl;

            }
            else {
                Hero.life = false;
                cout << ">> ��� ���� �������! ���� ���������.\n";
            }
        }
        else {
            cout << ">> " << Worlds_Names[i] << " � "
                << Worlds_Names[opposite] << " �������!\n";
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

// ���������� ������� OutputSystem
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

    cout << "help - ������ ������ \n";
    cout << "edit - �������� ������\n";
    cout << "info - ���������� � ������������������ �������� \n";
    cout << "status - ���������� � ��������� ��������� \n";
    cout << "go - ��� ����������� \n";
    cout << "start - ������ ������ � ���������� (���� ���� � ��� ���������)\n";
    cout << "exit - ��������� ������� ������\n";

}

// ���������� ������� InputSystem
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

// ���������� ������� StatisticsCollector
void StatisticsCollector::StartSession() {

    Session.startTime = time(0); 
    Session.ID = Session.startTime; 

    cout << "=== ������ ����� ������� ������ ===" << endl;
    cout << "ID ������: " << Session.ID << endl;

}

void StatisticsCollector::EndSession() {

    Session.endTime = time(0);
    Session.TimeMin = difftime(Session.endTime, Session.startTime) / 60.0;

    cout << "=== ������� ������ ��������� ===" << endl;
    cout << "endTime: " << Session.endTime << endl;
    cout << "TimeMin: " << Session.TimeMin << endl;

}

void StatisticsCollector::SaveData() {

    SaveStatistics.open("SaveStatistics.txt", ios::app);

    if (SaveStatistics.is_open()) {

        SaveStatistics << " ������� ������ �: " << Session.ID << endl;
        SaveStatistics << " Start time: " << Session.startTime << endl;
        SaveStatistics << " End time: " << Session.endTime << endl;
        SaveStatistics << " End of time in minutes: " << Session.TimeMin << endl;
        
        SaveStatistics.close();

    }
    else {
        cout << "���� �� ������ ��� �� ����������" << endl;

    }
}

// ���������� ������� GameCore
void GameCore::InitGame() {

    Init.CreateWorlds();

    Worlds[SADNESS].character.push_back({ "Beam1", "����������������� ������ ����� ��� ������� �����", 0 });
    Worlds[SADNESS].character[0].AddReplace(SADNESS, " (�������) : �� ���, ������� - ������ ? ����� �������� �������� ��� ������.���� ���� ���� ��������� �� ������������� ?");
    Worlds[SADNESS].character[0].AddReplace(FEAR, " (�����������): � ���� �������? ��� ������ ������ � �����, ��� �������! ����� ���� ���-������! ");
    Worlds[SADNESS].character[0].AddReplace(ANGER, " (� �������): ��... �� ���� �� ������������ ������ � ����-������? � �������?");
    Worlds[SADNESS].character.push_back({ "Beam2", "(������ ������. ����� �������� ��������)", 1 });
    Worlds[SADNESS].character[1].AddReplace(JOY, " (� ������ ����� ������ ��������): [�����]");
    Worlds[SADNESS].character[1].AddReplace(POWER, " (������� ����� �����): ������, � ���� �� ��������� ����������. ���� ���������� ������������");
    Worlds[SADNESS].character[1].AddReplace(CALM, " (������������� � ����): ����. � ��� ���� ��� �������? ���� �� ��������� �����������");
    Worlds[SADNESS].character.push_back({ "Beam3", "...", 2 });
    Worlds[SADNESS].character[2].AddReplace(SADNESS, " (C ������� �������):  ��� � ����������. ��� ������, � ���� ���� ���� ���� � �������");
    Worlds[SADNESS].character[2].AddReplace(FEAR, " (���� ���� � ����): �����... �����. �������������. ����� ���� ������.");
    Worlds[SADNESS].character[2].AddReplace(ANGER, " (����������): ������... ������ ��� ����� ����� ����");
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

    cout << "����� ������ ������ ��������? (�����)" << endl;
    cin >> choice1;

    if (choice1 > 0 && choice1 < Emotion.size()) {

        cout << "����� �������� ���������� ��� ��������� �����?" << endl;
        cin >> choice2;
        int num = choice1 - 1;
        Hero.emotions[num] = choice2;
        cout << "����������� ����� �������� ��� ����� " << Emotion_Names[num] << ": " << Hero.emotions[num] << endl;

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

            cout << "____������ �� ������� ���� ������____" << endl;
            cout << "���� �������� � ������. �� �������� ����������� � �������" << endl;

            Output.OutputStates();
            Output.OutputDialog(0);
            cin >> choice;
            if (Input.InputHandler(choice, 0)) start = true;
            else {
                cout << "������ �������" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(1);
            cin >> choice;
            if (Input.InputHandler(choice, 1)) start = true;
            else {
                cout << "������ �������" << endl;
                start = false;
            }

            Output.OutputStates();
            Output.OutputDialog(2);
            cin >> choice;
            if (Input.InputHandler(choice, 2)) start = true;
            else {
                cout << "������ �������" << endl;
                start = false;
            }
        }
    }
    else {
        cout << "������ � ���� �������� ���� �� � ��� �������������(" << endl;
    }
}

void GameCore::Go() {

    for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

        cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
        << (!Worlds[i].is_locked ? "��� ������ \n" : "��� ������ \n") << endl;

    }

    cout << "� ����� ��� ������� �������������? \n";
    int choice;

    cin >> choice;

    if (choice > 0 || choice <= Worlds[Hero.current_loc].portal.size()) {

        int target_index = choice - 1;
        Portal_& portal = Worlds[Hero.current_loc].portal[target_index];

        if (portal.open && !Worlds[portal.target].is_locked) {

            Hero.current_loc = portal.target;
            cout << "�� ������������ � " << Worlds_Names[Hero.current_loc] << endl;

        }
        else {
            cout << "���� ��� ������!\n";
        }
    }
}
