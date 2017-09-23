#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define PI 3.141592653589793238462643

int main(int argc, char* argv[])
{
    int a, b;
    long long int i, n;
    long double x, y, dx, area;

    n = atoll(argv[1]);                 // jumlah rectangle
    a = 0;                              // batas bawah
    b = 1;                              // batas atas
    dx = (double) (b-a) / n;            // lebar rectangle
    area = 0.0;

    double time = omp_get_wtime();

    #pragma omp parallel for private(x,y) reduction(+:area)
    for (i = 0; i < n; i++) {
        x = a + (i + 0.5) * dx;             // midpoint
        y = (4.0 / (1.0 + x*x));            // f(x) = 4 / (1+x^2)
        area += y * dx;
    }

    time = omp_get_wtime() - time;

    printf("%lf\n", time);
    return 0;
}
