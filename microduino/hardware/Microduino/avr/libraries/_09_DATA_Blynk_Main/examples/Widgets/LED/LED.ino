/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * Blynk using a LED widget on your phone!
 *
 * App dashboard setup:
 *   LED widget on V1
 *   LED widget on V2
 *
 *
 * WARNING :
 * For this example you'll need SimpleTimer library:
 *   https://github.com/jfturcot/SimpleTimer
 * Visit this page for more information:
 *   http://playground.arduino.cc/Code/SimpleTimer
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>
#include <SimpleTimer.h>

// Set ESP8266 Serial object
#define EspSerial Serial1

ESP8266 wifi(EspSerial);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

WidgetLED led1(V1);
WidgetLED led2(V2);

SimpleTimer timer;

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  // Set ESP8266 baud rate
  EspSerial.begin(115200);
  delay(10);

  Blynk.begin(auth, wifi, "Makermodule", "microduino");

  while (Blynk.connect() == false) {
    // Wait until connected
  }

  timer.setInterval(1000L, blinkLedWidget);
  timer.setInterval(200L, fadeLedWidget);
}

void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    BLYNK_LOG("LED1: off");
  } else {
    led1.on();
    BLYNK_LOG("LED1: on");
  }
}

void fadeLedWidget()
{
  static int value = 0;
  static int delta = 20;
  value += delta;
  if (value > 255 || value < 0) {
    delta = -delta;
  } else {
    BLYNK_LOG("LED2: %d", value);
    led2.setValue(value);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
