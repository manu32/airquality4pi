

#ifndef DHT_RESULT_H_
#define DHT_RESULT_H_

struct DHTResult
{
    using value_type = float;

    DHTResult() : m_humidity(0.0F), m_temperature(0.0F)
    {

    }

    DHTResult(float humidity, float temperature)
    : m_humidity(humidity), m_temperature(temperature)
    {

    }

    value_type m_humidity;
    value_type m_temperature;
};

#endif // DHT_RESULT_H_