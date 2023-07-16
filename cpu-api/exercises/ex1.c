/*
1. Write a program that calls fork(). Before calling fork(), have the main process
   access a variable (e.g., x) and set its value to something (e.g., 100).
   What value is the variable in the child process?
   What happens to the variable when both the child and parent change the value of x?
*/

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