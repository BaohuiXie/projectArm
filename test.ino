//back 初始角度20度，抬手角度增加
//shoulder 手臂垂直放下时140度，自身来看逆时针转（抬手）角度减少
//BICEP 初始180，手臂自身顺时针转角度增大，逆时针角度变小
//elbow 初始角度20度，极限是116度


//back
int sensorValueBack = 0;
int analogInBack = A0;
int angleBack;

//shoulder
int sensorValueShoulder = 0; // the value returned from the analog sensor, between 0 and 1023
int analogInShoulder = A1; // the analog pin that the sensor is on
int angleShoulder;

//bicep
int sensorValueBicep = 0;
int analogInBicep = A2;
int angleBicep;

//elbow
int sensorValueElbow = 0;
int analogInElbow = A3;
int angleElbow;




void setup() { 
   //back joint sensor
    pinMode(A0, INPUT);   //select the input pin for potentiometer
    //Shoulder joint sensor
    pinMode(A1, INPUT);   //select the input pin for potentiometer
    //bicep joint sensor
    pinMode(A2, INPUT);   //select the input pin for potentiometer
    //elbow joint sensor
    pinMode(A3, INPUT);   //select the input pin for potentiometer
    
   //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

void loop() {
  //read sensor section
//  sensorValueBack = analogRead(analogInBack);
//  angleBack = map(sensorValueBack,0,1023, 0,240);
//  Serial.print("angle of Back: ");
//  Serial.println(angleBack);
//  delay(3);
//  
//  sensorValueShoulder = analogRead(analogInShoulder);
//  angleShoulder = map(sensorValueShoulder,0,1023, 0,240);
//  Serial.print("angle of shoulder: ");
//  Serial.println(angleShoulder);
//  delay(3);
//  
  sensorValueBicep = analogRead(analogInBicep);
  angleBicep = map(sensorValueBicep,0,1023, 0,240);
  Serial.print("angle of bicep: ");
  Serial.println(angleBicep);
  delay(3);
  
//  sensorValueElbow = analogRead(analogInElbow);
//  angleElbow = map(sensorValueElbow,0,1023, 0,240);
//  Serial.print("angle of elbow: ");
//  Serial.println(angleElbow);
//  delay(3);
}
