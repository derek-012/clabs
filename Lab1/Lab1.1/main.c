#include <stdio.h>
#include <math.h>

int main() {
    int n = 5, m = 2;

    double r;
    printf("1) n/m++\n\tBefore: n = %d, m = %d", n, m);
    r = (double)n / m++;
    printf("\n\tResult: %f\n\tAfter: n = %d, m = %d\n\n", r, n, m);

    printf("2) m++<--n\n\tBefore: n = %d, m = %d", n, m);
    int b = m++<--n;
    printf("\n\tResult: %d\n\tAfter: n = %d, m = %d\n\n", b, n, m);

    printf("3) (m/n)++<n/m - not correct\n");

    printf("4) Function:");

    double nums[] = {3, 4, 7, 9};
    for (int i = 0; i < 4; i++) {
        double x = nums[i];
        r = sqrt(abs(x*x*x - 1)) - 7 * cos(pow(x, (double)4 / 3));
        printf("\n\tx = %.2f: %.5f", x, r);
    }

    return 0;
}
