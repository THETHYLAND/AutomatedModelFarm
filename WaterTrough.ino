#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"wtred", "wtsed"};
char charBuf[50];
int sensorread;
#define sensor A0
#define led 2
#include <printf.h>

void setup() {
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.openWritingPipe(addresses[1]); //00005
  radio.openReadingPipe(1, addresses[0]); //00004
  radio.setPALevel(RF24_PA_MAX);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  radio.printDetails();
}

void loop() {
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  while (!radio.available());
  Serial.println("Ok");
  sensorread = analogRead(sensor);
  if (sensorread == 0) {
    Serial.println("Filling");
    String message = "Filling";
    digitalWrite(led, HIGH);
    message.toCharArray(charBuf, 50);
    radio.stopListening();
    radio.openWritingPipe(addresses[1]);
    radio.write(&charBuf, sizeof(charBuf));
  }
  else if (sensorread > 0) {
    Serial.println("Full");
    String message = "Full";
    digitalWrite(led, LOW);
    message.toCharArray(charBuf, 50);
    radio.stopListening();
    radio.openWritingPipe(addresses[1]);
    radio.write(&charBuf, sizeof(charBuf));
  }
  delay(2000);
}
