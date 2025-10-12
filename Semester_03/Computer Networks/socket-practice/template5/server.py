import socket

HOST = socket.gethostbyname(socket.gethostname())
PORT_TCP = 1234

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_sock.bind((HOST, PORT_TCP))
    tcp_sock.listen(3)
    print(f"TCP server listening on {HOST}:{PORT_TCP}")
    return tcp_sock

if __name__ == "__main__":
    tcp_socket = setup_tcp()

    # Accept a connection
    conn, addr = tcp_socket.accept()
    print(f"Connected by {addr}")

    # Receive data from the client
    buff = conn.recv(1024)  # 1024 is the buffer size
    received_str = buff.decode('utf-8')
    numb, carac = received_str.split(';')
    number = int(numb)
    character = carac  # Already a string, no need to convert with chr()
    print(f"Received number: {number}")
    print(f"Received character: {character}")

    # Sending a response to the client
    conn.send("Hello".encode('utf-8'))
    print("Sent Hello to client")

    # Close the connection
    conn.close()
    print(f"Server {HOST} is closing...")
