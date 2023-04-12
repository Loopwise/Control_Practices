template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define DACn DAC1
#define fs 10 // Frecuencia de muestreo
#define tf 40 // Tiempo final
#define tc 10
#define tm 20
#define ta 30

const int N = tf*fs + 1; // Número de muestras

int i = 0;
long t_start;
long pwm = 0;

void setup() {
  analogWriteResolution(12);
  analogReadResolution(12);

  pinMode(DACn, OUTPUT);
  analogWrite(DACn, 0); 
  Serial.begin(115200);
  t_start = millis();

  delay(2500);
}

void loop(){
  if(i > N) return;
  for(i = 0; i <= N; i++){
    if(i == 0)
      pwm = 0;
    else if(i == tc*fs)
      pwm = 1023;
    else if(i == tm*fs)
      pwm = 2047;
    else if(i == ta*fs)
      pwm = 4095;
    analogWrite(DACn, pwm); // 12 bits resolution -> Max 4095
    Serial << i << ", " << pwm << ", " << analogRead(A0) << ", " << analogRead(A1) << '\n';
    delay(1000/fs);
  }
}
