#include <Adafruit_NeoPixel.h>

/**************************************************************
 * Modified Version of Strandtest for Binary Kitchen Doorsign *
 *                                                            *
 * Christian Richter 2015                                     *
 * Requires Adafruit Neopixel Library                         *
 * For Arduino Nano                                           *
 **************************************************************/

// pin of ws2812 strip
#define PIN 11
// pin of doorsignal
#define DOORPIN 12
// number of LEDS in Strip
#define NUMLEDS 29

// initialize Neopixel Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(DOORPIN, INPUT_PULLUP);
}

void loop() {
  // read doorpin
  uint8_t dp = digitalRead(DOORPIN);
  // if doorpin is high => door is open
  if(dp == HIGH) {
    // cycle through rgb rainbow
    rainbow(20);
  } else { // door is closed
    // switch each led of
    colorWipe(strip.Color(0, 0, 0), 50);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

