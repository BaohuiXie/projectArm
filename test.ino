//test sensor
int sensorPin=A0;
int sensorValue;
int angleValue;
void setup() {
  //sensor
    //Shoulder joint sensor
    pinMode(sensorPin,INPUT);   //select the input pin for potentiomete

   //value set up
    Serial.begin(9600); // Set up the serial connection for printing, start communication at 9600 baud
}

void loop() {
  sensorValue = analogRead(sensorPin);
  angleValue = map(sensorValue, 0, 1023, 0, 240);
  Serial.print("the angle is: ");
  Serial.println(angleValue);
}
