# LightTouch
A lightweight touchscreen library (4 wire) for particle devices. Scans the touchscreeen for touches and outputs position after debouncing. Debouncing is accomplished with oversampling scan detection.

update() must be called regularly from main loop.  When update returns true, main loop can call getX() and getY() for position data.

Position data can be mapped to an LCD screen by defining MAPTOSCREEN and determining the min and max, X and Y values of the touchscreen.

Pressure readings can be performed by defining EnablePressureRead in the header file.
Pressure varies with X position and is not recommended for reliable detection of touches.

Inspired by Touch_4Wire library by ScruffR and Adafruit Touch library

Created by Veen Nov. 24 2015


<b>LightTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym)</b>

<b>bool update(void)</b>

<b>int16_t getX(void)</b>

<b>int16_t getY(void)</b>

<b>bool scan(void)</b>

<b>int16_t readTouchY(void)</b>

<b>int16_t readTouchX(void)</b>

<b>void setRXPlate(uint16_t rxPlate)</b>

<b>int16_t readPressure(void)</b>

<b>int16_t getPressure(void)</b>
