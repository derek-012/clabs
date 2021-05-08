//
// Created by Andrew on 07.05.2021.
//

#include <iostream>
#include <fstream>
#include <io.h>
#include "get_functions.h"
#include "human.h"

using namespace std;

Human* new_human() {
    //const string line = "------------------------------";
    auto *h = new Human;
    string name;
    cout << "Ввод данных о человеке:" << endl;
    cout << "Имя: ";         std::getline(cin, name); name.copy(h->name, name.length()); h->name[name.length()] = '\0';
    cout << "Год рождения: ";  h->birthyear = get_year();
    cout << "Рост: ";        h->height = get_int();
    cout << "Вес: ";         h->weight = get_int();
    cout << "Пол: ";         h->gender = get_gender();

    return h;
}

void printHuman(Human human) {
    printf("%s:\n\tГод рождения: %d\n\tРост: %dcm\n\tВес: %dkg\n\tПол: %s\n",
           human.name, human.birthyear, human.height, human.weight, (human.gender == 0) ? "мужской" : "женский");
}

void exerciseA(Human* people, int list_size, int weight, int beginyear, int endyear) {
    printf("Задание A: люди с весом более %d, и годом рождения между %d и %d:\n",
           weight, beginyear, endyear);
    int count = 0;
    for(int i = 0; i < list_size; i++) {
        if (people[i].weight > weight && people[i].birthyear >= beginyear && people[i].birthyear <= endyear) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("Отсутствуют");
}

void exerciseB(Human* people, int list_size, int height) {
    printf("Задание B: женщины с ростом %d:\n", height);
    int count = 0;
    for(int i = 0; i < list_size; i++) {
        if (people[i].gender == 1 && people[i].height == height) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("Отсутствуют");
}

void exerciseC(Human* people, int list_size) {
    printf("Задание C: информация о людях в алфавитном порядке:\n");

    int l[4] = {0, 1, 2, 3};
    int t;
    for(int i = 0; i < list_size; i++) {
        for (int j = list_size - 1; j > i; j--) {
            if (strcmp(people[l[j]].name, people[l[j - 1]].name) < 0) {
                t = l[j];
                l[j] = l[j-1];
                l[j-1] = t;
            }
        }
    }

    for (int i : l) {
        printHuman(people[i]);
        printf("\n");
    }
}

size_t get_count_data(ifstream* infile) {
    int temp = infile->tellg();
    infile->seekg(0, ios_base::end);
    int pos = infile->tellg();
    infile->seekg(temp, ios::beg);
    return pos / sizeof(Human);
}

Human* get_list(ifstream* infile) {
    int size = get_count_data(infile);
    if (size == 0)
        return nullptr;

    Human* list = new Human[size];

    for (int i = 0; i < size; i++) {
        if (infile->read((char*) &list[i], sizeof(Human)).eof())
            break;
    }

    return list;
}

ofstream get_stream_append(char* filename) {
    ofstream outfile(filename, ios::binary | ios::app);
    cout << outfile.is_open() << endl;
    return outfile;
}