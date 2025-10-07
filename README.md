<p align="center"><img src="assets/lumenlab-logo.png" alt="LumenLab Logo" /></p>
<p align="center">Transforming pixels into a playground</p>

---

__LumenLab__ is an LED strip gaming and entertainment platform designed to transform your space into an interactive playground of games, animations, and lights. Built using a ESP32 microcontroller and the NeoPixel addressable LED strip, LumenLab delivers simple, one-dimension retro arcade-like games, entertaining animations, and general lighting effects that can make any room more engaging.

# Features

LumenLab is composed of multiple realms. The premier realm is its suite of games, but the platform also supports entertaining animations (called scenes) and general lighting utilities. After all it's still an LED strip!

## Games
Using an LED strip as a gaming platform is unique due to the constraint of only having one dimension to interact with. Since *only* the landscape x-axis is available, this constraint compels players to apply creative interpretation to appreciate the gameplay. This is not a modern AAA blockbuster with 4K graphics immersing you in the vision of a world crafted by another person. Instead, LumenLab's restriction subtly encourages players to philosophically revisit what it really means to play a game at it core. In its purest form, players follow rules and explore boundaries in pursuit of a goal. Game players encounter conflict and must experiment and adapt to overcome these obstacles. LumenLab forces players to experience gaming at its rawest, most atomic form: structured uncertainty and strategy until mastery is achieved. This has become the manifesto of the LumenLab. *Every individual playing its games has a unique mental concept of what they're experiencing.*

Because LumenLab works on a single dimension using an array of LEDs, it's aesthetically reminiscent of retro arcade games. However, LumenLab takes advantage of capabilities unavailable on old eight-bit game consoles. These capabilities include its ability to generate any arbitrary RGB color instead of being limited to 256 colors. Additionally, its UI takes advantage of the broad range of states and controls offered by the PS3 controller such as the number of available buttons and precise analog joy stick/trigger positions, contrasting from a cabinet arcade with only four discrete buttons. There are five games available, detailed below.

| Title | Description |
| :--- | --- |
| **Recall** |*In development.*<br><br>*Recall* is the low-hanging fruit of the games available. It is an adaptation of Hasbro's fifty-year-old [*Simon* game](https://shop.hasbro.com/en-us/product/simon-game-handheld-games-for-kids-electronic-games-for-1-player-ages-8-plus/E9383). Because of the ubitiquity of the game and the general public's familiarity with it and its rules, it's logical for this to be the first game offered, allowing players to adapt to the restrictions of LumenLab within a familiar format. The rules and gameplay are the identical to the original game. The LED strip momentarily displays a color, and you must press the button with the corresponding color on the PS3 controller. As additional colors are sequenced, players must recall the full sequence in correct order on every iteration. The goal is to exceed your previous high score.|
| **Phase Evasion** | *In development.* Details to be provided soon. |
| **Light Strike** | *In development.* Details to be provided soon. |
| **Reflex** | *In development.* Details to be provided soon. |
| **Pursuit** | *In development.* Details to be provided soon. |


## Scenes

An LED strip entertainment platform would not be complete if users did not have animations to enjoy. Inspired by the [WLED project](https://kno.wled.ge/), LumenLab is able to create captivating animations, many of which which support adjustments in real-time to suit your needs. Depending on the Scene chosen, moving the joystick can change the color, or pressing the directional buttons can change timing.

---

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