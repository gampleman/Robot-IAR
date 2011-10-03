int driveLeftMotor(float Value)
{
	CPhidgetMotorControl_setAcceleration (motoControl, 0, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 0, Value);
	return 0;
}

int driveRightMotor(float Value)
{
	CPhidgetMotorControl_setAcceleration (motoControl, 1, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 1, -1.0 * Value);
	return 0;
}



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
{
	double current;
	CPhidgetAdvancedServo_getPosition(servo, 0, &current);
	return fabs(current - expected) > 0.1;
}

int turnOnSpotRight()
{
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

int stop()
{
	driveRightMotor(0.0);
	driveLeftMotor(0.0);
	return 0;
}
