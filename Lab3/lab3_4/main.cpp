#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> random(1,80);

int** write_array(int n, int def) {
    int** array = new int*[n];
    for (int i = 0; i < n; i++) {
        array[i] = new int[n];
        for (int j = 0; j < n; j++) {
            array[i][j] = (i + j < n) ? random(generator) : def;
        }
    }
    return array;
}

void print_array(int** array, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

void change_numbers(int* num1, int* num2) {
    int buff;
    buff = *num1;
    *num1 = *num2;
    *num2 = buff;
}

void exercise(int** array, int n) {
    int check = 0;
    int* prev;
    while (!check) {
        check = 1;
        prev = &array[0][0];
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                if ((i + j < n) && *prev > array[i][j]) {
                    change_numbers(prev, &array[i][j]);
                    check = 0;
                }
                prev = &array[i][j];
            }
        }
    }
}

int main() {
    int def = 8;
    int n = 8;

    int** a = write_array(n, def);

    printf("Input array:\n");
    print_array(a, n);

    exercise(a, n);

    printf("Output array:\n");
    print_array(a, n);

    return 0;
}
