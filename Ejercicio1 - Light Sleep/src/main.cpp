#include <Arduino.h>          // Requerida para proyectos .cpp en PlatformIO
#include "esp_sleep.h"        // Librería nativa para funciones esp_sleep_*
#include "driver/rtc_io.h"    // Para mantener la resistencia pull-up activa en reposo

int counter = 0;
const int ledPin = 2;              // GPIO pin for onboard LED
#define buttonPin  GPIO_NUM_27    // Connect a pushbutton to GPIO 27

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); 

    // Mantiene el pull-up activo en el dominio RTC durante el reposo
    rtc_gpio_pullup_en(buttonPin);
    rtc_gpio_pulldown_dis(buttonPin);

    // Configura despertar por EXT0 cuando el pin pase a nivel BAJO (0 = GND)
    esp_err_t result = esp_sleep_enable_ext0_wakeup(buttonPin, 0);  

    if (result == ESP_OK) {
        Serial.println("EXT0 Wake-Up set successfully as wake-up source.");
    } else {
        Serial.println("Failed to set EXT0 Wake-Up as wake-up source.");
    }
}

void loop() {
    Serial.printf("Counter: %d\n", counter);
    counter++;

    digitalWrite(ledPin, HIGH); // LED encendido indicando actividad
    delay(5000);
    digitalWrite(ledPin, LOW);  // Apaga LED antes del reposo

    Serial.println("Going into light sleep mode");
    Serial.flush();             // Garantiza la salida completa del texto Serial
    delay(100);

    esp_light_sleep_start();    // Entra en light sleep

    Serial.println("Returning from light sleep");
    
    // Antirrebote básico para evitar despertares falsos continuos
    while(digitalRead(buttonPin) == LOW) {
        delay(10);
    }
}