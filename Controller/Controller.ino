//Set Pin Numbers

int redPin = 2;
int greenPin = 5;
int bluePin = 6;

int xPin = A1;
int yPin = A0;
int modePin = 4;

//Set other variables
int xValue;
int yValue;
int mode = 0;

int modeState;
int lastModeState = HIGH;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(modePin, INPUT_PULLUP);

  Serial.begin(9600);
  
}

void loop()
{
  /*setColor(255, 0, 0);  // red
  delay(1000);
  setColor(255, 127, 0);  // orange
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(75, 0, 130);  // indigo
  delay(1000);
  setColor(148, 0, 211);  // red
  delay(1000);*/

  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  modeState = digitalRead(modePin);


  //Button
  if (modeState != lastModeState) {               //check for a button state change
    delay(50);                                    //wait 50ms
    if (modeState != lastModeState) {             //if state is still changed after 50ms (to avoid bouncing)
      lastModeState = modeState;                  //change the stored state to the new state
      if (lastModeState == LOW) {                 //if the new stored state is LOW (The button is pressed and its connection to ground brings it down from the normal high state caused by the pulldwon resistor)
        Serial.println("Mode");                   //send a message to serial stating the button has been pressed
        if (mode == 3) {
          mode = 0;
        } else {
          mode++;
        }
        Serial.println(mode);
       }
     }
   }

   //Color Set
   switch(mode) {
    case 0 : setColor(0, 0, 0);
    break;
    case 1 : setColor(255, 0, 0);
    break;
    case 2 : setColor(0, 255, 0);
    break;
    case 3 : setColor(0, 0, 255);
    break;
   } 
   
   //Joystick
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
 


void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
