#pragma once
#include "Action.h"
class addwritestat :public Action
{
Point position;
	string RHS;
    public:
	addwritestat(ApplicationManager* pmanager);
	virtual void ReadActionParameters();
	virtual void Execute();
	~addwritestat();
};

