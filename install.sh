tar xzf sqlite.tar.gz
mkdir bld                ;#  Build will occur in a sibling directory
cd bld	                 ;#  Change to the build directory
../sqlite/configure      ;#  Run the configure script
make                     ;#  Run the makefile.
make sqlite3.c           ;#  Build the "amalgamation" source file

