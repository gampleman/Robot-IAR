// Macro to match imprecise measurements to a range of possible values
#define DELTA(a,b,c) (a < b + c && a > b - c)  
#define AT_BASE_WITH_FREQUENCY(n) (DELTA(state.frequency, n, 0.3))



/*
Attempts to match frequency to one of the known frequencies of stations. 
If a frequency is matched it executes a 'dance' and returns 1 (may not return immediately).
Otherwise returns 0.
*/
int dance() {
  if(AT_BASE_WITH_FREQUENCY(0.5)) {
    BehaviorLog("Dancin' to the tune of a frequency 0.5");
    driveBack();
    pause(0.5);
    turnOnSpotLeft();
    pause(6);
  } else if(AT_BASE_WITH_FREQUENCY(1)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 1");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(6);
   
  } else if(AT_BASE_WITH_FREQUENCY(2)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 2");
    driveBack();
    pause(0.5);
    stop();
    pause(1);
    driveBack();
  } else if(AT_BASE_WITH_FREQUENCY(4)) {
    // dance
    BehaviorLog("Dancin' to the tune of a frequency 4");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(3); // 180deg turn
    
  } else if(AT_BASE_WITH_FREQUENCY(6)) {
    BehaviorLog("Dancin' to the tune of a frequency 6");
    driveBack();
    pause(0.5);
    turnOnSpotRight();
    pause(3); // 180deg turn
    //get to next base
  } else if(AT_BASE_WITH_FREQUENCY(8)) {
    BehaviorLog("Dancin' to the tune of a frequency 8");
    // dance
    driveBack();
    pause(3);
    stop();
    pause(1);
    orientStraightAndDrive();
    pause(1);
    stop();
    pause(0.8);
    turnOnSpotRight();
    pause(3);
   
  } else { // no reasonable frequency detected
    state.frequency = 0;
    return 0;
  }
  BehaviorLog("Danced");
  state.AverageBaseLight = (float)10000;
  state.frequency = 0;
  state.wasOnBlackInLastIteration = 0;
  return 1;
}



/*
Main behavior function.
Called every 50ms unless something happens.
*/
void behave() {
  // Stuck detection
  if(sensor.SpinSensor == state.previousState) {
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
  state.previousState = sensor.SpinSensor;
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
      orientStraightAndDrive();
      msleep(1500L);
    }
  }
  else if (LEFT_LIGHT || RIGHT_LIGHT) {
    state.wasOnBlackInLastIteration = 1;
    if(sensor.FrontFacingIR > 420 && sensor.TopIR < 200 || state.frequency > 0.1) { // We see the gap
      if(state.frequency > 0.1)  {
        BehaviorLog("Seeing the gap (F: %d, T: %d)", sensor.FrontFacingIR, sensor.TopIR);
        BehaviorLog("Top Lights. Frequency: %f", state.frequency);
        if(!dance()) {
          BehaviorLog("Didn't dance");
          orientStraightAndDrive();
          sleep(2);
        }
      } else {
        BehaviorLog("Seeing the gap (F: %d, T: %d), but don't have frequency", sensor.FrontFacingIR, sensor.TopIR);
        orientStraightAndDrive();
        sleep(2);
      }
    } else if(sensor.RightWhisker && sensor.LeftWhisker == 0)  {
      BehaviorLog("Both light and right whisker");
      retreat(Left);
      msleep(700);
      state.lastWhiskerTriggered = Right;
    } else if(sensor.RightWhisker == 0 && sensor.LeftWhisker)  {
      BehaviorLog("Both light and left whisker");
      retreat(Right);
      msleep(700);
      state.lastWhiskerTriggered = Left;
    } else if(sensor.RightWhisker && sensor.LeftWhisker) {
      BehaviorLog("Both whiskers");
      retreat(Left);
      sleep(1);
      driveBack();
    }  else if(sensor.FrontFacingIR > 420) {
      BehaviorLog("Light & IR triggered (%d)", sensor.FrontFacingIR);
      driveBack();
      if(state.lastWhiskerTriggered == Right) {
        retreat(Right);
        state.lastWhiskerTriggered = Left;
      } else {
        retreat(Left);
        state.lastWhiskerTriggered = Right;
      }
      msleep(500);
    } else { // No whiskers 
      BehaviorLog("Both light and no whiskers");
      orientStraightAndDrive();
    }
  
  } else {
    if(state.wasOnBlackInLastIteration) {
      BehaviorLog("Exited black area and trying to return.");
      if(state.exitTrialCounter < 5) {
        if(state.lastWhiskerTriggered == Right) {
          turnOnSpotLeft();
          pause(0.6);
          orientStraightAndDrive();
        } else {
          turnOnSpotRight();
          pause(0.6);
          orientStraightAndDrive();
        }
        state.exitTrialCounter = state.exitTrialCounter + 1;
      } else {
        state.exitTrialCounter = 0;
      }
    }
    else if(sensor.LeftWhisker)  {
      BehaviorLog("Left whisker triggered");  
      retreat(Right);
      sleep(1);
      state.lastWhiskerTriggered = Left;
    }
    else if(sensor.RightWhisker) {
      BehaviorLog("Right whisker triggered");  
      retreat(Left);
      sleep(1); 
      driveBack();
      state.lastWhiskerTriggered = Right;
    }
    else if(sensor.FrontFacingIR > 450) {
      BehaviorLog("IR triggered (%d)", sensor.FrontFacingIR);
      driveBack();
      if(state.lastWhiskerTriggered == Right) {
        retreat(Right);
      } else {
        retreat(Left);
      }
      sleep(1);
      driveBack();
    } else {
	    BehaviorLog("Driving straight, (maybe) out of black area.");
		  orientStraightAndDrive();
	  }
	  state.wasOnBlackInLastIteration = 0;
	 }
}
