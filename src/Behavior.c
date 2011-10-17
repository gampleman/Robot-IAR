#define TURNING_DURATION 4
#define LIGHT_INCREASE_THRESHOLD 0.3

#define LEFT_LIGHT (state.AverageBaseLight / state.LeftLight > LIGHT_INCREASE_THRESHOLD)
#define RIGHT_LIGHT (state.AverageBaseLight / state.RightLight > LIGHT_INCREASE_THRESHOLD)

void behave() {
  BehaviorIDebug(state.LeftLight);
  BehaviorIDebug(state.RightLight);
  if(!LEFT_LIGHT && !RIGHT_LIGHT) {
    state.AverageBaseLight = (state.LeftLight + state.RightLight) / 2;
  }
  if(LEFT_LIGHT && !RIGHT_LIGHT) {
    goTowards(20,0.5);
    BehaviorLog("Left light triggered");
  }
  else if (!LEFT_LIGHT && RIGHT_LIGHT) {
    goTowards(160,0.5);
    BehaviorLog("Right light triggered");
  }
  else if (LEFT_LIGHT && RIGHT_LIGHT) {
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
	else if(timer.iteration > timer.threshold && timer.iteration < (timer.threshold + TURNING_DURATION)) {
    BehaviorLog("Turning %d, threshold: %d, iteration: %d", timer.threshold + TURNING_DURATION - timer.iteration, timer.threshold, timer.iteration);
    goTowards(30,1);
	}
	else {
		orientStraightAndDrive(1);
	}
}
