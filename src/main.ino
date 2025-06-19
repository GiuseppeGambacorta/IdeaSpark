#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configurazione display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  // Indirizzo I2C comune (prova anche 0x3D se non funziona)

// Pin I2C (ESP32 default)
#define SDA_PIN 21
#define SCL_PIN 22

// Crea oggetto display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("=== ESP32 IdeaSpark + SSD1306 ===");
  
  // Inizializza I2C con pin specifici
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Inizializza display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("ERRORE: Display SSD1306 non trovato!");
    Serial.println("Controlla:");
    Serial.println("- Connessioni I2C (SDA=21, SCL=22)");
    Serial.println("- Alimentazione display");
    Serial.println("- Indirizzo I2C (prova 0x3D invece di 0x3C)");
    while(1);
  }
  
  Serial.println("Display SSD1306 inizializzato!");
  
  // Test iniziale
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ESP32 IdeaSpark");
  display.println("");
  display.println("Display: SSD1306");
  display.println("Risoluzione: 128x64");
  display.println("");
  display.println("Sistema OK!");
  display.display();
  
  delay(3000);
}

void loop() {
  // Test 1: Contatore
  testCounter();
  delay(3000);
  
  // Test 2: Informazioni di sistema
  testSystemInfo();
  delay(3000);
  
  // Test 3: Grafica semplice
  testGraphics();
  delay(3000);
  
  // Test 4: Testo grande
  testBigText();
  delay(3000);
}

void testCounter() {
  static int counter = 0;
  counter++;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("CONTATORE:");
  
  display.setTextSize(3);
  display.setCursor(20, 25);
  display.print(counter);
  
  display.setTextSize(1);
  display.setCursor(0, 56);
  display.print("Ciclo: ");
  display.print(counter);
  
  display.display();
  
  Serial.print("Contatore: ");
  Serial.println(counter);
}

void testSystemInfo() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  display.println("SYSTEM INFO:");
  display.println("");
  display.print("Uptime: ");
  display.print(millis() / 1000);
  display.println("s");
  
  display.print("Free RAM: ");
  display.print(ESP.getFreeHeap());
  display.println("b");
  
  display.print("CPU Freq: ");
  display.print(ESP.getCpuFreqMHz());
  display.println("MHz");
  
  display.print("Chip: ");
  display.println("ESP32");
  
  display.display();
  
  Serial.println("--- System Info ---");
  Serial.print("Uptime: ");
  Serial.print(millis() / 1000);
  Serial.println(" secondi");
  Serial.print("Free RAM: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
}

void testGraphics() {
  display.clearDisplay();
  
  // Titolo
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 0);
  display.println("GRAPHICS");
  
  // Linee
  display.drawLine(0, 15, 127, 15, SSD1306_WHITE);
  display.drawLine(0, 63, 127, 63, SSD1306_WHITE);
  
  // Rettangoli
  display.drawRect(10, 20, 30, 20, SSD1306_WHITE);
  display.fillRect(50, 20, 30, 20, SSD1306_WHITE);
  
  // Cerchi
  display.drawCircle(95, 30, 10, SSD1306_WHITE);
  display.fillCircle(110, 30, 8, SSD1306_WHITE);
  
  // Triangolo
  display.drawTriangle(10, 45, 25, 60, 40, 50, SSD1306_WHITE);
  
  display.display();
  
  Serial.println("Test grafici completato");
}

void testBigText() {
  display.clearDisplay();
  
  // Testo grande centrato
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 10);
  display.println("ESP32");
  
  display.setCursor(10, 35);
  display.println("IdeaSpark");
  
  // Indicatore di stato
  display.setTextSize(1);
  display.setCursor(45, 55);
  display.println("READY");
  
  display.display();
  
  Serial.println("Test testo grande completato");
}

// Funzioni utility aggiuntive
void displayText(String text, int textSize = 1, int x = 0, int y = 0) {
  display.clearDisplay();
  display.setTextSize(textSize);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, y);
  display.println(text);
  display.display();
}

void displayMultiLine(String line1, String line2 = "", String line3 = "", String line4 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.println(line1);
  
  if (line2 != "") {
    display.setCursor(0, 16);
    display.println(line2);
  }
  
  if (line3 != "") {
    display.setCursor(0, 32);
    display.println(line3);
  }
  
  if (line4 != "") {
    display.setCursor(0, 48);
    display.println(line4);
  }
  
  display.display();
}