#include "Init.h"

Emotion_ GameLogicSystem::GetOpposite(Emotion_ feels) { // принимает одну эмоцию а возвращает противоположную

    switch (feels) {
    case (SADNESS): return JOY;
    case (JOY): return SADNESS;
    case (FEAR): return POWER;
    case (POWER): return FEAR;
    case (ANGER): return CALM;
    case (CALM): return ANGER;

    }
}

bool GameLogicSystem::LimitCheck(int value) { // проверка на достижение лимитов шкал

    if (value <= 0 || value >= 100) return true; // если достигли вернет true
    else return false; 

}

void GameLogicSystem::HeroLocCheck() {

    for (int i = 0; i < Emotion.size(); i++) {

        Emotion_ opposite = GetOpposite((Emotion_)i);

        if (Hero.current_loc == i || Hero.current_loc == (opposite)) { // Если игрок находится в одном из закрываемых миров - перемещаем

            vector<int> available_worlds; // массив открытых миров

            for (int j = 0; j < 6; j++) { // смотрим какие миры открыты 
                if (!Worlds[j].is_locked) {
                    available_worlds.push_back(j); // записываем в массив 
                }
            }

            if (!available_worlds.empty()) { // если массив не пуст, то перемещаем в рандомный мир
                int random_index = rand() % available_worlds.size(); // это позволяет исключить перемещение в уже закрытый мир
                Hero.current_loc = available_worlds[random_index];  // меняем мир игрока на рандомный ОТКРЫТЫЙ
                cout << ">> Переход в " << Worlds_Names[Hero.current_loc] // вывжу иформацию куда игрок переместился
                    << " из-за блокировки " << Worlds_Names[i] // какие миры заблокировались
                    << " и " << Worlds_Names[opposite] << endl;
            }
            else {
                Hero.life = false;
                cout << ">> Все миры закрыты! Игра завершена.\n";
                // Завершение игры
            }
        }
        else {
            cout << ">> " << Worlds_Names[i] << " и "
                << Worlds_Names[opposite] << " закрыты!\n";
        }
    }
}

void GameLogicSystem::LockedWorlds() {

    for (int i = 0; i < Emotion.size(); i++) { // перебираю все эмоции

        // преждме чем закрыть мир мне нужна проверка на то, находится ли игрок внутри закрываемого мира
        // если да - перемещаем, если нет - не пермещаем

        HeroLocCheck(); // проверка

        if (!Worlds[i].is_locked) { //

            Worlds[i].is_locked = true; // закрываю этот мир

            Emotion_ OppositeWorld = GetOpposite(Emotion[i]); // закрываю противоположный 
            Worlds[OppositeWorld].is_locked = true;

        }
    }
}

void GameLogicSystem::ChangeGamerule() { // здесь буду менять игровые правила исходя из значений шкал 

    for (int i = 0; i < Emotion.size(); i++) {

        int OpenLimit = Hero.emotions[i];
        OpenLimit -= 2;

        if (LimitCheck(OpenLimit)) {

            LockedWorlds();

        }
    }

}

void GameLogicSystem::Transfuse(Emotion_ feels) {

    Emotion_ opposite_emotion = GetOpposite(feels); // Эмоции как переливающиеся сосуды
    Hero.emotions[opposite_emotion] = 100 - Hero.emotions[feels];

}

void GameLogicSystem::Addition(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] += dominationRate; // +rate от указанной шкалы
    Transfuse(feels);

    for (int i = 0; i < Array.size(); i++) { // перебираю позитивные 

        ArrayNum = Array[i];

        if (ArrayNum != feels) { // искл доминанта

            Hero.emotions[ArrayNum] -= passiveRate;
            Transfuse(ArrayNum);
        }
    }

}

void GameLogicSystem::Subtraction(Emotion_ feels, vector<Emotion_> Array) {

    Hero.emotions[feels] -= dominationRate; // -rate от указанной шкалы
    Transfuse(feels); // корректирует связанную шкалу по принципу переливающихся сосудов

    for (int j = 0; j < Array.size(); j++) { // перебираю позитивные 

        ArrayNum = Array[j]; // записываю значение в вспомогательную переменную

        if (ArrayNum != feels) { // искл доминанта

            Hero.emotions[ArrayNum] += passiveRate;
            Transfuse(ArrayNum);

        }
    }
}

void GameLogicSystem::ChangeEmotions(Emotion_ DominationEmotion, bool sign) { // принимает доминирующую эмоцию и знак для фикс. значений

    // 1) Разделяю эмоции на позитивные и негативные, чтобы было проще работать с парами
    for (int i = 0; i < Emotion.size(); i++) {

        if (Emotion[i] % 2 == 0) { // если делится на два - четная эмоция - позитивная

            Positive.push_back({ Emotion[i] });

        }
        else { // если нет - нечетная - негативная

            Negative.push_back({ Emotion[i] });

        }
    }

    // 2) Использую эти массивы, меняю эмоции игрока
    if (DominationEmotion % 2 == 0) { // если делится на два - четная эмоция - позитивная

        sign ? Addition(DominationEmotion, Positive) : Subtraction(DominationEmotion, Positive); // DominationEmotion + 10 / -10
    }
    else { // если нет - нечетная - негативная

        sign ? Addition(DominationEmotion, Negative) : Subtraction(DominationEmotion, Negative); // DominationEmotion + 10 / -10

    }

    // 3) Очищаю массивы, чтобы они не забивались дубликатами

    vector<Emotion_>().swap(Positive); // обычный clear не очищает capacity
    vector<Emotion_>().swap(Negative); // такой подход позволяет очистить и сам массив и выделенную память

}