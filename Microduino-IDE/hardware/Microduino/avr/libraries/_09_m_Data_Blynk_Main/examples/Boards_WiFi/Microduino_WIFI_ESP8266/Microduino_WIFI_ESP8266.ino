/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how to use ESP8266 Shield (with AT commands)
  to connect your project to Blynk.

  WARNING!
    It's rather tricky to get it working, please read this article:
    https://github.com/blynkkk/blynk-library/wiki/ESP8266-with-AT-firmware

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

/**
**CoreUSB UART Port: [Serial1] [D0,D1]
**Core+ UART Port: [Serial1] [D2,D3]
**/
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define ESP8266_BAUD  115200
#endif

/**
**Core UART Port: [SoftSerial] [D2,D3]
**/
#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); /* RX:D2, TX:D3 */
#define ESP8266_BAUD  9600
#endif

ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
}

void loop()
{
  Blynk.run();
}

