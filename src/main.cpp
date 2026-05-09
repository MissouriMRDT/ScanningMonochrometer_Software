#include "ScanningMonochrometerSoftware.h" 

void setup()
{
  //Setup pins
  pinInitializations();

  //RoveComm setup
  roveComm.begin(RC_RAMANBOARD_IPADDRESS);
}


void loop()
{
  doRoveComm();

  if (reading)
    doSteps();
}


void doRoveComm()
{
  roveComm.read(roveCommPacket);

  switch(roveCommPacket.dataId)
  {
  //If request reading packet sent, start reading
  case RC_RAMANBOARD_REQUESTRAMANREADING_DATA_ID:
    reading = true;  
  }
}


void doSteps()
{
  if (steps < STEPS_MAX * 2)
  {
    data[steps] = analogRead(DATA_IN);

    steps++;
  
    //if at the begining set it to the default direction.
    //if half way through set it to the opposite direction.
    switch (steps)
    {
    case 0:
      digitalWrite(DIR_OUT, DIR_DEFAULT);
    case STEPS_MAX:
      digitalWrite(DIR_OUT, !DIR_DEFAULT);
    }

    toggleStep();
  }
  else
  {
    reading = false;
    steps = 0;
    sendRamanTelemetry();
  }
}


void toggleStep()
{
  digitalWrite(STEP_OUT, HIGH);
  toggleStepInterval.begin(detoggleStep, STEP_HIGH_TIME);
}


void detoggleStep()
{
  digitalWrite(STEP_OUT, LOW);
  toggleStepInterval.end();
}


void sendRamanTelemetry()
{
  roveComm.write(RC_RAMANBOARD_RAMANREADING_PART1_DATA_ID, 512, &data[0]);
  roveComm.write(RC_RAMANBOARD_RAMANREADING_PART2_DATA_ID, 512, &data[512]);
  roveComm.write(RC_RAMANBOARD_RAMANREADING_PART3_DATA_ID, 512, &data[1024]);
  roveComm.write(RC_RAMANBOARD_RAMANREADING_PART4_DATA_ID, 512, &data[1536]);
}


void pinInitializations()
{
  pinMode(EN_OUT, OUTPUT);
  digitalWrite(EN_OUT, EN_DEFAULT);

  pinMode(M0_OUT, OUTPUT);
  digitalWrite(M0_OUT, M0_DEFAULT);

  pinMode(M1_OUT, OUTPUT);
  digitalWrite(M1_OUT, M1_DEFAULT);

  pinMode(M2_OUT, OUTPUT);
  digitalWrite(M2_OUT, M2_DEFAULT);

  pinMode(STEP_OUT, OUTPUT);
  digitalWrite(STEP_OUT, STEP_DEFAULT);

  pinMode(DIR_OUT, OUTPUT);
  digitalWrite(DIR_OUT, DIR_DEFAULT);

  pinMode(STDBY_OUT, OUTPUT);
  digitalWrite(STDBY_OUT, STDBY_DEFAULT);

  pinMode(DATA_IN, INPUT);

  pinMode(LIMIT_SWITCH_IN, INPUT);
}