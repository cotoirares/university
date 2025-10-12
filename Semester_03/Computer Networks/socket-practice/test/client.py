import socket
import random
import time
from threading import Thread

def listen_for_computation(udp_sock, operation):
    while True:
        data, addr = udp_sock.recvfrom(1024)
        numbers_str = data.decode()
        numbers = list(map(int, numbers_str.split(',')))
        if operation == 'm':
            result = sum(numbers)/len(numbers)
        elif operation == '+':
            result = sum(numbers)
        else:
            result = 1
            for n in numbers:
                result *= n
        udp_sock.sendto(str(result).encode(), addr)


def send_computation_tasks(udp_sock, peers):
    while True:
        n = random.randint(2,5)
        numbers = [random.randint(1, 10) for _ in range(n)]
        operation = random.choice(['m', '+', '*'])
        for ip, (port, op) in peers.items():
            if op == operation:
                udp_sock.sendto(str(numbers).encode(), ('localhost', port))
                result = eval(udp_sock.recv(1024).decode())
                print(f"Result of {operation} on {numbers}: {result}")
                break
            time.sleep(2)

def start_client(server_host = 'localhost', server_port = 1234):
    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.connect((server_host, server_port))
    print(f"connected to the server at {server_host}:{server_port}")
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_port = random.randint(6000, 7000)
    udp_sock.bind((server_host, udp_port))
    print(f"UDP socket bound to port {udp_port}")

    operation = random.choice(['m', '+', '*'])
    server_sock.send(f"{udp_port}, {operation}".encode())

    peers_data = server_sock.recv(4096).decode()
    if peers_data:
        peers = peers_data.split(',') if peers_data else []
        print(f"Received peers list {peers}")
    else:
        peers = []
        print("No peers received")
    Thread(target=listen_for_computation, args=(udp_sock, operation), daemon=True).start()
    Thread(target=send_computation_tasks, args=(udp_sock, peers)).start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Cliend shutting down")
    finally:
        server_sock.close()
        udp_sock.close()


if __name__ == "__main__":
    start_client()