#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("Hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Hello, I'm child (pid:%d)\n", (int) getpid());
    } else {
        int rc_wait = wait(&rc);
        printf("Hello, I'm parent of %d (rc_wait:%d) (pid:%d)\n",
                    rc, rc_wait, (int) getpid());
    }
    return 0;
}