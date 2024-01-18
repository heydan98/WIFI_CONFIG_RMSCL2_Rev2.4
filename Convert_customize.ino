void Convert_RS485() {
  BaudRates_Customize = readFromEEPROM(190);
  if (BaudRates_Customize.length() > 0) {
    BaudRates = BaudRates_Customize.toInt();
  } else {
    BaudRates = 300;
  }

  ByteSend_Customize = readFromEEPROM(200);
  if (ByteSend_Customize.length() > 0) {
    byteSend_RS485[6] = ByteSend_Customize.toInt();
  } else {
    byteSend_RS485[0] = 0x00;
    byteSend_RS485[1] = 0x00;
    byteSend_RS485[2] = 0x00;
    byteSend_RS485[3] = 0x00;
    byteSend_RS485[4] = 0x00;
    byteSend_RS485[5] = 0x00;
    byteSend_RS485[6] = 0x00;
    byteSend_RS485[7] = 0x00;
  }

  if (ByteSend_Customize.length() == 12) {
    for (int i = 0; i < 6; i++) {
      byteTemperature[i] = (byte) (ByteSend_Customize.substring(i * 2, i * 2 + 2).toInt());
    }
  }
}
