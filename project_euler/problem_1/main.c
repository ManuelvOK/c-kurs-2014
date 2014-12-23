#include <stdio.h>

// calculate the sum of all numbers less than limit,
// which are divisible by divisor
int sumOfDivisibles(int divisor, int limit) {
    /* Sum of 1 ... n =
     * n * (n + 1) / 2
     */
    int n = (limit - 1) / divisor;
    return divisor * n * (n + 1) / 2;
}

int main(int argc, const char *argv[]) {
    /* Naive approach
     * iterate from 1 to 1000 and check each number
     */
    int result = 0;
    for (int i = 1; i < 1000; i++)
        if (i % 3 == 0 || i % 5 == 0)
            result += i;
    printf("\nresult (naive): %d\n", result);
    /* Smart approach
     * add the sum of all numbers divisible by either 3 or 5, minus the sum of
     * all numbers divisible by 3 and 5 (as they are counted twice)
     */
    result = sumOfDivisibles(3, 1000) + sumOfDivisibles(5, 1000)
        - sumOfDivisibles(15, 1000);
    printf("\nresult (smart:) %d\n", result);
    return 0;
}
