@echo off

@REM Setup project credentials
echo #pragma once> ..\include\secrets.h
echo:>>..\include\secrets.h
echo #define WIFI_SSID "<YOUR_NETWORK_SSID>">> ..\include\secrets.h
echo #define WIFI_PASSWORD "<YOUR_NETWORK_PASSWORD>">> ..\include\secrets.h
echo:>> ..\include\secrets.h
echo #define CLIENT_IP_ADDRESS "<YOUR.DESKTOP.IP.ADDR>">> ..\include\secrets.h
echo #define CLIENT_PORT 5555>> ..\include\secrets.h
echo:>> ..\include\secrets.h
echo #define SERIAL_BAUD 115200>> ..\include\secrets.h


@REM Setup runtime local configuration
echo ^[env^]> ..\platformio-override.ini
echo monitor_speed = 115200>> ..\platformio-override.ini

echo Created ^{project_root^}/include/secrets.h and ^{project_root^}/platformio-override.ini as starter templates.
echo Replace all values within ^<BRACKETS^> with your desired configuraitons and credentials.
echo Additionally, change the CLIENT_PORT to a different port if desired.
echo Make sure that the baud rate (monitor speed) in /include/secrets.h is the same as in /platformio-override.ini
echo Add any additional build flags to platformio-overrride.ini, such as your monitor or upload port.