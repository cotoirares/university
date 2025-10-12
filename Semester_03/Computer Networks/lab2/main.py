import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("172.30.242.179", 1234))

def send_file_line_by_line():
    print(s.send("file.txt".encode()))
    with open("file.txt", "r") as f:
        for line in f:
            s.sendall(line.encode())

def main():
    send_file_line_by_line()
    length = s.recv(4)
    length = struct.unpack("!I", length)[0]
    print(length)

main()









