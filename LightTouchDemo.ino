#include "LightTouch.h"

//Define Pins : XP and YM can be digital Pins
#define XP A0
#define YP A1
#define XM A2
#define YM A3


LightTouch Touch = LightTouch(XP, YP, XM, YM);

SYSTEM_MODE(SEMI_AUTOMATIC);


void setup(){
	Serial.begin(57600);
	delay(1000);

}
void loop(){
	int16_t touchY = 0;
	int16_t touchX = 0;
	uint8_t isTouching = Touch.update();
	if(isTouching){
		touchX = Touch.getX();
		touchY = Touch.getY();
		Serial.print("X = "); Serial.print(touchX);
		Serial.print("\tY = "); Serial.print(touchY);
		Serial.println(" ");
		delay(100);
	}


	//	Use these functions for finding the edge, setting invert and origin and
	//	testing a touchscreen
	/*bool isTouching = Touch.scan();
	static uint32_t loopCounter = 0;
	static uint32_t previousSerialDisplayTime = 0;
	int16_t touchY = Touch.readTouchY();
	int16_t touchX = Touch.readTouchX();
	if(millis()-previousSerialDisplayTime > 100){
		Serial.print("X = \t");
		Serial.print(touchX);
		Serial.print("\tY = \t"); Serial.print(touchY);
		Serial.print("\tisTouching = \t");Serial.print(isTouching);
		Serial.print("\tLoops: \t");Serial.print(loopCounter);
		Serial.println(" ");
		loopCounter = 0;
		previousSerialDisplayTime = millis();
	}
	loopCounter++;*/
}
