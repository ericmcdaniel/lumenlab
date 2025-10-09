<p align="center"><img src="assets/lumenlab-logo.png" alt="LumenLab Logo" /></p>
<p align="center">Transforming pixels into a playground</p>

---

__LumenLab__ is an LED strip gaming and entertainment platform designed to transform your space into an interactive playground of games, animations, and lights. Built using a ESP32 microcontroller, viewed with the NeoPixel addressable LED strip, and controlled by a PlayStation 3 game controller, LumenLab delivers simple, one-dimension retro arcade-style games, entertaining animations, and general lighting effects that can make any room more inviting.
<br>

# Features

LumenLab is composed of multiple realms. The premier realm is its suite of games, but the platform also supports entertaining animations (called scenes) and general lighting utilities. After all it's still an LED strip!

## Games
Using an LED strip as a gaming platform is unique due to the constraint of only having one dimension to interact with. Since *only* the landscape x-axis is available, this constraint compels players to apply creative interpretation during gameplay. This is not a modern AAA blockbuster with 4K graphics immersing you in the vision of a world crafted by another person. Instead, LumenLab's restriction subtly encourages players to philosophically revisit what it really means to play a game at it's core. In its purest form, a game player follows rules and explores boundaries in pursuit of a goal. Game players encounter conflict and must experiment and adapt to their environment to overcome obstacles. LumenLab forces players to experience gaming at its rawest, most atomic form: structured uncertainty and strategy until mastery is achieved. This has become the manifesto of the LumenLab. *Every individual playing its games has a unique mental concept of what they're experiencing.*

Because LumenLab works on a single dimension using an array of LEDs, it's aesthetically reminiscent of retro arcade games. However, LumenLab takes advantage of capabilities unavailable on old eight-bit game consoles. These capabilities include its ability to generate any arbitrary RGB color instead of being limited to 256 colors. Additionally, its UI takes advantage of the broad range of states and buttons offered by the PS3 controller such as the number of buttons available and precise analog joy stick/trigger positions, contrasting from a cabinet arcade with only four discrete buttons. There are six games available or in development, each detailed below.

| **Title** | **Description** |
| --- | --- |
| **Recall** |*Recall* is the low-hanging fruit of the games available. It is an adaptation of Hasbro's fifty-year-old game [*Simon*](https://shop.hasbro.com/en-us/product/simon-game-handheld-games-for-kids-electronic-games-for-1-player-ages-8-plus/E9383). Because of the ubiquity of the game and the general public's familiarity with it and its rules, it's logical for this to be the first game offered, allowing players to adapt to the restrictions of LumenLab within a familiar format. The rules and gameplay are the identical to the original game. The LED strip momentarily displays a color, and you must press the button with the corresponding color on the PS3 controller. As additional colors are sequenced, players must recall the full sequence in correct order on every iteration. The goal is to exceed your previous high score.<br><br>*In development.*|
| **Phase Evasion** | *Phase Evasion* is a game similar in spirit to Google Chrome's Easter egg game [*T-Rex Runner*](chrome://dino/). In *T-Rex Runner*, you are a dinosaur running in the desert. You must avoid obstacles like cacti and birds by jumping over them or ducking under them respectively. In *Phase Evasion*, you are a solid color entity, and you must evade the various color obstacles approaching you. Limited to the single dimension constraint, you cannot jump up or down, but instead must phase shift and blend into the obstacle's color to evade capture. The obstacles progressively move faster, and your goal is to exceed your previous high score.<br><br>*In development.* |
| **Light Strike** | *In development.* Details to be provided soon. |
| **Reflex** | *In development.* Details to be provided soon. |
| **Pursuit** | *In development.* Details to be provided soon. |
| **Spectrum** | *In development.* Details to be provided soon. |

## Scenes

An LED strip entertainment platform would not be complete if users did not have animations to enjoy. Inspired by the [WLED project](https://kno.wled.ge/), LumenLab is able to create captivating animations, many of which which support adjustments in real-time to suit your needs. Depending on the Scene chosen, moving the joystick can change the color, or pressing the directional buttons can change timing.

---

# Experience the Lights In Your Home
Being a hardware-forward project, it is not possible to experience LumenLab without physically having the device. Your options include either having a PCB professionally manufactured and assembled, or soldering your own prototype on a breadboard or perf board using off-the-shelf components.

This guide will walk through both options and their practicality.

## Method A: Professionally Manufactured and Assembled

A custom PCB was designed using KiCad and give LumenLab a clean aesthetic. All of the schematic files, PCB layout files, BOM, custom symbol libraries, footprints, 3D models, and Gerber files are all found in the `/board` directory. The PCB layout uses the manufacturing capabilities given by [PCBWay](https://www.pcbway.com/). Although you can potentially use any board house of your choosing, the ECAD model was designed with PCBWay's capabilities in mind. Production costs were minimized as much as possible, so the PCB was designed using only two layers and kept under 100 mm. This lowered manufacturing fees from $100 down to $5! Beware that the final PCB design is still in progress and is not immediately available for manufacture.

![PCB Design, front](./board/images/lumenlab-pcb-3d-view-front.png)
<p style="text-align: center; font-style: italic;">Figure 1: PCB layout (front)</p>

![PCB Design, back](./board/images/lumenlab-pcb-3d-view-back.png)
<p style="text-align: center; font-style: italic;">Figure 1: PCB layout (back)</p>

## Method B: Hand-Soldering a Prototype

This is the more accessible and classic route, however this can be tricky depending on your background with electronics. Below is the prototype BOM if you'd like to build LumenLab yourself using pre-built modules and THT components. If you're an advanced electronics enthusiast, you may even be able to omit some of the suggestions, such as skipping the buck converter, directly powering the LED strip, and using the 5V power directly from the Vin pin to level shift the LED strip's data signal). These "barebones" alterations are not discussed in this document.

Assembly is remarkably similar to the guidance given on the WLED project. Using their [wiring diagram here](https://kno.wled.ge/basics/wiring-guides/) would be an excellent starting point.

#### <center>Bill of Materials</center>
|  Device | Description |
| --- | --- |
| ESP32 WROOM microcontroller | Only the [WROOM variants](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-DEVKITC-32UE/12091813) are supported because those are the only variants that support the Bluetooth classic protocol (BR/EDR). |
| WS2815 LED light strip | The 12V variant of the NeoPixel addressable RGB WS2812B. This project uses the 5m (16.4ft), 300 LED strip in black. |
| 12V 10A DC power supply | The 10A supply is required due to the high current demands of displaying white at full brightness. |
| MP2338 buck converter | Any step down regulator will suffice as long as it outputs 5V and at least 1A. The MP2338 can deliver 2-3A, enough to reliable power the ESP32 during intense gameplay and Bluetooth connectivity. |
| SN74AHCT125N logic level shifter | The ESP32's GPIO lines work using 3.3V signals. Level shifting to 5V ensures that the LED strip's data lines are not lost or corrupted. |
| PlayStation 3 game controller | The input device to navigate the main menu and play games. |
| SSD1306 OLED display module | Using the 0.96" variant, this displays the main menu for mode selection and in game mode is a HUD showing basic statistic like the user's high score. |
| Passive components | Resistors, capacitors, diodes, and fuses as needed for power protection, power stability and smoothing, low-pass filtering, and signal damping to minimize ringing. Refer to your MCU and buck converter's datasheet for guidance on what passives are needed. |

## Software

Regardless of whether your build of LumenLab was professionally manufactured and assembled, or hand-soldered to a perf board, the software is identical between the two approaches. To build this project from scratch, you at minimum need the following frameworks and dependencies:

* **PlatformIO**: A feature-rich ecosystem for embedded development. This framework includes the C/C++ compiler (avr-gcc) needed for MCU development. You can use the toolchain CLI directly, but installing the Visual Studio Code extension is significantly more approachable. [Download PlatformIO here](https://platformio.org/).
* **Python3** (&GreaterEqual;3.6): A dependency of PlatformIO to compile and flash the device. Also used in the virtualizer for local development.

### LED Strip Virtualization

To streamline the software development cycle, a virtualizer was created so that you can visually see what the LEDs are doing on a computer screen. This enables new features to be developed without needing to physically connect to the LED strip. Using the ESP32 is still required regardless during development, however when compiling in debug mode, the MCU does not emit signals to the LED strip and instead sends its color data via USB serial for rendering. An accompanying Python script was created using [ModernGL](https://moderngl.readthedocs.io/en/5.8.2/), an OpenGL binding for Python.

### Building the Repository
In order to simplify the build process for this repo, a script to initialize global configuration settings and credentials has been provided for both Windows and *nix. These scripts auto-generate the configuration file needed for a clean build.

_secrets.h_ - A header file that #define variables at compile-time, such as your WLAN credentials, and host/port ip address
