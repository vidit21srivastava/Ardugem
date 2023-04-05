# ESPaIN Submission 

In this challenge, we have combined ESP8266 with an SPI TFT display; ESP connects to a local wifi network, then queries both api.coindesk.com and coinmarketcap.com every 60 seconds to retrieve a JSON formatted replies of the data we want. ArduinoJSON then handles the parsing of the data while SPI TFT displays the information we're interested in.

### Circuit Connections
The connections are as follows:
- SCK to GPIO4
- MOSI to GPIO4
- CS to GPIO15
- RST to GPIO0
- DC to GPIO2
- VCC to 3.3V
- GND to GND

## Library Used
We have used the following libraries.
- ESP8266WiFi.h
- ESP8266HTTPClient.h
- SPI.h
- ArduinoJson.h
- TFT_eSPI.h