// Course: COMP.2560 - System Programming
// University of Windsor

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd_in, fd_out;
    char ch;
    char *ack_msg = "I received your message.\n";

    //clean up any previous FIFOs 
    unlink("/tmp/fifo_c_to_s");
    unlink("/tmp/fifo_s_to_c");

    //create the two FIFOs 
    if(mkfifo("/tmp/fifo_c_to_s", 0777) == -1){
        perror("Error creating input FIFO");
        exit(1);
    }
    
    if(mkfifo("/tmp/fifo_s_to_c", 0777) == -1){
        perror("Error creating output FIFO");
        exit(1);
    }

    printf("Server started. Waiting for client connection...\n");

    //open input for reading (blocks until client opens for writing)
    fd_in = open("/tmp/fifo_c_to_s", O_RDONLY);
    //open output for writing
    fd_out = open("/tmp/fifo_s_to_c", O_WRONLY);

    printf("Client connected.\n");

    //read 1 byte at a time
    while(read(fd_in, &ch, 1) > 0){
        printf("Server received: %c\n", ch);
        
        write(fd_out, ack_msg, strlen(ack_msg) + 1); 
    }

    //cleanup
    close(fd_in);
    close(fd_out);
    unlink("/tmp/fifo_c_to_s");
    unlink("/tmp/fifo_s_to_c");
    return 0;
}