#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/tianpower_bms_ble/tianpower_bms_ble.h"

namespace esphome::tianpower_bms_ble::testing {

// Exposes protected decoder methods for direct testing.
class TestableTianpowerBmsBle : public TianpowerBmsBle {
 public:
  using TianpowerBmsBle::decode_software_version_data_;
  using TianpowerBmsBle::decode_hardware_version_data_;
  using TianpowerBmsBle::decode_status_data_;
  using TianpowerBmsBle::decode_general_info_data_;
  using TianpowerBmsBle::decode_mosfet_status_data_;
  using TianpowerBmsBle::decode_temperature_data_;
  using TianpowerBmsBle::decode_cell_voltages_data_;
  using TianpowerBmsBle::on_tianpower_bms_ble_data;
};

// ── Real frames from tests/esp32-ble-example-faker.yaml ───────────────────────
// Frame format: 0x55 <function> <address> [16 bytes payload] 0xaa

// Software version frame (0x81) ─────────────────────────────────────────────────
// "0.1.10"
static const std::vector<uint8_t> SOFTWARE_VERSION_FRAME_1 = {
    0x55, 0x14, 0x81,                                // start | response | address
    0x30, 0x2e, 0x31, 0x2e, 0x31, 0x30, 0x00, 0x00,  // "0.1.10" + padding
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // padding
    0xaa,                                            // end
};

// Hardware version frame (0x82) ────────────────────────────────────────────────
// "TP-LT55" "TB"
static const std::vector<uint8_t> HARDWARE_VERSION_FRAME_1 = {
    0x55, 0x14, 0x82,                                // start | response | address
    0x54, 0x50, 0x2d, 0x4c, 0x54, 0x35, 0x35, 0x00,  // "TP-LT55" + null
    0x54, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "TB" + padding
    0xaa,                                            // end
};

// Status frame (0x83) ──────────────────────────────────────────────────────────
// SOC=60%  voltage=52.34V  avg=28.0°C  ambient=23.0°C  mosfet=24.0°C
// current=0A  power=0W  SOH=100%
static const std::vector<uint8_t> STATUS_FRAME_1 = {
    0x55, 0x14, 0x83,  // start | response | address
    0x00, 0x3c,        // state_of_charge = 0x003C = 60 %
    0x14, 0x72,        // total_voltage   = 0x1472 = 5234 * 0.01 = 52.34 V
    0x01, 0x18,        // average_temp    = 0x0118 = 280  * 0.1  = 28.0 °C
    0x00, 0xe6,        // ambient_temp    = 0x00E6 = 230  * 0.1  = 23.0 °C
    0x00, 0xf0,        // mosfet_temp     = 0x00F0 = 240  * 0.1  = 24.0 °C
    0x00, 0x00,        // current         = 0x0000 = 0    * 0.01 = 0.00 A
    0x30, 0x30,        // unknown
    0x00, 0x64,        // state_of_health = 0x0064 = 100 %
    0xaa,              // end
};

// General info frame (0x84) ─────────────────────────────────────────────────────
// cells=16  temps=4  nominal=230Ah  remaining=138.96Ah  cycles=0  no errors
static const std::vector<uint8_t> GENERAL_INFO_FRAME_1 = {
    0x55, 0x14, 0x84,  // start | response | address
    0x10,              // cell_count = 16
    0x04,              // temp_sensor_count = 4
    0x59, 0xd8,        // nominal_capacity = 0x59D8 = 23000 * 0.01 = 230.00 Ah
    0x36, 0x48,        // capacity_remaining = 0x3648 = 13896 * 0.01 = 138.96 Ah
    0x00, 0x00,        // charging_cycles = 0
    0x00, 0x00,        // voltage_protection_bitmask = 0
    0x00, 0x00,        // current_protection_bitmask = 0
    0x00, 0x00,        // temperature_protection_bitmask = 0
    0x00, 0x00,        // error_bitmask = 0
    0xaa,              // end
};

// Mosfet status frame (0x85) - charging, limiting, no balancing
static const std::vector<uint8_t> MOSFET_STATUS_FRAME_1 = {
    0x55, 0x14, 0x85,  // start | response | address
    0x08, 0x23,        // mosfet_status = 0x0823: bit1=charging, bit16=limiting
    0x00, 0x00,        // overvoltage_protection_bitmask = 0
    0x00, 0x00,        // undervoltage_protection_bitmask = 0
    0x00, 0x00,        // high_alarm_bitmask = 0
    0x00, 0x00,        // low_alarm_bitmask = 0
    0x00, 0x00,        // balancing_bitmask = 0
    0x00, 0x00,        // unused
    0xaa,              // end
};

// Mosfet status frame (0x85) - charging, discharging, balancing cell 1+2
static const std::vector<uint8_t> MOSFET_STATUS_FRAME_WITH_BALANCING = {
    0x55, 0x14, 0x85,  // start | response | address
    0x08, 0x23,        // mosfet_status = 0x0823
    0x00, 0x00,        // overvoltage_protection_bitmask = 0
    0x00, 0x00,        // undervoltage_protection_bitmask = 0
    0x00, 0x00,        // high_alarm_bitmask = 0
    0x00, 0x00,        // low_alarm_bitmask = 0
    0x00, 0x03,        // balancing_bitmask = 3 (cells 1+2)
    0x00, 0x00,        // unused
    0xaa,              // end
};

// Temperature frame (0x87) ─────────────────────────────────────────────────────
// T1=23.0°C  T2=23.0°C  T3=23.0°C  T4=23.0°C  T5-8=0 (not installed)
static const std::vector<uint8_t> TEMPERATURES_FRAME_1 = {
    0x55, 0x14, 0x87,  // start | response | address
    0x00, 0xe6,        // temperature_1 = 0x00E6 = 230 * 0.1 = 23.0 °C
    0x00, 0xe6,        // temperature_2 = 23.0 °C
    0x00, 0xe6,        // temperature_3 = 23.0 °C
    0x00, 0xe6,        // temperature_4 = 23.0 °C
    0x00, 0x00,        // temperature_5 = 0 (not installed)
    0x00, 0x00,        // temperature_6 = 0
    0x00, 0x00,        // temperature_7 = 0
    0x00, 0x00,        // temperature_8 = 0
    0xaa,              // end
};

// Cell voltages frame (0x88) - cells 1-8 ────────────────────────────────────────
// C1=3.285V  C2=3.285V  C3=3.282V  C4=3.282V  C5=3.282V  C6=3.285V  C7=3.285V  C8=3.282V
// min=3.282 max=3.285 delta=0.003
static const std::vector<uint8_t> CELL_VOLTAGES_FRAME_1_8 = {
    0x55, 0x14, 0x88,  // start | response | address
    0x0c, 0xc1,        // cell_voltage_1 = 0x0CC1 = 3265 * 0.001 = 3.265 V
    0x0c, 0xd5,        // cell_voltage_2 = 3.285 V
    0x0c, 0xd2,        // cell_voltage_3 = 3.282 V
    0x0c, 0xd5,        // cell_voltage_4 = 3.285 V
    0x0c, 0xc8,        // cell_voltage_5 = 3.272 V
    0x0c, 0xd4,        // cell_voltage_6 = 3.276 V
    0x0c, 0xc8,        // cell_voltage_7 = 3.272 V
    0x0c, 0xd2,        // cell_voltage_8 = 3.282 V
    0xaa,              // end
};

// Cell voltages frame (0x89) - cells 9-16 ───────────────────────────────────────
static const std::vector<uint8_t> CELL_VOLTAGES_FRAME_9_16 = {
    0x55, 0x14, 0x89,  // start | response | address
    0x0c, 0xc8,        // cell_voltage_9  = 3.272 V
    0x0c, 0xc8,        // cell_voltage_10 = 3.272 V
    0x0c, 0xc7,        // cell_voltage_11 = 3.271 V
    0x0c, 0xc7,        // cell_voltage_12 = 3.271 V
    0x0c, 0xc1,        // cell_voltage_13 = 3.265 V
    0x0c, 0xc3,        // cell_voltage_14 = 3.267 V
    0x0c, 0xca,        // cell_voltage_15 = 3.274 V
    0x0c, 0xc8,        // cell_voltage_16 = 3.272 V
    0xaa,              // end
};

// Location frame (0x90) - not implemented yet
static const std::vector<uint8_t> LOCATION_FRAME_1 = {
    0x55, 0x14, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa,
};

// Location frame part 2 (0x91) - second half of 32-byte string
static const std::vector<uint8_t> LOCATION_FRAME_2 = {
    0x55, 0x14, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa,
};

// Owner frame (0x94) - not implemented yet
static const std::vector<uint8_t> OWNER_FRAME_1 = {
    0x55, 0x14, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa,
};

// Owner frame part 2 (0x95) - second half of 32-byte string
static const std::vector<uint8_t> OWNER_FRAME_2 = {
    0x55, 0x14, 0x95, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa,
};

// Invalid frames (from tests/esp32-ble-example-debug.yaml — test rejection logic)
static const std::vector<uint8_t> INVALID_FRAME_TOO_SHORT = {0x55, 0x14, 0x81, 0xaa};
static const std::vector<uint8_t> INVALID_FRAME_WRONG_START = {0x56, 0x14, 0x81, 0x00, 0xaa};
static const std::vector<uint8_t> INVALID_FRAME_WRONG_END = {0x55, 0x14, 0x81, 0x00, 0x00, 0xbb};

}  // namespace esphome::tianpower_bms_ble::testing
