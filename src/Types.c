struct stateT {
	unsigned int ServoPosition;
	unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
} state;

struct timerT {
  int iteration = 0;
  int threshold;
  } timer;