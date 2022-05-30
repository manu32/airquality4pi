
#include "db/db_manager.h"
#include "db/dht_sql_builder.h"
#include "dht_sensor/dht_sensor.h"

#include <iostream>
#include <thread>

void measure_and_save(rpi::dht::DHTSensor &sensor, DBManager &database)
{
    while (true)
    {
        auto measurement = sensor.measure();

        if (measurement.has_value())
        {
            DHTReadingSQLBuilder sql;
            std::string command =
                sql.insert_temperature(measurement.value().temperature())
                    .insert_humidity(measurement.value().humidity())
                    .now()
                    .into("dhtreadings");

            std::cout << std::setprecision(2) << "Temp: " << measurement.value().temperature() << 
                " Hum: " << measurement.value().humidity() << std::endl;

            database.open_db();
            database.execute(command);
            database.close_db();

            return;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main(int argc, char *argv[])
{
    std::unique_ptr<rpi::dht::DHTSensor> sensor =
        std::make_unique<rpi::dht::DHTSensor>();

    std::unique_ptr<DBManager> db = std::make_unique<DBManager>(
        "dhtdata.db");

    std::cout << "start server for measurements"<< std::endl;

    while (true)
    {
        measure_and_save(*sensor, *db);
        std::this_thread::sleep_for(std::chrono::seconds(180));
    }

    return 0;
}