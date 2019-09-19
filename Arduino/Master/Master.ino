
#include <Wire.h>

int headingpin = 3;

const byte buffSize = 40;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;
char messageFromPC[buffSize] = {0};
unsigned long replyToPCinterval = 500;

//=============

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
pinMode(headingpin, INPUT);           // set pin to input
}

//=============

void loop() {
int val = digitalRead(headingpin); 
if (val == HIGH)
{
  getDataFromPC();
  replyToPC();
}
}

//=============

void getDataFromPC() {

    // receive data from PC and save it into inputBuffer
    
  if(Serial.available() > 0) {

    char x = Serial.read();

      // the order of these IF clauses is significant
      
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    
    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) { 
      bytesRecvd = 0; 
      readInProgress = true;
    }
  }
}

//=============
 
void parseData() {

    // split the data into its parts
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(inputBuffer,",");      // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
  
}

//=============

void replyToPC() {

  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<");
    Serial.print(messageFromPC);
    Serial.println(">");
    
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(messageFromPC);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(9); // transmit to device #8
    Wire.write(messageFromPC);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  
  }
}
