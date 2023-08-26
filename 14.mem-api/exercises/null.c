#include <stdio.h>

int main(int argc, char* argv[]) {
    int* x = NULL;
    printf("The value under null ref pointer is %d", *x);
    return 0;
}
