/*
This file containes the main sensor callbacks, that mainly just assign some variable to `state`.
Implements connection specs described in readme.md.
*/

#define LEFT_LIGHT (sensor.LeftLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
#define RIGHT_LIGHT (sensor.RightLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
#define TOP_LIGHT (sensor.TopRightLight > 100 || sensor.TopLeftLight  > 100)


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
      sensor.TopIR = Value;
			break;
		case 2:
			SensorLog("Front-facing IR: %d", Value);
			sensor.FrontFacingIR = Value;
			break;
		case 4:
			SensorLog("Right Light sensor: %d", Value);
      sensor.RightLight = Value;
			break;
		case 5:
			SensorLog("Left Light sensor: %d", Value);
			sensor.LeftLight = Value;
			break;
		case 6:
			SensorLog("Top Right Light sensor: %d", Value);
      sensor.TopRightLight = Value;
			break;
		case 7:
			SensorLog("Top Left Light sensor: %d", Value);
			sensor.TopLeftLight = Value;
			break;
	}
	
	// Creates an initial light threshold, since AverageBaseLight should be bigger then 200 only on initialization
	if(!LEFT_LIGHT && !RIGHT_LIGHT && state.AverageBaseLight > 200) {
    state.AverageBaseLight = ((float)sensor.LeftLight + (float)sensor.RightLight) / 2;
    SensorLog("Current base average: %f and current threshold: %f", state.AverageBaseLight, state.AverageBaseLight*(1+LIGHT_INCREASE_THRESHOLD));
  }
	
	// light is on and we haven't executed this block for this flash yet
	if(TOP_LIGHT && !state.flashWasOn) {
    // Get precise current time
    timeval tim;
    gettimeofday(&tim, NULL);
    // convert to double in seconds
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    // convert last measuerd time to seconds
    double t1 = state.lastFlashSighted.tv_sec + (state.lastFlashSighted.tv_usec/1000000.0);
    // convert time to frequency
    double f = 1.0 / (t2 - t1);
    // sanity check
    if(f < 10 && f > 0.1)
      state.frequency = f;
    SensorLog("Top Left delta"); 
    BehaviorLog("Sensed frequency in left top light %f (t = %f, t1 = %f, t2 = %f)", state.frequency, t2 - t1, t1, t2);
    // a blink was detected, don't execute this until the light is off
    state.flashWasOn = 1;
    // store measured value for next iteration
    state.lastFlashSighted = tim;
	}
	// light is off
	if(!TOP_LIGHT) {
	  state.flashWasOn = 0;
	}
	return 0;
}


//callback that will run if an input changes.
//Index - Index of the input that generated the event, State - boolean (0 or 1) representing the input state (on or off)
int IKInputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{	
  double t1, t2, v;
  timeval tim;
  
	switch(Index)
	{
		case 1: 
			sensor.LeftWhisker = State;
      SensorLog("LeftWhisker = %d", sensor.LeftWhisker);
			break;
		case 2: 
			sensor.RightWhisker = State;
      SensorLog("RightWhisker = %d", sensor.RightWhisker);
			break;
		case 7:
		  sensor.SpinSensor = State;
		  SensorLog("Spinsensor = %f", sensor.SpinSensor);
      break;
		default: 
			SensorLog("Digital Input: %d > State: %d", Index, State);
	}
	return 0;
}
