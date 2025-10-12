import socket
import struct
import threading
import time

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
PORT_UDP = 1235  # Changed to a different port for UDP
BROADCAST_ADDRESS = "192.168.0.255"  # Replace with your network's broadcast address
running = True
N = 10
terrain = ["u"] * N
terrain_lock = threading.Lock()

def is_explored(terrain):
    return "u" not in terrain

def broadcast_terrain(udp_sock):
    global terrain
    while running:
        terrain_str = "".join(terrain)
        udp_sock.sendto(terrain_str.encode('utf-8'), ("0.0.0.0", PORT_UDP))
        time.sleep(1)

def setup_udp():
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_sock.bind(("0.0.0.0", PORT_UDP))
    print(f"UDP broadcasting on {HOST}:{PORT_UDP}")
    return udp_sock

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_sock.bind((HOST, PORT_TCP))
    tcp_sock.listen(7)
    print(f"TCP server listening on {HOST}:{PORT_TCP}")
    return tcp_sock

def handle_client(client_socket, address):
    global terrain, running
    try:
        while running:
            buff = client_socket.recv(3)
            if not buff or len(buff) != 3:
                break
            index = int(buff[0] << 8 | buff[1])
            value = chr(buff[2])
            print(f"Received {value} at index {index}")
            with terrain_lock:
                if 0 <= index < N and terrain[index] == "u":
                    terrain[index] = value
                    if is_explored(terrain):
                        #broadcast_terrain(terrain)
                        print("Terrain is fully explored!")
                        running = False
    except Exception as e:
        print(f"Error with client {address}: {e}")
    finally:
        print(f"Client {address} is closing...")
        client_socket.close()

def accept_clients(tcp_socket):
    global running
    while running:
        try:
            client_socket, address = tcp_socket.accept()
            print(f"Connection from {address}")
            threading.Thread(target=handle_client, args=(client_socket, address)).start()
        except Exception as e:
            break

if __name__ == "__main__":
    tcp_socket = setup_tcp()
    udp_socket = setup_udp()

    threading.Thread(target=accept_clients, args=(tcp_socket,)).start()
    threading.Thread(target=broadcast_terrain, args=(udp_socket,)).start()

    while running:
        time.sleep(1)

    tcp_socket.close()
    udp_socket.close()
