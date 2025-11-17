#include "Global.h"

// Определения глобальных переменных
vector<Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER };
string Emotion_Names[COUNT_Emotions] = { "Радость", "Грусть", "Сила", "Страх", "Спокойствие", "Гнев" };
string Worlds_Names[COUNT_Emotions] = { "Мир Радости", "Мир Грусти", "Мир Силы", "Мир Страха", "Мир Спокойствия", "Мир Гнева" };
Player Hero; 
Location Worlds[COUNT_Emotions];