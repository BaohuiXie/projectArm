// #        M1 pin  -> Digital pin 4
// #        E1 pin  -> Digital pin 5
// #        M2 pin  -> Digital pin 7
// #        E2 pin  -> Digital pin 6
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// #        VD: Power Supply 6.5V~12V; VS: Motor Power Supply 4.8～46V; 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int E1 = 6; //Inittial the output pin
int M1 = 7;
int E2 = 5;
int M2 = 4;
int sensorPin=2 ;//select the input pin for potentiometer
int sensorValue;
int userAngle1=0;
int validityTest=0;

void setup() {
  myservo.attach(sensorPin);  // attaches the servo to the servo object
  pinMode (M1, INPUT);
  pinMode (M2, INPUT);
}

void loop() 
{
  int value=155;
 // for(value=0;value<=255;value+=5)
 // {
    digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    sensorValue = analogRead(sensorPin);            // reads the value of the potentiometer (value between 0 and 1023)
    Serial.println(sensorValue);
    sensorValue = map(sensorValue, 0, 1023, 0, 255);     // scale it to use it with the servo (value between 0 and 180)
    
  
    if (sensorValue > 180){                             //sensor initial check
        Serial.print(" arm angle illegal.")}; 
    
    Serial.print(" Please enter the shoulder angle.");
    userAngle1 = Serial.read();
    validityTest = userAngle1+sensorValue;
    if (validityTest > 180){                            // sensor plus user input check
        Serial.print(" exceed maximum angle avaiable.")};
  
  
  
    Serial.println(sensorValue);
    myservo.write(sensorValue);                  // sets the servo position according to the scaled value
    delay(sensorValue);                           // waits for the servo to get there
 // }
}
http://inmoov.fr/default-hardware-map/
