﻿// OOPLab2Tpl.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include "Tasks.h"
#include "Examples.h"


/// @brief 
/// @return 
int main()
{
    cout << "OOP. Template for laboratory work #2.\n";

    char ch = '5';
    do {
        system("cls");
        MenuTask();
        ch = cin.get();

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищення буфера

        switch (ch) {
        case '1': task1(); break;
        case '2': task2(); break;
        case '3': task3(); break;
        case '4': task4(); break;
        case '5': Examples(); break;
        case '6': return 0;
        }

        cout << "Press Enter to continue...";
        cin.get(); // Очікування перед поверненням у меню

    } while (ch != '6');


    return 0;
}

