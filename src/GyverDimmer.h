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

// брезенхем одноканальный
template < uint8_t _D_PIN >
class DimmerBres {
public:
    DimmerBres() {
        pinMode(_D_PIN, OUTPUT);
        fastWrite(_D_PIN, LOW);
    }
    void write(uint8_t dim) {
        dimmer = dim;
    }
    void tick() {		
        int val = ((uint16_t)++count * dimmer) >> 8;		
        if (lastVal != (val != last)) fastWrite(_D_PIN, val != last);
        lastVal = (val != last);
        last = val;
    }
private:
    uint8_t count = 0, last = 0, lastVal = 0, dimmer = 0;
    void fastWrite(const uint8_t pin, bool val) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        if (pin < 8) bitWrite(PORTD, pin, val);
        else if (pin < 14) bitWrite(PORTB, (pin - 8), val);
        else if (pin < 20) bitWrite(PORTC, (pin - 14), val);
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
        bitWrite(PORTB, pin, val);
#else
        digitalWrite(pin, val);
#endif
    }
};

// брезенхем многоканальный
template < uint8_t _D_AMOUNT >
class DimmerBresMulti {
public:
    void attach(uint8_t num, uint8_t pin) {
        dimPins[num] = pin;
        pinMode(pin, OUTPUT);
    }
    void write(uint8_t ch, uint8_t dim) {
        dimmer[ch] = dim;
    }
    void tick() {		
        count++;
        for (byte i = 0; i < _D_AMOUNT; i++) {
            int val = ((uint16_t)count * dimmer[i]) >> 8;
            if (lastState[i] != (val != last[i])) fastWrite(dimPins[i], val != last[i]);
            lastState[i] = (val != last[i]);
            last[i] = val;
        }
    }
private:
    uint8_t count, last[_D_AMOUNT], lastState[_D_AMOUNT], dimmer[_D_AMOUNT], dimPins[_D_AMOUNT];
    void fastWrite(const uint8_t pin, bool val) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        if (pin < 8) bitWrite(PORTD, pin, val);
        else if (pin < 14) bitWrite(PORTB, (pin - 8), val);
        else if (pin < 20) bitWrite(PORTC, (pin - 14), val);
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
        bitWrite(PORTB, pin, val);
#else
        digitalWrite(pin, val);
#endif
    }
};

// плавный диммер одноканальный
template < uint8_t _D_PIN >
class Dimmer {
public:
    Dimmer(uint8_t freq = 50) {
        pinMode(_D_PIN, OUTPUT);
        fastWrite(_D_PIN, LOW);
        if (freq == 50) maxVal = 9300;
        else maxVal = 7600;
    }
    void write(uint8_t dim) {
        dimmer = map(dim, 0, 255, maxVal, 500);
    }
    bool tickZero() {
        fastWrite(_D_PIN, LOW);
        if (lastDim != dimmer) {
            lastDim = dimmer;
            return true;
        }
        return false;
    }
    void tickTimer() {
        fastWrite(_D_PIN, HIGH);
    }
    int getPeriod() {
        return dimmer;
    }
    
private:
    int dimmer = 0, lastDim = 0;
    int maxVal = 0;
    void fastWrite(const uint8_t pin, bool val) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        if (pin < 8) bitWrite(PORTD, pin, val);
        else if (pin < 14) bitWrite(PORTB, (pin - 8), val);
        else if (pin < 20) bitWrite(PORTC, (pin - 14), val);
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
        bitWrite(PORTB, pin, val);
#else
        digitalWrite(pin, val);
#endif
    }
};

// плавный диммер многоканальный
template < uint8_t _D_AMOUNT >
class DimmerMulti {
public:
    DimmerMulti(uint8_t freq = 50) {
        if (freq == 50) maxVal = 9300;
        else maxVal = 7600;
    }
    void attach(uint8_t num, uint8_t pin) {
        dimPins[num] = pin;
        pinMode(pin, OUTPUT);
    }
    void write(uint8_t ch, uint8_t dim) {
        dimmer[ch] = dim;
    }
    bool tickZero() {
        counter = 255;
    }
    void tickTimer() {
        for (byte i = 0; i < _D_AMOUNT; i++) {
            if (counter == dimmer[i]) fastWrite(dimPins[i], 1);  			// на текущем тике включаем
            else if (counter == dimmer[i] - 1) fastWrite(dimPins[i], 0);  	// на следующем выключаем
        }
        counter--;
    }
    int getPeriod() {
        return (maxVal == 9300) ? 37 : 31;	// us
    }
    
private:
    uint8_t dimmer[_D_AMOUNT], dimPins[_D_AMOUNT];
    int maxVal = 0;
    volatile int counter = 0;
    void fastWrite(const uint8_t pin, bool val) {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        if (pin < 8) bitWrite(PORTD, pin, val);
        else if (pin < 14) bitWrite(PORTB, (pin - 8), val);
        else if (pin < 20) bitWrite(PORTC, (pin - 14), val);
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny13__)
        bitWrite(PORTB, pin, val);
#else
        digitalWrite(pin, val);
#endif
    }
};

#endif