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
    long long fl = floor((double) a / (double) b); 
    return a - fl * b;
}

long long floor(double x) {
    if (x - (long long) x >= 0) {
        return (long long) x;
    }
    return (long long) x - 1;
}

int main() {
    //! for writing i, j, k for graphics
    FILE *fp;
    fp = fopen("for_graphics.txt", "w");

    long long ip = 13, jp = -9, lp = -4, ii, jj, ll;
    int kk;
    short gg = 0;

    for (int k = 1; k < 50; ++k) {
        kk = k - 1;
        
        ii = ip;
        jj = jp;
        ll = lp;

        ip = mod(ii + jj, 30) / (mod(abs(ll), 5) + 1) + mod(ii + ll, 30)/(mod(abs(jj), 5) + 1);
        jp = mod(max(kk * ii, (kk + 1) * jj), 25) - abs(jj - ll)/10;
        lp = abs(jj - ll)/10 + min(mod(ii + ll, 20), mod(jj * kk, 20)) - 10;
        fprintf(fp, "k = %d:\ni = %lld\nj = %lld\nl = %lld\n", k, ip, jp, lp);
        
        if (calc(ip, jp) == 1) {
            printf("Point is in at k = %d!\ni = %lld\nj = %lld\nl = %lld\n", k, ip, jp, lp);
            gg = 1;
            break;
        }
    }

    if (gg == 0) {
        printf("Couldn't make it in 50 iterations! :(\n");
    }

    fclose(fp);
    return 0;
}