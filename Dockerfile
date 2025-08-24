# Start from Python (needed for PlatformIO)
FROM python:3.11-slim

# Install dependencies for PlatformIO, ESP-IDF, and USB serial access
RUN apt-get update && apt-get install -y --no-install-recommends \
  git \
  curl \
  build-essential \
  libffi-dev \
  libssl-dev \
  python3-dev \
  udev \
  && rm -rf /var/lib/apt/lists/*

# Install PlatformIO CLI
RUN pip install --no-cache-dir platformio

# Set the working directory
WORKDIR /app

# Pre-download PlatformIO platforms for faster builds
RUN pio platform install espressif32 \
  && pio pkg install --global --library "PS3 Controller Host" --library "FastLED"

COPY . .

# Set up udev rules for USB device access
RUN echo 'SUBSYSTEM=="usb", MODE="0666"' > /etc/udev/rules.d/99-usb.rules

# Make sure PlatformIO caches in container
ENV PLATFORMIO_CORE_DIR=/root/.platformio

# Default command: open a shell
CMD ["/bin/bash"]
