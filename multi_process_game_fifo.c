// Course: COMP.2560 - System Programming
// University of Windsor

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

//FIFO names
#define FIFO1 "/tmp/pm_toto_in"
#define FIFO2 "/tmp/pm_toto_out"
#define FIFO3 "/tmp/pm_titi_in"
#define FIFO4 "/tmp/pm_titi_out"

void player(char *s, char *f_in, char *f_out);

int main(int argc, char *argv[]) {
    int fd1, fd2, fd3, fd4;
    char turn = 'T';

    //cleanup previous FIFOs
    unlink(FIFO1); unlink(FIFO2); unlink(FIFO3); unlink(FIFO4);

    //create the 4 FIFOs
    if (mkfifo(FIFO1, 0777) == -1) perror("mkfifo1");
    if (mkfifo(FIFO2, 0777) == -1) perror("mkfifo2");
    if (mkfifo(FIFO3, 0777) == -1) perror("mkfifo3");
    if (mkfifo(FIFO4, 0777) == -1) perror("mkfifo4");

    printf("This is a 2-player game with a referee using FIFOs\n");

    //fork Player 1 
    if (!fork()) {
        player("TOTO", FIFO1, FIFO2);
        exit(0);
    }

    //fork Player 2 
    if (!fork()) {
        player("TITI", FIFO3, FIFO4);
        exit(0);
    }

    //referee Logic
    
    //connect to TOTO
    fd1 = open(FIFO1, O_WRONLY);
    fd2 = open(FIFO2, O_RDONLY);

    //connect to TITI
    fd3 = open(FIFO3, O_WRONLY);
    fd4 = open(FIFO4, O_RDONLY);

    //game loop
    while (1) {
        printf("\nReferee: TOTO plays\n\n");
        write(fd1, &turn, 1); //signal TOTO to play
        read(fd2, &turn, 1);  //wait for TOTO

        printf("\nReferee: TITI plays\n\n");
        write(fd3, &turn, 1); //signal TITI to play
        read(fd4, &turn, 1);  //wait for TITI
    }
    return 0;
}

void player(char *s, char *f_in, char *f_out) {
    int points = 0;
    int dice;
    long int ss = 0;
    char turn;
    int fd_in_desc, fd_out_desc;

    // open FIFOs
    fd_in_desc = open(f_in, O_RDONLY);
    fd_out_desc = open(f_out, O_WRONLY);

    while (1) {
        read(fd_in_desc, &turn, 1); //wait for turn

        printf("%s: playing my dice\n", s);
        dice = (int)time(&ss) % 10 + 1;
        printf("%s: got %d points\n", s, dice);
        points += dice;
        printf("%s: Total so far %d\n\n", s, points);

        if (points >= 50) {
            printf("%s: game over I won\n", s);
            kill(0, SIGTERM); //terminate all processes
        }
        sleep(2);
        write(fd_out_desc, &turn, 1); 
    }
}