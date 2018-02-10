# memENC demo

### Demo Scenario: 
Judge Alice uses in-memory sqlite3 database in an untrusted VM to store the names of all witnesses in the murder Case No 3134.
Eve who works for the cloud company is paid by the main suspect to retrieve the list of witnesses and she is capable of cryo-freezing the physical RAM (cold boot) at any time.

##### Produced executables:
- *sqlite3*: sqlite3 v3.23.0 protected through memory encryption
- *eve.sh*: presents the data Eve will see the moment she performs cold boot
- *vanilla.sh* presents the data Eve could see with cold boot if the sqlite3 wasn't protected

### HowTo build

- `make build`
- `make`
- `ruby patch.rb`

### HowTo demo
- `sh eve.sh` in window one
- `./sqlite3` in-memory database in window two
- `.read populate.sql` from inside sqlite2 cl

### HowTo cleanup
- `make cleanall`
