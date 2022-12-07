#include <stdio.h>

void printmd(long long** m, long long n) {
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            printf("%lld ", m[i][j]);
        }
        printf("\n");
    }
}

void printm(long long** m, long long n) {
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            printf("%lld ", m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long** m = (long long**) malloc(n * sizeof(long long*));
    for (long long i = 0; i < n; ++i) {
        m[i] = (long long*) malloc(sizeof(long long) * n);
    }

    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            scanf("%lld", &m[i][j]);
        }
    }

    // printmd(m, n);
    printm(m, n);

    return 0;
}