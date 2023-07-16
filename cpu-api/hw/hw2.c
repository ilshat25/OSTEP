#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    printf("Program has started (pid:%d)\n", (int) getpid());
    close(STDOUT_FILENO);
    int fd = open("hw2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        return 1;
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", (int) getpid());
    } else {
        printf("Parent process (pid:%d)\n", (int) getpid());
    }
    return 0;
}
