//
// 1. Install library: Time, DS1307RTC
// 2. Connect TM74 at
//  A0   A1   A2   5V  GND - Arduino
//   |    |    |    |   |
//  SCLK RCLK DIO  VCC GND - TM74
// 3. Connect RTC module
//  SDA  SCL       GND  5V  - Arduino
//   |    |         |    |
//  SDA  SCL  SQW  GND  VCC - RTC module (DS1307RTC)
// 4. Compile and upload firmware
// 5. You are great ❤️❤️❤️
//

#include "TM74.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#define SCLK A0
#define RCLK A1
#define DIO  A2

TM74 disp(SCLK, RCLK, DIO);

// Decomposite 1-2 digit to template string
String to2digitsStr(uint8_t number) {
  if(number == 0)
    return "00";
  if(number > 0 && number < 10)
    return "0" + String(number);
  return String(number);
}

// Decomposite 4-char string to Segment and send to LED driver
void deconstructAndDisplay(String str, uint8_t second)
{
  const Segment segs[4] = {
    Segment(str[3]),
    Segment(str[2]),
    Segment(str[1], second % 2 == 0), // every second blink dot in second LED segment
    Segment(str[0])
  };
  disp.writeSegments(segs, sizeof(segs) / sizeof(Segment));
}

// main loop
void loop() {
  tmElements_t tm;    // time structure
  if (RTC.read(tm)) { // start RTC read
    String n1 = to2digitsStr(tm.Hour);   // read Hour and cast to string
    String n2 = to2digitsStr(tm.Minute); // read minute and cast to string
    deconstructAndDisplay(n1 + n2, tm.Second); // composite string
  }
  else delay(1500); // delay when RTC module has error
}
void setup() { }
