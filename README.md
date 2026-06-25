# Postu 🦴

**Sistema wearable de monitoreo postural con alertas progresivas e interfaz IoT**

Postu es un dispositivo vestible basado en ESP32 que detecta malas posturas en tiempo real durante actividades sedentarias como el trabajo en escritorio o el estudio. Al detectar una desviación angular sostenida, activa alertas progresivas sonoras, visuales y hápticas, y envía reportes de sesión por Telegram.

---

## Características

- Monitoreo postural en tiempo real con dos sensores ADXL345 (zona torácica y lumbar)
- Calibración de postura neutra con un botón
- Alertas progresivas: LED, buzzer con patrón pi-pi y motores de vibración háptica independientes por zona
- Intervalo de repetición del buzzer que se acorta a medida que aumenta el tiempo en mala postura
- Reporte de sesión enviado por Telegram con tiempo total, tiempo en mala postura y porcentaje de buena postura
- Dos buses I2C independientes para manejar dos sensores con la misma dirección

---

## Hardware

| Componente | Cantidad |
|---|---|
| ESP32 NodeMCU-32S | 1 |
| Sensor ADXL345 | 2 |
| Buzzer piezoeléctrico activo | 1 |
| Motor de vibración háptico de disco | 2 |
| Transistor NPN BC547 | 2 |
| Resistencia 1 kΩ | 2 |
| Diodo 1N4148 | 2 |
| Pulsador | 2 |
| Batería 9V | 1 |
| Regulador de tensión 7805 | 1 |
| Arnés reflectivo ajustable | 1 |
| Placas multiperforadas | — |

---

## Conexiones principales

| Componente | Pin ESP32 |
|---|---|
| ADXL345 torácico SDA | GPIO 21 |
| ADXL345 torácico SCL | GPIO 22 |
| ADXL345 lumbar SDA | GPIO 27 |
| ADXL345 lumbar SCL | GPIO 16 |
| Buzzer | GPIO 32 |
| Motor torácico | GPIO 33 |
| Motor lumbar | GPIO 26 |
| Botón calibrar | GPIO 4 |
| Botón resumen | GPIO 13 |

---

## Estructura del repositorio

```
postu/
├── firmware/
│   └── main/
│       ├── main.ino          # Loop principal y gestión de botones
│       ├── calibracion.h/.cpp # Lectura de sensores y cálculo de pitch
│       ├── timer.h/.cpp       # Detección de mala postura y timer
│       ├── alertas.h/.cpp     # Buzzer, LED y motores hápticos
│       └── telegram.h/.cpp    # Conexión WiFi y bot de Telegram
└── hardware/
    └── conexiones.md
```

---

## Configuración

Antes de compilar, editá `telegram.h` con tus credenciales:

```cpp
#define WIFI_SSID     "tu_red"
#define WIFI_PASSWORD "tu_contraseña"
#define BOT_TOKEN     "tu_token_de_botfather"
#define CHAT_ID       "tu_chat_id"
```

---

## Dependencias

Instalá desde el gestor de librerías de Arduino IDE:

- `UniversalTelegramBot`
- `ArduinoJson`

La comunicación con los sensores usa `Wire.h`, incluida por defecto en Arduino IDE.

---

## Cómo usar

1. Encendé el dispositivo con el switch
2. Ponete el arnés con los sensores correctamente posicionados
3. Adoptá tu postura correcta y presioná el **botón de calibración** (GPIO 4)
4. El LED deja de titilar — el sistema empieza a monitorear
5. Si llevás más de 5 segundos en mala postura, se activan las alertas
6. Presioná el **botón de resumen** (GPIO 13) para recibir el reporte por Telegram y apagar el dispositivo

---

## Principio de funcionamiento

El ADXL345 mide la aceleración gravitacional sobre los ejes X y Z. El ángulo de inclinación se calcula con:

```
pitch = atan2(az, ax) × (180 / π)
```

La desviación respecto a la postura neutra calibrada se compara contra un umbral de 10°. Si la supera durante más de 5 segundos, se activan las alertas de forma progresiva.

---

## Repositorio

[https://github.com/valjeon/postu](https://github.com/valjeon/postu)
