#!/usr/bin/python

# LIBRERIAS.
import serial
import MySQLdb

# CONSTANTES.
# Parametros para conexion con Arduino.
DISPOSITIVO = "/dev/ttyACM0"  # Nombre de dispositivo a utilizar.
BAUDIOS = 9600  # Baudios a los cuales leer el puerto de Arduino.

# Parametros para base de datos.
SERVIDOR = "localhost"
USUARIO = "UsuarioRiego"
FRASE = "UsuarioRiego"
BASE_DATOS = "sistema_riego"
TABLA_DATOS = "dato"

# Conexion a base de datos.
con = MySQLdb.connect(SERVIDOR, USUARIO, FRASE, BASE_DATOS)

# Crear cursor? a base de datos.
cursor = con.cursor()

# Conectar con Arduino y leer indefinidamente.
while True:
    try:
        print("Conectando a " + DISPOSITIVO)
        arduino = serial.Serial(DISPOSITIVO, BAUDIOS)

        # Leer valor proveniente de arduino.
        datos = arduino.readline()
        print(datos)
    except:
        print("Falla de conexion a " + DISPOSITIVO)
