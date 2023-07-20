#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

const int N = 100000;

int main(int argc, char* argv[]) {
    
    struct timeval start, end;
    if (gettimeofday(&start, NULL) < 0) {
        fprintf(stderr, "gettimeofday error...\n");
    }
    for (int i = 0; i < N; ++i) {
        if (read(STDIN_FILENO, NULL, 0) < 0) {
            fprintf(stderr, "read error...\n");
        }
    }
    if (gettimeofday(&end, NULL) < 0) {
        fprintf(stderr, "gettimeofday error...\n");
    }
    unsigned long long startTime = start.tv_sec * 1000000 + start.tv_usec;
    unsigned long long endTime = end.tv_sec * 1000000 + end.tv_usec; 
    unsigned long long diff = endTime - startTime;
    printf("start time: %lld us\nend time: %lld us\ndiff: %lld us\n",
        startTime, endTime, diff);
    printf("it's ~%.2f us for a system call (0-byte read)\n", (double)diff / N);
    return 0;
}
