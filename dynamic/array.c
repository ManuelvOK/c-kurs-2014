#include <stdio.h>
#include <stdlib.h>

struct DynArray {
    int* data;
    int size;
};

struct DynArray allocate(int size) {
    struct DynArray new;
    new.data = (int*) calloc(size, sizeof(int));
    new.size = size;
    return new;
}

void printArray(struct DynArray myArray) {
    int i;
    for (i = 0; i < myArray.size; i++)
        printf("%d\n", myArray.data[i]);
}

void setElement(struct DynArray* myArray, int pos, int val) {
    if (pos >= myArray->size) {
        myArray->data = (int*) realloc(myArray->data, (pos+1) * sizeof(int));
        for (; myArray->size <= pos; myArray->size++)
            myArray->data[myArray->size] = 0;
    }
    myArray->data[pos] = val;
}

int main(int argc, const char *argv[]) {
    struct DynArray array1;
    int n;
    puts("Länge des Arrays:");
    scanf("%d", &n);
    array1 = allocate(n);
    setElement(&array1, 10, 42);
    printArray(array1);
    free(array1.data);
    return 0;
}
