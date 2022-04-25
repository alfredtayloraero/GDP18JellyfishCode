#include <FastLED.h>

#define NUM_LEDS 5 //number of LEDs
#define LED_PIN 10 // LED Pin

#define DELAY 20
CRGB leds[NUM_LEDS];
int cycle=0;
int cycle2=0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);
  int s=0;
  while (s<DELAY-10){
    leds[s%5]=CRGB(64,64,64);
    leds[(s-1)%5]=CRGB(32,32,32);
    leds[(s-2)%5]=CRGB(4,4,4);
    leds[(s+1)%5]=CRGB(0,0,0);
    leds[(s+2)%5]=CRGB(0,0,0);
    FastLED.show();
    delay(900);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    s++;
  }
    while (s<DELAY){
    leds[s%5]=CRGB(64,0,0);
    leds[(s-1)%5]=CRGB(32,0,0);
    leds[(s-2)%5]=CRGB(4,0,0);
    leds[(s+1)%5]=CRGB(0,0,0);
    leds[(s+2)%5]=CRGB(0,0,0);
    FastLED.show();
    delay(900);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    s++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(cycle);
  switch(cycle%3){
    case 0:
      fill_solid(leds, 5,CRGB(10,10,64));
      break;
    case 1:
      fill_solid(leds, 5,CRGB(32,6,54));
      break;
    case 2:
      fill_solid(leds, 5,CRGB(6,32,54));
      break;
  }
  FastLED.show();
  delay(1000);
  switch(cycle%3){
    case 0:
      fill_solid(leds, 5,CRGB(21,8,59));
      break;
    case 1:
      fill_solid(leds, 5,CRGB(19,19,59));
      break;
    case 2:
      fill_solid(leds, 5,CRGB(8,21,59));
      break;
  }
  FastLED.show();
  delay(1000);
  cycle++;
  FastLED.clear();
}
