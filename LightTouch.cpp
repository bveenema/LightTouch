//  LightTouch.h ---------------------------------------------------------------
//  A lightweight touchscreen library (4 wire) for particle devices. Scans the
//  touchscreeen for touches and outputs position after debouncing.
//  Debouncing is accomplished with oversampling scan detection.
//
//  update() must be called regularly from main loop.  When update returns true,
//  main loop can call getX() and getY() for position data.
//
//  Postion data can be mapped to an LCD screen by defining MAPTOSCREEN and
//  determining the min and max, X and Y value of the touchscreen
//
//  Inspired by Touch_4Wire library by ScruffR and Adafruit Touch library
//
//  Created by Veen Nov. 24 2015
//------------------------------------------------------------------------------



#include "LightTouch.h"

LightTouch::LightTouch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
}

bool LightTouch::update(){
  static bool previousTouch = 0;
  bool returnVal = 0;
  //  Scan Touchscreen and read X and Y if touch is present
  _touch = scan();
  if(_touch>0){
    readTouchY();
    readTouchX();
  }

  // Wait for two positive scan results
  if(previousTouch + _touch > 1){
    returnVal = 1;
  }
  previousTouch = _touch;

  return returnVal;
}

bool LightTouch::scan(){
  pinMode(_xp, OUTPUT);
  pinResetFast(_xp);

  pinMode(_xm, INPUT);
  pinMode(_yp, INPUT);
  pinMode(_ym, INPUT_PULLUP);


  //Wait for output to settle
  delayMicroseconds(15);

  if(digitalRead(_ym)){
    return 0;
  }else{
    return 1;
  }
}

int16_t LightTouch::readTouchX(void) {
  pinMode(_xp, OUTPUT);
  pinMode(_xm, OUTPUT);
  pinMode(_yp, INPUT);
  pinMode(_ym, INPUT);

  pinSetFast(_xp);
  pinResetFast(_xm);
  _ADCx = analogRead(_yp);

  #if INVERTX == 1
    _xCoord = ADC_MAX_VALUE - _ADCx;
  #endif

  return _xCoord;
}

int16_t LightTouch::readTouchY(void) {
  pinMode(_xp, INPUT);
  pinMode(_xm, INPUT);
  pinMode(_yp, OUTPUT);
  pinMode(_ym, OUTPUT);

  pinSetFast(_yp);
  pinResetFast(_ym);
  _ADCy = analogRead(_xm);

  #if INVERTY == 1
    _yCoord = ADC_MAX_VALUE - _ADCy;
  #endif

  return _yCoord;
}

int16_t LightTouch::getX(void){
  #ifdef MAPTOSCREEN
    _xCoord = map(_xCoord,TOUCHXMIN,TOUCHXMAX,LCDXMIN,LCDXMAX);
  #endif
  return _xCoord;
}
int16_t LightTouch::getY(void){
  #ifdef MAPTOSCREEN
    _yCoord = map(_yCoord,TOUCHYMIN,TOUCHYMAX,LCDYMIN,LCDYMAX);
  #endif
  return _yCoord;
}
