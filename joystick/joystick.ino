#define Keypin 4
#define Xpin 3
#define Ypin 4

void setup() {
  pinMode(Keypin, 0);
  digitalWrite(Keypin, 1); //Pasa corriente por el boton permitiendo la detección del boton central por corte de corriente
  Serial.begin(9600);
}

void loop() {
  //Display de información obtenido de la documentación
  Serial.print("Switch:  ");
  Serial.print(digitalRead(Keypin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(Xpin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Ypin));
  Serial.print("\n\n");
  delay(1000);
}
