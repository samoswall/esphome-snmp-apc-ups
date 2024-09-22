from esphome.const import CONF_ID
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.core import CORE
from esphome.components.text_sensor import TextSensor

CODEOWNERS = ["@aquaticus"]

# No ethernet support at the moment
DEPENDENCIES = ["wifi","text_sensor"]

CONF_SNMP_MODEL_NAME='snmp_model_name'

snmp_ns = cg.esphome_ns.namespace("snmp")
SNMPComponent = snmp_ns.class_("SNMPComponent", cg.Component)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SNMPComponent),
            cv.Optional("contact", default=""): cv.string_strict,
            cv.Optional("location", default=""): cv.string_strict,
            cv.Required(CONF_SNMP_MODEL_NAME): cv.use_id(TextSensor),
        }
    ),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_location(config["location"]))
    cg.add(var.set_contact(config["contact"]))
    
    var_model_name = await cg.get_variable(config[CONF_SNMP_MODEL_NAME])
    cg.add(var.set_snmp_model_name(var_model_name))
    
    await cg.register_component(var, config)

    if CORE.is_esp8266 or CORE.is_esp32:
        cg.add_library(r"https://github.com/aquaticus/Arduino_SNMP.git", "2.1.0")
