import socket
import threading

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
PORT_UDP = 1234

def setup_tcp():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    tcp_socket.bind((HOST, PORT_TCP))
    # tcp_socket.listen(5) why 5?

    print(f"TCP Server listening at {HOST}:{PORT_TCP}")
    return tcp_socket

def setup_udp():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_socket.bind((HOST, PORT_UDP))

    print(f"UDP Server listening at {HOST}:{PORT_UDP}")
    return udp_socket

def handle_client(client_socket, address):
    print(f"Accepted connection from {address}")
    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        received_data = data.decode('utf-8')
        print(f"Received data: {received_data}")

if __name__ == "__main__":
    tcp_socket = setup_tcp()
    udp_socket = setup_udp()

    while True:
        client_socket, address = tcp_socket.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, address))
        client_thread.start()

