head="#include \"../resources/header.h\"\t//memenc\n\n"
mark1="rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &zLeftover);"
caller="\tif( SQLITE_OK == rc ){\n\tchar *val=readCmd(zSql);\n\tif (val!=NULL)\n\t\tshared_buffer=saveVal(val); //memenc\n\t}"
finishit="\nshmdt(shared_buffer);//memenc main"
mark2="rc = process_input(&data, 0);"

path="./bld/shell.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
count=1
File.foreach(path+".bak"){|line|
	if count==90
		fw.puts head
	elsif line.include? mark1
		fw.puts caller
	elsif if mark2
		fw.puts finishit
	else
		fw.puts line
	end
	count+=1
}
fw.close
system("make > /dev/null 2>&1")
