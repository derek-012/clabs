//
// Created by Andrew on 07.05.2021.
//

#ifndef LAB7_2_HUMAN_H
#define LAB7_2_HUMAN_H

struct Human {
    char name[60];
    int birthyear;
    int height;
    int weight;
    bool gender;
};

Human* new_human();

void printHuman(Human);
size_t get_count_data(ifstream* infile);
Human* get_list(ifstream* infile);
ofstream get_stream_append(char* filename);
void exerciseA(Human* people, int list_size, int weight, int beginyear, int endyear);
void exerciseB(Human* people, int list_size, int height);
void exerciseC(Human* people, int list_size);

#endif //LAB7_2_HUMAN_H
