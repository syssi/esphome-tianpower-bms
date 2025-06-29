import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID

from . import CONF_TIANPOWER_BMS_BLE_ID, TianpowerBmsBle

DEPENDENCIES = ["tianpower_bms_ble"]

CODEOWNERS = ["@syssi"]

CONF_CHARGING = "charging"
CONF_DISCHARGING = "discharging"
CONF_LIMITING_CURRENT = "limiting_current"
CONF_BALANCING = "balancing"

BINARY_SENSORS = [
    CONF_CHARGING,
    CONF_DISCHARGING,
    CONF_LIMITING_CURRENT,
    CONF_BALANCING,
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TIANPOWER_BMS_BLE_ID): cv.use_id(TianpowerBmsBle),
        cv.Optional(CONF_CHARGING): binary_sensor.binary_sensor_schema(
            icon="mdi:battery-charging"
        ),
        cv.Optional(CONF_DISCHARGING): binary_sensor.binary_sensor_schema(
            icon="mdi:power-plug"
        ),
        cv.Optional(CONF_LIMITING_CURRENT): binary_sensor.binary_sensor_schema(
            icon="mdi:car-speed-limiter"
        ),
        cv.Optional(CONF_BALANCING): binary_sensor.binary_sensor_schema(
            icon="mdi:scale-balance"
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TIANPOWER_BMS_BLE_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
