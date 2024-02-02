#include "main.h"
#include "HTML.h"
#include "FreeRTOS.h"
#include <PubSubClient.h>

void Read_Temp(void *parameter) {
  while (1) {
    if (millis() - previous_time > 10000) {
      // readRS232(2);
      // readRS232(detect_container());
      previous_time = millis();
    }
    if (millis() - previous_time_sensor > 5000) {
      readRS485();
      previous_time_sensor = millis();
    }
  }
}
void Send_Data_To_Server(void *parameter )
{
  while (1)
  {
    if (sendLoraData) {
      if (millis() - previousMillis_data > interval_data) {
        uplink_lorawan();
        previousMillis_data = millis();
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      recvStatus = lora.readData(outStr);
      if (recvStatus) {
        Serial.println(outStr);
      }
      lora.update();
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    if (send4Gdata) {
      if (millis() - previousMillis_data > 30000) {
        uplink_4G();
        previousMillis_data = millis();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      // recvStatus = lora.readData(outStr);
      // if (recvStatus) {
      //   Serial.println(outStr);
      // }
      // lora.update();
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    if (sendWifidata) {
      if (millis() - previousMillis_data > 30000) {
        uplink_wifi();
        previousMillis_data = millis();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      // recvStatus = lora.readData(outStr);
      // if (recvStatus) {
      //   Serial.println(outStr);
      // }
      // lora.update();
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }
}
WiFiClient espClient;
PubSubClient client(espClient);
// client.setServer(mqttServer, mqttPort);

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200, SERIAL_8N1, 16, 17);
  EEPROM.begin(512); 
  pinMode(buttonPin, INPUT);
  pinMode(RS485_PIN_DIR, OUTPUT);
  pinMode(PIN_PWRKEY, OUTPUT);
  digitalWrite(PIN_PWRKEY, HIGH);
  digitalWrite(RS485_PIN_DIR, RS485Transmit);
  Serial.println("Start");
  Read_Eui_From_EEPROM();
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
  Serial.println("Mode:" + readFromEEPROM(408));
  Serial.println("RS485_OPTIONS:" + readFromEEPROM(418));
  

  if (readFromEEPROM(398).length() > 0) {
    if (modeSelect == "WIFI") {
      // digitalWrite(PIN_SPICS, HIGH);
      client.setServer(mqttServer, mqttPort);
      sendLoraData = false;
      lora_connect = false;
      send4Gdata = false;
      sendWifidata = true;
      turnOffSIM();
      Serial.println("SSID: " + readFromEEPROM(435));
      Serial.println("PASSWORD: " + readFromEEPROM(455));
      WiFi.mode(WIFI_STA); //Optional
      WiFi.begin(readFromEEPROM(435), readFromEEPROM(455));
      Serial.println("\nConnecting");
      unsigned long startTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) {
        Serial.print(".");
        delay(500);
      }
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to the WiFi network");
        Serial.print("Local ESP32 IP: ");
        Serial.println(WiFi.localIP());
        
        while (!client.connected()) {
          Serial.println("Connecting to ThingsBoard MQTT...");
          if (client.connect(mqttClientId, mqttUsername, mqttPassword)) {
            Serial.println("Connected to ThingsBoard MQTT");
          } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
          }
        }
      } else {
        Serial.println("\nFailed to connect to the WiFi network");
        // Handle the case when WiFi connection fails
        // Add your code here
      }
      
    } else if (modeSelect == "SIM4G") {
      delay(10);
      sendLoraData = false;
      WiFi.mode(WIFI_OFF);
      lora_connect = false;
      turnOnSIM();
      Serial.println("Open 4G, Close WiFi and LoraWan");
      delay(16000);
      Serial.println("Check module SIM");
      isModuleSIM = moduleStateCheck();
      Serial.println(isModuleSIM);
      send4Gdata = true;
      delay(1000);
      // delay(10000);
      MQTT_connect();
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
        String Input1 = readFromEEPROM(378).substring(0, readFromEEPROM(378).indexOf(','));
        String Input2 = readFromEEPROM(378).substring(0, readFromEEPROM(378).indexOf(',')+ 1);
        String Input3 = readFromEEPROM(398).substring(0, readFromEEPROM(398).indexOf(','));
        String Input4 = readFromEEPROM(398).substring(readFromEEPROM(398).indexOf(',') + 1);

        int index_customInput1 = Input1.toInt();
        int index_customInput2 = Input2.toInt();
        int index_customInput3 = Input3.toInt();
        int index_customInput4 = Input4.toInt();
        
        Hum = (byteReceived_RS485[index_customInput1] << 8 ) + byteReceived_RS485[(index_customInput2)];
        Temp  = (byteReceived_RS485[index_customInput3] << 8 ) + byteReceived_RS485[(index_customInput4)];
        Serial.print(customInput3); Serial.println(float(Temp / 10), 2);
        Serial.print(customInput1); Serial.println(float(Hum / 10), 2);
      }
    } else if (modeSelect == "LORAWAN") {
      Serial.println("Open LoraWan, Close WiFi and 4G");
      lora_connect = true;
      sendLoraData = true;                                                                                                    
      WiFi.mode(WIFI_OFF);
      turnOffSIM();
      if (modeLoraSelect == "OTAA") {
        Serial.println("Mode OTAA");
        Serial.println("Class:" + readFromEEPROM(428));
        Serial.println("DEV EUI: " + readFromEEPROM(0));
        Serial.println("APP EUI: " + readFromEEPROM(18));
        Serial.println("APPS KEY OTAA: " + readFromEEPROM(36));
        Serial.println("Intenval_OTAA: " + readFromEEPROM(72));
        int intervalValue = readFromEEPROM(72).toInt();
        interval_data = intervalValue * 1000;
      } else if (modeLoraSelect == "ABP") {
        Serial.println("Mode ABP");
        Serial.println("Class:" + readFromEEPROM(428));
        Serial.println("DEV ADDR: " + readFromEEPROM(76));
        Serial.println("NWSK: " + readFromEEPROM(94));
        Serial.println("APPS KEY ABP: " + readFromEEPROM(110));
        Serial.println("Intenval_ABP: " + readFromEEPROM(146));
        int intervalValue = readFromEEPROM(146).toInt();
        interval_data = intervalValue * 1000;
      } else {
        Serial.println("FAIL");
        interval_data = 3000;
        }
      setup_lora();
      Serial.println("SeuploraDone");
    }
  }  else {Serial.println("Don't have mode");}

  if (readFromEEPROM(460).length() > 0) {
    if (readFromEEPROM(460) == "Temp/Hum" || readFromEEPROM(460) == "PH")
    {
      uint8_t tempArray[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
      memcpy(byteTemperature, tempArray, sizeof(tempArray));
      // BaudRates = 4800;
      BaudRates = 9600;
      SWSERIAL = SWSERIAL_8N1;
    } else {
      int index_customInput2 = customInput2.toInt();
      int index_customInput4 = customInput4.toInt();
      Serial.println("BaudRates_Customize: " + readFromEEPROM(150));
      Serial.println("ByteSend_Customize: " + readFromEEPROM(158));
      Serial.println("RS485_Config_Customize: " + readFromEEPROM(178));
      BaudRates = readFromEEPROM(150).toInt();
      if (readFromEEPROM(178).length() > 0) {
        String PDS = readFromEEPROM(178); // Parity + dataBits + stopBits
        SWSERIAL = "SWSERIAL_" + PDS;
        if (SWSERIAL.startsWith("SWSERIAL_")) {
          SWSERIAL = SWSERIAL.substring(10); //(SWSERIAL_)
        }
      }
    }
  }
  else {
    // BaudRates = 4800;
    BaudRates = 9600;
  }

  for (int i = 0; i < 5; i++)
  {
    int address = 198 + i * 30;
    String key = readFromEEPROM(address);
    if (readFromEEPROM(address).length() > 0){
      Serial.println("Key length>0, Key: " + key);
      if (key.length() > 0) {
        String dataType = readFromEEPROM(address + 10);
        String dataValue = readFromEEPROM(address + 20);

        if (dataType == "Digital") {
          int pinNumber = readFromEEPROM(address + 20).toInt();
          pinMode(pinNumber, INPUT);
          int pinState = digitalRead(pinNumber);
          String stateString = (pinState == HIGH) ? "true" : "false";
          Serial.print(key); Serial.println(" : " + stateString);
        }
        else if (dataType == "Analog") {
          String valuePart1 = dataValue.substring(0, dataValue.indexOf(','));
          String valuePart2 = dataValue.substring(dataValue.indexOf(',') + 1);

          int xValue = valuePart1.toInt();
          int yValue = valuePart2.toInt();

          stepValue = float(yValue - xValue) / 4095.0;
          //          int readAnalog = analogRead(PIN_ANALOG);
          float readAnalog = 1000;
          Percentage = float (readAnalog / 4095) * 100;
          SensorValue = readAnalog * stepValue + float(xValue) ;

          Serial.print(key); Serial.print(" : " ); Serial.print(Percentage); Serial.println(" % " );
          Serial.print(key); Serial.print(" : "); Serial.println(SensorValue);
        } else {
          Serial.print(key);
          Serial.print(" : ");
          Serial.println(dataValue);
        }
      }
    }
  }
  RS485Serial.begin(9600, SWSERIAL_8N1);
  Serial.println("RS485 baud Done");
  // RS485Serial.write(SWSERIAL.c_str());
  Serial.println("RS485 serial write Done");
  Convert_RS485();
  Serial.println("RS485 convert Done");
  Serial.println("RS485_Config: " + readFromEEPROM(178));

  xTaskCreatePinnedToCore(Interrupt, "Task1", 8000, NULL, 3, &Interrupt_p, 1);
  xTaskCreatePinnedToCore(Read_Temp, "Task2", 4000, NULL, 1, &Read_Temp_p, 0);
  xTaskCreatePinnedToCore(Send_Data_To_Server, "Task3", 6000, NULL, 1, &Send_Data_To_Server_p, 0);
  // xTaskCreatePinnedToCore(Display_Led, "Task3", 6000, NULL, 1, &Display_Led_p, 1);
  disableCore0WDT();
}

void loop() {
}