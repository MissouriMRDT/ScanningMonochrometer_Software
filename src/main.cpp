#include <Arduino.h>

const int EN = 23;
const int M0 = 25;
const int M1 = 27;
const int M2 = 29;
const int STDBY = 33;
const int STEP =35;
const int DIR = 37;
int dir = 0;
int m0 = 1, m1 = 1, m2 = 1; //sets steps to 256 steps/rev.

/*
Make a count int and a zeroing function that sets count to zero.
count will be the max steps so put it in the for loop instead of 256.
make a function to print wavelength

*/

// put function declarations here:
float findIPD(float VP_PD, float Vbias, float Rf);
int myFunction(int x, int y); 
void clockwise();
void counterClockwise();

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
  for(int i =0; i<256;i++){
    counterClockwise();
digitalWrite(STEP, HIGH);
delay(100);
digitalWrite(STEP, LOW);
if(digitalRead(EN) == LOW){
  i=256;
}
  }
    for(int i =0; i<256;i++){
clockwise();
      digitalWrite(STEP, HIGH);
delay(100);
digitalWrite(STEP, LOW);
if(digitalRead(EN) == LOW){
  i=256;
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