#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Library used for parsing Json from the API responses


//------- Replace the following! ------
char ssid[] = "BEAST_OP";       // your network SSID (name)
char password[] = "Shlok@*!))";  // your network key

WiFiClientSecure client;

// Just the base of the URL you want to connect to
#define TEST_HOST "api.coingecko.com"

// #define TEST_HOST_FINGERPRINT "B3 DD 76 06 D2 B5 A8 B4 A1 37 71 DB EC C9 EE 1C EC AF A3 8A"  //    SHA-1
#define TEST_HOST_FINGERPRINT "3A BB E6 3D AF 75 6C 50 16 B6 B8 5F 52 01 5F D8 E8 AC BE 27 7C 50 87 B1 27 A6 05 63 A8 41 ED 8A"  //    SHA-256
// The finger print will change every few months.


void setup() {

  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  //--------

  // If you don't need to check the fingerprint
  client.setInsecure();

  // If you want to check the fingerprint
  // client.setFingerprint(TEST_HOST_FINGERPRINT);

  makeHTTPRequest();
}

void makeHTTPRequest() {

  // Opening connection to server (Use 80 as port if HTTP)
  if (!client.connect(TEST_HOST, 443))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  // give the esp a breather
  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  client.print("/api/v3/simple/price?ids=ethereum%2Cbitcoin&vs_currencies=usd%2Ceur"); // %2C == ,
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return;
  }
  //delay(100);
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return;
  }

  // This is probably not needed for most, but I had issues
  // with the Tindie api where sometimes there were random
  // characters coming back before the body of the response.
  // This will cause no hard to leave it in
  // peek() will look at the character, but not take it off the queue
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    Serial.println("BAD");
  }

  //  // While the client is still availble read each
  //  // byte and print to the serial monitor
  //  while (client.available()) {
  //    char c = 0;
  //    client.readBytes(&c, 1);
  //    Serial.print(c);
  //  }

  //Use the ArduinoJson Assistant to calculate this:

  //StaticJsonDocument<192> doc;
  DynamicJsonDocument doc(192); //For ESP32/ESP8266 you'll mainly use dynamic.

  DeserializationError error = deserializeJson(doc, client);

  if (!error) {
    float ethereum_usd = doc["ethereum"]["usd"]; // 3961.66
    float ethereum_eur = doc["ethereum"]["eur"]; // 3261.73

    long bitcoin_usd = doc["bitcoin"]["usd"]; // 48924
    long bitcoin_eur = doc["bitcoin"]["eur"]; // 40281

    Serial.print("ethereum_usd: ");
    Serial.println(ethereum_usd);
    Serial.print("ethereum_eur: ");
    Serial.println(ethereum_eur);

    Serial.print("bitcoin_usd: ");
    Serial.println(bitcoin_usd);
    Serial.print("bitcoin_eur: ");
    Serial.println(bitcoin_eur);
    
  } else {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }





}

void loop() {
  // put your main code here, to run repeatedly:

}