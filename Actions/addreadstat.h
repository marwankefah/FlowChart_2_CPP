#pragma once
#include "Action.h"
class addreadstat :public Action
{
Point position;
	string RHS;
    public:
	addreadstat(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addreadstat();
};

