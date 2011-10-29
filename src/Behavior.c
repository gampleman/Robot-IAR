// Macro to match imprecise measurements to a range of possible values
#define DELTA(a,b,c) (a < b + c && a > b - c)  

/*
Attempts to match frequency to one of the known frequencies of stations. 
If a frequency is matched it executes a 'dance' and returns 1 (may not return immediately).
Otherwise returns 0.
*/
int dance() {
  if(DELTA(timer.frequency, 0.5, 0.25)) {
    driveBack();
    sleep(3);
    turnOnSpotLeft();
    sleep(10);
  } else if(DELTA(timer.frequency, 1, 0.3)) {
    BehaviorLog("Dancin' to the tune of a frequency 1");
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(10);
  } else if(DELTA(timer.frequency, 2, 0.5)) {
    driveBack();
    sleep(2);
    stop();
    sleep(3);
    driveBack();
  } else if(DELTA(timer.frequency, 4, 1)) {
    driveBack();
    sleep(2);
    turnOnSpotLeft();
    sleep(5);
  } else if(DELTA(timer.frequency, 6, 1)) {
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(5);
  } else if(DELTA(timer.frequency, 8, 1)) {
    // dance
    driveBack();
    sleep(2);
    stop();
    sleep(3);
    orientStraightAndDrive(1);
    sleep(1);
    //  get to new base
    turnOnSpotLeft();
    sleep(6);
    orientStraightAndDrive(1);
    sleep(2);
  } else {
    return 0;
  }
  return 1;
}

/*
Main behavior function.
Called every 50ms unless something happens.
*/
void behave() {
  
  if(LEFT_LIGHT && !RIGHT_LIGHT) {
    goTowards(80,0.5);
    BehaviorLog("Left light triggered");
    //Enter(Right)
  }
  else if (!LEFT_LIGHT && RIGHT_LIGHT) {
    goTowards(130,0.5);
    BehaviorLog("Right light triggered");
    //Enter(Left)
  }
  else if (LEFT_LIGHT && RIGHT_LIGHT) {
   // if(state.SonarValue > )
    /*if(TOP_LIGHT)  {
      BehaviorLog("Top Lights. Frequency: %f", timer.frequency);
      dance();
      //stop();
    } else*/ if(state.FrontFacingIR > 420 && state.TopIR < 200) { // We see the gap
      if(TOP_LIGHT)  {
        BehaviorLog("Seeing the gap (F: %d, T: %d)", state.FrontFacingIR, state.TopIR);
        BehaviorLog("Top Lights. Frequency: %f", timer.frequency);
        if(!dance()) {
          orientStraightAndDrive(0.5);
          sleep(2);
        }
        //stop();
      } else {
        BehaviorLog("Seeing the gap (F: %d, T: %d)", state.FrontFacingIR, state.TopIR);
        orientStraightAndDrive(0.5);
        sleep(2);
      }
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
      if(timer.enteredFrom = Left) {
        retreat(1);
      } else {
        retreat(0);
      }
      sleep(1);
  	  goTowards(120,0.5);
    } else if(state.RightWhisker == 0 && state.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
      if(timer.enteredFrom = Right) {
        retreat(0);
      } else {
        retreat(1);
      }
      sleep(1);
  	  goTowards(60,0.5);
    } else if(state.RightWhisker && state.LeftWhisker) {
      BehaviorLog("Both whiskers");
      retreat(0);
      sleep(1);
    } /*else if(rand() % 10 == 0) {
      sweepWithSonar();
    }*/ else { // No whiskers 
      BehaviorLog("Both light and either no whiskers");
      orientStraightAndDrive(0.5);
      //goTowards(130,0.5);
    }
  }
  else if(state.LeftWhisker)  {
    BehaviorLog("Left whisker triggered");  
    retreat(0);
    sleep(1);
    driveBack();
    timer.enteredFrom = Unknown;
  }
  else if(state.RightWhisker) {
    BehaviorLog("Right whisker triggered");  
    retreat(1);
    sleep(1); 
    driveBack();
    timer.enteredFrom = Unknown;
  }
  else if(state.FrontFacingIR > 420) {
    BehaviorLog("IR triggered (%d)", state.FrontFacingIR);
    driveBack();
    retreat(1);
    sleep(1);
    driveBack();
    timer.enteredFrom = Unknown;
  }
	else if(timer.iteration > timer.threshold && timer.iteration < (timer.threshold + TURNING_DURATION)) {
    BehaviorLog("Turning %d, threshold: %d, iteration: %d", timer.threshold + TURNING_DURATION - timer.iteration, timer.threshold, timer.iteration);
    goTowards(30,1);
    timer.enteredFrom = Unknown;
	}
	else {
    timer.enteredFrom = Unknown;
		orientStraightAndDrive(1);
	}
}
