/*
6. Write a slight modification of the previous program, this time using
   waitpid() instead of wait(). When would waitpid() be useful?
*/

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
        printf("Child process has finished (pid:%d)\n", getpid());
        exit(1); 
    }

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        sleep(3);
        printf("Child process has finished (pid:%d)\n", getpid());
        exit(2);
    }

    printf("Parent process (pid:%d)\n", getpid());
    int status;
    waitpid(rc, &status, 0);
    pr_exit(status);
    printf("Parent process has finised\n");
    return 0;
}