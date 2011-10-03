int driveLeftMotor(float Value)
{
	CPhidgetMotorControl_setAcceleration (motoControl, 0, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 0, Value);
}

int driveRightMotor(float Value)
{
	CPhidgetMotorControl_setAcceleration (motoControl, 1, 50.00);
	CPhidgetMotorControl_setVelocity (motoControl, 1, -1.0 * Value);
}