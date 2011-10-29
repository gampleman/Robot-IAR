#include <stdio.h>
#include <stdlib.h>
#include <phidget21.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#ifndef NO_POWERLIB
#include <libpowerbutton.h>
#endif
#include "Debug.c"
#include "Utils.c"
#include "State.c"
#include "Sensors.c"
#include "Setup.c"
#include "Movement.c"
#include "Behavior.c"


int main(int argc, char* argv[])
{
	setup();
	orientStraightAndDrive(1);
	// Makes it compile on OSX for faster development
	#ifdef NO_POWERLIB
	while(1)
	#else
	while(power_button_get_value()<2)
	#endif
	{
    timer.iteration++;
    timer.timeSinceLastLight++;
    behave();
    if(timer.iteration == (timer.threshold + TURNING_DURATION)) {
      timer.iteration = 0;
      timer.threshold += 4;
    }
		msleep(50L);
	}
	stop();
	teardown();
	return 0;
}

