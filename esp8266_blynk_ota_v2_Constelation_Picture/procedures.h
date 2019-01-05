

char* getotp(){
    TOTP totp = TOTP(hmacKey, 10);
    char code[7];
    WiFiUDP udp;
    EasyNTPClient ntpClient(udp, "pool.ntp.org"); // 
     long GMT = ntpClient.getUnixTime();
     char* newCode = totp.getCode(GMT);
     if(strcmp(code, newCode) != 0) {
     strcpy(code, newCode);
     Serial.println(code);
     return code;
}
}

/// Start of main function that performs HTTP OTA /// 
void checkForUpdates() {
  uint8_t mac[6];
  char macAddr[14];
  WiFi.macAddress( mac );
  ///sprintf(macAddr,"%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); /// small letters at MAC address
  sprintf(macAddr, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); /// capital letters at MAC address

  String fwURL = String( fwUrlBase );
  fwURL.concat("getfw.php?mac=");
  fwURL.concat( macAddr );
  
  String fwVersionURL = String( fwUrlBase );
  fwVersionURL.concat("checkfw.php?mac=");
  fwVersionURL.concat( macAddr );

  Serial.println( "Checking for firmware updates." );
  Serial.print( "MAC address: " );
  Serial.println( macAddr );
  terminal.println( "Checking for firmware updates." );
  terminal.print( "MAC address: " );
  terminal.println( macAddr );
  terminal.flush();
  
  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );

//  Serial.print( "Firmware URL: " );
//  Serial.println( fwURL );

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    terminal.print( "Current firmware version: " );
    terminal.println( FW_VERSION );
    terminal.flush();
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );

    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );
      terminal.println( "Preparing to update" );
      terminal.flush();

      String fwImageURL = fwURL;
      fwImageURL.concat( "&ps=" );
      fwImageURL.concat( getotp() );
////
      
        Serial.print( "Firmware Image URL: " );
        Serial.println( fwImageURL );
      t_httpUpdate_return ret = ESPhttpUpdate.update( fwImageURL );

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          ESP.restart();
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          ESP.restart();
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
      terminal.println( "Already on latest version" );
      terminal.flush();
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
    terminal.print( "Firmware version check failed, got HTTP response code " );
    terminal.println( httpCode );
    terminal.flush();
  }
  httpClient.end();
}
/// End of main function that performs HTTP OTA /// 

BLYNK_WRITE(V127) // Trigger this V Pin to reset wifi settings.
{
  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);
  wifiManager.resetSettings();  //reset settings
  ESP.restart();  //
}

/// V125 switch to activate HTTP file OTA on demand via boolean HTTP_OTA variable that activate in the loop V125 ///
/// START routine for manual (on demand) requesting HTTP file OTA. Virtual Button SW V125 is used ///
  BLYNK_WRITE(V125)
  {
    if (param.asInt()) {
        digitalWrite(LED_BUILTIN, LOW);
        checkForUpdates();
        digitalWrite(LED_BUILTIN, HIGH);
    } 
  }
/// Also called in setup for auto update on boot.
/// END routine for manual (on demand) requesting HTTP file OTA. Virtual Button SW V125 is used ///


/// MAC Function
String getMAC(){
  uint8_t mac[6];
  char result[14];
  sprintf(result, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); /// capital letters at MAC address 
  return String(result);
}
///

#define LED_BUILTIN 2 
#define FLASH_BTN 0

#define BLYNK_DEBUG // Optional, this enables lots of prints
#define BLYNK_PRINT Serial
