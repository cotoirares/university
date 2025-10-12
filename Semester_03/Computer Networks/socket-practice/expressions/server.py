import select
import socket
import threading
import time
import random

PORT = 7777
TCP_PORT = 1234

def make_expression():
    return f"{random.randint(1, 10)}{random.choice(['+', '-', '*', '/'])}{random.randint(1, 10)}"

def handle_student(conn, addr, expressions, answers):
    try:
        print(f"Connection from {addr}")
        student_answers = []

        for _ in range(len(answers)):
            ready_to_read, _, _ = select.select([conn], [], [], 5)  # 5-second timeout
            if ready_to_read:
                data = conn.recv(1024).decode('utf-8').strip()
                if not data:
                    break
                try:
                    idx, answer = map(int, data.split('.'))
                    if 0 <= idx < len(answers):
                        student_answers.append((idx, answer))
                except ValueError:
                    print(f"Invalid data format from student: {data}")
            else:
                print(f"No data received from {addr} within timeout period")
                break

        score = sum(1 for idx, ans in student_answers if ans == answers[idx])
        response = f"Your score is {score} out of {len(answers)}"
        conn.send(response.encode('utf-8'))

    except Exception as e:
        print(f"Error handling student {addr}: {e}")
    finally:
        conn.close()

if __name__ == "__main__":
    broadcast_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_sock.bind(('0.0.0.0', TCP_PORT))
    tcp_sock.listen(5)
    tcp_sock.setblocking(False)

    start_time = time.time()
    expressions = []
    answers = []
    student_threads = []

    print("Server started - broadcasting questions...")

    while time.time() - start_time < 12:
        expressions = [make_expression() for _ in range(3)]
        answers = [eval(expr) for expr in expressions]

        msg = ';'.join(expressions).encode('utf-8')
        broadcast_sock.sendto(msg, ('255.255.255.255', PORT))
        print(f"Broadcast: {msg.decode('utf-8')}")
        print(f"Answers: {answers}")

        try:
            readable, _, _ = select.select([tcp_sock], [], [], 0)
            if tcp_sock in readable:
                conn, addr = tcp_sock.accept()
                thread = threading.Thread(target=handle_student, args=(conn, addr, expressions, answers))
                thread.start()
                student_threads.append(thread)
        except Exception as e:
            print(f"Error accepting connection: {e}")

        time.sleep(2)

    print("Broadcasting phase ended")
    broadcast_sock.close()
    tcp_sock.settimeout(5)
    try:
        while True:
            try:
                conn, addr = tcp_sock.accept()
                thread = threading.Thread(target=handle_student, args=(conn, addr, expressions, answers))
                thread.start()
                student_threads.append(thread)
            except socket.timeout:
                break
    finally:
        tcp_sock.close()

    for thread in student_threads:
        thread.join()

    print("Server closed")
