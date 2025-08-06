#!/usr/bin/env python3
import sys
from pathlib import Path
import os
import subprocess
from pathlib import Path

def setup_venv_and_close():
  tools_dir = Path("tools")
  venv_dir = tools_dir / ".venv"

  if os.name == "nt":
    activate_cmd = f"{venv_dir}\\Scripts\\activate.bat"
  else:
    activate_cmd = f"source {venv_dir}/bin/activate"
  print(f"You are not running within the virtual environment.", file=sys.stderr)
  print(f"Activate the virtual environment with the following command:\n", file=sys.stderr)
  print(f"      {activate_cmd}", file=sys.stderr)
  sys.exit(1)

def in_venv():
    return sys.prefix != sys.base_prefix

def main():
  if not in_venv():
    setup_venv_and_close()

  base_dir = Path(__file__).parent.resolve()
  script_path = (base_dir / "led_gui" / "virtualization.py").resolve()
  cmd = [sys.executable, str(script_path)]

  if not script_path.exists():
    raise FileNotFoundError(f"Script not found: {script_path}")

  env = os.environ.copy()
  cwd = base_dir
  return subprocess.run(cmd, capture_output=True, text=True, env=env, cwd=cwd)

if __name__ == "__main__":
  main()