#include <cstdio>
int main()
{
    int N = 8;
    FILE * fl;
    fl=fopen("L:\\projects\\CLionProjects\\CLabs\\Lab5\\lab5_1\\file.txt","w");
    double d, x; float f; long lng; int i, y; short s;
    d = f = lng = i = s =100/3*N;
    fprintf(fl,"s = %hd i = %d lng = %ld f = %f d = %f\n", s, i, lng, f, d);
    d = 3.2; i = 2; x = ( y = d *N / i )*2;
    fprintf(fl,"x = %lf ;y = %d\n", x, y);
}