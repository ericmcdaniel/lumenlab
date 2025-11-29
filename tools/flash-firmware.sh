#!/bin/bash
set -e

echo "Flashing firmware to /dev/ttyUSB0 at 921600 baud."

esptool --chip esp32 --port /dev/ttyUSB0 --baud 921600 write-flash \
  -z 0x1000 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin

echo "Fireware installation complete!"
