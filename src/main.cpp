#include <Arduino.h>

const int EN = 5;
const int M0 = 6;
const int M1 = 7;
const int M2 = 8;
const int STDBY = 9;
const int STEP = 10;
const int DIR = 11;
int dir = 0;
int m0 = 1, m1 = 1, m2 = 1; //sets steps to 256 steps/rev.
int count = 0; // Initialize count variable
float wavelength = 0.0; // Initialize wavelength variable

/*
TODO:
Get the wavelength change per step and the initial wavelength. 
*/
void zeroCount();
// put function declarations here:
float findIPD(float VP_PD, float Vbias, float Rf);
int myFunction(int x, int y); 
void clockwise();
void counterClockwise();
void printWaveLength(float *WaveLength);

void setup() {
  Serial.begin(9600);
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

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0){
  count = Serial.parseInt();
 }
 counterClockwise();
  for(int i =0; i<count;i++){
digitalWrite(STEP, HIGH);
delay(100);
digitalWrite(STEP, LOW);
delay(100);
if(digitalRead(EN) == LOW){
  break;
}
  }
clockwise();
  for(int i =0; i<count;i++){
      digitalWrite(STEP, HIGH);
delay(100);
digitalWrite(STEP, LOW);
delay(100);
if(digitalRead(EN) == LOW){
  break;
}
    }
}

// put function definitions here:
//IPD = (VP_PD-Vbias)/Rf
int myFunction(int x, int y) {
  return x + y;
}
void clockwise() {
  dir = 1; // Set direction to clockwise
  digitalWrite(DIR, HIGH);
}
void counterClockwise() {
  dir = 0; // Set direction to counter-clockwise
  digitalWrite(DIR, LOW);
}
float findIPD(float VP_PD, float Vbias, float Rf) {
  return (VP_PD - Vbias) / Rf;
}
void printWaveLength(float *WaveLength){
  *WaveLength+= 0.0;
  Serial.print("The wavelength is: ");
  Serial.println(*WaveLength);
  Serial.print(" nms");
}

void zeroCount(){
  count = 0;
}