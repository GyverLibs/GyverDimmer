[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverDimmer.svg?color=brightgreen)](https://github.com/GyverLibs/GyverDimmer/releases/latest/download/GyverDimmer.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverDimmer.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverDimmer)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverDimmer?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverDimmer
Библиотека для управления симисторным диммером с Arduino
- Одноканальный и многоканальный диммер по алгоритму Брезенхема
- Одноканальный и многоканальный фазовый диммер

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverDimmer** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverDimmer/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
DimmerBres<пин> dim;                // диммер по Брезенхему
DimmerBresMulti<количество> dim;    // многоканальный диммер по Брезенхему
Dimmer<пин> dim;                    // фазовый диммер
DimmerMulti<количество> dim;        // многоканальный фазовый диммер
```

<a id="usage"></a>
## Использование
```cpp
// ====== DimmerBres ======
void write(uint8_t dim);    // установить величину диммирования 0-255
void tick();                // вызывать в прерывании детектора нуля

// ====== DimmerBresMulti ======
void attach(uint8_t num, uint8_t pin);  // подключить канал под номером num на пин pin
void write(uint8_t ch, uint8_t dim);    // установить величину диммирования 0-255 на канал ch
void tick();                            // вызывать в прерывании детектора нуля

// ====== Dimmer ======
void write(uint8_t dim);    // установить величину диммирования 0-255
bool tickZero();            // вызывать в прерывании детектора нуля
void tickTimer();           // вызывать в прерывании таймера 
int getPeriod();            // получить период для таймера

// ====== DimmerMulti ======
void attach(uint8_t num, uint8_t pin);  // подключить канал под номером num на пин pin
void write(uint8_t ch, uint8_t dim);    // установить величину диммирования 0-255 на канал ch
bool tickZero();            // вызывать в прерывании детектора нуля
void tickTimer();           // вызывать в прерывании таймера 
int getPeriod();            // получить период для таймера
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
// тест одного канала по Брезенхему

#define D_PIN 5
// zero cross на D2

#include <GyverDimmer.h>
DimmerBres<D_PIN> dim;   // указать пин диммера

void setup() {
  // завести прерывание на детектор нуля
  attachInterrupt(0, isr, RISING);  // D2 == 0
}

void isr() {
  dim.tick(); // вызывать тик в прерывании детектора нуля
}

void loop() {
  // принимает 0-255
  dim.write(analogRead(A0) / 4);
  delay(100);
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - переделан FastIO
- v1.1.1 - убран FastIO
- v1.2 - исправил баг в DimmerBres и DimmerBresMulti

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
