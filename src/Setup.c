int AttachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName(IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d attached!\n", name, serialNo);

	return 0;
}

int DetachHandler(CPhidgetHandle IFK, void *userptr)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (IFK, &name);
	CPhidget_getSerialNumber(IFK, &serialNo);

	printf("%s %10d detached!\n", name, serialNo);

	return 0;
}

int ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s", ErrorCode, unknown);
	return 0;
}

//callback that will run if an input changes.
//Index - Index of the input that generated the event, State - boolean (0 or 1) representing the input state (on or off)
int IKInputChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int State)
{	
	switch(Index)
	{
		case 0: 
			state.LeftWhisker = State;
			printf("Left Whisker: %d", State);
			break;
		case 1: 
			state.RightWhisker = State;
			printf("Right Whisker: %d", State);
			break;
		default: 
			printf("Digital Input: %d > State: %d\n", Index, State);
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

//callback that will run if the sensor value changes by more than the OnSensorChange trigger.
//Index - Index of the sensor that generated the event, Value - the sensor read value
int IKSensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value)
{
	switch(Index)
	{
		case 0: 
			printf("Spinning sensor: %d", Value);
			break;
		case 1:
			printf("Wheel-attached IR: %d", Value);
			break;
		case 2:
			printf("Front-facing IR: %d", Value);
			break;
		case 3: 
			printf("Sonar: %d", Value);
			break;
		case 4:
			printf("Light sensor: %d", Value);
			break;
		case 5:
			printf("Light sensor: %d", Value);
			break;
		case 6:
			printf("Light sensor: %d", Value);
			break;
		case 7:
			printf("Light sensor: %d", Value);
			break;
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

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Digital Inputs: %d\n# Digital Outputs: %d\n", numInputs, numOutputs);
	printf("# Sensors: %d\n", numSensors);
	printf("Ratiometric: %d\n", ratiometric);

	for(i = 0; i < numSensors; i++)
	{
		CPhidgetInterfaceKit_getSensorChangeTrigger (phid, i, &triggerVal);

		printf("Sensor#: %d > Sensitivity Trigger: %d\n", i, triggerVal);
	}

	return 0;
}


int MCInputChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, int State)
{
	printf("Input %d > State: %d\n", Index, State);
	return 0;
}

int MCVelocityChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	printf("Motor %d > Current Speed: %f\n", Index, Value);
	return 0;
}

int MCCurrentChangeHandler(CPhidgetMotorControlHandle MC, void *usrptr, int Index, double Value)
{
	printf("Motor: %d > Current Draw: %f\n", Index, Value);
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

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Inputs: %d\n# Motors: %d\n", numInputs, numMotors);

	return 0;
}


int ASPositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *usrptr, int Index, double Value)
{
	printf("Motor: %d > Current Position: %f\n", Index, Value);
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

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n# Motors: %d\n", serialNo, version, numMotors);

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
	printf("Waiting for interface kit to be attached....");
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
	printf("Waiting for MotorControl to be attached....");
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
	printf("Waiting for Phidget to be attached....");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)servo, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached device
	ASDisplayProperties(servo);
  CPhidgetAdvancedServo_setEngaged(servo, 0, 1);
	state.ServoPosition = 120;
	state.RightWhisker = 0;
	state.LeftWhisker = 0;
	return 0;
}

int teardown()
{
  printf("Closing...\n");
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