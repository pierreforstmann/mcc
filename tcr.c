/*
 *
 * tcr.c: very simple CPU and RAM performance test
 *
 *
 * Copyright Pierre Forstmann 2018
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int iterations;
    int array_size;
    void *p;
    int i;
    int j;

    if (argc != 3)
    {
	printf("argc=%d\n", argc);
	printf("Usage: tcr <iterations number> <array size>\n");
	exit(1);
    }
    iterations = atoi(argv[1]);
    array_size = atoi(argv[2]); 

    p = malloc(array_size*sizeof(int));
    if (p ==  NULL)
    {
     printf("malloc %lu failed\n", array_size*sizeof(int));
     exit(1);
    }
    printf("Starting %d iterations on array of %d integers ... \n",
            iterations, array_size);

    for (j=0; j < iterations ; j++)
    {
     for (i=0; i < array_size; i++)
    	 ((int *)p)[i]=i;
    }

    printf("... done.\n");
    free(p);
    exit(0);
}
