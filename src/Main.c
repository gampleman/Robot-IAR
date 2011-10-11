// - InterfaceKit simple -
// This simple example simply creates an InterfaceKit handle, hooks the event handlers and opens it.  It then waits
// for an InterfaceKit to be attached and waits for events to be fired. We progress through three steps, 1. Normal settings, 
// 2. Setting analog sensor sensitivity to 100, 3. Toggling Ratiometric, waiting for user input to proceed to next step to allow 
// data to be read.
//
// Copyright 2008 Phidgets Inc.  All rights reserved.
// This work is licensed under the Creative Commons Attribution 2.5 Canada License. 
// view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/

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
      timer.threshold++;
    }
		sleep(0.2);
	}
	stop();
	teardown();
	return 0;
}

