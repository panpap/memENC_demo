echo 'Table creation and population...'
echo 'create table IF NOT EXISTS sharcs_demo (name varchar PRIMARY KEY)'  | ./sqlite3 test.db
echo 'insert into sharcs_demo (name) values ("John Doe1")' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name) values ("John Doe2")' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name) values ("John Doe3")' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name) values ("John Doe4")' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name) values ("John Doe5")' | ./sqlite3 test.db
./sqlite3 -header -csv test.db "select * from sharcs_demo;" > DBcontents_sharcs_demo.csv
echo 'Database contents:Name|Salary'
echo 'select * from sharcs_demo' | ./sqlite3 test.db
