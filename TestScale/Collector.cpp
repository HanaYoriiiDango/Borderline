#include "systems.h"
#include <iostream>
#include <ctime>

using namespace std;

// Реализации методов StatisticsCollector
void StatisticsCollector::StartSession() {

    Session.startTime = time(0);
    Session.ID = Session.startTime;

    cout << "=== Начата новая игровая сессия ===" << endl;
    cout << "ID сессии: " << Session.ID << endl;

}

void StatisticsCollector::EndSession() {

    Session.endTime = time(0);
    Session.TimeMin = difftime(Session.endTime, Session.startTime) / 60.0;

    cout << "=== Игровая сессия завершена ===" << endl;
    cout << "endTime: " << Session.endTime << endl;
    cout << "TimeMin: " << Session.TimeMin << endl;

}

void StatisticsCollector::SaveData() {

    SaveStatistics.open("SaveStatistics.txt", ios::app);

    if (SaveStatistics.is_open()) {

        SaveStatistics << "_________________________________________________ " << endl;
        SaveStatistics << " Игровая сессия №: " << Session.ID << endl;
        SaveStatistics << " Start time: " << Session.startTime << endl;

        SaveStatistics << "Visit Sadness: " << Session.worldVisitSad << endl;
        SaveStatistics << "Visit Joy: " << Session.worldVisitJoy << endl;
        SaveStatistics << "Visit Power: " << Session.worldVisitPower << endl;
        SaveStatistics << "Visit Anger: " << Session.worldVisitAnger << endl;
        SaveStatistics << "Visit Fear: " << Session.worldVisitFear << endl;
        SaveStatistics << "Visit Calm:" << Session.worldVisitCalm << endl;
        SaveStatistics << "Всего перемещений по мирам: " << Session.AllVisitCount << endl;

        SaveStatistics << "выбрано ответных реплик: " << Session.counterChoices << endl;

        SaveStatistics << " End time: " << Session.endTime << endl;
        SaveStatistics << " End of time in minutes: " << Session.TimeMin << endl;
        SaveStatistics << "_________________________________________________ " << endl;

        SaveStatistics.close();

    }
    else {
        cout << "Файл не открыт или не существует" << endl;

    }
}

void StatisticsCollector::ClearStatistics() {

    SaveStatistics.open("SaveStatistics.txt", ios::trunc);

    if (SaveStatistics.is_open()) {
        SaveStatistics << "Статистика очищена " << "\n";
        SaveStatistics << "Игровая сессия №: " << Session.ID << "\n";
        SaveStatistics.close();
        cout << "✓ Statistics cleared!\n";

    }

    Hero.life = false;

}