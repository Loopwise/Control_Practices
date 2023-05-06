template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#define Pin_OUT 7 // Salida del Arduino -> Entrada al RC
#define Sys_IN A0 // Realimentación del Pin_OUT
#define Sys_OUT A1 // Realimentación del V_Condensador

const double tsim = 360; // Tiempo de Simulación
const double tk = 20; // Tiempo de inicio del Step
const double T = 0.1; // Cada cuánto tiempo se dará (ms)

const double N = tsim/T + 1;

int i = 0;

void setup() {
  pinMode(Pin_OUT, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if( i > N)
    return;
  
  for(i = 0; i < N ; i++){
    if( i == tk/T)
      digitalWrite(Pin_OUT, HIGH);
    
    Serial << i << ", " << analogRead(Sys_IN) << ", " << analogRead(Sys_OUT) << '\n';

    delay(T*1000);
  }

  digitalWrite(Pin_OUT, LOW);
}
