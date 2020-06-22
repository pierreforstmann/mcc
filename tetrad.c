/*
 *
 * tetrad.c= enter several tetrad
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

void scanf_tetrad(int p[2][2])
{
        printf("Enter 4 numbers:");
        scanf("%d %d %d %d", &p[0][0], &p[0][1], &p[1][0], &p[1][1]);
}

int main()
{
    int i,j, idx;
    int ttnb;
    int ***tt, **ctt;


    printf("Enter number of tetrad:");
    scanf("%d", &ttnb);

    tt = malloc(ttnb * sizeof (int [2][2]));
    if (tt == NULL)
    {
        perror("malloc");
        return 1;
    }

    for (idx=0; idx < ttnb; idx++)
    {
        tt[idx] = malloc(sizeof (int [2][2]));
        if (tt[idx] == NULL)
        {
            perror("malloc");
            return 1;
        }
    }


    for (idx=0; idx < ttnb; idx++)
    {
        scanf_tetrad((int (*)[2])tt[idx]);
    }

    printf("You entered:\n");
    for (idx=0; idx < ttnb; idx++)
    {
        printf("tetrad %d: ", idx);
        ctt = tt[idx];      
        for (i=0; i < 2; i++)
            for(j=0; j < 2; j++)
            {
                printf("%d ", *((int*)ctt + (i * 2) + j));
            }
        printf("\n");
    }


    return 0;   
}
