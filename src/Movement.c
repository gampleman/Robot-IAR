#define DRIVE_LEFT(Value) CPhidgetMotorControl_setVelocity (motoControl, 0, Value)
#define DRIVE_RIGHT(Value) CPhidgetMotorControl_setVelocity (motoControl, 1, -1.0 * Value)
#define SERVO(Value) CPhidgetAdvancedServo_setPosition(servo, 0, Value)

//int ServoPosition = 0;


int turnOnSpotRight()
{
	if(state.ServoPosition != 1) 
	{
		SERVO(20);
		sleep(2);
	}
	DRIVE_RIGHT(50);
	DRIVE_LEFT(-40);
	return 0;
}

int turnOnSpotLeft()
{
	if(state.ServoPosition != -1)
	{
		SERVO(220);
		sleep(2);
	}
	DRIVE_RIGHT(-40);
	DRIVE_LEFT(50);
}

int orientStraightAndDrive()
{
	if(state.ServoPosition != 0)
	{
		SERVO(110);
		sleep(2);
	}
	DRIVE_LEFT(50);
	DRIVE_RIGHT(50);
}


int stop()
{
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}
