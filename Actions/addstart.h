#pragma once
#include "Action.h"
class addstart :
	public Action
{
	Point position;

public:
addstart(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addstart();
};

