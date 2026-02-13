// Course: COMP.2560 - System Programming
// University of Windsor

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd_out, fd_in;
    char ch;
    char buf[100]; 

    //connect to the server's input FIFO
    //loop until the server is ready 
    while((fd_out = open("/tmp/fifo_c_to_s", O_WRONLY)) == -1){
        fprintf(stderr, "Trying to connect to server...\n");
        sleep(1);
    }
    
    //connect to the server's output FIFO to receive messages
    fd_in = open("/tmp/fifo_s_to_c", O_RDONLY);
    
    printf("Connected! Type a character and press Enter:\n");

    //read from keyboard until EOF 
    while((ch = getchar()) != EOF) { 
        if (ch == '\n') continue; 

        //send the character to the server
        write(fd_out, &ch, 1);

        //read the acknowledgment from the server
        read(fd_in, buf, 100); 
        
        //display the server's response
        printf("Server says: %s", buf);
    }

    //cleanup
    close(fd_out);
    close(fd_in);
    return 0;
}