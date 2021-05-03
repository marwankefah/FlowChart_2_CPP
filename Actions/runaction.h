#pragma once
#include "Action.h"
class runaction :
	public Action
{
public:
	runaction(ApplicationManager *pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~runaction();
};

