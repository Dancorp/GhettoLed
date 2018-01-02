# GhettoLed

**An evolved LED Mod for your sound machine based on Arduino.**

- Arduino Uno based
- Addressable Led strips (Left/Right channels & a custom static one)
- Stereo sound responsive from lineout
- Works on any sources
- A switch allow to turn lights on/off and change pattern.
- Manual or Autochange patterns

**Vidéo : https://www.youtube.com/watch?v=5PWkd7Fl-ms **


## How to customize the code
You need to set the number of LED on each LED strip.
You need to install FastLed library and use Arduino 1.65 software to prevent crashs.
(to be continued)


## How to use it
By default, all lights are turned off.
A short press on button allows to:
- Turn on the lights in manual mode
- Manually change the pattern.

A long press on button allows to:
- Turn on the lights in auto mode
- Turn off the lights

## What i need to make it ?
- An Arduino UNO
https://fr.aliexpress.com/item/UNO-R3-CH340G-ATmega328P-compatible-for-Arduino-UNO-R3/32523366108.html

- I recommand to use WS2812 strip led with 100 Leds / Meter because of the black PCB/Led (check pics) (1M 100 IP30)
https://fr.aliexpress.com/item/1m-4m-5m-WS2812B-Smart-led-pixel-strip-Black-White-PCB-30-60-144-leds-m/2036819167.html

- Depending your setup, you may need a dedicated power supply (5V 6A)
https://fr.aliexpress.com/item/LED-AC110V-220V-TO-DC-12V-24V-5V-1A-2A-5A-8A-10A-15A-20A-30A/32822508171.html

- For now, there is not PCB layout to share, i use an Arduino prototyping board :
https://www.ebay.com/itm/263092669047

- Some components (see Schematics folder)

## Resources
Some pics for the JVC M70 integration : https://photos.app.goo.gl/I8EfIdO2DLxacI033
Some pics of my prototyping board for the JVC M70 : https://photos.app.goo.gl/AQ6XMqi3j0m6LJvz1



## Original Topic on Boomboxery
http://boomboxery.com/forum/index.php/topic/26495-evolved-led-mod-for-jvc-m70/


**This source code is based on Scott Marley and Cine-Lights works.**
Cine-Lights : https://www.youtube.com/channel/UCOG6Bi2kvpDa1c8gHWZI5CQ
Scott Marley : https://www.youtube.com/user/scottmarley85


