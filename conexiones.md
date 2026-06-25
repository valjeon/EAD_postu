# Conexiones de hardware — Postu

## Sensores ADXL345

### Sensor torácico (bus I2C — Wire)

| Pin sensor | Pin ESP32 | Descripción |
|---|---|---|
| VCC | 3V3 | Alimentación |
| GND | GND | Tierra |
| SDA | GPIO 21 | Transmisión de datos I2C |
| SCL | GPIO 22 | Sincronización del bus I2C |

### Sensor lumbar (bus I2C — Wire1)

| Pin sensor | Pin ESP32 | Descripción |
|---|---|---|
| VCC | 3V3 | Alimentación |
| GND | GND | Tierra |
| SDA | GPIO 27 | Transmisión de datos segundo bus I2C |
| SCL | GPIO 16 | Sincronización del segundo bus I2C |

> Ambos sensores tienen dirección I2C `0x53`. Se usan dos buses independientes para evitar colisiones en el bus.

---

## Buzzer piezoeléctrico

| Pin buzzer | Pin ESP32 | Descripción |
|---|---|---|
| + (positivo) | GPIO 32 | Señal de control |
| - (negativo) | GND | Tierra |

---

## Motores hápticos

Cada motor se controla mediante un transistor NPN BC547. El pin de señal del ESP32 activa la base del transistor a través de una resistencia de 1 kΩ, permitiendo el paso de corriente al motor. Un diodo 1N4148 en paralelo con el motor protege el transistor de los picos de tensión inversa.

### Motor torácico

| Conexión | Detalle |
|---|---|
| Pin positivo del motor | 5V |
| Pin negativo del motor | Colector del BC547 |
| Base del BC547 | GPIO 33 → resistencia 1 kΩ |
| Emisor del BC547 | GND |
| Diodo 1N4148 | En paralelo con el motor, cátodo hacia 5V |

### Motor lumbar

| Conexión | Detalle |
|---|---|
| Pin positivo del motor | 5V |
| Pin negativo del motor | Colector del BC547 |
| Base del BC547 | GPIO 26 → resistencia 1 kΩ |
| Emisor del BC547 | GND |
| Diodo 1N4148 | En paralelo con el motor, cátodo hacia 5V |

> El BC547 visto desde la cara plana tiene los pines en este orden de izquierda a derecha: **Colector — Base — Emisor**.

---

## Pulsadores

Ambos pulsadores están configurados como `INPUT_PULLUP` en el firmware, por lo que no requieren resistencia externa. Leen `LOW` cuando están presionados.

| Función | Pin ESP32 | Pin 2 |
|---|---|---|
| Calibración | GPIO 4 | GND |
| Resumen / apagado | GPIO 13 | GND |

---

## Alimentación

| Conexión | Detalle |
|---|---|
| Batería 9V | Entrada del regulador 7805 |
| Salida del regulador (5V) | VIN del ESP32 y pin positivo de ambos motores |
| GND de la batería | GND del ESP32 y emisor de ambos transistores |

> Todos los GND deben estar conectados entre sí en una línea común.

---

## Resumen de pines ESP32

| GPIO | Componente | Función |
|---|---|---|
| 21 | ADXL345 torácico | SDA bus I2C |
| 22 | ADXL345 torácico | SCL bus I2C |
| 27 | ADXL345 lumbar | SDA bus I2C |
| 16 | ADXL345 lumbar | SCL bus I2C |
| 32 | Buzzer | Señal de control |
| 33 | Motor torácico | Señal de control (via BC547) |
| 26 | Motor lumbar | Señal de control (via BC547) |
| 4 | Pulsador calibración | INPUT_PULLUP |
| 13 | Pulsador resumen | INPUT_PULLUP |
| VIN | Regulador 7805 | Alimentación 5V |
| 3V3 | Sensores ADXL345 | Alimentación 3.3V |
| GND | Todos | Tierra común |
