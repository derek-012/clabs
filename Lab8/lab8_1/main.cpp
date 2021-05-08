#include <iostream>
using namespace std;

int N = 8;

int f(int n, int i = 2) {
    if (n <= 1) return false;
        else if (n == 2) return true;
            else if (n % i == 0) return false;
                else
                    if (i < n / 2) return f(n, i + 1);
                        else return true;
}
int main() {
    cout<<"f="<<f(10+N)<<"\n";
    cout<<"f="<<f(11)<<"\n";
    cout<<"f="<<f(12)<<"\n";
    return 0;
}