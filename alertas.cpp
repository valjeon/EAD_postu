#include "alertas.h"
#include "Arduino.h"

void iniciarAlertas() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_MOTOR_TOR, OUTPUT);
  pinMode(PIN_MOTOR_LUM, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_MOTOR_TOR, LOW);
  digitalWrite(PIN_MOTOR_LUM, LOW);
}

void vibraTorax() {
  digitalWrite(PIN_MOTOR_TOR, HIGH);
}

void vibraLumbar() {
  digitalWrite(PIN_MOTOR_LUM, HIGH);
}

void silenciarAlertas() {
  digitalWrite(PIN_MOTOR_TOR, LOW);
  digitalWrite(PIN_MOTOR_LUM, LOW);
}

unsigned long calcularIntervalo(unsigned long tiempoEnMala) {
  if (tiempoEnMala < 30000) return 10000;
  else if (tiempoEnMala < 60000) return 5000;
  else return 2000;
}

void actualizarBuzzer(bool malaPostura, unsigned long tiempoEnMala) {
  static int estado = 0;
  static unsigned long t = 0;
  static unsigned long ultimaSonadaT = 0;
  static bool sonoPrimera = false;

  if (!malaPostura) {
    digitalWrite(PIN_BUZZER, LOW);
    estado = 0;
    ultimaSonadaT = 0;
    sonoPrimera = false;
    return;
  }

  unsigned long ahora = millis();
  unsigned long intervalo = calcularIntervalo(tiempoEnMala);

  if (estado == 0) {
    if (!sonoPrimera || ahora - ultimaSonadaT >= intervalo) {
      estado = 1;
      t = ahora;
    }
    return;
  }

  switch (estado) {
    case 1:
      digitalWrite(PIN_BUZZER, HIGH);
      if (ahora - t >= DURACION_PITIDO) {
        digitalWrite(PIN_BUZZER, LOW);
        estado = 2;
        t = ahora;
      }
      break;
    case 2:
      if (ahora - t >= PAUSA_PITIDOS) {
        estado = 3;
        t = ahora;
      }
      break;
    case 3:
      digitalWrite(PIN_BUZZER, HIGH);
      if (ahora - t >= DURACION_PITIDO) {
        digitalWrite(PIN_BUZZER, LOW);
        estado = 0;
        ultimaSonadaT = ahora;
        sonoPrimera = true;
      }
      break;
  }
}