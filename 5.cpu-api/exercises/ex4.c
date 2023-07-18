/*
4. Write a program that calls fork() and then calls some form of
   exec() to run the program /bin/ls. See if you can try all of the
   variants of exec(), including (on Linux) execl(), execle(),
   execlp(), execv(), execvp(), and execvpe(). Why do
   you think there are so many variants of the same basic call?
*/

// APUE 8.10
//
//      +----------+              +----------+            +----------+
//      |  execlp  |              |  execl   |            |  execle  |
//      +----------+              +----------+            +----------+
//           || build argv             || build argv           || build argv
//           || as a vector            || as a vector          || as a vector
//           ||                        ||                      ||
//           \/                        \/                      \/
//      +----------+   try each   +----------+    use     +----------+
//      |  execvp  |------------->|  execv   |----------->|  execve  |
//      +----------+ PATH prefix  +----------+  environ   +----------+
//                                                             /\
//                                                             || build path from
//                                                             || /proc/self/fd alias
//                                                             ||
//                                                        +----------+
//                                                        |  fexecve |
//                                                        +----------+
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("The program started (pid:%d)\n", getpid());
    
    // execl
    printf("execl:\n");
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        if (execl("/bin/ls", "ls", (char*)0) < 0) {
            fprintf(stderr, "Execl error\n");
            exit(-1);
        }
    } else {
        printf("Parent process (pid:%d) (child_pid:%d)\n", getpid(), rc);
        if (wait(NULL) < 0) {
            fprintf(stderr, "Wait error...\n");
        }
    }
    printf("===============\n\n");

    // execle
    printf("execle:\n");
    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        char* ls_env[] = { "CWD=..", NULL };
        if (execle("/bin/bash", "bash", "-c", "ls $CWD", (char*)0, ls_env) < 0) {
            fprintf(stderr, "Execle error\n");
            exit(-1);
        }
    } else {
        printf("Parent process (pid:%d) (child_pid:%d)\n", getpid(), rc);
        if (wait(NULL) < 0) {
            fprintf(stderr, "Wait error...\n");
        }
    }
    printf("===============\n\n");

    // execlp
    printf("execlp:\n");
    rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed...\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process (pid:%d)\n", getpid());
        if (execlp("echo", "echo", "arg1", "arg2", "arg3", (char*)0) < 0) {
            fprintf(stderr, "Execlp error\n");
            exit(-1);
        }
    } else {
        printf("Parent process (pid:%d) (child_pid:%d)\n", getpid(), rc);
        if (wait(NULL) < 0) {
            fprintf(stderr, "Wait error...\n");
        }
    }

    return 0;
}