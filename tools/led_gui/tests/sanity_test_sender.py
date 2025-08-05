import socket
import time

NUM_LEDS = 300
UDP_IP = "0.0.0.0"
UDP_PORT = 5555

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

colors = [(255, 0, 0), (0, 0, 255), (255, 255, 255)]
shift = 0

while True:
  frame = []
  for i in range(NUM_LEDS):
    color = colors[(i + shift) % len(colors)]
    frame.extend(color)
  sock.sendto(bytes(frame), (UDP_IP, UDP_PORT))
  shift = (shift - 1) % len(colors)
  time.sleep(0.05)
