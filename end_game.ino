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

#define DEBOUNCE_DELAY 50

const int buttonPins[COUNTER] = { RBtn, YBtn, GBtn, BBtn };
const int ledPins[COUNTER] = { RLed, YLed, GLed, BLed };
const int tones[COUNTER] = { 1000, 1500, 2000, 2500 };

void setup(){
  pinMode( BZR , OUTPUT);
  randomSeed(analogRead(A1));
  

}

void loop(){
static unsigned long lastPressTimes[COUNTER] = {0};
  static unsigned long pressDurations[COUNTER] = {0};

  for (int i = 0; i < COUNTER; i++) {
    if (checkButtonPress(buttonPins[i], lastPressTimes[i], pressDurations[i])) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }


}





bool checkButtonPress(int buttonPin, unsigned long &lastPressTime, unsigned long &pressDuration) {
    static bool lastButtonState = LOW;
    bool buttonState = digitalRead(buttonPin);

    unsigned long currentTime = millis();
    if (buttonState != lastButtonState) {
        lastPressTime = currentTime;
    }
    if (buttonState == HIGH && (currentTime - lastPressTime) > DEBOUNCE_DELAY) {
        pressDuration = currentTime - lastPressTime;
        lastPressTime = currentTime;
        lastButtonState = buttonState; 
        return true;
    } else if (buttonState == LOW) {
        pressDuration = 0;
        lastButtonState = buttonState; 
    }
    return false;
}

