#ifndef SCANNING_MONOCHROMETER_HEADER
#define SCANNING_MONOCHROMETER_HEADER

#include <RoveComm.h>
#include <Arduino.h>
#include "PinAssignments.h"

void pinInitializations();
void doRoveComm();
void doSteps();
void toggleStep();
void detoggleStep();
void sendRamanTelemetry();

RoveCommEthernet roveComm;
RoveCommPacket roveCommPacket;

#define STEPS_MAX 50
#define STEP_HIGH_TIME 100
uint16_t steps = 0;
bool reading = false;
IntervalTimer toggleStepInterval;

uint16_t data[2048];
 
#endif