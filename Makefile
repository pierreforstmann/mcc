all:  tu64 tpf htob vd tetrad taio tsem tshm tal
tu64: tu64.c
	$(CC) -std=gnu99 -Wall -o $@ $<
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
tal: tal.c
	$(CC) -std=c11 -Wall -o $@ $< 
clean: 
	rm -f htob vd tetrad taio tsem tshm tpf tal tu64
