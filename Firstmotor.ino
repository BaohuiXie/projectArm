//"back" initial angle value of the sensor is 16. the arm rise means the angle value of the sensor increase
//"shoulder" initial angle value of the sensor is 140，the arm rise means the angle value of the sensor decrease
//"BICEP" initial angle value of the sensor is 180，for the arm itself, clockwise rotation means the angle value of the sensor increase
//elbow initial angle value of the sensor is 20，range must control within the range 116 to 20.

//************For safety do not select a input value that beyong or close to the min&max range******************************//
//************Otherwise, it will come up with following problem：***********************************************************//
//************1.the battery bank power supply can not support the arm to reach that position********************************//
//************2.The angular velocity may break the machanical parts. expectially for the elbow******************************//

//userInput value------------------------------------------------------------------------------------------------------
int userInBack=0;                  //input range 0-93   better select a number between 0-55，
                        //since the battery can not supply that much power to support the movement
int userInShoulder=0;            //input range -55 to 110
int userInBicep=0;                  //INPUT RANGE -40 TO 50
int userInElbow=20;                //input range 20 to 80

//by Baohui
//convert userInput value to sensor input value----------------------------------------------------------------------------------------------
int cvtUserInBack=(userInBack+17);                     //input range 17-110
int cvtUserInShoulder=(140-(userInShoulder));            //input range 30 to 195
int cvtUserInBicep=(180-(userInBicep));                  // input range 130 to 220
int cvtUserInElbow=(userInElbow+(8*userInElbow/20));       //input range 25 to 116


//---------------------------------------------------------------------------------------------------------------
//offset range of the sensor (range of each joint)
//back
int minBack = 17;           //corresponding to the actual value 0 for the arm 
int maxBack = 110;          //corresponding to the actual value 93 for the arm 
//shoulder
int minShoulder = 30;       //corresponding to the actual value 110 for the arm 
int maxShoulder = 195;      //corresponding to the actual value -55 for the arm 
  //bicep
int minBicep = 130;         //corresponding to the actual value 50 for the arm 
int maxBicep = 220;         //corresponding to the actual value -40 for the arm 
  //elbow
int minElbow =25;           //corresponding to the actual value 20 for the arm 
int maxElbow =116;          //corresponding to the actual value 80 for the arm 


//--------------------------------------------------------------------------------------------------
//configuration for H bridge (controlling direction)
//Back
int In1=6;
int In2=10;
int enA=3;
//Shoulder
int In3=2;
int In4=4;
int enB=5;
//bicep
int In11=7;
int In21=8;
int enA1=9;
//Elbow
int In31=13;
int In41=12;
int enB1=11;


//-------------------------------------------------------------------------------------------------------------
//configuration for sensor
//Back
int sensorValueBack = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInBack = A0; // the analog pin that the sensor is on
//shoulder
int sensorValueShoulder = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInShoulder = A1; // the analog pin that the sensor is on
//bicep
int sensorValueBicep = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInBicep = A2; // the analog pin that the sensor is on
//Elbow
int sensorValueElbow = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInElbow = A3; // the analog pin that the sensor is on



//---------------------------------------------------------------------------------------------------------------
//some value to be state
//Back
int angleBack;
int rotationStateBack; //0: clockwise (not rising), 1: Counterclockwise (rising)
//shoulder
int angleShoulder;
int rotationStateShoulder;   //0: clockwise (not rising), 1: Counterclockwise (rising)
//Bicep
int angleBicep;
int rotationStateBicep; //0: clockwise (not rising), 1: Counterclockwise (rising)
//Elbow
int angleElbow;
int rotationStateElbow; //0; clockwise (rising), 1: Counterclockwise (not rising)

//----------------------------------------------------------------------------------------------
//Setting
void setup() { 
   //sensor
   //Back joint sensor
    pinMode(A0, INPUT);    //select the input pin for potentiometer
    //Shoulder joint sensor
    pinMode(A1, INPUT);   //select the input pin for potentiometer
    //Bicep joint sensor
    pinMode(A2, INPUT);   //select the input pin for potentiometer
    //Elbow joint sensor
    pinMode(A3, INPUT);   //Select the input pin for potentiometer
    

   //H bridge
   //Back joint Motor
    pinMode(enA, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    //Shoulder joint Motor
    pinMode(enB, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    //Bicep joint Motor
    pinMode(enA1, OUTPUT);
    pinMode(In11, OUTPUT);
    pinMode(In21, OUTPUT);
    //Elbow joint Motor
    pinMode(enB1,OUTPUT);
    pinMode(In31 ,OUTPUT);
    pinMode(In41 ,OUTPUT);
    
   //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

//by Baohui
void loop() {
//  //read sensor section

  sensorValueBack = analogRead(analogInBack);
  angleBack = map(sensorValueBack,0,1023, 0,240);
  Serial.print("angle of Back: ");
  Serial.println(angleBack);
//  delay(3);
  
  sensorValueShoulder = analogRead(analogInShoulder);
  angleShoulder = map(sensorValueShoulder,0,1023, 0,240);
  Serial.print("angle of Shoulder: ");
  Serial.println(angleShoulder);
//  delay(3);

//
  sensorValueBicep = analogRead(analogInBicep);
  angleBicep = map(sensorValueBicep,0,1023, 0,240);
  Serial.print("angle of Bicep: ");
  Serial.println(angleBicep);
//  delay(3);
//
//
  sensorValueElbow = analogRead(analogInElbow);
  angleElbow = map(sensorValueElbow,0,1023,0,240);
  Serial.print("angle of Elbow:");
  Serial.println(angleElbow);
  Serial.print("angle of cvtUserInElbow:");
  Serial.println(cvtUserInElbow);
  
//  delay(3);
//  

  
  //determine state of arm rotation
  rotationStateBack = stateOfRotation(angleBack,cvtUserInBack);
  rotationStateShoulder = stateOfRotation(angleShoulder,cvtUserInShoulder);
  rotationStateBicep = stateOfRotation(angleBicep,cvtUserInBicep);
  rotationStateElbow = stateOfRotation(angleElbow,cvtUserInElbow);
//  


  //check state section
  Serial.print("state of Back rotation: ");
  Serial.println(rotationStateBack);
//
  Serial.print("state of Shoulder rotation: ");
  Serial.println(rotationStateShoulder);

  Serial.print("state of Bicep rotation: ");
  Serial.println(rotationStateBicep);
//
  Serial.print("state of Elbow rotation: ");
  Serial.println(rotationStateElbow);
//




  //operating section
  rotationOperator(rotationStateBack, angleBack, sensorValueBack, analogInBack,  In1, In2, enA, 230, cvtUserInBack, minBack, maxBack);
  rotationOperator(rotationStateShoulder, angleShoulder, sensorValueShoulder, analogInShoulder,  In3, In4, enB, 230, cvtUserInShoulder, minShoulder, maxShoulder);
  rotationOperator(rotationStateBicep, angleBicep, sensorValueBicep, analogInBicep,  In11, In21, enA1, 230, cvtUserInBicep, minBicep, maxBicep);
  rotationOperator(rotationStateElbow, angleElbow, sensorValueElbow, analogInElbow, In31, In41, enB1, 230, cvtUserInElbow, minElbow, maxElbow);
//  
  while(1){}
}



//-------------------------------------------------------------------------------------
//by Baohui
//determine state of arm rotation 
int stateOfRotation(int ang, int cvtUserinput){//cvtUserinput means the value of sensor
  //0: counterclockwise, 1: clockwise
  if(ang < cvtUserinput){
    return 1;
  }else if(ang > cvtUserinput){
    return 0;
  }
}

//---------------------------------------------------------------------------------------------
//by Baohui
//opertating the rotation for diferent motor or joint with different case
void rotationOperator(int roState, int angl, int senValue, int analogInPin, int pinNumber1, 
              int pinNumber2, int enNumber, int enSpeed, int cvtUserIn, int minRange, int maxRange){
   switch (roState){
    case 0:                                                                                
      while ((angl >= minRange-5) && (angl <= maxRange+5) && (angl >= cvtUserIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        counterClockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
        Serial.print("angle is : ");
         Serial.println(angl);
      }
      break;
    case 1:                                                                                
      while ((angl >= minRange-5) && (angl <= maxRange+5) && (angl <= cvtUserIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        clockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
      
         Serial.print("angle is : ");
         Serial.println(angl);
        }
       break;
     default:                      //rest
      turnOffMotor(pinNumber1, pinNumber2);
      break;
    }   
     Serial.print("JUMP OUT THE LOOP");
     turnOffMotor(pinNumber1, pinNumber2);
}



//--------------------------------------------------------------------------------------
//by Baohui
//turn off motors
void turnOffMotor(int pinNumber1, int pinNumber2){
  digitalWrite(pinNumber1, LOW);
  digitalWrite(pinNumber2, LOW);
}


//------------------------------------------------------------------------------------------
//by Baohui
//look from the back of the motor
void clockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
  digitalWrite(pinNumber1, LOW);         
  digitalWrite(pinNumber2, HIGH);
  analogWrite(enNumber, enSpeed);
  delay(30);//0.03sec
}
//(back:RISE)(shoulder:drop)(BICEP:rotate toward shelf(clockwise))(elbow:rise)


//------------------------------------------------------------------------------------------
//by Baohui
//look from the back of the motor
void counterClockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
   digitalWrite(pinNumber1, HIGH);         
   digitalWrite(pinNumber2, LOW);
   analogWrite(enNumber, enSpeed);
   delay(30);//0.03sec
}
//(back:DROP)(shoulder:rise)(BICEP:rotate leave shelf(counterclockwise))(ELBOW:drop)
