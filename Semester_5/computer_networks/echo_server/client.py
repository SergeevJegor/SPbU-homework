import socket
import time


if __name__ == '__main__':
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket:
        socket.connect(('142.93.128.77', 7354))
        i = 1

        while True:
            socket.send(b"Hey there!")
            data = socket.recv(1024)
            print(f"{i}. {repr(data)}")
            i += 1

            time.sleep(2)
