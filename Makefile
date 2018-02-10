FLAGS=-g -O0 -Wall -msse2 -msse -march=native -maes

all: monitor sqlite3 populator

sqlite3: sqlite3.o  shell.o 
	gcc $(FLAGS) -rdynamic -finstrument-functions ./bld/sqlite3.o ./bld/shell.o -lpthread -ldl -o sqlite3  -lcrypto

sqlite3.o:  ./bld/sqlite3.c  ./bld/sqlite3.h
	gcc $(FLAGS) -c ./bld/sqlite3.c -lpthread -ldl -o  ./bld/sqlite3.o

shell.o:  ./bld/shell.c resources/header.h resources/aes.h
	gcc $(FLAGS) -I./resources -c ./bld/shell.c -lpthread -o  ./bld/shell.o 

traced: sqlite3.o  shell.o
	gcc $(FLAGS) -o trace.o resources/trace.c
	gcc $(FLAGS) -rdynamic  -finstrument-functions ./bld/sqlite3.o  trace.o ./bld/shell.o -lpthread -ldl -o sqlite3

clean:
	rm -f sqlite3 *.csv *.db *.o install eve.sh bob.sh
	make clean -C resources/

cleanall: clean
	rm -fr bld sqlite

install: .tar .bld

build:
	sh build.sh

populator:
	ruby makePopulator.rb

monitor:
	make -C resources/
	echo "./resources/monitor 0" > eve.sh
	echo "./resources/monitor 1" > vanilla.sh
	chmod 755 *.sh

.tar:
	#wget https://www.sqlite.org/src/tarball/sqlite.tar.gz
