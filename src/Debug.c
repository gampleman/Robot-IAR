#define Log(...) printf(__VA_ARGS__); printf("\n");
#define IDebug(arg) printf("arg = %d\n", arg);



#ifdef SHOULD_DEBUG_BEHAVIOR
char *previous_log;
char *current_log;
#define BehaviorLog(...) sprintf(current_log, __VA_ARGS__); \
if(strcmp(current_log, previous_log) != 0) {printf("%s\n", current_log); previous_log = current_log;}
#define BehaviorIDebug(arg) printf("arg = %d\n", arg);
#else
#define BehaviorLog(...) 
#define BehaviorIDebug(arg)
#endif

#ifdef SHOULD_DEBUG_MOVEMENT
#define MovementLog(...) printf(__VA_ARGS__); printf("\n");
#define MovementIDebug(arg) printf("arg = %d\n", arg)
#else
#define MovementLog(...) 
#define MovementIDebug(arg)
#endif

#ifdef SHOULD_DEBUG_SETUP
#define SetupLog(...) printf(__VA_ARGS__); printf("\n");
#define SetupIDebug(arg) printf("arg = %d\n", arg);
#else
#define SetupLog(...) 
#define SetupIDebug(arg)
#endif

#ifndef SHOULD_DEBUG_SENSOR
#define SensorLog(...) 
#define SensorIDebug(arg)
#else
#define SensorLog(...) printf(__VA_ARGS__); printf("\n");
#define SensorIDebug(arg) printf("arg = %d\n", arg);
#endif