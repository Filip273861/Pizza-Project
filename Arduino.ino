#include "Display.h"

const int BUZZER_PIN = 3;
const int LEFT_BUTTON_PIN = 8;
const int RIGHT_BUTTON_PIN = 9;
const int LED1_PIN = 4;
const int LED2_PIN = 5;

int countdown = 0;
unsigned long lastUpdate = 0;
bool isTimerRunning = false;

void setup() {
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    handleButtons();
    if (isTimerRunning) {
        updateTimer();
    }
}

void handleButtons() {
    if (digitalRead(LEFT_BUTTON_PIN) == LOW) {
        resetTimer();
    }
    if (digitalRead(RIGHT_BUTTON_PIN) == LOW && !isTimerRunning) {
        startTimer(20);
    }
}

void resetTimer() {
    countdown = 0;
    isTimerRunning = false;
    lastUpdate = millis();
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    Display.show(countdown);
}

void startTimer(int duration) {
    countdown = duration;
    isTimerRunning = true;
    lastUpdate = millis();
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
}

void updateTimer() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - lastUpdate >= 1000) {
        lastUpdate = currentMillis;
        Display.show(countdown);
        
        if (countdown > 0) {
            countdown--;
            noTone(BUZZER_PIN);
        } else {
            endTimer();
        }
    }
}

void endTimer() {
    isTimerRunning = false;
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    soundAlarm();
}

void soundAlarm() {
    tone(BUZZER_PIN, 400, 600);
    delay(200);
    tone(BUZZER_PIN, 600, 600);
    delay(200);
    tone(BUZZER_PIN, 800, 800);
    delay(200);
}
