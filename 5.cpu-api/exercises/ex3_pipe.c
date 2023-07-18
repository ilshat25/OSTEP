/*
3. Write another program using fork(). The child process should
   print “hello”; the parent process should print “goodbye”. You should
   try to ensure that the child process always prints first; can you do
   this without calling wait() in the parent?
*/

// APUE 15.2
// PIPE implementation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
    printf("Program started (pid:%d)\n", (int) getpid());
    int fields[2];
    pipe(fields);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        return 1;
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", (int) getpid());
        close(fields[0]);
        write(fields[1], 0, 1);
        close(fields[1]);
        printf("Hello!\n");
    } else {
        printf("Parent process (pid:%d)\n", (int) getpid());
        int tmp = 0;
        close(fields[1]);
        read(fields[0], tmp, 1);
        close(fields[0]);
        printf("Goodbye...\n");
    }
    return 0;
}