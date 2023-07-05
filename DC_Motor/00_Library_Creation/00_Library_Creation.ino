template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include <Encoder.h>
#include "MotorDC.h"

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor(5, 7, 6, 2, 3);
int dC = 0;

// CPR = 2*PPR*Ratio;
//const int CPR = 2*12*75;
const int CPR = 2*7*30;

// Prototipos
void ISR_Velocity();
void ISR75_A();
void ISR75_B();

// Global Variables
long t_start = 0;

void setup(){ 
  Motor.begin(CPR);
  Motor.setup(ISR_CHANGE);

  Serial.begin(115200);

  while(!Serial.available());
  //delay(1000);

  t_start = millis();
}

void loop(){
  if(Serial.available()){
    dC = Serial.readStringUntil('\n').toInt();
    Motor.set_PWM(dC);
  }
  ISR_Velocity();
  Serial << dC << ',' << Motor.get_RPM() <<'\n';
  delay(500);
}

void ISR_Velocity(){
  Motor.update_States();
}

void ISR_CHANGE(){
  Motor.cont++;
}