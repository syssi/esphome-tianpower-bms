"""Schema structure tests for tianpower_bms_ble ESPHome component modules."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import components.tianpower_bms_ble as hub  # noqa: E402
from components.tianpower_bms_ble import (  # noqa: E402
    binary_sensor,
    sensor,
    text_sensor,
)


class TestHubConstants:
    def test_conf_id_defined(self):
        assert hub.CONF_TIANPOWER_BMS_BLE_ID == "tianpower_bms_ble_id"


class TestSensorLists:
    def test_cells_count(self):
        assert len(sensor.CELLS) == 24

    def test_cells_naming(self):
        assert sensor.CELLS[0] == "cell_voltage_1"
        assert sensor.CELLS[23] == "cell_voltage_24"
        for i, key in enumerate(sensor.CELLS, 1):
            assert key == f"cell_voltage_{i}"

    def test_temperatures_count(self):
        assert len(sensor.TEMPERATURES) == 8

    def test_temperatures_naming(self):
        assert sensor.TEMPERATURES[0] == "temperature_1"
        assert sensor.TEMPERATURES[7] == "temperature_8"
        for i, key in enumerate(sensor.TEMPERATURES, 1):
            assert key == f"temperature_{i}"

    def test_sensor_defs_completeness(self):
        assert sensor.CONF_TOTAL_VOLTAGE in sensor.SENSOR_DEFS
        assert sensor.CONF_STATE_OF_CHARGE in sensor.SENSOR_DEFS
        assert sensor.CONF_ERROR_BITMASK in sensor.SENSOR_DEFS
        assert sensor.CONF_MIN_CELL_VOLTAGE in sensor.SENSOR_DEFS
        assert sensor.CONF_MAX_CELL_VOLTAGE in sensor.SENSOR_DEFS
        assert sensor.CONF_DELTA_CELL_VOLTAGE in sensor.SENSOR_DEFS
        assert sensor.CONF_AVERAGE_CELL_VOLTAGE in sensor.SENSOR_DEFS
        assert len(sensor.SENSOR_DEFS) == 25

    def test_no_cell_keys_in_sensor_defs(self):
        for key in sensor.SENSOR_DEFS:
            assert key not in sensor.CELLS
            assert key not in sensor.TEMPERATURES


class TestBinarySensorConstants:
    def test_binary_sensor_defs_dict(self):
        assert binary_sensor.CONF_CHARGING in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_DISCHARGING in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_BALANCING in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_ONLINE_STATUS in binary_sensor.BINARY_SENSOR_DEFS
        assert len(binary_sensor.BINARY_SENSOR_DEFS) == 5

    def test_cell_balancing_sensors_count(self):
        assert len(binary_sensor.CELL_BALANCING_SENSORS) == 24

    def test_cell_balancing_sensors_naming(self):
        assert binary_sensor.CELL_BALANCING_SENSORS[0] == "cell_balancing_1"
        assert binary_sensor.CELL_BALANCING_SENSORS[23] == "cell_balancing_24"
        for i, key in enumerate(binary_sensor.CELL_BALANCING_SENSORS, 1):
            assert key == f"cell_balancing_{i}"


class TestTextSensorConstants:
    def test_text_sensors_list(self):
        assert text_sensor.CONF_SOFTWARE_VERSION in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_DEVICE_MODEL in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_ERRORS in text_sensor.TEXT_SENSORS
        assert len(text_sensor.TEXT_SENSORS) == 6
