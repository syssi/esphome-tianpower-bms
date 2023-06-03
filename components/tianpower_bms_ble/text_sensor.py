import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ICON, CONF_ID

from . import CONF_TIANPOWER_BMS_BLE_ID, TianpowerBmsBle

DEPENDENCIES = ["tianpower_bms_ble"]

CODEOWNERS = ["@syssi"]

CONF_SOFTWARE_VERSION = "software_version"
CONF_DEVICE_MODEL = "device_model"

ICON_DEVICE_MODEL = "mdi:chip"
ICON_SOFTWARE_VERSION = "mdi:numeric"

CONF_CHARGING_STATES = "charging_states"
CONF_DISCHARGING_STATES = "discharging_states"
CONF_CHARGING_WARNINGS = "charging_warnings"
CONF_DISCHARGING_WARNINGS = "discharging_warnings"

ICON_CHARGING_STATES = "mdi:alert-circle-outline"
ICON_DISCHARGING_STATES = "mdi:alert-circle-outline"
ICON_CHARGING_WARNINGS = "mdi:alert-circle-outline"
ICON_DISCHARGING_WARNINGS = "mdi:alert-circle-outline"

TEXT_SENSORS = [
    CONF_SOFTWARE_VERSION,
    CONF_DEVICE_MODEL,
    # CONF_CHARGING_STATES,
    # CONF_DISCHARGING_STATES,
    # CONF_CHARGING_WARNINGS,
    # CONF_DISCHARGING_WARNINGS,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TIANPOWER_BMS_BLE_ID): cv.use_id(TianpowerBmsBle),
        cv.Optional(CONF_SOFTWARE_VERSION): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_SOFTWARE_VERSION): cv.icon,
            }
        ),
        cv.Optional(CONF_DEVICE_MODEL): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_DEVICE_MODEL): cv.icon,
            }
        ),
        cv.Optional(CONF_CHARGING_STATES): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_CHARGING_STATES): cv.icon,
            }
        ),
        cv.Optional(CONF_DISCHARGING_STATES): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_DISCHARGING_STATES): cv.icon,
            }
        ),
        cv.Optional(CONF_CHARGING_WARNINGS): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_CHARGING_WARNINGS): cv.icon,
            }
        ),
        cv.Optional(CONF_DISCHARGING_WARNINGS): text_sensor.TEXT_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(text_sensor.TextSensor),
                cv.Optional(CONF_ICON, default=ICON_DISCHARGING_WARNINGS): cv.icon,
            }
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TIANPOWER_BMS_BLE_ID])
    for key in TEXT_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await text_sensor.register_text_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))
