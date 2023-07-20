#define SYSCTL_CORE_COUNT   "machdep.cpu.core_count"

#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#import <pthread.h>
#import <mach/thread_act.h>

typedef struct cpu_set {
  uint32_t    count;
} cpu_set_t;

static inline void
CPU_ZERO(cpu_set_t *cs) { cs->count = 0; }

static inline void
CPU_SET(int num, cpu_set_t *cs) { cs->count |= (1 << num); }

static inline int
CPU_ISSET(int num, cpu_set_t *cs) { return (cs->count & (1 << num)); }

int pthread_setaffinity_np(pthread_t thread, size_t cpu_size,
                           cpu_set_t *cpu_set)
{
  thread_port_t mach_thread;
  int core = 0;

  for (core = 0; core < 8 * cpu_size; core++) {
    if (CPU_ISSET(core, cpu_set)) break;
  }
  printf("binding to core %d\n", core);
  thread_affinity_policy_data_t policy = { core };
  mach_thread = pthread_mach_thread_np(thread);
  thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY,
                    (thread_policy_t)&policy, 1);
  return 0;
}

const int N = 100000;
const double systemCallTime = 0.67;

int main(int argc, char* argv[]) {
    cpu_set_t cpu_mask;
    CPU_ZERO(&cpu_mask);
    CPU_SET(1, &cpu_mask);
    pthread_setaffinity_np(0, sizeof(cpu_mask), &cpu_mask);

    int fd1[2];
    int fd2[2];
    char ch;
    pipe(fd1);
    pipe(fd2);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork error...\n");
        return -1;
    } else if (rc == 0) {
        for (int i = 0; i < N; ++i) {
            read(fd1[0], &ch, 1);
            write(fd2[1], "b", 1);
        }
        return 0;
    }

    struct timeval start, end;
    if (gettimeofday(&start, NULL) < 0) {
        fprintf(stderr, "gettimeofday error...\n");
    }
    for (int i = 0; i < N; ++i) {
        write(fd1[1], "a", 1);
        read(fd2[0], &ch, 1);
    }
    if (gettimeofday(&end, NULL) < 0) {
        fprintf(stderr, "gettimeofday error...\n");
    }

    unsigned long long startTime = start.tv_sec * 1000000 + start.tv_usec;
    unsigned long long endTime = end.tv_sec * 1000000 + end.tv_usec; 
    unsigned long long diff = endTime - startTime;
    printf("start time: %lld us\nend time: %lld us\ndiff: %lld us\n",
        startTime, endTime, diff);
    printf("it's ~%.2f us for a context switch\n", (double)diff / N - 4 * systemCallTime);
    return 0;
}
