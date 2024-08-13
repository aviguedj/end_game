#define RLed 6
#define YLed 9
#define GLed 10
#define BLed 11

#define RBtn 12
#define YBtn 2
#define GBtn 4
#define BBtn 3

#define BZR 5
#define NUM_OF_LEDS 4
const int Leds[NUM_OF_LEDS] = {GLed, YLed, BLed, RLed};
const int Btns[NUM_OF_LEDS] = {GBtn, YBtn, BBtn, RBtn};
const int tones[NUM_OF_LEDS] = {1000, 1500, 2000, 2500};

#define MAX_NUM_OF_LIGHTS 3
int ChosenIndexes[MAX_NUM_OF_LIGHTS];
int PressedIndexes[MAX_NUM_OF_LIGHTS];

int NumOfPressedIndexes = 0;
unsigned long lastDebounceTime[NUM_OF_LEDS] = {0};
unsigned long debounceDelay = 50; // הקטנת זמן דילוג כדי להגביר רגישות
unsigned long startTime = 0;
const unsigned long TIME_LIMIT = 1000;

#define  WAITING_FOR_NEW_GAME 51
#define  SHOWING_LIGHTS  52
#define  WAITING_FOR_INPUT 53
#define  CHECKING_RESULT  54
#define  GAME_WON  55
#define  GAME_LOST  56

int currentState = WAITING_FOR_NEW_GAME;

void setup() {
    pinMode(BZR, OUTPUT);
    initializeLedsAndButtons();
    randomSeed(analogRead(A1));
}

void loop() {
    unsigned long currentTime = millis();
    
    switch (currentState) {
        case WAITING_FOR_NEW_GAME:
            handleNewGameRequest();
            break;

        case SHOWING_LIGHTS:
            ShowLights();
            currentState = WAITING_FOR_INPUT;
            break;

        case WAITING_FOR_INPUT:
            handleGamePlay(currentTime);
            break;

        case CHECKING_RESULT:
            checkGameResult();
            break;

        case GAME_WON:
            handleWinState();
            break;

        case GAME_LOST:
            handleLoseState();
            break;
    }
}

void initializeLedsAndButtons() {
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        pinMode(Leds[i], OUTPUT);
        pinMode(Btns[i], INPUT_PULLUP);
    }
}

void startNewGame() {
    ChooseRandomLights();
    currentState = SHOWING_LIGHTS;
}

void handleNewGameRequest() {
    static bool buttonPressedLast = false;
    bool buttonPressedNow = (GetPressedBtns() > 0);

    if (buttonPressedNow && !buttonPressedLast) {
        ResetGame();
        startNewGame();
    }
    buttonPressedLast = buttonPressedNow;
}

void handleGamePlay(unsigned long currentTime) {
    if (currentTime - startTime > TIME_LIMIT) {
        currentState = GAME_LOST;
    } else {
        int pressedCount = GetPressedBtns();
        if (pressedCount > 0 && NumOfPressedIndexes < MAX_NUM_OF_LIGHTS) {
            delay(debounceDelay); // דילוג לאחר לחיצה
            for (int i = 0; i < NUM_OF_LEDS; i++) {
                if (digitalRead(Btns[i]) == LOW) {
                    PressedIndexes[NumOfPressedIndexes++] = i;
                    if (NumOfPressedIndexes >= MAX_NUM_OF_LIGHTS) {
                        break; // עצור אם הגענו למספר הנדרש של לחיצות
                    }
                }
            }
            if (NumOfPressedIndexes == MAX_NUM_OF_LIGHTS) {
                currentState = CHECKING_RESULT;
            }
        }
    }
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

int GetPressedBtns() {
    int count = 0;
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        unsigned long currentTime = millis();
        int btnState = digitalRead(Btns[i]);

        if (btnState == LOW) {
            if ((currentTime - lastDebounceTime[i]) > debounceDelay) {
                lastDebounceTime[i] = currentTime;
                if (digitalRead(Btns[i]) == LOW) {
                    count++;
                }
            }
        } else {
            lastDebounceTime[i] = currentTime;
        }
    }
    return count;
}

void checkGameResult() {
    if (CheckIfCorrect()) {
        currentState = GAME_WON;
    } else {
        currentState = GAME_LOST;
    }
}

bool CheckIfCorrect() {
    if (NumOfPressedIndexes != MAX_NUM_OF_LIGHTS) {
        return false;
    }
    for (int i = 0; i < MAX_NUM_OF_LIGHTS; i++) {
        bool matchFound = false;
        for (int j = 0; j < MAX_NUM_OF_LIGHTS; j++) {
            if (PressedIndexes[i] == ChosenIndexes[j]) {
                matchFound = true;
                break;
            }
        }
        if (!matchFound) {
            return false;
        }
    }
    return true;
}

void handleWinState() {
    digitalWrite(GLed, LOW);
    digitalWrite(RLed, LOW);
    delay(300);
    digitalWrite(GLed, HIGH);
    tone(BZR, 1000, 500);
    delay(1000);
    currentState = WAITING_FOR_NEW_GAME;
}

void handleLoseState() {
    digitalWrite(GLed, LOW);
    digitalWrite(RLed, LOW);
    delay(300);
    digitalWrite(RLed, HIGH);
    tone(BZR, 250, 500);
    delay(1000);
    currentState = WAITING_FOR_NEW_GAME;
}

void ResetGame() {
    digitalWrite(GLed, LOW);
    digitalWrite(RLed, LOW);
    delay(300);
    NumOfPressedIndexes = 0;
}
