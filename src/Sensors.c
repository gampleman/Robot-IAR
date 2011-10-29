/*
This file containes the main sensor callbacks, that mainly just assign some variable to `state`.
Implements connection specs described in readme.md.
*/

#define LEFT_LIGHT (state.LeftLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
#define RIGHT_LIGHT (state.RightLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
//define TOP_LIGHT ((float)state.TopRightLight / state.AverageTopLight > 1.9 || (float)state.TopLeftLight / state.AverageTopLight > 1.9)

#define TOP_LIGHT (state.TopRightLight > 300 || state.TopLeftLight  > 300)


//callback that will run if the sensor value changes by more than the OnSensorChange trigger.
//Index - Index of the sensor that generated the event, Value - the sensor read value
int IKSensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
	switch(Index)
	{
		case 0: 
			SensorLog("Spinning sensor: %d", Value);
			break;
		case 1:
			SensorLog("Top IR: %d", Value);
      state.TopIR = Value;
			break;
		case 2:
			SensorLog("Front-facing IR: %d", Value);
			state.FrontFacingIR = Value;
			break;
		case 3: 
			SensorLog("Sonar: %d", Value);
      BehaviorLog("Sensing sonar strength: %d ", Value);
      //if(Value < 40)
      //  BehaviorLog("Sensor is close");
      Measurement sensor;
      sensor.ServoAngle = state.ServoAngle;
      sensor.SonarValue = Value;
      AddMeasurement(sensor);
			break;
		case 4:
			SensorLog("Right Light sensor: %d", Value);
      state.RightLight = Value;
			break;
		case 5:
			SensorLog("Left Light sensor: %d", Value);
			state.LeftLight = Value;
			break;
		case 6:
			SensorLog("Top Right Light sensor: %d", Value);
      state.TopRightLight = Value;
			break;
		case 7:
			SensorLog("Top Left Light sensor: %d", Value);
			state.TopLeftLight = Value;
			break;
	}
	
	if(!LEFT_LIGHT && !RIGHT_LIGHT) {
    state.AverageBaseLight = ((float)state.LeftLight + (float)state.RightLight) / 2;
    SensorLog("Assigned bottom average: %f", state.AverageBaseLight);
  }
	
	// light is on and we haven't executed this block for this flash yet
	if(TOP_LIGHT && !timer.whateverbool) {
    // Get precise current time
    timeval tim;
    gettimeofday(&tim, NULL);
    // convert to double in seconds
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    // convert last measuerd time to seconds
    double t1 = timer.lastFlashSighted.tv_sec + (timer.lastFlashSighted.tv_usec/1000000.0);
    // convert time to frequency
    double f = 1.0 / (t2 - t1);
    // sanity check
    if(f < 10 && f > 0.001)
      timer.frequency = f;
    SensorLog("Top Left delta"); 
    BehaviorLog("Sensed frequency in left top light %f (t = %f, t1 = %f, t2 = %f)", timer.frequency, t2 - t1, t1, t2);
    // a blink was detected, don't execute this until the light is off
    timer.whateverbool = 1;
    //timer.timeSinceLastLight = 0;
	}
	// light is off
	if(!TOP_LIGHT) {
	  timer.whateverbool = 0;
	  //if(state.firstTopAverage == 1) {
	    state.AverageTopLight = ((float)state.TopLeftLight + (float)state.TopRightLight) / 2;
	    SensorLog("Assigned top average: %f", state.AverageTopLight);
	    state.firstTopAverage = 0;
	  //}  
	}
	return 0;
}


//callback that will run if an input changes.
//Index - Index of the input that generated the event, State - boolean (0 or 1) representing the input state (on or off)
int IKInputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{	
	switch(Index)
	{
		case 1: 
			state.LeftWhisker = State;
      SensorIDebug(state.LeftWhisker);
			break;
		case 2: 
			state.RightWhisker = State;
      SensorIDebug(state.RightWhisker);
			break;
		//case 3:
		//	state.BlackBumper = State;
		//	printf("Black Bumper: %d", State);
		//	break;
		//case 4:
		//	state.RedBumper = State;
		//	printf("Red Bumper: %d", State);
		//	break;
		//case 5:
		//	state.RedPlateBumper = State;
		//	printf("Red plate Bumper: %d", State);
		//	break;
		//case 6:
		//	state.BlueBumper = State;
		//	printf("Blue Bumper: %d", State);
		//	break;
		default: 
			SensorLog("Digital Input: %d > State: %d", Index, State);
	}
	return 0;
}
