
#include "dht_sensor/dht_sensor.h"

#include <stdint.h>

#include <thread>

#include <gtest/gtest.h>

using namespace rpi::dht;

static constexpr uint8_t max_cycles = 10U;

TEST(unit_test_dht_sensor, measurement)
{
    // check if measurement was successfull within 10 cycles

    DHTSensor::measurement_result_type result{};
    ::std::unique_ptr<DHTSensor> sensor = ::std::make_unique<DHTSensor>();
    
    for (auto count = 0U; count < max_cycles; ++count)
    {
        auto result = sensor->measure();

        if (result.has_value())
        {
            break;
        }

        // wait for 1 second
        ::std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

#ifdef __ARM_ARCH
    EXPECT_TRUE(result.has_value());
#else  //__ARM_ARCH
    EXPECT_FALSE(result.has_value());
#endif //__ARM_ARCH
}