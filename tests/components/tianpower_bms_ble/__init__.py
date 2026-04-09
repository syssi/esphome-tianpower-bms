import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

from tests.testing_helpers import ComponentManifestOverride

tianpower_bms_ble_ns = cg.esphome_ns.namespace("tianpower_bms_ble")
TianpowerBmsBle = tianpower_bms_ble_ns.class_("TianpowerBmsBle", cg.PollingComponent)


def override_manifest(manifest: ComponentManifestOverride) -> None:
    manifest.dependencies = []

    manifest.config_schema = cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(TianpowerBmsBle),
        }
    ).extend(cv.polling_component_schema("20s"))

    async def to_code_stub(config):
        var = cg.new_Pvariable(config[CONF_ID])
        await cg.register_component(var, config)

    manifest.to_code = to_code_stub
