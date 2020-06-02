import socket
import struct
import datetime


class NTP:
    address = '0.ru.pool.ntp.org'
    port = 123
    time_shift = 2208988800

    def __init__(self):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def get_time(self):
        data = '\x1b' + 47 * '\0'
        self.client.sendto(data.encode('utf-8'), (self.address, self.port))

        data, _ = self.client.recvfrom(1024)
        assert data, 'Error: got no data from NTP server'
        unpacked = struct.unpack('!12I', data)
        ts = unpacked[10] + float(unpacked[11]) / 2 ** 32 - self.time_shift
        return ts


if __name__ == '__main__':
    ntp = NTP()
    print('Current time: {}'.format(datetime.datetime.fromtimestamp(ntp.get_time())))
