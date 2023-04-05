#include <Wire.h>
#include <Adafruit_GFX.h>
// #include <TFT_ILI9163C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
// #include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
// #include <Arduino_Json.h>

const char* ssid = "BEAST_OP";
const char* password = "Shlok@*!))";
const char* crypto_id = "bitcoin";
const char* api_endpoint = "/coins/markets?vs_currency=usd&ids=";

void setup() {
  // put your setup code here, to run once:
  // pinMode(D4, OUTPUT);

  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  WiFiClient client;

}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(D4, HIGH);
  // delay(1000);
  // digitalWrite(D4, LOW);
  // delay(1000);
  
}
