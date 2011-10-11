#include <stdio.h>
#include <stdlib.h>
#include <phidget21.h>
#include <unistd.h>
#include <math.h>
#ifndef NO_POWERLIB
#include <libpowerbutton.h>
#endif
#include "Types.c"
#include "Setup.c"
#include "Movement.c"
#include "Behavior.c"



int main(int argc, char* argv[])
{
	setup();
	orientStraightAndDrive();
	#ifdef NO_POWERLIB
	while(1)
	#else
	while(power_button_get_value()<2)
	#endif
	{
    timer.iteration++;
    behave();
    if(timer.iteration == timer.threshold + TURNING_DURATION) {
      timer.iteration = 0;
      timer.threshold += 2;
    }
		sleep(0.1);
	}
	stop();
	teardown();
	return 0;
}

