const int gasPin = 6; //GAS sensor output pin to Arduino analog A0 pin
double output_value;

const int buzzer = 4;
String message = "";

const int electric = 9;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"hayrd", "haysd"};
char charBuf[50];


void setup() {
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  pinMode(gasPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(electric, INPUT_PULLUP);
  Serial.println("Starting");
  delay(10000);
  radio.openWritingPipe(addresses[1]); //00003
  radio.openReadingPipe(1, addresses[0]); //00002
  radio.printDetails();
}

void loop() {
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  while (!radio.available());
  output_value = digitalRead(gasPin);
  Serial.println(output_value);
  if (digitalRead(electric) == HIGH) {
    message = "Broken,";
  }
  else {
    message = "Working,";
  }
  if (output_value == 0) {
    message = message + "FIRE";
    tone(buzzer, 5000);
  }
  else {
    message = message + "Clear";
    noTone(buzzer);
  }

  message.toCharArray(charBuf, 50);
  radio.stopListening();
  radio.openWritingPipe(addresses[1]); //00003
  radio.write(&charBuf, sizeof(charBuf));
  Serial.println(charBuf);
  delay(1000);
}
