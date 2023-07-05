template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include "MotorDC.h"

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor(5, 7, 6, 2, 3);
int dC = 0;

// CPR = 4*PPR*Ratio;
//const int CPR = 4*12*75;
const int CPR = 4*7*30;

// Prototipos
void ISR_Velocity();

// Global Variables
long t_start = 0;

void setup(){ 
  Motor.begin(CPR);

  Serial.begin(115200);

  while(!Serial.available());

  t_start = millis();
}

void loop(){
  if(Serial.available()){
    dC = Serial.readStringUntil('\n').toInt();
    Motor.set_PWM(dC);
  }
  ISR_Velocity();
  Serial << dC << ',' << Motor.get_RPM() <<'\n';
  delay(5);
}

void ISR_Velocity(){
  Motor.update_States();
}