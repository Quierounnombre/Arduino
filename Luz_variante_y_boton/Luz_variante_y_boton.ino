#define rojo 6
#define verde 9
#define azul 10
#define espera 15
#define boton 13

void EnciendeRojo(void)
{
  for (int fade = 0 ; fade <= 255; fade += 5)
  {
    analogWrite(rojo, fade);
    delay (espera);
  }
}

void EnciendeAzul(void)
{
  for (int fade = 0 ; fade <= 255; fade += 5)
  {
    analogWrite(azul, fade);
    delay (espera);
  }
}

void EnciendeVerde(void)
{
  for (int fade = 0 ; fade <= 255; fade += 5)
  {
    analogWrite(verde, fade);
    delay (espera);
  }
}

void ApagaRojo(void)
{
  for (int fade = 255; fade >= 0; fade -= 5)
  {
    analogWrite(rojo, fade);
    delay (espera);
  }
}

void ApagaAzul(void)
{
  for (int fade = 255; fade >= 0; fade -= 5)
  {
    analogWrite(azul, fade);
    delay (espera);
  }
}

void ApagaVerde(void)
{
  for (int fade = 255; fade >= 0; fade -= 5)
  {
    analogWrite(verde, fade);
    delay (espera);
  }
}

void EnciendeAmbos(void)
{
  for (int fade = 0; fade <= 255; fade += 5)
  {
    analogWrite(rojo, fade);
    analogWrite(verde, fade);
    delay (espera);
  }
}
void setup() {
  pinMode(rojo, 1);
  pinMode(verde, 1);
  pinMode(azul, 1);
  pinMode(boton, 0);
}

void loop()
{
  if (digitalRead(boton) == LOW)
  {
    EnciendeRojo();
    EnciendeAzul();
    ApagaRojo();
    EnciendeVerde();
    ApagaAzul();
    EnciendeAmbos();
    EnciendeAzul();
    ApagaVerde();
    ApagaAzul();
  }
  else
  {
    digitalWrite(rojo, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(azul, LOW);
  }
}
