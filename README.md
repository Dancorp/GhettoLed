Changelog
- 05/23/2018 : Adding Autostandby Mode to turn on/off lights automaticly (based on volume level)
- 05/21/2018 : Adding Random Mode on pattern/Vu sequence.
- 04/2018 : Adding more Aux1 patterns


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
- GhettoLED Rev1.0 on a JVC M70 : https://youtu.be/DNqbE8rCtKw
- GhettoLED Rev1.2 on a National RS-4150 : https://www.facebook.com/NeoFunkyBlaster/videos/451267188665635/
 
## Compatible devices
Every boombox equiped with a lineout can be upgraded.
The challenge is about led integration. (speakers/grid shape) but they can be placed everywhere (radio scale, tape...)

## Known issues:
- Some little ground noise due to the Switched-mode power supply (Filtering needed)

## How to customize the code
- You need to set the number of LED on each LED strip. (N_PIXELS / N_PIXELS_AUX1 / N_PIXELS_AUX2)
- Depending your coding skills, you can change colors on some templates. (firsts VU for exemple)
- You need to install somes libraries and use Arduino v1.65 in case of crashs. (to be confirmed)
https://github.com/carlynorama/Arduino-Library-Button
https://github.com/FastLED/FastLED


## How to use it
By default, all lights are turned off.
A short press on button allows to:
- Turn on the lights in Auto Standby Mode
- Switch Pattern selection from Auto Change to Random Change and finally to Manual mode by selecting the next pattern.

A long press on button allows to:
- Turn on the lights in "Always On" Mode
- Turn off the lights

## What i need to make it ?
- An Arduino UNO
https://www.aliexpress.com/item/32523366108.html

- I recommend to use WS2812 strip led with 100 Leds / Meter because of the black PCB/Led (check pics) (1M 100 IP30)
https://www.aliexpress.com/item/2036819167.html

- Depending your setup, you may need a dedicated power supply 
Guide: https://github.com/thehookup/Holiday_LEDs_2.0/blob/master/Strip%20Wattage.pdf
https://www.aliexpress.com/item/32822508171.html

- Do your own Shield or use an Arduino prototyping board :
https://www.ebay.com/itm/263092669047

- Some components (see Schematics folder)

## Help needed !
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


