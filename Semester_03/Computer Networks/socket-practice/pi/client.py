import socket
import struct
import random
import time

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234
PORT_UDP = 1234
running = True

def setup_udp():
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # client
    udp_sock.connect((HOST, PORT_UDP))
    print(f"UDP connected to {HOST}:{PORT_UDP}")
    return udp_sock

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # client
    tcp_sock.connect((HOST, PORT_TCP))
    print(f"TCP connected to {HOST}:{PORT_TCP}")
    return tcp_sock

if __name__ == "__main__":
    udp_sock = setup_udp()
    tcp_sock = setup_tcp()

    while running:
        numb1 = random.randint(0, 100)
        numb2 = random.randint(0, 100)

        try:
            string_of_numbers = str(numb1) + ";" + str(numb2)
            udp_sock.send(string_of_numbers.encode('utf-8'))
            print(f"Sent numbers: {numb1}, {numb2}")
        except Exception as e:
            print(e)
            running = False

        try:
            pi_approx = tcp_sock.recv(4)
            pi_approx = struct.unpack("f", pi_approx)[0]
            print(f"Pi approximation: {pi_approx}")
        except Exception as e:
            print("Found approximation. Closing connection...")
            running = False
        #time.sleep(0.5)

    print(f"Client {HOST} is closing...\n")
    udp_sock.close()
    tcp_sock.close()








