#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

// CONSTANTES
#define DHTPIN 2
#define DHTTYPE DHT11
#define z 800
#define x 90000
#define y2 15
#define y 35
#define y1 10
#define z1 400
#define z2 300
// Pines para los distintos valores.
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
const int PIN_HUMEDAD = A0;
int pinLDR = 3;
int pinRelay = 4;
int luz = 0;
String regar;

// PREPARACION.
void setup() {
  // Preparar comunicacion serial.
  Serial.begin(9600);
  dht.begin();
  //BMP
   if (!bmp.begin()) 
   {
    //Serial.println("BMP180 sensor not found");
    while (1) {}
   }
  pinMode(pinRelay, OUTPUT);
}

// PRINCIPAL.
void loop() {
  // Leer valores.
  //Lectura con LDR
  luz = analogRead(pinLDR);
  //Se realiza lectra tanto en DHT11 como en BMP180, por lo cual se realiza promedio de ambas lecturas grados Celsius
  float t = dht.readTemperature() + 2;
  float t_bmp = bmp.readTemperature();
  //Lectura con BMP180 en Pa
  float pressure = bmp.readPressure();
  /*Lectura con sensor de humedad en humedad relativa (%)*/
  int humedad = analogRead(PIN_HUMEDAD);
  float t_prom = (t+t_bmp)/2;
  regar = deberegar(luz, t_prom, pressure, humedad);
  
  // Guardar datos obtenidos en formato Json.
  String datosJson = "{";
  datosJson += "\"luz\": " + toString(luz);
  datosJson += ", \"temperatura\": " + FtoString(t_prom,2) ;
  datosJson += ", \"presion\": " + FtoString(pressure,2);
  datosJson += ", \"humedad\": " + toString(humedad);
  datosJson += ", \"regando\": " + regar;
  datosJson += "}";

  // Desplegar en serial los datos obtenidos.
  Serial.println(datosJson);
  delay(2000);
};

      String FtoString (float n, int decimals) {
      int d = int(log10(n));
      //Serial.println(d);
      //Serial.println(n);
      String res = "";
      int a;
      for (int i = d; i >= 0 - decimals; i--) {
        a = int(n / pow(10, i));
                n -= a * pow(10, i);
        if (i == -1) {
        res += ".";
      }
      res += char(48 + a);
      //Serial.println(res);
    }
    return res;
  }

  String toString(int n) {
      int d = int(log10(n));
      String res = "";
      int a;
      for (int i = d; i >= 0; i--) {
        a = int(n / pow(10, i));
                n -= a * pow(10, i);
                res += char(48 + a);
      }
      return res;
    }

   String deberegar(int L, float T, float P, float H){
      //cuando llueve no regar
      if (P < x && T < y2)
        {
          digitalWrite(pinRelay, LOW);
          return "0";
        }
      if (T < y &&  T > y1 && L < z && H > z1)
      {
       digitalWrite(pinRelay, HIGH);
        return "1";
      }
      if (H < z2)
      {
        digitalWrite(pinRelay, LOW);
        return "0";
      }
      digitalWrite(pinRelay, LOW);
      return "0";
    }
