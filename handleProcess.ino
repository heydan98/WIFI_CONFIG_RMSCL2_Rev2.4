void handleProcess() {
  String value1 = server.arg("value1");
  String value2 = server.arg("value2");
  String value3 = server.arg("value3");
  String value4 = server.arg("value4");
  String value5 = server.arg("value5");
  String value6 = server.arg("value6");
  String value7 = server.arg("value7");
  String value8 = server.arg("value8");
  String value9 = server.arg("value9");
  String value10 = server.arg("value10");
  String value11 = server.arg("value11");
  String value12 = server.arg("value12");
  String value13 = server.arg("value13");
  String value14 = server.arg("value14");
  String value15 = server.arg("value15");
  String value16 = server.arg("value16");
  String value17 = server.arg("value17");
  String value18 = server.arg("value18");
  String value19 = server.arg("value19");
  String value20 = server.arg("value20");
  String value21 = server.arg("value21");
  String value22 = server.arg("value22");
  String value23 = server.arg("value23");
  String value24 = server.arg("value24");

  String TempInput = server.arg("tempInput");
  String HumInput = server.arg("humInput");
  String customInput1 = server.arg("customInput1");
  String customInput2 = server.arg("customInput2");
  String customInput3 = server.arg("customInput3");
  String customInput4 = server.arg("customInput4");

  modeSelect = server.arg("modeSelect");
  modeLoraSelect = server.arg("modeLoraSelect");

  Class = server.arg("classSelect");
  RS485_OPTIONS = server.arg("rs485Options");
  String data1 = server.arg("dataType1");
  String data2 = server.arg("dataType2");
  String data3 = server.arg("dataType3");
  String data4 = server.arg("dataType4");
  String data5 = server.arg("dataType5");

  server.send(200, "text/plain", "OK");
  dataSent = true;

  saveToEEPROM(0, value1);
  saveToEEPROM(20, value2);
  saveToEEPROM(40, value3);
  saveToEEPROM(76, value4);
  saveToEEPROM(86, value5);
  saveToEEPROM(106, value6);
  saveToEEPROM(146, value7);
  saveToEEPROM(182, value8);
  saveToEEPROM(190, value9);
  saveToEEPROM(200, value10);
  saveToEEPROM(220, value11);
  saveToEEPROM(240, value12);
  saveToEEPROM(260, value13);
  saveToEEPROM(270, value14);
  saveToEEPROM(290, value15);
  saveToEEPROM(300, value16);
  saveToEEPROM(320, value17);
  saveToEEPROM(330, value18);
  saveToEEPROM(350, value19);
  saveToEEPROM(360, value20);
  saveToEEPROM(380, value21);
  saveToEEPROM(475, value22);
  saveToEEPROM(490, value23);
  // saveToEEPROM(580, value24);
  saveToEEPROM(390, TempInput);
  saveToEEPROM(400, HumInput);
  saveToEEPROM(410, customInput1);
  saveToEEPROM(420, customInput2);
  saveToEEPROM(430, customInput3);
  saveToEEPROM(440, customInput4);
  
  saveToEEPROM(250, data1);
  saveToEEPROM(280, data2);
  saveToEEPROM(310, data3);
  saveToEEPROM(340, data4);
  saveToEEPROM(370, data5);
  saveToEEPROM(450, modeSelect);
  saveToEEPROM(460, RS485_OPTIONS);
  saveToEEPROM(470, Class);
  saveToEEPROM(507, modeLoraSelect);


  Serial.println("Data saved to EEPROM successfully.");

  webServerEnabled = false;
  server.stop();
  WiFi.disconnect();
  Serial.println("Disconnected from Wi-Fi_ESP32-WebServer");
  ESP.restart();
}
