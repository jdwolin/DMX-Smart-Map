

#include <Wire.h>


const byte buffSize = 40;
char inputBuffer[buffSize];
char stringish[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;
char messageFromPC[buffSize] = {0};
unsigned long replyToPCinterval = 500;
int headingpin = 3;
//=============

void setup() {
  Wire.begin(9);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial.println("<Arduino is ready>");
  pinMode(headingpin, OUTPUT);           // set pin to input
  digitalWrite(headingpin, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  delay(100);
  getDataFromPC();
  replyToPC();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  memset(stringish, 0, sizeof(stringish));
  int counter = 0;
  while (Wire.available()) { // loop through all but the last
  char c = Wire.read(); // receive byte as a character
  Serial.println(c);
  stringish[counter] = c;
  counter++;

  }
    Serial.print("<");
    Serial.print(stringish);
    Serial.println(">");
    digitalWrite(headingpin, LOW); 

}

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
    Serial.print("led set");
    Serial.println(">");
   digitalWrite(headingpin, HIGH);
  }
}



