import socket
import struct
import threading
import time

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
PORT_UDP = 1234
points = []
e = 0.0001
running = True
approx = 0.0

def convert_number(num):
    return (num - 50)/50

def points_in_circle():
    return sum(1 for x, y in points if x**2 + y**2 <= 1)

def estimate_pi():
    return 4 * points_in_circle() * len(points)**(-1)

def setup_udp():
  udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

  udp_sock.bind((HOST, PORT_UDP))

  print(f"UDP listening on {HOST}:{PORT_UDP}")
  return udp_sock

def setup_tcp():
  tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

  tcp_sock.bind((HOST, PORT_TCP))
  tcp_sock.listen(7)

  print(f"TCP server listening on {HOST}:{PORT_TCP}")
  return tcp_sock

def handle_client(client_socket, address):
    global points, running
    while running:
        try:
            approx_size = struct.pack("f", approx)
            client_socket.send(approx_size)
            time.sleep(0.05)
        except Exception as e:
            break
    client_socket.close()

def accept_clients(tcp_socket):
    global running
    while running:
        try:
            client_socket, address = tcp_socket.accept()
            print(f"Accepted connection from {address}")
            threading.Thread(target=handle_client, args=(client_socket, address)).start()
        except Exception as ex:
            break


if __name__ == "__main__":
    tcp_socket = setup_tcp()
    udp_socket = setup_udp()
    clients = []

    tcp_thread = threading.Thread(target=accept_clients, args=(tcp_socket,))
    tcp_thread.start()

    while running:
        #receive from udp two numbers in 0, 100
        buff, addr = udp_socket.recvfrom(7)
        numbers_str = buff.decode('utf-8')
        numb1, numb2 = numbers_str.split(';')
        numb1 = convert_number(int(numb1))
        numb2 = convert_number(int(numb2))
        points.append((numb1, numb2))
        old_approx = approx
        approx = estimate_pi()
        if abs(approx - old_approx) < e and approx > 0 and approx < 4:
            running = False
            print(f"Aprroximation stable at {approx}")

    tcp_socket.close()
    udp_socket.close()





