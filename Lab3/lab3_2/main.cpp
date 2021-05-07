#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> random(1,100);

int** write_matrix(int n, int m) {
    int** array = new int*[n];
    for (int i = 0; i < n; i++) {
        array[i] = new int[m];
        for (int j = 0; j < m; j++)
            array[i][j] = random(generator);
    }
    return array;
}

int* exercise(int** matrix, int n, int m) {
    int* vector = new int[n];
    int min, max;
    for (int i = 0; i < n; i++) {
        max = min = matrix[i][0];
        for (int j = 1; j < m; j++) {
            if (max < matrix[i][j]) max = matrix[i][j];
            if (min > matrix[i][j]) min = matrix[i][j];
        }
        vector[i] = min + max;
    }
    return vector;
}

void print_matrix(int** array, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    }
}

void print_vector(int* array, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}

int main() {
    int N = 16;
    int M = 5;

    int** a;
    a = write_matrix(N, M);

    int* b;
    b = exercise(a, N, M);

    printf("Array A:\n");
    print_matrix(a, N, M);

    printf("\nVector B: ");
    print_vector(b, N);

    return 0;
}
