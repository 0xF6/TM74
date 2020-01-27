#pragma once
#ifndef TM74_h
#define TM74_h
#include "Segment.h"
class TM74
{
  public:
    TM74(int pinSCLK, int _pinRCLK, int pinDIO);
    void write(unsigned char X);
	void write(unsigned char X, unsigned char port);
	void writeWithDot(unsigned char X, unsigned char port);

	void writeSegments(const Segment segs[], uint8_t size);

	void clear();
  protected:
    void reset();
    void relock(const uint8_t flag);

	int _pinRCLK;
	int _pinDIO;
	int _pinSCLK;
};

#endif
