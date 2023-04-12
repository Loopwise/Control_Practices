template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DACn DAC1
#define fs 10 // Frecuencia de muestreo
#define tf 80 // Tiempo final
#define ts 20

const int N = tf*fs + 1; // Número de muestras

int i = 0;
long t_start;
long pwm = 0;

void setup() {
  pinMode(DACn, OUTPUT);
  analogWriteResolution(12);
  analogReadResolution(12);
  
  analogWrite(DACn,0);  // Enables DAC0

  Serial.begin(115200);
  t_start = millis();

  delay(2500);
}

void loop(){
  if(i > N) return;
  for(i = 0; i <= N; i++){
    if(i == 0)
      pwm = 0;
    else if(i == ts*fs)
      pwm = 1023;
    analogWrite(DACn, pwm);
    Serial << i << ", " << pwm << ", " << analogRead(A0) << ", " << analogRead(A1) << '\n';
    delay(1000/fs);
  }
}
