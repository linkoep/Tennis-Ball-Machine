// Set pins
int LPWM1 = 3;
int RPWM1 = 5;
int LPWM2 = 9;
int RPWM2 = 10;

int mode;                     //control mode (0 = speed and spin)
int numModes = 2;                 //number of control modes (makes it easier to add more control later
int midSpeed = 125;               //initial speed to start to
int currentSpeed1;                //speed of motor one (top)
int currentSpeed2;                //speed of motor two (bottom)

int speedDifferential = 5;        //amount by which to increase speed
int spinDifferential = 5;         //amount by which to increase spin

char input;                        //character received by serial

void setup() {
  // Set pin modes
  pinMode (LPWM1, OUTPUT);
  pinMode (RPWM1, OUTPUT);
  pinMode (LPWM2, OUTPUT);
  pinMode (RPWM2, OUTPUT);
  
  //Spin up motor
  for (int i = 0; i < midSpeed; i++)
  {
    analogWrite (LPWM1, i);
    analogWrite (LPWM2, i);
    delay(10);
  }
  currentSpeed1 = midSpeed;     //set both motor speeds equal to speed reached at spin-up
  currentSpeed2 = midSpeed;

  mode = 0;

  //start serial communication
  Serial.begin(9600);
  Serial.println("Testing Serial");         //for testing purposes
}

void loop() {
  if (Serial.available() > 0) 
  {
    input = Serial.read();       //reads next serial character
    Serial.println(input);                                          //For testing purposes
    
    if (input == 'm')           //mode change received
    {
      if (mode == (numModes -1))
      {
        mode = 0;
      } else
      {
        mode++;
      }
      Serial.println("Mode Changed");
    }
    
    else if (mode == 0)       //when in mode zero
    {
      if (input == 'u')         //up signal received
      {
        addTopspin();
      }
    
      if (input == 'd')         //down signal received
      {
        addBackspin();
      }
      if (input == 'l')         //left signal received
      {
        increaseSpeed();
      }
      if (input == 'r')         //right signal received
      {
        decreaseSpeed();
      }
    }
    
     else if (mode == 1)       //when in mode one
    {
      if (input == 'u')         //up signal received
      {
        Serial.println("Moving up");
      }
    
      if (input == 'd')         //down signal received
      {
        Serial.println("Moving down");
      }
      if (input == 'l')         //left signal received
      {
        Serial.println("Moving left");
      }
      if (input == 'r')         //right signal received
      {
        Serial.println("Moving right");
      }
    }
    
  }

  
  

}




void showSpeed()            //print speed of both motors to serial
{
  Serial.print("Top motor at: ");
  Serial.println(currentSpeed1);
  Serial.print("Bottom motor at: ");
  Serial.println(currentSpeed2);
}

void increaseSpeed()                      
{
  if (currentSpeed1 < 255 && currentSpeed2 < 255)   //if both motors are capable, increase speed by speed differential
  {
    currentSpeed1 += speedDifferential;
    currentSpeed2 += speedDifferential;
    analogWrite (LPWM1, currentSpeed1);
    analogWrite (LPWM2, currentSpeed2);
    showSpeed();
    delay(100);
  } 

  else if (currentSpeed1 >= 255 && currentSpeed2 >= 255)        //otherwise print that one or both motors are at max speed
  {
    Serial.println("Max speed of both motors reached");
    showSpeed();
  }

  else if (currentSpeed1 >= 255)
  {
    Serial.println("Max speed of top motor reached");
    showSpeed();
  }

  else if (currentSpeed2 >= 255)
  {
    Serial.println("Max speed of bottom motor reached");
    showSpeed();
  }
}

void decreaseSpeed()                      
{
  if (currentSpeed1 > 0 && currentSpeed2 > 0)   //if both motors are capable, decrease speed by speed differential
  {
    currentSpeed1 -= speedDifferential;
    currentSpeed2 -= speedDifferential;
    analogWrite (LPWM1, currentSpeed1);
    analogWrite (LPWM2, currentSpeed2);
    showSpeed();
    delay(100);
  } 

  else if (currentSpeed1 <= 0 && currentSpeed2 <= 0)        //otherwise print that one or both motors are at min speed
  {
    Serial.println("Min speed of both motors reached");
    showSpeed();
  }

  else if (currentSpeed1 <= 0)
  {
    Serial.println("Min speed of top motor reached");
    showSpeed();
  }

  else if (currentSpeed2 <= 0)
  {
    Serial.println("Min speed of bottom motor reached");
    showSpeed();
  }
}

void addTopspin()                      
{
  if (currentSpeed1 < 255 && currentSpeed2 > 0)   //if both motors are capable, diverge speed by spin differential with top motor increasing
  {
    currentSpeed1 += spinDifferential;
    currentSpeed2 -= spinDifferential;
    analogWrite (LPWM1, currentSpeed1);
    analogWrite (LPWM2, currentSpeed2);
    showSpeed();
    delay(100);
  } 

  else if (currentSpeed1 >= 255 && currentSpeed2 <= 0)        //otherwise print that one or both motors are at max spin or max/min speed
  {
    Serial.println("Max topspin reached");
    showSpeed();
  }

  else if (currentSpeed1 >= 255)
  {
    Serial.println("Max speed of top motor reached");
    showSpeed();
  }

  else if (currentSpeed2 <= 0)
  {
    Serial.println("Min speed of bottom motor reached");
    showSpeed();
  }
}

void addBackspin()                      
{
  if (currentSpeed1 > 0 && currentSpeed2 < 255)   //if both motors are capable, diverge speed by spin differential with bottom motor increasing
  {
    currentSpeed1 -= spinDifferential;
    currentSpeed2 += spinDifferential;
    analogWrite (LPWM1, currentSpeed1);
    analogWrite (LPWM2, currentSpeed2);
    showSpeed();
    delay(100);
  } 

  else if (currentSpeed1 <= 0 && currentSpeed2 >= 255)        //otherwise print that one or both motors are at max spin or max/min speed
  {
    Serial.println("Max backspin reached");
    showSpeed();
  }

  else if (currentSpeed1 <= 0)
  {
    Serial.println("Min speed of top motor reached");
    showSpeed();
  }

  else if (currentSpeed2 >= 255)
  {
    Serial.println("Max speed of bottom motor reached");
    showSpeed();
  }
}

