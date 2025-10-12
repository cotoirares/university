import socket
import struct


def grade5_server(host='localhost', udp_port=10000):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind((host, udp_port))
    print("Server is listening for UDP messages...")
    try:
        data, addr = udp_socket.recvfrom(4096)
        begin = 1
        if data:
            operation = struct.unpack("c", data[0:begin])[0] #.decode()
            numbers = struct.unpack(">{}H".format(5), data[begin:])
            if isinstance(numbers, list) and isinstance(operation, str):
                print(f"Received numbers: {numbers} and function: {operation} from {addr}")
                udp_socket.sendto("Hello from server!".encode(), addr)
            else:
                udp_socket.sendto("Invalid data received.".encode(), addr)
    except Exception as e:
        print(f"Error: {e}")
    udp_socket.close()


if __name__ == "__main__":
    grade5_server()