#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

const int PAGE_SIZE = 4096;
const int ARRAY_SIZE = PAGE_SIZE / sizeof(int) * 4096;

int arr[ARRAY_SIZE];

unsigned time_diff(const struct timeval tm1, const struct timeval tm2) {
    const unsigned secondsDiff = tm2.tv_sec - tm1.tv_sec;
    return tm2.tv_usec + secondsDiff * 1000000 - tm1.tv_usec;
}

int main(int argc, char* argv[]) {
    cpu_set_t cpu_mask;
    CPU_ZERO(&cpu_mask);
    CPU_SET(1, &cpu_mask);
    pthread_setaffinity_np(0, sizeof(cpu_mask), &cpu_mask);

    if (argc < 3) {
        fprintf(stderr, "Two arguments are required: numpages<int>, trials<int>\n");
        exit(1);
    }
    const int numpages = atoi(argv[1]);
    const int trials = atoi(argv[2]);

    const int jump = PAGE_SIZE / sizeof(int);
    struct timeval tm1, tm2;
    unsigned long long res = 0;
    long long sum = 0;
    gettimeofday(&tm1, NULL);
    for (int i = 0; i < trials; ++i) {
        for (int k = 0; k < 1000; ++k) {
            for (int j = 0; j < numpages; ++j) {
                arr[j * jump] += 5;
            }
        }
    } 
    gettimeofday(&tm2, NULL);
    res += time_diff(tm1, tm2);
    printf("%d\t%f\n", numpages, res / (float)(numpages * trials));
    return 0;
}