FLAGS=-g -O0 -Wall -msse2 -msse -march=native -maes

all: populator monitor

populator: populator.o memEnc.o
	gcc $(FLAGS) -o populator memEnc.o populator.o -lcrypto

monitor: monitor.o  memEnc.o
	gcc $(FLAGS) -o monitor memEnc.o monitor.o -lcrypto

monitor.o: header.h memEnc.c monitor.c
	gcc $(FLAGS) -c monitor.c

populator.o: header.h memEnc.c populator.c
	gcc $(FLAGS) -c populator.c

memEnc.o: header.h memEnc.c
	gcc $(FLAGS) -c memEnc.c

clean:
	rm -f populator monitor *.o
