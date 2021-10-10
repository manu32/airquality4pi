
#include "db/db_manager.h"
#include "dht_sensor/dht_sensor.h"

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    std::cout << "setup done" << std::endl;
    std::string database_dir =
        "../../../../playground/sqlite_example/dhtdata.db";
    ::std::unique_ptr<DBManager> database =
        ::std::make_unique<DBManager>(database_dir);

    try
    {
        database->open_db();
    }
    catch(::std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "finished dht sensor example" << std::endl;
    return 0;
}