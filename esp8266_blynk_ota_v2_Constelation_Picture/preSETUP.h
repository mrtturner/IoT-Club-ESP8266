#include <Adafruit_NeoPixel.h>
//Required for WifiManager
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

//#include <ESP8266HTTPClient.h> //Must not be included for Web based OTA to work.
//Required for OTA
#include <ESP8266httpUpdate.h>

#include "sha1.h"
#include "TOTP.h"
#include <EasyNTPClient.h>

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson



bool HTTP_OTA = false;

WidgetTerminal terminal(V126);

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

const char* fwUrlBase = "http://www.chswebapps.co.uk/iot_ota/"; //Leave as set.
//OTP Secret. Leave this alone. Not curently utilised but must be present
uint8_t hmacKey[] = {0x70, 0x30, 0x62, 0x6e, 0xef, 0x38, 0x9a, 0x15, 0x9c, 0xce}; 
