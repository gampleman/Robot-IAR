#define Log(...) printf(__VA_ARGS__); printf("\n");
#define IDebug(arg) printf("arg = %d\n", arg);

#ifdef SHOULD_DEBUG_BEHAVIOR
#define BehaviorLog(...) printf(__VA_ARGS__); printf("\n");
#define BehaviorIDebug(arg) printf("arg = %d\n", arg);
#else
#define BehaviorLog(...) 
#define BehaviorIDebug(arg)
#endif



#ifdef SHOULD_DEBUG_MOVEMENT
#define MovementLog(...) printf(__VA_ARGS__); printf("\n");
#define MovementIDebug(arg) printf("arg = %d\n", arg);
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