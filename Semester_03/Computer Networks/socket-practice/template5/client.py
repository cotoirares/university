import socket
import random

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
running = True

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # client
    tcp_sock.connect((HOST, PORT_TCP))
    print(f"TCP connected to {HOST}:{PORT_TCP}")
    return tcp_sock

if __name__ == "__main__":
    tcp_sock = setup_tcp()
    number = random.randint(1, 100)
    character = random.choice("abcdef")
    message = f"{number};{character}"
    tcp_sock.send(message.encode('utf-8'))
    print(f"Sent message: {message}")
    buff = tcp_sock.recv(5)
    received_str = buff.decode('utf-8')
    print(f"Received message: {received_str}")
    tcp_sock.close()