   // reset wifi & check for firmware updates:
 int buttonState = digitalRead(FLASH_BTN);
  if (buttonState == LOW) {
    digitalWrite(LED_BUILTIN, LOW);
    checkForUpdates();
    WiFiManager wifiManager;
    wifiManager.setBreakAfterConfig(true);
    wifiManager.resetSettings();
    digitalWrite(LED_BUILTIN, HIGH);
    ESP.restart();
  }

  ESP.wdtFeed();
  
  Blynk.run();
