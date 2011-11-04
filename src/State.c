#define LIGHT_INCREASE_THRESHOLD 0.3


enum Movement {Backwards, None, Forwards};
enum Direction {Left, Right};

struct Sensors {
  unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
  int TopIR;
  int LeftLight;
  int RightLight;
  int TopRightLight;
  int TopLeftLight;
  double SpinSensor;
} sensor;


/*
Describes state of the robot.
*/
struct stateT {
	unsigned int ServoPosition;
  float AverageBaseLight;
  Movement expectedMovement;
  int expectedFor; //this name is kinda like flashWasOn => i have no idea what the heck it's supposed to do...
  Direction lastWhiskerTriggered;
  bool wasOnBlackInLastIteration;
  int exitTrialCounter;
  int previousState; // another obvious variable name, try to find out what this is doing - lol. 
  int stuckCounter; // i just <3 counting. btw, it sounds a bit like stock counter. i wish i had some stocks...
  float frequency;
  bool flashWasOn; // a boolean to use for frequency calculation to indicate the start or end of a flash
  timeval lastFlashSighted;
} state;




