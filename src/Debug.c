/*
Debugging utilities. Enable debugging in one area by compling with `make DEBUG=flag` where flag is one of BEHAVIOR, MOVEMENT, SETUP or SENSOR.

Running this program will produce four files named behavior.log, movement.log, sensor.log & setup.log. Each has timestamped logging messages relative to program start. I recommend running them trough `uniq` to get rid of many uninteresting messages.
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
#define IDebug(arg) printf(#arg "= %d\n", arg);

#define AFLog(where, ...) printf(__VA_ARGS__); printf( "\n"); fprintf(where, "[%ds] ", t()); fprintf(where, __VA_ARGS__); fprintf(where, "\n"); 

#define FLog(where, ...) fprintf(where, "[%ds] ", t()); fprintf(where, __VA_ARGS__); fprintf(where, "\n"); 

#ifdef SHOULD_DEBUG_BEHAVIOR
#define BehaviorLog(...) AFLog(logbehavior, __VA_ARGS__)
#else
#define BehaviorLog(...) FLog(logbehavior, __VA_ARGS__)
#endif


#ifdef SHOULD_DEBUG_MOVEMENT
#define MovementLog(...) AFLog(logmovement, __VA_ARGS__)
#else
#define MovementLog(...) FLog(logmovement, __VA_ARGS__)
#endif

#ifdef SHOULD_DEBUG_SETUP
#define SetupLog(...) AFLog(logsetup, __VA_ARGS__)
#else
#define SetupLog(...) FLog(logsetup, __VA_ARGS__)
#endif

#ifndef SHOULD_DEBUG_SENSOR
#define SensorLog(...) FLog(logsensor, __VA_ARGS__)
#else
#define SensorLog(...) AFLog(logsensor, __VA_ARGS__)
#endif