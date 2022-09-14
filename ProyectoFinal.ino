/*Equipo 6
 * Alan Pérez Fernández    A01640489 
 * Jorge Guillen Berrueta  A01639681
 * Davide Dunne Sanchez    A01642355
 */

//Librerias para Wi-Fi y Firebase
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Credenciales wifi
/* 1. Define the WiFi credentials */
#define ssid "DavideHotspot"
#define password "Master24Reference"

/* 2. Define the API Key */
#define API_KEY "AIzaSyCFcJh4SKTTkDrPGCEOvsIW1BOYZGULDvc"

/* 3. Credenciales Proyecto Firebase */
const char *FIREBASE_HOST="https://tc1001s-45f4f-default-rtdb.firebaseio.com/"; 
const char *FIREBASE_AUTH="UdnaymkGUQWPk9gyIBXBNjTuwisXtM7S1WqAkKKk";

// Firebase Data object in the global scope
FirebaseData firebaseData;

//Definimos Variables---------------------------------------------------------------------------

//Variables para foto resistor-------------------------------------------------&
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
//Variables para Ultrasonico
int trigPin = 2;
int echoPin = 0;
float duration;
float distance;
//Variables para Temperatura----------------------------------------------------&
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

const int DHTPin = 5;     // what digital pin we're connected to

DHT dht(DHTPin, DHTTYPE);


//Inicia SetUp-------------------------------------------------------------------------------------
void setup() {
  
  //Wi-Fi y Firebase

  Serial.begin(115200);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }
  Serial.print("\nConectado al Wi-Fi");
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Firebase.reconnectWiFi(true);
  
  //Foto resistor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  //Ultra sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  
  //Temperatura sensor
   Serial.begin(9600);
   Serial.println("DHTxx test!");

   dht.begin();

}
//Inicia loop--------------------------------------------------------------------------------------
void loop() {
  //Foto Resistor----------------------------------------------------------------&
  // Leemos el valor del sensor
  sensorValue = analogRead(sensorPin);
  // Encendemos el 'ledPin'
  digitalWrite(ledPin, HIGH);
  // Hacemos un delay en <sensorValue>
  delay(sensorValue);
  // Apagamos el 'ledPin'
  digitalWrite(ledPin, LOW);
  // Hacemos un delay en <sensorValue>
  delay(sensorValue);
  //Imprimimos el Serial Value, para poderlo revisar desde el 'serial monitor'
  Serial.print(sensorValue);

  //Codigo Ultra sensor----------------------------------------------------------&

  // Limpiamos 'trigPin'
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Ponemos 'trigPin' en alto por 10 micro segundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leemos lo que tarda en regresar la onda en microsegundos
  duration = pulseIn(echoPin, HIGH);
  Serial.print("echoPin: ");
  Serial.print(echoPin);
  // Calculamos la distancia
  distance= duration*0.034/2.0;
  // Imprimimos la distancia en el  'Serial Monitor'
  Serial.print(" ,Distance: ");
  Serial.println(distance);
  delay(200);

  //Codigo Temperatura-----------------------------------------------------------&

  // Wait a few seconds between measurements.
   delay(2000);

   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;

}
