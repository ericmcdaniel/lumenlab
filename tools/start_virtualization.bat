@echo off
set "VENV_PATH=tools\.venv"
set "SCRIPT_PATH=tools\led_gui\virtualization.py"

echo Activating Python virtual environment at %VENV_PATH%\Scripts\activate.bat
call "%VENV_PATH%\Scripts\activate.bat"
pip install -r tools\requirements.txt

echo Starting the virtualization
python "%SCRIPT_PATH%" %*

echo Deactivating .venv
call "%VENV_PATH%\Scripts\deactivate.bat"