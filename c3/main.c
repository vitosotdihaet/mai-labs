/* Курсовой проект №3, вариант №11        */
/* Студент гр. М8О-103Б-22 Клименко В. М. */

#include <stdio.h>
#include <math.h>

long double epsillon() {
    long double e = 1;
    long double eps;
    while(1 < (1 + e)){
        eps = e;
        e /= 2;
    }
    return eps;
}

unsigned long long factorial(unsigned long long a) {
    unsigned long long answ = 1;
    for (unsigned long long i = 1; i <= a; ++i) {
        answ *= i;
    }
    return answ;
}

long double mabs(long double a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

long double f(long double x) {
    return (1 - x * x/2) * cos(x) - x/2 * sin(x);
}

long double taylor(long double x, unsigned long long *iters, long double eps, long double k) {
    long double sum = 0, curr, next = 1, temp;
    for (unsigned long long i = 0; i <= 1000; ++i) {
        *iters = i;
        curr = next;
        next = pow(-1, i + 1) * (2 * pow(i + 1, 2) + 1) / (long double) factorial(2 * (i + 1)) * pow(x, 2 * (i + 1));
        temp = mabs(curr - next);
        if (temp < k * eps) {
            break;
        }
        sum += curr;
    }
    return sum;
}

int main() {
    unsigned long long n_t, n;
    long double eps = epsillon(), k = 1.5, a = 0.1, b = 0.6, x = a;

    printf("\nEnter number of x's iterations: ");
    scanf("%lld", &n);

    long double dx = (b - a) / (long double) n;

    printf("\n|x       |taylor's row           |native functions       |itrs\n");

    for (; x <= b; x += dx) {
        printf("|%.5Lf ", x);
        printf("|%.20Lf ", taylor(x, &n_t, eps, k));
        printf("|%.20Lf ", f(x));
        printf("|%3lld ", n_t);
        printf("\n");
    }
    printf("\nMachine-calculated epsillon = %.30Lf\n", eps);
    printf("Coefficient = %Lf\n\n", k);

    return 0;
}
