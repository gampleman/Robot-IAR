#define TURNING_DURATION 4
void behave() {
	if(state.LeftWhisker)  {
		retreat(0);
		sleep(1);
		driveBack();
	}
	else if(state.RightWhisker) {
		retreat(1);
		sleep(1);
		driveBack();
	}
	else if(state.FrontFacingIR > 350) {
		driveBack();
		retreat(1);
		sleep(1);
		driveBack();
	}
	else if(timer.iteration > timer.threshold && timer.iteration < timer.threshold + TURNING_DURATION) {
    turnOnSpotLeft();
	}
	else {
		orientStraightAndDrive();
	}
}