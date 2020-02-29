//userInput value
int userInputAngle1=0;

//configuration for H bridge (controlling direction)
int In1=7;
int In2=8;

//-------------------------------------------------------------------------------------------------------------
//configuration for speed control(to servo)
int servo1PIN = 2; // Control pin for servo motor, usually yellow wire to the servo
int minPulseTime = 500; // minimum servo pulse time
int maxPulseTime = 2400; // maximum servo pulse time
int pulseTime = 0; // Amount of time to pulse the servo
long lastPulse = 0; // the time in milliseconds of the last pulse
int refreshTime = 20; // the time needed in between pulses in milliseconds
//---------------------// servos have 50Hz rate, 1sec/50 = 20 milliseconds-----------
int sensorValue = 0; // the value returned from the analog sensor, between 0 and 1023
int analog1INPUTPIN = A0; // the analog pin that the sensor is on


void setup() {
    pinMode(In1,OUTPUT);  //HIGH: LOW:
    pinMode(In2,OUTPUT);  //HIGH: LOW:
    pinMode (A0,INPUT);   //select the input pin for potentiometer
    Serial.begin(9600);   //start communication at 9600 baud

    //Speed controlling setput
    pinMode(servo1PIN, OUTPUT); // Set servo pin as an output pin
    pulseTime = minPulseTime; // Set the motor position value to the minimum
    Serial.begin(9600); // Set up the serial connection for printing
}

//void loop() {
//    //SPEED controlling part
//    sensorValue = analogRead(analog1INPUTPIN); // read the analog input
//    pulseTime = map(sensorValue,0,1023,minPulseTime,maxPulseTime); // convert the analog value to a range between minPulse and maxPulse.
//    //pulse the servo again if the refresh time (20 ms) have passed:
//    if (millis() - lastPulse >= refreshTime) {
//        digitalWrite(In1,HIGH);
//        digitalWrite(In2,LOW); 
//    
//        digitalWrite(servo1PIN, HIGH); // turn on pulse to the servo
//        delayMicroseconds(pulseTime); // length of the pulse sets the motor position
//        digitalWrite(servo1PIN, LOW); // stop pulse to the servo
//        lastPulse = millis(); // save the time of the last pulse
//    }
//    Serial.println(sensorValue);
//    Serial.println(pulseTime);

    //direction controlling part
   
//    sensorValue = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
//    Serial.print("This is Sensor value: ");
//    sensorValue = map(sensorValue, 0, 1023, 0, 240);     // scale it to use it with the servo (value between 0 and 180)
//    Serial.println(sensorValue);
//    checkNoOverRotate();                 //check the current angle and input angle do not over rotate 
//    while (sensorValue < userInputAngle1) { // goes from 0 degrees to 180 degrees
//      digitalWrite(In1, HIGH);
//      digitalWrite(In2,HIGH);            //这个等下要看是正负方向
//      //myservo.write(10);
//      sensorValue = analogRead(A0);
//      sensorValue = map(sensorValue, 0, 1023, 0, 240);
//      Serial.print("Sensor value after rotate: ");
//      Serial.println(sensorValue);
//      //check if sensor have reach the desire angle
//      if (sensorValue==userInputAngle1){ 
//        digitalWrite(In2, LOW); 
//        //mservo.write(0);
//        Serial.println(" Reach the angle.");
//        Serial.print("Sensor value after rotate: ");
//        Serial.println(sensorValue);
//        while(1){}
//     }
//   }
//}
void checkNoOverRotate(){
  //check the current angle and input angle do not over rotate
    if (userInputAngle1 > 180){ //counterclockwise to the max=0 degree
      //sensor initial check
        Serial.print(" arm angle illegal.");
        while(1){}
    }
    if ((sensorValue+userInputAngle1) > 180){ //counterclockwise to the max=0 degree
      //sensor initial check
        Serial.print(" arm angle illegal.");
        while(1){}
    }
}




void stateOfMotor1(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  delay(3000);
}
void stateOfMotor2(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, HIGH);
  delay(3000);
}
void stopMotor(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(servo1PIN, LOW); // stop pulse to the servo
}

void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  //turn motor on
  digitalWrite(servo1PIN, HIGH); // turn on pulse to the servo
  stateOfMotor2();
  // now change motor directions
  stateOfMotor1();
  // now turn off motors
  stopMotor();
}

void loop()
{
  demoOne();
  delay(1000);
}
