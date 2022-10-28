/* Лабораторная работа №9, вариант №13
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include<stdio.h>

short calc(long long i, long long j) {
    if ((i + 10)*(i + 10) + (j + 10)*(j + 10) <= 100
    &&  (i + 20)*(i + 20) + (j + 20)*(j + 20) <= 100) {
        return 1;
    }
    return 0;
}

long long max(long long a, long long b) {
    if (a > b) { return a; }
    return b;
}

long long min(long long a, long long b) {
    if (a < b) { return a; }
    return b;
}

long long abs(long long a) {
    if (a < 0) { return -a; }
    return a;
}

long long sign(long long a) {
    if (a >  0) { return  1; }
    if (a == 0) { return  0; } 
                  return -1;
}

long long mod(long long a, long long b) {
    // printf("%Lf -> %lld; %Lf -> %lld\n", a, na, b, nb);
    return a - a / b * b;
}

int main() {
    //! for writing i, j, k for graphics
    // FILE *fp;
    // fp = fopen("for_graphics.txt", "a");

    long long i[51] = {13}, j[51] = {-9}, l[51] = {-4}, ii, jj, ll;
    int kk;
    short gg = 0;

    // for (int x = 0; x < 51; ++x) {
    //     printf("%Lf ", l[x]);
    // }

    for (int k = 1; k < 50; ++k) {
        kk = k - 1;
        
        ii = i[kk];
        jj = j[kk];
        ll = l[kk];

        i[k] = mod(ii + jj, 30) / (mod(abs(ll), 5) + 1) + mod(ii + ll, 30)/(mod(abs(jj), 5) + 1);
        j[k] = mod(max(kk * ii, (kk + 1) * jj), 25) - abs(jj - ll)/10;
        l[k] = abs(jj - ll)/10 + min(mod(ii + ll, 20), mod(jj * kk, 20)) - 10;
        // fprintf(fp, "k = %d:\ni = %lld\nj = %lld\nl = %lld\n", k, i[k], j[k], l[k]);
        
        if (calc(i[k], j[k]) == 1) {
            printf("Point is in at k = %d!\ni = %lld\nj = %lld\nl = %lld\n", k, i[k], j[k], l[k]);
            gg = 1;
            break;
        }
    }

    if (gg == 0) {
        printf("Couldn't make it in 50 iterations! :(\n");
    }

    // fclose(fp);
    return 0;
}