#define DRIVE_RIGHT(Value) CPhidgetMotorControl_setVelocity (motoControl, 1, round(0.75 * Value))
#define SERVO(Value) CPhidgetAdvancedServo_setPosition(servo, 0, Value)

// Constant that can be set compile time to account for varying strength of battery.
#ifndef BATTERY
#define BATTERY 1
#endif

// Sleep function with arbitrary precision that takes into affect battery power allowing for more dynamic timing
#define pause(t) msleep((long)round(t * BATTERY * 1000))

// Used to be a macro like DRIVE_RIGHT. but now has some code to track intended movement for stuck detection.
// Also higher factor accounts for increased friciton due to hall sensor.
void DRIVE_LEFT(double Value) {
  Movement move;
  if(Value > 0) { 
    move = Forwards; 
  } else if(Value == 0) {
    move = None;
  } else { 
    move = Backwards;
  }
  if(state.expectedMovement != move) {
    state.expectedMovement = move;
    state.expectedFor = 0;
  }
  CPhidgetMotorControl_setVelocity (motoControl, 0, round(-0.9 *Value));
}



int stop()
{
  MovementLog("stop()");
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}


// This starts the process of turning left
int turnOnSpotLeft()
{
  MovementLog("turnOnSpotLeft()");
	if(state.ServoPosition != 1) 
	{
		SERVO(50);
		state.ServoPosition = 1;
	}
	DRIVE_RIGHT(100);
	DRIVE_LEFT(-80);
	return 0;
}


int turnOnSpotRight()
{
  MovementLog("turnOnSpotRight()");
	if(state.ServoPosition != -1)
	{
		SERVO(190);
		state.ServoPosition = -1;
	}
	DRIVE_RIGHT(-80);
	DRIVE_LEFT(100);
}

int orientStraightAndDrive()
{
  MovementLog("orientStraightAndDrive()");
	SERVO(120);
	DRIVE_RIGHT(70);
	DRIVE_LEFT(70);
	state.ServoPosition = 0;
	return 0;
}

int retreat(Direction direction)
{
  
	if(direction == Right)
	{
	  MovementLog("retreat(Right)");
		SERVO(190);
		DRIVE_LEFT(-30);
		DRIVE_RIGHT(-80);
	} else
	{
	  MovementLog("retreat(Left)");
		SERVO(50);
		DRIVE_LEFT(-80);
		DRIVE_RIGHT(-30);
	}
	return 0;
}

int driveBack()
{
  MovementLog("driveBack()");
	SERVO(120);
	DRIVE_RIGHT(-75);
	DRIVE_LEFT(-75);
	pause(1);
	return 0;
}
