import socket
from threading import Thread


def spawn_client_thread(client_socket):
    thread = Thread(target=echo_function, args=[client_socket])
    thread.start()


def echo_function(client_socket):
    while True:
        chunk = client_socket.recv(1024)
        if chunk == b"":
            raise Exception("Connection is broken")
        else:
            client_socket.send(chunk)
            print(repr(chunk), '\n', {client_socket})


if __name__ == '__main__':
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', 8080))
    server_socket.listen(100500)

    while True:
        client, _ = server_socket.accept()
        spawn_client_thread(client)
