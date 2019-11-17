
int incomingByte = 0;
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;
int dataNumber = 0;  


// PWM
int PWM = 7;
int val = 255;
bool high = true;
int count = 0;


#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 4

SoftwareSerial XSERIAL = SoftwareSerial(rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
  XSERIAL.begin(1200);
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop() {
  
  if(high){
    analogWrite(PWM, val);
    val = 0;
    high = false;
  }
  else{
    analogWrite(PWM, val);
    val = 255;
    high = true;
  }
  

  delay(10);

  
  checkForInput();
  if(newData == true){
    XSERIAL.println(receivedChars);
    Serial.println(receivedChars);
    newData = false;
  }
}





void showNewNumber() {
  if (newData == true) 
  {
    dataNumber = 0;
    dataNumber = atoi(receivedChars);
    newData = false;
  }
}

void checkForInput() 
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  if (Serial.available() > 0) 
  {
    rc = Serial.read();

    if (rc != endMarker) 
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) 
      {
        ndx = numChars - 1;
      }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}
