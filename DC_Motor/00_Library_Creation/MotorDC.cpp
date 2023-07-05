#include <Arduino.h>
#include <Encoder.h>
#include "MotorDC.h"

MotorDC::MotorDC(){}

MotorDC::MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB){
  this -> ENM = ENM;
  this -> EN1 = EN1;
  this -> EN2 = EN2;
  this -> myEnc = new Encoder(ENCA, ENCB);
}

void MotorDC::begin(float CPR){
  pinMode(this -> ENM, OUTPUT);
  pinMode(this -> EN1, OUTPUT);
  pinMode(this -> EN2, OUTPUT);

  this -> CPR = CPR;
}

void MotorDC::set_PWM(int value){
  if(value > 0){
    digitalWrite(this -> EN1, LOW);
    digitalWrite(this -> EN2, HIGH);
  }else{
    digitalWrite(this -> EN1, HIGH);
    digitalWrite(this -> EN2, LOW);
  }
  analogWrite(this->ENM, abs(value));
}

void MotorDC::update_States(){
  int dt = millis() - (this -> t);

  if(dt < tMax) return;

  noInterrupts();
  int pos_diff = (this -> myEnc -> read()) - (this -> pos);
  this -> pos = this -> myEnc -> read();

  this -> RPM = pos_diff/(this -> CPR); // Revoluciones en tms
  this -> RPM *= 60.0*1000.0/dt; // Revoluciones por Minuto
  
  this -> t = millis();

  interrupts();
}

int MotorDC::get_RawPosition(){
  return this -> pos;
}

// Velocity (RPM)
float MotorDC::get_RPM(){
  return this -> RPM;
}

// Velocity (Rad/s)
float MotorDC::get_Velocity(){
  return 2.0*PI/60.0*(this -> RPM);
}

float MotorDC::get_Position(){
  return (this -> pos)/(this -> CPR);
}