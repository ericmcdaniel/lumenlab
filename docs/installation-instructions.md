# Installation Instructions

This guide explains how to flash the **LumenLab firmware** to your ESP32 using **Windows PowerShell**.
The process is fully automated using a single one-line command.

---

## Quick Install (One-Line PowerShell Command)

The installation script assumes you have Docker Desktop and WSL2 installed in advance and running. If you don't, download them first before proceeding.

> **Open PowerShell as Administrator**, then run:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; `iwr -useb https://raw.githubusercontent.com/ericmcdaniel/lumenlab/refs/heads/main/tools/install-lumenlab.ps1`
| iex
```

This command:

- Downloads the installation script
- Detects your ESP32
- Handles USB passthrough to WSL
- Pulls the latest Docker image
- Flashes the firmware automatically

---

## Troubleshooting

### “Timeout waiting for /dev/ttyUSB0”
- Ensure the ESP32 is physically plugged in
- Try a different USB cable (must support **data**, not just charging)
- Try unplugging and reconnecting the ESP32

---

### "usbipd : The term 'usbipd' is not recognized as the name of a cmdlet"
The script requires usbipd to be installed. This should have been included in your WSL2 installation, but if not you can install it manually.
```powershell
winget install --exact dorssel.usbipd-win
```

Then re-run the install command.

---

### “usbipd: error: Device is already attached”
The script attempts to resolve this automatically.
To manually reset device attachments:

```powershell
usbipd detach --all
```

Then re-run the install command.

---

### Docker error: “WSL integration disabled”
Open Docker Desktop, and enable it under:

> Docker Desktop → Settings → Resources → WSL Integration → Enable Ubuntu

---

## How to Verify Successful Flash

Assuming everything worked:
- The ESP32 will reboot
- The LumenLab logo should appear on the screen
- Red LED animations may begin if you don't connect your PS3 controller within 30 seconds

---