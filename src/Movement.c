<<<<<<< HEAD
int driveLeftMotor(float Value)
{
	CPhidgetMotorControl_setAcceleration (motoControl, 0, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 0, Value);
	return 0;
}
=======
#define DRIVE_LEFT(Value) CPhidgetMotorControl_setVelocity (motoControl, 0, Value)
#define DRIVE_RIGHT(Value) CPhidgetMotorControl_setVelocity (motoControl, 1, -1.0 * Value)
#define SERVO(Value) CPhidgetAdvancedServo_setPosition(servo, 0, Value)

//int ServoPosition = 0;

>>>>>>> 0c24d0a41d3d57b020edc4c597b1a1fd56ab18bb

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

<<<<<<< HEAD


int turnServoTo(double Value)
{

	CPhidgetAdvancedServo_setPosition(servo, 0, Value);
	CPhidgetAdvancedServo_setEngaged(servo, 0, 1);

}

int goTowards(double angle)
{
	// angle must be within 0 and 180 degrees
	// 0 is the servo motor turned fully to the right
	// 180 is the servo motor turned fully to the left
	turnServoTo(20+(angle*(5/9)));
	sleep(1.2);
	driveLeftMotor(35*(angle/180));
	driveRightMotor(35*(1-(angle/180)));
	return 0;
}

int motorHasntReachedDesiredPosition(double expected)
=======
int turnOnSpotLeft()
>>>>>>> 0c24d0a41d3d57b020edc4c597b1a1fd56ab18bb
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
<<<<<<< HEAD
	//turnServoTo(20);
	//sleep(0.8);
	//driveRightMotor(50);
	//driveLeftMotor(-40);
	goTowards(0);
	return 0;
}

int turnOnSpotLeft()
{

	turnServoTo(220);
	sleep(0.8);
	driveRightMotor(-40);
	driveLeftMotor(50);
}
=======
	if(state.ServoPosition != 0)
	{
		SERVO(110);
		sleep(2);
	}
	DRIVE_LEFT(50);
	DRIVE_RIGHT(50);
}

>>>>>>> 0c24d0a41d3d57b020edc4c597b1a1fd56ab18bb

int stop()
{
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}
