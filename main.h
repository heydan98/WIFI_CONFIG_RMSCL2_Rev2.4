#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Crc16.h>
#include <math.h>
#include <Ticker.h>
#include <lorawan.h>
#include <Update.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>

Ticker timer;
Ticker timer1;
Crc16 crc;

/**
 * @brief The DNSServer class provides a simple DNS server implementation for ESP32.
 * 
 * It allows the ESP32 to act as a DNS server, responding to DNS queries from clients on the network.
 * The DNSServer class can be used to redirect DNS queries to a specific IP address or to handle custom DNS responses.
 */
DNSServer dnsServer;
WebServer server(80);

// const sRFM_pins RFM_pins {
//   .CS = 5,
//   .RST = 4,
//   .DIO0 = 12,
//   .DIO1 = 14,
//   // .DIO2 = 19,
//   // .DIO5 = 21,
// };
/**
 * @brief Structure representing the pin configuration for RFM module.
 */
const sRFM_pins RFM_pins {
  .CS = 15,
  .RST = 33,
  .DIO0 = 32,
  .DIO1 = 35,
  .DIO2 = 23,
  .DIO5 = 23,
};
String modeSelect = "";
String ClassOTAA = "";
String ClassABP = "";
String RS485_OPTIONS = "";
String modeLoraSelect = "";
String index4G = "";
String value4G = "";
// 632a72b0220ea2a6
// 807086fb30340faec2680654dfb3887d

String DEV_EUI = "";
String APP_EUI = "";
String APPS_KEY_OTAA = "";
String INTERVAL_OTAA = "";
String SSID = "";
String PASSWORD = "";
String SIM4G = "";
String DEV_ADDR = "";
String NWSK = "";
String APPS_KEY_ABP = "";
String INTERVAL_ABP = "";

String BaudRates_Customize = "";
String ByteSend_Customize = "";
String RS485_Config_Customize = "";
String SWSERIAL;

String customInput1 = "";
String customInput2 = "";
String customInput3 = "";
String customInput4 = "";

String Device1 = "";
String Device2 = "";
String Device3 = "";
String Device4 = "";
String Device5 = "";

String DeviceValue1 = "";
String DeviceValue2 = "";
String DeviceValue3 = "";
String DeviceValue4 = "";
String DeviceValue5 = "";

String DataType1 = "";
String DataType2 = "";
String DataType3 = "";
String DataType4 = "";
String DataType5 = "";

String TempInput = "";
String HumInput = "";

float stepValue;
float Percentage;
float SensorValue;
volatile unsigned long buttonPressTime = 0;
/* LORAWAN downlink */
char outStr[255];
byte recvStatus = 0;
/***************************** RS485 *****************************/
int count_RS485 = 0;
int RS485_count = 0;
/* Declare RS485. */
int Temp4G;
int Hum4G;
#define RXD1 26//RS485
#define TXD1 27

#define RS485_PIN_DIR 25
#define RS485Transmit    HIGH
#define RS485Receive     LOW
// HardwareSerial RS485Serial(1);
SoftwareSerial RS485Serial(RXD1, TXD1);

uint8_t byteTemperature[6] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
uint8_t byteSend_RS485[8]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t byte_RS485[6]      = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t byteReceived_RS485[9];
int Hum, Temp;
float temperature_float = 0, humidity_float = 0;

/***************************** RS232 *****************************/
HardwareSerial RS232(2);
#define SP 5
#define SS 3
#define RS 9

#define SP_C 44
#define SS_C 36
#define RS_C 32
const byte message_sp_dakin[] = {0x16, 0x16, 0x11, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x97};
const byte message_ss_rs_daikin[] = {0x16, 0x16, 0x7 , 0x01 , 0xFF, 0xFF, 0xFF, 0x85, 0xBC};
//16 16 07 01 FF FF FF 85 BC
const byte message_sp_carrier[] = {0x30, 0x00, 0xef, 0x00, 0x03, 0x00, 0x00, 0x0b, 0x00, 0x0f, 0x02, 0xc2, 0x21};
const byte message_ss_rs_carrier[] = {0x30, 0x00, 0xef, 0x00, 0x03, 0x00, 0x00, 0x0b, 0x00, 0x07, 0x09, 0x84, 0x26};
//30 00 ef 00 03 00 00 0b 00 07 09 84 26
long value1 = 0, value2 = 0, value3 = 0;
float sp = 0,  ss = 0, rs = 0;
bool read_done = true;
bool read_sp = false;
bool read_ss = false;
byte data_rms_daikin[64];
byte data_rms_carrier[128];
byte data_rms_carrier_save[128];
byte hex_carrier[] = {0x00, 0x00, 0x00, 0x00};
int number_count = 0;
const int daikin  = 1;
const int carrier = 2;
/***************************** *****************************/
String Data_Lorawan;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 500;

const byte DNS_PORT = 53;
// const int buttonPin = 0;
#define buttonPin 5

int BaudRates;
bool buttonState = true;
bool webServerEnabled = false;
bool start_init = false;
bool dataSent = false;
bool rs485Enabled = true;
boolean State ;
bool sendLoraData = false; 
bool send4Gdata = false;
bool sendWifidata = false;
#define PIN_ANALOG 34
// #define PIN_SPICS 5
// #define PIN_ITR 26

/*****************************4G *****************************/
const char MQTTpublish[] = "v1/devices/me/telemetry";
String receive_AT;
String response = "";
bool isModuleSIM = false;
bool DEBUG = true;
#define PIN_PWRKEY 19
#define RXD2 16//SIM4G
#define TXD2 17
char data_mqtt[30];
int count = 0;
String data_wifi;
String data_4G;
const char *mqttServer = "demo.thingsboard.io";
const int mqttPort = 1883;
const char *mqttClientId = "763452";
const char *mqttUsername = "09090808";
const char *mqttPassword = "09090808";
/***************************** Setup Variable and Pin *****************************/
/* Time variable. */
unsigned long Millis = 0;
unsigned long previousMillis_data = 0;
unsigned long interval_data = 120000;
unsigned long previous_time = 0;
unsigned long previous_time_sensor = 0;
unsigned long previous_led = 0;
unsigned int counter = 0;     // message counter
unsigned int timer_previous = 0;
/*Setting GPIO*/
#define PIN_LED 18
#define LED_ON() digitalWrite(PIN_LED, HIGH)
#define LED_OFF() digitalWrite(PIN_LED, LOW)
/*Setting EEPROM*/
int lastButtonState = 0;
int buttonCounter = 0;
long timeButton = 0;
bool battery_state = false;

bool lora_connect = true;
// boolean lora_state = false;
// boolean rs485_state = true;
// boolean rs232_state = true;

// bool interruptMode = false;
// int previousButtonState = 0;
// unsigned long buttonPressStartTime = 0;

/***************************** LED 7 Segment *****************************/
/*Setting pin LED7Segment*/
int led_number = 0;
String led_string[] = {"SP--", "---C", "RS--", "---C", "SS--", "---C", "USDA", "---C", "HU--", "---H"};
byte hex[] = {0x00, 0x00, 0x00, 0x00};
int count_led = 0, dot;
String chain = "----";
#define LATCH_PIN 21 // ST_CP
#define CLOCK_PIN 22 // SH_CP
#define DATA_PIN 19  //DS
/*Setting variable LED7Segment*/
byte ledSegments[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //K common
byte pos[] = {0x0E, 0x0D, 0x0B, 0x07};
byte pos_led[] =  {0x0E, 0x0D, 0x0B, 0x07};
int arr[] = {0, 0, 0, 0};
boolean lora_state = false;
boolean rs485_state = true;
boolean rs232_state = true;
/***************************** Deepsleep Mode *****************************/
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 120