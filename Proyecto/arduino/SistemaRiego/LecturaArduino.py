#!/usr/bin/python

# LIBRERIAS.
import serial
import MySQLdb
import json


# CLASES.
class ValorArduino(object):
    def __init__(self, luz, temperatura, ph, humedad, regando):
        self.luz = float(luz)
        self.temperatura = float(temperatura)
        self.ph = float(ph)
        self.humedad = float(humedad)
        self.regando = int(regando)


# CONSTANTES.
# Parametros para conexion con Arduino.
DISPOSITIVO = "/dev/ttyACM0"  # Nombre de dispositivo a utilizar.
BAUDIOS = 9600  # Baudios a los cuales leer el puerto de Arduino.

# Parametros para base de datos.
SERVIDOR = "localhost"
USUARIO = "UsuarioRiego"
FRASE = "UsuarioRiego"
BASE_DATOS = "sistema_riego"
# Nombre de procedimiento para actualizar valores obtenido de Arduino.
ACTUALIZAR_VALORES = "ActualizarValores"


# FUNCIONES.
def ActualizarValores(valorArduino):
    "Actualizar valores leidos de arduino a base de datos."
    # Guardar parametros a actualizar.
    lecturas = (valorArduino.luz, valorArduino.temperatura,
                valorArduino.ph, valorArduino.humedad, valorArduino.regando)

    try:
        # Preparar conexion a base de datos.
        con = MySQLdb.connect(SERVIDOR, USUARIO, FRASE, BASE_DATOS)
        cursor = con.cursor()

        # Actualizar valores.
        cursor.callproc(ACTUALIZAR_VALORES, lecturas)
        con.commit()
    except:
        print("Fallo de conexion a " + BASE_DATOS)
    finally:
        # Cerrar conexiones a almacenamiento.
        cursor.close()
        con.close()


# PRINCIPAL.
# Conectar con Arduino y leer indefinidamente.
# Obtener datos de arduino y convertir a formato usable.
repetir = True
while repetir:
    try:
        print("Conectando a " + DISPOSITIVO)
        arduino = serial.Serial(DISPOSITIVO, BAUDIOS)

        # Leer y desplegar valor proveniente de arduino.
        datosJson = arduino.readline()
        print(datosJson)

        # Guardar y convertir datos a formato apropiado.
        datos = lambda: None
        datos.__dict__ = json.loads(datosJson)
        valorArduino = ValorArduino(datos.luz, datos.temperatura,
                                    datos.presion, datos.humedad, datos.regando)

        # Guardar datos obtenidos en almacenamiento.
        ActualizarValores(valorArduino)
    except:
        print("Falla de conexion a " + DISPOSITIVO)
        repetir = False
