// Pin setup
  const int speedIncrease = 2;
  const int speedDecrease = 3;
  const int topSpin = 4;
  const int backSpin = 5;
  const int XPin = A1;
  const int YPin = A0;

  // Button States
  int speedIncreaseState;
  int speedDecreaseState;
  int topSpinState;
  int backSpinState;

  //Previous button states
  int lastSpeedIncreaseState = LOW;
  int lastSpeedDecreaseState = LOW;
  int lastTopSpinState = LOW;
  int lastBackSpinState = LOW;

 /* //Debounce stuff
  long DBTSpeedIncrease;
  long DBTSpeedDecrease;
  long DBTTopSpin;
  long DBTBackSpin;
  long debounceDelay = 50; */

  //Joystick States
  int XValue;
  int YValue;

void setup() {
  pinMode(speedIncrease, INPUT);
  pinMode(speedDecrease, INPUT);
  pinMode(topSpin, INPUT);
  pinMode(backSpin, INPUT);
  pinMode(XPin, INPUT);
  pinMode(YPin, INPUT);

  Serial.begin(9600);

}
void loop() {
  speedIncreaseState = digitalRead(speedIncrease);
  speedDecreaseState = digitalRead(speedDecrease);
  topSpinState = digitalRead(topSpin);
  backSpinState = digitalRead(backSpin);
  XValue = analogRead(XPin);
  YValue = analogRead(YPin);

 
  /* The following code checks for a state change, changes the last stored state
     and sends the corresponding signal to serial if the button was pressed 
     Commented out sections are for debouncing the input, which currently doesn't work for me*/
  /*if (speedIncreaseState != lastSpeedIncreaseState) {
    DBTSpeedIncrease = millis();
  }
  if ((millis() - DBTSpeedIncrease) > debounceDelay) { */
    if (speedIncreaseState != lastSpeedIncreaseState) {
      lastSpeedIncreaseState = speedIncreaseState;
      if (lastSpeedIncreaseState == HIGH) {
        Serial.println("a");
      }
    }
  //}

 // The following does the same for the next button
  /*if (speedDecreaseState != lastSpeedDecreaseState) {
    DBTSpeedDecrease = millis();
  }
  if ((millis() - DBTSpeedDecrease) > debounceDelay) { */
    if (speedDecreaseState != lastSpeedDecreaseState) {
      lastSpeedDecreaseState = speedDecreaseState;
      if (lastSpeedDecreaseState == HIGH) {
        Serial.println("b");
      }
    }
  //}

  //And for the next
 /* if (topSpinState != lastTopSpinState) {
    DBTTopSpin = millis();
  }
  if ((millis() - DBTTopSpin) > debounceDelay) { */
    if (topSpinState != lastTopSpinState) {
      lastTopSpinState = topSpinState;
      if (lastTopSpinState == HIGH) {
        Serial.println("c");
      }
    }
  //}

  //And for the next
 /* if (backSpinState != lastBackSpinState) {
    DBTBackSpin = millis();
  }
  if ((millis() - DBTBackSpin) > debounceDelay) { */
    if (backSpinState != lastBackSpinState) {
      lastBackSpinState = backSpinState;
      if (lastBackSpinState == HIGH) {
        Serial.println("d");
      }
    }
 // }

 //Joystick Code Block
  if (!(XValue < 600 && XValue > 400 && YValue < 600 && YValue > 400)){
    if(XValue > 600) {
      Serial.println("right");
    } else if (XValue < 400) {
      Serial.println("left");
    } else if (YValue > 600) {
      Serial.println("up");
    } else if (YValue < 400) {
      Serial.println("down");
    }
    delay(100);
  }
 
}
