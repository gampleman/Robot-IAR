/*
Debugging utilities. Enable debugging in one area by compling with `make DEBUG=flag` where flag is one of BEHAVIOR, MOVEMENT, SETUP or SENSOR.
*/
FILE *behavior;
FILE *movement;
FILE *sensor;
FILE *setup;


int init_debugging() {
  if((behavior=fopen("behavior.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  if((movement=fopen("movement.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  if((sensor=fopen("sensor.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  if((setup=fopen("setup.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  return 0;
}

#define Log(...) printf(__VA_ARGS__); printf("\n");
#define IDebug(arg) printf("arg = %d\n", arg);

#ifdef SHOULD_DEBUG_BEHAVIOR
#define BehaviorLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(behavior, __VA_ARGS__); fprintf(behavior, "\n")
#define BehaviorIDebug(arg) printf("arg = %d\n", arg);
#else
#define BehaviorLog(...) fprintf(behavior, __VA_ARGS__); fprintf(behavior, "\n")
#define BehaviorIDebug(arg)
#endif

#ifdef SHOULD_DEBUG_MOVEMENT
#define MovementLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(movement, __VA_ARGS__); fprintf(movement, "\n")
#define MovementIDebug(arg) printf("arg = %d\n", arg)
#else
#define MovementLog(...) fprintf(movement, __VA_ARGS__); fprintf(movement, "\n")
#define MovementIDebug(arg)
#endif

#ifdef SHOULD_DEBUG_SETUP
#define SetupLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(setup, __VA_ARGS__); fprintf(setup, "\n")
#define SetupIDebug(arg) printf("arg = %d\n", arg);
#else
#define SetupLog(...) fprintf(setup, __VA_ARGS__); fprintf(setup, "\n")
#define SetupIDebug(arg)
#endif

#ifndef SHOULD_DEBUG_SENSOR
#define SensorLog(...) fprintf(sensor, __VA_ARGS__); fprintf(sensor, "\n")
#define SensorIDebug(arg)
#else
#define SensorLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(sensor, __VA_ARGS__); fprintf(sensor, "\n")
#define SensorIDebug(arg) printf("arg = %d\n", arg);
#endif