#pragma once
#include "Init.h"

class GameCore { // ����� ����, � ������� � ������������ ��� �������  
private:
    InitSystem Init; // ������� ������������� ���� ������� ��������
    InputSystem Input; // ������� ��������� �����
    OutputSystem Output; // ������� ��������� ������ 
    GameLogicSystem Logic; // ������� ��� ��������� ������� ������ 

public: // ����� � ���������� ��� �������� ������� 
    void InitGame(); // ����� ���������� ��� �������������
    void Edit(); // ��������� ���� ��������
    void Help(); // ����� ���� ������
    void StatusInfo(); // ����� ����
    void InitInfo(); // ����� ���������� � ������������������ ��������
    void StartDialog(); // �������� ������, ���� ���� � ��� ���������
    void Go(); // ����������� ����� ������

};