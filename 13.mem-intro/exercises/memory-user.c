#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const unsigned long long ITERATION_LIMIT = 33554432000;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: memory-user <number of megabytes to allocate by the program>\n");
        exit(1);
    }
    printf("pid = %d\n", getpid());
    unsigned long long megabytes = strtol(argv[1], (char**)NULL, 10);
    unsigned long long bytes = 1024 * 1024 * megabytes;
    printf("%llu bytes (or %llu megabytes) are going to be allocated\n", bytes, megabytes);
    char* mem = malloc(bytes);
    printf("memory was allocated\n");
    unsigned long long i = 0;
    char ch;
    for (unsigned long long i = 0; i < ITERATION_LIMIT; ++i) {
        mem[i % bytes] = (char)(i % 256);
    }

    free(mem);
    return 0;
}