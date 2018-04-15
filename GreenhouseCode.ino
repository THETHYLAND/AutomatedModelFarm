#include <dht.h>
dht DHT;
// Soil moisture sensor variables
#define soilsensor 2
int soilval;
//Temp sensor
#define dht_apin 9 // Analog Pin sensor is connected to
double tempval;

#define led 10

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"ghred", "ghsed"};
char charBuf[50];
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]); //00005
  radio.openReadingPipe(1, addresses[0]); //00004
  radio.setPALevel(RF24_PA_MAX);
  pinMode(soilval, INPUT);
  pinMode(dht_apin, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}
void loop() {
  String soilread = "";
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  while (!radio.available());
  soilval = digitalRead(soilsensor);
  if (soilval == 1) {
    soilread = "Dry";
    digitalWrite(led, HIGH);
  }
  else if (soilval == 0) {
    soilread = "Watered";
    digitalWrite(led, LOW);
  }
  //soilval = map(soilval, 550, 0, 0, 100);
  int test = DHT.read11(dht_apin);
  String temps = String(DHT.temperature);
  String message = "";
  message = String(soilread) + "," + temps;
  message.toCharArray(charBuf, 50);
  Serial.println(message);
  radio.stopListening();
  radio.write(&charBuf, sizeof(charBuf));
  delay(1000);
  Serial.print(soilread);
}
