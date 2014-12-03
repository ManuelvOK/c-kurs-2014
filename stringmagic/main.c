#include <stdio.h>

int main(int argc, const char *argv[]) {
    char input[128] = {0};
    char output[256] = {0};
    int i;
    puts("String?");
    scanf("%127s", input);
    for (i = 0; input[i] != 0; i++) {
        // trage input[i] und " " in output ein
        output[2*i] = input[i];
        if (input[i+1] != 0)
            output[2*i+1] = ' ';
    }
    printf("%s\n", output);
    return 0;
}
