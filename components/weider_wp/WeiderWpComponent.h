#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <map>

namespace esphome {
namespace weider_wp {

typedef enum {
    PROCESS_NONE,
    PROCESS_SENSORS,
    PROCESS_COMMAND,
    PROCESS_CODES,
} t_process_states;


class WeiderWpComponent : public Component, public uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void read();

  void set_feed_temperature_sensor(sensor::Sensor *feed_temperature_sensor) { feed_temperature_sensor_ = feed_temperature_sensor; }
  void set_brine_temperature_sensor(sensor::Sensor *brine_temperature_sensor) { brine_temperature_sensor_ = brine_temperature_sensor; }
  void set_outside_temperature_sensor(sensor::Sensor *outside_temperature_sensor) { outside_temperature_sensor_ = outside_temperature_sensor; }
  void set_room_temperature_sensor(sensor::Sensor *room_temperature_sensor) { room_temperature_sensor_ = room_temperature_sensor; }
  void set_buffer_temperature_sensor(sensor::Sensor *buffer_temperature_sensor) { buffer_temperature_sensor_ = buffer_temperature_sensor; }
  void set_boiler_temperature_sensor(sensor::Sensor *boiler_temperature_sensor) { boiler_temperature_sensor_ = boiler_temperature_sensor; }
  void set_heatpump_1_temperature_sensor(sensor::Sensor *heatpump_1_temperature_sensor) { heatpump_1_temperature_sensor_ = heatpump_1_temperature_sensor; }
  void set_heatpump_2_temperature_sensor(sensor::Sensor *heatpump_2_temperature_sensor) { heatpump_2_temperature_sensor_ = heatpump_2_temperature_sensor; }
  void set_reserved_1_temperature_sensor(sensor::Sensor *reserved_1_temperature_sensor) { reserved_1_temperature_sensor_ = reserved_1_temperature_sensor; }
  void set_reserved_2_temperature_sensor(sensor::Sensor *reserved_2_temperature_sensor) { reserved_2_temperature_sensor_ = reserved_2_temperature_sensor; }
  void set_room_set_temperature_sensor(sensor::Sensor *room_set_temperature_sensor) { room_set_temperature_sensor_ = room_set_temperature_sensor; }
  void set_feed_2_temperature_sensor(sensor::Sensor *feed_2_temperature_sensor) { feed_2_temperature_sensor_ = feed_2_temperature_sensor; }
  void set_brine_2_temperature_sensor(sensor::Sensor *brine_2_temperature_sensor) { brine_2_temperature_sensor_ = brine_2_temperature_sensor; }

  void set_e00_binary_sensor(binary_sensor::BinarySensor *e00_binary_sensor) { e00_binary_sensor_ = e00_binary_sensor; }
  void set_e01_binary_sensor(binary_sensor::BinarySensor *e01_binary_sensor) { e01_binary_sensor_ = e01_binary_sensor; }
  void set_e02_binary_sensor(binary_sensor::BinarySensor *e02_binary_sensor) { e02_binary_sensor_ = e02_binary_sensor; }
  void set_e03_binary_sensor(binary_sensor::BinarySensor *e03_binary_sensor) { e03_binary_sensor_ = e03_binary_sensor; }
  void set_e04_binary_sensor(binary_sensor::BinarySensor *e04_binary_sensor) { e04_binary_sensor_ = e04_binary_sensor; }
  void set_e05_binary_sensor(binary_sensor::BinarySensor *e05_binary_sensor) { e05_binary_sensor_ = e05_binary_sensor; }
  void set_e06_binary_sensor(binary_sensor::BinarySensor *e06_binary_sensor) { e06_binary_sensor_ = e06_binary_sensor; }
  void set_e07_binary_sensor(binary_sensor::BinarySensor *e07_binary_sensor) { e07_binary_sensor_ = e07_binary_sensor; }
  void set_e08_binary_sensor(binary_sensor::BinarySensor *e08_binary_sensor) { e08_binary_sensor_ = e08_binary_sensor; }
  void set_e09_binary_sensor(binary_sensor::BinarySensor *e09_binary_sensor) { e09_binary_sensor_ = e09_binary_sensor; }
  void set_e10_binary_sensor(binary_sensor::BinarySensor *e10_binary_sensor) { e10_binary_sensor_ = e10_binary_sensor; }

  void set_a00_binary_sensor(binary_sensor::BinarySensor *a00_binary_sensor) { a00_binary_sensor_ = a00_binary_sensor; }
  void set_a01_binary_sensor(binary_sensor::BinarySensor *a01_binary_sensor) { a01_binary_sensor_ = a01_binary_sensor; }
  void set_a02_binary_sensor(binary_sensor::BinarySensor *a02_binary_sensor) { a02_binary_sensor_ = a02_binary_sensor; }
  void set_a03_binary_sensor(binary_sensor::BinarySensor *a03_binary_sensor) { a03_binary_sensor_ = a03_binary_sensor; }
  void set_a04_binary_sensor(binary_sensor::BinarySensor *a04_binary_sensor) { a04_binary_sensor_ = a04_binary_sensor; }
  void set_a05_binary_sensor(binary_sensor::BinarySensor *a05_binary_sensor) { a05_binary_sensor_ = a05_binary_sensor; }
  void set_a06_binary_sensor(binary_sensor::BinarySensor *a06_binary_sensor) { a06_binary_sensor_ = a06_binary_sensor; }
  void set_a07_binary_sensor(binary_sensor::BinarySensor *a07_binary_sensor) { a07_binary_sensor_ = a07_binary_sensor; }
  void set_a08_binary_sensor(binary_sensor::BinarySensor *a08_binary_sensor) { a08_binary_sensor_ = a08_binary_sensor; }
  void set_a09_binary_sensor(binary_sensor::BinarySensor *a09_binary_sensor) { a09_binary_sensor_ = a09_binary_sensor; }
  void set_a10_binary_sensor(binary_sensor::BinarySensor *a10_binary_sensor) { a10_binary_sensor_ = a10_binary_sensor; }
  void set_a11_binary_sensor(binary_sensor::BinarySensor *a11_binary_sensor) { a11_binary_sensor_ = a11_binary_sensor; }
  void set_a12_binary_sensor(binary_sensor::BinarySensor *a12_binary_sensor) { a12_binary_sensor_ = a12_binary_sensor; }
  void set_a13_binary_sensor(binary_sensor::BinarySensor *a13_binary_sensor) { a13_binary_sensor_ = a13_binary_sensor; }
  void set_a14_binary_sensor(binary_sensor::BinarySensor *a14_binary_sensor) { a14_binary_sensor_ = a14_binary_sensor; }
  void set_a15_binary_sensor(binary_sensor::BinarySensor *a15_binary_sensor) { a15_binary_sensor_ = a15_binary_sensor; }

  void set_dtr_pin(GPIOPin *pin_dtr) { pin_dtr_ = pin_dtr; }
  float get_setup_priority() const override { return setup_priority::DATA; }

  void check_timeout();
  void process_sensors();
  void process_codes();
  void write();

 protected:
  std::string buffer;
  GPIOPin *pin_dtr_{nullptr};
  uint32_t last_received{0};
  uint32_t setup_timeout{0};
  bool input_states_[11];
  bool output_states_[16];
  t_process_states process_flag_{PROCESS_NONE};
  std::map<std::string, sensor::Sensor*> name_to_sensor_mapping_;
  std::vector<binary_sensor::BinarySensor*> binary_sensors_;
  std::string command_expect_;
  std::vector<std::string> commands_to_send_;

  sensor::Sensor *feed_temperature_sensor_;
  sensor::Sensor *brine_temperature_sensor_;
  sensor::Sensor *outside_temperature_sensor_;
  sensor::Sensor *room_temperature_sensor_;
  sensor::Sensor *buffer_temperature_sensor_;
  sensor::Sensor *boiler_temperature_sensor_;
  sensor::Sensor *heatpump_1_temperature_sensor_;
  sensor::Sensor *heatpump_2_temperature_sensor_;
  sensor::Sensor *reserved_1_temperature_sensor_;
  sensor::Sensor *reserved_2_temperature_sensor_;
  sensor::Sensor *room_set_temperature_sensor_;
  sensor::Sensor *feed_2_temperature_sensor_;
  sensor::Sensor *brine_2_temperature_sensor_;

  binary_sensor::BinarySensor *e00_binary_sensor_;
  binary_sensor::BinarySensor *e01_binary_sensor_;
  binary_sensor::BinarySensor *e02_binary_sensor_;
  binary_sensor::BinarySensor *e03_binary_sensor_;
  binary_sensor::BinarySensor *e04_binary_sensor_;
  binary_sensor::BinarySensor *e05_binary_sensor_;
  binary_sensor::BinarySensor *e06_binary_sensor_;
  binary_sensor::BinarySensor *e07_binary_sensor_;
  binary_sensor::BinarySensor *e08_binary_sensor_;
  binary_sensor::BinarySensor *e09_binary_sensor_;
  binary_sensor::BinarySensor *e10_binary_sensor_;

  binary_sensor::BinarySensor *a00_binary_sensor_;
  binary_sensor::BinarySensor *a01_binary_sensor_;
  binary_sensor::BinarySensor *a02_binary_sensor_;
  binary_sensor::BinarySensor *a03_binary_sensor_;
  binary_sensor::BinarySensor *a04_binary_sensor_;
  binary_sensor::BinarySensor *a05_binary_sensor_;
  binary_sensor::BinarySensor *a06_binary_sensor_;
  binary_sensor::BinarySensor *a07_binary_sensor_;
  binary_sensor::BinarySensor *a08_binary_sensor_;
  binary_sensor::BinarySensor *a09_binary_sensor_;
  binary_sensor::BinarySensor *a10_binary_sensor_;
  binary_sensor::BinarySensor *a11_binary_sensor_;
  binary_sensor::BinarySensor *a12_binary_sensor_;
  binary_sensor::BinarySensor *a13_binary_sensor_;
  binary_sensor::BinarySensor *a14_binary_sensor_;
  binary_sensor::BinarySensor *a15_binary_sensor_;

};

}  // namespace weider_wp
}  // namespace esphome
