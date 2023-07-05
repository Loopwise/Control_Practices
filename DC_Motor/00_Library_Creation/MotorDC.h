#pragma once

#ifndef MOTORDC_h
#define MOTORDC_h

#ifndef tMax
#define tMax 5
#endif

#include <Encoder.h>

class MotorDC{
private:
  byte EN1, EN2, ENM;
  Encoder *myEnc = new Encoder(100, 100);
  unsigned int t = 0;
  int pos_diff = 0;
  float CPR, velocity = 0;
  float RPM = 0;

public:
  volatile int cont = 0;
  volatile float pos = 0;

  MotorDC();
  MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB);

  void begin(float CPR);
  void setup(void (*ISR_CHANGE)(void));

  void update_States();
  void set_PWM(int value);
  
  int get_RawPosition();
  float get_Position();

  float get_Velocity();
  float get_RPM();
  
};

#endif