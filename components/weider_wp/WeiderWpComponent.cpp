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

#define VERSION "0.0.2"
#define WEIDER_RECV_TIMEOUT 60 * 1000

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

    binary_sensors_.push_back(this->e00_binary_sensor_);
    binary_sensors_.push_back(this->e01_binary_sensor_);
    binary_sensors_.push_back(this->e02_binary_sensor_);
    binary_sensors_.push_back(this->e03_binary_sensor_);
    binary_sensors_.push_back(this->e04_binary_sensor_);
    binary_sensors_.push_back(this->e05_binary_sensor_);
    binary_sensors_.push_back(this->e06_binary_sensor_);
    binary_sensors_.push_back(this->e07_binary_sensor_);
    binary_sensors_.push_back(this->e08_binary_sensor_);
    binary_sensors_.push_back(this->e09_binary_sensor_);
    binary_sensors_.push_back(this->e10_binary_sensor_);

    binary_sensors_.push_back(this->a00_binary_sensor_);
    binary_sensors_.push_back(this->a01_binary_sensor_);
    binary_sensors_.push_back(this->a02_binary_sensor_);
    binary_sensors_.push_back(this->a03_binary_sensor_);
    binary_sensors_.push_back(this->a04_binary_sensor_);
    binary_sensors_.push_back(this->a05_binary_sensor_);
    binary_sensors_.push_back(this->a06_binary_sensor_);
    binary_sensors_.push_back(this->a07_binary_sensor_);
    binary_sensors_.push_back(this->a08_binary_sensor_);
    binary_sensors_.push_back(this->a09_binary_sensor_);
    binary_sensors_.push_back(this->a10_binary_sensor_);
    binary_sensors_.push_back(this->a11_binary_sensor_);
    binary_sensors_.push_back(this->a12_binary_sensor_);
    binary_sensors_.push_back(this->a13_binary_sensor_);
    binary_sensors_.push_back(this->a14_binary_sensor_);
    binary_sensors_.push_back(this->a15_binary_sensor_);
    this->setup_timeout = millis();
}

void WeiderWpComponent::loop() {
    switch(this->process_flag_) {
        case PROCESS_SENSORS:
            this->process_sensors();
            break;
        case PROCESS_CODES:
            this->process_codes();
            break;
        case PROCESS_NONE:
        default:
            this->write();
            this->check_timeout();
    }
    this->read();
}

void WeiderWpComponent::write() {
    if(this->commands_to_send_.size() > 0) {
        this->command_expect_ = this->commands_to_send_.front();
        this->commands_to_send_.pop();
        this->write_str(this->command_expect_.c_str());
    }
}

void WeiderWpComponent::check_timeout() {
    if((millis() - this->last_received) > WEIDER_RECV_TIMEOUT) {
        ESP_LOGD(TAG, "Receive Timeout, invalidating all sensors");

        {
            std::map<std::string, sensor::Sensor*>::iterator it;
            for(it = this->name_to_sensor_mapping_.begin(); it != this->name_to_sensor_mapping_.end(); it++) {
                if(it->second) {
                    it->second->publish_state(NAN);
                }
            }
        }
        for(int i=0; i<this->binary_sensors_.size(); i++)
        {
            if(this->binary_sensors_[i])
                this->binary_sensors_[i]->publish_state(NAN);
        }

        this->last_received = millis();
    }
}

void WeiderWpComponent::process_codes() {


}

void WeiderWpComponent::process_error(std::string msg) {
    std::string part = msg.substr(4, msg.find(" ", 4) - 4);
    std::string error;

    int err = atoi(msg.substr(msg.rfind(" ") + 1).c_str());
    //ESP_LOGD(TAG, "Error: %s in part %s with message %d", msg.c_str(), part.c_str(), err);
    if(part == "Waermepumpe") {
        if(err & (1 << 0))
            error += "Pressostat WP1, ";
        if(err & (1 << 1))
            error += "Pressostat WP2, ";
        if(err & (1 << 2))
            error += "Sole/GW zu kalt, ";
        if(err & (1 << 3))
            error += "Hochdruck WP1, ";
        if(err & (1 << 4))
            error += "Hochdruck WP2, ";
        if(err & (1 << 5))
            error += "Verdampfer WP1, ";
        if(err & (1 << 6))
            error += "Verdampfer WP2, ";
        // According to the docs, this is 0x20, but this is plain wrong.
        if(err & (1 << 7))
            error += "SI-Kette/Thermorel., ";
    } else if(part == "Temp.sensor") {
        if(err & (1 << 0))
            error += "Vorlauffühler fehlt, ";
        if(err & (1 << 1))
            error += "Solefühler fehlt, ";
        if(err & (1 << 2))
            error += "Außenfühler fehlt, ";
        if(err & (1 << 3))
            error += "Raumfühler fehlt, ";
        if(err & (1 << 4))
            error += "Pufferfühler fehlt, ";
        if(err & (1 << 5))
            error += "Boilerfühler fehlt, ";
        if(err & (1 << 6))
            error += "Verdampferfühler WP1 fehlt, ";
        if(err & (1 << 7))
            error += "Verdampferfühler WP2 fehlt, ";
        if(err == 0)
            error += "Reservefühler fehlt, ";
    } else if(part == "Stroemung") {
        if(err & (1 << 0))
            error += "SWE1 immer aus, ";
        if(err & (1 << 1))
            error += "SWE2 immer aus, ";
        if(err & (1 << 2))
            error += "SWE1 immer ein, ";
        if(err & (1 << 3))
            error += "SWE2 immer ein, ";
        if(err & (1 << 4))
            error += "GW Vorrat WP1, ";
        if(err & (1 << 5))
            error += "GW Vorrat WP2, ";
    }
    this->current_error_ += msg.substr(4) + ": " + error.substr(0, error.size() - 2);
}

void WeiderWpComponent::process_sensors() {
    size_t pos = this->buffer.find(LINE_DELIMITER);
    if(pos == std::string::npos)
        return;

    //ESP_LOGD(TAG, "Processing: %s", this->buffer.c_str());
    //ESP_LOGD(TAG, "%s", this->buffer.c_str());

    std::string temp = this->buffer.substr(0, pos);
    while(temp[0] == '\f' || temp[0] == '\r' || temp[0] == '\n') {
        ESP_LOGD(TAG, "Removed %x", temp[0]);
        temp.erase(0, 1);
    }

    if(temp.rfind("T-", 0) == 0) {
        std::string key = temp.substr(0, 10);
        std::string val = temp.substr(10, 7);
        float val_f = atof(val.c_str());
        std::map<std::string, sensor::Sensor*>::iterator it;
        for(it = this->name_to_sensor_mapping_.begin(); it != this->name_to_sensor_mapping_.end(); it++) {
            if(key.find(it->first) == 0) {
                if(it->second)
                    it->second->publish_state(val_f);
            }
        }
    } else if(temp[0] == 'E' && temp[3] == ' ' && temp[1] != 'r') {
        // Input
        int number = atoi(temp.substr(1,2).c_str());
        if(number > 0 && number < 11)
            this->input_states_[number] = true;
    } else if(temp[0] == 'A' && temp[3] == ' ') {
        // Output
        int number = atoi(temp.substr(1,2).c_str());
        if(number > 0 && number < 16)
            this->output_states_[number] = true;
    } else if(temp.rfind("Err", 0) == 0) {
        // Error
        this->process_error(temp);
    } else {
        ESP_LOGD(TAG, "Did not yet understand %s", temp.c_str());
    }
    this->buffer.erase(0, pos + strlen(LINE_DELIMITER));
    if(this->buffer == "\r\n" || this->buffer == "") {
        ESP_LOGD(TAG, "Set flag NONE");
        this->process_flag_ = PROCESS_NONE;
        this->buffer.clear();
        for(int i=0; i<16; i++) {
            if(this->output_states_[i]) {
                if(this->binary_sensors_[i + 11])
                    this->binary_sensors_[i + 11]->publish_state(true);
            } else {
                if(this->binary_sensors_[i + 11])
                    this->binary_sensors_[i + 11]->publish_state(false);
            }
            this->output_states_[i] = false;
            if(i < 11) {
                if(this->input_states_[i]) {
                    if(this->binary_sensors_[i])
                        this->binary_sensors_[i]->publish_state(true);
                } else {
                    if(this->binary_sensors_[i])
                        this->binary_sensors_[i]->publish_state(false);
                }
                this->input_states_[i] = false;
            }
        }
        if(this->error_sensor_)
            this->error_sensor_->publish_state(this->current_error_);
        this->current_error_.clear();
    }
    //ESP_LOGD(TAG, "Buffer left: %s", this->buffer.c_str());

}

void WeiderWpComponent::reset() {
    this->commands_to_send_.push("R\r\n");
}

void WeiderWpComponent::read() {
    uint8_t cnt = this->available();
    uint8_t buf[512];
    uint8_t bytes = 0;
    while (cnt > 0) {
        //ESP_LOGD(TAG, "%d bytes available, reading", cnt);
        if((bytes + cnt) < sizeof(buf)) {
            this->read_array(&buf[bytes], cnt);
            bytes += cnt;
            cnt = this->available();
        } else {
            //ESP_LOGD(TAG, "rcv'd incomplete frame, clearing buffer");
            while(cnt > 0) {
                this->read_array(buf, cnt);
                cnt = this->available();
            }
            cnt = 0;
            bytes = 0;
        }
    }

    if(bytes == 0)
        return;

    //std::string tmp(reinterpret_cast<const char*>(buf), bytes);
    //ESP_LOGD(TAG, "Read %d bytes as %s", bytes, tmp.c_str());
    this->buffer.append(reinterpret_cast<const char*>(buf), bytes);

    if(this->buffer.find(FRAME_START) != 0 && this->command_expect_.empty()) {
        ESP_LOGD(TAG, "rcv'd incomplete frame: does not start with start tag");
        this->buffer.clear();
        return;
    }

    if(this->command_expect_ == "C") {
        if(this->buffer.rfind("Code 99") != std::string::npos) {
            this->process_flag_ = PROCESS_CODES;
            this->last_received = millis();
            this->command_expect_.clear();
        } else {
            return;
        }
    } else if(this->command_expect_ == "R") {
        ESP_LOGD(TAG, "Got answer to reset: %s", this->buffer.c_str());
        this->last_received = millis();
        this->buffer.clear();
        this->command_expect_.clear();
        return;
    }

    if(this->buffer.size() < 2) {
        ESP_LOGD(TAG, "Buffer has less than 2 bytes, invalid");
        return;
    }
    //if(this->buffer[this->buffer.size()-1] != '\n' || this->buffer[this->buffer.size()-2] != '\r') {
    if(this->buffer.rfind(FRAME_END) == std::string::npos) {
        ESP_LOGD(TAG, "rcv'd incomplete frame: frame end not found");
        return;
    }

    //ESP_LOGD(TAG, "Processing: %s", this->buffer.c_str());
    this->process_flag_ = PROCESS_SENSORS;
    this->last_received = millis();
}

} // weider_wp
} // esphome

