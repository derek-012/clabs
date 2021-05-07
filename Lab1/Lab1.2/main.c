#include <stdio.h>
#include <math.h>

int main() {
    int radius = 2;
    int n = 6;

    double x[] = {-1.3, 3, -0.7, 1.9, 0.6, -2};
    double y[] = {0.7, -0, -0.4, 1.1, 1.2, 0};

    int r;

    for (int i = 0; i < n; i++) {
        r = 0;
        if(x[i] > 0) {
            if (y[i] < -x[i] + 2 && y[i] > x[i] - 2) {
                r = 1;
            }
        } else {
            if (radius*radius >= x[i]*x[i] + y[i]*y[i])
                r = 1;
        }
        printf("Result [%d] (x = %.2f; y = %.2f): %s\n", i, x[i], y[i], (r) ? "TRUE" : "FALSE");
    }

    return 0;
}
