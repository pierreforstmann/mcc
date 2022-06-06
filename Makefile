all:  tpf htob vd tetrad taio tsem tshm
tpf: tpf.c
	$(CC) -std=gnu99 -Wall -o $@ $<
htob: htob.c
	$(CC) -std=gnu99 -Wall -o $@ $<
vd: vd.c
	$(CC) -std=gnu99 -Wall -o $@ $<
tetrad: tetrad.c
	$(CC) -std=gnu99 -Wall -o $@ $<
taio: taio.c
	$(CC) -std=gnu99 -Wall -o $@ $< -laio
tsem: tsem.c
	$(CC) -std=gnu99 -Wall -o $@ $< -lpthread
tshm: tshm.c
	$(CC) -std=gnu99 -Wall -o $@ $< 
clean: 
	rm -f htob vd tetrad taio tsem tshm tpf
