// APUE 8.9 and 10.16
// SIGNALS implementation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void sig_usr(const int signo) {
    printf("Recived SIGUSR1 signal\n");
}

void InitSigMask() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        fprintf(stderr, "Signal failed...\n");
    }
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &newmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask failed...\n");
        exit(1);
    }
}

void SendUserSignal(const int pid) {
    kill(pid, SIGUSR1);
}

void WaitUserSignal() {
    sigset_t zeromask;
    sigemptyset(&zeromask);
    if (sigsuspend(&zeromask) != -1) {
        fprintf(stderr, "Signal suspend failed...\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    printf("Program started (pid:%d)\n", (int) getpid());
    InitSigMask();
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        return 1;
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", (int) getpid());
        printf("Hello!\n");
        SendUserSignal(getppid());
    } else {
        sleep(1);
        printf("Parent process (pid:%d)\n", (int) getpid());
        WaitUserSignal();
        printf("Goodbye...\n");
    }
    return 0;
}
