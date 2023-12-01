#define power_pin 5  // Pin para alimentar el sensor de salinidad

int x[] = { 1, 2, 3 }; //Valores que van a cambiar con la calibración 
//int y[] = { 0g, 10g, 20g }; //Los gramos de sal utilizados


void setup() {
  pinMode(power_pin, OUTPUT);
  Serial.begin(9600);
  calibracion();
}

void calibracion() {
  int adc0;
  Serial.println("Meter 0 gramos y pulsa A");
  while (Serial.available() == 0) {
    delay(1000);
  }
  if (Serial.available() > 0) {
    int n_bytes = Serial.available();
    char a = Serial.read();
    if (a == 'A') {
      
      digitalWrite(power_pin, HIGH);
      delay(100);
      
      adc0 = analogRead(A0);
      digitalWrite(power_pin, LOW);
      delay(100);

      x[0] = adc0;
      Serial.print("Valor =");
      Serial.println(x[0]);
    }
    for (int i = 1; i < n_bytes; i++) {
      Serial.read();
    }
  }
  delay(1000);

  Serial.println("Meter 10 gramos y pulsa B");
  while (Serial.available() == 0) {
    delay(1000);
  }
  if (Serial.available() > 0) {
    int n_bytes = Serial.available();
    char b = Serial.read();
    if (b == 'B') {
      digitalWrite(power_pin, HIGH);
      delay(100);
      
      adc0 = analogRead(A0);
      digitalWrite(power_pin, LOW);
      delay(100);
  
      x[1] = adc0;
      Serial.print("Valor =");
      Serial.println(x[1]);
    }
    for (int i = 1; i < n_bytes; i++) {
      Serial.read();
    }
  }
  delay(1000);

  Serial.println("Meter 20 gramos y pulsa C");
  while (Serial.available() == 0) {
    delay(1000);
  }
  if (Serial.available() > 0) {
    int n_bytes = Serial.available();
    char c = Serial.read();
    if (c == 'C') {
      digitalWrite(power_pin, HIGH);
      delay(100);
      
      adc0 = analogRead(A0);
      digitalWrite(power_pin, LOW);
      delay(100);

      x[2] = adc0;
      Serial.print("Valor =");
      Serial.println(x[2]);
    }
    for (int i = 1; i < n_bytes; i++) {
      Serial.read();
    }
  }
  delay(1000);
}

//Función de salinidad
float interpolate(int* x, int adc0) {
  float salinidad = 0;
  
  float l1 = (10*(adc0-x[0]))/(x[1]-x[0]) * (adc0-x[2])/(x[1]-x[2]);
  
  float l2 = (20*(adc0-x[0]))/(x[2]-x[0]) * (adc0-x[1])/(x[2]-x[1]);

  salinidad = l1 + l2;

  return salinidad;
}
void loop() {
  int16_t adc0;



  // Alimentamos la sonda con un tren de pulsos
  digitalWrite(power_pin, HIGH);
  delay(100);

  // Leemos cuando hay un nivel alto
  adc0 = analogRead(A0);
  digitalWrite(power_pin, LOW);
  delay(100);

  // Realizamos el cálculo de la salinidad con Langrange
  float ressalinidad = interpolate(x, adc0);

  // presentamos lectura
  Serial.print("Lectura digital = ");
  Serial.println(adc0, DEC);
  Serial.print("Salinidad = ");
  Serial.print(ressalinidad, 2);  
  Serial.println("g");
  delay(1000);  
}
