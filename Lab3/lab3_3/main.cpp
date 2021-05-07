#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> random(1,80);

int** write_array(int n, int m) {
    int** array = new int*[n];
    for (int i = 0; i < n; i++) {
        array[i] = new int[m];
        for (int j = 0; j < m; j++) {
            array[i][j] = random(generator);
        }
    }
    return array;
}

int get_k(int n) {
    return random(generator) % n;
}

void check_k_num(int* k1, int* k2) {
    if (*k1 > *k2) {
        int buff = *k1;
        *k1 = *k2;
        *k2 = buff;
    }
}

int get_new_size(int n, int k1, int k2) {
    return n - (k2 - k1 + 1);
}

int** exercise(int** array, int n, int m, int k1, int k2) {
    int new_size = get_new_size(n, k1, k2);
    int k = 0;
    int** b = new int*[new_size];
    for (int i = 0; i < n; i++) {
        if (i < k1 || i > k2) {
            b[k++] = array[i];
        } else {
            delete[] array[i];
        }
    }
    return b;
}

void print_array(int** array, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 10;
    int m = 8;

    int k1 = get_k(n);
    int k2 = get_k(n);
    check_k_num(&k1, &k2);
    printf("K1 = %d\tK2 = %d\n\n", k1, k2);

    int** a = write_array(n, m);

    printf("Input array:\n");
    print_array(a, n, m);

    int** b = exercise(a, n, m, k1, k2);

    printf("Result:\n");
    print_array(b, get_new_size(n, k1, k2), m);
    return 0;
}
