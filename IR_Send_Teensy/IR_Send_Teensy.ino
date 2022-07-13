#include <IRremote.h>
IRsend irsend;

// This code will work for Teensy 2.0 board (Transmit Pin 10). Also "Leonardo" or "Arduino/Genuino Micro" or "Pro Micro" board (pin 9 for Pro Micro). 
// See https://www.pjrc.com/teensy/td_libs_IRremote.html
// See also https://www.arduino.cc/reference/en/libraries/irremote/

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
  delay(100);
  Serial.print("Ready");
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    long type = Serial.parseInt();
    // do it again:
    unsigned long data = Serial.parseInt();
    // do it again:
    unsigned long len = Serial.parseInt();

    // user input must be decimal. The two numbers can be separated with spaces and/or commas. 
    // for example, to send NEC code 0x04fb83, send "0,326531,16"

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') 
    {
      // print the numbers in one string as hexadecimal:
      Serial.print(type, HEX);
      Serial.print(", ");
      Serial.print(data, HEX);
      Serial.print(", ");
      Serial.println(len, HEX);

      switch (type) {
          case 0:
            irsend.sendNEC(data, 32);
            for (int i=0;i<len;i++)
            {
              delay(100);
              irsend.sendNEC(REPEAT, 32);
            }
            break;                        
          case 3:
            for (int i=0;i<3;i++)
            {
              irsend.sendSAMSUNG(data, len);
            }
            break;
          case 4:
            for (int i=0;i<3;i++)
            {
              irsend.sendSony(data, len);
            }
            break;
          case 5:            
            for (int i=0;i<3;i++)
            {
              delay(100);
              irsend.sendRC5(data, len);
            }
            break;
          case 6:
            for (int i=0;i<3;i++)
            {
              delay(100);
              irsend.sendRC6(data, len);
            }
          default:
            // if nothing else matches, do the default
            // default is optional
            send4(data);
          break;
        }
    }
  }
}


// DISH remote always sends the same code 4 times
void send4(long code) {
  for (int i = 0; i < 4; i++) {
    irsend.sendDISH(code, 16); //sendDISH always leaves the LED on, that's curious, but inconsequential
    //delay(10);
  }
}
  