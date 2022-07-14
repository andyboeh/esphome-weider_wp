/* Copyright (C) 2022 Andreas Boehler
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "WeiderWpComponent.h"

#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/core/helpers.h"

#define VERSION "0.0.1"

namespace esphome {
namespace weider_wp {

static const char *TAG = "weider_wp";
static const char *FRAME_START = "\f\r\n";
static const char *FRAME_END = "\r\n\r\n";
static const char *LINE_DELIMITER = "\r\n";

using namespace esphome;

void WeiderWpComponent::setup() {
    ESP_LOGCONFIG(TAG, "Setting up Weider WP component...");

    if(this->pin_dtr_) {
        ESP_LOGD(TAG, "Setting DTR for PC mode");
        this->pin_dtr_->setup();
        this->pin_dtr_->digital_write(true);
    }
    this->bytes = 0;
    name_to_sensor_mapping_.insert({"T-Vorlauf ", this->feed_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Sole    ", this->brine_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Aussen  ", this->outside_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Raum    ", this->room_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Puffer  ", this->buffer_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Boiler  ", this->boiler_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-WP1     ", this->heatpump_1_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-WP2     ", this->heatpump_2_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Reserv1 ", this->reserved_1_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Reserv2 ", this->reserved_2_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Raumsoll", this->room_set_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Vorlauf2", this->feed_2_temperature_sensor_});
    name_to_sensor_mapping_.insert({"T-Sole2   ", this->brine_2_temperature_sensor_});

    name_to_binary_sensor_mapping_.insert({"E00 ", this->e00_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E01 ", this->e01_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E02 ", this->e02_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E03 ", this->e03_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E04 ", this->e04_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E05 ", this->e05_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E06 ", this->e06_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E07 ", this->e07_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E08 ", this->e08_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E09 ", this->e09_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E10 ", this->e10_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E11 ", this->e11_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E12 ", this->e12_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E13 ", this->e13_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E14 ", this->e14_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"E15 ", this->e15_binary_sensor_});

    name_to_binary_sensor_mapping_.insert({"A00 ", this->a00_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A01 ", this->a01_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A02 ", this->a02_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A03 ", this->a03_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A04 ", this->a04_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A05 ", this->a05_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A06 ", this->a06_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A07 ", this->a07_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A08 ", this->a08_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A09 ", this->a09_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A10 ", this->a10_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A11 ", this->a11_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A12 ", this->a12_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A13 ", this->a13_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A14 ", this->a14_binary_sensor_});
    name_to_binary_sensor_mapping_.insert({"A15 ", this->a15_binary_sensor_});

}

void WeiderWpComponent::loop() {
    this->read();
}

void WeiderWpComponent::read() {
    uint8_t cnt = this->available();
    while (cnt > 0) {
        //ESP_LOGD(TAG, "bytes available, reading");
        if((this->bytes + cnt) < sizeof(this->buffer)) {
            this->read_array(&this->buffer[bytes], cnt);
            this->bytes += cnt;
            cnt = this->available();
        } else {
            //ESP_LOGD(TAG, "rcv'd incomplete frame, clearing buffer");
            while(cnt > 0) {
                this->read_array(this->buffer, cnt);
                cnt = this->available();
            }
            cnt = 0;
            this->bytes = 0;
        }
    }
    if(this->bytes == 0)
        return;

    std::string buf(reinterpret_cast<const char*>(this->buffer), this->bytes);

    if(buf.find(FRAME_START) != 0) {
        //ESP_LOGD(TAG, "rcv'd incomplete frame: does not start with start tag");
        this->bytes = 0;
        return;
    }
    if(buf.find(FRAME_END) == std::string::npos) {
        //ESP_LOGD(TAG, "rcv'd incomplete frame: frame end not found");
        return;
    }
    size_t pos = 0;
    std::vector<binary_sensor::BinarySensor*> sensors_on;
    while((pos = buf.find(LINE_DELIMITER)) != std::string::npos) {
        std::string token = buf.substr(0, pos);
        ESP_LOGD(TAG, token.c_str());
        if(token.find("T-") == 0) {
            std::string key = token.substr(0, 10);
            std::string val = token.substr(10, 7);
            float val_f = atof(val.c_str());
            std::map<std::string, sensor::Sensor*>::iterator it;
            for(it = this->name_to_sensor_mapping_.begin(); it != this->name_to_sensor_mapping_.end(); it++) {
                if(key.find(it->first) == 0) {
                    if(it->second)
                        it->second->publish_state(val_f);
                }
            }
        } else {
            std::map<std::string, binary_sensor::BinarySensor*>::iterator it;
            for(it = this->name_to_binary_sensor_mapping_.begin(); it != this->name_to_binary_sensor_mapping_.end(); it++) {
                if(token.find(it->first) == 0) {
                    if(it->second)
                        sensors_on.push_back(it->second);
                }
            }
        }
        buf.erase(0, pos + strlen(LINE_DELIMITER));
    }
    std::map<std::string, binary_sensor::BinarySensor*>::iterator it;
    for(it = this->name_to_binary_sensor_mapping_.begin(); it != this->name_to_binary_sensor_mapping_.end(); it++) {
        if(std::find(sensors_on.begin(), sensors_on.end(), it->second) != sensors_on.end()) {
            if(it->second) {
                it->second->publish_state(true);
            }
        } else {
            if(it->second) {
                it->second->publish_state(false);
            }
        }
    }
    //ESP_LOGD(TAG, "Frame parsed successfully");
    this->bytes = 0;
}

} // hmlgw
} // weider_wp

