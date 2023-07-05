#pragma once

#ifndef MOTORDC_h
#define MOTORDC_h

#ifndef tMax
#define tMax 5
#endif

#include <Encoder.h>

class MotorDC{
private:
  // Atributos Puente H y Encoder
  byte EN1, EN2, ENM;
  Encoder *myEnc = new Encoder(100, 100);

  // Atributos de Cálculo
  unsigned int t = 0;
  float CPR;

  // Atributos de 
  volatile float pos = 0;
  volatile float RPM = 0;

public:
  // Constuctores
  MotorDC();
  MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB);

  // Métodos Generales
  void begin(float CPR);
  void set_PWM(int value);

  // Método de Actualización General
  void update_States();
  
  // Métodos de Posición
  int get_RawPosition();
  float get_Position();

  // Métodos de Velocidad
  float get_RPM();
  float get_Velocity();
};

#endif