#include <Arduino.h>

// put function declarations here:
float findIPD(float VP_PD, float Vbias, float Rf);
int myFunction(int x, int y); 
void clockwise();
void counterClockwise();

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
//IPD = (VP_PD-Vbias)/Rf
int myFunction(int x, int y) {
  return x + y;
}
void clockwise() {
  // Code to rotate clockwise
}
void counterClockwise() {
  // Code to rotate counter-clockwise
  dir = 0; // Set direction to counter-clockwise
}
float findIPD(float VP_PD, float Vbias, float Rf) {
  return (VP_PD - Vbias) / Rf;
}