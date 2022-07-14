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
from esphome import pins
from esphome.components import uart, sensor
from esphome.const import CONF_ID

# ESPHome doesn't know the Stream abstraction yet, so hardcode to use a UART for now.

DEPENDENCIES = ["uart"]

weiderwp_ns = cg.esphome_ns.namespace("weider_wp")
WeiderWpComponent = weiderwp_ns.class_("WeiderWpComponent", cg.Component, uart.UARTDevice)

CONF_DTR_PIN = 'dtr_pin'
MULTI_CONF = True

CONFIG_SCHEMA = (
	cv.Schema(
		{
			cv.GenerateID(): cv.declare_id(WeiderWpComponent),
			cv.Optional(CONF_DTR_PIN): pins.gpio_output_pin_schema,
		}
	)
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_DTR_PIN in config:
        dtr = await cg.gpio_pin_expression(config[CONF_DTR_PIN])
        cg.add(var.set_dtr_pin(dtr))
