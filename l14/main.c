#include <stdio.h>
#include <stdlib.h>

void printmd(long long** m, long long n) {
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            printf("%lld ", m[i][j]);
        }
        printf("\n");
    }
}

void printm(long long** m, long long n) {
    long long j1 = n - 1, j2 = 1;

    while (1) {
        if (j1 > -1) {
            long long  i = 0, j = j1;
            for (; j > -1; --j) {
                printf("%lld ", m[i][j]);
                ++i;
            }
            i -= 2;
            ++j;
            for (; i > -1; --i) {
                printf("%lld ", m[i][j]);
                ++j;
            }
        }
        if (j2 < n) {
            long long  i = n - 1, j = j2;
            for (; j < n; ++j) {
                printf("%lld ", m[i][j]);
                --i;
            }
            i += 2;
            --j;
            for (; i < n; ++i) {
                printf("%lld ", m[i][j]);
                --j;
            }
        }
        j1 -= 2;
        j2 += 2;
        if (j1 < 0 && j2 > n - 1) {
            printf("\n");
            break;
        }
    }
}

int main() {
    long long n;

    while (scanf("%lld", &n) != EOF){   
        long long** m = (long long**) malloc(n * sizeof(long long*));
        for (long long i = 0; i < n; ++i) {
            m[i] = (long long*) malloc(sizeof(long long) * n);
        }

        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                scanf("%lld", &m[i][j]);
            }
        }

        printf("\n");
        printm(m, n);
        printf("\n");
    }

    printf("End of program.\n");

    return 0;
}
