#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

string printbin(int num) {
    string result;
    int i = 134217728;
    while (true) {
        if (num & i)
            result.append("1");
        else
            result.append("0");
        if (i == 1) break;
        i >>= 1;
    }
    return result;
}

int main() {
    SetConsoleOutputCP( 65001 );
    int A;
    unsigned int x;

    cout << "Введите число A: ";
    cin >> A;
    cout <<"Введите x: ";
    cin >> x;
    cout << endl;

    A = A << x;
    cout << "В двоичной: " << printbin(A) << endl;
    cout << "В восьмеричной: " << oct << A << endl;
    cout << "В десятичной: " << dec << A << endl;
    cout << "В шестнадцатеричной: " << hex << A;
    return 0;
}
