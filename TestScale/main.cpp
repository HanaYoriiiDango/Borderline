#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;

enum Worlds_Num { SADNESS, JOY, FEAR, CALM, ANGER, POWER }; // ������������� ����, name
string Emotion_Names[6] = { "������", "�������", "�����", "�����������", "����", "����" };
string Worlds_Names[6] = { "��� ������", "��� �������", "��� ������", "��� �����������", "��� �����", "��� ����" };

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
        // ������������ ������� ����� ������� �����  wdq
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
//		   {"���", {
//			   {10, -5, 0, 0, 0, 0},   // ������� 1: ������� �������
//			   {-15, 5, 0, 0, 0, 0},   // ������� 2: ��� �������
//			   {5, 0, 5, -5, 0, 0}     // ������� 3: �����
//		   }},
//		   {"�����", {
//			   {5, -2, 0, 0, 0, 0},    // ������� 1: �����
//			   {-5, 2, 0, 0, 0, 0},
//			   {0, 0, 5, -5, 0, 0}
//		   }},
//		   {"����", {
//			   {0, 0, 0, 0, 5, -5},    // ����/����
//			   {0, 0, 5, -5, 0, 0},    // �����/�����������
//			   {0, 0, -5, 5, 0, 0}
//		   }}
//};

/* 

1) ����������� ������ ���� ���� ��� ������ � ������� ������ 
1.1) ��� �������� ����� ����� ������� ����
1.2) ����� �������� ����� �� �������� � �� �������������� ���������� ���������
2) ����������� ����� ��� Go ��� � �� ������ - �������� 
3) Master - ������� ������, ������ ������� �����. Test - ����� ��� ������  ? 
4) �� ���� ����� ���� ��������� ��� �� ������, � ��� ��������� ������ �� �����
5) ����� ��������������� ������� � �������� ������ �� ����� ����� �� ����������� ��� ������ ������� 
6) ��� ������ � ���������� � ���� ������������ ��� ��������� ������ ���� 
6.1) ��� ���������� ����� ������ ����� ������  (0 / 100) ��� ����������� � �� ����������� � ������ 
7) ��� ���� ������� ������� 
8) � ������������ �� ���������� ������ � �������� ����� �������� ��������� � �������
9) ��������� �������� ��� ������� ������������� ����������?



*/
void limit() {

    // ����� ���������� ������ ����������� �� ����� ����� ����� 
    // ����� ����� ��������, ������� ����� ��������� �� ����� �� �������� ������ ����� �� 0 � 100
    // ����� ������� ����������� �� ����� ����� ����� �������. �.� ���� �� �������� 100 � sadness, �� �� ����� �������� �� ������������ ������ � Joy 
    // ���� ������� �������
    // � ������ ����������� ��� ��� ��� ����������� ��� �� ����� ��� � �� ������� Go - �����? 
    // ��� ��� � ���� ����������� ������ ����������� �� ���� ����� �����, �� � ������� ������ ��������� ��  
    Hero.emotions[JOY] = 100 - Hero.emotions[SADNESS]; // ������ ��� �������������� ������
    Hero.emotions[CALM] = 100 - Hero.emotions[ANGER];
    Hero.emotions[POWER] = 100 - Hero.emotions[FEAR];

    for (int i = 0; i < 6; i++) {

            if (Hero.emotions[i] <= 0 || Hero.emotions[i] >= 100) {

                if (i != Hero.current_loc && Hero.emotions[i] > 0 && Hero.emotions[i] < 100) {
                        Hero.current_loc = i;
                        cout << ">> �� ������������ � " << Worlds_Names[Hero.Current_loc] << " ��-�� ��������������.\n";
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

    Worlds[0].name = "��� ������";
    Worlds[0].portal.push_back({ "��� �������", 1 });
    Worlds[0].portal.push_back({ "��� ������", 2 });
    Worlds[0].portal.push_back({ "��� �����������", 3 });
    Worlds[0].portal.push_back({ "��� �����", 4 });
    Worlds[0].portal.push_back({ "��� ����", 5 });

    Worlds[1].name = "��� �������";
    Worlds[1].portal.push_back({ "��� ������", 0 });
    Worlds[1].portal.push_back({ "��� ������", 2 });
    Worlds[1].portal.push_back({ "��� �����������", 3 });
    Worlds[1].portal.push_back({ "��� �����", 4 });
    Worlds[1].portal.push_back({ "��� ����", 5 });

    Worlds[2].name = "��� ������";
    Worlds[2].portal.push_back({ "��� ������", 0 });
    Worlds[2].portal.push_back({ "��� �������", 1 });
    Worlds[2].portal.push_back({ "��� �����������", 3 });
    Worlds[2].portal.push_back({ "��� �����", 4 });
    Worlds[2].portal.push_back({ "��� ����", 5 });

    Worlds[3].name = "��� �����������";
    Worlds[3].portal.push_back({ "��� ������", 0 });
    Worlds[3].portal.push_back({ "��� �������", 1 });
    Worlds[3].portal.push_back({ "��� ������", 2 });
    Worlds[3].portal.push_back({ "��� �����", 4 });
    Worlds[3].portal.push_back({ "��� ����", 5 });

    Worlds[4].name = "��� �����";
    Worlds[4].portal.push_back({ "��� ������", 0 });
    Worlds[4].portal.push_back({ "��� �������", 1 });
    Worlds[4].portal.push_back({ "��� ������", 2 });
    Worlds[4].portal.push_back({ "��� �����������", 3 });
    Worlds[4].portal.push_back({ "��� ����", 5 });

    Worlds[5].name = "��� ����";
    Worlds[5].portal.push_back({ "��� ������", 0 });
    Worlds[5].portal.push_back({ "��� �������", 1 });
    Worlds[5].portal.push_back({ "��� ������", 2 });
    Worlds[5].portal.push_back({ "��� �����������", 3 });
    Worlds[5].portal.push_back({ "��� �����", 4 });
}

void Start_Game() {

    bool start = true;
    string temp;

    while (start) {


        cout << "��� ������� ����� �� ����������, ��� � ���� ����� \n";
        cout << "Go - ��� ����������� \n";
        cin >> temp;

        if (temp == "Go") {

            for (int i = 0; i < Worlds[Hero.current_loc].portal.size(); i++) {

                cout << i + 1 << ")" << left << setw(20) << Worlds[Hero.current_loc].portal[i].name << "\t"
                     << (Worlds[Hero.current_loc].portal[i].open ? "��� ������ \n" : "��� ������ \n") << endl;

            }

            cout << "� ����� ��� ������� �������������? \n";
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
                Ela.text("�����? (������ 1 ��� 2) ", 60, 40, 50, 50, 50, 50);
                Ela.info();
                cout << "1) ��� ()" << endl;
                cout << "2) �� ()" << endl;
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
                 
                    Hero.emotions[JOY] = 100 - Hero.emotions[SADNESS]; // ������ ��� �������������� ������
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
//		cout << "\n�� ���������� � " << Worlds_Names[Hero.Current_loc] << ". ���� ����������� " << c.Name << ".\n";
//		cout << "������ �������:\n";
//		cout << "1) ��� ���� �� ��� �������?�\n";
//		cout << "2) �� ������� �������\n";
//		cout << "3) ��� ���� �����\n";
//		cin >> choice;  
//
//        if (choice < 1 || choice > 3) {
//            cout << "������������ �����. ���������.\n";
//            continue;
//        }
//
//        // ���������� �������
//		NPC& c = Characters[round % 3];
// 
//        int idx = choice - 1;
//        for (int i = 0; i < 6; i++) {
//            Emotions[i] += c.Effect[idx][i];
//            if (Emotions[i] > 100) Emotions[i] = 100;
//            if (Emotions[i] < 0) Emotions[i] = 0;
//        }
//
//        // ������ ��� �������������� ������:
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
//            cout << "\n��� ������ �������� ������� ��������. �� ������� ����...\n���� ��������.\n";
//            break;
//        }
//
//        // ������� � ������ ���, ���� ������� ������ ����� �� �������
        if (Emotions[Hero.Current_loc] <= 0 || Emotions[Hero.Current_loc] >= 100) {
            for (int i = 0; i < 6; i++) {
                if (i != Hero.Current_loc && Emotions[i] > 0 && Emotions[i] < 100) {
                    Hero.Current_loc = i;
                    cout << ">> �� ������������ � " << Worlds_Names[Hero.Current_loc] << " ��-�� ��������������.\n";
                    break;
                }
            }
        }
//
//        // ����� ������
//        cout << "\n������� ������:\n";
//        for (int i = 0; i < 6; i++) {
//            cout << Emotion_Names[i] << ": " << Emotions[i] << "\n";
//        }
//
//        round++;��
//	}


int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	Init_Game();
	Start_Game();

}