count=ARGV[0]
count=`grep "#define SLOTS_SIZE"  resources/header.h`.split(" ").last if count==nil
fw=File.new("populate.sql","w")
fw.puts "create table IF NOT EXISTS memenc_demo (name varchar PRIMARY KEY);"
for i in 0..count.to_i-1
	fw.puts "insert into memenc_demo (name) values (\"John Doe#{i}\");"
end
fw.close
#puts "Successfully Produced #{count} J. Does"
