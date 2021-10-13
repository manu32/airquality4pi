
#include "db/db_manager.h"
#include "dht_sensor/dht_sensor.h"
#include "db/dht_sql_builder.h"

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{

    DHTReadingSQLBuilder sql;

    std::string command =
        sql.insert_temperature(32.0F).insert_humidity(85.0F).now().into("dhtreadings");

    std::cout << command << std::endl;
    return 0;
}