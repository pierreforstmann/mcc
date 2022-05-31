all:  htob vd tetrad taio tsem tshm
vd: vd.c
	$(CC) -std=gnu99 -Wall -o $@ $<
tetrad: tetrad.c
	$(CC) -std=gnu99 -Wall -o $@ $<
taio: taio.c
	$(CC) -std=gnu99 -Wall -o $@ $< -laio
tsem: tsem.c
	$(CC) -std=gnu99 -Wall -o $@ $< -lpthread
clean: 
	rm -f htob vd tetrad taio tsem tshm
