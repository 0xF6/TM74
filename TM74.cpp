extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include <Arduino.h>
#include "./TM74.h"
#include "./Segment.h"

TM74::TM74(int pinSCLK, int pinRCLK, int pinDIO)
{
  _pinSCLK = pinSCLK;
  _pinRCLK = pinRCLK;
  _pinDIO  = pinDIO ;

  pinMode(pinSCLK, OUTPUT);
  pinMode(pinRCLK, OUTPUT);
  pinMode(pinDIO , OUTPUT);

  reset();
}

void TM74::relock(const uint8_t flag)
{
  int targetPin = 0;

  if(flag == 0x1) targetPin = _pinSCLK;
  else            targetPin = _pinRCLK;
  
  digitalWrite(targetPin, LOW);
  digitalWrite(targetPin, HIGH);  
}
void TM74::write(unsigned char ref)
{
  for (int i = 8; i >= 1; i--)
  {
    if (ref & 0x80)
      digitalWrite(_pinDIO, HIGH);
    else  
      digitalWrite(_pinDIO, LOW);
    ref <<= 1;
    relock(0x1);
    if (digitalRead(_pinDIO) == 0)
      pinMode(_pinDIO, HIGH);
  }
}

void TM74::writeSegments(const Segment segs[], uint8_t size)
{
  uint8_t modules[] = {
    0b0001,
    0b0010,
    0b0100,
    0b1000
  };
  if(size != 4)
  {
    for(auto i = 0; i != sizeof(modules) / sizeof(uint8_t); i++)
      write(INVALID_SEGMENT, modules[i]);
    return;
  }
  
  for(auto i = 0; i != sizeof(modules); i++)
  {
    auto segment = segs[i];
    auto modulePort = modules[i];

    if(segment.isDot())
      writeWithDot(segment.getRaw(), modulePort);
    else
      write(segment.getRaw(), modulePort);
  }
}

void TM74::reset()
{
  digitalWrite(_pinSCLK, HIGH);
  digitalWrite(_pinRCLK, HIGH);
  digitalWrite(_pinDIO , HIGH);
}

void TM74::writeWithDot(unsigned char data, unsigned char port)
{
  data &= ~'\u0080';
  write(data, port);
}

void TM74::write(unsigned char X, unsigned char port)
{
  write(X);
  write(port);
  relock(0x0);
}
