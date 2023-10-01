import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import button

from esphome.const import CONF_ID
from .. import weiderwp_ns, WeiderWpComponent, CONF_WEIDER_ID

DEPENDENCIES = ["weider_wp", "button"]
CODEOWNERS = ["@andyboeh"]

WeiderButton = weiderwp_ns.class_("WeiderButton", button.Button, cg.Component)

CONFIG_SCHEMA = button.BUTTON_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(WeiderButton),
        cv.GenerateID(CONF_WEIDER_ID): cv.use_id(WeiderWpComponent),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await button.register_button(var, config)

    parent = await cg.get_variable(config[CONF_WEIDER_ID])
    cg.add(var.set_weider_parent(parent))
