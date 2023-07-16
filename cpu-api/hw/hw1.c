#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x = 100;
    printf("Program has started (x:%d) (pid:%d)\n", x, (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        return 1;
    } else if (rc == 0) {
        // child
        printf("Child process (x:%d) (pid:%d)\n", x, (int)getpid());
        x += 10;
        printf("Child process (x:%d) (pid:%d)\n", x, (int)getpid());
    } else {
        // parent
        printf("Parent process (x:%d) (pid:%d)\n", x, (int)getpid());
        x += 20;
        printf("Parent process (x:%d) (pid:%d)\n", x, (int)getpid());
    }
    return 0;
}