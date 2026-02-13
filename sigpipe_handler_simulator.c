// Course: COMP.2560 - System Programming
// University of Windsor
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

//signal handler for SIGPIPE
void sigpipe_handler(int signum) {
    printf("Caught the SIGPIPE signal.\n");
    //handler returns without terminating the process
}

int main() {
    int fd[2];
    char *msg = "Testing broken pipe";
    int ret;

    //create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    //close the read-end
    close(fd[0]);

    //install the signal handler
    signal(SIGPIPE, sigpipe_handler);

    //write to the pipe
    //this will trigger the SIGPIPE signal because the read-end is closed
    ret = write(fd[1], msg, strlen(msg));

    //check return value +
    if (ret == -1) {
        printf("write function returns %d\n", ret);
        perror("pipe problem");
    }

    close(fd[1]);
    return 0;
}