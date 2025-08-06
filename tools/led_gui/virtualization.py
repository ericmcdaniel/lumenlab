import pygame
import socket
import sys
import logging
from pathlib import Path

def main():
  NUM_LEDS = 300
  WINDOW_WIDTH = 1660
  WINDOW_HEIGHT = 906
  LED_RADIUS = 9
  LED_MARGIN = 4
  BG_COLOR = (32, 32, 32)

  PORT = 5555

  logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

  logger = logging.getLogger(__name__)

  def compute_led_positions():
    positions = []
    x = 50
    y = 10

    for index, _ in enumerate([0] * NUM_LEDS):
      if index > 278:
        y -= LED_MARGIN + LED_RADIUS
      elif index == 278:
        x -= (LED_MARGIN + LED_RADIUS) * 4
        y -= (LED_MARGIN + LED_RADIUS) * 4
      elif index > 166:
        x -= LED_MARGIN + LED_RADIUS
      elif index == 166:
        x -= (LED_MARGIN + LED_RADIUS) * 4
        y += (LED_MARGIN + LED_RADIUS) * 4
      elif index > 112:
        y += LED_MARGIN + LED_RADIUS
      elif index == 112:
        x += (LED_MARGIN + LED_RADIUS) * 4
        y += (LED_MARGIN + LED_RADIUS) * 4
      elif index > 0:
        x += LED_MARGIN + LED_RADIUS
      elif index == 0:
        x += (LED_MARGIN + LED_RADIUS) * 4
        y += (LED_MARGIN + LED_RADIUS) * 4
      positions.append((int(x), int(y), LED_RADIUS, LED_RADIUS))

    return positions

  logger.info("Initializing LED strip visualizer")
  pygame.init()
  screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
  screen.fill(BG_COLOR)
  pygame.display.set_caption("ESP32 LED Strip Visualizer")
  base_dir = Path(__file__).parent.parent.parent.resolve()
  icon_path = (base_dir / "assets" / "lumenlab-icon.png").resolve()
  pygame.display.set_icon(pygame.image.load(icon_path))
  clock = pygame.time.Clock()

  font = pygame.font.SysFont("Arial, Sans Serif", 48)
  text_surface = font.render("LumenLab LED Debug Visualizer", True, (200, 200, 200))
  text_rect = text_surface.get_rect(center=(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 3))
  screen.blit(text_surface, text_rect)

  led_positions = compute_led_positions()
  led_colors = [(255, 255, 255)] * NUM_LEDS

  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  sock.bind(("0.0.0.0", PORT))
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 4096)

  logger.info(f"Listening for UDP packets send from ESP32 on port {PORT}...")


  running = True
  while running:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        running = False
        break

    sock.settimeout(0.01)
    try:
      data, _ = sock.recvfrom(4096)
      if len(data) >= NUM_LEDS * 3:
        led_colors = [ (data[i], data[i + 1], data[i + 2]) for i in range(0, NUM_LEDS * 3, 3) ]
    except socket.timeout:
      pass
    except Exception as e:
      logging.error("UDP receive error:", e)
      continue

    for pos, color in zip(led_positions, led_colors):
      pygame.draw.rect(screen, color, pos, LED_RADIUS)
    pygame.display.flip()

    clock.tick(60)

  pygame.quit()
  sys.exit()


if __name__ == "__main__":
  main()