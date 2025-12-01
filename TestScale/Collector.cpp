#include "systems.h"
#include <iostream>
#include <ctime>

using namespace std;

// Реализации методов StatisticsCollector
void StatisticsCollector::StartSession() {

    session.startTime = time(0);
    session.ID = session.startTime;

    cout << "=== Начата новая игровая сессия ===" << endl;
    cout << "ID сессии: " << session.ID << endl;

}

void StatisticsCollector::EndSession() {

    session.endTime = time(0);
    session.TimeMin = difftime(session.endTime, session.startTime) / 60.0;

    cout << "=== Игровая сессия завершена ===" << endl;
    cout << "endTime: " << session.endTime << endl;
    cout << "TimeMin: " << session.TimeMin << endl;

}

void StatisticsCollector::RecordVisit() {

    switch (Hero.current_loc) {
    case SADNESS: session.worldVisitSad++; break;
    case JOY: session.worldVisitJoy++; break;
    case POWER: session.worldVisitPower++; break;
    case FEAR: session.worldVisitFear++; break;
    case CALM: session.worldVisitCalm++; break;
    case ANGER: session.worldVisitAnger++; break;
    }

}

void StatisticsCollector::SaveData() {

    SaveStatistics.open("SaveStatistics.txt", ios::app);

    if (SaveStatistics.is_open()) {

        SaveStatistics << "_________________________________________________ " << endl;
        SaveStatistics << " Игровая сессия №: " << session.ID << endl;
        SaveStatistics << " Start time: " << session.startTime << endl;

        SaveStatistics << "Visit Sadness: " << session.worldVisitSad << endl;
        SaveStatistics << "Visit Joy: " << session.worldVisitJoy << endl;
        SaveStatistics << "Visit Power: " << session.worldVisitPower << endl;
        SaveStatistics << "Visit Anger: " << session.worldVisitAnger << endl;
        SaveStatistics << "Visit Fear: " << session.worldVisitFear << endl;
        SaveStatistics << "Visit Calm:" << session.worldVisitCalm << endl;
        SaveStatistics << "Всего перемещений по мирам: " << session.AllVisitCount << endl;

        SaveStatistics << "выбрано ответных реплик: " << session.counterChoices << endl;

        SaveStatistics << " End time: " << session.endTime << endl;
        SaveStatistics << " End of time in minutes: " << session.TimeMin << endl;
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
        SaveStatistics << "Игровая сессия №: " << session.ID << "\n";
        SaveStatistics.close();
        cout << "✓ Statistics cleared!\n";

    }

    Hero.life = false;

}