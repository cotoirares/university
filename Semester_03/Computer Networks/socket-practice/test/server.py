import socket
from threading import Thread

def handle_client(client_socket, address, peers, connected_sockets):
    try:
        data = client_socket.recv(1024).decode()
        if not data:
            raise ConnectionError("no data received")
        udp_port, operation = data.strip().split(',')
        peers[address[0]] = (int(udp_port), operation)
        print(f"Registered {address[0]}: {udp_port} with operation {operation}")

        peer_list = ','.join([f"{ip}:{port}:{op}" for ip, (port, op) in peers.items()])
        client_socket.send(peer_list.encode())
        # broadcast_peer_list(peers, connected_sockets)
    except Exception as e:
        print(f"Client {address} disconnected: {e}")
    finally:
        if address[0] in peers:
            del peers[address[0]]
            print(f"Removed {address[0]} from peers")
        if client_socket in connected_sockets:
            connected_sockets.remove(client_socket)
            client_socket.close()
            # broadcast_peer_list(peers, connected_sockets)

def broadcast_peer_list(peers, connected_sockets):
    peer_list = ','.join([f"{ip}:{port}:{op}" for ip, (port, op) in peers.items()])
    for sock in connected_sockets:
        try:
            sock.send(peer_list.encode())
        except Exception as e:
            print(f"Failed to send peer list to a client: {e}")

def start_server(host = 'localhost', port=1234):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(5)
    print(f"Sever listening on {host}:{port}")

    peers = {}
    connected_sockets = []

    while True:
        client_sock, addr = server.accept()
        print(f"Accepted connection from {addr}")
        connected_sockets.append(client_sock)
        Thread(target=handle_client, args=(client_sock, addr, peers, connected_sockets), daemon=True).start()


if __name__ == "__main__":
    start_server()
