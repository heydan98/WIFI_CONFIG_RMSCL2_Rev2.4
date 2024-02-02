void saveToEEPROM(int address, String value)
{
  for (int i = 0; i < value.length(); ++i)
  {
    EEPROM.write(address + i, value[i]);
  }
  EEPROM.write(address + value.length(), 0); // Null terminator
  EEPROM.commit();
}

String readFromEEPROM(int address)
{
  String value = "";
  for (int i = 0; i < 50; ++i)
  {
    byte byteValue = EEPROM.read(address + i);
    if (byteValue == 0)
    {
      break;
    }
    value += char(byteValue);
  }
  return value;
}
void Read_Eui_From_EEPROM()
{
  // ===== EEPROM OTAA ====//
  for (int i = 0; i < 18; ++i)
  {
    DEV_EUI += char(EEPROM.read(i));
  }
  DEV_EUI.remove(DEV_EUI.indexOf(0));
  for (int i = 18; i < 36; ++i)
  {
    APP_EUI += char(EEPROM.read(i));
  }
  APP_EUI.remove(APP_EUI.indexOf(0));
  for (int i = 36; i < 72; ++i)
  {
    APPS_KEY_OTAA += char(EEPROM.read(i));
  }
  APPS_KEY_OTAA.remove(APPS_KEY_OTAA.indexOf(0));
  for (int i = 72; i < 76; ++i)
  {
    INTERVAL_OTAA += char(EEPROM.read(i));
  }
  INTERVAL_OTAA.remove(INTERVAL_OTAA.indexOf(0));
  // ======= EEPROM ABP ========//
  for (int i = 76; i < 94; ++i)
  {
    DEV_ADDR += char(EEPROM.read(i));
  }
  DEV_ADDR.remove(DEV_ADDR.indexOf(0));
  for (int i = 94; i < 110 ; ++i)
  {
    NWSK += char(EEPROM.read(i));
  }
  NWSK.remove(NWSK.indexOf(0));

  for (int i = 110; i < 146; ++i)
  {
    APPS_KEY_ABP += char(EEPROM.read(i));
  }
  APPS_KEY_ABP.remove(APPS_KEY_ABP.indexOf(0));
  for (int i = 146; i < 150; ++i)
  {
    INTERVAL_ABP += char(EEPROM.read(i));
  }
  INTERVAL_ABP.remove(INTERVAL_ABP.indexOf(0));


  // ======== Customize ===========//
  for (int i = 150; i < 158; ++i)
  {
    BaudRates_Customize += char(EEPROM.read(i));
  }
  BaudRates_Customize.remove(BaudRates_Customize.indexOf(0));
  for (int i = 158; i < 178; ++i)
  {
    ByteSend_Customize += char(EEPROM.read(i));
  }
  ByteSend_Customize.remove(ByteSend_Customize.indexOf(0));
  for (int i = 178; i < 198; ++i)
  {
    RS485_Config_Customize += char(EEPROM.read(i));
  }
  RS485_Config_Customize.remove(RS485_Config_Customize.indexOf(0));

  //====== DataSend===========//
  for (int i = 198; i < 208; ++i)
  {
    Device1 += char(EEPROM.read(i));
  }
  Device1.remove(Device1.indexOf(0));
  for (int i = 208; i < 218; ++i)
  {
    DataType1 += char(EEPROM.read(i));
  }
  DataType1.remove(DataType1.indexOf(0));
  for (int i = 218; i < 228; ++i)
  {
    DeviceValue1 += char(EEPROM.read(i));
  }
  DeviceValue1.remove(DeviceValue1.indexOf(0));
  for (int i = 228; i < 238; ++i)
  {
    Device2 += char(EEPROM.read(i));
  }
  Device2.remove(Device2.indexOf(0));
  for (int i = 238; i < 248; ++i)
  {
    DataType2 += char(EEPROM.read(i));
  }
  DataType2.remove(DataType2.indexOf(0));
  for (int i = 248; i < 258; ++i)
  {
    DeviceValue2 += char(EEPROM.read(i));
  }
  DeviceValue2.remove(DeviceValue2.indexOf(0));
  for (int i = 258; i < 268; ++i)
  {
    Device3 += char(EEPROM.read(i));
  }
  Device3.remove(Device3.indexOf(0));
  for (int i = 268; i < 278; ++i)
  {
    DataType3 += char(EEPROM.read(i));
  }
  DataType3.remove(DataType3.indexOf(0));
  for (int i = 278; i < 288; ++i)
  {
    DeviceValue3 += char(EEPROM.read(i));
  }
  DeviceValue3.remove(DeviceValue3.indexOf(0));

  for (int i = 288; i < 298; ++i)
  {
    Device4 += char(EEPROM.read(i));
  }
  Device4.remove(Device4.indexOf(0));
  for (int i = 298; i < 308; ++i)
  {
    DataType4 += char(EEPROM.read(i));
  }
  DataType4.remove(DataType4.indexOf(0));
  for (int i = 308; i < 318; ++i)
  {
    DeviceValue4 += char(EEPROM.read(i));
  }
  DeviceValue4.remove(DeviceValue4.indexOf(0));
  for (int i = 318; i < 328; ++i)
  {
    Device5 += char(EEPROM.read(i));
  }
  Device5.remove(Device5.indexOf(0));
  for (int i = 328; i < 338; ++i)
  {
    DataType5 += char(EEPROM.read(i));
  }
  DataType5.remove(DataType5.indexOf(0));
  for (int i = 338; i < 348; ++i)
  {
    DeviceValue5 += char(EEPROM.read(i));
  }
  DeviceValue5.remove(DeviceValue5.indexOf(0));

  // ======== Name Data Temp/Hum ======//
  for (int i = 348; i < 358; ++i)
  {
    TempInput += char(EEPROM.read(i));
  }
  TempInput.remove(TempInput.indexOf(0));
  for (int i = 358; i < 368 ; ++i)
  {
    HumInput += char(EEPROM.read(i));
  }
  HumInput.remove(HumInput.indexOf(0));

  for (int i = 368; i < 378; ++i)
  {
    customInput1 += char(EEPROM.read(i));
  }
  customInput1.remove(customInput1.indexOf(0));
  for (int i = 378; i < 388 ; ++i)
  {
    customInput2 += char(EEPROM.read(i));
  }
  customInput2.remove(customInput2.indexOf(0));
  for (int i = 388; i < 398; ++i)
  {
    customInput3 += char(EEPROM.read(i));
  }
  customInput3.remove(customInput3.indexOf(0));
  for (int i = 398; i < 408 ; ++i)
  {
    customInput4 += char(EEPROM.read(i));
  }
  customInput4.remove(customInput4.indexOf(0));


  // ======== MODE AND CLASS AND RS485======//
  for (int i = 408; i < 418; ++i)
  {
    modeSelect += char(EEPROM.read(i));
  }
  modeSelect.remove(modeSelect.indexOf(0));

  for (int i = 428; i < 431; ++i)
  {
    ClassOTAA += char(EEPROM.read(i));
  }
  ClassOTAA.remove(ClassOTAA.indexOf(0));

  for (int i = 431; i < 435; ++i)
  {
    ClassOTAA += char(EEPROM.read(i));
  }
  ClassOTAA.remove(ClassOTAA.indexOf(0));

  for (int i = 418; i < 428; ++i)
  {
    RS485_OPTIONS += char(EEPROM.read(i));
  }
  RS485_OPTIONS.remove(RS485_OPTIONS.indexOf(0));

  for (int i = 435; i < 455; ++i)
  {
    SSID += char(EEPROM.read(i));
  }
  SSID.remove(SSID.indexOf(0));
  
  for (int i = 455; i < 475; ++i)
  {
    PASSWORD += char(EEPROM.read(i));
  }
  PASSWORD.remove(PASSWORD.indexOf(0));
  
  // for (int i = 505; i < 510; ++i)
  // {
  //   SIM4G += char(EEPROM.read(i));
  // }
  // SIM4G.remove(SIM4G.indexOf(0));

  for (int i = 475; i < 480; ++i)
  {
    modeLoraSelect += char(EEPROM.read(i));
  }
  modeLoraSelect.remove(modeLoraSelect.indexOf(0));

  // for (int i = 480; i < 495; ++i)
  // {
  //   index4G += char(EEPROM.read(i));
  // }
  // index4G.remove(index4G.indexOf(0));

  // for (int i = 495; i < 512; ++i)
  // {
  //   value4G += char(EEPROM.read(i));
  // }
  // value4G.remove(value4G.indexOf(0));
}
