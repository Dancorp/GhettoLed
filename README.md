![GhettoLed on a JVC M70](https://hackadaycom.files.wordpress.com/2018/01/ghettoled_boombox_arduino_led_strips.jpg)


# GhettoLed

**An evolved LED Mod for your sound machine based on Arduino.**

- Arduino Uno based
- Addressable Led strips (Left/Right channels & a custom static one)
- Stereo sound responsive from lineout
- Works on any sources
- A switch allow to turn lights on/off and change pattern.
- Customisable effects
- Manual, Autochange, Random patterns
- Can Manage : 2 "Stereo" Led Strips et 2 additionals Strips (Aux1 for a pattern, Aux2 for the "mode" color)

## What's it look like?
GhettoLED Rev1.0 on a JVC M70 : https://youtu.be/DNqbE8rCtKw
 
## Compatible devices
Every boombox equiped with a lineout can be upgraded.
The challenge is about led integration. (speakers/grid shape) but they can be placed everywhere (radio scale, tape...)

## Known issues:
- Some little ground noise due to the Switched-mode power supply (Filtering needed)

## How to customize the code
- You need to set the number of LED on each LED strip.
- Depending your coding skills, you can change colors on some templates. (firsts VU for exemple)
- You need to install FastLed library and use Arduino 1.65 software to prevent crashs.
- to be continued...

## How to use it
By default, all lights are turned off.
A short press on button allows to:
- Turn on the lights in Auto mode (predefined sequence)
- Switch to Manual mode and select the next pattern.

A long press on button allows to:
- Turn on the lights in Random mode
- Turn off the lights

## What i need to make it ?
- An Arduino UNO
https://fr.aliexpress.com/item/UNO-R3-CH340G-ATmega328P-compatible-for-Arduino-UNO-R3/32523366108.html

- I recommend to use WS2812 strip led with 100 Leds / Meter because of the black PCB/Led (check pics) (1M 100 IP30)
https://fr.aliexpress.com/item/1m-4m-5m-WS2812B-Smart-led-pixel-strip-Black-White-PCB-30-60-144-leds-m/2036819167.html

- Depending your setup, you may need a dedicated power supply (5V 6A)
https://fr.aliexpress.com/item/LED-AC110V-220V-TO-DC-12V-24V-5V-1A-2A-5A-8A-10A-15A-20A-30A/32822508171.html

- Do your own Shield or use an Arduino prototyping board :
https://www.ebay.com/itm/263092669047

- Some components (see Schematics folder)

## Help needed !
- Most templates have been created for a linear system. If some have a correct visual rendering, others would need to be adapted to the round shape. (-fire- for exemple)
Anyone can propose modified or original templates.
- Regarding electronics, I need tips on filtering to remove power supply and LED noise.
- Looking for a way to turn off light when a silence is detected during a predefined time. (a kind of autostop)

## Resources
- Some pics for the JVC M70 integration : https://photos.app.goo.gl/I8EfIdO2DLxacI033
- Some pics of my prototyping board for the JVC M70 : https://photos.app.goo.gl/AQ6XMqi3j0m6LJvz1



## Original Topic on Boomboxery (not updated anymore)
http://boomboxery.com/forum/index.php/topic/26495-evolved-led-mod-for-jvc-m70/


**This source code is based on Scott Marley and Cine-Lights works.**
- Cine-Lights : https://www.youtube.com/channel/UCOG6Bi2kvpDa1c8gHWZI5CQ
- Scott Marley : https://www.youtube.com/user/scottmarley85


