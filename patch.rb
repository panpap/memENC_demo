readval='char *readCmd(char *line){\n\tprintf(\"readCmd>$ %s\n\",line);//memenc\n\tchar s[256], s2[256];\n\tstrcpy(s, line);\n\tstrcpy(s2, line);\n\tchar* cmd = strtok(s, " ");\n\tif (strcmp(cmd,"insert")!=0)\n\t\treturn;\n\tstrtok(s2, "\"");\n\tchar* value = strtok(NULL, "\""); //get second part\n\treturn strdup(value);\n}\n\n'
headers='#include "../resources/header.h"\t//memenc\n'
saveVal='char *shared_buffer;\nvoid saveVal(char *value){//memenc\n\tint8_t computed_cipher[STRING_SIZE];\n\ttime_t t;\n\tsrand((unsigned) time(&t));\n\tint pos=rand()%SLOTS_SIZE;\n\tshared_buffer = create_shared_mem_buffer();\n\taes128_load_key(enc_key);\n\taes128_enc(plain,computed_cipher);\n\tint c=0;pos--;\n\tfor (c=pos*STRING_SIZE; c < pos*STRING_SIZE+strlen((char *)computed_cipher); c++)\n\t\tshared_buffer[c]=computed_cipher[c-(pos*STRING_SIZE)];\n\tprintf("\nSECURELY INSERTED %d\n",pos);\n\treturn shared_buffer; \n}\n'\

#patch sqlite3.c
path="./bld/shell.c"
system("mv "+path+" "+path+".bak")
fw=File.new(path,"w")
count=1
File.foreach(path".bak"){|line|
	if count==90
		fw.puts headers
	elsif count==9876
		fw.puts readval+saveVal
	elsif count==9919
		fw.puts "char *val=readCmd(zLine)\tif val!=NULL\n\t\tsaveVal(val); //memenc\n\n"
	elsif count==15552
		fw.puts "shmdt(shared_buffer);//memenc main"
	else
		fw.puts line
		count+=1
	end
}
fw.close
system("make > /dev/null 2>&1")
