#The server chooses a random float number <SRF>. Run multiple clients. Each client chooses a random float number <CRF> and send it to the server. When the server does not receive any incoming connection for at least 10 seconds it chooses the client that has guessed the best approximation (is closest) for its own number and sends it back the message “You have the best guess with an error of <SRV>-<CRF>”. It also sends to each other client the string “You lost !”. The server closes all connections after this
# implement the code for the client - send a float number <CRV> to the server and receive the message “You have the best guess with an error of <SRV>-<CRF>” or “You lost !”.

import socket
import random

def main():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print(str(e))
    s.connect(('172.30.251.45', 12345))
    crf = random.uniform(0, 100)
    s.send(str(crf).encode())
    print(s.recv(1024).decode())
    s.close()

main()
