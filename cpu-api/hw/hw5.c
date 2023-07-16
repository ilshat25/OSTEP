// APUE 8.6

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void pr_exit(const int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number=%d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (coredump file was generated)" : "");
#else
                "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
    }
}

int main(int argc, char* argv[]) {
    printf("The program started (pid:%d)\n", getpid());
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        sleep(1);
        printf("Child process has finished\n");
        exit(123); // to see in the parent
    } else {
        printf("Parent process (pid:%d) (child_pid:%d)\n", getpid(), rc);
        int status;
        wait(&status);
        pr_exit(status);
        printf("Parent process has finised\n");
    }
    return 0;
}