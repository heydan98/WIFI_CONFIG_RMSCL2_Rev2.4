// void readRS232(int container)
// {
//   switch(container)
//   {
//     case daikin:
//       readData_daikin(&sp, &ss, &rs);
//       break;
      
//     case carrier:
//       read_sp = !read_sp;
//       if(read_sp)
//       {
//         Serial.println("send ss");
//         readData_SS_carrier();
//       }
//       else
//       {
//         Serial.println("send sp");
//         readData_SP_carrier();
//       }
//       break;
//   }  
//   display_led_string(&sp, &ss, &rs, &temperature_float);
// }
// float Decode(long input)
// {
//   float value_1, value_2;
//   int sign = (input >> 12) & 0b0011;  //$
//   if (sign == 0)
//   {
//     value_2 = (input & 0b111111) / 6;
//     value_1 = (input >> 6) & 0b111111;
//     return value_1 + (value_2 / 10.0);
//   } else
//   {
//     input = (~input + 0b100);
//     value_2 = (input & 0b111111) / 6;
//     value_1 = (input >> 6) & 0b11111111;
//     return (value_1 + (value_2 / 10.0)) * -1.0;
//   }
// }
// float Decode2(long input)
// {
//   float value;
//   int sign = (input >> 12) & 0b0011;
//   if (input > 0xFD00 && input <= 0xFFFF)
//   {
//     value = (int) ((0xFFFF - input) + 1) / -10.0;
//   } else if (input > 0x0000 && input < 0xFD00)
//   {
//     value = (int) (input) / 10.0;
//   }
//   return value;
// }

// void readData_daikin(float* value_sp, float* value_ss, float* value_rs) {
//   memset(data_rms_daikin, 0, sizeof(data_rms_daikin));
//   if (RS232.available() == 0 && read_done )
//   {
//     Serial.println("sent sp daikin ");
//     RS232.write(message_sp_dakin, sizeof(message_sp_dakin));
//     read_done = false;
//   }
//   else if (RS232.available() == 0 && !read_done )
//   {
//     Serial.println("sent rs ss daikin ");
//     RS232.write(message_ss_rs_daikin, sizeof(message_ss_rs_daikin));
//     read_done = true;
//   }
//   if (RS232.available() > 0)
//   {
//     LED_ON();
//     RS232.readBytes(data_rms_daikin, sizeof(data_rms_daikin));
//     for (int i = 0; i < sizeof(data_rms_daikin); i++)
//     {
//       Serial.print(data_rms_daikin[i], HEX);
//       Serial.print(" ");
//     }
//     if (data_rms_daikin[0] == 0x16 && data_rms_daikin[1] == 0x16 && data_rms_daikin[2] == 0x91) //$
//     {
//       Serial.println();
//       Serial.print("-> SP: ");
//       value1 = (data_rms_daikin[SP] << 8) + data_rms_daikin[SP + 1];
//       Serial.print(value1, HEX);
//       Serial.print(" ");
//       *value_sp = Decode(value1);
//       Serial.println(*value_sp);
//       value1 = 0;
//     }
//     if (data_rms_daikin[0] == 0x16 && data_rms_daikin[1] == 0x16 && data_rms_daikin[2] == 0x87) //$
//     {
//       Serial.println();
//       Serial.print("-> SS: ");
//       value2 = (data_rms_daikin[SS] << 8) + data_rms_daikin[SS + 1];
//       Serial.print(value2, HEX);
//       Serial.print(" ");
//       *value_ss = Decode2(value2);
//       Serial.println(*value_ss);
//       Serial.print("-> RS: ");
//       value3 = (data_rms_daikin[RS] << 8) + data_rms_daikin[RS + 1];
//       Serial.print(value3, HEX);
//       Serial.print(" ");
//       *value_rs = Decode2(value3);
//       Serial.println(*value_rs);
//       value2 = 0;
//       value3 = 0;
//     }
//     count_RS232 = 0;
//   }
//   else
//   {
//     count_RS232++;
//     Serial.println(count_RS232);
//     if (count_RS232 > 3)
//     {
//       for (int i = 0; i < sizeof(data_rms_daikin); i++)
//       {
//         data_rms_daikin[i] = 0x00;
//       }
//     }
//   }
// }
// void readData_SS_carrier()
// {
//   String byte_carrier_string;
//   int read_rs232 = 0;
//   memset(data_rms_carrier, 0, sizeof(data_rms_carrier));
//   memset(data_rms_carrier_save, 0, sizeof(data_rms_carrier_save));
//   if (RS232.available() == 0)
//   {
//     Serial.println("sent rs ss carrier ");
//     RS232.write(message_ss_rs_carrier, sizeof(message_ss_rs_carrier));
//   }
//   while (RS232.available() == 0)
//   {
//     if (read_rs232 > 5 || (RS232.available() > 0))
//     {
//       read_rs232 = 0;
//       break;
//     }
//     else
//     {
//       read_rs232++;
//       delay(20);
//     }
//   }
//   if (RS232.available() > 0)
//   {
//     RS232.readBytes(data_rms_carrier, sizeof(data_rms_carrier));
//     bool isTrue = false;
//     LED_ON();
//     for (int i = 0; i < sizeof(data_rms_carrier); i++)
//     {
//       if (data_rms_carrier[i] == 0xEF)
//       {
//         memcpy(data_rms_carrier, &data_rms_carrier[i], sizeof(data_rms_carrier));
//         isTrue = true;
//       }
//       if (isTrue)
//       {
//         Serial.print(data_rms_carrier[i], HEX);
//         Serial.print(" ");
//       }
//     }
//     Serial.println("");
//   }
//   Serial.println(data_rms_carrier[0]);
//   if (data_rms_carrier[0] == 0xEF && data_rms_carrier[4] == 0xE9 )
//     //  && data_rms_carrier_save[4] == 0xE9
//   {
//     Serial.println("da vao ss carrier ");
//     for (int i = 0; i < 4; i++)
//     {
//       hex_carrier[i] = data_rms_carrier[RS_C - i];
//       Serial.print(hex_carrier[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
//     byte_carrier_string = byteToString();
//     rs = hexToFloat(byte_carrier_string);
//     Serial.print("RS:"); Serial.println(rs);
//     delay(50);
//     for (int i = 0; i < 4; i++)
//     {
//       hex_carrier[i] = data_rms_carrier[SS_C - i];
//       Serial.print(hex_carrier[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
//     byte_carrier_string = byteToString();
//     ss = hexToFloat(byte_carrier_string);
//     Serial.print("SS:"); Serial.println(ss);
//   }
// }


// void readData_SP_carrier()
// {
//   String byte_carrier_string;
//   int read_rs232 = 0;
//   memset(data_rms_carrier, 0, sizeof(data_rms_carrier));
//   RS232.readBytes(data_rms_carrier, sizeof(data_rms_carrier));
//   memset(data_rms_carrier, 0, sizeof(data_rms_carrier));
//   memset(data_rms_carrier_save, 0, sizeof(data_rms_carrier_save));
//   if (RS232.available() == 0)
//   {
//     Serial.println("sent sp carrier ");
//     RS232.write(message_sp_carrier, sizeof(message_sp_carrier));
//   }
//   while (RS232.available() == 0)
//   {
//     if (read_rs232 > 5 || (RS232.available() > 0))
//     {
//       read_rs232 = 0;
//       break;
//     }
//     else
//     {
//       read_rs232++;
//       delay(20);
//     }
//   }
//   if (RS232.available() > 0)
//   {
//     RS232.readBytes(data_rms_carrier, sizeof(data_rms_carrier));
//     bool isTrue = false;
//     LED_ON();
//     for (int i = 0; i < sizeof(data_rms_carrier); i++)
//     {
//       if (data_rms_carrier[i] == 0xEF)
//       {
//         memcpy(data_rms_carrier, &data_rms_carrier[i], sizeof(data_rms_carrier));
//         isTrue = true;
//       }
//       if (isTrue)
//       {
//         Serial.print(data_rms_carrier[i], HEX);
//         Serial.print(" ");
//       }
//     }
//     Serial.println("");
//   }
//   Serial.println(data_rms_carrier[0]);
//   if (data_rms_carrier[0] == 0xEF && data_rms_carrier[4] == 0x60 )
//     //  && data_rms_carrier_save[4] == 0x60
//   {
//     Serial.println("da vao sp carrier ");
//     for (int i = 0; i < 4; i++)
//     {
//       hex_carrier[i] = data_rms_carrier[SP_C - i];
//       Serial.print(hex_carrier[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
//     byte_carrier_string = byteToString();
//     Serial.println(byte_carrier_string);
//     sp = hexToFloat(byte_carrier_string);
//   }
// }


// String byteToString()
// {
//   char buffer_carrier[9];
//   sprintf(buffer_carrier, "%02X%02X%02X%02X", hex_carrier[0], hex_carrier[1], hex_carrier[2], hex_carrier[3]);
//   String result_str = String(buffer_carrier);
//   return result_str;
// }
// float hexToFloat(String result_str)
// {
//   float result;
//   unsigned long hexValue = strtoul(result_str.c_str(), NULL, 16);
//   memcpy(&result, &hexValue, sizeof(result));
//   return result;
// }

// void display_led_string(float *sp, float *ss, float *rs, float *temperature_float)
// {
//   float array_t[4] = {*sp, *ss, *rs, *temperature_float};
//   for(int i = 0; i<4; i++)
//   { 
//       int index = (i*2) + 1 ;
//       if(array_t[i] < -10.0)
//       {
//          led_string[index] = String(int(array_t[i])) + "C";   
//       }
//       else if (array_t[i] > 0 && array_t[i] < 10.0)
//       {
//          led_string[index] = " " + String(array_t[i], 1) + "C"; 
//       }
//       else
//       {
//          led_string[index] = String(array_t[i], 1) + "C";   
//       }
//   }      
// }
