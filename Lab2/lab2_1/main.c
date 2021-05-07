#include <stdio.h>

int main() {
    int n = 15;
    int p[15], a[15];
    p[0] = 8;
    for (int i = 1; i < n; ++i)
        p[i] = (p[i-1] * 11 + 7) % 100;
    for (int i = 0; i < n; i++)
        a[i] = p[i] - 50;

    for (int i = 1; i < n; i++) {
        int curr = a[i];
        int j = i-1;
        while (j >= 0 && a[j] > curr) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = curr;
    }

    printf("X = %d", a[0]);

    return 0;
}
