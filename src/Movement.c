

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



int turnServoBy(double Value)
{

	CPhidgetAdvancedServo_setPosition(servo, 0, Value);
	CPhidgetAdvancedServo_setEngaged(servo, 0, 1);

}

int motorHasntReachedDesiredPosition(double expected)
{
	double current;
	CPhidgetAdvancedServo_getPosition(servo, 0, &current);
	return fabs(current - expected) > 0.1;
}

int turnOnSpotRight()
{
	turnServoBy(20);
	sleep(3);
	driveRightMotor(50);
	driveLeftMotor(-40);
	return 0;
}

int turnOnSpotLeft()
{

	turnServoBy(220);
	sleep(3);
	driveRightMotor(-40);
	driveLeftMotor(50);
}

int stop()
{
	driveRightMotor(0.0);
	driveLeftMotor(0.0);
	return 0;
}
