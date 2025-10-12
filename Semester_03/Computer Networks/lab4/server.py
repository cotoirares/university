import socket
import subprocess
import multiprocessing

def handle_client(data, address):
    command = data.decode()
    print(f"Received command from {address}: {command}")

    try:
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        output = result.stdout + result.stderr
        exit_code = result.returncode
    except Exception as e:
        output = str(e)
        exit_code = -1

    response = f"Exit code: {exit_code}\nOutput:\n{output}"
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(response.encode(), address)
    sock.close()

def main():
    server_address = ('', 12345)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(server_address)
    print(f"Server listening on port {server_address[1]}")

    while True:
        data, address = sock.recvfrom(65535)
        process = multiprocessing.Process(target=handle_client, args=(data, address))
        process.start()

if __name__ == '__main__':
    main()
