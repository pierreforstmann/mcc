#!/bin/sh
#
# gcc.sh: compile and link with gcc checks enabled for C11
#
gcc -o $1 -Wall -pedantic -Wextra -std=c11 $1.c

