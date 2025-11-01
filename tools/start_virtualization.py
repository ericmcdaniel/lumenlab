#!/usr/bin/env python3
import sys
import os
from pathlib import Path
import argparse


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

    parser = argparse.ArgumentParser(
        prog="LumenLab LED Virtualizer",
        description="A virtualization of what the physical LEDs are displaying",
        epilog='''
Usage Example:
        python start_virtualization.py --num_leds 300 --width 1650 --height 950 --port COM3 --baud_rate 921600
                -or-
        python start_virtualization.py -p COM3
''',
        formatter_class=argparse.RawTextHelpFormatter,
        allow_abbrev=False
    )

    parser.add_argument("-L", "--num_leds", type=int, default=300, help="The number of LEDs in your LED strip")
    parser.add_argument("-p", "--port", type=str, default="COM3", help="The USB serial port that the ESP32 is connected to. Defaults to COM3")
    parser.add_argument("-b", "--baud_rate", type=int, default=921600, help="The baud rate for serial streaming what the LEDs are doing. Defaults to 921600")
    window_dimensions = parser.add_argument_group("Window Dimensions", "Configure the visualization's height and width")
    window_dimensions.add_argument("-W", "--width", type=int, default=1650, help="The width of the window in pixels. Defaults to 1650")
    window_dimensions.add_argument("-H", "--height", type=int, default=950, help="The height of the window in pixels. Defaults to 950")
    args, _ = parser.parse_known_args()

    from led_gui.virtualization import start_led_virtualization
    start_led_virtualization(
        window_size=(args.width, args.height),
        num_leds=args.num_leds,
        port=args.port,
        baud_rate=args.baud_rate
    )


if __name__ == "__main__":
    main()
