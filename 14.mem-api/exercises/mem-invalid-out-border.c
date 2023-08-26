#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const int size = 100;
    int* x = (int*)malloc(sizeof(int) * size);
    printf("Array of size=%d was allocated on address %p\n", size, x);
    printf("Try to assign value to %d's element of array\n", size);
    x[size] = size;
    printf("x[%d] = %d\n", size, x[size]);
    free(x);
    return 0;
}
