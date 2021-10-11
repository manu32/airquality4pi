
#ifndef DHT_SQL_BUILDER_
#define DHT_SQL_BUILDER_

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

class DHTSQLBuilder
{

::std::stringstream m_stream;

public:

    DHTSQLBuilder()
    : m_stream()
    {
        m_stream << "INSERT INTO ";
    }

    DHTSQLBuilder& insert_measurement_into_table(std::string table)
    {  
        m_stream << table << " (HUMIDITY,TEMPERATURE,CURRENTDATE,CURRENTIME) VALUES (";
        return *this;
    }

    DHTSQLBuilder& with_humidity(float humidity)
    {
        m_stream << std::fixed << std::setprecision(2) << humidity << ",";
        return *this;
    }

    DHTSQLBuilder& with_temperature(float temperature)
    {
        m_stream << std::fixed << std::setprecision(2) << temperature << ",";
        return *this;
    }

    DHTSQLBuilder& on_date(std::string date)
    {
        m_stream << date << ",";
        return *this;
    }

    DHTSQLBuilder& at_time(std::string time)
    {
        m_stream << time << ");";
        return *this;
    }

    DHTSQLBuilder& with_current_date_and_time()
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        m_stream << std::put_time(std::localtime(&time), "%Y-%m-%d") << "," << 
        std::put_time(std::localtime(&time), "%H:%M:%S") << ");";
        return *this;
    }

    ::std::string command() 
    {
        return m_stream.str();
    }

};

#endif // DHT_SQL_BUILDER_
