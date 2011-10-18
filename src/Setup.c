int AttachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName(IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	SetupLog("%s %10d attached!", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	SetupLog("%s %10d detached!", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown)
{
	SetupLog("Error handled. %d - %s", ErrorCode, unknown);
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

//callback that will run if an output changes.
//Index - Index of the output that generated the event, State - boolean (0 or 1) representing the output state (on or off)
int IKOutputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{
	printf("Digital Output: %d > State: %d\n", Index, State);
	return 0;
}


#define LEFT_LIGHT (state.LeftLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
#define RIGHT_LIGHT (state.RightLight / state.AverageBaseLight  > 1 + LIGHT_INCREASE_THRESHOLD)
#define TOP_LIGHT (state.TopRightLight > 200 || state.TopLeftLight > 200)

/// state.AverageTopLight  > 1 + LIGHT_INCREASE_THRESHOLD)

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
			SensorLog("Wheel-attached IR: %d", Value);
			break;
		case 2:
			SensorLog("Front-facing IR: %d", Value);
			state.FrontFacingIR = Value;
			break;
		case 3: 
			SensorLog("Sonar: %d", Value);
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
    SensorLog("Assigned average: %f", state.AverageBaseLight);
  }
	
	if(TOP_LIGHT && !timer.whateverbool) {

    timer.frequency = timer.timeSinceLastLight;
    BehaviorLog("Sensed frequency in left top light %f %d", 20/(float)timer.frequency, timer.frequency);
    timer.whateverbool = 1;
    timer.timeSinceLastLight = 0;
	}
	if(!TOP_LIGHT) {
	  timer.whateverbool = 0;
	}
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
//Will also display the number of inputs, outputs, and analog inputs on the interface kit as well as the state of the ratiometric flag
//and the current analog sensor sensitivity.
int IKDisplayProperties(CPhidgetInterfaceKitHandle phid)
{
	int serialNo, version, numInputs, numOutputs, numSensors, triggerVal, ratiometric, i;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetInterfaceKit_getInputCount(phid, &numInputs);
	CPhidgetInterfaceKit_getOutputCount(phid, &numOutputs);
	CPhidgetInterfaceKit_getSensorCount(phid, &numSensors);
	CPhidgetInterfaceKit_getRatiometric(phid, &ratiometric);

	SetupLog("%s", ptr);
	SetupLog("Serial Number: %10d\nVersion: %8d", serialNo, version);
	SetupLog("# Digital Inputs: %d\n# Digital Outputs: %d", numInputs, numOutputs);
	SetupLog("# Sensors: %d", numSensors);
	SetupLog("Ratiometric: %d", ratiometric);

	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_getSensorChangeTrigger (phid, i, &triggerVal);

		SetupLog("Sensor#: %d > Sensitivity Trigger: %d\n", i, triggerVal);
	}

	return 0;
}


int MCInputChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, int State)
{
	SetupLog("Input %d > State: %d", Index, State);
	return 0;
}

int MCVelocityChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	SetupLog("Motor %d > Current Speed: %f", Index, Value);
	return 0;
}

int MCCurrentChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	SetupLog("Motor: %d > Current Draw: %f", Index, Value);
	return 0;
}

int MCDisplayProperties(CPhidgetMotorControlHandle phid)
{
	int serialNo, version, numInputs, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);
	
	CPhidgetMotorControl_getInputCount(phid, &numInputs);
	CPhidgetMotorControl_getMotorCount(phid, &numMotors);

	SetupLog("%s", ptr);
	SetupLog("Serial Number: %10d\nVersion: %8d", serialNo, version);
	SetupLog("# Inputs: %d\n# Motors: %d", numInputs, numMotors);

	return 0;
}


int ASPositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *usrptr, int Index, double Value)
{
	SetupLog("Motor: %d > Current Position: %f", Index, Value);
	return 0;
}

//Display the properties of the attached phidget to the screen.  We will be displaying the name, serial number and version of the attached device.
int ASDisplayProperties(CPhidgetAdvancedServoHandle phid)
{
	int serialNo, version, numMotors;
	const char* ptr;

	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);

	CPhidgetAdvancedServo_getMotorCount (phid, &numMotors);

	SetupLog("%s", ptr);
	SetupLog("Serial Number: %10d\nVersion: %8d\n# Motors: %d", serialNo, version, numMotors);

	return 0;
}



CPhidgetInterfaceKitHandle ifKit = 0;
CPhidgetMotorControlHandle motoControl = 0;
CPhidgetAdvancedServoHandle servo = 0;




int setup()
{
	int result, numSensors, i;
	const char *err;
  //handles *Handles;
	//Declare an InterfaceKit handle

	// Setup the IFKit
	CPhidgetInterfaceKit_create(&ifKit);
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)ifKit, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)ifKit, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)ifKit, ErrorHandler, NULL);
	CPhidgetInterfaceKit_set_OnInputChange_Handler (ifKit, IKInputChangeHandler, NULL);
	CPhidgetInterfaceKit_set_OnSensorChange_Handler (ifKit, IKSensorChangeHandler, NULL);
	CPhidgetInterfaceKit_set_OnOutputChange_Handler (ifKit, IKOutputChangeHandler, NULL);
	CPhidget_open((CPhidgetHandle)ifKit, -1);
  
	//get the program to wait for an interface kit device to be attached
	SetupLog("Waiting for interface kit to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)ifKit, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}
	//Display the properties of the attached interface kit device
	IKDisplayProperties(ifKit);

  // Setup motoControl
  
	CPhidgetMotorControl_create(&motoControl);
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)motoControl, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)motoControl, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)motoControl, ErrorHandler, NULL);
	CPhidgetMotorControl_set_OnInputChange_Handler (motoControl, MCInputChangeHandler, NULL);
	CPhidgetMotorControl_set_OnVelocityChange_Handler (motoControl, MCVelocityChangeHandler, NULL);
	CPhidgetMotorControl_set_OnCurrentChange_Handler (motoControl, MCCurrentChangeHandler, NULL);
	CPhidget_open((CPhidgetHandle)motoControl, -1);
	SetupLog("Waiting for MotorControl to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)motoControl, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}
	MCDisplayProperties(motoControl);
	CPhidgetMotorControl_setAcceleration (motoControl, 0, 50.00);
	CPhidgetMotorControl_setAcceleration (motoControl, 1, 50.00);

  // Setup AdvancedServo
	CPhidgetAdvancedServo_create(&servo);
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)servo, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)servo, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)servo, ErrorHandler, NULL);

	CPhidgetAdvancedServo_set_OnPositionChange_Handler(servo, ASPositionChangeHandler, NULL);
	CPhidget_open((CPhidgetHandle)servo, -1);
	SetupLog("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)servo, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached device
	ASDisplayProperties(servo);
  CPhidgetAdvancedServo_setEngaged(servo, 0, 1);
	state.ServoPosition = 0;
	state.RightWhisker = 0;
	state.LeftWhisker = 0;
	state.FrontFacingIR = 0;
  timer.threshold = 10;
  timer.iteration = 0;
  state.AverageBaseLight = 10000.0;
  state.TopLeftLight = 0;
  state.TopRightLight = 0;
  state.AverageTopLeftLight = 1000;
  state.AverageTopRightLight = 1000;
  timer.whateverbool = 0;
  timer.timeSinceLastLight = 0;
  #ifdef FREQUENCY
  timer.frequency = FREQUENCY;
  #endif
	#ifndef NO_POWERLIB
	power_button_reset();
	
	while(power_button_get_value()==0)
	{
		sleep(1);
	}
	#endif
	
	
	return 0;
}

int teardown()
{
  SetupLog("Closing...\n");
  #ifndef NO_POWERLIB
	power_button_reset();
	#endif
  
	
	CPhidgetAdvancedServo_setPosition(servo, 0, 120);
	sleep(2);
	// Close IFKIT
	CPhidget_close((CPhidgetHandle)ifKit);
	CPhidget_delete((CPhidgetHandle)ifKit);
	// close motoControl
  	CPhidget_close((CPhidgetHandle)motoControl);
	CPhidget_delete((CPhidgetHandle)motoControl);
	// disengage and close servo
	CPhidgetAdvancedServo_setEngaged(servo, 0, 0);
	CPhidget_close((CPhidgetHandle)servo);
	CPhidget_delete((CPhidgetHandle)servo);
	//all done, exit
	return 0;
}
