homeBerry
=========

Bored of getting up to open the door for your cat and then realizing that the cat is just messing with you?
With homBerry automation system now you can leave him outside without even moving from your couch !!

The idea is to control a home form a web interface using a rasberryPi as server and n microcontrollers to do the dirty job like taking temperatures, pressures, swiching things (such as ligths, doors, windows,...) and whatever you want.

The comunication is done over a i2c network wich is nice because is cheap, reliable, only has 2 wires, is multimaster and also is directlly implemented on the rasPi and a lot of microcontrollers like atmegas or PICs.

The raspi also will host a website to control and read values from the microcontrollers.
