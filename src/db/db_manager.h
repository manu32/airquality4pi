
#ifndef DB_MANAGER_H_
#define DB_MANAGER_H_

#include <exception>
#include <filesystem>
#include <sqlite3.h>
#include <string.h>
#include <iostream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

class DBManager
{
    ::std::string m_filename;
    sqlite3 *m_db;
    bool m_is_open;

  public:
    explicit DBManager(const ::std::string &filename)
        : m_filename(filename), m_is_open(false)
    {
    }

    ~DBManager()
    {
        std::cout << "close database"<< std::endl;
        if(is_open())
        {
            close_db();
        }
    }

    constexpr bool is_open()
    {
        return m_is_open;
    }

    bool db_exists()
    {
        return ::std::filesystem::exists(m_filename);
    }

    void open_db()
    {
        if (db_exists())
        {
            auto success = sqlite3_open(m_filename.c_str(), &m_db);

            if (success == SQLITE_OK)
            {
                m_is_open = true;
            }
            else
            {
                throw std::runtime_error("Could not open database.");
            }
        }
        else
        {
             throw std::runtime_error("Could not find database file.");
        }


    }

    bool execute(const std::string& sql_command)
    {
        char *zErrMsg = 0;
        auto success = sqlite3_exec(m_db, sql_command.c_str(), callback, 0, &zErrMsg);

        return success == SQLITE_OK;
    }

    void close_db()
    {
        m_is_open = !sqlite3_close(m_db);
    };
};

#endif // DB_MANAGER_H_