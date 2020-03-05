//motor 从背面看过去 counterclockwise rotating means shoulder自身角度来说counterclockwise
//userInput value----------------------------------------------------------------------------------------------
int userInBack=80;
int userInShoulder=150;
int userInBicep=80;



//---------------------------------------------------------------------------------------------------------------
//offset range of the sensor (range of each joint)
//back
int minBack = 0;
int maxBack = 90;
//shoulder
int minShoulder = 0;
int maxShoulder = 180;
//bicep
int minBicep = 0;
int maxBicep = 180;



//--------------------------------------------------------------------------------------------------
//configuration for H bridge (controlling direction)
//Shoulder
int In1=7;
int In2=8;
int ENA=9;
//Back
int In3=2;
int In4=4;
int ENB=3;



//-------------------------------------------------------------------------------------------------------------
//configuration for sensor
//shoulder
int sensorValueShoulder = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInShoulder = A0; // the analog pin that the sensor is on
//Back
int sensorValueBack = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInBack = A1; // the analog pin that the sensor is on



//---------------------------------------------------------------------------------------------------------------
//some value to be state
//shoulder
int angleShoulder;
int rotationStateShoulder;   //0: clockwise (not raising), 1: Counterclockwise (rising)
//Back
int angleBack;
int rotationStateBack; //0: clockwise (not raising), 1: Counterclockwise (rising)



//----------------------------------------------------------------------------------------------
//Setting
void setup() { 
   //sensor
    //Shoulder joint sensor
    pinMode(A0, INPUT);   //select the input pin for potentiometer
    //Back joint sensor
    pinMode(A1, INPUT);

   //H bridge
    //Shoulder joint Motor
    pinMode(ENA, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    //Back joint Motor
    pinMode(ENB, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);

   //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

void loop() {
  //read sensor section
  //sensorValueBack = analogRead(analogInBack);
  //angleBack = map(sensorValueBack,0,1023, 0,240);
  sensorValueShoulder = analogRead(analogInShoulder);
  angleShoulder = map(sensorValueShoulder,0,1023, 0,240);
 Serial.print("angle of shoulder: ");
  Serial.println(angleShoulder);
  delay(3);

  
  //determine state of arm rotation
  //rotationStateBack = stateOfRotation(angleBack,userInBack);
  rotationStateShoulder = stateOfRotation(angleShoulder,userInShoulder);
  


  //check state section
//  Serial.print("state of Back rotation: ");
//  Serial.println(rotationStateShoulder);
//  delay(3);
  Serial.print("state of Shoulder rotation: ");
  Serial.println(rotationStateShoulder);
  delay(3);




// speed is set to 150 in the midterm demo

  //operating section
  //rotationOperator(rotationStateBack, angleBack, sensorValueBack, analogInBack,  In3, In4, ENB, 150, userInBack, minBack, maxBack);
  rotationOperator(rotationStateShoulder, angleShoulder, sensorValueShoulder, analogInShoulder,  In1, In2, ENA, 150, userInShoulder, minShoulder, maxShoulder);
  if(angleShoulder == userInShoulder){
      while(1){};  
  }
}



//---------------------------------------------------------------------------------------------
//opertating the rotation for diferent motor or joint with different case
void rotationOperator(int roState, int angl, int senValue, int analogInPin, int pinNumber1, 
              int pinNumber2, int enNumber, int enSpeed, int userIn, int minRange, int maxRange){
   switch (roState){
    case 1:                                                                                // Counterclockwise (rising)
      while ((angl >= minRange) && (angl < maxRange) && (angl < userIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        counterClockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
        delay(3);
         Serial.print("angle of Shoulder: ");
         Serial.println(angl);
         delay(3);
      }
      break;
    case 0:                                                                                // clockwise (no rising)
      while ((angl >= minRange) && (angl < maxRange) && (angl > userIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        clockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
        delay(3);
         Serial.print("angle of Shoulder: ");
         Serial.println(angl);
         delay(3);
        }
       break;
     default:                      //rest
      
      break;
    }   
}



//-------------------------------------------------------------------------------------
//determine state of arm rotation
int stateOfRotation(int ang, int userinput){
  //0: not raising, 1: raising 这个要注意查
  if(ang < userinput){
    return 1;
  }else if(ang > userinput){
    return 0;
  }
}


//--------------------------------------------------------------------------------------
//turn off motors
void turnOffMotor(int pinNumber1, int pinNumber2){
  digitalWrite(pinNumber1, LOW);
  digitalWrite(pinNumber2, LOW);
}


//------------------------------------------------------------------------------------------
//从马达背面看过去
void clockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
  analogWrite(enNumber, enSpeed);
  digitalWrite(pinNumber1, LOW);         
  digitalWrite(pinNumber2, HIGH);
}



//------------------------------------------------------------------------------------------
//从马达背面看过去
void counterClockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
   analogWrite(enNumber, enSpeed);
   digitalWrite(pinNumber1, HIGH);         
   digitalWrite(pinNumber2, LOW);
}
