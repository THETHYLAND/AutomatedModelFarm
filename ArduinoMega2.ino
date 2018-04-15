#include <core_build_options.h>
#include <secTimer.h>

#include <TimeLib.h>
#include <Time.h>

#include <SPI.h>

#include <nRF24L01.h>

#include <RF24.h>

char charBuf[50] = "";

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {
  "ghred","ghsed","hayrd","haysd","wtred","wtsed"};

char hayans[50] = "";
char greenans[50] = "";
char waterans[50] = "";

int count = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);

}

void loop() {

  String sends = "ok";
  sends.toCharArray(charBuf, 50);
  delay(100);

  if(count<5){
    startup();
  }

  Serial.flush();
  String final = "";

  radio.stopListening();
  radio.openWritingPipe(addresses[0]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
  while (!radio.available());
  radio.read(&greenans, sizeof(greenans));
  final=final+String(greenans)+",";
  delay(2000);

  radio.stopListening();
  radio.openWritingPipe(addresses[2]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[3]);
  radio.startListening();
  while (!radio.available()){
  };
  radio.read(&hayans, sizeof(hayans));
  final=final+String(hayans)+",";
  delay(2000);

  radio.stopListening();
  radio.openWritingPipe(addresses[4]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[5]);
  radio.startListening();
  while (!radio.available());
  radio.read(&waterans, sizeof(waterans));
  final=final+String(waterans);
  delay(2000);
  Serial.println(final);

}

void startup(){
  String final1 = "";
  radio.stopListening();
  radio.openWritingPipe(addresses[0]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
  while (!radio.available());
  radio.read(&greenans, sizeof(greenans));
  final1=final1+String(greenans)+",";
  delay(2000);

  radio.stopListening();
  radio.openWritingPipe(addresses[2]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[3]);
  radio.startListening();
  while (!radio.available()){
  };
  radio.read(&hayans, sizeof(hayans));
  final1=final1+String(hayans)+",";
  delay(2000);

  radio.stopListening();
  radio.openWritingPipe(addresses[4]);
  radio.write(&charBuf, sizeof(charBuf));
  radio.openReadingPipe(1, addresses[5]);
  radio.startListening();
  while (!radio.available());
  radio.read(&waterans, sizeof(waterans));
  final1=final1+String(waterans);
  delay(2000);
}





