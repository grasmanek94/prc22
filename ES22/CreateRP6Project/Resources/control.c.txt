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
}

void loop(void)
{

}