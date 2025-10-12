import socket
import struct
import random
import time

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
PORT_UDP = 1235  # Changed to match the new UDP port
N = 10  # Match with the server's N value
letters = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

def setup_udp():
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_sock.bind((HOST, PORT_UDP))  # Bind to receive broadcasts
    print(f"UDP socket ready to receive from {HOST}:{PORT_UDP}")
    return udp_sock

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.connect((HOST, PORT_TCP))
    print(f"TCP connected to {HOST}:{PORT_TCP}")
    return tcp_sock

if __name__ == "__main__":
    udp_sock = setup_udp()
    tcp_sock = setup_tcp()

    while True:
        index = random.randint(0, N - 1)
        value = str(random.choice(letters))
        print(f"Sending {value} at index {index}")
        tcp_sock.send(struct.pack(">Hc", index, value.encode('utf-8')))
        time.sleep(1)

        buff = udp_sock.recv(1024)
        if not buff:
            break
        terrain = list(buff.decode('utf-8'))
        print(f"Received terrain: {terrain}")
        if "u" not in terrain:
            print("Terrain fully explored!")
            break

    print("Client closing...")
    udp_sock.close()
    tcp_sock.close()
