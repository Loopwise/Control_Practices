template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DACn DAC1
#define fs 10

// Constantes PID
const double a[] = {0.5341, 0.01254, -0.5215};
const double b[] = {1, -1.647, 0.6469};

// Time delay vectors
double X[3], e[3];

// Global variables
double sP = 700;

double Compute_Cz();

void setup() {
  for(int i = 0; i < 3; i++)
    X[i] = e[i] = 0;
  
  pinMode(DACn, OUTPUT);
  analogWriteResolution(12);
  analogReadResolution(12);

  analogWrite(DACn,0);
  Serial.begin(115200);

  delay(1000);
}

void loop() {
  if(Serial.available()){
    sP = Serial.readStringUntil('\n').toInt();
  }
  double out = Compute_Cz();
  analogWrite(DACn, out);
  Serial << sP << ", " << e[2] << ", " << out << ", " << analogRead(A1) << '\n';
  delay(1000/fs);
}

double Compute_Cz(){
  e[2] = sP - analogRead(A1);
  X[2] = (a[0]*e[2] + a[1]*e[1] + a[2]*e[0]) - (b[1]*X[1] + b[2]*X[0]);
  X[2] /= b[0];

  // Avanzamos en el tiempo
  e[0] = e[1]; X[0] = X[1];
  e[1] = e[2]; X[1] = X[2];

  if(X[2] > 4095) return 4095;
  if(X[2] < 0) return 0;
  return X[2];
}
