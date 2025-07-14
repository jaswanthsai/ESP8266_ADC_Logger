#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "xxxxxxxx";
const char* password = "xxxxxxxxxx";

const char* serverUrl = "http://api.thingspeak.com/update?api_key=YOUR_API_KEY";  // 🔁 Replace with your key

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi connected");
}

void loop() {
  int adcValue = analogRead(A0);
  Serial.println("ADC: " + String(adcValue));

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String fullUrl = String(serverUrl) + "&field1=" + String(adcValue);  // Add ADC to field1

    http.begin(client, fullUrl);
    int httpCode = http.GET();

    Serial.println("ThingSpeak POST: " + String(httpCode));
    http.end();
  } else {
    Serial.println("❌ Wi-Fi not connected");
  }

  delay(5000);  // Send every 5 seconds
}
