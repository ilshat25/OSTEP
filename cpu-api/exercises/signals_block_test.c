#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sigismemeber(const sigset_t* set, const int signo) {
    return (*set & (1 << (signo - 1))) != 0;
}

void pr_mask(const char* str) {
    sigset_t procmask;
    if (sigprocmask(0, NULL, &procmask) < 0) {
        fprintf(stderr, "Sigprocmask error...");
    } else {
        printf("%s", str);
        if (sigismemeber(&procmask, SIGINT)) {
            printf(" SIGINT");
        }
        if (sigismemeber(&procmask, SIGUSR1)) {
            printf(" SIGUSR1");
        }
        printf("\n");
    }
}

void sig_int(int signo) {
    pr_mask("\nIn sig_int: ");
}

int main(int argc, char* argv[]) {
    sigset_t newmask, oldmask, waitmask;

    pr_mask("The program started: ");

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGINT) failed\n");
    }
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "sigprocmask failed\n");
    }

    pr_mask("In critical region: ");

    if (sigsuspend(&waitmask) != -1) {
        fprintf(stderr, "sigsuspend failed\n");
    }

    pr_mask("After return from sigsuspend: ");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask failed\n");
    }

    pr_mask("Program exit: ");
    return 0;
}