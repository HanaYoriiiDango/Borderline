#include "systems.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

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

    vector<Emotion_>().swap(Positive);
    vector<Emotion_>().swap(Negative);

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
            Collector.session.AllVisitCount++;
            Collector.RecordVisit();

            

            cout << "Ты переместился в " << Worlds_Names[Hero.current_loc] << endl;

        }
        else {
            cout << "Этот мир закрыт!\n";
        }
    }
}

void GameLogicSystem::StatusInfo() {
    for (int i = 0; i < Emotion.size(); i++) {

        cout << left << setw(40) << Emotion_Names[i] << "\t" <<
            ((Hero.emotions[i] > 98 || Hero.emotions[i] < 2) ? "Disabled" : to_string(Hero.emotions[i])) << endl;

    }
}