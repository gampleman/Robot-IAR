#define TURNING_DURATION 4
#define LIGHT_THRESHOLD 160
void behave() {
  //BehaviorIDebug(state.LeftLight);
  //BehaviorIDebug(state.RightLight);
  if(state.LeftLight > LIGHT_THRESHOLD && state.RightLight < LIGHT_THRESHOLD) {
    goTowards(20,0.5);
    BehaviorLog("Left light triggered");
  }
  else if (state.LeftLight < LIGHT_THRESHOLD && state.RightLight > LIGHT_THRESHOLD) {
    goTowards(160,0.5);
    BehaviorLog("Right light triggered");
  }
  else if (state.LeftLight > LIGHT_THRESHOLD && state.RightLight > LIGHT_THRESHOLD) {
    //BehaviorLog("Both lights triggered");
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
      BehaviorLog("Both light and left whisker");
      goTowards(80,0.5);
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
  	  goTowards(100,0.5);
    } else if(state.RightWhisker && state.LeftWhisker)  {
      BehaviorLog("Both light and both whiskers");
     	  stop();
      	  sleep(2);
      	  driveBack();
      	  sleep(3);
      	  turnOnSpotLeft();
      	  sleep(3);
    } else {
      BehaviorLog("Both light and no whiskers");
      orientStraightAndDrive(0.5);
    }
  }
   else if(state.LeftWhisker)  {
   BehaviorLog("Left whisker triggered");  
   retreat(0);
   sleep(1);
   driveBack();
  }
  else if(state.RightWhisker) {
    BehaviorLog("Reft whisker triggered");  
    retreat(1);
    sleep(1); 
    driveBack();
  }
  else if(state.FrontFacingIR > 350) {
    BehaviorLog("IR triggered (%d)", state.FrontFacingIR);
    driveBack();
    retreat(1);
    sleep(1);
    driveBack();
  }
	else if(timer.iteration > timer.threshold && timer.iteration < timer.threshold + TURNING_DURATION) {
    BehaviorLog("Turning %d", timer.threshold + TURNING_DURATION - timer.iteration);
    goTowards(30,1);
	}
	else {
		orientStraightAndDrive(1);
	}
}
