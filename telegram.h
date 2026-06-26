#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID     "WIFI"
#define WIFI_PASSWORD "PASSWORD"
#define BOT_TOKEN     "TOKEN"
#define CHAT_ID       "CHAT_ID"
// el token del bot y el chat_id se deben configurar para el telegram del usuario

void iniciarTelegram();
void enviarMensaje(String mensaje);
void enviarResumen(unsigned long tiempoTotal, unsigned long tiempoMala);

#endif
