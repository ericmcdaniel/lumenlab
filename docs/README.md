# Component Selection

The following details the ICs and components selected, general information, and their justification as to why I selected it where available.

### ESP32-WROOM-32D
* *[Datasheet](./vendor/esp32-wroom-32d-datasheet.pdf)*

The only ESP32 variant that support the Bluetooth classic protocol (BR/EDR) are the WROOM variants, eliminating selections such as the more powerful S3. Bluetooth classic is required as the PS3 controller does not support BLE (Bluetooth Low Energy).

**For those using a DevKit for protyping:** You can examine [the GPIO pinout for the ESP32 DevKit here](./vendor/esp32-pinout.avif). This is the pinout for my particular DevKit. Your mileage may vary.

### MP2338 step down buck converter
* *[Datasheet](./vendor/mp2338-datasheet.pdf)*
* *[Distributor](https://www.digikey.com/en/products/detail/monolithic-power-systems-inc/MP2338GTL-Z/15966227)*
* *Manufacturer:* Monolithic Power Systems, Inc.
* *Package:* SOT-583

### AP7361C LDO regulator
* *[Datasheet](./vendor/ap7361c-datasheet.pdf)*
* *[Distributor](https://www.digikey.com/en/products/detail/diodes-incorporated/AP7361C-33E-13/5638317)*
* *Manufacturer:* Diodes, Inc.
* *Package:* SOT-223-3

I originally selected the AMS1117 by EVVOSEMI as that is what's provided on the ESP32-WROOM-32 DevKit, however the AP7361C is more efficient due to it's 340 mV drop at 1A (compared to AMS1117's 1.2V drop at 1A). The AP7361C also has a high PSRR with 75dB @ 1kHz, however the AMS1117's PSRR is the same under similar conditions.
