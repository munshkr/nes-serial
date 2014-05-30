all: serial.nes

serial.nes: crt0.o serial.o runtime.lib nes.cfg
	ld65 -o serial.nes -C nes.cfg crt0.o serial.o runtime.lib

crt0.o: crt0.s
	ca65 crt0.s

serial.o: serial.c
	cc65 -Oi serial.c --add-source
	ca65 serial.s

clean:
	rm -f *.o *.nes serial.s

run:
	nestopia serial.nes
