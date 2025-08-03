import socket
import time

HOST = 'localhost'
PORT = 5555

colors = ['red', 'white', 'blue']

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
  for color in colors:
      print(f"Sending color: {color}")
      sock.sendto(color.encode('utf-8'), (HOST, PORT))
      time.sleep(0.5)

sock.close()
