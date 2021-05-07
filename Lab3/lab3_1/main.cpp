#include <iostream>
#include <iomanip>

const int N=8;
using namespace std;

int** form_matr(int n){
    int **matr=new int*[n];
    for(int i=0;i<n;i++)
        matr[i]=new int [n];
    return matr;
}

void zapolnen(int ** matr,int n){
    int p=N;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            matr[i][j]=p++;
        }
}

void printArray (int ** matr,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<setw(5)<<matr[i][j];
        cout<<"\n";}
}

int main() {
    int n;
    n = 10 + N % 10;
    int **matr = form_matr(n);
    zapolnen(matr, n);
    printArray(matr, n);
    int t;
    for (int i = 0; i < n; i++)
        for (int j = i; j <= n - i - 1; j++) {
            t = matr[i][j];
            matr[i][j] = matr[n - i - 1][j];
            matr[n - i - 1][j] = t;
        }
    printf("\n\n");
    printArray(matr, n);
    return 0;
}