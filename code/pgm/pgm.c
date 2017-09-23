#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int w;      // width
    int h;      // height
    int lv;     // max gray level
    int **P;    // the pixels
} pgm_t;

typedef enum
{
    ROBERTS,
    PREWITT,
    SOBEL,
    SCHARR
} pgm_filter_t;

int** pgm_P_alloc(int h, int w) {
    int **P;
    P = calloc(h, sizeof(int*));
    for (int i = 0; i < h; i++)
        P[i] = calloc (w, sizeof(int));
    return P;
}

void pgm_P_free(int** P, int h) {
    for (int i = 0; i < h; i++)
        free(P[i]);
    free(P);
    P = NULL;
}

pgm_t pgm_read(char* filename)
{
    int w, h, lv, i, j;
    int **P;
    FILE *in;

    in = (filename) ? fopen(filename, "r") : stdin;

    // FIXME: no comment lines allowed
    fscanf(in, "P2\n%d %d\n%d\n", &w, &h, &lv);

    // pixels allocation: h x w
    P = pgm_P_alloc(h, w);

    // read the pixels
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            fscanf(in, "%d", &P[i][j]);

    if (filename) fclose(in);

    return (pgm_t) {w, h, lv, P};
}

void pgm_write(pgm_t img, char* filename)
{
    int i, j;
    FILE *out;

    out = (filename) ? fopen(filename, "w") : stdout;

    fprintf(out, "P2\n");
    fprintf(out, "%d %d\n", img.w, img.h);
    fprintf(out, "%d\n", img.lv);
    for (i = 0; i < img.h; i++) {
        for (j = 0; j < img.w; j++)
            fprintf(out, "%d ", img.P[i][j]);
        fprintf(out, "\n");
    }

    if (filename) fclose(out);
}

void pgm_threshold(pgm_t img, int thr)
{
    int i, j;
    for (i = 0; i < img.h; i++)
        for (j = 0; j < img.w; j++)
            img.P[i][j] = (img.P[i][j] < thr)? 0 : img.lv;
}

void pgm_invert(pgm_t img)
{
    int i, j;
    for (i = 0; i < img.h; i++)
        for (j = 0; j < img.w; j++)
            img.P[i][j] = img.lv - img.P[i][j];
}

pgm_t pgm_convolve(pgm_t img, double kernel[3][3])
{
    int i, j, x, y;
    int **P;

    P = pgm_P_alloc(img.h, img.w);

    for (i = 1; i < img.h-1; i++)
        for (j = 1; j < img.w-1; j++)
            for (y = -1; y <= 1; y++)
                for (x = -1; x <= 1; x++)
                    P[i][j] += img.P[i+y][j+x] * kernel[y+1][x+1];

    return (pgm_t) { img.w, img.h, img.lv, P };
}

void pgm_edge(pgm_t img, pgm_filter_t filter)
{
    pgm_t x, y;
    int i, j;
    double roberts_x[3][3] = {{ 0,  0,  0}, { 0,  1,  0}, { 0,  0, -1}};
    double roberts_y[3][3] = {{ 0,  0,  0}, { 0,  0,  1}, { 0, -1,  0}};
    double prewitt_x[3][3] = {{ 1,  0, -1}, { 1,  0, -1}, { 1,  0, -1}};
    double prewitt_y[3][3] = {{ 1,  1,  1}, { 0,  0,  0}, {-1, -1, -1}};
    double sobel_x[3][3]   = {{ 1,  0, -1}, { 2,  0, -2}, { 1,  0, -1}};
    double sobel_y[3][3]   = {{ 1,  2,  1}, { 0,  0,  0}, {-1, -2, -1}};
    double scharr_x[3][3]  = {{ 3,  0, -3}, {10,  0,-10}, { 3,  0, -3}};
    double scharr_y[3][3]  = {{ 3, 10,  3}, { 0,  0,  0}, {-3,-10, -3}};

    switch (filter) {
        case ROBERTS:
            x = pgm_convolve(img, roberts_x);
            y = pgm_convolve(img, roberts_y);
            break;
        case PREWITT:
            x = pgm_convolve(img, prewitt_x);
            y = pgm_convolve(img, prewitt_y);
            break;
        case SOBEL:
            x = pgm_convolve(img, sobel_x);
            y = pgm_convolve(img, sobel_y);
            break;
        case SCHARR:
            x = pgm_convolve(img, scharr_x);
            y = pgm_convolve(img, scharr_y);
            break;
    }

    for (i = 0; i < img.h; i++)
        for (j = 0; j < img.w; j++)
            img.P[i][j] = sqrt((x.P[i][j] * x.P[i][j]) + (y.P[i][j] * y.P[i][j]));

    pgm_P_free(x.P, img.h);
    pgm_P_free(y.P, img.h);
}

void pgm_rotate_180(pgm_t img)
{
    int **P, i, j;

    P = pgm_P_alloc(img.h, img.w);

    for (i = 0; i < img.h; i++)
        for (j = 0; j < img.w; j++)
            P[i][j] = img.P[i][j];                      // copy

    for (i = 0; i < img.h; i++)
        for (j = 0; j < img.w; j++)
            img.P[i][j] = P[img.h-i-1][img.w-j-1];

    pgm_P_free(P, img.h);
}

int main()
{
    pgm_t img;

    img = pgm_read("bogor.pgm");
    //pgm_rotate_180(img);
    //pgm_write(img, "rotate.pgm");
    pgm_edge(img, SOBEL);
    pgm_write(img, "sobel.pgm");
    //pgm_write(img2, "rotate2.pgm");

    return 0;
}
