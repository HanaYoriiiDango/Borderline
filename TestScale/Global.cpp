#include "Global.h"

// ����������� ���������� ����������
vector<Emotion_> Emotion{ JOY, SADNESS, POWER, FEAR, CALM, ANGER };
string Emotion_Names[COUNT_Emotions] = { "�������", "������", "����", "�����", "�����������", "����" };
string Worlds_Names[COUNT_Emotions] = { "��� �������", "��� ������", "��� ����", "��� ������", "��� �����������", "��� �����" };
Player Hero;
Location Worlds[COUNT_Emotions];