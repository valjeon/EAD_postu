#include "timer.h"
#include "alertas.h"
#include "Arduino.h"
#include "telegram.h"

unsigned long tiempoTotalInicio = 0;
unsigned long tiempoAcumuladoMala = 0;
unsigned long inicioDeMala = 0;

unsigned long tiempoMalaPostura = 0;
bool enMalaPostura = false;

void actualizarTimer(float desviacionTor, float desviacionLum) {

  if (tiempoTotalInicio == 0) {
    tiempoTotalInicio = millis();
    Serial.println("Timer total iniciado");
  }

  bool malaPostura = abs(desviacionTor) > UMBRAL_TOR || abs(desviacionLum) > UMBRAL_LUM;

  if (malaPostura) {
    if (!enMalaPostura) {
      tiempoMalaPostura = millis();
      inicioDeMala = millis();
      enMalaPostura = true;
    }

    unsigned long tiempoTranscurrido = millis() - tiempoMalaPostura;
    Serial.print("Mala postura: ");
    Serial.print(tiempoTranscurrido / 1000);
    Serial.println("s");

    if (tiempoTranscurrido >= TIEMPO_ALERTA) {
      if (abs(desviacionTor) > UMBRAL_TOR) {
        vibraTorax();
      }
      if (abs(desviacionLum) > UMBRAL_LUM) {
        vibraLumbar();
      }
      actualizarBuzzer(true, tiempoTranscurrido);
    } else {
      silenciarAlertas();
      actualizarBuzzer(false, 0);
    }

  } else {
    if (enMalaPostura) {
      actualizarBuzzer(false, 0);
      silenciarAlertas();
      tiempoAcumuladoMala += millis() - inicioDeMala;  // ahora sí tiene valor correcto
      Serial.print("Tiempo acumulado mala postura: ");
      Serial.print(tiempoAcumuladoMala / 1000);
      Serial.println("s");
      Serial.println("Postura corregida ✓");
    }
    enMalaPostura = false;
    tiempoMalaPostura = 0;
  }
}