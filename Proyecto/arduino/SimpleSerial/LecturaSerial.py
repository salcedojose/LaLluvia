#!python2
import serial

# Obtencion de puerto.
puerto = serial.Serial('/dev/ttyACM0', 9600)

# Quedar en lectura.
while True:
    print puerto.readline()
