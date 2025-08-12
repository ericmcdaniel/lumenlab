<p align="center"><img src="assets/lumenlab-logo.png" alt="LumenLab Logo" /></p>
<p align="center">Transforming pixels into a playground — <i>because lighting should be more than just bright</i></p>

---

__LumenLab__ is a creative LED platform designed to transform your space into an interactive playground of light. Built around an ESP32 and the WS2815 addressable LED strip, LumenLab enables programmable animations, simple games, and dynamic lighting effects that make any room more engaging—especially for children. Whether you're adding ambiance under a lofted bed or building custom visual experiences, LumenLab provides a flexible, open foundation for experimenting with light and interactivity.


# Requirements
* Must download and install the driver to interact with the CP2102N USB-to-UART Bridge. [Available for download here.](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

# Dependencies
* python3
* platformio
* g++

# Build
In order to simplify the build process for this repo, a script to initialize global configuration settings and credentials has been provided for both Windows and *nix OS. These scripts auto-generate the relevant files needed for a clean build.

_secrets.h_ - A header file that #define variables at compile-time, such as your WLAN credentials, and host/port ip address