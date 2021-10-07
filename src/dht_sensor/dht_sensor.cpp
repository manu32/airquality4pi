
#include "dht_sensor.h"

#include <stdint.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

int data[5] = {0, 0, 0, 0, 0};

namespace rpi::dht
{

DHTSensor::DHTSensor() : m_config()
{
    if (wiringPiSetup() == -1)
    {
        throw std::runtime_error("Couldn't setup WiringPi.");
    }
}

DHTSensor::measurement_result_type DHTSensor::measure()
{
    uint8_t last_state = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    /* pull pin down for 18 milliseconds */
    pinMode(m_config.connected_pin(), OUTPUT);
    digitalWrite(m_config.connected_pin(), LOW);
    delay(18);

    /* prepare to read the pin */
    pinMode(m_config.connected_pin(), INPUT);

    /* detect change and read data */
    for (i = 0; i < m_config.max_measurements(); i++)
    {
        counter = 0;
        while (digitalRead(m_config.connected_pin()) == last_state)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
            {
                break;
            }
        }
        last_state = digitalRead(m_config.connected_pin());

        if (counter == 255)
            break;

        /* ignore first 3 transitions */
        if ((i >= 4) && (i % 2 == 0))
        {
            /* shove each bit into the storage bytes */
            data[j / 8] <<= 1;
            if (counter > 16)
                data[j / 8] |= 1;
            j++;
        }
    }

    /*
     * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
     * print it out if data is good
     */
    if ((j >= 40) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        float h = (float)((data[0] << 8) + data[1]) / 10;
        if (h > 100)
        {
            h = data[0]; // for DHT11
        }
        float temperature = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;

        if (temperature > 125)
        {
            temperature = data[2]; // for DHT11
        }
        if (data[2] & 0x80)
        {
            temperature = -temperature;
        }

        auto humidity = temperature * 1.8f + 32;

        return DHTResult(std::move(humidity), std::move(temperature));
    }
    else
    {
        // measured data not good
        return std::nullopt;
    }

    // always return false on non-arm-machines since there is no HW installed
    // return std::nullopt;
}

}; // namespace rpi::dht
