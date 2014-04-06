import serial
from time import sleep, localtime, strftime

ROOT_DIR = ".."
DUMPS_DIR = "dumps"

MODULE = 1
PROM = 2

def get_data(addr, ser):
    higher = chr((addr & 0xFF00) >> 8)
    lower = chr(addr & 0x00FF)
    ser.write(higher)
    ser.write(lower)
    data = ser.read()

    return ord(data)


ser = serial.Serial('/dev/ttyACM0', 115200, timeout = 2)
ser.flushInput()
ser.flushOutput()

f = open('%s/%s/module_%s_prom_%s_%s.txt' % (ROOT_DIR, DUMPS_DIR, MODULE, PROM, strftime("%Y%m%d_%H%M%S", localtime())), 'w')

for addr in xrange(0, 0x3fff + 1):
    data = get_data(addr, ser)
    f.write("A: 0x%s, D: 0x%s, D: %s\n" % (format(addr, '04x'), format(data, '02x'), data))

ser.close()
f.close()




