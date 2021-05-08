#include <iostream>
#include <windows.h>

unsigned long long func(int n, int i = 1, int x_prev = 1) {
    int x = 3 * x_prev + 1;
    if (i < n)
        return x * func(n, i+1, x);
    else
        return x;
}

int main() {
    SetConsoleOutputCP( 65001 );
    printf("Введите количество элементов: ");
    int n;
    scanf("%d", &n);
    printf("Сложение первых %d элементов: %llu", n, func(n));
    return 0;
}
