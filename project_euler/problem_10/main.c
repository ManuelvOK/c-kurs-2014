#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// is called once during smart approach
void sievePrimes(int* numbers, int max) {
    int end = (int) sqrt((double) max);
    for (int i = 2; i <= end; i++) {
        if (numbers[i])
            continue;
        else {
            for (int j = 2 * i; j <= max; j += i)
                numbers[j] = 1;
        }
    }
}

// is called for every number during brute-force approach
int isPrime(int number) {
    register int end = (int) sqrt((double) number);
    for (int i = 2; i <= end; i++)
        if (number % i == 0)
            return 0;
    return 1;
}

int main(int argc, const char *argv[]) {
    int max = 2000000;
    /*
     * smart: sieve all primes using the sieve of Eratosthenes
     * then iterate from 2 to 1999999 adding the primes
     */
    long sum = 0;
    int* numbers = (int*) calloc(max, sizeof(int));
    sievePrimes(numbers, max);
    for (int i = 2; i < max; i++)
        if (!numbers[i])
            sum += i;
    printf("%ld\n", sum);
    /*
     * naive: iterate from 2 to 1999999
     * check each number and add it, if it is prime
     */
    sum = 0;
    for (int i = 2; i < max; i++)
        if (isPrime(i))
            sum += i;
    printf("%ld\n", sum);
    return 0;
}
