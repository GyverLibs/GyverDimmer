This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverDimmer.svg?color=brightgreen)](https://github.com/GyverLibs/GyverDimmer/releases/latest/download/GyverDimmer.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverDimmer.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverDimmer)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverDimmer?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverDimmer
Library for managing a simistor dimmer with Arduino
- Single and multichannel dimmer according to the Bresenham algorithm
- Single and Multichannel Phase Dimmer

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverDimmer** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverDimmer/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
DimmerBres<пин> dim;                // dimmer
DimmerBresMulti<количество> dim;    // multichannel dimmer in Bresenham
Dimmer<пин> dim;                    // phase dimmer
DimmerMulti<количество> dim;        // multichannel phase dimmer
```

<a id="usage"></a>
## Use of use
```cpp
// ====== DimmerBres ======
void write(uint8_t dim);    // set the dimming value 0-255
void tick();                // interrupt

// ====== DimmerBresMulti ======
void attach(uint8_t num, uint8_t pin);  // connect channel number num to pin pin
void write(uint8_t ch, uint8_t dim);    // set the dimming value 0-255 on the channel ch
void tick();                            // interrupt

// ====== Dimmer ======
void write(uint8_t dim);    // set the dimming value 0-255
bool tickZero();            // interrupt
void tickTimer();           // timer
int getPeriod();            // timer

// ====== DimmerMulti ======
void attach(uint8_t num, uint8_t pin);  // connect channel number num to pin pin
void write(uint8_t ch, uint8_t dim);    // set the dimming value 0-255 on the channel ch
bool tickZero();            // interrupt
void tickTimer();           // timer
int getPeriod();            // timer
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
// one-channel test on Bresenham

#define D_PIN 5
// zero cross on D2

#include <GyverDimmer.h>
DimmerBres<D_PIN> dim;   // pin

void setup() {
  // shutter
  attachInterrupt(0, isr, RISING);  // D2 == 0
}

void isr() {
  dim.tick(); // ticulate
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
- v1.1.1 - FastIO removed
- v1.2 - Fixed a bug in DimmerBres and DimmerBresMulti

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
