#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

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
int findIPD(float VP_PD, float Vbias, float Rf) {
  return (VP_PD - Vbias) / Rf;
}