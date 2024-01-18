String response_AT_Command(String command, const int timeout, boolean debug) {
  String response = "";
  if (command.equals("1A") || command.equals("1a")) {
    Serial.println();
    
    Serial.println(command);

    Serial.println("Get a 1A, input a 0x1A");
    Serial1.write(26);
    Serial1.println();
    return "";
  } else {

    Serial1.println(command);
    Serial.println(command);

  }

  long int time = millis();
  while ((time + timeout) > millis()) {
    while (Serial1.available()) {
      char c = Serial1.read();
      Serial.println("response");
      
      response += c;
    }
  }
  if (debug) {
    Serial.println("hahahaha");
    Serial.println(response);

  }

  return response;
}

bool moduleStateCheck() {
  int i = 0;
  bool moduleState = false;
  for (i = 0; i < 10; i++) {
    String msg = String("");
    msg = response_AT_Command("AT", 1000, DEBUG);
    Serial.println("Hihihi");
    Serial.println(msg);
    Serial.println("Hihihi");


    if (msg.indexOf("OK") >= 0) {
      Serial1.println("SIM7600 Module had turned on.");
      Serial.println("Huhuhu");

      moduleState = true;
      return moduleState;
    }
    delay(1000);
  }
  return moduleState;
}


void MQTT_connect() {
  char ATCommand[200];
  String msg = "";
  msg = response_AT_Command("AT+CMQTTDISC=0,60", 500, DEBUG);
  delay(200);
  msg = response_AT_Command("AT+CMQTTREL=0", 500, DEBUG);
  delay(200);
  msg = response_AT_Command("AT+CMQTTSTOP", 500, DEBUG);
  delay(200);
  msg = response_AT_Command("AT+CMQTTSTART", 500, DEBUG);
  delay(200);
  msg = response_AT_Command("AT+CMQTTACCQ=0,\"123456\",0", 500, DEBUG);
  delay(200);
  msg = response_AT_Command("AT+CMQTTDISC=0,60", 500, DEBUG);
  delay(200);
  // sprintf(ATCommand, "AT+CMQTTCONNECT=0,\"tcp://%s:%s\",60,1,\"%s\",\"%s\"", "103.199.6.216", "3003", "test", "test");
  sprintf(ATCommand, "AT+CMQTTCONNECT=0,\"tcp://%s:%s\",60,1,\"%s\",\"%s\"", "demo.thingsboard.io", "1883", "huybac", "huybac");
  msg = response_AT_Command(ATCommand, 500, DEBUG);
}
void MQTT_publish(String data_) {
  char ATCommand[200];
  String msg = "";
  sprintf(ATCommand, "AT+CMQTTTOPIC=0,%d", strlen(MQTTpublish));
  msg = response_AT_Command(ATCommand, 1000, DEBUG);
  sprintf(ATCommand, "%s", MQTTpublish);
  msg = response_AT_Command(ATCommand, 1000, DEBUG);
  sprintf(ATCommand, "AT+CMQTTPAYLOAD=0,%d", strlen(data_.c_str()));
  msg = response_AT_Command(ATCommand, 1000, DEBUG);
  sprintf(ATCommand, "%s", data_.c_str());
  msg = response_AT_Command(ATCommand, 1000, DEBUG);
  sprintf(ATCommand, "AT+CMQTTPUB=0,1,60,0");
  msg = response_AT_Command(ATCommand, 1000, DEBUG);
}