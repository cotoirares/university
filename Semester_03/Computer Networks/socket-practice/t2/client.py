import socket
import threading
import time
import random
import math

def safe_eval(func_str, x):
    allowed_funcs = {
        'x': x,
        'math': math,
        'sin': math.sin,
        'pi': math.pi,
        '_builtins_': {}
    }
    return eval(func_str, allowed_funcs)


def listen_for_area_estimates(udp_socket):
    while True:
        data, _ = udp_socket.recvfrom(1024)
        print(data.decode())

def generate_and_send_points(tcp_socket, func_str):
    while True:
        time.sleep(2)
        n = random.randint(5, 20)
        results = []
        for _ in range(n):
            x = random.uniform(0, 1)
            y = random.uniform(0, 1)
            fx = safe_eval(func_str, x)
            results.append(int(y < fx))
        # Send batch of binary results to server
        tcp_socket.sendall(bytes(results))

def register_with_server(server_host, server_tcp_port, udp_port):
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.connect((server_host, server_tcp_port))
    # Send UDP port to server
    tcp_socket.sendall(str(udp_port).encode())
    # Receive function string from server
    function_str = tcp_socket.recv(1024).decode()
    print(f"Received function from server: {function_str}")
    return tcp_socket, function_str

def start_client(server_host='localhost', server_tcp_port=8000, udp_port=9000):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind(('', udp_port))

    tcp_socket, function_str = register_with_server(server_host, server_tcp_port, udp_port)

    threading.Thread(target=listen_for_area_estimates, args=(udp_socket,)).start()
    threading.Thread(target=generate_and_send_points, args=(tcp_socket, function_str)).start()


if __name__ == "__main__":
    start_client()