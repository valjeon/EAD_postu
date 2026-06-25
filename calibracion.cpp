#include "calibracion.h"
#include <Arduino.h>
#include <math.h>
#include "telegram.h"

#define ADXL345_ADDR 0x53
#define OFFSET_X -0.74
#define OFFSET_Z -0.82
#define SCALE 0.0039 * 9.81

//inicialización de variables
float pitchNeutroTor = 0;
float pitchNeutroLum = 0;
bool calibrado = false;

void readAccel(TwoWire &wire, int &x, int &y, int &z) { //recibe como variables de entrada las coordenadas
  wire.beginTransmission(ADXL345_ADDR);
  wire.write(0x32);
  wire.endTransmission(false);
  wire.requestFrom(ADXL345_ADDR, 6);
  x = (int16_t)(wire.read() | (wire.read() << 8));
  y = (int16_t)(wire.read() | (wire.read() << 8));
  z = (int16_t)(wire.read() | (wire.read() << 8));
}

float getPitch(TwoWire &wire) {
  int x, y, z;
  readAccel(wire, x, y, z);
  float ax = x * SCALE + OFFSET_X;
  float az = z * SCALE + OFFSET_Z;
  return atan2(az, ax) * 180.0 / M_PI; // devuelve el valor en grados 
}

void initADXL(TwoWire &wire) { //inicializa cada sensor escribiendo directamente sobre el bus I2C
  wire.beginTransmission(ADXL345_ADDR);
  wire.write(0x2D); //selecciona el registro 0x2D
  wire.write(0x08); //escribe el valor 0x08, que activa el modo de medición continua del sensor
  wire.endTransmission();
  
}

void calibrar(TwoWire &wireTor, TwoWire &wireLum) {
  float sumaTor = 0, sumaLum = 0;
  for (int i = 0; i < 20; i++) {
    sumaTor += getPitch(wireTor);
    sumaLum += getPitch(wireLum);
    delay(50);
  }
  pitchNeutroTor = sumaTor / 20.0;
  pitchNeutroLum = sumaLum / 20.0;
  calibrado = true;
  Serial.print("Torácica neutra: ");
  Serial.println(pitchNeutroTor);
  Serial.print("Lumbar neutra: ");
  Serial.println(pitchNeutroLum);
  enviarMensaje("Estoy calibrado!"); // se le avisa al usuario por Telegram que se calibró
}