  
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        typedef struct {
         int c;
        } s;
        s *ps;
        int n = 3;
        int i;

        ps = (s *)malloc(sizeof(s) * n);
        ps[0].c = 0;
        ps[1].c = 1;
        ps[2].c = 2;

        for ( i = 0 ; &ps[i] ; i++)
                printf("i=%d ps[i]=%d \n", i, ps[i].c);

        exit(0);
}
