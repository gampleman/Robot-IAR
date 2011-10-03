UNAME := $(shell uname -s)
default:
ifeq ($(UNAME),Linux)
	g++ src/Main.c -o bin/main -lPhidget21
endif
ifeq ($(UNAME),Darwin)
	g++ src/Main.c -o bin/main -framework Phidget21 -I /Library/Frameworks/Phidget21.framework/Headers
endif
