import socket
import threading
import time
import random
import math

# Predefined list of functions
functions = [
    {'func': lambda x: x, 'str': 'x'},
    {'func': lambda x: x*2, 'str': 'x*2'},
    {'func': lambda x: math.sin(math.pi * x), 'str': 'math.sin(math.pi * x)'}
]

total_points = 0
points_below_curve = 0
current_function = random.choice(functions)
clients = {}
lock = threading.Lock()
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def compute_area_periodically():
    global total_points, points_below_curve
    while True:
        time.sleep(5)
        if total_points > 0:
            area = points_below_curve / total_points
            send_area_to_clients(area)
            print(f"Current estimated area: {area}")

def send_area_to_clients(area):
    message = f"Current area estimate: {area}".encode()
    for addr, client_info in clients.items():
        udp_socket.sendto(message, (addr[0], client_info['udp_port']))

def broadcast_final_result():
    global total_points, points_below_curve
    area = points_below_curve / total_points
    message = f"Final area estimate: {area}".encode()
    print(f"Final area estimate: {area}")
    for addr, client_info in clients.items():
        udp_socket.sendto(message, (addr[0], client_info['udp_port']))
        client_info['conn'].close()

def reset_for_new_function():
    global total_points, points_below_curve, current_function
    current_function = random.choice(functions)
    total_points = 0
    points_below_curve = 0
    print("Switching to new function for computation.")

def handle_client(conn, addr):
    global total_points, points_below_curve
    print(f"Client {addr} connected.")
    try:
        # Receive UDP port from client
        udp_port = int(conn.recv(1024).decode())
        clients[addr] = {'conn': conn, 'udp_port': udp_port}
        # Send function string to client
        conn.sendall(current_function['str'].encode())
        # Receive batches of binary data
        while True:
            data = conn.recv(4096)
            if not data:
                break
            results = list(data)
            with lock:
                points_below_curve += sum(results)
                total_points += len(results)
            if total_points >= 100:
                broadcast_final_result()
                reset_for_new_function()
    except Exception as e:
        print(f"Error with client {addr}: {e}")
    finally:
        conn.close()
        with lock:
            if addr in clients:
                del clients[addr]
        print(f"Client {addr} disconnected.")

def tcp_listener(host='localhost', tcp_port=8000):
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.bind((host, tcp_port))
    tcp_socket.listen()
    print("Server is listening for TCP connections...")
    while True:
        conn, addr = tcp_socket.accept()
        threading.Thread(target=handle_client, args=(conn, addr)).start()

def start_server():
    threading.Thread(target=tcp_listener).start()
    threading.Thread(target=compute_area_periodically).start()

if __name__ == "__main__":
    start_server()