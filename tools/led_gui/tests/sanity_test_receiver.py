import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 5555))
while True:
    data, addr = sock.recvfrom(1024)
    print(data)
    rgb = [
        (data[i], data[i + 1], data[i + 2]) for i in range(0, len(data), 3)
    ]

    # Print a preview
    for i in range(5):
        print(f"LED {i}: R={rgb[i][0]} G={rgb[i][1]} B={rgb[i][2]}")
