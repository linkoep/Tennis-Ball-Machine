// Set pins
int LPWM1 = 3;
int RPWM1 = 5;

void setup() {
  // put your setup code here, to run once:
pinMode (LPWM1, OUTPUT);
pinMode (RPWM1, OUTPUT);


}

void loop() {
  analogWrite(LPWM1, 255);
  delay(10000);
  analogWrite(LPWM1, 0);
  delay(5000);
  analogWrite(RPWM1, 255);
  delay(10000);
  analogWrite(RPWM1, 0);
  delay(5000);
  

}
