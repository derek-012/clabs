#include <iostream>
#include<fstream>
#include <cstring>
using namespace std;

int N = 8;

int main(){
    struct rB {
        char name[10];
        char ph[5];
    };
    int i, j, nr;
    ofstream f;
    char s[10];
    struct {
        bool b;
        union {
            short c;
            short d;
        };
    }a;
    f.open("LR9_1.txt", ios::binary);
    rB rBk;
    strcpy(rBk.name,"AA"); strcpy(rBk.ph,"2222");
    f.write((char*)&rBk, sizeof rBk);
    strcpy(rBk.name,"BBB"); strcpy(rBk.ph,"333");
    f.write((char*)&rBk, sizeof rBk);
    strcpy(rBk.name,"CC"); strcpy(rBk.ph,"444");
    f.write((char*)&rBk, sizeof rBk);
    f.close();
    ifstream ff ("LR9_1.txt",ios::binary);

    nr=sizeof(rB);
    a.c = N;
    a.d= 10 * N;
    cout << a.c << " " << a.d << "\n";

    for(int i = 0; i < 3; i++){
        ff.read((char*)&rBk, sizeof rBk);
        cout << rBk.name << " " << rBk.ph;
    }
    cout << "n=" << nr;
    cout << " " << rBk.name << "\n";
    ff.read((char*)&rBk, sizeof rBk);
    cout << rBk.ph << "\n";
    ff.close();

    return 0;
}
