#include <Wire.h>
#include <Arduino.h>
#include "calibracion.h"
#include "timer.h"
#include "alertas.h"
#include "telegram.h"

#define PIN_BOTON_CALIBRE 13
#define PIN_LED 23
#define PIN_BOTON_RESUMEN 4

extern float pitchNeutroTor;
extern float pitchNeutroLum;
extern bool calibrado;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTON_RESUMEN, INPUT_PULLUP);
  pinMode(PIN_BOTON_CALIBRE, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  Wire1.begin(21,22);   //21 SDA, 22 SCL
  Wire.begin(27,16);
  initADXL(Wire);
  initADXL(Wire1);
  iniciarAlertas();
  iniciarTelegram();
  Serial.println("Presioná el botón para calibrar");
  enviarMensaje("Hola soy Postu!");
}

void loop() {
  if (digitalRead(PIN_BOTON_CALIBRE) == LOW) {
    delay(50);  // anti-rebote
    calibrar(Wire, Wire1);
    while (digitalRead(PIN_BOTON_CALIBRE) == LOW);  // espera a que se suelte el botón
  }

  if (digitalRead(PIN_BOTON_RESUMEN) == LOW) {
    delay(50);  // anti-rebote
    enviarResumen(millis() - tiempoTotalInicio, tiempoAcumuladoMala);
    while (digitalRead(PIN_BOTON_RESUMEN) == LOW);  // espera a que se suelte el botón
  }

  if (!calibrado) { // mientras que no se haya calibrado la postura referencial, el LED titila
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    delay(200);
    return;
  }

  float desviacionTor = getPitch(Wire) - pitchNeutroTor;
  float desviacionLum = getPitch(Wire1) - pitchNeutroLum;
  Serial.print("DesviacionTor: ");
  Serial.print(desviacionTor);
  Serial.print("  DesviacionLum: ");
  Serial.println(desviacionLum);
  actualizarTimer(desviacionTor, desviacionLum);
  delay(200);
}