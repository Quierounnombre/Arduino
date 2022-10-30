long digito1 = 0;
long digito2 = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  if ((Serial.available() - 1) > 0) //Compruba si hay algo en el buffer
  {
    if(digito1 == 0)
      {
        digito1 = Serial.parseInt(); //atoi para serial, hacen lo mismo
        Serial.print("Primer numero introducido: ");
        Serial.println(digito1);
      }
    else if(digito2 == 0)
      {
        digito2 = Serial.parseInt();
        Serial.print("Segundo numero introducido: ");
        Serial.println(digito2);
      }
    else
      {
        digito1 = digito1 + digito2;
        Serial.print("El resultado de la suma es: ");
        Serial.println(digito1);
        digito1 = 0;
        digito2 = Serial.read();//limpia el buffer y evita sobre machacar la memoria de digito1.
        digito2 = 0;
      }
  }
} 
