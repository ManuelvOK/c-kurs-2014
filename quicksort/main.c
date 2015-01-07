#include <stdio.h>
#include <stdlib.h>

int randomNumbers[] = {3, 7, 5, 42, 6, 18, 4};

void printArray(int array[], int length) {
    printf("[%d", array[0]);
    for (int i = 1; i < length; i++)
        printf(", %d", array[i]);
    printf("]\n");
}

void quicksort(int array[], int left, int right) {
    int middle = array[left + (right - left) /2];
    int l, r, buffer;
    for (l = left, r = right - 1; l <= r; l++, r--) {
        while (array[l] < middle)
            l++;
        while (array[r] > middle)
            r--;
        if (l > r)
            break;
        buffer = array[l];
        array[l] = array[r];
        array[r] = buffer;
    }
    if (left < r)
        quicksort(array, left, r);
    if (l < right)
        quicksort(array, l, right);
}

int main(int argc, const char *argv[]) {
    printArray(randomNumbers, sizeof(randomNumbers) / sizeof(int));
    quicksort(randomNumbers, 0, sizeof(randomNumbers) / sizeof(int));
    printArray(randomNumbers, sizeof(randomNumbers) / sizeof(int));
    return 0;
}
