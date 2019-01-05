ESP.wdtDisable();
ESP.wdtEnable(WDTO_8S);

pinMode(FLASH_BTN, INPUT);

// Debug console
  Serial.begin(9600);




   //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

         strcpy(blynk_token, json["blynk_token"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read



  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length

  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 32);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //exit after config instead of connecting
  wifiManager.setBreakAfterConfig(true);


  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //add all your parameters here
  wifiManager.addParameter(&custom_blynk_token);
  //wifiManager.addParameter(&custom_blynk_token);
  
  //reset settings - for testing
  //wifiManager.resetSettings();

  //tries to connect to last known settings
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP" with password "password"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
    Serial.println("failed to connect, we should reset and see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  
  //read updated parameters
  strcpy(blynk_token, custom_blynk_token.getValue());




    //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    //json["blynk_server"] = blynk_server;
    //json["blynk_port"] = blynk_port;
    json["blynk_token"] = blynk_token;


    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
  
if (schoolServer==1){
  Blynk.config(blynk_token, IPAddress(192,168,16,107), 8080);
  ESP.wdtFeed();
  Blynk.connect();
}else{
  Blynk.config(blynk_token);
  ESP.wdtFeed();
  Blynk.connect();
}
  



terminal.println("System Started");
terminal.flush();
//terminal.print("Device MAC Address: ");
//terminal.println(getMAC());


