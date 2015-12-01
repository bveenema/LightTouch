//  LightTouch.h ---------------------------------------------------------------
//  A lightweight touchscreen library (4 wire) for particle devices. Scans the
//  touchscreeen for touches and outputs position after debouncing.
//  Debouncing is accomplished with oversampling scan detection.
//
//  update() must be called regularly from main loop.  When update returns true,
//  main loop can call getX() and getY() for position data.
//
//  Postion data can be mapped to an LCD screen by defining MAPTOSCREEN and
//  determining the min and max, X and Y values of the touchscreen
//
//  Inspired by Touch_4Wire library by ScruffR and Adafruit Touch library
//
//  Created by Veen Nov. 24 2015
//------------------------------------------------------------------------------

#ifndef LightTouch_h
#define LightTouch_h

//Set INVERTX or INVERTY to 1 to invert the respective axis
#define INVERTX 1
#define INVERTY 1

//Use the commented code in the demo to determine the edges of the touchscreeen;
//TOUCHXMIN, TOUCHYMIN, TOUCHXMAX, TOUCHYMAX. If MAPTOSCREEN is defined, the
//returned vale when getX() or getY() is called will be mapped to the lcd pixels
//Rounh Touch X and Y min and max down or up respectively to give a margin of 50
//on the min and max bounds
#define MAPTOSCREEN
#ifdef MAPTOSCREEN
#define TOUCHXMIN 280
#define TOUCHYMIN 300
#define TOUCHXMAX 3800
#define TOUCHYMAX 3500

#define LCDXMIN 0
#define LCDYMIN 0
#define LCDXMAX 128
#define LCDYMAX 64
#endif

#include "application.h"

//Make sure all versions of Particle FW have FastIO
#if (SYSTEM_VERSION < 0x00040400) // no fast pin functions before 0.4.4
#if defined(STM32F2XX)  // for the Photon and friends
#define pinResetFast(_pin)	               (PIN_MAP[_pin].gpio_peripheral->BSRRH = PIN_MAP[_pin].gpio_pin)
#define pinSetFast(_pin)	                 (PIN_MAP[_pin].gpio_peripheral->BSRRL = PIN_MAP[_pin].gpio_pin)
#elif defined(STM32F10X_MD)  // for the Core
#define pinResetFast(_pin)	               (PIN_MAP[_pin].gpio_peripheral->BRR = PIN_MAP[_pin].gpio_pin)
#define pinSetFast(_pin)	                 (PIN_MAP[_pin].gpio_peripheral->BSRR = PIN_MAP[_pin].gpio_pin)
#endif
#define digitalWriteFast(_pin, _hilo)      (_hilo ? pinSetFast(_pin) : pinResetFast(_pin))
#define pinReadFast(_pin)                  (PIN_MAP[_pin].gpio_peripheral->IDR & PIN_MAP[_pin].gpio_pin ? 0xFF : LOW)
#endif

#define ADC_MAX_VALUE (0x0FFF)

class LightTouch {
 public:
  LightTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);

  bool update(void);
  int16_t getX(void);
  int16_t getY(void);
  bool scan(void);
  int16_t readTouchY(void);
  int16_t readTouchX(void);

private:
  bool _touch;
  uint8_t _yp, _ym, _xm, _xp;
  uint16_t _ADCx, _ADCy;
  int16_t _xCoord, _yCoord;
};

#endif
