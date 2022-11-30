#ifndef SMBROKER_H
#define SMBROKER_H

#include "SceneManager.h"

//Scene Manager Broker to redirect manager
struct SMBroker
{
public:
	SceneManager* sman;
};

#endif // !SMBROKER_H
