#include <Adafruit_NeoPixel.h>

/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
char data = 0;            //Variable for storing received data

# define PIN 6

# define NUMPIXELS 3
#define  LED 2
#define  LED 5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);



void setup()
{
  Serial.begin(9600);   //Sets the baud for serial data transmission
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pixels.begin();
  pixels.show();
}
void loop()
{


  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data
    Serial.print(data);          //Print Value inside data in Serial monitor
    Serial.print("\n");

    if (data == '1')
    {
      //  pixels.setPixelColor(1,pixels.Color(255,255,255));
      //  pixels.setPixelColor(0,pixels.Color(0,0,0));
      //  pixels.show();
      pixels.setPixelColor(0, 0, 0, 0, 255);
      pixels.show();
    }
    if (data == '0')
    {
      // pixels.setPixelColor(1,pixels.Color(0,0,0));
      // pixels.show();
      pixels.setPixelColor(0, 0, 0, 0, 0);
      pixels.show();
    }
    if (data == '3')
    { // Checks whether value of data is equal to 1
      pixels.setPixelColor(1, 0, 0, 0, 255);
      pixels.show();

    }
    if (data == '2')
    { //  Checks whether value of data is equal to 0
      pixels.setPixelColor(1, 0, 0, 0, 0);
      pixels.show();
    }

    if (data == '5')
    {
     pixels.setPixelColor(2, 0, 0, 0, 255);
      pixels.show();
    }
    if (data == '4')
    {
      pixels.setPixelColor(2, 0, 0, 0, 0);
      pixels.show();
    }
  }

}
