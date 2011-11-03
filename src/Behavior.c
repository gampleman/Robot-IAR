// Macro to match imprecise measurements to a range of possible values
#define DELTA(a,b,c) (a < b + c && a > b - c)  
#define AT_BASE_WITH_FREQUENCY(n) (DELTA(timer.frequency, n, 0.3))



/*
Attempts to match frequency to one of the known frequencies of stations. 
If a frequency is matched it executes a 'dance' and returns 1 (may not return immediately).
Otherwise returns 0.
*/
int dance() {
  Heading heading;
  if(state.LeftWhisker && state.RightWhisker) {
    heading = Straight;
  } else if(state.LeftWhisker) {
    heading = Rightish;
  } else if(state.RightWhisker) {
    heading = Leftish;
  }
  if(AT_BASE_WITH_FREQUENCY(0.5)) {
    BehaviorLog("Dancin' to the tune of a frequency 0.5");
    driveBack();
    pause(0.5);
    turnOnSpotLeft();
    pause(6);
    // get to a new base
    ontoTheNextOne(0, heading);
  } else if(AT_BASE_WITH_FREQUENCY(1)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 1");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(6);
    //  get to new base
    ontoTheNextOne(1, heading);
  } else if(AT_BASE_WITH_FREQUENCY(2)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 2");
    driveBack();
    pause(0.5);
    stop();
    pause(1);
    driveBack();
    // get to new base
    ontoTheNextOne(2, heading);
  } else if(AT_BASE_WITH_FREQUENCY(4)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 4");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(3); // 180deg turn
    // get to next base
    ontoTheNextOne(4, heading);
  } else if(AT_BASE_WITH_FREQUENCY(6)) {
    BehaviorLog("Dancin' to the tune of a frequency 6");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(3); // 180deg turn
    //get to next base
    ontoTheNextOne(6, heading);
  } else if(AT_BASE_WITH_FREQUENCY(8)) {
    BehaviorLog("Dancin' to the tune of a frequency 8");
    // dance
    driveBack();
    pause(3);
    stop();
    pause(1);
    orientStraightAndDrive(1);
    pause(1);
    stop();
    pause(0.8);
    turnOnSpotRight();
    pause(1.5);
    //  get to new base
    ontoTheNextOne(8, heading);
  } else { // no reasonable frequency detected
    timer.frequency = 0;
    return 0;
  }
  BehaviorLog("Danced");
  state.AverageBaseLight = (float)10000;
  timer.frequency = 0;
  state.wasOnBlackInLastIteration = 0;
  return 1;
  state.movedOntoTheNextOne = 0;
}



/*
Main behavior function.
Called every 50ms unless something happens.
*/
void behave() {
  // Stuck detection
  //SensorLog("current spin input: %d, previous spin input %d", state.SpinSensor, state.previousState);
  if(state.SpinSensor == state.previousState) {
    state.stuckCounter++;
  } else {
    state.stuckCounter = 0;
    state.expectedFor = 0;
  }
  if (state.stuckCounter > 6) {
      state.expectedFor = state.expectedFor + 1;
      state.stuckCounter = 0;
      BehaviorLog("stuck cycle %d", state.expectedFor);
  }
  state.previousState = state.SpinSensor;
  if(state.expectedMovement != None && state.expectedFor > 2) { // stuck
    SensorLog("expectedfor weirdo value %d", state.expectedFor);
    state.expectedFor = 0;
    if(state.expectedMovement == Forwards) {
      BehaviorLog("Stuck and was moving forward");
      driveBack();
      sleep(1);
      if(state.lastWhiskerTriggered == Left) {
        retreat(Right);
      } else {
        retreat(Left);
      }
      msleep(1500L);
    } else {
      BehaviorLog("Stuck and was moving backwards");
      orientStraightAndDrive(1);
      msleep(1500L);
    }
  } /*else if(LEFT_LIGHT && !RIGHT_LIGHT) {
    goTowards(80,0.5);
    BehaviorLog("Left light triggered");
    //Enter(Right)
  }
  else if (!LEFT_LIGHT && RIGHT_LIGHT) {
    goTowards(130,0.5);
    BehaviorLog("Right light triggered");
    //Enter(Left)
  }*/
  else if (LEFT_LIGHT || RIGHT_LIGHT) {
   state.wasOnBlackInLastIteration = 1;
   state.IRcausedExitFromBlack = 1;
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
        } else {
          state.sawFrequency = 0;
        }
      } else {
        BehaviorLog("Seeing the gap (F: %d, T: %d), but don't have frequency", state.FrontFacingIR, state.TopIR);
        orientStraightAndDrive(0.5);
        sleep(2);
      }
    } else if(state.RightWhisker && state.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
      //if(timer.enteredFrom = Left) {
      //  retreat(1);
      //} else {
        retreat(Left);
      //}
      msleep(700);
      //driveBack();
      state.lastWhiskerTriggered = Right;
  	  //goTowards(120,0.5);
    } else if(state.RightWhisker == 0 && state.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
      //if(timer.enteredFrom = Right) {
      //  retreat(0);
      //} else {
        retreat(Right);
      //}
      msleep(700);
      //driveBack();
      state.lastWhiskerTriggered = Left;
  	  //goTowards(60,0.5);
    } else if(state.RightWhisker && state.LeftWhisker) {
      BehaviorLog("Both whiskers");
      retreat(Left);
      sleep(1);
      driveBack();
    }  else if(state.FrontFacingIR > 420) {
      BehaviorLog("Light & IR triggered (%d)", state.FrontFacingIR);
      driveBack();
      state.IRcausedExitFromBlack = 0;
      if(state.lastWhiskerTriggered == Right) {
        retreat(Right);
        state.lastWhiskerTriggered = Left;
      } else {
        retreat(Left);
        state.lastWhiskerTriggered = Right;
      }
      msleep(500);
      //driveBack();
  }/*else if(rand() % 10 == 0) {
      sweepWithSonar();
    }*/ else { // No whiskers 
      BehaviorLog("Both light and no whiskers");
      orientStraightAndDrive(0.5);
      //goTowards(130,0.5);
  
    }
  
  } 
  #if 1
  else {
    if(state.wasOnBlackInLastIteration) {
      BehaviorLog("Exited black area and trying to return.");
      if(state.exitTrialCounter < 5) {
        /*if (state.IRcausedExitFromBlack) {
          turnOnSpotRight();
          sleep(1);
          orientStraightAndDrive(1);
          msleep(800L);
          state.IRcausedExitFromBlack = 1;
        } else*/ if(state.lastWhiskerTriggered == Right) {
          /*driveBack();
          sleep(1);
          turnOnSpotRight();
          sleep(2);
          retreat(Right);
          sleep(3);
          turnOnSpotRight();
          sleep(1);*/
          turnOnSpotLeft();
          pause(0.6);
          orientStraightAndDrive(1);
        } else {
          /*driveBack();
          sleep(1);
          turnOnSpotLeft();
          sleep(2);
          retreat(Left);
          sleep(3);
          turnOnSpotLeft();
          sleep(1);*/
            turnOnSpotRight();
            pause(0.6);
            orientStraightAndDrive(1);
        }
        state.exitTrialCounter = state.exitTrialCounter + 1;
      } else {
        state.exitTrialCounter = 0;
        BehaviorLog("I'm fed up with this station... :( I'm moving on");
        if (state.sawFrequency && state.movedOntoTheNextOne) {
          if (AT_BASE_WITH_FREQUENCY((int)timer.frequency)) {
            ontoTheNextOne((int)timer.frequency, Straight);
          } else {
            ontoTheNextOne((int)timer.frequency + 1, Straight);
          }
        } else {
          ontoTheNextOne(100, Straight);
        }
      }
    }
    else if(state.LeftWhisker)  {
      BehaviorLog("Left whisker triggered");  
      retreat(Right);
      sleep(1);
      timer.enteredFrom = Unknown;
      state.lastWhiskerTriggered = Left;
    }
    else if(state.RightWhisker) {
      BehaviorLog("Right whisker triggered");  
      retreat(Left);
      sleep(1); 
      driveBack();
      timer.enteredFrom = Unknown;
      state.lastWhiskerTriggered = Right;
    }
    else if(state.FrontFacingIR > 450) {
      BehaviorLog("IR triggered (%d)", state.FrontFacingIR);
      driveBack();
      if(state.lastWhiskerTriggered == Right) {
        retreat(Right);
      } else {
        retreat(Left);
      }
      sleep(1);
      driveBack();
      timer.enteredFrom = Unknown;
    }
	  /*else if(timer.iteration > timer.threshold && timer.iteration < (timer.threshold + TURNING_DURATION)) {
      BehaviorLog("Turning %d, threshold: %d, iteration: %d", timer.threshold + TURNING_DURATION - timer.iteration, timer.threshold, timer.iteration);
      goTowards(30,1);
      timer.enteredFrom = Unknown;
	  }*/
	  else {
	    BehaviorLog("Driving straight, (maybe) out of black area."); // well, this is not really true.......
      timer.enteredFrom = Unknown;
		  orientStraightAndDrive(1);
	  }
	  state.wasOnBlackInLastIteration = 0;
	 }
	 #endif
}
