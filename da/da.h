/*
**
** da.h 
**
** dynamic 2d array (i.e without using tab[][] expression)
**
**
** created 22.09.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** we suppose array contains only strings
*/

struct da {
	char *t;
	int max_num_cols;
	int max_num_rows;
	int item_length;
} da;

extern char* get_item(struct da *s, int p_row_number, int p_col_number);

extern void set_item(struct da *s, int p_row_number, int p_col_number, char *p_item);

extern struct da *create_da(int p_num_rows, int p_num_cols, int p_item_length);

extern void drop_da(struct da *s);

extern void print_da(struct da *s);
