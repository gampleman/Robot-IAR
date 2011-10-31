#define TURNING_DURATION 4
#define LIGHT_INCREASE_THRESHOLD 0.12

#define Enter(what) if(timer.enteredFrom == Unknown) { BehaviorLog("Entered from what"); timer.enteredFrom = what;} else {timer.enteredFrom = Unknown;} 


enum Movement {Backwards, None, Forwards};
enum Whisker {Left, Right};

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
  int SpinSensor;
  float AverageBaseLight;
  float AverageTopLight;
  bool firstTopAverage;
  int ServoAngle;
  Movement expectedMovement;
  Whisker lastWhiskerTriggered;
} state;


typedef enum ENTRANCE { ELeft, Unknown, ERight};
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
  

} timer;




