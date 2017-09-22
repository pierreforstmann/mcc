/*
**
** da.c
**
** dynamic 2d array (i.e without using tab[][] expression)
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
** created 21.09.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "da.h"

/*
** we suppose array contains only strings
*/

char *get_item(struct da *s, int p_row_number, int p_col_number)
{
	if (p_row_number > s->max_num_rows)
	{
		printf("get_item: invalid row number: %d\n", p_row_number);
		exit(-1);
	}
	if (p_col_number > s->max_num_cols)
	{
		printf("get_item: invalid col number: %d\n", p_col_number);
		exit(-1);
	}
	return ((char*)s->t + (p_row_number*(s->max_num_cols)*(s->item_length)) 
                            + (p_col_number*(s->item_length)));			
}

void set_item(struct da *s, int p_row_number, int p_col_number, char *p_item)
{
	if (p_row_number > s->max_num_rows)
	{
		printf("set_item: invalid row number: %d\n", p_row_number);
		exit(-1);
	}
	if (p_col_number > s->max_num_cols)
	{
		printf("set_item: invalid col number: %d\n", p_col_number);
		exit(-1);
	}
	if ( strlen(p_item) > s->item_length)
	{
		printf("set_item: invalid item length: %d \n", strlen(p_item));
		exit(-1);
	}
	strcpy((char*)s->t 
                + (p_row_number * s->max_num_cols * s->item_length) + (p_col_number * s->item_length), 
               p_item);
	

}


struct da *create_da(int p_num_rows, int p_num_cols, int p_item_length)
{
	char *t;
	struct da *s;
	char *init_item;
	int i,j;

	t = malloc(p_num_cols * p_num_rows * p_item_length);
	if (t == NULL)	
	{
		printf("malloc for t failed:\n");
		exit(-1);
	}
	s = (struct da *)malloc(sizeof(struct da));
	if (s == NULL)	
	{
		printf("malloc for f failed:\n");
		exit(-1);
	}
	s->t = t;
	s->max_num_cols = p_num_cols;
	s->max_num_rows = p_num_rows;
	s->item_length = p_item_length;

	init_item = (char *)malloc(p_item_length);	
	if (init_item == NULL)
	{
		printf("malloc for init_item failed:\n ");
		exit(-1);		
	}
	for (i=0; i < p_item_length - 1; i++)
		*(init_item + i) = 'I';
	*(init_item + p_item_length - 1) = '\0';
	for (i=0; i < s->max_num_rows; i++)
		for (j=0; j < s->max_num_cols; j++)
			set_item(s, i, j, init_item);		

	free((void*)init_item);
	return s;	
}


void drop_da(struct da *s)
{
	free((void *)s->t);
	free((void *)s);
	
}

void print_da(struct da *s)
{
	int i,j;
	for (i=0; i < s->max_num_rows; i++)
		for (j=0; j < s->max_num_cols; j++) 
			printf("t[%d,%d]=%s\n",i,j, get_item(s, i, j));
}

