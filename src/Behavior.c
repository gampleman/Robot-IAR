void behave() {
  if(LEFT_LIGHT && !RIGHT_LIGHT) {
    goTowards(20,0.5);
    BehaviorLog("Left light triggered");
  }
  else if (!LEFT_LIGHT && RIGHT_LIGHT) {
    goTowards(160,0.5);
    BehaviorLog("Right light triggered");
  }
  else if (LEFT_LIGHT && RIGHT_LIGHT) {
    if(TOP_LEFT_LIGHT)  {
      BehaviorLog("Top Left Light. Frequency: %f", timer.frequency);
      stop();
    } else if(TOP_RIGHT_LIGHT) {
      BehaviorLog("Top Right Light. Frequency: %f", timer.frequency);
      stop();
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
  	  goTowards(120,0.5);
    } else if(state.RightWhisker == 0 && state.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
  	  goTowards(60,0.5);
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
    BehaviorLog("Right whisker triggered");  
    retreat(1);
    sleep(1); 
    driveBack();
  }
  else if(state.FrontFacingIR > 420) {
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
