template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include "MotorDC.h"
#include "MBED_RPi_Pico_TimerInterrupt.h"

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor75(10, 9, 8, 2, 3);
int dutyCycle = 0;
int dC75 = 0;

const int PPR75 = 3591.84;

// Prototipos
void ISR_Velocity();
void ISR75_A();
void ISR75_B();

#define TIMER0_INTERVAL_MS 5
MBED_RPI_PICO_Timer ITimer0(0);

// Global Variables
long t_start = 0;

void setup(){ 
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, ISR_Velocity);
  Motor75.begin(PPR75);
  Motor75.setup(ISR75_A, ISR75_B);
  Motor75.start(true);

  Serial.begin(115200);

  while(!Serial.available());
  //delay(1000);

  t_start = millis();
}

void loop(){
  if(Serial.available()){
    dC75 = Serial.readStringUntil('\n').toInt();
    if(dC75 >= 0)
      Motor75.start(true);
    else
      Motor75.start(false);
      
    dC75 = abs(dC75);

    Motor75.set_PWM(dC75);
  }
  Serial << millis() - t_start << ',' << dC75 << ',' << Motor75.get_RPM()<< '\n';
  delay(5);
}

void ISR_Velocity(uint alarm_num){
  TIMER_ISR_START(alarm_num);
  Motor75.update_States();
  TIMER_ISR_END(alarm_num);
}

void ISR75_A(){
  Motor75.contA++;
}

void ISR75_B(){
  Motor75.contB++;
}