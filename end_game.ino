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

#define MAX_NUM_OF_LIGHTS 3

int ChosenIndexes[MAX_NUM_OF_LIGHTS];
int PressedIndexes[MAX_NUM_OF_LIGHTS];

int NumOfPressedIndexes = 0;
bool gameWon = false;
unsigned long lastDebounceTime[NUM_OF_LEDS] = {0};
unsigned long debounceDelay = 150;
unsigned long startTime = 0;
const unsigned long TIME_LIMIT = 1000;
bool waitingForNewGame = false;

void setup(){
  Serial.begin(9600);
  pinMode( BZR , OUTPUT);
  randomSeed(analogRead(A1));
  
 LastPressTime=millis();
for (int i = 0; i < COUNTER ; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

}

void loop(){


}

void waitToStart(){
  CurrBtn=digitalRead(buttonPins);
    if((CurrBtn == HIGH) && (LastBtn == LOW)&&(millis() - LastPressTime > 50)){
      LastPressTime=millis();
    }
    LastBtn=CurrBtn;
  }


void sound(){
  digitalWrite(BZR,HIGH);
  delay(500);
  digitalWrite(BZR,LOW);
}

void startGame(){
for (int i = 0; i < COUNTER ; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  sound();

}
void ChooseRandomLights() {
    for (int i = 0; i < MAX_NUM_OF_LIGHTS; i++) {
        ChosenIndexes[i] = random(0, NUM_OF_LEDS);
    }
}
void ShowLights() {

    for (int i = 0; i < MAX_NUM_OF_LIGHTS; i++) {
        digitalWrite(Leds[ChosenIndexes[i]], HIGH);
    }
    delay(500); 
    for (int i = 0; i < MAX_NUM_OF_LIGHTS; i++) {
        digitalWrite(Leds[ChosenIndexes[i]], LOW);
    }
    
    delay(500); 
    tone(BZR, 500, 500); 
    startTime = millis(); 
}