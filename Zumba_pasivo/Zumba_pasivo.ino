#include <pitches.h>
#define zumbador 11
#define espera 1000
#define boton 13

int melody[] = {
  NOTE_C4, NOTE_A5};
bool state = true;

void setup() {
  pinMode(boton, 0);
  pinMode(zumbador, 1);
}

void loop() {
  if (digitalRead(boton) == 0)
  {
    state = true;
  delay(300);
  }
  if (state == true)
  {
    for (int i = 0; i < (sizeof(melody) - 1); i++)
    {
      tone(11, melody[i], espera);
      delay(espera + 1);
    }
    state = false;
  }
}
