class GameLogicSystem {
private:
    Emotion_ ArrayNum;
    int dominationRate = 10; // ���������� ��� ��������� �����������/��������� ������ g�
    int passiveRate = 5;

public:
    vector<Emotion_> Positive;
    vector<Emotion_> Negative;

    Emotion_ GetOpposite(Emotion_ feels) { // ��������� ���� ������ � ���������� ���������������

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

    bool Stabilization() { // ������������� ������������� ��� �������� ���� �� 50

        int count = 0;

        for (int i = 0; i < Emotion.size(); i++) {

            Hero.emotions[i] = 50;
            count++;

        }
        if (count == 6) return true;
        else false;
    }

    bool FindDominant(Emotion_ feels, int Value) { // ��������� ����������� ����� �� ���������� ��������
        // � ����� ��� �������� ����� ����� ������� �� ���� ������������ r

        bool findTrue = false; // ���� ��� ����������� ��� ��� ������� true 

        for (int i = 0; i < COUNT_Emotions; i++) { // ��������� ������

            if (Hero.emotions[feels] > Value) { // �������� ��������� ����� �� ���������
                if (i != feels && Hero.emotions[feels] > Hero.emotions[i]) findTrue = true;
                // ������� ����� ����� ������� �� ���� ������������
                // ������ ������ ������� �����? ������ ��� ��� ��������� ��������� �� ������ �������� �����
                // ������� ��� �������� "�����������", ����� ��� >= Value
                // ������� � ���� ��������� ��������� ����� ������ � ����������, �� �� � ����� ��
            }
        }

        if (findTrue) return true; // ���� ���� ��������� �� ���������� true
        else false;
    }

    bool CheckScope(int MinValue, int MaxValue) { // ��������� ��� ������ ������ � �������� ���������� ���������

        int counterTrue = 0; // ������� ������ 

        for (int i = 0; i < COUNT_Emotions; i++) { // ��������� ��� ������

            int EmotionValue = Hero.emotions[i]; // ��������� ������ �� ��������� ����������

            if (EmotionValue <= MinValue || EmotionValue >= MaxValue) counterTrue++; // +1 ���� ������ ���� ����� ��������� � ��������� �� 40 �� 60

        }

        if (counterTrue == 6) return true; // ������ true, ������ ���� ��������� ��������� 6 ������
        else return false; // ����� ������ �� ��������

    }

    bool IsCheckAllLimit(int MinLimit, int MaxLimit) { // ��������� ��� ������ �� ���������� ��������� �������

        bool confirm = false;

        for (int i = 0; i < COUNT_Emotions; i++) { // ���������� ������

            int EmotionValue = Hero.emotions[i]; // ��������� ������ �� ��������� ����������

            if (EmotionValue <= MinLimit || EmotionValue >= MaxLimit) confirm = true;
            // ���� ���� ���� ������ �������� ��������� ������� - true

        }

        if (confirm) return true; // ���� ��������� �� �������� ������ ������������� - ���������� true 
        else return false;
    }

    int ReturnWorldsLocked() { // ���������� ���������� �������� �����

        int counterLocked = 0; // �������

        for (int i = 0; i < COUNT_Emotions; i++) { // ��������� ������

            if (Worlds[i].is_locked) { // �������� ����������

                counterLocked++; // ������ ������ �������� ���

            }
        }

        return counterLocked; // ��������� ���������� �������� �����

    }

    bool IsAllWorldsOpen() { // ��������� ��� �� ���� �������, ���� �� - true

        int count = 0; // �������

        for (int i = 0; i < COUNT_Emotions; i++) { // ��������� ����

            if (!Worlds[i].is_locked) count++; // +1 � ������� ���� ��� ������

        }

        if (count == 6) return true;// ���� ��� 6 ������ ������� - ������ true
        else return false;

    }

    bool TriggerBreaking() {

        int count = 0;

        if (Hero.states == Breaking) { // ���� ����� � ������ ��

            int random_index; // ���������� ��� ��������� ����� �������� �����

            for (int i = 0; i < Emotion.size(); i++) { // ��������� 

                random_index = rand() % 31 - 15; // ����� ���������� o� 15 � �� -15
                Hero.emotions[i] += random_index; // ���������� ��������� �������� � ������ ������ ������
                count++;
            }

        }
        if (count == 6) return true; // ������� �������� 6 ������ - true
        else return false;
    }

    States_ TriggerStates(States_ states) { // ����� � ���� ��������� ��� ������� ��� ������� ���������

        //States_ OldStates = Hero.states;
        States_ triggerID = Stability;

        if (states == Stability) { //____________������������__________________________
            // ����� ��� ��������� �������� ��� ������ �� ����������� ���������

            if (FindDominant(FEAR, 70)) triggerID = Anxiety; // �������� �� �������
            // �� ������� : ��������� ������� ��������� ���� � ������ ����� > 70 
            // � ��� ���� ��� ����� ������� ����� �� ����

            //if (FindDominant(SADNESS, 70)) triggerID = Depression; // �������� �� ���������
            // �� ������� : ��������� ��������� ��������� ���� � ������ ������ > 70 
            // � ��� ���� ��� ����� ������� ����� �� ����

            //if (FindDominant(ANGER, 70)) triggerID = Rage; // �������� �� �����������
            // �� ������� : ��������� ����������� ��������� ���� � ������ ���� > 70 
            // � ��� ���� ��� ����� ������� ����� �� ����

            //if (ReturnWorldsLocked() == 4) triggerID = Apathy;// �������� �� ������
            // �� �������: ��������� ������ ��������� ���� � ������ ������������ ������ � ������� �����  

            //if (ReturnWorldsLocked() == 2) triggerID = Crisis;// �������� �� ������
            // �� �������: ��������� ������� ��������� ���� � ������ ������������ ������ � ���� �����  

        }

        if (states == Anxiety) { // �������� �� ��������� ���������� �������

            if (Hero.emotions[FEAR] < 50) triggerID = Weariness;

        }

        if (states == Depression) {  // �������� �� ��������� ���������� ���������

            //if (Hero.emotions[JOY] > 50) triggerID = Weariness;

        }

        if (states == Rage) {// �������� �� ��������� ���������� �����������

            //if (Hero.emotions[CALM] > 50) triggerID = Weariness;

        }

        if (states == Breaking) { //__________�����_________________________
            // 1 - ������� ������ ���������, ��� ����� ������ ���� � �������� 30 � 70
            //if (CheckScope(30, 70)) triggerID = Weariness; // �������� �� ���������

            // 2 - ������� ������ ������, ���� ���� �� ���� �� ���� ����� �� �������
            //if (IsCheckAllLimit(0, 100)) triggerID = Apathy; // �������� �� ������
        }

        if (states == Apathy) { //__________������_________________________

            // �������� ��� ���� �� ����������
            //if (IsAllWorldsOpen()) triggerID = Weariness; // ���� ��� ���� ������� ������� �� ������ � ���������

        }

        if (states == Weariness) { //__________���������_________________________

            //if (CheckScope(40, 60)) triggerID = Stability; // �������� �� ���������� �������� ��������
            // ���� CheckScope ������ true ������� �� ��������� � ������������
        }

        if (states == Crisis) { //_______________������__________________________

            //if (CheckScope(40, 60)) triggerID = Stability; // �������� �� ���������� �������� ��������
            // ���� CheckScope ������ true ������� �� ������� � ������������
        }

        //if (triggerID != OldStates) return triggerID;
        return triggerID;
    }

    bool StatesRegulator() { // ���������� ���������� ���������, �������� �������� ��� ������� ��������� ������

        States_ old_states = Hero.states; // ���������� ������ ������� ���������
        States_ new_states = TriggerStates(Hero.states); // ���������� ��� ������ ���������
        Hero.states = new_states; // ���������� ����� ��������� ������

        if (Hero.states != old_states) return true; // ���� ��������� ����������, �� true
        else false;

        //vector<is_function<void ()>> Trigger; // ��� ����������� ����� ������� ������ �� �������

    }

    void EffectStates() { // ��������� ��� ������� �� ���������

        if (StatesRegulator()) { // ���� ��������� ����������, ��������� ������ ���������

            //___________________________________�������_____________________________________________________

            if (Hero.states == Anxiety) {


            }

            //___________________________________���������_____________________________________________________

            if (Hero.states == Depression) {


            }

            //___________________________________�����������_____________________________________________________

            if (Hero.states == Rage) {

            }

            //___________________________________����� (�����)_____________________________________________________

            // �������� ������: 
            // ���� ����� �������� �����, �� ����� ������ �������� ���������� ������ 20 ������
            // ����� ��� �������������, ����� ������ ������ �������� �������� � ������� ������� QTE
            // � ���������� �� ������ � ������ QTE ������� �������� 2 + 2 = 4
            // ���� ����� �� �����-�� ��������� ������� �������� �� 4, � 65 - �� ����� ������ ��� ����� �������� �� +-15
            // ���� ����� ������� 4, �� ����� ��������� � ������� ���������
            // ����� ��������� � ���������� ������ ������ - ��� ���� ������, � ���� �������� ������ ������ ���� ���� ���

            if (Hero.states == Breaking) {


            }
            //___________________________________������________________________________________________________

            if (Hero.states == Apathy) {


            }
            //___________________________________���������_____________________________________________________

            if (Hero.states == Weariness) {


            }

            //___________________________________������_____________________________________________________

            if (Hero.states == Crisis) {




            }
        }
    }

    void HeroLocCheck() {

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

    void LockedWorlds() {

        for (int i = 0; i < Emotion.size(); i++) { // ��������� ��� ������

            // ������� ��� ������� ��� ��� ����� �������� �� ��, ��������� �� ����� ������ ������������ ����
            // ���� �� - ����������, ���� ��� - �� ���������

            HeroLocCheck();

            if (!Worlds[i].is_locked) { //

                Worlds[i].is_locked = true; // �������� ���� ���

                Emotion_ OppositeWorld = GetOpposite(Emotion[i]); // �������� ��������������� 
                Worlds[OppositeWorld].is_locked = true;

            }
        }
    }

    void ChangeGamerule() { // ����� ���� ������ ������� ������� ������ �� �������� ���� 

        for (int i = 0; i < Emotion.size(); i++) {

            int OpenLimit = Hero.emotions[i];
            OpenLimit -= 2;

            if (LimitCheck(OpenLimit)) {

                LockedWorlds();



            }
        }

    }

    void Transfuse(Emotion_ feels) {

        Emotion_ opposite_emotion = GetOpposite(feels); // ������ ��� �������������� ������
        Hero.emotions[opposite_emotion] = 100 - Hero.emotions[feels];

    }

    void Addition(Emotion_ feels, vector<Emotion_> Array) {

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

    void Subtraction(Emotion_ feels, vector<Emotion_> Array) {

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

    void ChangeEmotions(Emotion_ DominationEmotion, bool sign) { // ��������� ������������ ������ � ���� ��� ����. ��������

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
};

class OutputSystem { // ������� ������ ����������
public:

    void OutputDialog(int npcID) {

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // ��������� ���� ���������� � ���� ������

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { // �������� � ���� 

                cout << Worlds[Hero.current_loc].character[i].text_NPC << endl; // ������ ����� ���������  

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // ��������� ��������� �������

                    cout << j + 1 << ") " << Worlds[Hero.current_loc].character[npcID].Answer[j].text << endl; // � ������ ��

                }
            }
        }
    }

    void OutputStates() { // ����� ������ ��������� ������, �����

        cout << "������� ���������: " << States_Names[Hero.states] << endl;

        for (int i = 0; i < Emotion.size(); i++) {

            cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl; // ������� ������� ������ ������

        }

        cout << "���� ����: " << endl;

        for (int i = 0; i < Hero.items.size(); i++) {

            cout << left << setw(20) << Items_Names[i] << "\t" << 1 << endl; // ������� �������� ������

        }
    }

    void CommandInfo() { // ����� ������ ������

        cout << "Help - ������ ������ \n";
        cout << "Edit - �������� ������ / ���������\n";
        cout << "Info - ���������� � ������������������ �������� \n";
        cout << "Status - ���������� � ��������� ��������� \n";
        cout << "Go - ��� ����������� \n";
        cout << "Use - ��������� ������������ ������� �� ���������\n";
        cout << "Start - ������ ������ � ���������� (���� ���� � ��� ���������)\n";
    }
};

class InputSystem : GameLogicSystem {
private:

public:

    bool InputHandler(int choice, int npcID) { // ������������ ���� ������

        int counter = 0;

        if (choice == 0) return false;
        if (choice != 0) choice -= 1; // �� � ����������� j + 1

        for (int i = 0; i < Worlds[Hero.current_loc].character.size(); i++) { // ��������� ���������� � ���� ������

            if (Worlds[Hero.current_loc].character[i].ID == npcID) { //�������� �� ���� 

                for (int j = 0; j < Worlds[Hero.current_loc].character[i].Answer.size(); j++) { // ��������� �������� ������� ������ ���������

                    if (choice == j) { // ��������� ���� � �������� w3w��

                        ChangeEmotions(Worlds[Hero.current_loc].character[i].Answer[j].id, true); // ��������� ID � �������, true - �� ���������
                        StatesRegulator();
                        counter++;

                    }
                }
            }
        }

        if (counter == 1) return true;

    }
};

