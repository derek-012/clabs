#include <iostream>
#include <stdio.h>
#include <string>

char fin[] = "L:\\projects\\CLionProjects\\CLabs\\Lab5\\lab5_2\\data.txt";
char fout1[] = "L:\\projects\\CLionProjects\\CLabs\\Lab5\\lab5_2\\result1.txt";
char fout2[] = "L:\\projects\\CLionProjects\\CLabs\\Lab5\\lab5_2\\result2.txt";

struct Passenger {
    char name[60];
    int count;
    int weight;
};

struct PassengerList {
    Passenger *data;
    PassengerList *next;
};

PassengerList *head;

Passenger* readOne(FILE *fl) {
    if (feof(fl)) {
        return nullptr;
    }

    char buff;

    Passenger *p = new Passenger;
    int i = 0;
    while (true) {
        buff = (char) fgetc(fl);
        if (buff != ',')
            p->name[i++] = buff;
        else
            break;
    }

    p->name[i] = '\0';

    char number[6], *end;
    fscanf(fl, "%s,", number);
    p->count = strtol(number, &end, 10);
    fscanf(fl, "%s\n", number);
    p->weight = strtol(number, &end, 10);

    return p;
}

void printOne(Passenger *p) {
    printf("%s, %d, %d\n", p->name, p->count, p->weight);
}

void read(FILE *fl) {
    head = new PassengerList;
    head->data = readOne(fl);
    PassengerList *current;
    PassengerList *prev = head;
    Passenger *p;
    while (true) {
        p = readOne(fl);
        if (p == nullptr)
            break;
        current = new PassengerList;
        current->data = p;
        current->next = nullptr;
        prev->next = current;
        prev = current;
    }
}

void printAll(PassengerList *list) {
    PassengerList *current = list;
    while (true) {
        if (current != nullptr)
            printOne(current->data);
        else
            break;
        current = current->next;
    }
}

void writeOne(FILE *fl, Passenger *p) {
    fprintf(fl, "%s, %d, %d\n", p->name, p->count, p->weight);
}

void writeExercise1(FILE *fl) {
    PassengerList *current = head;

    while (current != nullptr) {
        if (current->data->count <= 2)
            writeOne(fl, current->data);
        current = current->next;
    }
}

void writeExercise2(FILE *fl) {
    PassengerList *current = head;
    int sum = 0;
    int count;
    for (count = 0; current != nullptr; count++, current = current->next) {
        sum += current->data->count;
    }

    int average = sum / count;

    current = head;

    while (current != nullptr) {
        if (current->data->count > average)
            writeOne(fl, current->data);
        current = current->next;
    }
}

int main() {
    FILE *fl;
    fl = fopen(fin, "r");
    read(fl);
    printAll(head);
    FILE *flout1, *flout2;

    flout1 = fopen(fout1, "w+");
    writeExercise1(flout1);

    flout2 = fopen(fout2, "w+");
    writeExercise2(flout2);

    fclose(fl);
    fclose(flout1);
    fclose(flout2);
    return 0;
}
