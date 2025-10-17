#include "Init.h"

Emotion_ GameLogicSystem::GetOpposite(Emotion_ feels) { // ��������� ���� ������ � ���������� ���������������

    switch (feels) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return POWER;
    case (POWER): return FEAR;
    case (ANGER): return CALM;
    case (CALM): return ANGER;

    }
}

bool GameLogicSystem::LimitCheck(int value) { // �������� �� ���������� ������� ����

    if (value <= 0 || value >= 100) return true; // ���� �������� ������ true
    else return false; 

}

void GameLogicSystem::HeroLocCheck() {

    for (int i = 0; i < Emotion.size(); i++) {

        Emotion_ opposite = GetOpposite((Emotion_)i);

        if (Hero.current_loc == i || Hero.current_loc == (opposite)) { // ���� ����� ��������� � ����� �� ����������� ����� - ����������

            vector<int> available_worlds; // ������ �������� �����

            for (int j = 0; j < 6; j++) { // ������� ����� ���� ������� 
                if (!Worlds[j].is_locked) {
                    available_worlds.push_back(j); // ���������� � ������ 
                }
            }

            if (!available_worlds.empty()) { // ���� ������ �� ����, �� ���������� � ��������� ���
                int random_index = rand() % available_worlds.size(); // ��� ��������� ��������� ����������� � ��� �������� ���
                Hero.current_loc = available_worlds[random_index];  // ������ ��� ������ �� ��������� ��������
                cout << ">> ������� � " << Worlds_Names[Hero.current_loc] // ����� ��������� ���� ����� ������������
                    << " ��-�� ���������� " << Worlds_Names[i] // ����� ���� ���������������
                    << " � " << Worlds_Names[opposite] << endl;
            }
            else {
                Hero.life = false;
                cout << ">> ��� ���� �������! ���� ���������.\n";
                // ���������� ����
            }
        }
        else {
            cout << ">> " << Worlds_Names[i] << " � "
                << Worlds_Names[opposite] << " �������!\n";
        }
    }
}

void GameLogicSystem::LockedWorlds() {

    for (int i = 0; i < Emotion.size(); i++) { // ��������� ��� ������

        // ������� ��� ������� ��� ��� ����� �������� �� ��, ��������� �� ����� ������ ������������ ����
        // ���� �� - ����������, ���� ��� - �� ���������

        HeroLocCheck(); // ��������

        if (!Worlds[i].is_locked) { //

            Worlds[i].is_locked = true; // �������� ���� ���

            Emotion_ OppositeWorld = GetOpposite(Emotion[i]); // �������� ��������������� 
            Worlds[OppositeWorld].is_locked = true;

        }
    }
}

void GameLogicSystem::ChangeGamerule() { // ����� ���� ������ ������� ������� ������ �� �������� ���� 

    for (int i = 0; i < Emotion.size(); i++) {

        int OpenLimit = Hero.emotions[i];
        OpenLimit -= 2;

        if (LimitCheck(OpenLimit)) {

            LockedWorlds();

        }
    }

}

void GameLogicSystem::Transfuse(Emotion_ feels) {

    Emotion_ opposite_emotion = GetOpposite(feels); // ������ ��� �������������� ������
    Hero.emotions[opposite_emotion] = 100 - Hero.emotions[feels];

}

void GameLogicSystem::Addition(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] += dominationRate; // +rate �� ��������� �����
    Transfuse(feels);

    for (int i = 0; i < Array.size(); i++) { // ��������� ���������� 

        ArrayNum = Array[i];

        if (ArrayNum != feels) { // ���� ���������

            Hero.emotions[ArrayNum] -= passiveRate;
            Transfuse(ArrayNum);
        }
    }

}

void GameLogicSystem::Subtraction(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] -= dominationRate; // -rate �� ��������� �����
    Transfuse(feels); // ������������ ��������� ����� �� �������� �������������� �������

    for (int j = 0; j < Array.size(); j++) { // ��������� ���������� 

        ArrayNum = Array[j]; // ��������� �������� � ��������������� ����������

        if (ArrayNum != feels) { // ���� ���������

            Hero.emotions[ArrayNum] += passiveRate;
            Transfuse(ArrayNum);

        }
    }
}

void GameLogicSystem::ChangeEmotions(Emotion_ DominationEmotion, bool sign) { // ��������� ������������ ������ � ���� ��� ����. ��������

    // 1) �������� ������ �� ���������� � ����������, ����� ���� ����� �������� � ������
    for (int i = 0; i < Emotion.size(); i++) {

        if (Emotion[i] % 2 == 0) { // ���� ������� �� ��� - ������ ������ - ����������

            Positive.push_back({ Emotion[i] });

        }
        else { // ���� ��� - �������� - ����������

            Negative.push_back({ Emotion[i] });

        }
    }

    // 2) ��������� ��� �������, ����� ������ ������
    if (DominationEmotion % 2 == 0) { // ���� ������� �� ��� - ������ ������ - ����������

        sign ? Addition(DominationEmotion, Positive) : Subtraction(DominationEmotion, Positive); // DominationEmotion + 10 / -10
    }
    else { // ���� ��� - �������� - ����������

        sign ? Addition(DominationEmotion, Negative) : Subtraction(DominationEmotion, Negative); // DominationEmotion + 10 / -10

    }

    // 3) ������ �������, ����� ��� �� ���������� �����������

    vector<Emotion_>().swap(Positive); // ������� clear �� ������� capacity
    vector<Emotion_>().swap(Negative); // ����� ������ ��������� �������� � ��� ������ � ���������� ������

}