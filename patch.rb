readval='char *readVal(char *line){\n\tprintf(\"readVal>$ %s\n\",line); //panpap\n\tchar s[256], s2[256];\n\tstrcpy(s, line);\n\tstrcpy(s2, line);\n\tchar* cmd = strtok(s, " ");\n\tif (strcmp(cmd,"insert")!=0)\n\t\treturn;\n\tstrtok(s2, "\"");\n\tchar* value = strtok(NULL, "\""); //get second part\n\treturn strdup(value);\n}\n\n'
saveVal='void saveVal(char *value){\n\tprintf("saveValue>$ %s\n",value); //panpap\n}\n'
path="./bld/shell.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
count=1
#patch shell.c
File.foreach(path".bak"){|line|
	if count==37
		"#include \"../resources/header.h\" //panpap"
}
fw.close

#patch sqlite3.c
path="./bld/sqlite3.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
File.foreach(path".bak"){|line|
	elsif count==
		fw.puts readval+saveVal
	elsif count==
		fw.puts "patchCommand(readVal(zSql)); //panpap"
	elsif count==15203
		fw.puts "//panpap main"
	else
		fw.puts line
		count+=1
	end
}
fw.close



#if nSql{
#	char *val=readVal(zLine)
#	if val!=NULL
#		saveVal(val); //panpap
#}
