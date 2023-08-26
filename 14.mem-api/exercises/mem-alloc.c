#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int* x = (int*)malloc(sizeof(int));
    printf("The memory was allocated, x=%d\n", *x);
    *x = 10;
    printf("Now x=%d\n", *x);
    return 0;
}