# LightTouch
A lightweight touchscreen library (4 wire) for particle devices. Scans the touchscreeen for touches and outputs position after debouncing. Debouncing is accomplished with oversampling scan detection.

update() must be called regularly from main loop.  When update returns true, main loop can call getX() and getY() for position data.

Postion data can be mapped to an LCD screen by defining MAPTOSCREEN and determining the min and max, X and Y values of the touchscreen.

Inspired by Touch_4Wire library by ScruffR and Adafruit Touch library

Created by Veen Nov. 24 2015
