#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <omp.h>

long long int N;
double sum, mini, maxi, sumvar;

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
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; i++)
        sum += A[i];
    return sum / N;
}

double max(double *A) {
    int i;
    double maxi = DBL_MIN;
    #pragma omp parallel for reduction(max:maxi)
    for (i = 0; i < N; i++)
        maxi = (A[i] > maxi) ? A[i] : maxi;
    return maxi;
}

double min(double *A) {
    int i;
    double mini = DBL_MAX;
    #pragma omp parallel for reduction(min:mini)
    for (i = 0; i < N; i++)
        mini = (A[i] < mini) ? A[i] : mini;
    return mini;
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

    rataan   = mean(A);
    maksimum = max(A);
    minimum  = min(A);

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
