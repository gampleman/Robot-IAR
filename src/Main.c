#include <stdio.h>
#include <stdlib.h>
#include <phidget21.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>
#ifndef NO_POWERLIB
#include <libpowerbutton.h>
#endif
#include "Debug.c"
#include "Types.c"
#include "Setup.c"
#include "Movement.c"
#include "Behavior.c"

int __nsleep(const struct timespec *req, struct timespec *rem)
{
    struct timespec temp_rem;
    if(nanosleep(req,rem)==-1)
        __nsleep(rem,&temp_rem);
    else
        return 1;
}
 
int msleep(unsigned long milisec)
{
    struct timespec req={0},rem={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    __nsleep(&req,&rem);
    return 1;
}

int main(int argc, char* argv[])
{
	setup();
	orientStraightAndDrive(1);
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

