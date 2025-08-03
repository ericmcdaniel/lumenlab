import pygame
import socket
import threading
import queue

# Config
WIDTH, HEIGHT = 1800, 900
MARGIN = 50
NUM_CIRCLES = 300
UDP_PORT = 5555
CIRCLE_RADIUS = 5

# Thread-safe queue for colors
color_queue = queue.Queue()

# Compute perimeter circle positions as a list of (x,y) tuples
def compute_perimeter_positions():
    w, h = WIDTH - 2 * MARGIN, HEIGHT - 2 * MARGIN
    perimeter = 2 * (w + h)
    step = perimeter / NUM_CIRCLES
    positions = []
    d = 0
    while len(positions) < NUM_CIRCLES:
        x = d % perimeter
        if x < w:
            px, py = MARGIN + x, MARGIN
        elif x < w + h:
            px, py = WIDTH - MARGIN, MARGIN + (x - w)
        elif x < 2 * w + h:
            px, py = WIDTH - MARGIN - (x - w - h), HEIGHT - MARGIN
        else:
            px, py = MARGIN, HEIGHT - MARGIN - (x - 2 * w - h)
        positions.append((int(px), int(py)))
        d += step
    return positions

# UDP listener thread
def udp_listener():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('0.0.0.0', UDP_PORT))
    print(f"[UDP] Listening on port {UDP_PORT}")
    while True:
        data, _ = sock.recvfrom(1024)
        color_str = data.decode('utf-8').strip().lower()
        if color_str in ("red", "white", "blue"):
            print(f"Received color: {color_str}")
            color_queue.put(color_str)

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("LED Circle Display")

    positions = compute_perimeter_positions()

    # Initial color: white
    current_color = pygame.Color('white')

    # Start UDP listener thread
    threading.Thread(target=udp_listener, daemon=True).start()

    running = True
    clock = pygame.time.Clock()

    while running:
        # Event handling (just quit)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Check for color update from UDP thread
        while not color_queue.empty():
            color_name = color_queue.get()
            current_color = pygame.Color(color_name)

        # Clear screen
        screen.fill((0, 0, 0))

        # Draw circles
        for pos in positions:
            pygame.draw.circle(screen, current_color, pos, CIRCLE_RADIUS)

        pygame.display.flip()
        clock.tick(60)  # Limit to 60 FPS

    pygame.quit()

if __name__ == "__main__":
    main()
