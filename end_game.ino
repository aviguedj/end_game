#define RLed 6
#define YLed 9
#define GLed 10
#define BLed 11

#define RBtn 12
#define YBtn 2
#define GBtn 4
#define BBtn 3

#define BZR 5

#define COUNTER 4


const int buttonPins[COUNTER] = { RBtn, YBtn, GBtn, BBtn };
const int ledPins[COUNTER] = { RLed, YLed, GLed, BLed };
const int tones[COUNTER] = { 1000, 1500, 2000, 2500 };

void setup(){
  pinMode( BZR , OUTPUT);
  randomSeed(analogRead(A1));

}

void loop(){

}
