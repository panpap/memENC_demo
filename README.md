# memENC demo

### HowTo build

- `make build`
- `make`
- `ruby patch.rb`

### HowTo demo

- `sh eve.sh` Memory snooping Eve in terminal two. Eve can cryo-freeze RAM (cold boot) at any time and retrieve all  memory contents
- `./sqlite3` in-memory database in terminal one
- `.read populate.sql` from inside sqlite2 cl
