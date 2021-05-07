#include <iostream>
#include <random>

int main() {
    std::random_device rd;

    int n = rd() % 20 + 10;
    printf("Array size = %d", n);
    int *a;
    a = new int[n];

    printf("\n\nInput array:");
    for (int i = 0; i < n; i++) {
        *(a+i) = rd() % 90 + 10;
        printf(" %d", *(a+i));
    }

    printf("\n\nProcessed array:");
    int min;
    int buff;
    for (int i = 1; i < n; i += 2) {
        min = i;
        for (int j = i + 2; j < n; j += 2)
            if (*(a+j) < *(a+min))
                min = j;

        if (min != i) {
            buff = *(a+i);
            *(a+i) = *(a+min);
            *(a+min) = buff;
        }
    }
    for (int i = 0; i < n; i++) {
        printf(" %d", *(a+i));
    }

    printf("\n\nOutput array:");
    int* b;
    b = new int[n/2];
    for (int i = 1, j = 0; i < n; i += 2, j++)
        *(b+j) = *(a+i);
    delete a;
    for (int i = 0; i < n/2; i++) {
        printf(" %d", *(b+i));
    }
    return 0;
}
