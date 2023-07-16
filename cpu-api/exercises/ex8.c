/*
8. Write a program that creates two children, and connects the standard
   output of one to the standard input of the other, using the pipe() system call.
*/

// APUE 15.2 and 3.12
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int BUF_SIZE = 128;

int main(int argc, char* argv[]) {
    printf("The program started (pid:%d)\n", getpid());
    
    int fd[2];
    pipe(fd);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        printf("Child process has finished (pid:%d)\n", getpid());
        exit(0);
    }

    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        char message[BUF_SIZE];
        fgets(message, BUF_SIZE, stdin);
        printf("Message from another child process: \"%s\"\n", message);
        printf("Child process has finished (pid:%d)\n", getpid());
        exit(0);
    }

    printf("Parent process (pid:%d)\n", getpid());
    // wait for all child processes
    while(wait(NULL) > 0);
    printf("Parent process has finised\n");
    return 0;
}
