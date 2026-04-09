#include <gtest/gtest.h>
#include "common.h"

namespace esphome::tianpower_bms_ble::testing {

// ── Software version frame (0x81) ───────────────────────────────────────────

TEST(TianpowerBmsBleSoftwareVersionTest, DecodeSoftwareVersion) {
  TestableTianpowerBmsBle bms;
  text_sensor::TextSensor version;
  bms.set_software_version_text_sensor(&version);

  bms.decode_software_version_data_(SOFTWARE_VERSION_FRAME_1);

  EXPECT_EQ(version.state, "0.1.10");
}

TEST(TianpowerBmsBleSoftwareVersionTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, SOFTWARE_VERSION_FRAME_1);
}

TEST(TianpowerBmsBleSoftwareVersionTest, NullSensorDoesNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_software_version_data_(SOFTWARE_VERSION_FRAME_1);
}

// ── Hardware version frame (0x82) ────────────────────────────────────────────

TEST(TianpowerBmsBleHardwareVersionTest, DecodeDeviceModel) {
  TestableTianpowerBmsBle bms;
  text_sensor::TextSensor model;
  bms.set_device_model_text_sensor(&model);

  bms.decode_hardware_version_data_(HARDWARE_VERSION_FRAME_1);

  EXPECT_EQ(model.state, "TP-LT55");
}

TEST(TianpowerBmsBleHardwareVersionTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, HARDWARE_VERSION_FRAME_1);
}

TEST(TianpowerBmsBleHardwareVersionTest, NullSensorDoesNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_hardware_version_data_(HARDWARE_VERSION_FRAME_1);
}

// ── Status frame (0x83) ──────────────────────────────────────────────────────

TEST(TianpowerBmsBleStatusTest, StateOfCharge) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soc;
  bms.set_state_of_charge_sensor(&soc);

  bms.decode_status_data_(STATUS_FRAME_1);

  EXPECT_FLOAT_EQ(soc.state, 60.0f);
}

TEST(TianpowerBmsBleStatusTest, TotalVoltage) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor voltage;
  bms.set_total_voltage_sensor(&voltage);

  bms.decode_status_data_(STATUS_FRAME_1);

  EXPECT_NEAR(voltage.state, 52.34f, 0.001f);
}

TEST(TianpowerBmsBleStatusTest, CurrentPower) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor current, power, charging_power, discharging_power;
  bms.set_current_sensor(&current);
  bms.set_power_sensor(&power);
  bms.set_charging_power_sensor(&charging_power);
  bms.set_discharging_power_sensor(&discharging_power);

  bms.decode_status_data_(STATUS_FRAME_1);

  EXPECT_FLOAT_EQ(current.state, 0.0f);
  EXPECT_FLOAT_EQ(power.state, 0.0f);
  EXPECT_FLOAT_EQ(charging_power.state, 0.0f);
  EXPECT_FLOAT_EQ(discharging_power.state, 0.0f);
}

TEST(TianpowerBmsBleStatusTest, Temperatures) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor avg, ambient, mosfet;
  bms.set_average_temperature_sensor(&avg);
  bms.set_ambient_temperature_sensor(&ambient);
  bms.set_mosfet_temperature_sensor(&mosfet);

  bms.decode_status_data_(STATUS_FRAME_1);

  EXPECT_NEAR(avg.state, 28.0f, 0.1f);
  EXPECT_NEAR(ambient.state, 23.0f, 0.1f);
  EXPECT_NEAR(mosfet.state, 24.0f, 0.1f);
}

TEST(TianpowerBmsBleStatusTest, StateOfHealth) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soh;
  bms.set_state_of_health_sensor(&soh);

  bms.decode_status_data_(STATUS_FRAME_1);

  EXPECT_FLOAT_EQ(soh.state, 100.0f);
}

TEST(TianpowerBmsBleStatusTest, NullSensorsDoNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_status_data_(STATUS_FRAME_1);
}

// ── General info frame (0x84) ────────────────────────────────────────────────

TEST(TianpowerBmsBleGeneralInfoTest, NominalCapacity) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor nominal;
  bms.set_nominal_capacity_sensor(&nominal);

  bms.decode_general_info_data_(GENERAL_INFO_FRAME_1);

  EXPECT_NEAR(nominal.state, 230.00f, 0.001f);
}

TEST(TianpowerBmsBleGeneralInfoTest, CapacityRemaining) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor remaining;
  bms.set_capacity_remaining_sensor(&remaining);

  bms.decode_general_info_data_(GENERAL_INFO_FRAME_1);

  EXPECT_NEAR(remaining.state, 138.96f, 0.001f);
}

TEST(TianpowerBmsBleGeneralInfoTest, ChargingCycles) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor cycles;
  bms.set_charging_cycles_sensor(&cycles);

  bms.decode_general_info_data_(GENERAL_INFO_FRAME_1);

  EXPECT_FLOAT_EQ(cycles.state, 0.0f);
}

TEST(TianpowerBmsBleGeneralInfoTest, NoProtectionBitmasks) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor voltage_prot, current_prot, temp_prot, error;
  bms.set_voltage_protection_bitmask_sensor(&voltage_prot);
  bms.set_current_protection_bitmask_sensor(&current_prot);
  bms.set_temperature_protection_bitmask_sensor(&temp_prot);
  bms.set_error_bitmask_sensor(&error);
  text_sensor::TextSensor errors_text;
  bms.set_errors_text_sensor(&errors_text);

  bms.decode_general_info_data_(GENERAL_INFO_FRAME_1);

  EXPECT_FLOAT_EQ(voltage_prot.state, 0.0f);
  EXPECT_FLOAT_EQ(current_prot.state, 0.0f);
  EXPECT_FLOAT_EQ(temp_prot.state, 0.0f);
  EXPECT_FLOAT_EQ(error.state, 0.0f);
  EXPECT_EQ(errors_text.state, "");
}

TEST(TianpowerBmsBleGeneralInfoTest, NullSensorsDoNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_general_info_data_(GENERAL_INFO_FRAME_1);
}

TEST(TianpowerBmsBleGeneralInfoTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, GENERAL_INFO_FRAME_1);
}

// ── Mosfet status frame (0x85) ───────────────────────────────────────────────

TEST(TianpowerBmsBleMosfetStatusTest, ChargingAndLimitingCurrent) {
  TestableTianpowerBmsBle bms;
  binary_sensor::BinarySensor charging, discharging, limiting;
  bms.set_charging_binary_sensor(&charging);
  bms.set_discharging_binary_sensor(&discharging);
  bms.set_limiting_current_binary_sensor(&limiting);

  bms.decode_mosfet_status_data_(MOSFET_STATUS_FRAME_1);

  EXPECT_TRUE(charging.state);
  EXPECT_FALSE(discharging.state);
  EXPECT_TRUE(limiting.state);
}

TEST(TianpowerBmsBleMosfetStatusTest, BalancingBitmask) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor balancing;
  binary_sensor::BinarySensor balancing_binary;
  bms.set_balancing_bitmask_sensor(&balancing);
  bms.set_balancing_binary_sensor(&balancing_binary);

  bms.decode_mosfet_status_data_(MOSFET_STATUS_FRAME_WITH_BALANCING);

  EXPECT_FLOAT_EQ(balancing.state, 3.0f);
  EXPECT_TRUE(balancing_binary.state);
}

TEST(TianpowerBmsBleMosfetStatusTest, CellBalancingSensors) {
  TestableTianpowerBmsBle bms;
  binary_sensor::BinarySensor cells[2];
  bms.set_cell_balancing_binary_sensor(0, &cells[0]);
  bms.set_cell_balancing_binary_sensor(1, &cells[1]);

  bms.decode_mosfet_status_data_(MOSFET_STATUS_FRAME_WITH_BALANCING);

  EXPECT_TRUE(cells[0].state);  // cell 1 is balancing (bit 0)
  EXPECT_TRUE(cells[1].state);  // cell 2 is balancing (bit 1)
}

TEST(TianpowerBmsBleMosfetStatusTest, NullSensorsDoNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_mosfet_status_data_(MOSFET_STATUS_FRAME_1);
}

TEST(TianpowerBmsBleMosfetStatusTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, MOSFET_STATUS_FRAME_1);
}

// ── Temperature frame (0x87) ─────────────────────────────────────────────────

TEST(TianpowerBmsBleTemperatureTest, FourTemperatures) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor t1, t2, t3, t4;
  bms.set_temperature_sensor(0, &t1);
  bms.set_temperature_sensor(1, &t2);
  bms.set_temperature_sensor(2, &t3);
  bms.set_temperature_sensor(3, &t4);

  bms.decode_temperature_data_(TEMPERATURES_FRAME_1);

  EXPECT_NEAR(t1.state, 23.0f, 0.1f);
  EXPECT_NEAR(t2.state, 23.0f, 0.1f);
  EXPECT_NEAR(t3.state, 23.0f, 0.1f);
  EXPECT_NEAR(t4.state, 23.0f, 0.1f);
}

TEST(TianpowerBmsBleTemperatureTest, SensorsNotInstalled) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor t5, t6, t7, t8;
  bms.set_temperature_sensor(4, &t5);
  bms.set_temperature_sensor(5, &t6);
  bms.set_temperature_sensor(6, &t7);
  bms.set_temperature_sensor(7, &t8);

  bms.decode_temperature_data_(TEMPERATURES_FRAME_1);

  EXPECT_FLOAT_EQ(t5.state, 0.0f);
  EXPECT_FLOAT_EQ(t6.state, 0.0f);
  EXPECT_FLOAT_EQ(t7.state, 0.0f);
  EXPECT_FLOAT_EQ(t8.state, 0.0f);
}

TEST(TianpowerBmsBleTemperatureTest, NullSensorsDoNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_temperature_data_(TEMPERATURES_FRAME_1);
}

TEST(TianpowerBmsBleTemperatureTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, TEMPERATURES_FRAME_1);
}

// ── Cell voltages frames (0x88, 0x89) ────────────────────────────────────────

TEST(TianpowerBmsBleCellVoltagesTest, AllSixteenCells) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor cells[16];
  for (int i = 0; i < 16; i++) {
    bms.set_cell_voltage_sensor(i, &cells[i]);
  }
  sensor::Sensor min_v, max_v, min_cell, max_cell, delta, avg;
  bms.set_min_cell_voltage_sensor(&min_v);
  bms.set_max_cell_voltage_sensor(&max_v);
  bms.set_min_voltage_cell_sensor(&min_cell);
  bms.set_max_voltage_cell_sensor(&max_cell);
  bms.set_delta_cell_voltage_sensor(&delta);
  bms.set_average_cell_voltage_sensor(&avg);

  bms.decode_cell_voltages_data_(0, CELL_VOLTAGES_FRAME_1_8);
  bms.decode_cell_voltages_data_(1, CELL_VOLTAGES_FRAME_9_16);

  EXPECT_NEAR(cells[0].state, 3.265f, 0.001f);   // C1
  EXPECT_NEAR(cells[1].state, 3.285f, 0.001f);   // C2
  EXPECT_NEAR(cells[2].state, 3.282f, 0.001f);   // C3
  EXPECT_NEAR(cells[3].state, 3.285f, 0.001f);   // C4
  EXPECT_NEAR(cells[4].state, 3.272f, 0.001f);   // C5
  EXPECT_NEAR(cells[5].state, 3.284f, 0.001f);   // C6
  EXPECT_NEAR(cells[6].state, 3.272f, 0.001f);   // C7
  EXPECT_NEAR(cells[7].state, 3.282f, 0.001f);   // C8
  EXPECT_NEAR(cells[8].state, 3.272f, 0.001f);   // C9
  EXPECT_NEAR(cells[9].state, 3.272f, 0.001f);   // C10
  EXPECT_NEAR(cells[10].state, 3.271f, 0.001f);  // C11
  EXPECT_NEAR(cells[11].state, 3.271f, 0.001f);  // C12
  EXPECT_NEAR(cells[12].state, 3.265f, 0.001f);  // C13
  EXPECT_NEAR(cells[13].state, 3.267f, 0.001f);  // C14
  EXPECT_NEAR(cells[14].state, 3.274f, 0.001f);  // C15
  EXPECT_NEAR(cells[15].state, 3.272f, 0.001f);  // C16

  EXPECT_NEAR(min_v.state, 3.265f, 0.001f);
  EXPECT_NEAR(max_v.state, 3.285f, 0.001f);
  EXPECT_NEAR(min_cell.state, 1.0f, 0.1f);
  EXPECT_NEAR(max_cell.state, 2.0f, 0.1f);
  EXPECT_NEAR(delta.state, 0.020f, 0.001f);
  EXPECT_NEAR(avg.state, 3.2744f, 0.0001f);
}

TEST(TianpowerBmsBleCellVoltagesTest, NullSensorsDoNotCrash) {
  TestableTianpowerBmsBle bms;
  bms.decode_cell_voltages_data_(0, CELL_VOLTAGES_FRAME_1_8);
  bms.decode_cell_voltages_data_(1, CELL_VOLTAGES_FRAME_9_16);
}

TEST(TianpowerBmsBleCellVoltagesTest, DispatchedViaOnData) {
  TestableTianpowerBmsBle bms;
  bms.on_tianpower_bms_ble_data(0x13, CELL_VOLTAGES_FRAME_1_8);
  bms.on_tianpower_bms_ble_data(0x13, CELL_VOLTAGES_FRAME_9_16);
}

// ── Frame dispatch and validation ───────────────────────────────────────────

TEST(TianpowerBmsBleDispatchTest, ValidFrameDispatched) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soc;
  bms.set_state_of_charge_sensor(&soc);

  bms.on_tianpower_bms_ble_data(0x13, STATUS_FRAME_1);

  EXPECT_FLOAT_EQ(soc.state, 60.0f);
}

TEST(TianpowerBmsBleDispatchTest, InvalidFrameTooShort) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soc;
  soc.state = -1.0f;
  bms.set_state_of_charge_sensor(&soc);

  bms.on_tianpower_bms_ble_data(0x13, INVALID_FRAME_TOO_SHORT);

  EXPECT_FLOAT_EQ(soc.state, -1.0f);
}

TEST(TianpowerBmsBleDispatchTest, InvalidFrameWrongStart) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soc;
  soc.state = -1.0f;
  bms.set_state_of_charge_sensor(&soc);

  bms.on_tianpower_bms_ble_data(0x13, INVALID_FRAME_WRONG_START);

  EXPECT_FLOAT_EQ(soc.state, -1.0f);
}

TEST(TianpowerBmsBleDispatchTest, InvalidFrameWrongEnd) {
  TestableTianpowerBmsBle bms;
  sensor::Sensor soc;
  soc.state = -1.0f;
  bms.set_state_of_charge_sensor(&soc);

  bms.on_tianpower_bms_ble_data(0x13, INVALID_FRAME_WRONG_END);

  EXPECT_FLOAT_EQ(soc.state, -1.0f);
}

}  // namespace esphome::tianpower_bms_ble::testing
