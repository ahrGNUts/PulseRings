#include <Adafruit_NeoPixel.h>

#define SENSORPIN A0
#define INNER 5
#define OUTER 6

int beatSignal;
int innerThreshold = 250;
int outerThreshold = 500;
int clampedSignal;

Adafruit_NeoPixel ring24 = Adafruit_NeoPixel(24, OUTER, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel ring16 = Adafruit_NeoPixel(16, INNER, NEO_RGB + NEO_KHZ800);

// indexes for LED and color addressing
int outerLEDIdx, innerLEDIdx, outerColIdx, innerColIdx;

void setup() {
  pinMode(INNER, OUTPUT);
  pinMode(OUTER, OUTPUT);
  Serial.begin(9600);

  ring24.begin();
  ring16.begin();
  ring24.show();
  ring16.show();

}

void loop() {
  beatSignal = analogRead(SENSORPIN);

  Serial.println(beatSignal);

  if(beatSignal > threshold) {
    clampedSignal = clampValue(beatSignal, 500, 970, 0, 75);
    
    for(int i = 0; i < 24; i++) {
      ring24.setPixelColor(i, 0, clampedSignal, 0);
    }
    
  } else {
    for(int i = 0; i < 24; i++){
      ring24.setPixelColor(i, 0, 0, 0);
    }
  }
  ring24.show();

}

int clampValue(int value, int oldMin, int oldMax, int newMin, int newMax) {
  int oldRange = oldMax - oldMin;
  int newRange = newMax - newMin;

  return (((value - oldMin) * newRange) / oldRange) + newMin;
}

