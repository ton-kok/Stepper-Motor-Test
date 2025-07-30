#include <Arduino.h>
#define btnpin 8
unsigned long lastDebounceTime = 0;
typedef struct {
    bool currentState;
    bool lastState;
} ButtonState;

const long debounceDelay = 100;


ButtonState buttonRead(int readPin) {
    static int lastButtonState = LOW;
    static int buttonState = LOW;
    static unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 50;

    int reading = digitalRead(readPin);

    // Save last stable state before potentially updating
    ButtonState result;
    result.lastState = buttonState;

    // Debounce logic
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
        }
    }

    lastButtonState = reading;
    result.currentState = buttonState;

    return result;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(btnpin,INPUT);
  Serial.begin(9600);
}

void loop() {
  ButtonState btn = buttonRead(btnpin);
  if (btn.lastState == LOW && btn.currentState == HIGH) {
      Serial.println("sdf");
  }
}
