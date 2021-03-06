FLAGS=-g -O0 -Wall -msse2 -msse -march=native -maes

all: monitor vanilla populateSQL

sqlite3: sqlite3.o  shell.o resources/memEnc.o
	gcc $(FLAGS) -rdynamic -finstrument-functions resources/memEnc.o ./bld/sqlite3.o ./bld/shell.o -lpthread -ldl -o sqlite3  -lcrypto

vanilla: sqlite3.o  shell.o resources/memEnc.o
	ruby patch.rb 1

sqlite3.o:  ./bld/sqlite3.c  ./bld/sqlite3.h
	gcc $(FLAGS) -c ./bld/sqlite3.c -lpthread -ldl -o  ./bld/sqlite3.o

shell.o:  ./bld/shell.c resources/header.h resources/memEnc.c
	gcc $(FLAGS) -I./resources -c ./bld/shell.c -lpthread -o  ./bld/shell.o 

clean:
	rm -f sqlite3_* *.csv *.db *.o install eve.sh alice.sh
	make clean -C resources/

cleanall: clean
	rm -fr bld sqlite populate.sql

install: .tar .bld

build:
	sh build.sh

populateSQL:
	ruby makePopulator.rb

monitor:
	make -C resources/
	echo "./resources/monitor 0 1" > eve.sh
	echo "./resources/monitor 1 0" > alice.sh
	chmod 755 *.sh

tar:
	wget https://www.sqlite.org/src/tarball/sqlite.tar.gz
