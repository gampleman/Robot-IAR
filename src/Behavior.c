#define DELTA(a,b) (a - 0.1 < b && a + 0.1 > b)  

void dance() {
  if(DELTA(timer.frequency, 0.5)) {
    driveBack();
    sleep(3);
    turnOnSpotLeft();
    sleep(10);
  } else if(DELTA(timer.frequency, 1)) {
    BehaviorLog("Dancin' to the tune of a frequency 1");
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(10);
  } else if(DELTA(timer.frequency, 2)) {
    driveBack();
    sleep(2);
    stop();
    sleep(3);
    driveBack();
  } else if(DELTA(timer.frequency, 4)) {
    driveBack();
    sleep(2);
    turnOnSpotLeft();
    sleep(5);
  } else if(DELTA(timer.frequency, 6)) {
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(5);
  } else if(DELTA(timer.frequency, 8)) {
    driveBack();
    sleep(2);
    stop();
    sleep(3);
    orientStraightAndDrive(1);
    sleep(1);
  } 
  
}


void behave() {
  dance();
  return;
  
  if(LEFT_LIGHT && !RIGHT_LIGHT) {
    goTowards(20,0.5);
    BehaviorLog("Left light triggered");
  }
  else if (!LEFT_LIGHT && RIGHT_LIGHT) {
    goTowards(160,0.5);
    BehaviorLog("Right light triggered");
  }
  else if (LEFT_LIGHT && RIGHT_LIGHT) {
    if(TOP_LIGHT)  {
      BehaviorLog("Top Lights. Frequency: %f", timer.frequency);
      dance();
      //stop();
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
  	  goTowards(120,0.5);
    } else if(state.RightWhisker == 0 && state.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
  	  goTowards(60,0.5);
    } else {
      BehaviorLog("Both light and either no or both(!!!!) whiskers");
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
