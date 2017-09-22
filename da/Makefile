all:	lib tda

lib:	da.h da.c
	gcc -o libda.a -c da.c

tda:	tda.c
	gcc -o tda -L. -lda tda.c

clean:	
	rm libda.a tda
