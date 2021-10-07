
#ifndef DHT_RESULT_H_
#define DHT_RESULT_H_

#include <utility>

struct DHTResult
{
    using value_type = float;

    DHTResult() : m_humidity(0.0F), m_temperature(0.0F)
    {
    }

    DHTResult(value_type &&humidity, value_type &&temperature)
        : m_humidity(humidity), m_temperature(temperature)
    {
    }

    value_type temperature() const
    {
        return m_temperature;
    }

    value_type humidity() const
    {
        return m_humidity;
    }

    value_type m_humidity;
    value_type m_temperature;
};

#endif // DHT_RESULT_H_