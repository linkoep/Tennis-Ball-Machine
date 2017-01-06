// Pin setup
  const int increase = 2;
  const int decrease = 3;
  const int xPin = A1;
  const int yPin = A0;
  const int mode = 4;

 // Button States
  int increaseState;
  int decreaseState;
  int modeState;

  //Previous button states
  int lastIncreaseState = HIGH;
  int lastDecreaseState = HIGH;
  int lastModeState = HIGH;

  //Joystick States
  int xValue;
  int yValue;

  
void setup() {
  pinMode(increase, INPUT_PULLUP);
  pinMode(decrease, INPUT_PULLUP);
  pinMode(mode, INPUT_PULLUP);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  Serial.begin(9600);

}

void loop() {
  increaseState = digitalRead(increase);
  decreaseState = digitalRead(decrease);
  modeState = digitalRead(mode);
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

//_________________________________
//    Buttons
//_________________________________

 
  if (increaseState != lastIncreaseState) {         //check for a button state change
    delay(50);                                      //wait 50ms
    if (increaseState != lastIncreaseState) {       //if state is still changed after 50ms (to avoid bouncing)
      lastIncreaseState = increaseState;            //change the stored state to the new state
      if (lastIncreaseState == LOW) {               //if the new stored state is LOW (The button is pressed and its connection to ground brings it down from the normal high state caused by the pulldwon resistor)
        Serial.println("Increase");                 //send a message to serial stating the button has been pressed
      }
    }
  }

  if (decreaseState != lastDecreaseState) {         //check for a button state change
    delay(50);                                      //wait 50ms
    if (decreaseState != lastDecreaseState) {       //if state is still changed after 50ms (to avoid bouncing)
      lastDecreaseState = decreaseState;            //change the stored state to the new state
      if (lastDecreaseState == LOW) {               //if the new stored state is LOW (The button is pressed and its connection to ground brings it down from the normal high state caused by the pulldwon resistor)
        Serial.println("Decrease");                 //send a message to serial stating the button has been pressed
      }
    }
  }

  if (modeState != lastModeState) {               //check for a button state change
    delay(50);                                    //wait 50ms
    if (modeState != lastModeState) {             //if state is still changed after 50ms (to avoid bouncing)
      lastModeState = modeState;                  //change the stored state to the new state
      if (lastModeState == LOW) {                 //if the new stored state is LOW (The button is pressed and its connection to ground brings it down from the normal high state caused by the pulldwon resistor)
        Serial.println("Mode");                   //send a message to serial stating the button has been pressed
      }
    }
  }

//_________________________________
//      Joystick
//_________________________________
if (!(xValue < 600 && xValue > 400 && yValue < 600 && yValue > 400)){   //Check if any values are not between 400 and 600
    if(xValue > 600) {                                                  //If the X value is greater than 600 (center)
      Serial.println("right");                                          //Send a message to serial stating the joystick has moved right
    } else if (xValue < 400) {                                          //Same thing for the other 3 values
      Serial.println("left");
    } else if (yValue < 400) {
      Serial.println("up");
    } else if (yValue > 600) {
      Serial.println("down");
    }
    delay(100);                                                         //10 messages per second should be enough to give a quick response without making the motor move in too small increments
  }
}
