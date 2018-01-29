path="./bld/shell.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
count=1
File.foreach(path".bak"){|line|
	if count==37
		"#include \"resources/header.h\"
	elsif count==14845
		fw.puts "patchCommand(getVal(zSql)); //panpap"
	elsif count==15203
		fw.puts "//panpap"
	else
		fw.puts line
		count+=1
	end
}
fw.close
