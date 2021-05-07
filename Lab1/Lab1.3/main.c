#include <stdio.h>

int main() {
    FILE* f;

    if ((f = fopen("numbers.txt", "r")) == NULL) {
        printf("File not found.");
        return 1;
    }

    int min, max;
    int buff;
    fscanf(f, "%d ", &buff);
    min = buff;
    max = buff;

    while (!feof(f)) {
        fscanf(f, "%d ", &buff);
        if (buff == 0) break;
        if (min > buff) min = buff;
        if (max < buff) max = buff;
    }

    printf("Min = %d\nMax = %d\nSum = %d", min, max, min + max);

    return 0;
}
