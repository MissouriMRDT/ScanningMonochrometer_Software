#include <Arduino.h>
#include "RoveComm.h"
uint16_t data[2048]{};
const int EN = 41;
const int M0 = 0;
const int M1 = 1;
const int M2 = 2;
const int STDBY = 38;
const int STEP = 39;
const int DIR = 40;
const int LIMIT_SWITCH = 27;
int dir = 0;
int m0 = 1, m1 = 1, m2 = 1; // sets steps to 256 steps/rev.
int count = 0;              // Initialize count variable
const int maxsteps = 256;
float Data[maxsteps]; // array that stores the wavelength values
float initialWavelength = 0.0; // Initialize initial wavelength variable
float wavelength = initialWavelength;     // Initialize wavelength variable
/*
TODO:
Get the wavelength change per step and the initial wavelength.
actually get the maximum steps needed
*/
RoveCommEthernet roveComm;
RoveCommPacket packet;

void doRoveComm();
void sendData();
void zeroCount();
#define LASER_OUT
// put function declarations here:
float findIPD(float VP_PD, float Vbias, float Rf);
int myFunction(int x, int y);
void clockwise();
void counterClockwise();
void printWaveLength(float *WaveLength);
void stepread();
void setup()
{
  Serial.begin(115200);
  roveComm.begin(RC_RAMANBOARD_IPADDRESS);
  pinMode(STDBY, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  digitalWrite(STDBY, LOW); // Set STDBY low to enable the driver
  pinMode(EN, OUTPUT);

  digitalWrite(M0, HIGH);
  digitalWrite(M1, HIGH); // sets M 0-2 to 1.that sets up for 256 steps.
  digitalWrite(M2, HIGH);
  delay(1000); // Wait for the driver to initialize
}

void loop(){
  // put your main code here, to run repeatedly:
  doRoveComm();
  if (Serial.available() > 0)
  {
    count = Serial.parseInt();
  }
  counterClockwise();
  stepread();
  clockwise();
  stepread();
}

// put function definitions here:
// IPD = (VP_PD-Vbias)/Rf
void stepread()
{
  for(int i = 0; i < count; i++)
  {
    digitalWrite(STEP, HIGH);
    delay(100);
    digitalWrite(STEP, LOW);
    delay(100);
  }
}
void doRoveComm()
{
    //This will retrieve the most recent packet sent and pass it 
    //into the "packet" variable.
    roveComm.read(packet);

    //This switch will just cover each different packet you could receive
    switch(packet.dataId)
    {
    //Change Laser State
    
    //case RC_RAMANBOARD_LASER_DATA:
        
    //this sets the pin to the value that is passed through rovecomm
        
        //digitalWrite(LASER_OUT, packet.i8data[0]);
        
        //TODO: Watchdog stuff so the laser doesn't stay on 
        //[i can help with this if you need]

        break;

    case RC_RAMANBOARD_REQUESTRAMANREADING_DATA_ID:
        //This will be where you read your data and send it back
        
        sendData();

        break;
    }
}
void sendData()
{
    //This is where you send the data back to basestation.
    //Because this is built for a different system it will be expecting
    //an array of 2048 uint16_t's you do not have to use all of them.
    roveComm.write(RC_RAMANBOARD_RAMANREADING_PART1_DATA_ID, 512, &data[0]);
        roveComm.write(RC_RAMANBOARD_RAMANREADING_PART2_DATA_ID, 512, &data[512]);
        roveComm.write(RC_RAMANBOARD_RAMANREADING_PART3_DATA_ID, 512, &data[1024]);
        roveComm.write(RC_RAMANBOARD_RAMANREADING_PART4_DATA_ID, 512, &data[1536]);
    //You have to send the data in 4 parts.
}

int myFunction(int x, int y)
{
  return x + y;
}
void clockwise()
{
  dir = 1; // Set direction to clockwise
  digitalWrite(DIR, HIGH);
}
void counterClockwise()
{
  dir = 0; // Set direction to counter-clockwise
  digitalWrite(DIR, LOW);
}
float findIPD(float VP_PD, float Vbias, float Rf)
{
  return (VP_PD - Vbias) / Rf;
}
void printWaveLength(float *WaveLength)
{
  *WaveLength += 0.0;
  Serial.print("The wavelength is: ");
  Serial.println(*WaveLength);
  Serial.print(" nms");
}

void zeroCount()
{
  counterClockwise();
  while(digitalRead(LIMIT_SWITCH) == LOW){
    digitalWrite(STEP, HIGH);
    delay(100);
    digitalWrite(STEP, LOW);
    delay(100);
  }
 wavelength = initialWavelength;
  count = 0;
}