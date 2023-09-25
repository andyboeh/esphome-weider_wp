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
from esphome.components import binary_sensor
from esphome.const import CONF_ID

# ESPHome doesn't know the Stream abstraction yet, so hardcode to use a UART for now.

DEPENDENCIES = ["weider_wp"]

from . import WeiderWpComponent

CONF_E00 = "heatpump_e00"
CONF_E01 = "heatpump_e01"
CONF_E02 = "heatpump_e02"
CONF_E03 = "heatpump_e03"
CONF_E04 = "heatpump_e04"
CONF_E05 = "heatpump_e05"
CONF_E06 = "heatpump_e06"
CONF_E07 = "heatpump_e07"
CONF_E08 = "heatpump_e08"
CONF_E09 = "heatpump_e09"
CONF_E10 = "heatpump_e10"

CONF_A00 = "heatpump_a00"
CONF_A01 = "heatpump_a01"
CONF_A02 = "heatpump_a02"
CONF_A03 = "heatpump_a03"
CONF_A04 = "heatpump_a04"
CONF_A05 = "heatpump_a05"
CONF_A06 = "heatpump_a06"
CONF_A07 = "heatpump_a07"
CONF_A08 = "heatpump_a08"
CONF_A09 = "heatpump_a09"
CONF_A10 = "heatpump_a10"
CONF_A11 = "heatpump_a11"
CONF_A12 = "heatpump_a12"
CONF_A13 = "heatpump_a13"
CONF_A14 = "heatpump_a14"
CONF_A15 = "heatpump_a15"

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.use_id(WeiderWpComponent),
			cv.Optional(CONF_E00): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E01): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E02): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E03): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E04): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E05): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E06): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E07): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E08): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E09): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_E10): binary_sensor.binary_sensor_schema(),

			cv.Optional(CONF_A00): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A01): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A02): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A03): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A04): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A05): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A06): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A07): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A08): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A09): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A10): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A11): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A12): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A13): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A14): binary_sensor.binary_sensor_schema(),
			cv.Optional(CONF_A15): binary_sensor.binary_sensor_schema(),

		}
	)
)

async def to_code(config):
	parent = await cg.get_variable(config[CONF_ID])

	if CONF_E00 in config:
		conf = config[CONF_E00]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e00_binary_sensor(sens))
	if CONF_E01 in config:
		conf = config[CONF_E01]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e01_binary_sensor(sens))
	if CONF_E02 in config:
		conf = config[CONF_E02]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e02_binary_sensor(sens))
	if CONF_E03 in config:
		conf = config[CONF_E03]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e03_binary_sensor(sens))
	if CONF_E04 in config:
		conf = config[CONF_E04]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e04_binary_sensor(sens))
	if CONF_E05 in config:
		conf = config[CONF_E05]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e05_binary_sensor(sens))
	if CONF_E06 in config:
		conf = config[CONF_E06]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e06_binary_sensor(sens))
	if CONF_E07 in config:
		conf = config[CONF_E07]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e07_binary_sensor(sens))
	if CONF_E08 in config:
		conf = config[CONF_E08]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e08_binary_sensor(sens))
	if CONF_E09 in config:
		conf = config[CONF_E09]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e09_binary_sensor(sens))
	if CONF_E10 in config:
		conf = config[CONF_E10]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_e10_binary_sensor(sens))

	if CONF_A00 in config:
		conf = config[CONF_A00]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a00_binary_sensor(sens))
	if CONF_A01 in config:
		conf = config[CONF_A01]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a01_binary_sensor(sens))
	if CONF_A02 in config:
		conf = config[CONF_A02]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a02_binary_sensor(sens))
	if CONF_A03 in config:
		conf = config[CONF_A03]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a03_binary_sensor(sens))
	if CONF_A04 in config:
		conf = config[CONF_A04]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a04_binary_sensor(sens))
	if CONF_A05 in config:
		conf = config[CONF_A05]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a05_binary_sensor(sens))
	if CONF_A06 in config:
		conf = config[CONF_A06]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a06_binary_sensor(sens))
	if CONF_A07 in config:
		conf = config[CONF_A07]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a07_binary_sensor(sens))
	if CONF_A08 in config:
		conf = config[CONF_A08]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a08_binary_sensor(sens))
	if CONF_A09 in config:
		conf = config[CONF_A09]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a09_binary_sensor(sens))
	if CONF_A10 in config:
		conf = config[CONF_A10]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a10_binary_sensor(sens))
	if CONF_A11 in config:
		conf = config[CONF_A11]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a11_binary_sensor(sens))
	if CONF_A12 in config:
		conf = config[CONF_A12]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a12_binary_sensor(sens))
	if CONF_A13 in config:
		conf = config[CONF_A13]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a13_binary_sensor(sens))
	if CONF_A14 in config:
		conf = config[CONF_A14]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a14_binary_sensor(sens))
	if CONF_A15 in config:
		conf = config[CONF_A15]
		sens = await binary_sensor.new_binary_sensor(conf)
		cg.add(parent.set_a15_binary_sensor(sens))


