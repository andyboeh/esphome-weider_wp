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
from esphome import automation
from esphome.components import uart, sensor
from esphome.const import CONF_ID

# ESPHome doesn't know the Stream abstraction yet, so hardcode to use a UART for now.

DEPENDENCIES = ["uart"]

weiderwp_ns = cg.esphome_ns.namespace("weider_wp")
WeiderWpComponent = weiderwp_ns.class_("WeiderWpComponent", cg.Component, uart.UARTDevice)
SetCodeAction = weiderwp_ns.class_("SetCodeAction", automation.Action)

CONF_DTR_PIN = 'dtr_pin'
CONF_WEIDER_ID = 'weider_id'
CONF_CODE = 'code'
CONF_VALUE = 'value'
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

@automation.register_action(
    "weider_wp.set_code",
    SetCodeAction,
    automation.maybe_simple_id(
        {
             cv.GenerateID(): cv.use_id(WeiderWpComponent),
            cv.Required(CONF_CODE): cv.templatable(
              cv.int_range(min=1, max=99),
            ),
            cv.Required(CONF_VALUE): cv.templatable(
              cv.int_range(min=-999, max=9999),
            ),
        },
    ),
)

async def set_code_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    if CONF_CODE in config and CONF_VALUE in config:
        template_ = await cg.templatable(
            config[CONF_CODE], args, cg.int_
        )
        value_ = await cg.templatable(
            config[CONF_VALUE], args, cg.int_
        )
        cg.add(var.set_code(template_))
        cg.add(var.set_value(value_))
    return var

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_DTR_PIN in config:
        dtr = await cg.gpio_pin_expression(config[CONF_DTR_PIN])
        cg.add(var.set_dtr_pin(dtr))
