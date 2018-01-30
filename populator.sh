echo 'Table creation and population...'
echo 'create table IF NOT EXISTS sharcs_demo (name varchar PRIMARY KEY, salary numeric)'  | ./sqlite3 test.db
echo 'insert into sharcs_demo (name, salary) values ("John Doe1", 11111)' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name, salary) values ("John Doe2", 22222)' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name, salary) values ("John Doe3", 33333)' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name, salary) values ("John Doe4", 44444)' | ./sqlite3 test.db
#echo 'insert into sharcs_demo (name, salary) values ("John Doe5", 55555)' | ./sqlite3 test.db
./sqlite3 -header -csv test.db "select * from sharcs_demo;" > DBcontents_sharcs_demo.csv
echo 'Database contents:Name|Salary'
echo 'select * from sharcs_demo' | ./sqlite3 test.db
