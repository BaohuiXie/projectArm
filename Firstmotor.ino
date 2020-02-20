// #        M1 pin  -> Digital pin 4
// #        E1 pin  -> Digital pin 5
// #        M2 pin  -> Digital pin 7
// #        E2 pin  -> Digital pin 6
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// #        VD: Power Supply 6.5V~12V; VS: Motor Power Supply 4.8～46V; 

int E1 = 6; //Inittial the output pin
int M1 = 7;
int E2 = 5;
int M2 = 4;
int sensorValue;
int userAngle1;
int validityTest;

void setup() {
  pinMode (M1, OUTPUT);
  pinMode (M2, OUTPUT);
  pinMode (A0,INPUT);   //select the input pin for potentiometer
  Serial.begin(9600);   //start communication at 9600 baud
}

void loop() 
{
  int value=155;
 // for(value=0;value<=255;value+=5)
 // {
    digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    sensorValue = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
    Serial.print("This is Sensor value");
    sensorValue = map(sensorValue, 0, 1023, 0, 255);     // scale it to use it with the servo (value between 0 and 180)
    Serial.println(sensorValue);

    if (sensorValue > 191) //(180/240)=(X/255)counterclockwise to the max=0 degree
    {                             //sensor initial check
        Serial.print(" arm angle illegal.");
        while(1){}
    }
    if (sensorValue = 0; sensorValue <= 191) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      digitalWrite(M1,HIGH);
      digitalWrite(M2,HIGH);             
      analogWrite(E1, value);   //PWM Speed Control
      analogWrite(E2, value);   //PWM Speed Control
      delay(15);                       // waits 15ms for the servo to reach the position
    }else {
      digitalWrite(M1,LOW);
      digitalWrite(M2,LOW);     
      analogWrite(E1, value);   //PWM Speed Control
      analogWrite(E2, value);   //PWM Speed Control
      delay(15);                       // waits 15ms for the servo to reach the position
    }
//    Serial.print(" Please enter the shoulder angle.");
//    
//   if(Serial.available())
//   {
//        userAngle1 = Serial.read();
//   }                  // Returnn The first byte of incoming serial data available (or -1 if no data is available). Data type: int.
//   validityTest = userAngle1+sensorValue;
//   if (validityTest > 180)
//   {                            // sensor plus user input check
//        Serial.print(" exceed maximum angle avaiable.");
//   }
        
   // myservo.write(sensorValue);                  // sets the servo position according to the scaled value
    delay(30);                           // waits for the servo to get there
   
 // }
}
