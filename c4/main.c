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
    return pow(M_E, x) + sqrt(1 + pow(M_E, 2*x)) - 2;
}

long double fp1(long double x) {
    return pow(M_E, x) + 1/(sqrt(1 + pow(M_E, 2*x)));
}

long double f2(long double x) {
    return log(x) - x + 1.8;
}

long double fp2(long double x) {
    return 1/x - 1;
}

long double dichotomy(long double a, long double b, long double e, long double (*f) (long double)) {
    long double c = (a + b) / 2., fa = f(a), fb = f(b), fc = f(c);
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

long double iterations1(long double x, long double e) {
    long double fx = log(2 - sqrt(1 + pow(M_E, 2*x)));
    if (mabs(x - fx) < e) {
        return x;
    }
    return iterations1(fx, e);
}

long double iterations2(long double x, long double e) {
    long double fx = log(x) + 1.8;
    if (mabs(x - fx) < e) {
        return x;
    }
    return iterations2(fx, e);
}

long double newton1(long double x, long double e) {
    long double fx = x - f1(x)/fp1(x);
    if (mabs(x - fx) < e) {
        return fx;
    }
    return newton1(fx, e);
}

long double newton2(long double x, long double e) {
    long double fx = x - f2(x)/fp2(x);
    if (mabs(x - fx) < e) {
        return fx;
    }
    return newton2(fx, e);
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

    printf("_________________________________________________________________\n");
    printf("Function:                  | Methods:   | Root:                  \n");
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Dichotomy  | %.20Lf\n", dichotomy(a1, b1, k * eps, f1));
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Iterations | %.20Lf\n", iterations1((a1 + b1)/2., k * eps * 10000.));
    printf("e^x + sqrt(1 + e^(2x)) - 2 | Newton     | %.20Lf\n", newton1((a1 + b1)/2., k * eps * 10.));
    printf("lnx - x + 1.8              | Dichotomy  | %.20Lf\n", dichotomy(a2, b2, k * eps, f2));
    printf("lnx - x + 1.8              | Iterations | %.20Lf\n", iterations2((a2 + b2)/2., k * eps * 10000.));
    printf("lnx - x + 1.8              | Newton     | %.20Lf\n", newton2((a2 + b2)/2., k * eps * 10.));

    return 0;
}