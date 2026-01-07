#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "XXXXXXXX" //Cambiar esto
#define BLYNK_TEMPLATE_NAME "XXXXXXXX" //Cambiar esto
#define BLYNK_AUTH_TOKEN "XXXXXXXX" //Cambiar esto

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// 🔐 WiFi
char ssid[] = "XXXXXXXX"; //Cambiar esto
char pass[] = "XXXXXXXX"; //Cambiar esto

// 💡 LED azul (GPIO2, activo LOW)
#define LED_PIN 2

// 🔌 Relé (D1 = GPIO5)
#define RELAY_PIN 5

void ledOn()  { digitalWrite(LED_PIN, LOW); }
void ledOff() { digitalWrite(LED_PIN, HIGH); }

void relayOn()  { digitalWrite(RELAY_PIN, HIGH); }
void relayOff() { digitalWrite(RELAY_PIN, LOW); }

// 🔘 Botón en Blynk (V0)
BLYNK_WRITE(V0) {
  int estado = param.asInt();

  if (estado == 1) {
    ledOn();
    relayOn();
    Serial.println("📱 Botón presionado → LED y RELÉ ENCENDIDOS");
  } else {
    ledOff();
    relayOff();
    Serial.println("📱 Botón soltado → LED y RELÉ APAGADOS");
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // 🔹 Todo apagado al iniciar
  ledOff();
  relayOff();

  Serial.begin(115200);
  delay(200);

  // 🔹 Conectar WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  // 🔹 Conectar Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
