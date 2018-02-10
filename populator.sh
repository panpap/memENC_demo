echo 'Table creation and population...'
echo 'create table IF NOT EXISTSmemenc_demo (name varchar PRIMARY KEY)'  | ./sqlite3 test.db
echo 'insert into memenc_demo (name) values ("John Doe1")' | ./sqlite3 test.db
#echo 'insert into memenc_demo (name) values ("John Doe2")' | ./sqlite3 test.db
#echo 'insert into memenc_demo (name) values ("John Doe3")' | ./sqlite3 test.db
#echo 'insert into memenc_demo (name) values ("John Doe4")' | ./sqlite3 test.db
#echo 'insert into memenc_demo (name) values ("John Doe5")' | ./sqlite3 test.db
