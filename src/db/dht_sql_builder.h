
#ifndef DHT_SQL_BUILDER_
#define DHT_SQL_BUILDER_

#include "sql_builder.h"

class DHTReadingSQLBuilder : public SQLInsertBuilder
{

  public:
    DHTReadingSQLBuilder()
    {
    }

    DHTReadingSQLBuilder &insert_temperature(const float &temperature)
    {
        insert("temperature", temperature);
        return *this;
    }

    DHTReadingSQLBuilder &insert_humidity(const float &humidity)
    {
        insert("humidity", humidity);
        return *this;
    }

    DHTReadingSQLBuilder &now()
    {
        auto in_time_t = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        insert("currentdate", time_t_to_str(in_time_t, time_format::date()));
        insert("currentime", time_t_to_str(in_time_t, time_format::time()));
        return *this;
    }

    DHTReadingSQLBuilder &at_time(const std::chrono::system_clock::time_point& time)
    {
        auto in_time_t = std::chrono::system_clock::to_time_t(time);
        insert("currentdate", time_t_to_str(in_time_t, time_format::date()));
        insert("currentime", time_t_to_str(in_time_t, time_format::time()));
        return *this;
    }
};

#endif // DHT_SQL_BUILDER_
