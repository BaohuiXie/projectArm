//-------------------------------------------------------------------------------------------------------------
//configuration for sensor
int sensorValue1 = 0; // the value returned from the analog sensor, between 0 and 1023
int analog1INPUTPIN = A0; // the analog pin that the sensor is on
int angle1;


void setup() { 
   //sensor
    //Shoulder joint sensor
    pinMode(A0,INPUT);   //select the input pin for potentiometer
       //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}



void loop() {
  //read sensor section
  sensorValue1 = analogRead(analog1INPUTPIN);
  angle1 = map(sensorValue1,0,1023, 0,240);
  Serial.print("angle value: ");
  Serial.println(angle1);
}
