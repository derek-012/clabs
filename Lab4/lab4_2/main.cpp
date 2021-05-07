#include <iostream>
#include <cstring>

const int n = 4;

struct Human {
    char name[60];
    int birthyear;
    int height;
    int weight;
    int gender;
};

void printHuman(Human human) {
    printf("%s:\n\tBirth year: %d\n\tHeight: %dcm\n\tWeight: %dkg\n\tGender: %s\n",
           human.name, human.birthyear, human.height, human.weight, (human.gender == 0) ? "male" : "female");
}

void exerciseA(Human* people, int weight, int beginyear, int endyear) {
    printf("Exercise A: human with weight more %d, and birth year between %d and %d.\nHumans:\n",
           weight, beginyear, endyear);
    int count = 0;
    for(int i = 0; i < n; i++) {
        if (people[i].weight > weight && people[i].birthyear >= beginyear && people[i].birthyear <= endyear) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("None");
}

void exerciseB(Human* people, int height) {
    printf("Exercise B: women with height %d.\nWomen:\n", height);
    int count = 0;
    for(int i = 0; i < n; i++) {
        if (people[i].gender == 1 && people[i].height == height) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("None");
}

void exerciseC(Human* people) {
    printf("Exercise C: information about people is alphabetic.\nPeople:\n");

    int l[n] = {0, 1, 2, 3};
    int t;
    for(int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
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

int main() {
    Human people[n] = {
            {"Philander Pamela Addison", 1983, 184, 71, 1},
            {"Tillie Adalynn Abbott", 1998, 169, 64, 1},
            {"Aubrey Shantel Hutson", 1994, 172, 54, 1},
            {"Paxton Bernie Cason", 1986, 178, 82, 0}
    };
    exerciseA(people, 50, 1990, 2000);
    printf("\n");
    exerciseB(people, 169);
    printf("\n");
    exerciseC(people);
    return 0;
}
