//
// Created by Andrew on 07.05.2021.
//
#include <string>
#include "is_number.h"

// Проверка на число
bool is_number(std::string str) {
    int size = str.length();
    if (size == 0)
        return false;

    for (int i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    return true;
}