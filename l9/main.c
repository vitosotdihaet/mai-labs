/* Лабораторная работа №9, вариант №13
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

short calc(int i, int j) {
    if ((i + 10)*(i + 10) + (j + 10)*(j + 10) <= 100
    &&  (i + 20)*(i + 20) + (j + 20)*(j + 20) <= 100) {
        return 1;
    }
    return 0;
}

int max(int a, int b) {
    if (a > b) { return a; }
    return b;
}

int min(int a, int b) {
    if (a < b) { return a; }
    return b;
}

int sign(int a) {
    if (a >  0) { return  1; }
    if (a == 0) { return  0; } 
                  return -1;
}

int mod(int a, int b) {
    int fl = floor((double) a / (double) b);
    return a - fl * b;
}

int main() {
    //! for writing i, j, k for graphics
    FILE *fp;
    fp = fopen("for_graphics.txt", "w");

    int ik = 13, jk = -9, lk = -4, ii, jj, ll, kk;
    short gg = 0;

    for (int k = 1; k < 50; ++k) {
        kk = k - 1;
        ii = ik;
        jj = jk;
        ll = lk;

        ik = mod(ii + jj, 30) / (mod(abs(ll), 5) + 1) + mod(ii + ll, 30)/(mod(abs(jj), 5) + 1);
        jk = mod(max(kk * ii, (kk + 1) * jj), 25) - abs(jj - ll)/10;
        lk = abs(jj - ll)/10 + min(mod(ii + ll, 20), mod(jj * kk, 20)) - 10;
        fprintf(fp, "k = %d:\ni = %d\nj = %d\nl = %d\n", k, ik, jk, lk);
        
        if (calc(ik, jk) == 1) {
            printf("Point is in at k = %d!\ni = %d\nj = %d\nl = %d\n", k, ik, jk, lk);
            gg = 1;
            break;
        }
    }

    if (gg == 0) {
        printf("Couldn't make it in 50 iterations! :(\n");
        printf("Last point:\ni = %d\nj = %d\nl = %d\n", ik, jk, lk);
    }

    fclose(fp);
    return 0;
}