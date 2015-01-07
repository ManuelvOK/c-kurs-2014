#include <assert.h>
#include <stdio.h>
#define xxx 0

int main(int argc, const char *argv[]) {
    signed int n = 45, x;
    char c = 'A', y;

    int foo;
    // n * 32
    x = xxx;
    assert(x == n * 32);
    // n % 16
    x = xxx;
    assert(x == n % 16);
    // -n
    x = xxx;
    assert(x == -n);

    // kleiner Buchstabe
    y = xxx;
    assert(y == 'a');
    y = xxx;

    foo = 'A' + 'B' * 256 + 'C' * 256 * 256;
    foo = 'A' | 'B' << 8 * sizeof(char) | 'C' << 2 * 8 * sizeof(char);
    printf("%s\n", &foo);

    return 0;
}
