#include <stdio.h>
#include <math.h>

#include<unistd.h>

long double mabs(long double a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

long double f1(long double x) {
    return powl(M_E, x) + sqrtl(1 + powl(M_E, 2*x)) - 2;
}

long double fd1(long double x) {
    return powl(M_E, x) + 1/(sqrtl(1 + powl(M_E, 2*x)));
}

long double fn1(long double x) {
    return logl(2 - sqrtl(1 + powl(M_E, 2*x)));
}


long double f2(long double x) {
    return logl(x) - x + 1.8;
}

long double fd2(long double x) {
    return 1/x - 1;
}

long double fn2(long double x) {
    return logl(x) + 1.8;
}

long double dichotomy(long double a, long double b, long double e, long double (*f) (long double)) {
    long double c = (a + b) / 2., fb = f(b), fc = f(c);
    long double answ;
    if (c + e > b) { // same as x ≈ (ak + bk)/2
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


long double iterations(long double x, long double e, long double (*f) (long double), long double (*fn) (long double)) {
    long double fx = fn(x);
    if (mabs(x - fx) < e) {
        return x;
    }
    return iterations(fx, e, f, fn);
}

long double newton(long double x, long double e, long double (*f) (long double), long double (*fd) (long double)) {
    long double fx = x - f(x)/fd(x);
    if (mabs(x - fx) < e) {
        return fx;
    }
    return newton(fx, e, f, fd);
}


long double calc_eps() {
    long double e = 1;
    long double eps;
    while(1 < (1 + e)){
        eps = e;
        e /= 2;
    }
    return eps;
}

int main() {
    long double eps = calc_eps(), k = 1.;

    long double a1 = -1., b1 = 0.;
    long double a2 = 2., b2 = 3.;

    long double d1 = dichotomy(a1, b1, k * eps, f1), d2 = dichotomy(a2, b2, k * eps, f2);
    long double i1 = iterations((a1 + b1)/2., k * eps * 10000., f1, fn1), i2 = iterations((a2 + b2)/2., k * eps, f2, fn2);
    long double n1 = newton((a1 + b1)/2., k * eps, f1, fd1), n2 = newton((a2 + b2)/2., k * eps * 10., f2, fd2);

    printf("___________________________________________________________________________________________\n");
    printf("Function:                  | Method:    | Root:                   | Function at found x:   \n");
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Dichotomy  | %.20Lf | %.21Lf\n", d1, f1(d1));
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Iterations | %.20Lf | %.21Lf\n", i1, f1(d1));
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Newton     | %.20Lf | %.21Lf\n", n1, f1(d1));
    printf("lnx - x + 1.8              | Dichotomy  | %.21Lf | %.21Lf\n", d2, f2(d2));
    printf("lnx - x + 1.8              | Iterations | %.21Lf | %.21Lf\n", i2, f2(d2));
    printf("lnx - x + 1.8              | Newton     | %.21Lf | %.21Lf\n", n2, f2(d2));

    return 0;
}