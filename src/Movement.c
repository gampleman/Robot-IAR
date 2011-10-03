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

int turnOnSpotLeft()
{
	
}

int turnServo(float Value)
{
	CPhidgetAdvancedServo_setPosition (servo, 0, Value);
}

int turnOnSpotRight()
{
	turnServo(50);
	driveRightMotor(50);
	driveLeftMotor(-40);
	
}

int stop()
{
	driveRightMotor(0.0);
	driveLeftMotor(0.0);
	return 0;
}