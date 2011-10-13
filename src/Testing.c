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
	goTowards(20);
	sleep(2);
	stop();
	teardown();
	return 0;
}

