#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TARGET 100
#define BASE 10

int main(int argc, const char *argv[]) {
    double d_count = 0;
    int sum = 0;
    for (int i = 1; i <= TARGET; i++)
        d_count += log((double) i) / log((double) BASE);
    printf("%g\n", d_count);
    int* number = (int*) calloc(d_count, sizeof(int));
    number[0] = 1;
    d_count = 0;
    for (int i = 1; i <= TARGET; i++) {
        d_count += log((double) i) / log((double) BASE);
        long long carry = 0;
        for (int c = 0; c < d_count; c++) {
            carry += number[c] * i;
            number[c] = carry % BASE;
            carry /= BASE;
        }
    }
    for (int i = d_count; i >= 0; i--)
        sum += number[i];
    printf("%d\n", sum);
    return 0;
}
