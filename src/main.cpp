
#include "dht_sensor/dht_sensor.h"

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    std::cout << "setup done" << std::endl;

    rpi::dht::DHTSensor dht;

    for (auto count = 0; count < 100U; ++count)
    {
        auto result = dht.measure();

        if (result.has_value())
        {
            std::cout << "temp: " << result.value().temperature()
                      << "°C ,humidity: " << result.value().humidity() << " %"
                      << std::endl;
            break;
        }
        std::cout << count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "finished dht sensor example" << std::endl;
    return 0;
}