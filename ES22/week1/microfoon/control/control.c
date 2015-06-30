#include <RP6ControlLib.h>
#include <someCommonLib.h>
#include "control.h"

int main(void)
{
	setup();
	someCommonFunction();
	while(true) 
	{
		loop();
	}
	return 0;
}

void setup(void)
{
	initRP6Control();

	setLEDs(0b0000);
	dischargePeakDetector();

	initLCD();
	clearLCD();
}

void loop(void)
{
	static uint8_t ledstate = 1;
	uint16_t tmp = getMicrophonePeak();
	
	clearLCD();
	writeIntegerLengthLCD(tmp, DEC, 4);
	writeCharLCD(':');
	writeIntegerLengthLCD((uint16_t)ledstate, DEC, 4);
	
	if (tmp > 512)
	{
		ledstate <<= 1;
		if (ledstate == 16)
		{
			ledstate = 1;
		}
	}

	setLEDs(ledstate);
	mSleep(100);
}