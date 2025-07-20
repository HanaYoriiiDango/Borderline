#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;

enum Worlds_Num { SADNESS, JOY, FEAR, CALM, ANGER, POWER }; // инициализирую миры, name
string Emotion_Names[6] = { "Грусть", "Радость", "Страх", "Спокойствие", "Гнев", "Сила" };
string Worlds_Names[6] = { "Мир Грусти", "Мир Радости", "Мир Страха", "Мир Спокойствия", "Мир Гнева", "Мир Силы" };

struct Portal_ {
    string name;
    int target;
    bool open = true;

};

struct Location {
    string name;
    vector<Portal_> portal;


};


struct info {
    
    string dialog_Text;
    int effect[6];

};

class NPC {
public:

    string name;
    vector<info> words;

    NPC(string name) : name(name) {};

    void text( string letter, int sadness, int joy,int fear , int calm, int anger, int power) {

        words.push_back({ letter, {sadness, joy, fear, calm, anger, power} });
        // наследование классов изучи полезно будет 
    }

    void info() {

        cout << name << ": ";

        for (int i = 0; i < words.size(); i++) {
            
            cout << words[i].dialog_Text;

            for (int j = 0; j < 6; j++) {

                cout << "(" << words[i].effect[j] << ") ";

            }

            cout << "\n";
        }

    }
    
};

struct Player {

	string name;
	int current_loc = ANGER;
    int emotions[6] = { 50, 50, 50, 50, 50, 50 };

};
 

Player Hero;
Location Worlds[6];
vector<NPC> Characters;
int Effect[2][6];

//NPC Characters[3] = {
//		   {"Эла", {
//			   {10, -5, 0, 0, 0, 0},   // Реплика 1: сильное влияние
//			   {-15, 5, 0, 0, 0, 0},   // Реплика 2: ещё сильнее
//			   {5, 0, 5, -5, 0, 0}     // Реплика 3: смесь
//		   }},
//		   {"Лоран", {
//			   {5, -2, 0, 0, 0, 0},    // Реплика 1: слабо
//			   {-5, 2, 0, 0, 0, 0},
//			   {0, 0, 5, -5, 0, 0}
//		   }},
//		   {"Ними", {
//			   {0, 0, 0, 0, 5, -5},    // Гнев/Сила
//			   {0, 0, 5, -5, 0, 0},    // Страх/Спокойствие
//			   {0, 0, -5, 5, 0, 0}
//		   }}
//};

/* 

1) перемещение внутри мира пока что только в формате текста 
1.1) все описания также нужно вводить сюда
1.2) Выбор действий никак не меняетсЯ и не ограничивается выбранными репликами
2) Перемещение будет как Go так и по шкалам - срастить 
3) Master - готовая версия, всегда рабочая ветка. Test - ветка для тестов  √ 
4) По мере роста кода раскидать все по файлам, в них стараться сильно не срать
5) Нужно автоатизировать систему с влиянием реплик на шкалы чтобы не прописывать для каждой реплики 
6) эти эмоции с персонажей я буду использовать для изменения эмоций шкал 
6.1) при достижении одной эмоции своих границ  (0 / 100) мир закрывается и мы пермещаемся в другой 
7) мне дают вариант ответов 
8) в зависмимости от выбранного ответа я имзменяю шкалу согласно паттернам в таблице
9) Насколько подойдут для проекта ассоциативные контейнеры?



*/
void limit() {

    // Нужно разобратья логику перемещения по мирам через шкалы 
    // Нужна такая проверка, которая будет проверять не зашло ли значение каждой шкалы за 0 и 100
    // Нужно связать перемещение по мирам через шкалы попарно. Т.е если мы достигли 100 в sadness, то по такой механике мы перемещаемся только в Joy 
    // миры попарно связаны
    // я должен блокировать сам мир для перемещения как по шкале так и по команде Go - флаги? 
    // Так как у меня отсутствует логика перемещения по миры через шкалы, то я сначало должен прописать ее  
    Hero.emotions[JOY] = 100 - Hero.emotions[SADNESS]; // Эмоции как переливающиеся сосуды
    Hero.emotions[CALM] = 100 - Hero.emotions[ANGER];
    Hero.emotions[POWER] = 100 - Hero.emotions[FEAR];

    for (int i = 0; i < 6; i++) {

            if (Hero.emotions[i] <= 0 || Hero.emotions[i] >= 100) {

                if (i != Hero.current_loc && Hero.emotions[i] > 0 && Hero.emotions[i] < 100) {
                        Hero.current_loc = i;
                        cout << ">> Ты переместился в " << Worlds_Names[Hero.Current_loc] << " из-за нестабильности.\n";
                        break;
                }
                
            }

            Hero.emotions[i] = 100;
            Worlds[Hero.current_loc].portal[i].open = false;
        
    }
}


void Init_Game() {

    NPC Ela("PORNO");
    Ela.text("BLADIMIR PUTIN MOLODEC", 100, 50, 100, 99, 90, 99);
    //Ela.info();

    Worlds[0].name = "Мир Грусти";
    Worlds[0].portal.push_back({ "Мир Радости", 1 });
    Worlds[0].portal.push_back({ "Мир Страха", 2 });
    Worlds[0].portal.push_back({ "Мир Спокойствия", 3 });
    Worlds[0].portal.push_back({ "Мир Гнева", 4 });
    Worlds[0].portal.push_back({ "Мир Силы", 5 });

    Worlds[1].name = "Мир Радости";
    Worlds[1].portal.push_back({ "Мир Грусти", 0 });
    Worlds[1].portal.push_back({ "Мир Страха", 2 });
    Worlds[1].portal.push_back({ "Мир Спокойствия", 3 });
    Worlds[1].portal.push_back({ "Мир Гнева", 4 });
    Worlds[1].portal.push_back({ "Мир Силы", 5 });

    Worlds[2].name = "Мир Страха";
    Worlds[2].portal.push_back({ "Мир Грусти", 0 });
    Worlds[2].portal.push_back({ "Мир Радости", 1 });
    Worlds[2].portal.push_back({ "Мир Спокойствия", 3 });
    Worlds[2].portal.push_back({ "Мир Гнева", 4 });
    Worlds[2].portal.push_back({ "Мир Силы", 5 });

    Worlds[3].name = "Мир Спокойствия";
    Worlds[3].portal.push_back({ "Мир Грусти", 0 });
    Worlds[3].portal.push_back({ "Мир Радости", 1 });
    Worlds[3].portal.push_back({ "Мир Страха", 2 });
    Worlds[3].portal.push_back({ "Мир Гнева", 4 });
    Worlds[3].portal.push_back({ "Мир Силы", 5 });

    Worlds[4].name = "Мир Гнева";
    Worlds[4].portal.push_back({ "Мир Грусти", 0 });
    Worlds[4].portal.push_back({ "Мир Радости", 1 });
    Worlds[4].portal.push_back({ "Мир Страха", 2 });
    Worlds[4].portal.push_back({ "Мир Спокойствия", 3 });
    Worlds[4].portal.push_back({ "Мир Силы", 5 });

    Worlds[5].name = "Мир Силы";
    Worlds[5].portal.push_back({ "Мир Грусти", 0 });
    Worlds[5].portal.push_back({ "Мир Радости", 1 });
    Worlds[5].portal.push_back({ "Мир Страха", 2 });
    Worlds[5].portal.push_back({ "Мир Спокойствия", 3 });
    Worlds[5].portal.push_back({ "Мир Гнева", 4 });
}

void Start_Game() {

    bool start = true;
    string temp;

    while (start) {


        cout << "тут ебанина какая то происходит, все в огне нахуй \n";
        cout << "Go - для перемещения \n";
        cin >> temp;

        if (temp == "Go") {

            for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

                cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
                     << (Worlds[Hero.current_loc].portal[i].open ? "Мир открыт \n" : "Мир закрыт \n") << endl;

            }

            cout << "В какой мир желаешь переместиться? \n";
            int choice;
            cin >> choice;

            if (choice > 0 || choice < 6) {

                for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

                    if (choice == Worlds[Hero.current_loc].portal[i].target) {

                        Hero.current_loc = Worlds[Hero.current_loc].portal[i].target;
                        cout << "Current loc: " << Hero.current_loc << endl;

                    }
                }
            }
        }
        if (temp == "Loc") {

            cout << "Current loc: " << Hero.current_loc << endl;

        }
        if (temp == "Start") {


            bool start = true;

            while (start) {

            for (int i = 0; i < 6; i++ ) {

                cout << left << setw(20) << Emotion_Names[i] << "\t" << Hero.emotions[i] << endl;

            }

                int choice;

                NPC Ela("Ela");
                Ela.text("Сосал? (выбери 1 или 2) ", 60, 40, 50, 50, 50, 50);
                Ela.info();
                cout << "1) нет ()" << endl;
                cout << "2) да ()" << endl;
                cin >> choice;

                if (choice > 0 || choice < 2) {

                    switch (choice) {
                    case(1):
                        Hero.emotions[SADNESS] += 10;
                        cout << "Sadness: " << Hero.emotions[SADNESS] << "\n";
                        break;
                    case(2):
                        Hero.emotions[JOY] += 10;
                        cout << "Joy: " << Hero.emotions[JOY] << "\n";
                        break;
                    }

                    limit();
                 
                    Hero.emotions[JOY] = 100 - Hero.emotions[SADNESS]; // Эмоции как переливающиеся сосуды
                    Hero.emotions[CALM] = 100 - Hero.emotions[ANGER];
                    Hero.emotions[POWER] = 100 - Hero.emotions[FEAR];

                }
            }
        }
    }    
}






//    bool start = true;
//	int round = 0;
//	int choice;
//
//	while (start) {
//
//		NPC& c = Characters[round % 3];
//		cout << "\nТы находишься в " << Worlds_Names[Hero.Current_loc] << ". Тебе встречается " << c.Name << ".\n";
//		cout << "Выбери реплику:\n";
//		cout << "1) «Ты ведь всё ещё помнишь?»\n";
//		cout << "2) «Я пытался забыть»\n";
//		cout << "3) «Ты была права»\n";
//		cin >> choice;
//
//        if (choice < 1 || choice > 3) {
//            cout << "Некорректный выбор. Повторите.\n";
//            continue;
//        }
//
//        // Применение эффекта
//		NPC& c = Characters[round % 3];
// 
//        int idx = choice - 1;
//        for (int i = 0; i < 6; i++) {
//            Emotions[i] += c.Effect[idx][i];
//            if (Emotions[i] > 100) Emotions[i] = 100;
//            if (Emotions[i] < 0) Emotions[i] = 0;
//        }
//
//        // Эмоции как переливающиеся сосуды:
//        Emotions[JOY] = 100 - Emotions[SADNESS];
//        Emotions[CALM] = 100 - Emotions[ANGER];
//        Emotions[POWER] = 100 - Emotions[FEAR];
//
//        bool extreme = true;
//        for (int i : {SADNESS, FEAR, ANGER}) {
//            if (Emotions[i] != 0 && Emotions[i] != 100) {
//                extreme = false;
//                break;
//            }
//        }
//        if (extreme) {
//            cout << "\nВсе эмоции достигли крайних пределов. Ты теряешь себя...\nИгра окончена.\n";
//            break;
//        }
//
//        // Перенос в другой мир, если текущая эмоция вышла за пределы
        if (Emotions[Hero.Current_loc] <= 0 || Emotions[Hero.Current_loc] >= 100) {
            for (int i = 0; i < 6; i++) {
                if (i != Hero.Current_loc && Emotions[i] > 0 && Emotions[i] < 100) {
                    Hero.Current_loc = i;
                    cout << ">> Ты переместился в " << Worlds_Names[Hero.Current_loc] << " из-за нестабильности.\n";
                    break;
                }
            }
        }
//
//        // Вывод эмоций
//        cout << "\nТекущие эмоции:\n";
//        for (int i = 0; i < 6; i++) {
//            cout << Emotion_Names[i] << ": " << Emotions[i] << "\n";
//        }
//
//        round++;вы
//	}


int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	Init_Game();
	Start_Game();

}