import esphome.codegen as cg
from esphome.components import ble_client
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

DEPENDENCIES = ["ble_client"]
AUTO_LOAD = ["binary_sensor", "sensor", "text_sensor"]
MULTI_CONF = True

CONF_TIANPOWER_BMS_BLE_ID = "tianpower_bms_ble_id"

tianpower_bms_ble_ns = cg.esphome_ns.namespace("tianpower_bms_ble")
TianpowerBmsBle = tianpower_bms_ble_ns.class_(
    "TianpowerBmsBle", ble_client.BLEClientNode, cg.PollingComponent
)

TIANPOWER_BMS_BLE_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_TIANPOWER_BMS_BLE_ID): cv.use_id(TianpowerBmsBle),
    }
)

CONFIG_SCHEMA = cv.All(
    cv.require_esphome_version(2024, 12, 0),
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TianpowerBmsBle),
        }
    )
    .extend(ble_client.BLE_CLIENT_SCHEMA)
    .extend(cv.polling_component_schema("10s")),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await ble_client.register_ble_node(var, config)
