#include <stdio.h>

int main(int argc, const char *argv[]) {
    char input[256] = {0};
    int n, i;
    puts("String?");
    scanf("%255s", input);
    puts("From letter #?");
    scanf("%d", &n);
    n--;
    for (i = n; i < 255; printf("%c", input[i++]));
    printf("\n");
    for (i = n; i < 255; printf("%c", *(input + i++)));
    printf("\n");
    printf("%s\n", input + n);
    printf("%s\n", &(input[n]));
    return 0;
}
