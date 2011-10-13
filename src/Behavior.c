#define TURNING_DURATION 4
#define LIGHT_THRESHOLD 160
void behave() {
  printf("\n\n\nLeft Light: %d, Right Light: %d\n\n\n", state.LeftLight, state.RightLight);
  if(state.LeftLight > LIGHT_THRESHOLD && state.RightLight < LIGHT_THRESHOLD) {
    goTowards(20);

  }
  else if (state.LeftLight < LIGHT_THRESHOLD && state.RightLight > LIGHT_THRESHOLD) {
    goTowards(160);

  }
  else if (state.LeftLight > LIGHT_THRESHOLD && state.RightLight > LIGHT_THRESHOLD) {
    // orientStraightAndDrive();
    // sleep(2);
    //stop();
    // sleep(2);
    // driveBack();
    // sleep(2);
    // turnOnSpotLeft();
    // sleep(2);
    //stop();
    //sleep(2);
    if(state.LeftWhisker && state.RightWhisker == 0)  {
      goTowards(80);
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
  	  goTowards(100);
    } else if(state.RightWhisker && state.LeftWhisker)  {
     	  stop();
      	  sleep(2);
      	  driveBack();
      	  sleep(4);
      	  turnOnSpotLeft();
      	  sleep(3);
    } else {
      orientStraightAndDrive();
    }
  }
  // else if(state.LeftWhisker)  {
  //  retreat(0);
  //  sleep(1);
  //  driveBack();
  // }
  // else if(state.RightWhisker) {
  //  retreat(1);
  //  sleep(1); 
  //  driveBack();
  // }
  // else if(state.FrontFacingIR > 350) {
  //  driveBack();
  //  retreat(1);
  //  sleep(1);
  //  driveBack();
  // }
	else if(timer.iteration > timer.threshold && timer.iteration < timer.threshold + TURNING_DURATION) {
    turnOnSpotLeft();
	}
	else {
		orientStraightAndDrive();
	}
}
