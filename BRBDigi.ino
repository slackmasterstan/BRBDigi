#include "DigiKeyboard.h"

#define BUTTONPIN  0
#define GROUNDPIN  2 // You can use pin 2 as ground or the actualy ground pin.
#define LEDPIN     1

// Button default state.  NC - LOW, NO - HIGH
#define BUTTONDEFAULT LOW
#define DEBOUNCEDELAY 50

int buttonState;
int buttonCurrRead;
int buttonPrevRead;
long debounceStart;
boolean buttonPressed = false;

void setup() {
  pinMode(LEDPIN, OUTPUT);

  // Blink
  digitalWrite(LEDPIN, HIGH);
  DigiKeyboard.delay(500);
  digitalWrite(LEDPIN, LOW);


  // Setup Input
  pinMode(BUTTONPIN, INPUT);
  digitalWrite(BUTTONPIN, HIGH);

  // Setup ground
  pinMode(GROUNDPIN, OUTPUT);
  digitalWrite(GROUNDPIN, LOW);

  // Delay otherwise seem to have problem enumerating while P0 and P2 are tied together.
  DigiKeyboard.delay(5000);


  // Blink
  digitalWrite(LEDPIN, HIGH);
  DigiKeyboard.delay(500);
  digitalWrite(LEDPIN, LOW);
}


void loop() {

  buttonCurrRead = digitalRead(BUTTONPIN);
  
  // has the button changed states?  If so lets start counting
  if (buttonCurrRead != buttonPrevRead) {
    debounceStart = millis();
  } 
  
  // has out count exceeded our delay? If so change set buttonState
  if ((millis() - debounceStart) > DEBOUNCEDELAY) {
    buttonState = buttonCurrRead;
  }

  // keep track of current read value for next pass
  buttonPrevRead = buttonCurrRead;

  // Is our button state different than our button default and have we sent key press?
  if ((buttonState != BUTTONDEFAULT) && !buttonPressed) {

   //  press USB key(s)
   DigiKeyboard.sendKeyStroke(KEY_L, MOD_GUI_LEFT);
 
    // Wait a short moment, and release. 
    digitalWrite(LEDPIN, HIGH);
    DigiKeyboard.delay(100);
    digitalWrite(LEDPIN, LOW);
    DigiKeyboard.sendKeyStroke(0);

   // keep track if we have sent keypress
    buttonPressed = true;
  }
  
  // if state changes make sure we "unpress" button
  if (buttonState == BUTTONDEFAULT && buttonPressed) {

    // Button is no longer pressed
    buttonPressed = false;
    
  }
}
