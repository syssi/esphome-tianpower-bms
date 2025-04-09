#!/bin/bash

if [[ $2 == tests/* ]]; then
  C="../components"
else
  C="components"
fi

esphome -s mac_address 90:A6:BF:93:A0:69 -s external_components_source $C ${1:-run} ${2:-esp32-ble-example-faker.yaml}
