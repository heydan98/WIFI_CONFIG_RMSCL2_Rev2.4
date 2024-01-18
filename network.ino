void setup_lora()
{
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    lora_connect = false;
    delay(2000);
    return;
  }

  if (modeLoraSelect == "OTAA")
  {
    if (Class == "A" )
    {
      lora.setDeviceClass(CLASS_A);
    } else
    {
      lora.setDeviceClass(CLASS_C);
    }
    lora.setDataRate(SF10BW125);
    lora.setChannel(MULTI);
    lora.setDevEUI(DEV_EUI.c_str());
    lora.setAppEUI(APP_EUI.c_str());
    lora.setAppKey(APPS_KEY_OTAA.c_str());
    bool isJoined;
    do {
      for (int i = 0; i < 4; i++)
      {
        if (millis() - Millis > 3000) {
          Serial.println("Joining...");
          isJoined = lora.join();
          Millis = millis();
        }
      }
    } while (!isJoined && !start_init);

  } else if (modeLoraSelect == "ABP") {
    if (Class == "A" )
    {
      lora.setDeviceClass(CLASS_A);
    } else
    {
      lora.setDeviceClass(CLASS_C);
    }
    lora.setDataRate(SF7BW125);
    lora.setChannel(MULTI);
    lora.setDevAddr(DEV_ADDR.c_str());
    lora.setNwkSKey(NWSK.c_str());
    lora.setAppSKey(APPS_KEY_ABP.c_str());
    bool isJoined = true;
  }
  if (!start_init)
  {
    Serial.println("Joined to network");
    delay(500);
    char myStr[50] = "{\"state\":\"true\"}";
    Serial.print("Sending: ");
    Serial.println(myStr);
    lora.sendUplink(myStr, strlen(myStr), 0, 1);
    lora_state = true;
    for (int i = 0; i < sizeof(byteTemperature); i++)
    {
      byte_RS485[i] = byteTemperature[i];
    }
    CRC_RS485_return();
    delay(10);
    RS485();
    delay(10);
    if (RS485_OPTIONS == "Temp/Hum" || RS485_OPTIONS == "PH") {
      Hum = (byteReceived_RS485[3] << 8 ) + byteReceived_RS485[4];
      Temp  = (byteReceived_RS485[5] << 8 ) + byteReceived_RS485[6];
      Serial.print(TempInput); Serial.println(float(Temp / 10), 2);
      Serial.print(HumInput); Serial.println(float(Hum / 10), 2);
    } else {
      String Input1 = readFromEEPROM(420).substring(0, readFromEEPROM(420).indexOf(','));
      String Input2 = readFromEEPROM(420).substring(0, readFromEEPROM(420).indexOf(',')+ 1);
      String Input3 = readFromEEPROM(440).substring(0, readFromEEPROM(440).indexOf(','));
      String Input4 = readFromEEPROM(440).substring(readFromEEPROM(440).indexOf(',') + 1);

      int index_customInput1 = Input1.toInt();
      int index_customInput2 = Input2.toInt();
      int index_customInput3 = Input3.toInt();
      int index_customInput4 = Input4.toInt();
      
      Hum = (byteReceived_RS485[index_customInput1] << 8 ) + byteReceived_RS485[(index_customInput2)];
      Temp  = (byteReceived_RS485[index_customInput3] << 8 ) + byteReceived_RS485[(index_customInput4)];
      Serial.print(customInput3); Serial.println(float(Temp / 10), 2);
      Serial.print(customInput1); Serial.println(float(Hum / 10), 2);
    }
  }
}
void uplink_lorawan()
{
  int health = 99;
  boolean state = true;
  String temp_str, hum_str;
  if (Temp == 0)
  {
    temp_str = "***";
    hum_str = "***";
  }
  else
  {
    temp_str = String(temperature_float, 1);
    hum_str = String(humidity_float, 1);
  }

  String data_lorawan = "";
  bool hasData = false;

  for (int i = 0; i < 15; i++)
  {
    int address = 240 + i * 30;
    String key = readFromEEPROM(address);

    if (key.length() > 0)
    {
      String dataType = readFromEEPROM(address + 10);
      String dataValue = readFromEEPROM(address + 20);

      if (dataType == "Digital" || dataType == "Analog" || dataType == "Customize")
      {
        String value = "";
        if (dataType == "Digital")
        {
          int pinNumber = readFromEEPROM(address + 20).toInt();
          pinMode(pinNumber, INPUT);
          int pinState = digitalRead(pinNumber);
          String stateString = (pinState == HIGH) ? "true" : "false";
          value = stateString;
        }
        else if (dataType == "Analog")
        {
          String valuePart1 = dataValue.substring(0, dataValue.indexOf(','));
          String valuePart2 = dataValue.substring(dataValue.indexOf(',') + 1);

          int xValue = valuePart1.toInt();
          int yValue = valuePart2.toInt();

          stepValue = float (yValue - xValue) / 4095;
          //          int readAnalog = analogRead(PIN_ANALOG);
          float readAnalog = 1000;
          Percentage = (readAnalog / 4095) * 100;
          SensorValue = readAnalog * stepValue + float(xValue) ;
          value = SensorValue;
        } else {
          value = dataValue;
        }
        if (hasData)
        {
          data_lorawan += ",";
        }

        data_lorawan += "\"" + key + "\":\"" + value + "\"";

        hasData = true;
      }
    }
  }
  
  String temp_hum_str;
  if (RS485_OPTIONS == "Temp/Hum" || RS485_OPTIONS == "PH") {
    temp_hum_str = "\"" + String(TempInput) + "\":\"" + String(float(Temp) / 10.0, 2) + "\","
                          + "\"" + String(HumInput) + "\":\"" + String(float(Hum) / 10.0, 2) + "\"";
  } else {
    temp_hum_str = "\"" + String(customInput3) + "\":\"" + String(float(Temp) / 10.0, 2) + "\","
                          + "\"" + String(customInput1) + "\":\"" + String(float(Hum) / 10.0, 2) + "\"";
  }

  String Data_Lorawan = "{" + temp_hum_str;
  if (hasData)
  {
    Data_Lorawan += "," + data_lorawan;
  }
  Data_Lorawan += "}";

  int str_len = Data_Lorawan.length() + 1;
  char Data[str_len];
  Data_Lorawan.toCharArray(Data, str_len);
  Serial.println((char *)Data);
  lora.sendUplink(Data, strlen(Data), 0, 1);
  counter++;
}
