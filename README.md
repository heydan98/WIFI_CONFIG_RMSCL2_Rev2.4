# ESP32 RMS Container

This project implements a versatile sensor data collection and transmission system using an ESP32 microcontroller. It supports multiple communication protocols including LoRaWAN, 4G, and Wi-Fi for data transmission, as well as RS485 for sensor interfacing.

## Features

- Multiple communication modes: LoRaWAN (OTAA/ABP), 4G, and Wi-Fi
- RS485 sensor support for temperature, humidity, pH, and custom sensors
- MQTT support for data transmission (in Wi-Fi and 4G modes)
- EEPROM storage for configuration persistence
- FreeRTOS task management for concurrent operations
- Interrupt-driven button input for mode selection
- Configurable data transmission intervals
- Support for digital and analog inputs

## Hardware Requirements

- ESP32 development board
- RS485 interface
- LoRaWAN module (optional)
- 4G module (optional)
- Various sensors (depending on configuration)

## Software Dependencies

- Arduino core for ESP32
- FreeRTOS
- PubSubClient library
- EEPROM library
- WiFi library
- Custom LoRaWAN library (not included in this repository)

## Configuration

The system is highly configurable through EEPROM storage. Key configuration options include:

- Communication mode (LoRaWAN, 4G, or Wi-Fi)
- LoRaWAN parameters (DEV EUI, APP EUI, APPS KEY, etc.)
- Wi-Fi credentials
- MQTT server details
- RS485 sensor options and custom configurations
- Data transmission intervals

## Main Components

1. `setup()`: Initializes the system, reads configuration from EEPROM, and sets up the selected communication mode.
2. `Read_Temp()`: Periodically reads data from RS485 sensors.
3. `Send_Data_To_Server()`: Handles data transmission based on the selected communication mode.
4. `Interrupt()`: Manages button interrupt for mode selection (implementation not shown in the provided code).

## Usage

1. Configure the system by writing appropriate values to EEPROM.
2. Upload the code to your ESP32 board.
3. The system will start automatically, reading sensor data and transmitting it according to the configured settings.
