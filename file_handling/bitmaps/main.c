#include <stdlib.h>
#include <stdio.h>

int main(void) {
    const int width = 800, height = 800, radius = 200;
    // open a file in binary write mode
    FILE* bitmap = fopen("first.ppm", "wb");
    // write the ppm header into the file
    fprintf(bitmap, "P3\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // write the current pixel as a triple (r g b) into the file
            // fprintf(bitmap, "%d %d %d ", x % 256, y % 256, (x * y) % 256);
            if ((x - width / 2) * (x - width / 2)
                 + (y - height / 2) * (y - height / 2) <= radius * radius) {
                fprintf(bitmap, "%d %d %d ", 255, 0, 0);
            } else {
                fprintf(bitmap, "%d %d %d ", 255, 255, 255);
            }
        }
    }
    // close the file
    fclose(bitmap);
    return EXIT_SUCCESS;
}
