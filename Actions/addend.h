#pragma once
#include "Action.h"
class addend :
	public Action
{
	Point position;

public:
addend(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addend();
};

