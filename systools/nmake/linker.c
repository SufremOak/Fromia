#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "nmake.h"

int linker(char *objfile, char *exe)
{
    pid_t pid;
    int status;
    char *argv[4];

    argv[0] = "ld";
    argv[1] = "-o";
    argv[2] = exe;
    argv[3] = objfile;
    argv[4] = NULL;

    if ((pid = fork()) == 0) {
        execvp("ld", argv);
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
        return -1;
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 0;
        } else {
            return -1;
        }
    }
}