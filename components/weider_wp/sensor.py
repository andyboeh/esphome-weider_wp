# Copyright (C) 2022 Andreas Boehler
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_CELSIUS, DEVICE_CLASS_TEMPERATURE, STATE_CLASS_MEASUREMENT

# ESPHome doesn't know the Stream abstraction yet, so hardcode to use a UART for now.

DEPENDENCIES = ["weider_wp"]

from . import WeiderWpComponent

CONF_TEMPERATURE_FEED = 'feed_temperature'
CONF_TEMPERATURE_BRINE = 'brine_temperature'
CONF_TEMPERATURE_OUTSIDE = 'outside_temperature'
CONF_TEMPERATURE_ROOM = 'room_temperature'
CONF_TEMPERATURE_BUFFER = 'buffer_temperature'
CONF_TEMPERATURE_BOILER = 'boiler_temperature'
CONF_TEMPERATURE_HEATPUMP_1 = 'heatpump_1_temperature'
CONF_TEMPERATURE_HEATPUMP_2 = 'heatpump_2_temperature'
CONF_TEMPERATURE_RESERVED_1 = 'reserved_1_temperature'
CONF_TEMPERATURE_RESERVED_2 = 'reserved_2_temperature'
CONF_TEMPERATURE_ROOM_SET = 'room_set_temperature'
CONF_TEMPERATURE_FEED_2 = 'feed_2_temperature'
CONF_TEMPERATURE_BRINE_2 = 'brine_2_temperature'
CONF_PT1000_HP1 = 'heatpump_1_pt1000'
CONF_STEPS_HP1 = 'heatpump_1_steps'
CONF_PT1000_HP2 = 'heatpump_2_pt1000'
CONF_STEPS_HP2 = 'heatpump_2_steps'
CONF_MIXERPOS_1 = 'mixerpos_1'
CONF_MIXERPOS_2 = 'mixerpos_2'
CONF_LB = 'lb'

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.use_id(WeiderWpComponent),
			cv.Optional(CONF_TEMPERATURE_FEED): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
		    cv.Optional(CONF_TEMPERATURE_BRINE): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_OUTSIDE): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_ROOM): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_BUFFER): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_BOILER): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_HEATPUMP_1): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_HEATPUMP_2): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_RESERVED_1): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_RESERVED_2): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_ROOM_SET): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_FEED_2): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			cv.Optional(CONF_TEMPERATURE_BRINE_2): sensor.sensor_schema(
			    unit_of_measurement = UNIT_CELSIUS,
			    accuracy_decimals = 1,
			    device_class = DEVICE_CLASS_TEMPERATURE,
			    state_class = STATE_CLASS_MEASUREMENT,
			),
			
		}
	)
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])

    if CONF_TEMPERATURE_FEED in config:
        conf = config[CONF_TEMPERATURE_FEED]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_feed_temperature_sensor(sens))

    if CONF_TEMPERATURE_BRINE in config:
        conf = config[CONF_TEMPERATURE_BRINE]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_brine_temperature_sensor(sens))

    if CONF_TEMPERATURE_OUTSIDE in config:
        conf = config[CONF_TEMPERATURE_OUTSIDE]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_outside_temperature_sensor(sens))

    if CONF_TEMPERATURE_ROOM in config:
        conf = config[CONF_TEMPERATURE_ROOM]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_room_temperature_sensor(sens))

    if CONF_TEMPERATURE_BUFFER in config:
        conf = config[CONF_TEMPERATURE_BUFFER]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_buffer_temperature_sensor(sens))

    if CONF_TEMPERATURE_BOILER in config:
        conf = config[CONF_TEMPERATURE_BOILER]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_boiler_temperature_sensor(sens))

    if CONF_TEMPERATURE_HEATPUMP_1 in config:
        conf = config[CONF_TEMPERATURE_HEATPUMP_1]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_heatpump_1_temperature_sensor(sens))

    if CONF_TEMPERATURE_HEATPUMP_2 in config:
        conf = config[CONF_TEMPERATURE_HEATPUMP_2]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_heatpump_2_temperature_sensor(sens))

    if CONF_TEMPERATURE_RESERVED_1 in config:
        conf = config[CONF_TEMPERATURE_RESERVED_1]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_reserved_1_temperature_sensor(sens))

    if CONF_TEMPERATURE_RESERVED_2 in config:
        conf = config[CONF_TEMPERATURE_RESERVED_2]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_reserved_2_temperature_sensor(sens))

    if CONF_TEMPERATURE_ROOM_SET in config:
        conf = config[CONF_TEMPERATURE_ROOM_SET]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_room_set_temperature_sensor(sens))

    if CONF_TEMPERATURE_FEED_2 in config:
        conf = config[CONF_TEMPERATURE_FEED_2]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_feed_2_temperature_sensor(sens))

    if CONF_TEMPERATURE_BRINE_2 in config:
        conf = config[CONF_TEMPERATURE_BRINE_2]
        sens = await sensor.new_sensor(conf)
        cg.add(parent.set_brine_2_temperature_sensor(sens))
