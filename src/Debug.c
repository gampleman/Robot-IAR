/*
Debugging utilities. Enable debugging in one area by compling with `make DEBUG=flag` where flag is one of BEHAVIOR, MOVEMENT, SETUP or SENSOR.
*/

FILE *logbehavior;
FILE *logmovement;
FILE *logsensor;
FILE *logsetup;
time_t logtime;


int init_debugging() {
  time(&logtime);
  if((logbehavior = fopen("behavior.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1; 
  }
  if((logmovement=fopen("movement.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  if((logsensor=fopen("sensor.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  if((logsetup=fopen("setup.log", "w")) == NULL) {
    printf("Cannot open file.\n");
    return 1;
  }
  return 0;
}

int close_debugging() {
  fclose(logbehavior);
  fclose(logmovement);
  fclose(logsetup);
  fclose(logsensor);
}

int t() {
  time_t t;
  time(&t);
  return round(difftime(t, logtime));
}

#define Log(...) printf(__VA_ARGS__); printf("\n");
#define IDebug(arg) printf("arg = %d\n", arg);


#define BehaviorLog(...) printf(__VA_ARGS__); printf( "\n"); fprintf(logbehavior, "[%ds] ", t()); fprintf(logbehavior, __VA_ARGS__); fprintf(logbehavior, "\n"); 

#ifdef SHOULD_DEBUG_MOVEMENT
#define MovementLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(logmovement, __VA_ARGS__); fprintf(logmovement, "\n")
#define MovementIDebug(arg) printf("arg = %d\n", arg)
#else
#define MovementLog(...) fprintf(logmovement, __VA_ARGS__); fprintf(logmovement, "\n")
#define MovementIDebug(arg)
#endif

#ifdef SHOULD_DEBUG_SETUP
#define SetupLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(logsetup, __VA_ARGS__); fprintf(logsetup, "\n")
#define SetupIDebug(arg) printf("arg = %d\n", arg);
#else
#define SetupLog(...) fprintf(logsetup, __VA_ARGS__); fprintf(logsetup, "\n")
#define SetupIDebug(arg)
#endif

#ifndef SHOULD_DEBUG_SENSOR
#define SensorLog(...) fprintf(logsensor, __VA_ARGS__); fprintf(logsensor, "\n")
#define SensorIDebug(arg)
#else
#define SensorLog(...) printf(__VA_ARGS__); printf("\n"); fprintf(logsensor, __VA_ARGS__); fprintf(logsensor, "\n")
#define SensorIDebug(arg) printf("arg = %d\n", arg);
#endif