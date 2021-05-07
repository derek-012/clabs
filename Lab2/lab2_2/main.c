#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 25;
    int numbers[n];
    printf("Input array:");
    for (int i = 0; i < n; i++)
        printf(" %d", numbers[i] = rand() % 90 + 10);

    int min;
    int buff;
    for (int i = 1; i < n; i += 2) {
        min = i;
        for (int j = i + 2; j < n; j += 2) {
            if (numbers[j] < numbers[min])
                min = j;
        }
        if (min != i) {
            buff = numbers[i];
            numbers[i] = numbers[min];
            numbers[min] = buff;
        }
    }

    printf("\nOutput array:");
    for (int i = 0; i < n; ++i) {
        printf(" %d", numbers[i]);
    }
    return 0;
}

