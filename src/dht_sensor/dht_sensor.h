
#include "dht_result.h"

#include <stdint.h>

#include <optional>
#include <utility>

#define DHT_SENSOR_DEFAULT_PIN 7U // GPIO-22

namespace rpi::dht
{

struct DHTConfiguration
{
    using pin_type = uint8_t;
    using size_type = uint16_t;

    constexpr DHTConfiguration()
        : m_gpio_pin(DHT_SENSOR_DEFAULT_PIN), m_max_measurements(85U)
    {
    }

    constexpr DHTConfiguration(uint8_t pin, uint16_t max_measurements)
        : m_gpio_pin(pin), m_max_measurements(max_measurements)
    {
    }

    constexpr pin_type connected_pin() const
    {
        return m_gpio_pin;
    }

    constexpr size_type max_measurements() const
    {
        return m_max_measurements;
    }

    uint8_t m_gpio_pin;
    uint16_t m_max_measurements;
};

class DHTSensor
{
  public:
    using measurement_result_type = ::std::optional<DHTResult>;
    using config_type = DHTConfiguration;

    DHTSensor();

    bool update_config(config_type &config);
    measurement_result_type measure();

  private:
    config_type m_config;
    int m_registers[5];
};

}; // namespace rpi::dht