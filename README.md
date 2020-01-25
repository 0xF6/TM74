<!-- Logo -->
<p align="center">
  <a href="#">
    <img height="128" width="128" src="https://user-images.githubusercontent.com/13326808/73127381-6e083300-3fd0-11ea-9aa5-31a5440eb5b0.png">
  </a>
</p>
<!-- Name -->
<h1 align="center">
  TM74 LED Driver
</h1>
<!-- desc -->
<h4 align="center">
  Arduino library for 4-Bit LED Digital Tube Module with two 74HC595D-chip
</h4>

<!-- popup badges -->
<p align="center">
  <a href="https://t.me/ivysola">
    <img src="https://img.shields.io/badge/Ask%20Me-Anything-1f425f.svg?style=popout-square&logo=telegram">
  </a>
</p>

<!-- big badges -->
<p align="center">
  <a href="#">
    <img src="https://forthebadge.com/images/badges/made-with-c-plus-plus.svg">
    <img src="https://forthebadge.com/images/badges/oooo-kill-em.svg">
    <img src="https://forthebadge.com/images/badges/ages-18.svg">
    <img src="https://forthebadge.com/images/badges/powered-by-electricity.svg">
  </a>
</p>

![image](https://user-images.githubusercontent.com/13326808/73127222-38fae100-3fce-11ea-9098-d9fb9eaf9d93.png)
![image](https://user-images.githubusercontent.com/13326808/73127230-4d3ede00-3fce-11ea-9542-80a3bd1fc1c2.png)



### Usage

```cpp

// A0   A1   A2   5V  GND
//  |    |    |    |   |
// SCLK RCLK DIO  VCC GND

// SCLK, RCLK and DIO - control pins for this module
// VCC - 5V pin
// GND - zero pin
#include "TM74.h"
#define SCLK A0 
#define RCLK A1 
#define DIO  A2

TM74 disp(SCLK, RCLK, DIO);

const uint8_t useDot = 0x1;


void setup() 
{ 
    // fill segment data
    const Segment segs[4] = {
        Segment('1'), // 4 display
        Segment('1'), // 3 display
        Segment('2', useDot), // 2 display with enabled dot indication
        Segment('3') // 1 display
    };
    // send data to module
    disp.writeSegments(segs, sizeof(segs) / sizeof(Segment));
}

```

#### Symbols support for using in Segment

```cpp
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
'A', 'b', 'C', 'd', 'E', 'F'
'°' // (degree)
'-' // (minus)
```

### Examples


`/examples/time_display.ino` - with using RTC module displaying current time on current display