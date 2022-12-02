#include <stdio.h>
#include <math.h>

long double mabs(long double a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

long double f1(long double x) {
    return pow(M_E, x) + sqrt(1 + pow(M_E, 2*x)) - 2;
}

long double f2(long double x) {
    return log(x)/log(M_E) - x + 1.8;
}

long double dichotomy(long double a, long double b, long double e, long double (*f) (long double)) {
    long double c = (a + b) / 2., fa = f(a), fb = f(b), fc = f(c);
    // printf("%.10Lf, %.10Lf, %.10Lf\n", a, b, c);
    // printf("%.50Lf <? %.50Lf\n", mabs(fa - fb), e);
    long double answ;
    if (mabs(fa - fb) < e) {
        answ = c;
    } else if ((fc * fb) < 0) {
        answ = dichotomy(c, b, e, f);
    } else if ((fc * fb) > 0) {
        answ = dichotomy(a, c, e, f);
    } else {
        answ = c;
    }
    return answ;
}

long double calc_eps() {
    long double e = 1;
    long double eps;
    while(1 < (1 + e)){
        eps = e;
        e /= 1.5;
    }
    return eps;
}

int main() {
    long double eps = calc_eps(), k = 1.;
    long double a1 = -1., b1 = 0.;
    long double a2 = 2., b2 = 3.;

    printf("______________________________________________________________\n");
    printf("Function:                 | Methods:   | Root:               \n");
    printf("e^x + sqrt(1 + e^(2x) - 2 | Dichotomy: | %.20Lf\n", dichotomy(a1, b1, k * eps, f1));
    printf("lnx - x + 1.8             | Dichotomy: | %.20Lf\n", dichotomy(a2, b2, k * eps, f2));


    return 0;
}