#define LIGHT_INCREASE_THRESHOLD 0.3


enum Movement {Backwards, None, Forwards};
enum Direction {Left, Right};

struct Sensors {
  unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
  int TopIR;
  // These two are the bottom sensors
  int LeftLight;
  int RightLight;
  int TopRightLight;
  int TopLeftLight;
  double SpinSensor; // = Hall sensor
} sensor;


/*
Describes state of the robot.
*/
struct stateT {
	unsigned int ServoPosition;     // used to indicate whether or not the servo is set straight
  float AverageBaseLight;         // simply average of both of the bottom light sensors 
  Movement expectedMovement;      // Which way is the robot expected to move based on motor commands (simplest feedback possible)
  int expectedFor;                // How many cyckles is the robot stuck (TBD rename)
  Direction lastWhiskerTriggered; // Which whisker was last triggered
  bool wasOnBlackInLastIteration; 
  int exitTrialCounter;
  int previousState;              // Previous state of the Hall sensor
  int stuckCounter;               // For how many iterations has the Hall sensor not changed
  float frequency;                // Frequency detected so far
  bool flashWasOn;                // a boolean to use for frequency calculation to indicate the start or end of a flash
  timeval lastFlashSighted;       // Time when the last flash was seen
} state;




