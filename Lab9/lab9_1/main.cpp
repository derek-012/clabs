#include <cstdio>

int N = 8;

int main () {
    unsigned int a= N & 0xFFFE;
    int b;
    printf ("The shifted number is %u\n", a);
    printf ("Enter the shift direction: left (0) and right(1) \n");
    scanf ("%d", &b);
    if (!b)
        a = a << 11;
        //a = a << ((N^3)&(N|3));
    else
        a = a >> 1;
    printf ("The shifted number is %u\n", a);
    return 0;
}