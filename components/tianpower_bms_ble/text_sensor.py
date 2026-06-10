import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import CONF_TIANPOWER_BMS_BLE_ID, TIANPOWER_BMS_BLE_COMPONENT_SCHEMA

CODEOWNERS = ["@syssi"]
DEPENDENCIES = ["tianpower_bms_ble"]

CONF_SOFTWARE_VERSION = "software_version"
CONF_DEVICE_MODEL = "device_model"
CONF_VOLTAGE_PROTECTION = "voltage_protection"
CONF_CURRENT_PROTECTION = "current_protection"
CONF_TEMPERATURE_PROTECTION = "temperature_protection"
CONF_ERRORS = "errors"
CONF_LOCATION = "location"
CONF_OWNER = "owner"

ICON_DEVICE_MODEL = "mdi:chip"
ICON_SOFTWARE_VERSION = "mdi:numeric"
ICON_VOLTAGE_PROTECTION = "mdi:alert-circle-outline"
ICON_CURRENT_PROTECTION = "mdi:alert-circle-outline"
ICON_TEMPERATURE_PROTECTION = "mdi:alert-circle-outline"
ICON_ERRORS = "mdi:alert-circle-outline"
ICON_LOCATION = "mdi:map-marker"
ICON_OWNER = "mdi:account"

TEXT_SENSORS = [
    CONF_SOFTWARE_VERSION,
    CONF_DEVICE_MODEL,
    CONF_VOLTAGE_PROTECTION,
    CONF_CURRENT_PROTECTION,
    CONF_TEMPERATURE_PROTECTION,
    CONF_ERRORS,
    CONF_LOCATION,
    CONF_OWNER,
]

CONFIG_SCHEMA = TIANPOWER_BMS_BLE_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_SOFTWARE_VERSION): text_sensor.text_sensor_schema(
            icon=ICON_SOFTWARE_VERSION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_DEVICE_MODEL): text_sensor.text_sensor_schema(
            icon=ICON_DEVICE_MODEL,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_VOLTAGE_PROTECTION): text_sensor.text_sensor_schema(
            icon=ICON_VOLTAGE_PROTECTION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_CURRENT_PROTECTION): text_sensor.text_sensor_schema(
            icon=ICON_CURRENT_PROTECTION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_TEMPERATURE_PROTECTION): text_sensor.text_sensor_schema(
            icon=ICON_TEMPERATURE_PROTECTION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_ERRORS): text_sensor.text_sensor_schema(
            icon=ICON_ERRORS,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_LOCATION): text_sensor.text_sensor_schema(
            icon=ICON_LOCATION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_OWNER): text_sensor.text_sensor_schema(
            icon=ICON_OWNER,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TIANPOWER_BMS_BLE_ID])
    for key in TEXT_SENSORS:
        if key in config:
            conf = config[key]
            sens = await text_sensor.new_text_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))
