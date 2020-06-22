/*
 * vd.c validate date format 'YYYY-DD-MM'
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

        char year[4];
        char month[2];
        char day[2];
        int rc;

    if (argc != 2)
    {
        printf("usage: vd YYYY-MM-DD\n");
        return 1;
    }
    
    rc = sscanf(argv[1], "%4[0-9]-%2[0-9]-%2[0-9]", 
                             year, month, day);
    if (rc == 3)
        printf("%d %d %d \n", atoi(year), atoi(month), atoi(day));
    else
    {
        printf("Incorrect date format\n");
        return 1;
    }

    return 0;
}
