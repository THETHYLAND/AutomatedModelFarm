//L293D
//Motor A
const int aright  = 9;  // Pin 14 of L293
const int aleft  = 10;  // Pin 10 of L293
const int bleft  = 4;  // Pin 14 of L293
const int bright  = 5;  // Pin 10 of L293


unsigned long previousMillis = 0;

const long interval = 15000;

unsigned long seconds = 0;

//This will run only one time.
void setup() {
  pinMode(aleft, OUTPUT);
  pinMode(aright, OUTPUT);
  pinMode(bleft, OUTPUT);
  pinMode(bright, OUTPUT);
  Serial.println("Starting");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(aleft, HIGH);
    digitalWrite(aright, LOW);
    digitalWrite(bleft, HIGH);
    digitalWrite(bright, LOW);
    delay(195);
    digitalWrite(aleft, LOW);
    digitalWrite(aright, LOW);
    digitalWrite(bleft, LOW);
    digitalWrite(bright, LOW);
    delay(2000);
    digitalWrite(aleft, LOW);
    digitalWrite(aright, HIGH);
    digitalWrite(bleft, LOW);
    digitalWrite(bright, HIGH);
    delay(195);
    digitalWrite(aleft, LOW);
    digitalWrite(aright, LOW);
    digitalWrite(bleft, LOW);
    digitalWrite(bright, LOW);
    delay(2000);
  }
}

