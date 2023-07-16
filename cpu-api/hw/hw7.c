#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("The program started (pid:%d)\n", getpid());
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        close(STDOUT_FILENO);
        int res = printf("Child process has finished");
        fprintf(stderr, "%d\n", res);
        res = fflush(stdout);
        fprintf(stderr, "%d %s\n", res, strerror(errno));
    } else {
        printf("Parent process (pid:%d) (child_pid:%d)\n", getpid(), rc);
        printf("Parent process has finised\n");
    }
    return 0;
}
