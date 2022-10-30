#include <SR04.h>
#define TRIGER_PIN 7
#define ECHO_PIN 6

SR04 UltraSonidos = SR04(ECHO_PIN, TRIGER_PIN);
long echoreturn = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  echoreturn = UltraSonidos.Distance();
  Serial.print(echoreturn);
  Serial.print("cm\n");
  delay(1000);

}
