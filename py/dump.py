import serial
import string
from time import sleep, localtime, strftime

ROOT_DIR = ".."
DUMPS_DIR = "dumps"

MODULE = 1
PROM = 1

def get_data(addr, ser):
    higher = chr((addr & 0xFF00) >> 8)
    lower = chr(addr & 0x00FF)
    ser.write(higher)
    ser.write(lower)
    data = ser.read()

    return ord(data)


def dump_rom():
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout = 2)
    ser.flushInput()
    ser.flushOutput()

    filename = '%s/%s/module_%s_prom_%s_%s' % (ROOT_DIR, DUMPS_DIR, MODULE, PROM, strftime("%Y%m%d_%H%M%S", localtime()))
    fhex = open('%s.hex' % filename, 'wb')

    for addr in xrange(0, 0x3fff + 1):
        data = get_data(addr, ser)
        fhex.write(chr(data))

    ser.close()
    fhex.close()


if __name__ == '__main__':
    dump_rom()

