# ESP32 Power Management: Deep Sleep & Light Sleep

Este repositorio contiene la solución para la **Tarea #6 de Sistemas Embebidos**, enfocada en la implementación y análisis de modos de bajo consumo energético en el microcontrolador ESP32 utilizando **PlatformIO** en Visual Studio Code.

El proyecto aborda la diferenciación práctica entre la simulación de bajo consumo (**Light Sleep**) y la verificación en hardware real (**Deep Sleep**).

---

## 🚀 Características del Proyecto

* **Framework:** Arduino / ESP-IDF (PlatformIO).
* **Modo Light Sleep (Simulado / Wokwi):** Pausa el reloj de la CPU manteniendo la memoria RAM y reanudando la ejecución exactamente en el punto de suspensión. Consumo aproximado: 0.8 mA.
* **Modo Deep Sleep (Hardware Real):** Apaga la CPU y periféricos principales, conservando únicamente el dominio RTC. Al despertar, ejecuta un reinicio completo del sistema. Consumo aproximado: 10 µA.
* **Fuentes de Despertar:** Interrupción externa por pin RTC (EXT0) y temporizador interno RTC (`timer_wakeup`)[cite: 1].

---

## 🛠️ Requisitos e Instalación

### Software
1. [Visual Studio Code](https://code.visualstudio.com/)
2. Extensión de [PlatformIO IDE](https://platformio.org/)

### Hardware Requerido
* Placa de desarrollo **ESP32 Dev Module**
* 1x Pulsador (Pushbutton)
* 1x Resistencias de 10 kΩ (opcional según la fuente EXT0)
* 1x LED (integrado en GPIO 2 o externo)
* Cable Micro-USB / USB-C

---

## 🔌 Conexión del Circuito

| Componente | Pin ESP32 | Configuración |
| :--- | :--- | :--- |
| **LED Indicador** | GPIO 2 | Salida digital (LED integrado o externo con R de 220 Ω) |
| **Pulsador (Light Sleep)** | GPIO 27 | Conectado a GND (`INPUT_PULLUP` interno) |
| **Pulsador (Deep Sleep)** | GPIO 33 | Conectado a GND o 3.3V según evento de activación |

> **Nota para Light Sleep:** Se activa explícitamente el resistor *pull-up* del dominio RTC (`rtc_gpio_pullup_en`) para evitar despertares involuntarios causados por ruido en un pin flotante durante el estado de reposo.

---
