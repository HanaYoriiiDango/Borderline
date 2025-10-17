
/*____________________________________ЗАМЕТКИ______________________________________________________________



*/

int main() {

    setlocale(LC_ALL, "RU"); // настраивает локализацию (даты чила валюты и тд)
    SetConsoleCP(1251); // ввод на кириллице
    SetConsoleOutputCP(1251); // вывод кириллици
    srand((time(nullptr))); // nullptr == NULL == 0, nullptr - более современный и типобезопасный стандарт 

    GameCore Game;
    Game.InitGame();
    Game.Help();

    string temp; // переменная для ввода команд 

    while (Hero.life) {

        cin >> temp; // ожидаем ввода одной из команд 
        if (temp == "test") Game.test();
        if (temp == "Edit") Game.Edit();
        if (temp == "Help") Game.Help(); // выводит все команды
        if (temp == "Status") Game.StatusInfo(); // выводит шкалы и состояние игрока
        if (temp == "Info") Game.InitInfo(); // выводит инфу о инциализированных обьектах
        if (temp == "Go") Game.Go(); // выводит все доступные миры для игрока и позволяет перемещаться по тем мирам что  ему доступны  
        if (temp == "Use") Game.Use(); // позволяет ипользовать предметы игрока
        if (temp == "Start") Game.StartDialog(); // начинаем диалог с персонажем
    }
}