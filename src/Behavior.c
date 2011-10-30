// Macro to match imprecise measurements to a range of possible values
#define DELTA(a,b,c) (a < b + c && a > b - c)  
#define AT_BASE_WITH_FREQUENCY(n) (DELTA(timer.frequency, n, 0.3))
/*
Attempts to match frequency to one of the known frequencies of stations. 
If a frequency is matched it executes a 'dance' and returns 1 (may not return immediately).
Otherwise returns 0.
*/
/* is my picture showing now?*/
int dance() {
  if(AT_BASE_WITH_FREQUENCY(0.5)) {
    BehaviorLog("Dancin' to the tune of a frequency 0.5");
    driveBack();
    sleep(3);
    turnOnSpotLeft();
    sleep(10);
  } else if(AT_BASE_WITH_FREQUENCY(1)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 1");
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(10);
    //  get to new base
    turnOnSpotLeft();
    sleep(5);
    orientStraightAndDrive(1);
    sleep(2);
  } else if(AT_BASE_WITH_FREQUENCY(2)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 2");
    driveBack();
    sleep(1);
    stop();
    sleep(1);
    driveBack();
    // get to new base
    turnOnSpotRight();
    sleep(3);
    orientStraightAndDrive(1);
    sleep(2);
  } else if(AT_BASE_WITH_FREQUENCY(4)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 4");
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(5);
    // get to next base
    turnOnSpotRight();
    sleep(7);
    orientStraightAndDrive(1);
    sleep(2);
  } else if(AT_BASE_WITH_FREQUENCY(6)) {
    BehaviorLog("Dancin' to the tune of a frequency 6");
    driveBack();
    sleep(2);
    turnOnSpotRight();
    sleep(5);
  } else if(AT_BASE_WITH_FREQUENCY(8)) {
    BehaviorLog("Dancin' to the tune of a frequency 8");
    // dance
    driveBack();
    sleep(2);
    stop();
    sleep(3);
    orientStraightAndDrive(1);
    sleep(1);
    //  get to new base
    turnOnSpotLeft();
    sleep(8);
    orientStraightAndDrive(1);
    sleep(2);
  } else { // no reasonable frequency detected
    timer.frequency = 0;
    return 0;
  }
  BehaviorLog("Danced");
  state.AverageBaseLight = (float)10000;
  timer.frequency = 0;
  return 1;
}

/*
Main behavior function.
Called every 50ms unless something happens.
*/
void behave() {
  // Stuck detection
  if(state.expectedMovement != None && state.SpinSensor < 20) { // stuck
    if(state.expectedMovement == Forwards) {
      CPhidgetMotorControl_setVelocity (motoControl, 0, -75);
      msleep(400L);
    } else {
      CPhidgetMotorControl_setVelocity (motoControl, 0, 75);
      msleep(400L);
    }
  } else if(LEFT_LIGHT && !RIGHT_LIGHT) {
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
    } else*/ 
    if(state.FrontFacingIR > 420 && state.TopIR < 200 || timer.frequency > 0.1) { // We see the gap
      if(timer.frequency > 0.1)  {
        BehaviorLog("Seeing the gap (F: %d, T: %d)", state.FrontFacingIR, state.TopIR);
        BehaviorLog("Top Lights. Frequency: %f", timer.frequency);
        if(!dance()) {
          BehaviorLog("Didn't dance");
          orientStraightAndDrive(0.5);
          sleep(2);
        }
      } else {
        BehaviorLog("Seeing the gap (F: %d, T: %d), but don't have frequency", state.FrontFacingIR, state.TopIR);
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
      msleep(1500L);
  	  //goTowards(120,0.5);
    } else if(state.RightWhisker == 0 && state.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
      if(timer.enteredFrom = Right) {
        retreat(0);
      } else {
        retreat(1);
      }
      msleep(1500L);
  	  //goTowards(60,0.5);
    } else if(state.RightWhisker && state.LeftWhisker) {
      BehaviorLog("Both whiskers");
      retreat(0);
      msleep(1500L);
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
