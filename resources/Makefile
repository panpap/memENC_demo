FLAGS=-g -O0 -Wall -msse2 -msse -march=native -maes

all: populator monitor

populator: populator.o 
	gcc $(FLAGS) -o populator populator.o -lcrypto

monitor: monitor.o  header.h aes.h
	gcc $(FLAGS) -o monitor monitor.o -lcrypto

monitor.o: header.h aes.h monitor.c
	gcc $(FLAGS) -c monitor.c

populator.o: header.h aes.h populator.c
	gcc $(FLAGS) -c populator.c

clean:
	rm -f populator monitor *.o
