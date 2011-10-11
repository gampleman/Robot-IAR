#include <stdio.h>
#include <phidget21.h>
#include <unistd.h>
#include <math.h>
#include <libpowerbutton.h>
#include "Types.c"
#include "Setup.c"
#include "Movement.c"
#include "Behavior.c"



int main(int argc, char* argv[])
{
	setup();
	orientStraightAndDrive();
	while(power_button_get_value()<2)
	{
    timer.iteration++;
    behave();
    if(timer.iteration == timer.threshold + TURNING_DURATION) {
      timer.iteration = 0;
      timer.threshold += 2;
    }
		sleep(0.2);
	}
	stop();
	teardown();
	return 0;
}

