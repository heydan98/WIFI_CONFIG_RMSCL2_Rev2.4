#include "main.h"
#include "HTML.h"
#include "FreeRTOS.h"

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
  }
}
void turnOnSIM() {
  digitalWrite(PIN_PWRKEY, LOW);
  delay(50);
  digitalWrite(PIN_PWRKEY, HIGH);
}
void turnOffSIM() {
  digitalWrite(PIN_PWRKEY, LOW);
  delay(2600);
  digitalWrite(PIN_PWRKEY, HIGH);
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512); 
  pinMode(buttonPin, INPUT);
  // pinMode(PIN_SPICS, OUTPUT);
  // pinMode(SMART_CONFIG, INPUT);
  pinMode(RS485_PIN_DIR, OUTPUT);
  digitalWrite(RS485_PIN_DIR, RS485Transmit);
  Serial.println("Start");
  Read_Eui_From_EEPROM();
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
  Serial.println("Mode:" + readFromEEPROM(450));
  Serial.println("Class:" + readFromEEPROM(470));
  Serial.println("RS485_OPTIONS:" + readFromEEPROM(460));
  Serial.println("SSID: " + readFromEEPROM(475));
  Serial.println("PASSWORD: " + readFromEEPROM(490));

  if (readFromEEPROM(440).length() > 0) {
    if (modeSelect == "WIFI") {
      // digitalWrite(PIN_SPICS, HIGH);
      sendLoraData = false;
      lora_connect = false;
      turnOffSIM();
      Serial.println("SSID: " + readFromEEPROM(475));
      Serial.println("PASSWORD: " + readFromEEPROM(490));
      WiFi.mode(WIFI_STA); //Optional
      WiFi.begin(readFromEEPROM(475), readFromEEPROM(490));
      Serial.println("\nConnecting");
      while(WiFi.status() != WL_CONNECTED){
          Serial.print(".");
          delay(500);
      }
      Serial.println("\nConnected to the WiFi network");
      Serial.print("Local ESP32 IP: ");
      Serial.println(WiFi.localIP());
      
    } else if (modeSelect == "SIM4G") {
      // digitalWrite(PIN_SPICS, HIGH);
      turnOnSIM();
      sendLoraData = false;
      WiFi.mode(WIFI_OFF);
      lora_connect = false;
      Serial.println("Open 4G, Close WiFi and LoraWan");
      delay(10500);
      Serial.println("Check module SIM");
      isModuleSIM = moduleStateCheck();
      Serial.print(isModuleSIM);
      // delay(10000);
      MQTT_connect();
      sprintf(data_mqtt, "{\"count\":%d}", count);
      MQTT_publish(data_mqtt);
    } else if (modeSelect == "LORAWAN") {
        //digitalWrite(PIN_SPICS, LOW);
        Serial.println("Open LoraWan, Close WiFi and 4G");
        lora_connect = true;
        sendLoraData = true;
        WiFi.mode(WIFI_OFF);
        turnOffSIM();
        if (modeLoraSelect == "OTAA") {
          Serial.println("Mode OTAA");
          Serial.println("DEV EUI: " + readFromEEPROM(0));
          Serial.println("APP EUI: " + readFromEEPROM(20));
          Serial.println("APPS KEY OTAA: " + readFromEEPROM(40));
          Serial.println("Intenval_OTAA: " + readFromEEPROM(76));
          int intervalValue = readFromEEPROM(76).toInt();
          interval_data = intervalValue * 1000;
        } else if (modeLoraSelect == "ABP") {
          Serial.println("Mode ABP");
          Serial.println("DEV ADDR: " + readFromEEPROM(86));
          Serial.println("NWSK: " + readFromEEPROM(106));
          Serial.println("APPS KEY ABP: " + readFromEEPROM(146));
          Serial.println("Intenval_ABP: " + readFromEEPROM(182));
          int intervalValue = readFromEEPROM(182).toInt();
          interval_data = intervalValue * 1000;
        } else {
          Serial.println("FAIL");
          interval_data = 3000;
          }
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
      Serial.println("BaudRates_Customize: " + readFromEEPROM(190));
      Serial.println("ByteSend_Customize: " + readFromEEPROM(200));
      Serial.println("RS485_Config_Customize: " + readFromEEPROM(220));
      BaudRates = readFromEEPROM(190).toInt();
      if (readFromEEPROM(220).length() > 0) {
        String PDS = readFromEEPROM(220); // Parity + dataBits + stopBits
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
    int address = 240 + i * 30;
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
  // RS485Serial.begin(BaudRates);
  Serial.println("RS485 baud Done");
  // Serial.println(BaudRates);

  // RS485Serial.write(SWSERIAL.c_str());
  Serial.println("RS485 serial write Done");
  Convert_RS485();
  Serial.println("RS485 convert Done");
  Serial.println("RS485_Config: " + readFromEEPROM(220));
  setup_lora();
  Serial.println("SeuploraDone");

  xTaskCreatePinnedToCore(Interrupt, "Task1", 8000, NULL, 1, &Interrupt_p, 1);
  xTaskCreatePinnedToCore(Read_Temp, "Task2", 4000, NULL, 1, &Read_Temp_p, 0);
  xTaskCreatePinnedToCore(Send_Data_To_Server, "Task3", 6000, NULL, 1, &Send_Data_To_Server_p, 0);
  disableCore0WDT();
}

void loop() {
}