//
// Created by Andrew on 07.05.2021.
//

#include <iostream>
#include "is_number.h"
#include "get_functions.h"

// Функция для получения ответа да/нет
bool get_answer() {
    char c;
    do {
        cin >> c;
        cin.ignore();
        if (c == 'Y' || c == 'y')
            return true;

        if (c == 'N' || c == 'n')
            return false;

        printf("Ответ некорректный, повторите попытку (Y - да, N - нет): ");
    } while (true);
}

// Функция для получения int
int get_int() {
    string c;
    int result;
    do {
        cin >> c;
        cin.ignore();

        if (is_number(c)) {
            result = stoi(c);
            return result;
        }

        printf("Введенное значение не является числом, повторите попытку: ");
    } while (true);
}

// Функция получения года
int get_year() {
    int year;
    do {
        year = get_int();
        if (year > 1950 && year <= 2021)
            return year;
        cout << "Введенные данные не являются годом, повторите попытку: ";
    } while (true);
}

// Функция получения пола
bool get_gender() {
    char c;
    do {
        cin >> c;
        cin.ignore();
        if (c == 'M' || c == 'm')
            return false;

        if (c == 'F' || c == 'f')
            return true;

        printf("Ответ некорректный, повторите попытку (M - мужской, F - женский): ");
    } while (true);
}