#include <Arduino.h>
#include "MotorDC.h"

MotorDC::MotorDC(){}

MotorDC::MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB){
  this -> ENM = ENM;
  this -> EN1 = EN1;
  this -> EN2 = EN2;
  this -> ENCA = ENCA;
}

void MotorDC::begin(float PPR){
  pinMode(this -> ENM, OUTPUT);
  pinMode(this -> EN1, OUTPUT);
  pinMode(this -> EN2, OUTPUT);

  pinMode(this -> ENCA, INPUT);
  pinMode(this -> ENCB, INPUT);

  this -> PPR = PPR;
}

void MotorDC::setup(void (*ISR_A)(void), void (*ISR_B)(void)){
  attachInterrupt(digitalPinToInterrupt(this -> ENCA), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(this -> ENCB), ISR_B, CHANGE);

  interrupts();
}

void MotorDC::start(bool state){
  digitalWrite(this -> EN1, state);
  digitalWrite(this -> EN2, !state);
  digitalWrite(this -> ENM, LOW);

  if(state)
    this -> signo = 1;
  else
    this -> signo = -1;
}

void MotorDC::set_PWM(int value){
  if(value < 0){
    digitalWrite(this -> EN1, LOW);
    digitalWrite(this -> EN2, HIGH);
    analogWrite(this -> ENM, value);
  }else{
    digitalWrite(this -> EN1, HIGH);
    digitalWrite(this -> EN2, LOW);
    analogWrite(this -> ENM, value);
  }
}

void MotorDC::update_States(){
  int dt = millis() - (this -> t);

  if(dt < tMax) return;

  noInterrupts();

  int pos_diff = (this -> signo) * ((this -> contA) + (this -> contB));
  this -> pos += pos_diff;

  (this -> contA) = (this -> contB) = 0;

  this -> RPM = 2.0*pos_diff/(this -> PPR); // Revoluciones en tms
  this -> RPM *= 60.0*1000.0/dt; // Revoluciones por Minuto
  this -> velocity = 2.0*PI/60.0*(this -> RPM); // Rad/s
  this -> t = millis();

  interrupts();
}

int MotorDC::get_RawPosition(){
  return (this -> pos);
}

float MotorDC::get_RPM(){
  return this -> RPM;
}

float MotorDC::get_Velocity(){
  return this -> velocity;
}

float MotorDC::get_Position(){
  return (this -> pos)/(this -> PPR);
}