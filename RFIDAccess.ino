/*

   All the resources for this project: https://www.hackster.io/Aritro
   Modified by Aritro Mukherjee


*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


////PIR Sensor/////

int PIRPin = 2;               // choose the input pin (for PIR sensor)
int PIRPin2 = 3;               // choose the input pin (for PIR sensor)
int PIRPin3 = 4;               // choose the input pin (for PIR sensor)

int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int val2 = 0;
int val3 = 0;                    // variable for reading the pin status
boolean Armed = false;

const int sensor = 7;
int state;
const int buzzer = 8;

#define led1 5
#define led2 6
#define led3 13

////////////////////

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(PIRPin, INPUT);     // declare sensor as input
  pinMode(PIRPin2, INPUT);     // declare sensor as input
  pinMode(PIRPin3, INPUT);     // declare sensor as input
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(sensor, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
  while (digitalRead(sensor) == HIGH) {
    noTone(buzzer);
    val = digitalRead(PIRPin);  // read input value
    val2 = digitalRead(PIRPin2);  // read input value
    val3 = digitalRead(PIRPin3);  // read input value
    if (val == HIGH) {
      Serial.print("1");
      tone(buzzer, 4000);
      delay(100);
      tone(buzzer, 5000);
      delay(100);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    if (val2 == HIGH) {
      Serial.print("2");
      tone(buzzer, 4000);
      delay(100);
      tone(buzzer, 5000);
      delay(100);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led3, LOW);
    }
    if (val3 == HIGH) {
      Serial.print("3");
      tone(buzzer, 4000);
      delay(100);
      tone(buzzer, 5000);
      delay(100);
      digitalWrite(led3, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
    if (val == LOW && val2 == LOW && val3 == LOW) {
      noTone(buzzer);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
  }
  if (digitalRead(sensor) == LOW) {
    noTone(buzzer);
    if (!Armed) {
      UnArmed();
    }
    else if (Armed) {
      noTone(buzzer);
      Alarm();
    }
  }
}


void UnArmed() {

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "80 2F 8F 4D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
    Armed = true;

  }

  else
  {
    Serial.println("Error");
    delay(3000);
  }

}

void Alarm() {
  noTone(buzzer);
  val = digitalRead(PIRPin);  // read input value
  val2 = digitalRead(PIRPin2);  // read input value
  val3 = digitalRead(PIRPin3);  // read input value
  if (val == HIGH) {
    Serial.println("Motion Detected1");
    delay(100);
    tone(buzzer, 4000);
    delay(100);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if (val2 == HIGH) {
    Serial.println("Motion Detected2");
    delay(100);
    tone(buzzer, 4000);
    delay(100);
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
  }
  if (val3 == HIGH) {
    Serial.println("Motion Detected3");
    delay(100);
    tone(buzzer, 4000);
    delay(100);
    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  if (val == LOW && val2 == LOW && val3 == LOW) {
    noTone(buzzer);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  else {
    disarm();
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  else {
    disarm();
  }
}


void disarm() {
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "80 2F 8F 4D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
    Armed = false;

  }

  else
  {
    Serial.println("Error");
    delay(3000);
  }
}

