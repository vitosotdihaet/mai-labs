#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b) ? (a) : (b)

void printmd(long long** m, long long n) {
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            printf("%lld ", m[i][j]);
        }
        printf("\n");
    }
}

void foo(long long** m, long long n, long long a) {
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            if (i < j + 1) {
                m[i][j] *= a;
            }
        }
    }
    printmd(m, n);
}

int main() {
    long long n, maxi;

    while (scanf("%lld", &n) != EOF) {
        long long** m = (long long**) malloc(n * sizeof(long long*));
        maxi = 0;
        for (long long i = 0; i < n; ++i) {
            m[i] = (long long*) malloc(sizeof(long long) * n);
        }

        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                scanf("%lld", &m[i][j]);
                if (j < i + 1) {
                    maxi = max(m[i][j], maxi);
                }
            }
        }

        printf("\n");
        foo(m, n, maxi);
        printf("\n");
    }

    printf("End of program.\n");

    return 0;
}
