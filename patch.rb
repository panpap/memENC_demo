head="#include \"../resources/header.h\"\t//memenc\n\n"
mark1="rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &zLeftover);"
caller="\tif( SQLITE_OK == rc ){\n\tchar *val=readCmd(zSql);\n\tif (val!=NULL)\n\t\tmemenc_buf=saveVal(val,memenc_buf); //memenc\n\t}"
finishit="\nexitNicely(memenc_buf);//memenc main"
mark2="rc = process_input(&data, 0);"
mark3="char **azCmd = 0;"
rand="\ttime_t t;\n\tsrand((unsigned) time(&t));"

path="./bld/shell.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
count=1
File.foreach(path+".bak"){|line|
	if count==90
		fw.puts head
		mod=true
	elsif line=="static int shell_exec("
		fw.puts "char *memenc_buf=NULL;"
		mod=true
	end
	fw.puts line
	if not mod
		if line.include? mark1
			fw.puts caller
		elsif if line.include? mark2
			fw.puts finishit
		end
		elsif line.include? mark3
			fw.puts rand
		end
	end
	count+=1
	mod=false
}
fw.close
system("make > /dev/null 2>&1")
