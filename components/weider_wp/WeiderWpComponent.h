#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <map>

namespace esphome {
namespace weider_wp {


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
  

  void set_dtr_pin(GPIOPin *pin_dtr) { pin_dtr_ = pin_dtr; }
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  int bytes;
  uint8_t buffer[4096];
  GPIOPin *pin_dtr_{nullptr};
  std::map<std::string, sensor::Sensor*> name_to_sensor_mapping_;
  std::vector<std::pair<std::string, std::string> > write_queue;
  bool expect{false};
  std::string last_command;
  int update_interval{5000};
  uint32_t last_update_{0};
  
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
};

}  // namespace weider_wp
}  // namespace esphome
