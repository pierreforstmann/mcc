/*
**
** tda.c
**
** test dynamic 2d array (i.e without using tab[][] expression)
**
** A 2 dimension array is just a sequence of single dimension array
** where each 2D row is a single dimension array;
** this is essential to be able to compute direct address of any element.
** general rule for t[x,y] where: 
** - each element has size S 
** - each row has C elements (= number of columns)
** - index starts at 0 (<> from 1!):
** => address of x,y  = (x * C * S) + (y * S)
**
** created 22.09.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "da.h"

/*
** dtoa: single digit to char (because itoa not found)
** 
*/
char	dtoa(int p)
{
	if (p < 0 || p > 9) {
		printf("dtoa: invalid argument: %d \n");
		exit(-1);
	}
	if (p == 0)
		return '0';
	if (p == 1)
		return '1';
	if (p == 2)
		return '2';
	if (p == 3)
		return '3';
	if (p == 4)
		return '4';
	if (p == 5)
		return '5';
	if (p == 6)
		return '6';
	if (p == 7)
		return '7';
	if (p == 8)
		return '8';
	if (p == 9)
		return '9';
		
}

main (int argc, char **argv)
{
	struct da *s;
	int i,j;
	char tmp[5];
	int num_rows, num_cols, item_length;

	num_rows = 3;
	num_cols = 2;
	item_length = 5;
	s = create_da(num_rows, num_cols, item_length);	

	print_da(s);	

	for (i=0; i <  num_rows ; i++)
		for(j=0; j < num_cols; j++) {
		printf("i=%d and j=%d \n", i,j);
		/* fill array with self describing data */
		tmp[0] = dtoa(i);		
		tmp[1] = ';';
		tmp[2] = dtoa(j); 
		tmp[3] = '\0';
		set_item(s, i, j, tmp);
		printf("tmp=%s \n", tmp);
	}

	print_da(s);

	drop_da(s);
}
