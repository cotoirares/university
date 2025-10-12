import socket
import struct


def grade5_client(server_host='localhost', server_udp_port=10000):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # TCP
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    numbers = [1, 2, 3, 4, 5]
    op = chr(43) # '+'
    operation_str = struct.pack("c", op) #op.encode()
    encoded = struct.pack(">{}H".format(len(numbers)), *numbers)
    message = operation_str + encoded
    udp_socket.sendto(message, (server_host, server_udp_port))
    try:
        data, _ = udp_socket.recvfrom(1024)
        print(data.decode())
    except Exception as e:
        print(f"Error receiving data: {e}")
    udp_socket.close()

if __name__ == "__main__":
    grade5_client()
