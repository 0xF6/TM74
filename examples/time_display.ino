#include "TM74.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#define SCLK A0
#define RCLK A1
#define DIO  A2

TM74 disp(SCLK, RCLK, DIO);

String to2digitsStr(uint8_t number) {
  if(number == 0)
    return "00";
  if(number > 0 && number < 10)
    return "0" + String(number);
  return String(number);
}

void deconstructAndDisplay(String str, uint8_t second)
{
  const Segment segs[4] = {
    Segment(str[3]),
    Segment(str[2]),
    Segment(str[1], second % 2 == 0),
    Segment(str[0])
  };
  disp.writeSegments(segs, sizeof(segs) / sizeof(Segment));
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    String n1 = to2digitsStr(tm.Hour);
    String n2 = to2digitsStr(tm.Minute);
    deconstructAndDisplay(n1 + n2, tm.Second);
  }
  else delay(1500);
}
void setup() { }
