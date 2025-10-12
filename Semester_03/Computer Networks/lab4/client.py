import sys
import socket
def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <command>")
        sys.exit(1)
    command = sys.argv[1]
    server_address = ('localhost', 12345)

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    try:
        print(f"Sending command: {command}")
        sock.sendto(command.encode(), server_address)

        print("Waiting for response...")
        data, _ = sock.recvfrom(65535)
        response = data.decode()
        print(f"Received response:\n{response}")
    finally:
        sock.close()

if __name__ == '__main__':
    main()
