#include "Running.h"

void exitGame()
{
	__running = false;
}

bool _getrunning()
{
	return __running;
}

void _setrunning(bool s)
{
	__running = s;
}
