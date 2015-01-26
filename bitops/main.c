#include <assert.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
    signed int n = 45, x;
    char c = 'A', y;

    int foo;
    // n * 32
    x = n << 5;
    assert(x == n * 32);
    // n % 16
    x = n & 15;
    assert(x == n % 16);
    // -n
    x = ~n + 1;
    assert(x == -n);

    // kleiner Buchstabe zu c
    y = c | 32;
    assert(y == 'a');

    foo = 'A' + 'B' * 256 + 'C' * 256 * 256;
    foo = 'A' | 'B' << 8 * sizeof(char) | 'C' << 2 * 8 * sizeof(char);
    printf("%s\n", &foo);

    return 0;
}
