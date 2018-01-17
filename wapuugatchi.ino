#include <Wire.h>
#include <Bounce2.h>
#include <ESP8266WiFi.h>
#include <SFE_MicroOLED.h>

#include "Wapuu.h"
#include "SimpleTimer.h"

#define PIN_RESET 255
#define DC_JUMPER 0
#define PIN_A D5
#define PIN_B D6
#define PIN_C D7
#define PIN_SPEAKER D8

MicroOLED oled( PIN_RESET, DC_JUMPER );

String mac = WiFi.macAddress();

Bounce bounce_a = Bounce();
Bounce bounce_b = Bounce();
Bounce bounce_c = Bounce();

SimpleTimer timer;

uint8_t bmpuu [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA0, 0x80, 0x38, 0xB4, 0xBE, 0xDF, 0x47, 0x97, 0xDF, 0xDF,
  0xDD, 0xDF, 0xDF, 0xDF, 0xBF, 0xFF, 0xFE, 0xFC, 0xFA, 0xF6, 0xC6, 0x06, 0x06, 0x06, 0x02, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF0, 0xFC, 0xFD, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD, 0xFD, 0xFD,
  0xFD, 0xFE, 0xFE, 0xFE, 0xFD, 0xFD, 0xFB, 0x07, 0xF7, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0C, 0x1E, 0x3E, 0x79, 0xF7, 0xCF, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0x03, 0xFD, 0xFD,
  0xFB, 0x07, 0xFB, 0xFD, 0xFE, 0xFE, 0x7E, 0x7D, 0x3B, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x78, 0x78, 0xF0, 0xE0, 0xC0, 0x80, 0x80, 0x80, 0xC3, 0xC3,
  0x43, 0x60, 0x31, 0x19, 0x0D, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Wapuu wapuu;

void WapuuTick() {
  wapuu.tick();
  wapuu.report();
}

void setup() {
  Serial.begin( 74880 );
  Serial.println();
  Serial.println();
  Serial.println( "Mac: " + mac );
  Serial.println();

  oled.begin();
  oled.clear( ALL );
  oled.display();   
  delay( 1000 );
  oled.clear( PAGE );
  oled.drawBitmap( bmpuu );
  oled.display();

  pinMode( PIN_A, INPUT_PULLUP );
  bounce_a.attach( PIN_A );
  bounce_a.interval( 5 );

  pinMode( PIN_B, INPUT_PULLUP );
  bounce_b.attach( PIN_B );
  bounce_b.interval( 5 );

  pinMode( PIN_C, INPUT_PULLUP );
  bounce_c.attach( PIN_C );
  bounce_c.interval( 5 );

  timer.setInterval( 1000, WapuuTick );
}

void loop() {
  timer.run();

  bounce_a.update();
  bounce_b.update();
  bounce_c.update();

  if ( bounce_a.fell() ) {
    Serial.println( "Button A Pressed!" );
  }
  if ( bounce_b.fell() ) {
    Serial.println( "Button B Pressed!" );
  }
  if ( bounce_c.fell() ) {
    Serial.println( "Button C Pressed!" );
  }
}
