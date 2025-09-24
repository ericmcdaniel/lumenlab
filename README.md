<p align="center"><img src="assets/lumenlab-logo.png" alt="LumenLab Logo" /></p>
<p align="center">Transforming pixels into a playground</p>

---

__LumenLab__ is an LED entertainment platform designed to transform your personal space into an interactive playground of games and lights. Built on an ESP32-WROOM, the WS2815 addressable LED strip, and controlled by a PS3 controller, LumenLab delivers simple and retro games, programmable animations, and dynamic lighting effects that make any room more engaging.

# Development Setup
## Requirements
Being an LED strip platform controlled by a microcontroller, a combination of hardware and software is required to replicate the platform shown below. Some of the physical components can be substituted for appropriate alternatives, however be cautioned that this may change other parts of the overall design.

### Hardware
The easier method to get a base setup would be to follow [the wiring diagram from the WLED Project](https://kno.wled.ge/basics/wiring-guides/).
|  Device | Description |
| --- | --- |
| ESP32 WROOM microcontroller | Only the WROOM variants are supported because those are the only variants that support the Bluetooth classic protocol (BR/EDR). |
| WS2815 LED light strip | The 12V variant of the NeoPixel addressable RGB WS2812B. This project uses the 5 meter, 300 LED strip in black. |
| 12V 10A DC power supply | The 10A supply is needed to illuminate the full strip white at full brightness. |
| MP2338 buck converter | Any step down regulator will suffice as long as it outputs 5V and 2 to 3 amps. |
| SN74AHCT125N logic level shifter | To convert the 3.3V signal for the LED strip up to 5V. |
| PlayStation 3 game controller | The primary input device to interact with LumenLab. |
| SSD1306 OLED display module | To render menu options. This project uses the 0.96" variant. |
| Five-way tactile switch | To control the menu displayed on the OLED display. |
| Passive components | As specified in your MCU's datasheet for high pass filtering and power stability. |


### Software
| Dependency | Description |
| --- | --- |
| [PlatformIO](https://platformio.org/) | A feature-rich ecosystem for embedded development. You could use the toolchain CLI, but the Visual Studio Code extension is very approachable. This includes the C/C++ compiler (avr-gcc) needed for MCU development. |
| Python3 (&GreaterEqual;3.6)| Required by PlatformIO to compile and flash the device. Also used in the virtualizer for local development. |

There is a Dockerfile provided. It does *not* work for me on Windows/WSL due to issues mapping the COM ports to POSIX serial devices. I have not tested this on a native Linux machine, so I will keep the file for now.

## Building the repo
In order to simplify the build process for this repo, a script to initialize global configuration settings and credentials has been provided for both Windows and *nix OS. These scripts auto-generate the relevant files needed for a clean build.

_secrets.h_ - A header file that #define variables at compile-time, such as your WLAN credentials, and host/port ip address