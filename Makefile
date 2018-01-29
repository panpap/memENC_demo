demo: sqlite3

all: sqlite3

sqlite3: sqlite3.o  shell.o
	gcc -g -rdynamic  -finstrument-functions ./bld/sqlite3.o ./bld/shell.o -lpthread -ldl -o sqlite3

sqlite3.o:  ./bld/sqlite3.c  ./bld/sqlite3.h
	gcc -g -rdynamic -finstrument-functions -c  ./bld/sqlite3.c -lpthread -ldl -o  ./bld/sqlite3.o

shell.o:  ./bld/shell.c
	gcc -g -rdynamic -finstrument-functions -c  ./bld/shell.c -lpthread -o  ./bld/shell.o

traced: sqlite3.o  shell.o
	gcc -c -o trace.o trace.c
	gcc -g -rdynamic  -finstrument-functions ./bld/sqlite3.o  trace.o ./bld/shell.o -lpthread -ldl -o sqlite3

clean:
	rm -f sqlite3 *.csv *.db *.o 

cleanall: clean
	rm -fr bld sqlite sqlite.tar.gz*

install: .tar .bld

.bld:
	sh install.sh

.tar:
	wget https://www.sqlite.org/src/tarball/sqlite.tar.gz
