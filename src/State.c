#define TURNING_DURATION 4
#define LIGHT_INCREASE_THRESHOLD 0.3

#define Enter(what) if(timer.enteredFrom == Unknown) { BehaviorLog("Entered from what"); timer.enteredFrom = what;} else {timer.enteredFrom = Unknown;} 


enum Movement {Backwards, None, Forwards};
enum Direction {Left, Right};

/*
Describes state of the robots sensory inputs.
*/
struct stateT {
	unsigned int ServoPosition;
	unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
  int TopIR;
  int LeftLight;
  int RightLight;
  int TopRightLight;
  int TopLeftLight;
  double SpinSensor;
  float AverageBaseLight;
  float AverageTopLight;
  bool firstTopAverage;
  int ServoAngle;
  Movement expectedMovement;
  int expectedFor; //this name is kinda like whateverbool => i have no idea what the heck it's supposed to do...
  Direction lastWhiskerTriggered;
  bool wasOnBlackInLastIteration;
  int exitTrialCounter;
  bool sawFrequency;
  bool movedOntoTheNextOne;
  int previousState; // another obvious variable name, try to find out what this is doing - lol. 
  int stuckCounter; // i just <3 counting. btw, it sounds a bit like stock counter. i wish i had some stocks...
  int tempStuckCounter; // more counters!!!111one1!1
} state;


enum ENTRANCE { ELeft, Unknown, ERight};
/*
Contains state that is not reactive, one could say knowledge about the world.
*/
struct timerT {
  int iteration;
  int threshold;
  time_t lastTimeChange;
  float frequency;
  bool whateverbool; // a boolean to use for frequency calculation to indicate the start or end of a flash
  int timeSinceLastLight;
  ENTRANCE enteredFrom;
  timeval lastFlashSighted;
  bool foundStation;
  timeval lastSpinChange;
} timer;




