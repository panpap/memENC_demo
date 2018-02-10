# memENC demo

HowTo install
-----------------
- sh install.sh

HowTo run
-----------------
- make
- ruby patch.rb

HowTo demo
-----------------
- ./sqlite3 # in-memory database in terminal one
- sh eve.sh # memory snooping Eve in terminal two. Eve can cryo-freeze RAM (cold boot) at any time retrieving all memory contents
- sh populator.sh
