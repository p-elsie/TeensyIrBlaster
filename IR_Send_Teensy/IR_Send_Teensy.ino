#include <IRremote.h>
IRsend irsend;

//Lirc codes for Dish Network
//power_on 1
//up       26
//select   16
//0        17
//1        4
//2        5
//3        6
//4        8
//5        9
//6        10
//7        12
//8        13
//9        14

//ASCII
//a 0x61
//b 0x62
//p 0x70
//s 0x73
//u 0x75
//0 0x30
// ...
//9 0x39

void setup()
{
  Serial.begin(9600);
}

void loop() {
  int inByte = Serial.read();
  switch (inByte) {
    case 0x61:
      //user sent 'a'. we toggle power on LG TV
      irsend.sendNEC(0x20DF10EF, 32);
      //Serial.println("toggle power - LG TV");
      break;
    case 0x62:
      //user sent 'b'. we toggle power on Samsung TV
      irsend.sendSAMSUNG(0xE0E040BF, 32);
      //Serial.println("toggle power - Samsung TV");
      break;
    case 0x70:
      //user sent 'p' so we send the power_on command
      send4(1);
      //Serial.println("power on - Dish");
      break;
    case 0x73:
      // 's' means 'select'
      send4(16);
      //Serial.println("select");
      break;
    case 0x75:
      // 'u' means 'up'
      send4(26);
      //Serial.println("up");
      break;
    case 0x30:
      // '0' button
      send4(17);
      //Serial.println("zero");
      break;
    case 0x31:
      // '1' button
      send4(4);
      break;
    case 0x32:
      // '2' button
      send4(5);
      break;
    case 0x33:
      // '3' button
      send4(6);
      break;
    case 0x34:
      // '4' button
      send4(8);
      break;
    case 0x35:
      // '5' button
      send4(9);
      break;
    case 0x36:
      // '6' button
      send4(10);
      break;
    case 0x37:
      // '7' button
      send4(12);
      break;
    case 0x38:
      // '8' button
      send4(13);
      break;
    case 0x39:
      // '9' button
      send4(14);
      break;
  }
  delay(50);
}


void send4(long code) {
  int unit = 0x240; //remote has 'unit code' 10
  code <<= 10;
  long data = code | unit; 
  for (int i = 0; i < 4; i++) {
    irsend.sendDISH(data, 16);
  }
}
  
