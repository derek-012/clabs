#include <iostream>
#include <cstring>
#include<cctype>
using namespace std;

const int N=4;

struct myType
{
    char fff[20];
    char aaa[20];
    int b;
    double c;
};

void printStruct(myType st[],int n){
    for (int i=0;i<n;i++){
        cout << " fff: " << st[i].fff << " aaa: "<< st[i].aaa ;
        cout << " b : " << st[i].b<<" c : " << st[i].c << endl;
    }
}

int main() {
    myType st[] = {{"assdss",   "ssdhshf", 4, 4.5},
                   {"jherhhgb", "xczvfdg", 9, 2.4},
                   {"xcvfd",    "hhgeryt", 5, 4.1},
                   {"jrhjdfd",  "tyyyyy",  7, 3.5}};
    printStruct(st, N);
    char t[20];
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j > i; j--) {
            if (strcmp(st[j].aaa, st[j - 1].aaa) < 0) {
                strcpy(t, st[j].aaa);
                strcpy(st[j].aaa, st[j - 1].aaa);
                strcpy(st[j - 1].aaa, t);
            }
        }
    }

    printf("\n\n");
    printStruct(st, N);
}