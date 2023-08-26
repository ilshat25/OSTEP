#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const int size = 100;
    int* x = (int*)malloc(sizeof(int) * size);
    printf("Array of size=%d was allocated on address %p\n", size, x);
    free(x);
    printf("Array was freed\n");
    printf("Try to print value after free\n");
    printf("x[%d] = %d\n", size / 2, x[size / 2]);
    return 0;
}
