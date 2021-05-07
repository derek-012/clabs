#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double EPS = 0.000001;

double calc(double x) {
    double result = 1;
    double r = 1;
    double temp;
    int i = 1;
    do {
        r *= (0.5 - (i - 1)) / i;
        temp = r * pow(x, i++);
        result += temp;
    } while (fabs(temp) > EPS);
    return result;
}

int main() {
    double x;
    char* buff;
    buff = malloc(20);
    while (1) {
        printf("Enter x (-1;1) :");
        scanf("%s", buff);
        if ((x = strtod(buff, &buff)) != 0 && (fabs(x) < 1.0))
            break;
        printf("Not correct double number. Try again.\n\n");
    }

    long int e;
    while(1) {
        printf("Enter EPS:");
        scanf("%s", buff);
        if ((e = strtol(buff, &buff, 10)) != 0)
            break;
        printf("Not correct integer number. Try again.\n\n");
    }

    EPS = pow(10, -e);
    printf("EPS = %lf\n\n", EPS);
    printf("result = %lf\n", calc(x));
    return 0;
}
