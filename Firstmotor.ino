//userInput value----------------------------------------------------------------------------------------------
int userInputAngle1=10;




//configuration for H bridge (controlling direction)------------------------------------------------------------
int In1=7;
int In2=8;



//-------------------------------------------------------------------------------------------------------------
//configuration for servo
int servo1PIN = 11; // Control pin for servo motor, usually yellow wire to the servo



//-------------------------------------------------------------------------------------------------------------
//configuration for sensor
int sensorValue1 = 0; // the value returned from the analog sensor, between 0 and 1023
int analog1INPUTPIN = A0; // the analog pin that the sensor is on



//---------------------------------------------------------------------------------------------------------------
//some value to be state
int angle1;
int rotationState1;   //0: not raising, 1: raising



//PWM value set up configuration
int minPulseTime = 500; // minimum servo pulse time
int maxPulseTime = 2400; // maximum servo pulse time
int pulseTime = 0; // Amount of time to pulse the servo
long lastPulse = 0; // the time in milliseconds of the last pulse
int refreshTime = 20; // the time needed in between pulses in milliseconds

void setup() {
    //servo
    pinMode(servo1PIN, OUTPUT); // Set servo pin as an output pin

    
   //sensor
    pinMode (A0,INPUT);   //select the input pin for potentiometer

   //value set up
    pulseTime = minPulseTime; // Set the motor position value to the minimum
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

void loop() {
  //read sensor section
  sensorValue1 = analogRead(analog1INPUTPIN);
  angle1 = map(sensorValue1,0,1023, 0,240);
  pulseTime = 1000;                               //暂定
  
  //determine state of arm rotation
  rotationState1 = stateOfRotation(angle1,userInputAngle1);
  
  Serial.print("state of rotation: ");
  Serial.println(rotationState1);
  rotationOperator(rotationState1, angle1, sensorValue1, analog1INPUTPIN, userInputAngle1);

}




//opertating the rotation for diferent motor or joint with different case-------------------
void rotationOperator(int roState, int angl, int senValue, int motorSignalPin, int userIn){
   switch (roState){
    case 1:
      while (angl > 0 && angl < userIn) { 
        senValue = analogRead(motorSignalPin);
        angl = map(senValue,0,1023,0,240);
        //generate PWM
        pwmGenerator(angl);
      }
      break;
    case 0:
      while (angl > userIn && angl > 0) { 
        senValue = analogRead(motorSignalPin);
        angl = map(senValue,0,1023,0,240);
        //generate PWM
        pwmGenerator(angl);
        }
       break;
     default:                      //rest
      
      break;
    }    
    Serial.print("angle: ");
    Serial.println(angl);
    while(1){};
}




//determine state of arm rotation--------------------------------------
int stateOfRotation(int ang, int userinput){
  if(ang < userinput){
    return 1;
  }else if(ang > userinput){
    return 0;
  }
}


//generate PWM-----------------------------------------------------------------
void pwmGenerator(int angl){
  //generate PWM
      if (millis() - lastPulse >= refreshTime) {
          digitalWrite(servo1PIN, HIGH); // turn on pulse to the servo
          delayMicroseconds(pulseTime); // length of the pulse sets the motor position
          digitalWrite(servo1PIN, LOW); // stop pulse to the servo
          lastPulse = millis(); // save the time of the last pulse
      }
      Serial.print("while angle: ");
      Serial.println(angl);
      delay(15);                       // waits 15ms for the servo to reach the position
}
