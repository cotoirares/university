#The server chooses a random float number <SRF>. Run multiple clients. Each client chooses a random float number <CRF> and send it to the server. When the server does not receive any incoming connection for at least 10 seconds it chooses the client that has guessed the best approximation (is closest) for its own number and sends it back the message “You have the best guess with an error of <SRV>-<CRF>”. It also sends to each other client the string “You lost !”. The server closes all connections after this
# implement the code for the server - receive a float number <CRV>. When the server does not receive any incoming connection for at least 10 seconds it chooses the client that has guessed the best approximation (is closest) for its own number and sends it back the message “You have the best guess with an error of <SRV>-<CRF>”. It also sends to each other client the string “You lost !”. The server closes all connections after this.

import socket
import random
import time

def main():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print(str(e))
    s.bind(('0.0.0.0', 12345))
    s.listen(5)
    clients = []
    while True:
        try:
            client, addr = s.accept()
            clients.append(client)
            print("Client connected")
        except:
            print("No more clients connected")
            break
    srf = random.uniform(0, 100)
    print("SRF: ", srf)
    time.sleep(10)
    best_guess = 100
    best_client = None
    for client in clients:
        crf = float(client.recv(1024).decode())
        print("CRF: ", crf)
        if abs(srf - crf) < best_guess:
            best_guess = abs(srf - crf)
            best_client = client
    for client in clients:
        if client == best_client:
            client.send(f"You have the best guess with an error of {srf - crf}".encode())
        else:
            client.send("You lost !".encode())
        client.close()
    s.close()

main()





