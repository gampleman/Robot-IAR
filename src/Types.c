
struct stateT {
	unsigned int ServoPosition;
	unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
  	int LeftLight;
  	int RightLight;
} state;

struct timerT {
  int iteration;
  int threshold;
} timer;

