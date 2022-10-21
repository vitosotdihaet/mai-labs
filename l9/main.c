/* Лабораторная работа №9, вариант №13
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include<stdio.h>

short calc(long double i, long double j) {
    if ((i + 10)*(i + 10) + (j + 10)*(j + 10) <= 100
    &&  (i + 20)*(i + 20) + (j + 20)*(j + 20) <= 100) {
        return 1;
    }
    return 0;
}

long double max(long double a, long double b) {
    if (a > b) { return a; }
    return b;
}

long double min(long double a, long double b) {
    if (a < b) { return a; }
    return b;
}

long double abs(long double a) {
    if (a < 0) { return -a; }
    return a;
}

long double sign(long double a) {
    if (a >  0) { return  1; }
    if (a == 0) { return  0; } 
                  return -1;
}

long double mod(long double a, long double b) {
    long long na = a;
    long long nb = b;
    // printf("%Lf -> %lld; %Lf -> %lld\n", a, na, b, nb);
    return na - na / nb * nb;
}

int main() {
    long double i[51] = {13.}, j[51] = {-9.}, l[51] = {-4.}, ii, jj, ll;
    int kk;
    short gg = 0;

    // for (int x = 0; x < 51; ++x) {
    //     printf("%Lf ", l[x]);
    // }

    for (int k = 1; k <= 50; ++k) {
        kk = k - 1;
        ii = i[kk];
        jj = j[kk];
        ll = l[kk];
        i[k] = mod(ii + jj, 30.0) / (mod(abs(ll), 5.0) + 1.0) + mod(ii + ll, 30.0)/(mod(abs(jj), 5.0) + 1.0);
        j[k] = mod(max(kk * ii, (kk + 1.0) * jj), 25.0) - abs(jj - ll)/10.0;
        l[k] = abs(jj - ll)/10.0 + min(mod(ii + ll, 20.0), mod(jj * kk, 20.0)) - 10.0;
        // printf("here are your nums at %d:\ni = %Lf\nj = %Lf\nl = %Lf\n", k, i[k], j[k], l[k]);
        if (calc(i[k], j[k]) == 1) {
            printf("Point is in at k = %d!\ni = %Lf\nj = %Lf\nl = %Lf\n", k, i[k], j[k], l[k]);
            gg = 1;
            break;
        }
    }

    if (gg == 0) {
        printf("Couldn't make it in 50 iterations! :(\n");
    }

    return 0;
}