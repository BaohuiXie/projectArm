//back 初始角度20度，抬手角度增加
//shoulder 手臂垂直放下时140度，自身来看逆时针转（抬手）角度减少
//elbow 初始角度20度，极限是110度


//back
int sensorValueBack = 0;
int analogInBack = A0;
int angleBack;
//configuration for H bridge (controlling direction)
//Back
int In1=6;
int In2=10;
int enA=3;


//shoulder
int sensorValueShoulder = 0; 
int analogInShoulder = A1; 
int angleShoulder;
//configuration for H bridge (controlling direction)
//Shoulder
int In3=2;
int In4=4;
int enB=5;



//bicep
int sensorValueBicep = 0;
int analogInBicep = A2;
int angleBicep;
//configuration for H bridge (controlling direction)
//bicep
int In11=7;
int In21=8;
int enA1=9;



//elbow
int sensorValueElbow = 0;
int analogInElbow = A3;
int angleElbow;
//configuration for H bridge (controlling direction)
//Elbow
int In31=13;
int In41=12;
int enB1=11;




void setup() { 
   //back joint sensor
    pinMode(A0, INPUT);   //select the input pin for potentiometer
    //Shoulder joint sensor
    pinMode(A1, INPUT);   //select the input pin for potentiometer
    //bicep joint sensor
    pinMode(A2, INPUT);   //select the input pin for potentiometer
    //elbow joint sensor
    pinMode(A3, INPUT);   //select the input pin for potentiometer


    //h-bridge
    //back motor
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
  //read sensor section
//  sensorValueBack = analogRead(analogInBack);
//  angleBack = map(sensorValueBack,0,1023, 0,240);
//  Serial.print("angle of Back: ");
//  Serial.println(angleBack);
//  delay(300);
//  
//  sensorValueShoulder = analogRead(analogInShoulder);
//  angleShoulder = map(sensorValueShoulder,0,1023, 0,240);
//  Serial.print("angle of shoulder: ");
//  Serial.println(angleShoulder);
//  delay(300);
//  
//  sensorValueBicep = analogRead(analogInBicep);
//  angleBicep = map(sensorValueBicep,0,1023, 0,240);
//  Serial.print("angle of bicep: ");
//  Serial.println(angleBicep);
//  delay(300);
  
//  sensorValueElbow = analogRead(analogInElbow);
//  angleElbow = map(sensorValueElbow,0,1023, 0,240);
//  Serial.print("angle of elbow: ");
//  Serial.println(angleElbow);
//  delay(300);


//-----------------------------------------------
//test h-bridge
//back
//  digitalWrite(In1, HIGH);         
//  digitalWrite(In2, LOW);
//  analogWrite(enA, 220);
//  delay(1000);
//  digitalWrite(In1, LOW);
//  digitalWrite(In2, LOW);


//shoulder
//  digitalWrite(In3, LOW);         
//  digitalWrite(In4, HIGH);
//  analogWrite(enB, 220);
//  delay(1000);
//  digitalWrite(In3, LOW);
//  digitalWrite(In4, LOW);


//bicep
//  digitalWrite(In11, LOW);         
//  digitalWrite(In21, HIGH);
//  analogWrite(enA1, 220);
//  delay(1000);
//  digitalWrite(In11, LOW);
//  digitalWrite(In21, LOW);

  
//ELBOW
//bicep
//  digitalWrite(In31, LOW);         
//  digitalWrite(In41, HIGH);
//  analogWrite(enB1, 220);
//  delay(1000);
//  digitalWrite(In31, LOW);
//  digitalWrite(In41, LOW);
  
  sensorValueBack = analogRead(analogInBack);
  angleBack = map(sensorValueBack,0,1023, 0,240);
  Serial.print("angle of Back: ");
  Serial.println(angleBack);
  //while(1){}
}


//HIGH
////FOR BACK
//void rotationOperator(int roState, int angl, int senValue, int analogInPin, int pinNumber1, 
//              int pinNumber2, int enNumber, int enSpeed, int cvtUserIn, int minRange, int maxRange){
//   switch (roState){
//    case 0:                                                                                // Counterclockwise (rising)
//    //每个值所加减的5是为了防止速度过猛导致的越值
//      while ((angl >= (minRange-5)) && (angl <= (maxRange+5)) && (angl <= cvtUserIn)) { 
//        senValue = analogRead(analogInPin);
//        angl = map(senValue,0,1023,0,240);
//        counterClockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
//        Serial.print("angle is : ");
//         Serial.println(angl);
//      }
//      break;
//    case 1:                                                                                // clockwise (no rising)
//      while ((angl >= (minRange-5)) && (angl <= (maxRange+5)) && (angl >= cvtUserIn)) { 
//        senValue = analogRead(analogInPin);
//        angl = map(senValue,0,1023,0,240);
//        clockWiseRotate(pinNumber1,pinNumber2,enNumber,enSpeed);
//      
//         Serial.print("angle is : ");
//         Serial.println(angl);
//        }
//       break;
//     default:                      //rest
//      turnOffMotor(pinNumber1, pinNumber2);
//      break;
//    }   
//    Serial.print("JUMP OUT THE LOOP");
//    turnOffMotor(pinNumber1, pinNumber2);
//}

//determine state of arm rotation (for back)
//int stateOfRotation(int ang, int cvtUserinput){//cvtUserinput means the value of sensor
//  //0: counterclockwise, 1: clockwise
//  if(ang < cvtUserinput){
//    return 0;
//  }else if(ang > cvtUserinput){
//    return 1;
//  }
//}
