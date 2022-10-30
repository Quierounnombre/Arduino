#define zumbador 11
#define espera 10
#define boton 13

bool state = true;

void setup() {
  pinMode(boton, 0);
  pinMode(zumbador, 1);
}

void loop() {
  if (digitalRead(boton) == 0)
  {
    if(state == false)
      state = true;
    else
      state = false;
  delay(300);
  }
  if (state == true)
  {
    digitalWrite(zumbador, 1);
  }
  else
  {
    digitalWrite(zumbador, 0);
  }
}
