#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

// CONSTANTES
#define DHTPIN 2
#define DHTTYPE DHT11
// Pines para los distintos valores.
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
const int PIN_HUMEDAD = A0;
int pinLDR = 3;
int luz = 0;


// PREPARACION.
void setup() {
  // Preparar comunicacion serial.
  Serial.begin(9600);
  dht.begin();
  //BMP
   if (!bmp.begin()) 
   {
    Serial.println("BMP180 sensor not found");
    while (1) {}
   }
}

// PRINCIPAL.
void loop() {
  // Leer valores.
  //Lectura con LDR
  luz = analogRead(pinLDR);
  //Se realiza lectra tanto en DHT11 como en BMP180, por lo cual se realiza promedio de ambas lecturas grados Celsius
  float t = dht.readTemperature();
  float t_bmp = bmp.readTemperature();
  //Lectura con BMP180 en Pa
  float pressure = bmp.readPressure();
  /*Lectura con sensor de humedad en humedad relativa (%)*/
  int humedad = analogRead(PIN_HUMEDAD);

  // Guardar datos obtenidos en formato Json.
  String datosJson = "{";
  datosJson += "\"luz\": " + String(luz);
  datosJson += ", \"temperatura\": " + String((t+t_bmp)/2);
  datosJson += ", \"presion\": " + String(pressure);
  datosJson += ", \"humedad\": " + String(humedad);
  datosJson += "}";

  // Desplegar en serial los datos obtenidos.
  Serial.println(datosJson);
  delay(5000);
}
