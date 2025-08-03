# LED Virtualizer

An LED visualizer using fastplotlib that listens for UDP color commands and updates a ring of virtual LEDs.

## Usage

Setup your virtual environment first
``` bash
cd tools
python -m venv .venv

# For Windows:
.venv\Scripts\activate

# Otherise, for *nix
source .venv/bin/activate
```

Lastly, install the dependencies and run the virtualizer
``` bash
pip install -r requirements.txt
python virtualization.py
```