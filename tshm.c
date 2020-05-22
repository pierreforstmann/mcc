/*
 * tshm.c
 * 
 * Simple example of shared memory between parent and child process
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t pid;
    int shmid;
    char *addr;

    shmid = shmget(2,1024,0666|IPC_CREAT);
    addr = (char *) shmat(shmid, (void *) 0, 0);
    printf("In parent => addr: %p \n", (void *)addr);
    printf("In parent  =>  writing *addr ... \n");
    *addr = 'P';
    printf("In parent  =>  ... writing *addr: done \n");
    printf("In parent  => reading *addr = %c \n", *addr);

    pid = fork();
    if(pid == 0) 
    {
        printf("In child  => PID: %d PPID: %d\n", getpid(), getppid());
        printf("In child  => addr: %p \n", (void *)addr);
        printf("In child  => reading *addr = %c \n", *addr);
        printf("In child  => writing *addr ... \n");
        *addr = 'C';
        printf("In child  => ... writing *addr: done \n");
        printf("In child  => reading *addr = %c \n", *addr);
        printf("In child  => exiting \n");
        exit(EXIT_SUCCESS);
    }
    else if(pid > 0) 
    {
        printf("In parent => PID: %d\n", getpid());
        printf("In parent => waiting for child process to finish ...\n");
        wait(NULL);
        printf("In parent => child process finished.\n");
        printf("In parent  => reading *addr = %c \n", *addr);
    }
    else {
        printf("In parent => unable to create child process.\n");
    }

   printf("In parent => exiting.\n"); 
  return EXIT_SUCCESS;
}
