This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverDimmer
Triac dimmer control library with Arduino
- Single and multi-channel Bresenham dimmer
- Single and multi-channel phase dimmer

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverDimmer** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GyverDimmer/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
DimmerBres<pin> dim;// Bresenham dimmer
DimmerBresMulti<number> dim; // Bresenham multi-channel dimmer
Dimmer<pin> dim; // phase dimmer
DimmerMulti<number> dim; // multi-channel phase dimmer
```

<a id="usage"></a>
## Usage
```cpp
// ====== DimmerBres ======
void write(uint8_t dim); // set dimming amount 0-255
void tick(); // call in zero detector interrupt

// ====== DimmerBresMulti ======
void attach(uint8_t num, uint8_t pin); // connect channel number num to pin pin
void write(uint8_t ch, uint8_t dim); // set dimming amount 0-255 per channel ch
void tick(); // call in zero detector interrupt

// ====== Dimmer ======
void write(uint8_t dim); // set dimming amount 0-255
bool tickZero(); // call in zero detector interrupt
void tickTimer(); // call in a timer interrupt
int getPeriod(); // get period for timer

// ====== DimmerMulti ======
void attach(uint8_t num, uint8_t pin); // connect channel number num to pin pin
void write(uint8_t ch, uint8_t dim); // set dimming amount 0-255 per channel ch
bool tickZero(); // call in zero detector interrupt
void tickTimer(); // call in a timer interrupt
int getPeriod(); // get period for timer
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
// test of one channel according to Bresenham

#define D_PIN 5
// zero cross on D2

#include <GyverDimmer.h>
DimmerBres<D_PIN> dim; // specify dimmer pin

void setup() {
  // start an interrupt on the zero detector
  attachInterrupt(0, isr, RISING); // D2 == 0
}

void isr() {
  dim.tick(); // call tick in null detector interrupt
}

void loop() {
  // takes 0-255
  dim.write(analogRead(A0) / 4);
  delay(100);
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - redesigned FastIO
- v1.1.1 - yBran FastIO
- v1.2 - fixed bug in DimmerBres and DimmerBresMulti

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!