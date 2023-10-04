#include <stdio.h>
#include <sys/time.h>

const int MAX_TIMES = 100;
const int SHOW_WINDOWN = 5;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void m_gettimeofday() {
    struct timeval current_time[MAX_TIMES];
    for (int i = 0; i < MAX_TIMES; ++i) {
        gettimeofday(&current_time[i], NULL);
    }
    for (int i = 0; i < MIN(SHOW_WINDOWN, MAX_TIMES); ++i) {
        printf("%d: microseconds: %d\n", i + 1, current_time[i].tv_usec);
    }
    if (MAX_TIMES > SHOW_WINDOWN) {
        if (MAX_TIMES > 2 * SHOW_WINDOWN) {
            printf("...\n");
        }
        for (int i = MAX(SHOW_WINDOWN, MAX_TIMES - SHOW_WINDOWN); i < MAX_TIMES; ++i) {
            printf("%d: microseconds: %d\n", i + 1, current_time[i].tv_usec);
        }
    }
}

int main(int argc, char* argv[]) {
    m_gettimeofday();
    return 0;
}