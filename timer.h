#ifndef TIMER_H
#define TIMER_H

#define UMBRAL_TOR 10.0
#define UMBRAL_LUM 10.0
#define TIEMPO_ALERTA 5000

extern unsigned long tiempoMalaPostura;
extern bool enMalaPostura;
extern unsigned long tiempoTotalInicio;      
extern unsigned long tiempoAcumuladoMala;   

void actualizarTimer(float desviacionTor, float desviacionLum);

#endif