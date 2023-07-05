template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define Ts  0.1

// Constantes PID
const double a[] = {0.5341, 0.01254, -0.5215};
const double b[] = {1, -1.647, 0.6469};

// Time delay vectors
double X[3], e[3];

// Global variables
double sP = 0;
double Sys_out;

Adafruit_MCP4725 DACn;

double Compute_Cz();

void setup() {
  for(int i = 0; i < 3; i++)
    X[i] = e[i] = 0;
  
  DACn.begin(0x60);
  DACn.setVoltage(0, false);

  Serial.begin(115200);

  Serial << "SetPoint, Error, Control, Salida\n";
}

void loop() {
  if(Serial.available())
    sP = Serial.readStringUntil('\n').toFloat(); // De 0 a 5v

  Sys_out = analogRead(A1); // Salida en Escala de 0 a 1023
  Sys_out *= 5.0/1023; // Reescalado de 0 a 5v

  double out = Compute_Cz(); // Salida en Escala de 0 a 5v
  double dac_out = map(out, 0, 5, 0, 4095); // Escalamos de 0 a 4095 para el DAC

  DACn.setVoltage(dac_out, false);

  Serial << sP << ", " << e[2] << ", " << out << ", " << Sys_out << '\n';

  delay(1000*Ts);
}

double Compute_Cz(){
  e[2] = sP - Sys_out; // Error en escala de 0 a 5V

  X[2] = (a[0]*e[2] + a[1]*e[1] + a[2]*e[0]) - (b[1]*X[1] + b[2]*X[0]);
  X[2] /= b[0];

  // Avanzamos en el tiempo
  e[0] = e[1]; X[0] = X[1];
  e[1] = e[2]; X[1] = X[2];

  if(X[2] > 5) return 5;
  if(X[2] < 0) return 0;
  return X[2];
}
