// CONSTANTES.
// Pines para los distintos valores.
const byte PIN_LUZ = 2;
const byte PIN_TEMPERATURA = 3;
const byte PIN_PH = 4;
const byte PIN_HUMEDAD = 5;

// PREPARACION.
void setup() {
  // Preparar comunicacion serial.
  Serial.begin(9600);

  // Preparar valores de entrada.
  pinMode(PIN_LUZ, INPUT);
  pinMode(PIN_TEMPERATURA, INPUT);
  pinMode(PIN_PH, INPUT);
  pinMode(PIN_HUMEDAD, INPUT);
}

// PRINCIPAL.
void loop() {
  // Leer valores.
  const int luz = analogRead(PIN_LUZ);
  const int temperatura = analogRead(PIN_TEMPERATURA);
  const int ph = analogRead(PIN_PH);
  const int humedad = analogRead(PIN_HUMEDAD);

  // Guardar datos obtenidos en formato Json.
  String datosJson = "{";
  datosJson += "\"luz\": " + String(luz);
  datosJson += ", \"temperatura\": " + String(temperatura);
  datosJson += ", \"ph\": " + String(ph);
  datosJson += ", \"humedad\": " + String(humedad);
  datosJson += "}";

  // Desplegar en serial los datos obtenidos.
  Serial.println(datosJson);
  delay(1000);
}
