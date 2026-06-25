#include "telegram.h"
#include "Arduino.h"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

void iniciarTelegram() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  client.setInsecure();  // sin verificación SSL
}

void enviarMensaje(String mensaje) {
  bot.sendMessage(CHAT_ID, mensaje, "");
}

void enviarResumen(unsigned long tiempoTotal, unsigned long tiempoMala) {
  // convertir a segundos
  unsigned long total_s = tiempoTotal / 1000;
  unsigned long mala_s = tiempoMala / 1000;

  // evita división por cero
  if (total_s == 0) total_s = 1;

  // asegurarse que mala no supere total
  if (mala_s > total_s) mala_s = total_s;

  int porcentajeMala = (mala_s * 100) / total_s;
  int porcentajeBuena = 100 - porcentajeMala;

  String msg = "📊 *Resumen de sesión*\n";
  msg += "⏱ Tiempo total: " + String(total_s / 60) + " min " + String(total_s % 60) + " seg\n";
  msg += "❌ Tiempo en mala postura: " + String(mala_s / 60) + " min " + String(mala_s % 60) + " seg\n";
  msg += "✅ Porcentaje buena postura: " + String(porcentajeBuena) + "%\n";

  bot.sendMessage(CHAT_ID, msg, "Markdown");
}