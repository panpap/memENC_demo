# memENC demo

### Demo Scenario: 
Judge Alice uses in-memory sqlite3 database in an untrusted VM to store the names of all witnesses in the murder Case No 3134.
Eve who works for the cloud company is paid by the main suspect to retrieve the list of witnesses and she is capable of cryo-freezing the physical RAM (cold boot) at any time.

##### Produced executables:
- *sqlite3_vanilla*: sqlite3 v3.23.0 vanilla
- *sqlite3_protected*: sqlite3 v3.23.0 protected through memory encryption
- *eve.sh*: presents the data Eve will see the moment she performs cold boot
- *alice.sh* presents the data that Alice can after decrypting data.

### HowTo build

- `make build`
- `make`
- `ruby patch.rb`

### HowTo demo
- `sh eve.sh` in window one
- `./sqlite3_vanilla` in-memory database in window two
- `.read populate.sql` from inside sqlite2 cl
- `./sqlite3_protected` in-memory database in window two
- `.read populate.sql` from inside sqlite2 cl

### HowTo cleanup
- `make cleanall`
