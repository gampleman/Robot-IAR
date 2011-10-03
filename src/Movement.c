
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


int goTowards(double angle)
{
	// angle must be within 0 and 180 degrees
	// 0 is the servo motor turned fully to the right
	// 180 is the servo motor turned fully to the left
	SERVO(20+(angle*(5/9)));
	sleep(1.2);
	DRIVE_LEFT(35*(angle/180));
	DRIVE_RIGHT(35*(1-(angle/180)));
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
	//turnServoTo(20);
	//sleep(0.8);
	//driveRightMotor(50);
	//driveLeftMotor(-40);
	goTowards(0);
	return 0;
}


int stop()
{
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}
