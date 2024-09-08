/*
    Библиотека для управления симисторным диммером с Arduino
    Документация:
    GitHub: https://github.com/GyverLibs/GyverDimmer
    Возможности:
    - Одноканальный и многоканальный диммер по алгоритму Брезенхема
    - Одноканальный и многоканальный фазовый диммер

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - переделан FastIO
    v1.1.1 - убран FastIO
    v1.2 - исправил баг в DimmerBres и DimmerBresMulti
*/

#ifndef GyverDimmer_h
#define GyverDimmer_h
#include <Arduino.h>
#include <GyverIO.h>

// брезенхем одноканальный
template <uint8_t _D_PIN>
class DimmerBres {
   public:
    DimmerBres() {
        gio::init(_D_PIN, OUTPUT);
        gio::write(_D_PIN, LOW);
    }

    void write(uint8_t dim) {
        dimmer = dim;
    }

    void tick() {
        uint16_t val = ((uint16_t)++count * dimmer) >> 8;
        if (lastVal != (val != last)) gio::write(_D_PIN, val != last);
        lastVal = (val != last);
        last = val;
    }

   private:
    uint8_t count = 0, last = 0, lastVal = 0, dimmer = 0;
};

// брезенхем многоканальный
template <uint8_t _D_AMOUNT>
class DimmerBresMulti {
   public:
    void attach(uint8_t num, uint8_t pin) {
        dimPins[num] = pin;
        gio::init(pin, OUTPUT);
    }

    void write(uint8_t ch, uint8_t dim) {
        dimmer[ch] = dim;
    }

    void tick() {
        count++;
        for (uint8_t i = 0; i < _D_AMOUNT; i++) {
            uint16_t val = ((uint16_t)count * dimmer[i]) >> 8;
            if (lastState[i] != (val != last[i])) gio::write(dimPins[i], val != last[i]);
            lastState[i] = (val != last[i]);
            last[i] = val;
        }
    }

   private:
    uint8_t count, last[_D_AMOUNT], lastState[_D_AMOUNT], dimmer[_D_AMOUNT], dimPins[_D_AMOUNT];
};

// плавный диммер одноканальный
template <uint8_t _D_PIN>
class Dimmer {
   public:
    Dimmer(uint8_t freq = 50) {
        gio::init(_D_PIN, OUTPUT);
        gio::write(_D_PIN, LOW);
        maxVal = (freq == 50) ? 9300 : 7600;
    }

    void write(uint8_t dim) {
        dimmer = map(dim, 0, 255, maxVal, 500);
    }

    bool tickZero() {
        gio::write(_D_PIN, LOW);
        if (lastDim != dimmer) {
            lastDim = dimmer;
            return true;
        }
        return false;
    }

    void tickTimer() {
        gio::write(_D_PIN, HIGH);
    }

    uint16_t getPeriod() {
        return dimmer;
    }

   private:
    uint16_t dimmer = 0, lastDim = 0, maxVal = 0;
};

// плавный диммер многоканальный
template <uint8_t _D_AMOUNT>
class DimmerMulti {
   public:
    DimmerMulti(uint8_t freq = 50) {
        maxVal = (freq == 50) ? 9300 : 7600;
    }

    void attach(uint8_t num, uint8_t pin) {
        gio::init(pin, OUTPUT);
        dimPins[num] = pin;
    }

    void write(uint8_t ch, uint8_t dim) {
        dimmer[ch] = dim;
    }

    void tickZero() {
        counter = 255;
    }

    void tickTimer() {
        for (uint8_t i = 0; i < _D_AMOUNT; i++) {
            if (counter == dimmer[i]) gio::write(dimPins[i], 1);           // на текущем тике включаем
            else if (counter == dimmer[i] - 1) gio::write(dimPins[i], 0);  // на следующем выключаем
        }
        counter--;
    }

    uint16_t getPeriod() {
        return (maxVal == 9300) ? 37 : 31;  // us
    }

   private:
    uint8_t dimmer[_D_AMOUNT], dimPins[_D_AMOUNT];
    uint16_t maxVal = 0;
    volatile uint16_t counter = 0;
};

#endif
