FLAGS=-g -O0 -Wall -msse2 -msse -march=native -maes

all: populator monitor

populator: populator.o
	gcc $(FLAGS) -o populator populator.o

monitor: monitor.o
	gcc $(FLAGS) -o monitor monitor.o

monitor.o:
	gcc $(FLAGS) -c monitor.c

populator.o:
	gcc $(FLAGS) -c populator.c

clean:
	rm -f populator monitor *.o
