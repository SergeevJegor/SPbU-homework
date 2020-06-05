import socket
import struct
import datetime
import time


class NTP:
    address = '0.ru.pool.ntp.org'
    port = 123
    time_shift = 2208988800

    def __init__(self):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def get_time(self):
        data = '\x1b' + 47 * '\0'

        t0 = time.time()
        self.client.sendto(data.encode('utf-8'), (self.address, self.port))
        t3 = time.time()

        data, _ = self.client.recvfrom(1024)
        assert data, 'Error: got no data from NTP server'

        unpacked = struct.unpack('!12I', data)
        t1 = unpacked[8] + float(unpacked[9]) / 2 ** 32 - self.time_shift
        t2 = unpacked[10] + float(unpacked[11]) / 2 ** 32 - self.time_shift

        ts = time.time() + (((t1 - t0) + (t2 - t3)) / 2)
        return ts


if __name__ == '__main__':
    ntp = NTP()
    print('Current time: {}'.format(datetime.datetime.fromtimestamp(ntp.get_time())))
