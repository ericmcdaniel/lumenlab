# LumenLab

### Transforming pixels into a playground — because lighting should be more than just bright

# Build
In order to simplify the build process for this repo, a script to initialize global configuration settings and credentials has been provided for both Windows and *nix OS. These scripts auto-generate the relevant files needed for a clean build.

|File|Description|
|---|---|
|secrets.h|A header file that #define variables at compile-time, such as your WLAN credentials, and host/port ip address|
|platformio-override.ini|Environment settings for using PlatformIO, such as your baud rate and upload_port|