template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include "MotorDC.h"

#define ENDRV 7

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor75(4, 5, 6, 2, 3);
int dutyCycle = 0;
int dC75 = 0;

const int PPR75 = 3591.84;

// Prototipos
void ISR75_A();
void ISR75_B();

void setup(){ 
  pinMode(ENDRV, OUTPUT);
  digitalWrite(ENDRV, HIGH);

  Motor75.begin(PPR75);
  Motor75.setup(ISR75_A, ISR75_B);
  Motor75.start(true);

  Serial.begin(115200);
}


void loop(){
  if(Serial.available()){
    dC75 = Serial.readStringUntil('\n').toInt();
    if(dC75 >= 0)
      Motor75.start(true);
    else
      Motor75.start(false);
      
    dC75 = abs(dC75);

    Motor75.set_DutyCycle(dC75);

    for(int i = 0; i < 10; i++)
      delay(50);
  }
  dutyCycle = 0;
  Serial << "Raw Position Motor 75:" << Motor75.get_RawPosition() << '\n';
  Motor75.set_DutyCycle(dutyCycle);

}

void ISR75_A(){
  Motor75.contA++;
}

void ISR75_B(){
  Motor75.contB++;
}