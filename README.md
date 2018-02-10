# memENC demo

###HowTo build

- `sh install.sh`
- `make`
- `ruby patch.rb`

###HowTo demo

- `sh eve.sh` .I memory snooping Eve in terminal two. Eve can cryo-freeze RAM (cold boot) at any time retrieving all memory contents
- `./sqlite3 .I` in-memory database in terminal one
- `.read populate.sql` .I from inside sqlite2 
