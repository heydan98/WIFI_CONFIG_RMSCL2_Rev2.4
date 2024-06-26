void Interrupt(void *parameter) {
  while (1) {
    if (start_init == true) {
      WiFi.mode(WIFI_AP);
      IPAddress localIP(192, 168, 1, 1);
      IPAddress gateway(192, 168, 1, 1);
      IPAddress subnet(255, 255, 255, 0);
      WiFi.softAPConfig(localIP, gateway, subnet);
      WiFi.softAP("ESP32-WebServer", "12345678");
      ArduinoOTA.setHostname("ESP32-OTA");
      ArduinoOTA.begin();

      // Setup web server
      String html = String(htmlContent); // Copy the HTML content to a String
      // Read values from EEPROM
      String value1 = readFromEEPROM(0);
      String value2 = readFromEEPROM(18);
      String value3 = readFromEEPROM(36);
      String value4 = readFromEEPROM(72);
      String value5 = readFromEEPROM(76);
      String value6 = readFromEEPROM(94);
      String value7 = readFromEEPROM(110);
      String value8 = readFromEEPROM(146);
      String value9 = readFromEEPROM(150);
      String value10 = readFromEEPROM(200);
      String value11 = readFromEEPROM(218);
      String tempInput = readFromEEPROM(348);
      String humInput = readFromEEPROM(358);
      String customInput1 = readFromEEPROM(368);
      String customInput2 = readFromEEPROM(378);
      String customInput3 = readFromEEPROM(388);
      String customInput4 = readFromEEPROM(480);
      String value22 = readFromEEPROM(435);
      String value23 = readFromEEPROM(455);
      // String value24 = readFromEEPROM(480);
      // String value25 = readFromEEPROM(495);

      String modeSelect = readFromEEPROM(408);
      String classSelectOTAA = readFromEEPROM(428);
      String classSelectABP = readFromEEPROM(431);
      
      String rs485Options = readFromEEPROM(418);
      String modeLoraSelect = readFromEEPROM(475);
      



      html.replace("id=\"value1\"", "id=\"value1\" value=\"" + value1 + "\"");
      html.replace("id=\"value2\"", "id=\"value2\" value=\"" + value2 + "\"");
      html.replace("id=\"value3\"", "id=\"value3\" value=\"" + value3 + "\"");
      html.replace("id=\"value4\"", "id=\"value4\" value=\"" + value4 + "\"");
      html.replace("id=\"value5\"", "id=\"value5\" value=\"" + value5 + "\"");
      html.replace("id=\"value6\"", "id=\"value6\" value=\"" + value6 + "\"");
      html.replace("id=\"value7\"", "id=\"value7\" value=\"" + value7 + "\"");
      html.replace("id=\"value8\"", "id=\"value8\" value=\"" + value8 + "\"");
      html.replace("id=\"value9\"", "id=\"value9\" value=\"" + value9 + "\"");
      html.replace("id=\"value10\"", "id=\"value10\" value=\"" + value10 + "\"");
      html.replace("id=\"value11\"", "id=\"value11\" value=\"" + value11 + "\"");
      html.replace("id=\"value22\"", "id=\"value22\" value=\"" + value22 + "\"");
      html.replace("id=\"value23\"", "id=\"value23\" value=\"" + value23 + "\"");
      // html.replace("id=\"value24\"", "id=\"value24\" value=\"" + value24 + "\"");
      // html.replace("id=\"value25\"", "id=\"value25\" value=\"" + value25 + "\"");
      html.replace("id=\"tempInput\"", "id=\"tempInput\" value=\"" + tempInput + "\"");
      html.replace("id=\"humInput\"", "id=\"humInput\" value=\"" + humInput + "\"");
      html.replace("id=\"customInput1\"", "id=\"customInput1\" value=\"" + customInput1 + "\"");
      html.replace("id=\"customInput2\"", "id=\"customInput2\" value=\"" + customInput2 + "\"");
      html.replace("id=\"customInput3\"", "id=\"customInput3\" value=\"" + customInput3 + "\"");
      html.replace("id=\"customInput4\"", "id=\"customInput4\" value=\"" + customInput4 + "\"");
      html.replace("id=\"modeSelect\"", "id=\"modeSelect\" value=\"" + modeSelect + "\"");
      html.replace("id=\"classSelectOTAA\"", "id=\"classSelectOTAA\" value=\"" + classSelectOTAA + "\"");
      html.replace("id=\"classSelectABP\"", "id=\"classSelectABP\" value=\"" + classSelectABP + "\"");
      html.replace("id=\"rs485Options\"", "id=\"rs485Options\" value=\"" + rs485Options + "\"");
      html.replace("id=\"modeLoraSelect\"", "id=\"modeLoraSelect\" value=\"" + modeLoraSelect + "\"");
      html.replace("id=\"index4G\"", "id=\"index4G\" value=\"" + index4G + "\"");
      html.replace("id=\"value4G\"", "id=\"value4G\" value=\"" + value4G + "\"");


      dnsServer.setTTL(3600);
      dnsServer.start(DNS_PORT, "*", localIP);
      server.on("/process", HTTP_POST, handleProcess);
      // Serial.println("HTTP server started 3");
      server.on("/update", HTTP_GET, handleFirmwareUpdate);
      // Serial.println("HTTP server started 4");
      server.on("/wpad.dat", []() {
        server.send(404);
      });
      
      server.on("/update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        // Serial.println("HTTP server started 5");
        ESP.restart();
      });
      server.onNotFound([html]() {
        server.send(200, "text/html", htmlContent);
        Serial.println("Server not found");
      });
      // server.on("/process", HTTP_POST, handleProcess);
      // // Serial.println("HTTP server started 3");
      // server.on("/update", HTTP_GET, handleFirmwareUpdate);
      // // Serial.println("HTTP server started 4");
      // server.on("/wpad.dat", []() {
      //   server.send(404);
      // });
      
      // server.on("/update", HTTP_POST, []() {
      //   server.sendHeader("Connection", "close");
      //   server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      //   // Serial.println("HTTP server started 5");
      //   ESP.restart();
      // });
      
      server.begin();
      start_init = false;
    }
    ArduinoOTA.handle();
    if (webServerEnabled) {
      dnsServer.processNextRequest();
      server.handleClient();
    }
    if (dataSent) {
      dataSent = false;
    } vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
