import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import DEVICE_CLASS_CONNECTIVITY, ENTITY_CATEGORY_DIAGNOSTIC

from . import CONF_TIANPOWER_BMS_BLE_ID, TIANPOWER_BMS_BLE_COMPONENT_SCHEMA

CODEOWNERS = ["@syssi"]
DEPENDENCIES = ["tianpower_bms_ble"]

CONF_ONLINE_STATUS = "online_status"
CONF_CHARGING = "charging"
CONF_DISCHARGING = "discharging"
CONF_LIMITING_CURRENT = "limiting_current"
CONF_BALANCING = "balancing"

CELL_BALANCING_SENSORS = [f"cell_balancing_{i}" for i in range(1, 25)]

# key: binary_sensor_schema kwargs
BINARY_SENSOR_DEFS = {
    CONF_ONLINE_STATUS: {
        "device_class": DEVICE_CLASS_CONNECTIVITY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_CHARGING: {"icon": "mdi:battery-charging"},
    CONF_DISCHARGING: {"icon": "mdi:power-plug"},
    CONF_LIMITING_CURRENT: {"icon": "mdi:car-speed-limiter"},
    CONF_BALANCING: {"icon": "mdi:scale-balance"},
}

BINARY_SENSORS = list(BINARY_SENSOR_DEFS)

_CELL_BALANCING_SCHEMA = binary_sensor.binary_sensor_schema(icon="mdi:scale-balance")

CONFIG_SCHEMA = TIANPOWER_BMS_BLE_COMPONENT_SCHEMA.extend(
    {
        **{
            cv.Optional(key): binary_sensor.binary_sensor_schema(**kwargs)
            for key, kwargs in BINARY_SENSOR_DEFS.items()
        },
        **{cv.Optional(key): _CELL_BALANCING_SCHEMA for key in CELL_BALANCING_SENSORS},
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TIANPOWER_BMS_BLE_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = await binary_sensor.new_binary_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
    for i, key in enumerate(CELL_BALANCING_SENSORS):
        if key in config:
            conf = config[key]
            sens = await binary_sensor.new_binary_sensor(conf)
            cg.add(hub.set_cell_balancing_binary_sensor(i, sens))
