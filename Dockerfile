FROM python:3.11-slim AS builder

RUN apt-get update && apt-get install -y --no-install-recommends \
  git curl build-essential libffi-dev libssl-dev python3-dev udev \
  && rm -rf /var/lib/apt/lists/*

RUN pip install --no-cache-dir platformio

WORKDIR /app

RUN pio platform install espressif32 \
  && pio pkg install --global --library "PS3 Controller Host@^1.1.0" \
  && pio pkg install --global --library "FastLED@^3.10.2" \
  && pio pkg install --global --library "Adafruit SSD1306@^2.5.15" \
  && pio pkg install --global --library "Adafruit GFX Library@^1.12.1"

COPY . .

RUN chmod +x /app/tools/flash-firmware.sh

RUN echo "Building PlatformIO release firmware..." && pio run --environment release

FROM python:3.11-slim

WORKDIR /app

RUN pip install --no-cache-dir esptool pyserial

COPY --from=builder /app/tools/flash-firmware.sh ./tools/flash-firmware.sh
COPY --from=builder /app/.pio/build/release/bootloader.bin ./bootloader.bin
COPY --from=builder /app/.pio/build/release/partitions.bin ./partitions.bin
COPY --from=builder /app/.pio/build/release/firmware.bin ./firmware.bin

RUN chmod +x /app/tools/flash-firmware.sh

CMD ["/app/tools/flash-firmware.sh"]
