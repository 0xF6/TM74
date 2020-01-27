#include "Segment.h"
#include <Arduino.h>
const unsigned char digitToSegment[19] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
    0b10001000, // A
    0b10000011, // b
    0b11000110, // C
    0b10100001, // d
    0b10000110, // E
    0b10001110, // f
    0b10011100, // ° (degree)
    0b10111111, // - (minus),
    INVALID_SEGMENT  // INVALID_SEGMENT 
};
const char digitToChar[19] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    'a', 'b', 'c', 'd', 'e', 'f', '\xb0', '-', '#'
};




Segment::Segment(char symbol, u2_t dot)
{
    this->raw = cast2raw(symbol);
    this->dot = dot;
}

char Segment::toLower_r(char s)
{
    switch (s)
    {
        case 'A': return 'a';
        case 'B': return 'b';
        case 'C': return 'c';
        case 'D': return 'd';
        case 'E': return 'e';
        case 'F': return 'f';
        default:
            return s;
    }
}


unsigned char Segment::cast2raw(char symbol)
{
    auto index = findInFonts(symbol);
    if(index == -1)
        return INVALID_SEGMENT;
    return digitToSegment[index];
}


uint8_t Segment::findInFonts(char symbol)
{
    auto size = sizeof(digitToSegment);
    auto target = toLower_r(symbol);
    for(auto i = 0; i != size; i++)
    {
        if(digitToChar[i] == target)
            return i;
    }
    return -1;
}

