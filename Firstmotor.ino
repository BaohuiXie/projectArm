//userInput value----------------------------------------------------------------------------------------------
int userInputAngle1=10;



//--------------------------------------------------------------------------------------------------
//configuration for H bridge (controlling direction)
int In1=7;
int In2=8;
int ENA=9;



//-------------------------------------------------------------------------------------------------------------
//configuration for sensor
int sensorValue1 = 0; // the value returned from the analog sensor, between 0 and 1023
int analog1INPUTPIN = A0; // the analog pin that the sensor is on



//---------------------------------------------------------------------------------------------------------------
//some value to be state
int angle1;
int rotationState1;   //0: not raising, 1: raising



//----------------------------------------------------------------------------------------------
//Setting
void setup() { 
   //sensor
    //Shoulder joint sensor
    pinMode(A0,INPUT);   //select the input pin for potentiometer

   //H bridge
    //Shoulder joint Motor
    pinMode(ENA, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);

   //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

void loop() {
  //read sensor section
  sensorValue1 = analogRead(analog1INPUTPIN);
  angle1 = map(sensorValue1,0,1023, 0,240);
 
  
  //determine state of arm rotation
  rotationState1 = stateOfRotation(angle1,userInputAngle1);
  
  Serial.print("state of rotation: ");
  Serial.println(rotationState1);
  rotationOperator(rotationState1, angle1, sensorValue1, analog1INPUTPIN, userInputAngle1);

}



//---------------------------------------------------------------------------------------------
//opertating the rotation for diferent motor or joint with different case
void rotationOperator(int roState, int angl, int senValue, int motorSignalPin, int userIn){
   switch (roState){
    case 1:
      while (angl > 0 && angl < userIn) { 
        senValue = analogRead(motorSignalPin);
        angl = map(senValue,0,1023,0,240);
        
      }
      break;
    case 0:
      while (angl > userIn && angl > 0) { 
        senValue = analogRead(motorSignalPin);
        angl = map(senValue,0,1023,0,240);
        
        }
       break;
     default:                      //rest
      
      break;
    }    
    Serial.print("angle: ");
    Serial.println(angl);
    while(1){};
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
void clockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
  analogWrite(enNumber, enSpeed);
  digitalWrite(pinNumber1, HIGH);         //这个要验证
  digitalWrite(pinNumber2, LOW);
}



//------------------------------------------------------------------------------------------
void clockWiseRotate(int pinNumber1, int pinNumber2,int enNumber, int enSpeed){
   analogWrite(enNumber, enSpeed);
  digitalWrite(pinNumber1, LOW);         //这个要验证
  digitalWrite(pinNumber2, HIGH);
}
