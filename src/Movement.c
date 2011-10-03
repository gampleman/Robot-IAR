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



int turnServoBy(double Value, double *expected)
{
	double curr_pos;
	if(CPhidgetAdvancedServo_getPosition(servo, 0, &curr_pos) == EPHIDGET_OK)
	{
		expected = Value + curr_pos;
		CPhidgetAdvancedServo_setPosition (servo, 0, expected);
		CPhidgetAdvancedServo_setEngaged(servo, 0, 1);
	} else {
		return -1;
	}
}

int motorHasntReachedDesiredPosition(expected)
{
	double current;
	CPhidgetAdvancedServo_getPosition(servo, 0, &current);
	return fabs(result - expectedResult) > 0.1;
}

int turnOnSpotRight()
{
	double expected;
	turnServoBy(50, &expected);
	while(motorHasntReachedDesiredPosition(expected)) {
		sleep(0.5);
	}
	driveRightMotor(50);
	driveLeftMotor(-40);
	return 0;
}

int turnOnSpotLeft()
{
	double expected;
	turnServoBy(-50, &expected);
	while(motorHasntReachedDesiredPosition(expected)) {
		sleep(0.5);
	}
	driveRightMotor(-40);
	driveLeftMotor(50);
}

int stop()
{
	driveRightMotor(0.0);
	driveLeftMotor(0.0);
	CPhidgetAdvancedServo_setEngaged(servo, 0, 0);
	return 0;
}