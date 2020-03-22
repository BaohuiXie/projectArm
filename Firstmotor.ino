//bicep 校准时sensor(红黄绿，黄绿蓝)调到110， 手臂与shoulder两束对齐， range: 20-200 (0-180)， sensor背对你clockwise为增大角度，红为地线绿为火线
//shoulder motor 从背面看过去 counterclockwise rotating means shoulder自身角度来说counterclockwise
//back 初始角度20度，抬手角度增加
//shoulder 手臂垂直放下时140度，自身来看逆时针转（抬手）角度减少
//BICEP 初始180，手臂自身顺时针转角度增大，逆时针角度变小
//elbow 初始角度20度，极限是116度-20度
//userInput value----------------------------------------------------------------------------------------------
int userInBack=(90+20);
int userInShoulder=90;
int userInBicep=170;                  // plus 20 is defalt value, do not delect (20-200)
int userInElbow=90;


//---------------------------------------------------------------------------------------------------------------
//offset range of the sensor (range of each joint)
//back
int minBack = 20;
int maxBack = 110;
//shoulder
int minShoulder = 30;
int maxShoulder = 180;
  //bicep
int minBicep = 130;
int maxBicep = 220;
  //elbow
int minElbow =20;
int maxElbow =116;


//--------------------------------------------------------------------------------------------------
//configuration for H bridge (controlling direction)
//Back
int In1=0;
int In2=1;
int enA=3;
//Shoulder
int In3=2;
int In4=4;
int enB=5;
//bicep
int In11=7;
int In21=8;
int enA1=6;
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

void loop() {
//  //read sensor section
//  sensorValueBack = analogRead(analogInBack);
//  angleBack = map(sensorValueBack,0,1023, 0,240);
//  Serial.print("angle of Back: ");
//  Serial.println(angleBack);
//  delay(3);
  
  sensorValueShoulder = analogRead(analogInShoulder);
  angleShoulder = map(sensorValueShoulder,0,1023, 0,240);
  Serial.print("angle of Shoulder: ");
  Serial.println(angleShoulder);
  delay(3);
//
//
//  sensorValueBicep = analogRead(analogInBicep);
//  angleBicep = map(sensorValueBicep,0,1023, 0,240);
//  Serial.print("angle of Bicep: ");
//  Serial.println(angleBicep);
//  delay(3);
//
//
//  sensorValueElbow = analogRead(analogInElbow);
//  angleElbow = map(sensorValueElbow,0,1023,0,240);
//  Serial.print("angle of Elbow:");
//  Serial.println(angleElbow);
//  delay(3);
//  

  
  //determine state of arm rotation
//  rotationStateBack = stateOfRotation(angleBack,userInBack);
  rotationStateShoulder = stateOfRotation(angleShoulder,userInShoulder);
//  rotationStateBicep = stateOfRotation(angleBicep,userInBicep);
//  rotationStateElbow = stateOfRotation(angleElbow,userInElbow);
//  


  //check state section
//  Serial.print("state of Back rotation: ");
//  Serial.println(rotationStateBack);

  Serial.print("state of Shoulder rotation: ");
  Serial.println(rotationStateShoulder);

//  Serial.print("state of Bicep rotation: ");
//  Serial.println(rotationStateBicep);
//
//  Serial.print("state of Elbow rotation: ");
//  Serial.println(rotationStateElbow);
//



// speed is set to 150 in the midterm demo

  //operating section
//  rotationOperator(rotationStateBack, angleBack, sensorValueBack, analogInBack,  In1, In2, enA, 200, userInBack, minBack, maxBack);
  rotationOperator(rotationStateShoulder, angleShoulder, sensorValueShoulder, analogInShoulder,  In3, In4, enB, 200, userInShoulder, minShoulder, maxShoulder);
//  rotationOperator(rotationStateBicep, angleBicep, sensorValueBicep, analogInBicep,  In11, In21, enA1, 200, userInBicep, minBicep, maxBicep);
//  rotationOperator(rotationStateElbow, angleElbow, sensorValueElbow, analogInElbow, In31, In41, enB1, 200, userInElbow, minElbow, maxElbow);
//  
}



//---------------------------------------------------------------------------------------------
//opertating the rotation for diferent motor or joint with different case
void rotationOperator(int roState, int angl, int senValue, int analogInPin, int pinNumber1, 
              int pinNumber2, int enNumber, int enSpeed, int userIn, int minRange, int maxRange){
   switch (roState){
    case 1:                                                                                // Counterclockwise (rising)
      while ((angl > minRange) && (angl < maxRange) && (angl < userIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        counterClockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
        Serial.print("angle of : ");
         Serial.println(angl);
      }
      break;
    case 0:                                                                                // clockwise (no rising)
      while ((angl > minRange) && (angl < maxRange) && (angl > userIn)) { 
        senValue = analogRead(analogInPin);
        angl = map(senValue,0,1023,0,240);
        clockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
      
         Serial.print("angle of : ");
         Serial.println(angl);
        }
       break;
     default:                      //rest
      turnOffMotor(pinNumber1, pinNumber2);
      break;
     turnOffMotor(pinNumber1, pinNumber2);
    }   
}



//-------------------------------------------------------------------------------------
//determine state of arm rotation
int stateOfRotation(int ang, int userinput){
  //0: not raising, 1: clockwise(rise) 
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
  digitalWrite(pinNumber1, LOW);         
  digitalWrite(pinNumber2, HIGH);
  analogWrite(enNumber, enSpeed);
  delay(30);//0.03sec
}



//------------------------------------------------------------------------------------------
//从马达背面看过去
void counterClockWiseRotate(int pinNumber1, int pinNumber2, int enNumber, int enSpeed){
   digitalWrite(pinNumber1, HIGH);         
   digitalWrite(pinNumber2, LOW);
   analogWrite(enNumber, enSpeed);
   delay(30);//0.03sec
}
