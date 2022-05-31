/*
 * 
 * tsem.c = test semaphore with shared memory
 * 
 *
 * compile with: gcc -Wall -o tsem -lpthread tsem.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>

int main(){
    int i;
    int shm_id;
    pid_t pid;
    int *addr; 
    int data;
    pid_t current_pid;
    key_t shm_key;
    sem_t *sem;

    shm_key = ftok("/dev/null", 65);
    shm_id = shmget(shm_key, sizeof(int), 0644 | IPC_CREAT);
    if (shm_id < 0){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    sem_unlink("semaphore");
    sem = sem_open("semaphore", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    } 

    addr = (int *) shmat(shm_id, (void *) 0, 0);   
    if (addr == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    *addr = 0;

    for (i = 0; i < 2; i++){
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            sem_close(sem);
            sem_unlink("semaphore");
            exit(EXIT_FAILURE);
        }
    }


    if (pid == 0)
    {
        current_pid = getpid();
	printf("Child %d: waiting for critical section \n", current_pid);
       	sem_wait(sem);
	printf("Child %d: enters in critical section \n", current_pid);
       	printf("child %d: Enter the data:\n", current_pid);
       	scanf("%d", &data);
        printf("Child %d: new value of data = %d\n", current_pid, data);
       	printf("Child %d: sum of whole data so far = %d\n", current_pid, *addr += data);
       	sem_post(sem);
	      printf("Child %d exits from critical section\n", current_pid);
       	exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        //parent process
        while ((pid = waitpid(-1, NULL, 0)))
        {
            if (errno == ECHILD)
            {
                break;
            }
        }
        puts("All children exited");
        shmdt(addr);
        shmctl(shm_id, IPC_RMID, 0);
        sem_close(sem);         
        sem_unlink("semaphore");
        exit(0);
    }

    exit(0);
}
