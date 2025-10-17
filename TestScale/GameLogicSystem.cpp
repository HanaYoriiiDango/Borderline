class GameLogicSystem {
private:
    Emotion_ ArrayNum;
    int dominationRate = 10; // переменные для изменения доминантной/пассивной эмоции gц
    int passiveRate = 5;

public:
    vector<Emotion_> Positive;
    vector<Emotion_> Negative;

    Emotion_ GetOpposite(Emotion_ feels) { // принимает одну эмоцию а возвращает противоположную

        switch (feels) {
        case (SADNESS): return JOY;
        case (JOY): return SADNESS;
        case (FEAR): return POWER;
        case (POWER): return FEAR;
        case (ANGER): return CALM;
        case (CALM): return ANGER;

        }
    }

    bool LimitCheck(int value) {

        if (value <= 0 || value >= 100) return true;
        else return false;

    }

    bool Stabilization() { // принудительно устанавливает все значения шкал на 50

        int count = 0;

        for (int i = 0; i < Emotion.size(); i++) {

            Hero.emotions[i] = 50;
            count++;

        }
        if (count == 6) return true;
        else false;
    }

    bool FindDominant(Emotion_ feels, int Value) { // проверяет конкретнкую шкалу на конкретное значение
        // а также что указаная шкала самая большая из всех перебираемых r

        bool findTrue = false; // флаг для потвеждения что все условия true 

        for (int i = 0; i < COUNT_Emotions; i++) { // перебираю эмоции

            if (Hero.emotions[feels] > Value) { // проверяю указанную шкалу со значением
                if (i != feels && Hero.emotions[feels] > Hero.emotions[i]) findTrue = true;
                // текущая шкала самая большая из всех перебираемых
                // почему второе условие такое? Потому что оно позволяет исключать из списка проверку шкалы
                // которая уже является "доминантной", тобиш она >= Value
                // Поэтому я буду сранивать указанную шкалу только с остальными, но не с самой же
            }
        }

        if (findTrue) return true; // если флаг поменялся то возвращает true
        else false;
    }

    bool CheckScope(int MinValue, int MaxValue) { // Проверяет все эмоции игрока в пределах указанного интервала

        int counterTrue = 0; // счетчик баллов 

        for (int i = 0; i < COUNT_Emotions; i++) { // перебираю все эмоции

            int EmotionValue = Hero.emotions[i]; // записываю эмоцию во временную переменную

            if (EmotionValue <= MinValue || EmotionValue >= MaxValue) counterTrue++; // +1 балл только если шкала находится в диапозоне от 40 до 60

        }

        if (counterTrue == 6) return true; // вернет true, только если программа посчитает 6 баллов
        else return false; // иначе ничего не меняется

    }

    bool IsCheckAllLimit(int MinLimit, int MaxLimit) { // Проверяет все эмоции на достижение указанных лимитов

        bool confirm = false;

        for (int i = 0; i < COUNT_Emotions; i++) { // перебеираю эмоции

            int EmotionValue = Hero.emotions[i]; // записываю эмоцию во временную переменную

            if (EmotionValue <= MinLimit || EmotionValue >= MaxLimit) confirm = true;
            // если хоть одна эмоция достигла заданного предела - true

        }

        if (confirm) return true; // если пересение за заданный предел подтвержденно - возвращаем true 
        else return false;
    }

    int ReturnWorldsLocked() { // возвращает количество закрытых миров

        int counterLocked = 0; // счетчик

        for (int i = 0; i < COUNT_Emotions; i++) { // перебираю эмоции

            if (Worlds[i].is_locked) { // проверка закрытость

                counterLocked++; // считаю каждый закрытый мир

            }
        }

        return counterLocked; // возвращаю количество закрытых миров

    }

    bool IsAllWorldsOpen() { // Проверяет все ли миры открыты, если да - true

        int count = 0; // счетчик

        for (int i = 0; i < COUNT_Emotions; i++) { // перебираю миры

            if (!Worlds[i].is_locked) count++; // +1 в счетчик если мир открыт

        }

        if (count == 6) return true;// если все 6 мировы открыты - вернет true
        else return false;

    }

    bool TriggerBreaking() {

        int count = 0;

        if (Hero.states == Breaking) { // если игрок в откате то

            int random_index; // переменная для рандомной смены значения шкалы

            for (int i = 0; i < Emotion.size(); i++) { // перебираю 

                random_index = rand() % 31 - 15; // шкалы колеблются oт 15 и до -15
                Hero.emotions[i] += random_index; // записываем рандомные значения в массив эмоций игрока
                count++;
            }

        }
        if (count == 6) return true; // счетчик набирает 6 баллов - true
        else return false;
    }

    States_ TriggerStates(States_ states) { // здесь я буду проверять все условия для каждого состояния

        //States_ OldStates = Hero.states;
        States_ triggerID = Stability;

        if (states == Stability) { //____________СТАБИЛЬНОСТЬ__________________________
            // здесь все возможные триггеры для выхода со стабильного состояния

            if (FindDominant(FEAR, 70)) triggerID = Anxiety; // проверка на тревогу
            // по условию : состояние тревоги наступает если у игрока страх > 70 
            // И при этом это самая большая шкала из всех

            //if (FindDominant(SADNESS, 70)) triggerID = Depression; // проверка на депрессию
            // по условию : состояние депрессии наступает если у игрока грусть > 70 
            // И при этом это самая большая шкала из всех

            //if (FindDominant(ANGER, 70)) triggerID = Rage; // проверка на раздражение
            // по условию : состояние раздражения наступает если у игрока гнев > 70 
            // И при этом это самая большая шкала из всех

            //if (ReturnWorldsLocked() == 4) triggerID = Apathy;// проверка на апатию
            // по условию: состояние апатии наступает если у игрока заблокирован доступ к четырем мирам  

            //if (ReturnWorldsLocked() == 2) triggerID = Crisis;// проверка на кризис
            // по условию: состояние кризиса наступает если у игрока заблокирован доступ к двум мирам  

        }

        if (states == Anxiety) { // Проверка на усталость вследствие тревоги

            if (Hero.emotions[FEAR] < 50) triggerID = Weariness;

        }

        if (states == Depression) {  // Проверка на усталость вследствие депрессии

            //if (Hero.emotions[JOY] > 50) triggerID = Weariness;

        }

        if (states == Rage) {// Проверка на усталость вследствие раздражения

            //if (Hero.emotions[CALM] > 50) triggerID = Weariness;

        }

        if (states == Breaking) { //__________ОТКАТ_________________________
            // 1 - словить просто усталость, все шкалы должны быть в пределах 30 и 70
            //if (CheckScope(30, 70)) triggerID = Weariness; // проверка на усталость

            // 2 - словить просто апатию, если хотя бы одна из шкал дошла до предела
            //if (IsCheckAllLimit(0, 100)) triggerID = Apathy; // проверка на апатию
        }

        if (states == Apathy) { //__________АПАТИЯ_________________________

            // проверяю всу миры на открытость
            //if (IsAllWorldsOpen()) triggerID = Weariness; // если все миры открыты выходим из апатии в усталость

        }

        if (states == Weariness) { //__________УСТАЛОСТЬ_________________________

            //if (CheckScope(40, 60)) triggerID = Stability; // проверка на стабильный диапозон значений
            // если CheckScope вернет true выходим из усталости в стабильность
        }

        if (states == Crisis) { //_______________КРИЗИС__________________________

            //if (CheckScope(40, 60)) triggerID = Stability; // проверка на стабильный диапозон значений
            // если CheckScope вернет true выходим из кризиса в стабильность
        }

        //if (triggerID != OldStates) return triggerID;
        return triggerID;
    }

    bool StatesRegulator() { // регулирует обновление состояний, проверяя триггеры при текущем состоянии игрока

        States_ old_states = Hero.states; // переменная хранит прошлое состояние
        States_ new_states = TriggerStates(Hero.states); // переменная для нового состояния
        Hero.states = new_states; // записываем новое состояние игроку

        if (Hero.states != old_states) return true; // если состояние обновилось, то true
        else false;

        //vector<is_function<void ()>> Trigger; // лол оказывается можно создать массив из функций

    }

    void EffectStates() { // Реализует все эффекты от состояний

        if (StatesRegulator()) { // Если состояние изменилось, применяем эффект состояния

            //___________________________________ТРЕВОГА_____________________________________________________

            if (Hero.states == Anxiety) {


            }

            //___________________________________ДЕПРЕССИЯ_____________________________________________________

            if (Hero.states == Depression) {


            }

            //___________________________________РАЗДРАЖЕНИЕ_____________________________________________________

            if (Hero.states == Rage) {

            }

            //___________________________________ЛОМКА (ОТКАТ)_____________________________________________________

            // Механика отката: 
            // если игрок получает откат, то шкалы должны хаотично изменяться каждые 20 секунд
            // чтобы это предотвратить, игрок должен гасить подобные всплески с помощью быстрых QTE
            // в консольной же версии я заменю QTE обычным примером 2 + 2 = 4
            // если игрок по какой-то неведомой причине отвечате не 4, а 65 - то этому умнику все шкалы рандомлю на +-15
            // если челик ответит 4, то шкалы останутся в прежних значениях
            // Также поскольку в консольной версии таймер - это дичь полная, я буду хаотично менять эмоции лишь один раз

            if (Hero.states == Breaking) {


            }
            //___________________________________АПАТИЯ________________________________________________________

            if (Hero.states == Apathy) {


            }
            //___________________________________УСТАЛОСТЬ_____________________________________________________

            if (Hero.states == Weariness) {


            }

            //___________________________________КРИЗИС_____________________________________________________

            if (Hero.states == Crisis) {




            }
        }
    }

    void HeroLocCheck() {

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

    void LockedWorlds() {

        for (int i = 0; i < Emotion.size(); i++) { // перебираю все эмоции

            // преждме чем закрыть мир мне нужна проверка на то, находится ли игрок внутри закрываемого мира
            // если да - перемещаем, если нет - не пермещаем

            HeroLocCheck();

            if (!Worlds[i].is_locked) { //

                Worlds[i].is_locked = true; // закрываю этот мир

                Emotion_ OppositeWorld = GetOpposite(Emotion[i]); // закрываю противоположный 
                Worlds[OppositeWorld].is_locked = true;

            }
        }
    }

    void ChangeGamerule() { // здесь буду менять игровые правила исходя из значений шкал 

        for (int i = 0; i < Emotion.size(); i++) {

            int OpenLimit = Hero.emotions[i];
            OpenLimit -= 2;

            if (LimitCheck(OpenLimit)) {

                LockedWorlds();



            }
        }

    }

    void Transfuse(Emotion_ feels) {

        Emotion_ opposite_emotion = GetOpposite(feels); // Эмоции как переливающиеся сосуды
        Hero.emotions[opposite_emotion] = 100 - Hero.emotions[feels];

    }

    void Addition(Emotion_ feels, vector<Emotion_> Array) {

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

    void Subtraction(Emotion_ feels, vector<Emotion_> Array) {

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

    void ChangeEmotions(Emotion_ DominationEmotion, bool sign) { // принимает доминирующую эмоцию и знак для фикс. значений

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
};

class OutputSystem { // система вывода информации
public:

    void OutputDialog(int npcID) {

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // перебираю всех персонажей в мире игрока

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { // сраниваю с айди 

                cout << Worlds[Hero.current_loc].character[i].text_NPC << endl; // вывожу текст персонажа  

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // перебираю ответьные реплики

                    cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl; // и вывожу их

                }
            }
        }
    }

    void OutputStates() { // вывод общего состояния игрока, шакал

        cout << "Текущее состояние: " << States_Names[Hero.states] << endl;

        for (int i = 0; i < Emotion.size(); i++) {

            cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // выводим текущие эмоции игрока

        }

        cout << "Ваши вещи: " << endl;

        for (int i = 0; i < Hero.items.size(); i++) {

            cout << left << setw(20) << Items_Names[i] << "\t" << 1 << endl; // выводим предметы игрока

        }
    }

    void CommandInfo() { // вывод списка команд

        cout << "Help - список команд \n";
        cout << "Edit - изменить эмоции / состояние\n";
        cout << "Info - информация о инициализированных объектах \n";
        cout << "Status - информация о состоянии персонажа \n";
        cout << "Go - для перемещения \n";
        cout << "Use - позволяет использовать предмет из инвенторя\n";
        cout << "Start - начать диалог с персонажем (если есть с кем поболтать)\n";
    }
};

class InputSystem : GameLogicSystem {
private:

public:

    bool InputHandler(int choice, int npcID) { // Обрабатывает ввод игрока

        int counter = 0;

        if (choice == 0) return false;
        if (choice != 0) choice -= 1; // тк в демонтрации j + 1

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // перебираю персонажей в мире игрока

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { //проверка на айди 

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // перебираю ответные реплики игрока персонажу

                    if (choice == j) { // сравниваю ввод с репликой w3wйц

                        ChangeEmotions(Worlds[Hero.current_loc].character[i].Answer[j].id, true); // записываю ID в функцию, true - по умолчанию
                        StatesRegulator();
                        counter++;

                    }
                }
            }
        }

        if (counter == 1) return true;

    }
};

