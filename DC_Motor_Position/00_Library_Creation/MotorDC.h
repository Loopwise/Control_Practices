#pragma once

#ifndef MOTORDC_h
#define MOTORDC_h

#ifndef tMax
#define tMax 5
#endif

class MotorDC{
private:
  byte EN1, EN2, ENM;
  byte ENCA, ENCB;
  unsigned int t = 0;
  int pos_diff = 0;
  float PPR, velocity = 0, velocityB = 0;
  float RPM = 0;
  int signo = 1;

public:
  volatile int contA = 0;
  volatile int contB = 0;
  volatile float pos = 0;

  MotorDC();
  MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB);

  void begin(float PPR);
  void setup(void (*ISR_A)(void), void (*ISR_B)(void));
  void start(bool state);

  void update_States();
  void set_PWM(int value);
  int get_RawPosition();
  float get_Velocity();

  float get_RPM();
  float get_Position();
};

#endif