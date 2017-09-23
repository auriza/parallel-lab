#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <omp.h>

long long int N;

double *generate() {
    double *A;
    int i;
    A = malloc(N * sizeof(double));
    for (i = 0; i < N; i++)
        A[i] = rand()%100;
    return A;
}

void print(double *A) {
    int i;
    for (i = 0; i < N; i++)
        printf("%g ", A[i]);
}

double mean(double *A) {
    int i;
    double sum = 0;
    for (i = 0; i < N; i++)
        sum += A[i];
    return sum / N;
}

double max(double *A) {
    int i;
    double max = DBL_MIN;
    for (i = 0; i < N; i++)
        max = (A[i] > max) ? A[i] : max;
    return max;
}

double min(double *A) {
    int i;
    double min = DBL_MAX;
    for (i = 0; i < N; i++)
        min = (A[i] < min) ? A[i] : min;
    return min;
}

double variance(double *A, double mean) {
    double sumvar = 0;
    int i;
    #pragma omp parallel for reduction(+:sumvar)
    for (i = 0; i < N; i++)
        sumvar += (A[i] - mean) * (A[i] - mean);
    return sumvar / N;
}

int main(int argc, char* argv[]) {
    double *A;
    double rataan, maksimum, minimum, ragam, dev_std;
    double time;

    N = atoll(argv[1]);
    A = generate();

    time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        rataan   = mean(A);

        #pragma omp section
        maksimum = max(A);

        #pragma omp section
        minimum  = min(A);
    }

    ragam    = variance(A, rataan);
    dev_std  = sqrt(ragam);

    time = omp_get_wtime() - time;

    printf("Rataan      : %f\n", rataan);
    printf("Maksimum    : %f\n", maksimum);
    printf("Minimum     : %f\n", minimum);
    printf("Ragam       : %f\n", ragam);
    printf("Deviasi std : %f\n", dev_std);
    printf("Waktu       : %f\n", time);

    return 0;
}
