//Written by Alfred Taylor, 2022 for GDP 18: Robotic Jellyfish Swimmers


#include <Servo.h>
#include <FastLED.h>

//Frequency of oscillations is speed2*5/(3*angle range)
#define SPEED2 102 //Speed going down (2*speed1)
#define CRATIO 0.33 //Ratio between downstroke speed and upstroke speed
#define MAXSPEED 108 //maximum testing speed2 before resetting (2.5Hz)
#define MAXANGLE 150 //Maximum angle of the servo
#define MINANGLE 15 //Minimum angle of the servo
#define DELAY 120 //Delay before starting the routine
#define DELAY2 15 //Delay between frequencies
//#define SECONDS 30 //Time it aims for at each frequency (Ends up slightly below this at high frequency)
#define SMOOTHNESS 2//Angle increment per function call

#define NUM_LEDS 5 //number of LEDs
#define LED_PIN 10 // LED Pin
CRGB leds [NUM_LEDS];

Servo servo;
int angle=MINANGLE+20; //Sets starting angle so Jelly can be assembled
int speed2=SPEED2;//Sets initial speeds
int speed1=(int)SPEED2*CRATIO;
int cycle=0; //Cycle is used to keep track of the number of cycles
int cycle2=0;
int smoothdelay=200*SMOOTHNESS;

void setup() {
  servo.attach(9);
  servo.write(angle);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(LED_BUILTIN, OUTPUT);
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
  
  
  while (angle<MAXANGLE){
    angle++;
    servo.write(angle);
    delay(30);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //int limit = SECONDS*5*(1-CRATIO)*speed2/(MAXANGLE-MINANGLE);  
  cycle2=cycle%3;

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
  
  while(angle<MAXANGLE){
    angle+=2; //Changed degree increments to 2deg to decrease overhead from other instructions
    servo.write(angle);
    delay(smoothdelay/speed1);
  }
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
  
  while(angle>MINANGLE){ //Servo decreases its target angle by 2 degrees every 600ms/speed2
    angle-=2;
    servo.write(angle); //This PWM command 
    delay(smoothdelay/speed2);
  }
  
  cycle++;

  if (false){   //Once the number of cycles passes the number required for a 30s run
    //Opens bell before changing frequency
    while(angle<MAXANGLE){
      //angle+=2; //Changed degree increments to 2deg to decrease overhead from other instructions
      //servo.write(angle);
    delay(smoothdelay/speed1);}
    
    speed2+=18;   //Speed2 is incremented by 18 which increases the frequencies by .25Hz
    speed1=speed2/2; //Speed1 is set 
    //cycle=0; //Cycle is reset
    int s=0;
    while (s<DELAY2){ //Flashes while changing frequencies and waiting for DELAY2 seconds
      delay(900);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      s++;
    }
    if (speed2>MAXSPEED+1){ //If speed2 is greater than the maximum speed the test resets to the minimum speed
      speed2=SPEED2;
      speed1=(int)SPEED2*CRATIO;
    }
  }
  /*
  servo.write(0);
  delay(500);
  servo.write(180);
  delay(500);
  */
}
