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
    while((pos = buf.find(LINE_DELIMITER)) != std::string::npos) {
        std::string token = buf.substr(0, pos);
        ESP_LOGD(TAG, token.c_str());
        if(token.find("T-") != std::string::npos) {
            std::string key = token.substr(0, 10);
            std::string val = token.substr(10, 7);
            float val_f = atof(val.c_str());
            std::map<std::string, sensor::Sensor*>::iterator it;
            for(it = this->name_to_sensor_mapping_.begin(); it != this->name_to_sensor_mapping_.end(); it++) {
                if(key.find(it->first) != std::string::npos) {
                    if(it->second)
                        it->second->publish_state(val_f);
                }
            }
        }
        buf.erase(0, pos + strlen(LINE_DELIMITER));
    }
    //ESP_LOGD(TAG, "Frame parsed successfully");
    this->bytes = 0;
}

} // hmlgw
} // weider_wp

