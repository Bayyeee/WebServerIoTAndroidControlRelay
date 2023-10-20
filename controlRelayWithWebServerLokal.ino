#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Haji";
const char *password = "hajikadap123";

const int relay1Pin = 4;  // GPIO pin untuk relay 1
const int relay2Pin = 5;  // GPIO pin untuk relay 2

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Koneksi WiFi...");
  }

  server.on("/relay/1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay1Pin, HIGH);
    request->send(200, "text/plain", "Relay 1 dinonaktifkan");
  });

  server.on("/relay/1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay1Pin, LOW);
    request->send(200, "text/plain", "Relay 1 diaktifkan");
  });

  server.on("/relay/2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay2Pin, HIGH);
    request->send(200, "text/plain", "Relay 2 dinonaktifkan");
  });

  server.on("/relay/2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay2Pin, LOW);
    request->send(200, "text/plain", "Relay 2 diaktifkan");
  });

  server.on("/relay/all/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay1Pin, HIGH);
    digitalWrite(relay2Pin, HIGH);
    request->send(200, "text/plain", "Semua relay dinonaktifkan");
  });

  server.on("/relay/all/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    request->send(200, "text/plain", "Semua relay diaktifkan");
  });


  server.begin();
}

void loop() {
}