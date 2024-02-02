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
  value10.replace(" ", "");  // This will replace spaces with an empty string
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
  index4G = server.arg("index4G");
  value4G = server.arg("value4G");

  ClassOTAA = server.arg("classSelectOTAA");
  ClassABP = server.arg("classSelectABP");

  RS485_OPTIONS = server.arg("rs485Options");
  String data1 = server.arg("dataType1");
  String data2 = server.arg("dataType2");
  String data3 = server.arg("dataType3");
  String data4 = server.arg("dataType4");
  String data5 = server.arg("dataType5");

  server.send(200, "text/plain", "OK");
  dataSent = true;

  saveToEEPROM(0, value1);
  saveToEEPROM(18, value2);
  saveToEEPROM(36, value3);
  saveToEEPROM(72, value4);
  saveToEEPROM(76, value5);
  saveToEEPROM(94, value6);
  saveToEEPROM(110, value7);
  saveToEEPROM(146, value8);
  saveToEEPROM(150, value9);
  saveToEEPROM(158, value10);
  saveToEEPROM(178, value11);
  saveToEEPROM(198, value12);
  saveToEEPROM(218, value13);
  saveToEEPROM(228, value14);
  saveToEEPROM(248, value15);
  saveToEEPROM(258, value16);
  saveToEEPROM(278, value17);
  saveToEEPROM(288, value18);
  saveToEEPROM(308, value19);
  saveToEEPROM(318, value20);
  saveToEEPROM(338, value21);
  saveToEEPROM(435, value22);
  saveToEEPROM(455, value23);
  // saveToEEPROM(580, value24);
  saveToEEPROM(348, TempInput);
  saveToEEPROM(358, HumInput);
  saveToEEPROM(368, customInput1);
  saveToEEPROM(378, customInput2);
  saveToEEPROM(388, customInput3);
  saveToEEPROM(398, customInput4);
  
  saveToEEPROM(208, data1);
  saveToEEPROM(238, data2);
  saveToEEPROM(268, data3);
  saveToEEPROM(298, data4);
  saveToEEPROM(328, data5);
  saveToEEPROM(408, modeSelect);
  saveToEEPROM(418, RS485_OPTIONS);
  saveToEEPROM(428, ClassOTAA);
  saveToEEPROM(431, ClassABP);
  saveToEEPROM(475, modeLoraSelect);
  saveToEEPROM(480, index4G);
  saveToEEPROM(495, value4G);




  Serial.println("Data saved to EEPROM successfully.");

  webServerEnabled = false;
  server.stop();
  WiFi.disconnect();
  Serial.println("Disconnected from Wi-Fi_ESP32-WebServer");
  ESP.restart();
}
