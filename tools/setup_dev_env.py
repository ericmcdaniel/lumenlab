#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path

def create_secrets_header():
  root_dir = Path(__file__).parent.parent
  secrets_file = root_dir / "include" / "secrets.h"

  with open(secrets_file, "w") as file:
    # Setup project credentials
    file.write("#pragma once\n\n")

    file.write("#define WIFI_SSID \"<YOUR_NETWORK_SSID>\"\n")
    file.write("#define WIFI_PASSWORD \"<YOUR_NETWORK_PASSWORD>\"\n\n")

    file.write("#define CLIENT_IP_ADDRESS \"<YOUR.DESKTOP.IP.ADDR>\"\n")
    file.write("#define CLIENT_PORT 12345\n\n")
    file.write("#define SERIAL_BAUD 115200\n")

def setup_python_virtual_environment():
  tools_dir = Path("tools")
  venv_dir = tools_dir / ".venv"

  print(f"\n\nCreating a python virtual environment in {venv_dir}...")
  subprocess.check_call([sys.executable, "-m", "venv", str(venv_dir)])

  requirements_file = tools_dir / "requirements.txt"
  if requirements_file.exists():
      print("Installing dependencies from requirements.txt...")
      pip_exe = venv_dir / ("Scripts" if os.name == "nt" else "bin") / "pip"
      subprocess.check_call([str(pip_exe), "install", "-r", str(requirements_file)])
  else:
      print("No requirements.txt found. Skipping package installation.")

  if os.name == "nt":
      activate_cmd = f"{venv_dir}\\Scripts\\activate"
  else:
      activate_cmd = f"source {venv_dir}/bin/activate"

  activate_script = Path("activate-virtual-env")
  if os.name == "nt":
      script_path = activate_script.with_suffix(".bat")
      activate_cmd = f"{venv_dir}\\Scripts\\activate.bat"
      script_path.write_text(f"@echo off\ncall {activate_cmd}\n")
  else:
      script_path = activate_script.with_suffix(".sh")
      activate_cmd = f"source {venv_dir}/bin/activate"
      script_path.write_text(f"#!/bin/bash\n{activate_cmd}\n")
      script_path.chmod(0o755)

  print(f"\nSetup complete.")
  print(f"Activate the virtual environment by running:\n")
  print(f"    {script_path}")

def main():
  create_secrets_header()

  print("\nCreated {project_root}/include/secrets.h as a starter template.")
  print("  • Replace all values within <BRACKETS> with your desired configuraitons and credentials.")
  print("  • Additionally, change the CLIENT_PORT to a different port if desired.\n\n")
  print("Make sure that the baud rate (monitor speed) in /include/secrets.h is the same as in /platformio.ini")

  setup_python_virtual_environment()

if __name__ == "__main__":
  main()