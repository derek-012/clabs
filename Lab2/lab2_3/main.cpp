#include <iostream>

using namespace std;
int N = 8;
int* form(int &n) {
    n = 10 + N % 10;
    int *a = new int[n];
    *a = N;
    for(int i = 1; i < n; i++)
        *(a+i) = *(a+i-1) + 1;
    return a;
}

int main(){
    int *a, n,i,*p;
    a=form(n);
    for (int k = 0; k < n; k++) {
        printf("a[%d] = %d;\n", k, *(a+k));
    }
    for (p = &a[0], i = 0 ; i <n; i++ )
    {
        *(p+i) -= N * N;
    }
    for (int k = 0; k < n; k++) {
        printf("a[%d] = %d;\tp[%d] = %d\n", k, *(a+k), k, *(p+k));
    }
    return 0;
}