
/*____________________________________�������______________________________________________________________



*/

int main() {

    setlocale(LC_ALL, "RU"); // ����������� ����������� (���� ���� ������ � ��)
    SetConsoleCP(1251); // ���� �� ���������
    SetConsoleOutputCP(1251); // ����� ���������
    srand((time(nullptr))); // nullptr == NULL == 0, nullptr - ����� ����������� � �������������� �������� 

    GameCore Game;
    Game.InitGame();
    Game.Help();

    string temp; // ���������� ��� ����� ������ 

    while (Hero.life) {

        cin >> temp; // ������� ����� ����� �� ������ 
        if (temp == "test") Game.test();
        if (temp == "Edit") Game.Edit();
        if (temp == "Help") Game.Help(); // ������� ��� �������
        if (temp == "Status") Game.StatusInfo(); // ������� ����� � ��������� ������
        if (temp == "Info") Game.InitInfo(); // ������� ���� � ����������������� ��������
        if (temp == "Go") Game.Go(); // ������� ��� ��������� ���� ��� ������ � ��������� ������������ �� ��� ����� ���  ��� ��������  
        if (temp == "Use") Game.Use(); // ��������� ����������� �������� ������
        if (temp == "Start") Game.StartDialog(); // �������� ������ � ����������
    }
}