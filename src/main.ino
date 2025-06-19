#include <Arduino.h>

// Definizione manuale del LED (prova questi pin)
#define LED_PIN 2    // GPIO2 - più comune per ESP32 WROOM-32
// #define LED_PIN 5    // GPIO5 - alternativa
// #define LED_PIN 16   // GPIO16 - altra alternativa
// #define LED_PIN 17   // GPIO17 - altra alternativa

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Configura il pin come output
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("=== ESP32 IdeaSpark Test ===");
  Serial.println("Board avviato!");
  Serial.print("Usando GPIO: ");
  Serial.println(LED_PIN);
  
  // Test immediato
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED dovrebbe essere ACCESO");
  delay(2000);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED dovrebbe essere SPENTO");
  delay(1000);
}

void loop() {
  // Blink normale
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(500);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(500);
  
  // Info debug ogni 10 secondi
  static unsigned long lastInfo = 0;
  if (millis() - lastInfo > 10000) {
    lastInfo = millis();
    Serial.println("--- Sistema OK ---");
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" secondi");
  }
}