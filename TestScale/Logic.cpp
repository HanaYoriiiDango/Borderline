#include "systems.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Реализации методов GameLogicSystem
Emotion_ GameLogicSystem::GetOpposite(Emotion_ feels) { // Возвращает противоположную эмоцию
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
bool GameLogicSystem::LimitCheck(int value) { // Проверка на достижение пределов шкал

    if (value <= 2 || value >= 98) return true;
    else return false;

}

bool GameLogicSystem::HeroLocCheck() { // Проверка на флаг текущего мира 

    return Worlds[Hero.current_loc].is_locked;

}

Emotion_ GameLogicSystem::DetectedEmotion(int feels) { // Возвращает эмоцию, которая достигла предела 

    if (LimitCheck(Hero.emotions[feels])) return (Emotion_)feels;
    return COUNT_Emotions;

}

void GameLogicSystem::LockedValue(Emotion_ feels) { // Контролирует чтобы эмоции не вышли за пределы

    int value = Hero.emotions[feels];

    if (value < 0) value = 0; // проверяем, если достигли - фиксируем
    if (value > 100) value = 100;

    Hero.emotions[feels] = value; // перезаписываем

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


void GameLogicSystem::Transfuse(Emotion_ feels) { // Меняем значение пары и проверяем их на пределы

    Emotion_ opposite_emotion = GetOpposite(feels); // Ищем противоположную эмоцию
    int new_value = 100 - Hero.emotions[feels]; // Получаем новое значение противоположной шкалы 
    Hero.emotions[opposite_emotion] = new_value; // Записываем новое значение

    // проверяем на достижение пределов
    LockedValue(feels);
    LockedValue(opposite_emotion);

}

void GameLogicSystem::Addition(Emotion_ feels, vector<Emotion_> Array) { // операция увеличения шкалы

    Hero.emotions[feels] += dominationRate; // увеличиваем доминирующую
    Transfuse(feels); // меняем связанную 

    for (int i = 0; i < Array.size(); i++) { // Перебираем группу 

        ArrayNum = Array[i]; // используем вспомогательную переменную

        if (ArrayNum != feels) { // Она не должна быть доминирующей 

            Hero.emotions[ArrayNum] -= passiveRate; // уменьшаем пассивные
            Transfuse(ArrayNum); // и связанные с ними

        }
    }
}

void GameLogicSystem::Subtraction(Emotion_ feels, vector<Emotion_> Array) { // операция уменьшения шкалы

    Hero.emotions[feels] -= dominationRate; // Уменьшаем доминирующую
    Transfuse(feels); // меняем связанную

    for (int j = 0; j < Array.size(); j++) { // перебираем группу

        ArrayNum = Array[j]; // используем вспомогательную переменную

        if (ArrayNum != feels) { // она не должна быть доминирующей

            Hero.emotions[ArrayNum] += passiveRate; // увеличиваем пассивные 
            Transfuse(ArrayNum); // и связанные с ними

        }
    }
}

void GameLogicSystem::ChangeEmotions(Emotion_ DominationEmotion, bool sign) { // изменение шкал эмоций

    // 1. Предварительная очистка
    vector<Emotion_>().swap(Positive);
    vector<Emotion_>().swap(Negative);

    // 2. Перебираем эмоции на группы 
    for (int i = 0; i < Emotion.size(); i++) {

        if (Emotion[i] % 2 == 0) { // проверяем на четность

            Positive.push_back({ Emotion[i] });

        }
        else {

            Negative.push_back({ Emotion[i] });

        }
    }

    // 3. Проверяем переданную эмоцию на четность / нечетность, выбираем операцию, передаем массив
    if (DominationEmotion % 2 == 0) {

        sign ? Addition(DominationEmotion, Positive) : Subtraction(DominationEmotion, Positive);

    }
    else {

        sign ? Addition(DominationEmotion, Negative) : Subtraction(DominationEmotion, Negative);

    }

    // 4. После использования очищаем массивы
    vector<Emotion_>().swap(Positive);
    vector<Emotion_>().swap(Negative);

    ChangeGamerule(); // изменяем игровые правила

}

void GameLogicSystem::ProcessGo() { // функция перемещения игрока 

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

void GameLogicSystem::StatusInfo() { // Выводит информацию о состоянии игрока 
    for (int i = 0; i < Emotion.size(); i++) {

        cout << left << setw(40) << Emotion_Names[i] << "\t" <<
            ((Hero.emotions[i] > 98 || Hero.emotions[i] < 2) ? "Disabled" : to_string(Hero.emotions[i])) << endl;

    }
}