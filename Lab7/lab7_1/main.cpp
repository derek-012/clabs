#include <iostream>
using namespace std;
#define concat(a,b) a##b

int main()
{
    int ij = 30;
    cout << concat(i,j);
    return 0;
}