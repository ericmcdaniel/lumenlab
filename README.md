# LumenLab

### Transforming pixels into a playground — because lighting should be more than just bright

# Dependencies
* python3
* platformio
* g++

# Build
In order to simplify the build process for this repo, a script to initialize global configuration settings and credentials has been provided for both Windows and *nix OS. These scripts auto-generate the relevant files needed for a clean build.

_secrets.h_ - A header file that #define variables at compile-time, such as your WLAN credentials, and host/port ip address