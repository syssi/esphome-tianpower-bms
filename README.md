# esphome-tianpower-bms

![GitHub actions](https://github.com/syssi/esphome-tianpower-bms/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-tianpower-bms)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-tianpower-bms)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-tianpower-bms)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor a Tianpower Battery Management System via BLE

Credits: Thanks to [@xpinguinx](https://github.com/xpinguinx) for heavily testing the early beta versions and sponsoring the first release!

## Supported devices

* Tianpower TP-LT55 used in BASEN 48V 200Ah Bluetooth battery bank<br>
  Probably advertised via BLE as `TP_123456`

* Tianpower TP-LT55AT used in BASEN 48V 280Ah/300Ah Bluetooth battery bank ([#17](https://github.com/syssi/esphome-tianpower-bms/issues/17))<br>
  Probably advertised via BLE as `TP_123456`

* Tianpower BMS used in BASEN 10KW Wall-Mounted 51.2V 200Ah battery bank ([#16](https://github.com/syssi/esphome-tianpower-bms/issues/16))<br>
  Probably advertised via BLE as `TP_BSTBD-23I-xxx`

* Tianpower TP-LT55 used in BASEN 14.3KW Wall-Mounted 51.2V 300Ah battery bank ([#46](https://github.com/syssi/esphome-tianpower-bms/issues/46))<br>
  Probably advertised via BLE as `TP_BSTBD-23J-xxx`

* Tianpower TP-LT52 used in BASENGREEN BR-WM-LV 5kWh Wall-Mounted 51.2V 100Ah battery bank ([#44](https://github.com/syssi/esphome-basen-bms/discussions/44))<br>
  Probably advertised via BLE as `TP_BSTBD-24I-xxx`

* Tianpower TP-LT52 (SW 0.1.31) used in BASENGREEN 10kWh Wall-Mounted 51.2V 200Ah battery bank ([#19](https://github.com/syssi/esphome-tianpower-bms/discussions/19))<br>
  Probably advertised via BLE as `TP_BSTBD-23F-xxx`

* Tianpower TP-LT55AT (BN-HES16S48V200LT55A-V1.1.2) used in BASENGREEN BR-OW-LV 14.33kWh 51.2V 280Ah battery bank ([#22](https://github.com/syssi/esphome-tianpower-bms/discussions/22))<br>
  Probably advertised via BLE as `TP_BSTBD-24C-xxxx`

* Tianpower TP-LT55A in BASENGREEN 48V DIY KITS V2 battery bank ([#31](https://github.com/syssi/esphome-tianpower-bms/issues/31))<br>
  Probably advertised via BLE as `TP_123456`

## Requirements

* [ESPHome 2024.6.0 or higher](https://github.com/esphome/esphome/releases).
* Generic ESP32 board

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://syssi/esphome-tianpower-bms@main
```

or just use the `esp32-example.yaml` as proof of concept:

```bash
# Install esphome
pip3 install esphome

# Clone this external component
git clone https://github.com/syssi/esphome-tianpower-bms.git
cd esphome-tianpower-bms

# Create a secrets.yaml containing some setup specific secrets
cat > secrets.yaml <<EOF
bms0_mac_address: MY_BMS_MAC_ADDRESS

wifi_ssid: MY_WIFI_SSID
wifi_password: MY_WIFI_PASSWORD

mqtt_host: MY_MQTT_HOST
mqtt_username: MY_MQTT_USERNAME
mqtt_password: MY_MQTT_PASSWORD
EOF

# Validate the configuration, create a binary, upload it, and start logs
esphome run esp32-ble-example.yaml

```

## Example response all sensors enabled

```
[I][tianpower_bms_ble:273]: Software version frame received
[D][tianpower_bms_ble:274]:   55.14.81.30.2E.31.2E.31.30.00.00.00.00.00.00.00.00.00.00.AA (20)
[D][text_sensor:064]: 'tianpower-bms-ble software version': Sending state '0.1.10'

[I][tianpower_bms_ble:288]: Hardware version frame received
[D][tianpower_bms_ble:289]:   55.14.82.54.50.2D.4C.54.35.35.00.54.42.00.00.00.00.00.00.AA (20)
[D][text_sensor:064]: 'tianpower-bms-ble device model': Sending state 'TP-LT55'

[I][tianpower_bms_ble:307]: Status frame received
[D][tianpower_bms_ble:308]:   55.14.83.00.3C.14.72.01.18.00.E6.00.F0.00.00.30.30.00.64.AA (20)
[D][sensor:094]: 'tianpower-bms-ble state of charge': Sending state 60.00000 % with 0 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble total voltage': Sending state 52.34000 V with 2 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble average temperature': Sending state 28.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble ambient temperature': Sending state 23.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble mosfet temperature': Sending state 24.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble current': Sending state 0.00000 A with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble power': Sending state 0.00000 W with 2 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble charging power': Sending state 0.00000 W with 2 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble discharging power': Sending state 0.00000 W with 2 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble state of health': Sending state 100.00000 % with 0 decimals of accuracy

[I][tianpower_bms_ble:351]: General info frame received
[D][tianpower_bms_ble:352]:   55.14.84.10.04.59.D8.36.48.00.00.00.00.00.00.00.00.00.00.AA (20)
[D][sensor:094]: 'tianpower-bms-ble nominal capacity': Sending state 230.00000 Ah with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble capacity remaining': Sending state 138.95999 Ah with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble charging cycles': Sending state 0.00000  with 0 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble voltage protection bitmask': Sending state 0.00000  with 0 decimals of accuracy
[D][text_sensor:064]: 'tianpower-bms-ble voltage protection': Sending state ''
[D][sensor:094]: 'tianpower-bms-ble current protection bitmask': Sending state 0.00000  with 0 decimals of accuracy
[D][text_sensor:064]: 'tianpower-bms-ble current protection': Sending state ''
[D][sensor:094]: 'tianpower-bms-ble temperature protection bitmask': Sending state 0.00000  with 0 decimals of accuracy
[D][text_sensor:064]: 'tianpower-bms-ble temperature protection': Sending state ''
[D][sensor:094]: 'tianpower-bms-ble error bitmask': Sending state 0.00000  with 0 decimals of accuracy
[D][text_sensor:064]: 'tianpower-bms-ble errors': Sending state ''

[I][tianpower_bms_ble:400]: Mosfet status frame received
[D][tianpower_bms_ble:401]:   55.14.85.08.23.00.00.00.00.00.00.00.00.00.00.00.00.00.00.AA (20)
[D][binary_sensor:036]: 'tianpower-bms-ble charging': Sending state ON
[D][binary_sensor:036]: 'tianpower-bms-ble discharging': Sending state ON
[D][binary_sensor:036]: 'tianpower-bms-ble limiting current': Sending state ON
[I][tianpower_bms_ble:428]: Temperature frame received
[D][tianpower_bms_ble:429]:   55.14.87.00.E6.00.E6.00.E6.00.E6.00.00.00.00.00.00.00.00.AA (20)
[D][sensor:094]: 'tianpower-bms-ble temperature 1': Sending state 23.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble temperature 2': Sending state 23.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble temperature 3': Sending state 23.00000 °C with 1 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble temperature 4': Sending state 23.00000 °C with 1 decimals of accuracy

[I][tianpower_bms_ble:458]: Cell voltages frame (chunk 0) received
[D][tianpower_bms_ble:459]:   55.14.88.0C.C1.0C.D5.0C.D2.0C.D5.0C.C8.0C.D4.0C.C8.0C.D2.AA (20)
[D][sensor:094]: 'tianpower-bms-ble cell voltage 1': Sending state 3.26500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 2': Sending state 3.28500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 3': Sending state 3.28200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 4': Sending state 3.28500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 5': Sending state 3.27200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 6': Sending state 3.28400 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 7': Sending state 3.27200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 8': Sending state 3.28200 V with 3 decimals of accuracy

[I][tianpower_bms_ble:458]: Cell voltages frame (chunk 1) received
[D][tianpower_bms_ble:459]:   55.14.89.0C.C8.0C.C8.0C.C7.0C.C7.0C.C1.0C.C3.0C.CA.0C.C8.AA (20)
[D][sensor:094]: 'tianpower-bms-ble cell voltage 9': Sending state 3.27200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 10': Sending state 3.27200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 11': Sending state 3.27100 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 12': Sending state 3.27100 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 13': Sending state 3.26500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 14': Sending state 3.26700 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 15': Sending state 3.27400 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble cell voltage 16': Sending state 3.27200 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble min cell voltage': Sending state 3.26500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble max cell voltage': Sending state 3.28500 V with 3 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble max voltage cell': Sending state 2.00000  with 0 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble min voltage cell': Sending state 1.00000  with 0 decimals of accuracy
[D][sensor:094]: 'tianpower-bms-ble delta cell voltage': Sending state 0.02000 V with 3 decimals of accuracy

[D][tianpower_bms_ble:255]: The location frame isn't supported yet
[D][tianpower_bms_ble:259]: The owner frame isn't supported yet
```

## Protocol

See [docs/protocol-design.md](docs/protocol-design.md).

## Known issues

None.

## Debugging

If this component doesn't work out of the box for your device please update your configuration to increase the log level to see details about the BLE communication and incoming traffic:

```
logger:
  level: VERY_VERBOSE
  logs:
    esp32_ble: DEBUG
    esp32_ble_tracker: VERY_VERBOSE
    tianpower_bms_ble: VERY_VERBOSE
    scheduler: DEBUG
    component: DEBUG
    sensor: DEBUG
    mqtt: INFO
    mqtt.idf: INFO
    mqtt.component: INFO
    mqtt.sensor: INFO
    mqtt.switch: INFO
    api.service: INFO
    api: INFO
    api: INFO
```

## References

None.
