#include <Arduino.h>

// Definición de pines y constantes
#define LED_PIN 2              // LED integrado (o externo en GPIO 2)
#define BUTTON_PIN GPIO_NUM_33 // Pin RTC para interrupción externa
#define TIME_TO_SLEEP 10       // Tiempo de reposo en segundos
#define uS_TO_S_FACTOR 1000000ULL // Factor de conversión a microsegundos

// Prototipos de funciones
void checkWakeupReason();
void executeActiveTask();
void prepareAndEnterDeepSleep();

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1000); // Pausa para inicializar la comunicación Serial

  checkWakeupReason();
  executeActiveTask();
  prepareAndEnterDeepSleep();
}

void loop() {
  // En Deep Sleep el procesador se reinicia al despertar, loop() queda vacío
}

void checkWakeupReason() {
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  Serial.println("\n-------------------------------------------");
  switch(wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0: 
      Serial.println(">> Causa de despertar: Interrupción Externa (Botón en GPIO 33)"); 
      break;
    case ESP_SLEEP_WAKEUP_TIMER: 
      Serial.println(">> Causa de despertar: Temporizador RTC (10 segundos)"); 
      break;
    default: 
      Serial.println(">> Causa de despertar: Reinicio / Primera energización"); 
      break;
  }
}

void executeActiveTask() {
  Serial.println(">> Estado: Tarea activa en ejecución.");
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
    Serial.printf("   Procesando sensor/tarea... %d/5\n", i + 1);
  }
  Serial.println(">> Tarea finalizada.");
}

void prepareAndEnterDeepSleep() {
  Serial.println(">> Configurando fuentes de despertar...");
  
  // 1. Configuración por Temporizador
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
  // 2. Configuración por Pin Externo (RTC GPIO 33 detecta nivel ALTO / 1)
  esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 1);

  Serial.println(">> Entrando en DEEP SLEEP. Espera 10s o pulsa GPIO 33...");
  Serial.flush(); // Vaciado del buffer Serial antes de cortar energía
  
  esp_deep_sleep_start();
}