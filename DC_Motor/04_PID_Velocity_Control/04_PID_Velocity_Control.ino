template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include "MotorDC.h"
#include "MBED_RPi_Pico_TimerInterrupt.h"

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor75(10, 9, 8, 2, 3);
int dC75 = 0;

const int PPR75 = 3591.84;

// Prototipos
void ISR_Velocity();
void ISR75_A();
void ISR75_B();
double Compute_Cz();

#define TIMER0_INTERVAL_MS 5
MBED_RPI_PICO_Timer ITimer0(0);

// Global Variables
double X[3], e[3];
double a[] = {0.743, -1.342, 0.6056};
double b[] = {1, -1.91, 0.9098};
double Cz;

long t_start = 0;

void setup(){
  for(int i = 0; i < 3; i++)
    X[i] = e[i] = 0;
  
  // Timer Initialization
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, ISR_Velocity);

  // Motor Initialization
  Motor75.begin(PPR75);
  Motor75.setup(ISR75_A, ISR75_B);
  Motor75.start(true);

  Serial.begin(115200);

  while(!Serial.available());

  t_start = millis();
}

void loop(){
  if(Serial.available()){
    dC75 = Serial.readStringUntil('\n').toInt();
    if(dC75 >= 0)
      Motor75.start(true);
    else
      Motor75.start(false);
  }
  Cz= map(Compute_Cz(), 0, 130, 0, 1023);
  Motor75.set_PWM(Cz);
  Serial << millis() - t_start << ',' << Cz << ',' << Motor75.get_RPM()<< '\n';
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

double Compute_Cz(){
  e[2] = dC75 - Motor75.get_RPM();
  X[2] = (a[0]*e[2] + a[1]*e[1] + a[2]*e[0]) - (b[1]*X[1] + b[2]*X[0]);
  X[2] /= b[0];

  // Avanzamos en el tiempo
  e[0] = e[1]; X[0] = X[1];
  e[1] = e[2]; X[1] = X[2];

  if(X[2] >= 1023) return 1023;
  else if(X[2] < 0) return 0;
  else if (X[2] <= -1023) return -1023;
  return X[2];
}