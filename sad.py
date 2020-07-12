import sys
import os

# a = open("index.html");
# string = ""
# for i in range(24):
#    string += a.readline() + "\n";
#
# string += a.readline()[:40] + "70/100 </h1>\n";
# for i in range(18):
#     string += a.readline() + "\n";
# string += sys.argv[1];
#
# for i in a.readlines():
#     string += i +"\n";
#
# o = open("index.html", 'w');
# o.write(string);
# a.close();
# o.close();
a = open("base.html");
string = "";

for i in range(43):
    string += a.readline() + "\n";

log = open("log.txt")
count = 0
for line in log.readlines():
    string += "<p> Test case" + str(count) + "</p>\n"
    if line.strip() == "pass":
        color = "color:#008000"
    else:
        color = "color:#FF0000"
    string += "<ol style =" + color + ">"+ line + "</ol>\n";
    count+=1;
for i in a.readlines():
    string += i + "\n"
o = open("index.html", "w");
o.write(string);
o.close();


os.system("python -m http.server");

