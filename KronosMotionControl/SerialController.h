#ifndef __KronosMotionControlSimulator__SerialController__
#define __KronosMotionControlSimulator__SerialController__

#include "Arduino.h"

#define DEFAULT_BAUD_RATE 9600
#define MAX_SERIAL_CALLBACKS 20

typedef void (*CallbackFunc)();

class SerialController{

public:
	
    SerialController(int baud=DEFAULT_BAUD_RATE);
	
	void begin();
	void loop();
	
	void addCommand(char *key,  CallbackFunc _func, char *docstring);
	void showCommands();

private:
	
	int baudrate;
	int nCallbacks;
	CallbackFunc callbackFuncs[MAX_SERIAL_CALLBACKS];
	char callbackTriggerKeys[MAX_SERIAL_CALLBACKS];
	char *callbackDocstrings[MAX_SERIAL_CALLBACKS];
	
};

#endif
