#ifndef ALERTAS_H
#define ALERTAS_H

#define PIN_BUZZER     32
#define PIN_MOTOR_TOR  33 
#define PIN_MOTOR_LUM  26

#define DURACION_PITIDO  400
#define PAUSA_PITIDOS    200

void iniciarAlertas();
void vibraTorax();
void vibraLumbar();
void silenciarAlertas();
void actualizarBuzzer(bool malaPostura, unsigned long tiempoEnMala);

#endif