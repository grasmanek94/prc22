#include <RP6RobotBaseLib.h>
#include <someCommonLib.h>
#include "base.h"

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
	initRobotBase();
}

void loop(void)
{

}