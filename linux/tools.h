#ifndef LINUX_TOOLS
#define LINUX_TOOLS

#include <sstream>
#include "../sqlite3.h"

std::stringstream get_chrome_pass(sqlite3* db);

#endif