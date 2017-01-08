// Set pins
int LPWM1 = 3;
int RPWM1 = 5;
int LPWM2 = 9;
int RPWM2 = 10;

int midSpeed = 125;
int currentSpeed;

int input;

void setup() {
  // put your setup code here, to run once:
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
  currentSpeed = midSpeed;

  //start serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0);
  {
    input = Serial.read();
    if (input == 'a')
    {
      if (currentSpeed < 255)
      {
        increaseSpeed();
        Serial.print("Speeding up to ");
        Serial.println(currentSpeed);
      } else
      {
        Serial.println("Max Speed Reached");
      }
    }
  
    if (input == 'b')
    {
      if (currentSpeed > 0)
      {
        decreaseSpeed();
        Serial.print("Slowing down to ");
        Serial.println(currentSpeed);
      } else
      {
        Serial.println("Min Speed Reached");
      }
    }
  }

  
  

}

void increaseSpeed()
{
  currentSpeed += 5;
  analogWrite (LPWM1, currentSpeed);
  analogWrite (LPWM2, currentSpeed);
  delay(100);
}

void decreaseSpeed()
{
  currentSpeed -= 5;
  analogWrite (LPWM1, currentSpeed);
  analogWrite (LPWM2, currentSpeed);
  delay(100);
}

