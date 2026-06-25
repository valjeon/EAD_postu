#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID     "valen"
#define WIFI_PASSWORD "somisomi"
#define BOT_TOKEN     "8879900282:AAHFds_jG-bmP921XIs8T5O00Xst3EJNQPc"
#define CHAT_ID       "8651092577"
// el token del bot y el chat_id se deben configurar para el telegram del usuario

void iniciarTelegram();
void enviarMensaje(String mensaje);
void enviarResumen(unsigned long tiempoTotal, unsigned long tiempoMala);

#endif