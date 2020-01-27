#pragma once
#ifndef __SEGMENT__
#define __SEGMENT__
#include "Arduino.h"

typedef uint8_t u2_t;
#define FALSE 0
#define TRUE  1
#define INVALID_SEGMENT ((unsigned char)0b00110110)
struct Segment{
	public:
		Segment(uint8_t number) 
            : Segment(number, FALSE) { };
		Segment(uint8_t number, u2_t dot) 
            : Segment(static_cast<char>(number), dot) { };
		Segment(char symbol)
            : Segment(symbol, FALSE) { };
		Segment(char symbol, u2_t dot);

		unsigned char getRaw() { return this->raw; }
		u2_t isDot () { return this->dot; }
	protected:
        u2_t findInFonts(char symbol);
		unsigned char cast2raw(char symbol);
		char toLower_r(char symbol);

		unsigned char raw;
		u2_t    dot;
};

#endif
