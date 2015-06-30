#include <RP6RobotBaseLib.h>
#include <someCommonLib.h>
#include "base.h"
#include "RP6I2CmasterTWI.h"     // Include the I2C-Bus Slave Library

/*****************************************************************************/
// I2C

/**
* This function gets called automatically if there was an I2C Error like
* the slave sent a "not acknowledge" (NACK, error codes e.g. 0x20 or 0x30).
* The most common mistakes are:
*   - using the wrong address for the slave
*   - slave not active or not connected to the I2C-Bus
*   - too fast requests for a slower slave
* Be sure to check this if you get I2C errors!
*/
void I2C_transmissionError(uint8_t errorState)
{
	writeString_P("\nI2C ERROR - TWI STATE: 0x");
	writeInteger(errorState, HEX);
	writeChar('\n');
}

#define ARDUINO_ADDRESS       (42)
#define ARDUINO_WRITE_ADDRESS (ARDUINO_ADDRESS << 1)
#define ARDUINO_READ_ADDRESS (ARDUINO_WRITE_ADDRESS  + 1)

int main(void)
{
	initRobotBase();

	I2CTWI_initMaster(100);

	I2CTWI_setTransmissionErrorHandler(I2C_transmissionError);

	powerON();

	startStopwatch1();

	uint8_t value = 38;
	while (true)
	{
		task_I2CTWI(); // Call I2C Management routine
		task_RP6System();

		if (getStopwatch1() > 1000)
		{
			setStopwatch1(1);

			value ^= 64;
			I2CTWI_transmitByte(ARDUINO_WRITE_ADDRESS, value);
			writeString("Written value: <");
			writeInteger(value, DEC);
			writeString("> Read value: <");
			writeInteger(I2CTWI_readByte(ARDUINO_READ_ADDRESS), DEC);
			writeString(">\r\n");
		}
	}
	return 0;
}
