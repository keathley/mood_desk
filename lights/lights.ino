#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define BAUD 9600

#define COMMAND_NONE 0
#define COMMAND_BIAS 49
#define COMMAND_AMBIANCE 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int command;

const uint32_t BIAS_WHITE = strip.Color(250, 250, 250);

void setup() {  
  // Start Serial connection
  Serial.begin(BAUD);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  command = COMMAND_NONE;
}

void loop() {  
  if ( Serial.available() )
    command = Serial.read();
  
  switch ( command ) {
    case COMMAND_BIAS:
      colorWipe(BIAS_WHITE, 50);
      break;
    case COMMAND_AMBIANCE:
    case COMMAND_NONE:
    default:
      rainbow(20);
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

//void bias(uint8_t wait) {
//  uint_t i, j;
//  
//  for (i = 0; i < strip.numPixels(); i++) {
//    strip.setPixelColor(i, 
//  }
//}

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

