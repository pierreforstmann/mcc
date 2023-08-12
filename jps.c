/*
 * Jurassic Park System
 *
 * jps.c
 *
 * Copyright Pierre Forstmann 2023.
 *
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF_SIZE    256

int main(int argc, char **argv)
{
        int i;
        char buf[MAX_BUF_SIZE];
        int j;

        printf("Jurassic Park, System Security Interface\n");
        printf("Version 4.0.5, Alpha E\n");
        printf("Ready...\n");



        for (i=0; i < 3; i++)
        {
                printf("> ");
                fgets(buf, MAX_BUF_SIZE, stdin);

                j=0;
                while (buf[j] != ' ' && buf[j] != '\n')
                        j++;
                buf[j]='\0';
                if ( i < 2)
                        printf("%s: PERMISSION DENIED.\n", buf);
                else
                        printf("%s: PERMISSION DENIED....and...\n", buf);
        }

        while (1)
        {
                printf("YOU DIDN'T SAY THE MAGIC WORD!\n");
                sleep(1);
        }

        exit(0);
}

