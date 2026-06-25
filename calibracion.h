#ifndef CALIBRACION_H
#define CALIBRACION_H

#include <Wire.h>

extern float pitchNeutroTor;
extern float pitchNeutroLum;
extern bool calibrado;

void initADXL(TwoWire &wire);
float getPitch(TwoWire &wire);
void calibrar(TwoWire &wireTor, TwoWire &wireLum);

#endif